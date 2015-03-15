///////////////////////////////////////////////////////////////////////////
/// @file NoeudButoirCirculaire.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudButoirCirculaire.h"
#include "Utilitaire.h"
#include "../../Global/SingletonGlobal.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudButoirCirculaire::NoeudButoirCirculaire(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudButoirCirculaire::NoeudButoirCirculaire(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudButoirCirculaire::~NoeudButoirCirculaire()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudButoirCirculaire::~NoeudButoirCirculaire()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudButoirCirculaire::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirCirculaire::afficherConcret() const
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
	else if (illumine_){
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	}
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
/// @fn void NoeudButoirCirculaire::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirCirculaire::animer(float temps)
{
	NoeudComposite::animer(temps);
	if (!animer_)
		return;

	if (compteurIllumination_ < TEMPS_ILLUMINATION_NOEUD_BUTOIRCIRCULAIREE)
	{
		compteurIllumination_ += temps;
		illumine_ = true;
	}
	else
	{
		illumine_ = false;
	}

	if (selectionne_ || impossible_ || transparent_) 
	{
		if (etatButoir_ == INITIAL){
			ajustable_ = true;
			return;
		}
		else
			ajustable_ = false;
	}

	switch (etatButoir_)
	{
	case ALLER:
		scale_ *= 1 + temps * SCALE_MAX_NOEUD_BUTOIRCIRCULAIRE / TEMPS_DEMI_ANIMATION_NOEUD_BUTOIRCIRCULAIREE;
		if (compteurAnimation_ >= TEMPS_DEMI_ANIMATION_NOEUD_BUTOIRCIRCULAIREE / 2) 
		{
			Etat temp = etatButoir_;
			if (etatPrecedentButoir_ == INITIAL)
				etatButoir_ = RETOUR;
			else
				etatButoir_ = INITIAL;
			etatPrecedentButoir_ = temp;
			compteurAnimation_ = 0;
		}
		break;
	case RETOUR:
		scale_ *= 1 - temps * SCALE_MAX_NOEUD_BUTOIRCIRCULAIRE / TEMPS_DEMI_ANIMATION_NOEUD_BUTOIRCIRCULAIREE;
		if (compteurAnimation_ >= TEMPS_DEMI_ANIMATION_NOEUD_BUTOIRCIRCULAIREE / 2) 
		{
			Etat temp = etatButoir_;
			if (etatPrecedentButoir_ == INITIAL)
				etatButoir_ = ALLER;
			else
				etatButoir_ = INITIAL;
			etatPrecedentButoir_ = temp;
			compteurAnimation_ = 0;
		}
		break;
	case INITIAL:
		if (etatPrecedentButoir_ == INITIAL)
			etatButoir_ = ALLER;
		else
			etatButoir_ = etatPrecedentButoir_;
		etatPrecedentButoir_ = INITIAL;
		break;
	}

	compteurAnimation_+=temps;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudButoirCirculaire::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudButoirCirculaire::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<glm::dvec3> NoeudButoirCirculaire::obtenirVecteursEnglobants()
///
/// La boite englobante d'un butoir circulaire, c'est un rayon.
/// Pour etre conforme avec les boites englobantes des autres noeuds, 
/// on retourne quand meme un vector<glm::dvec3> mais avec un seul element
/// dont le x contient le rayon.
///
/// @return Un vecteur<glm::dvec3> dont le seul element a le rayon de l'objet
/// comme premiere coordonnee.
/// 
////////////////////////////////////////////////////////////////////////
std::vector<glm::dvec3> NoeudButoirCirculaire::obtenirVecteursEnglobants()
{
	double rayonModele = (boite_.coinMax.x - boite_.coinMin.x) / 2.0;
	return{ glm::dvec3{ rayonModele * scale_.x, 0, 0 } };
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void aidecollision::DetailsCollision NoeudAbstrait::detecterCollisions(NoeudAbstrait* bille)
///
/// Cette fonction retourne un objet detail collision pour la 
/// collision de la bille sur l'objet courant.
///
/// @return details contient l'information sur la collision de la bille avec *this.
///
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudButoirCirculaire::detecterCollisions(NoeudAbstrait* bille)
{
	std::vector<glm::dvec3> boite = obtenirVecteursEnglobants();
	double rayonBille = bille->obtenirVecteursEnglobants()[0].x;
	aidecollision::DetailsCollision details;
	double rayon = boite[0].x;
	details = aidecollision::calculerCollisionCercle((glm::dvec2)obtenirPositionRelative(), rayon, (glm::dvec2)bille->obtenirPositionRelative(), rayonBille);
	if (details.type != aidecollision::COLLISION_AUCUNE)
	{
		return details;
	}
	return details;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille)
///
/// Cette fonction effectue la réaction a la collision de la bille sur 
/// l'objet courant. Cette fonction est a reimplementer si on veut autre 
/// chose qu'un rebondissement ordinaire.
///
/// @return details contient l'information sur la collision de la bille avec *this.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirCirculaire::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille)
{
	NoeudAbstrait::traiterCollisions(details, bille);
	SingletonGlobal::obtenirInstance()->collisionButoirCirculaire();
	compteurIllumination_ = 0;
}