///////////////////////////////////////////////////////////////////////////
/// @file NoeudRessort.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudRessort.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <iostream>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRessort::NoeudRessort(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRessort::NoeudRessort(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	assignerEstAjustable(false);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRessort::~NoeudRessort()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRessort::~NoeudRessort()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRessort::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRessort::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du modele.
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	if (colorShift_)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	if (pause_) {
		glBlendFunc(GL_SRC_ALPHA, GL_ZERO); // Set The Blending Function For Translucency
		glEnable(GL_BLEND);
	}
	else if (impossible_)
		glColorMask(0, 1, 1, 1);
	else if (selectionne_) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
		if (twin_ != nullptr && twin_ != NULL)
			twin_->setTransparent(true);

	}
	else if (transparent_) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	else
		if (twin_ != nullptr && twin_ != NULL)
			twin_->setTransparent(false);
	if (twin_ != nullptr && twin_ != NULL)
		if (!selectionne_ && !twin_->estSelectionne())
			twin_->setTransparent(false);
	liste_->dessiner();
	glPopAttrib();
	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRessort::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRessort::animer(float temps)
{
	NoeudComposite::animer(temps);
	if (!animer_)
		return;
	switch (etatRessort_)
	{
	case EN_COMPRESSION:
		if (scale_.y > 0.3)
		{
			scale_ = { scale_.x, scale_.y * exp(temps * log(0.002)), scale_.z }; // exp(temps * log(0.002)) = 0.002^temps
			positionRelative_ -= scale_.y /5 * translationCompression_ ; // Très heuristique comme calcul 
			// Updater l'attribut distanceCompresseion_
		}
		break;

	case EN_DECOMPRESSION:
		if (scale_.y < scaleYOriginal_)
		{
			scale_ = { scale_.x, scale_.y * exp(-temps * log(0.0002)), scale_.z }; // exp(-temps * log(0.002)) = 0.002^(-temps)
			positionRelative_ += scale_.y/5 * translationCompression_;
			// Updater l'attribut distanceCompresseion_ 
		}
			// La decompression devra etre reimplementee pour respecter l'equation differentielle
		if (scale_.y > scaleYOriginal_)
		{
			scale_ = { scale_.x, scaleYOriginal_, scale_.z };
			positionRelative_ = positionOriginale_;
			// Updater l'attribut distanceCompresseion_ 
			etatRessort_ = LANCER_BILLE;
		}
		break;

	case LANCER_BILLE:

		etatRessort_ = AU_REPOS;

		break;

	case AU_REPOS:
		
		break;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRessort::compresser()
///
/// Cette fonction active l'animation qui fait compresser les ressorts. On en
/// profite pour sauvegarder le scale initial et pour definir un vecteur 
/// qui servira a faire en sorte que la base du ressort reste sur place.
/// 
/// @remark appelee quand la bonne touche est appuyee.
///
////////////////////////////////////////////////////////////////////////
void NoeudRessort::compresser()
{
	if (etatRessort_ == AU_REPOS)
	{
		double longueurOriginale_ = scale_.y *(boite_.coinMax.y - boite_.coinMin.y);
		scaleYOriginal_ = obtenirAgrandissement().y;
		positionOriginale_ = positionRelative_;
		double angleEnRadian = -rotation_[2] * utilitaire::PI_180;
		glm::dmat3 transform = glm::dmat3{ glm::dvec3{ cos(angleEnRadian), -sin(angleEnRadian), 0.0 },
											glm::dvec3{ sin(angleEnRadian), cos(angleEnRadian), 0.0f },
											glm::dvec3{ 0.0, 0.0, 1.0 } };
		translationCompression_ = transform * glm::dvec3{ 0, 0.8, 0 };
	}

	etatRessort_ = EN_COMPRESSION;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudRessort::relacher()
///
/// Cette fonction active l'animation qui fait relacher le ressort.
///
/// @remark appelee quand la bonne touche est relachee
///
////////////////////////////////////////////////////////////////////////
void NoeudRessort::relacher()
{
	//                                 longueur originale                           -            Longueur courante.
	// distanceCompression_ = scaleYOriginal_*(boite_.coinMax.y - boite_.coinMin.y) - scale_.y*(boite_.coinMax.y - boite_.coinMin.y);
	distanceCompression_ = (scaleYOriginal_ - scale_.y) * (boite_.coinMax.y - boite_.coinMin.y);
	std::cout << "Distance compression " << distanceCompression_ << std::endl;
	etatRessort_ = EN_DECOMPRESSION;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudRessort::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudRessort::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}



void NoeudRessort::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float facteurRebond)
{
	switch (etatRessort_)
	{
	case EN_COMPRESSION:
	case AU_REPOS:	
		NoeudAbstrait::traiterCollisions(details, bille, 0.2);
		break;

	case EN_DECOMPRESSION:
		bille->assignerPositionRelative(bille->obtenirPositionRelative() + details.enfoncement * details.direction); // direction est un vecteur normal.
		break;

	case LANCER_BILLE:
		
		// energiePotentielle = (1. / 2.) * constanteRessort * (distanceCompression_*distanceCompression_);
		// Energie cinetique = 1/2 m v^2
		// ==> 2 E / m = v^2
		// ==> sqrt(2 E / m) = v,
		// Conservation d'energie : energie cinetique donnee a la bille = energie emmagasinee dans le ressort.
		// ==> v = sqrt(2 (1/2 constanteRessort* distanceCompression^2 / m)
		// ==> v = sqrt(constRessort/m) * distanceCompression
		// ==> v = uneConstante * distanceCompression.
		std::cout << "TraiterCollision en etat LANCER_BILLE" << std::endl;
		double uneConstante = 400;
		bille->assignerPositionRelative(bille->obtenirPositionRelative() + 1.1*details.enfoncement * details.direction); // direction est un vecteur normal.
		bille->assignerVitesse(uneConstante * distanceCompression_ * details.direction);
	
		break;

	}
}