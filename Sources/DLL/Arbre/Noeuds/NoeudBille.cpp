///////////////////////////////////////////////////////////////////////////
/// @file NoeudBille.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudBille.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBille::NoeudBille(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBille::NoeudBille(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	vitesse_ = glm::dvec3{ 10,60, 0 };
	constanteDeFrottement_ = 1.0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBille::~NoeudBille()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBille::~NoeudBille()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::afficherConcret() const
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

	glTranslatef(0.0, -10, 0.0); // Il faudrait changer le modèle
	liste_->dessiner();
	glPopAttrib();
	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::animer(float temps) // rajouter des parametres ou une fonction animerCollision(float temps, detailCollision detail)
{
	bool animer_ = false;
	if (animer_ == false)
		return;
	// Somme des forces agissant sur les particules.
	
	glm::dvec3 attractionsPortails{ 0, 0, 0 };
	glm::dvec3 gravite{ 0, -20*masse_, 0 };
	glm::dvec3 forceFrottement{ 0, 0, 0 };
	if (glm::length(vitesse_) > 0.001)
		forceFrottement = -constanteDeFrottement_ * glm::normalize(vitesse_);
	glm::dvec3 forceTotale = forceFrottement + gravite + attractionsPortails;

	// Calcul de la nouvelle positon.
	glm::dvec3 nouvellePosition = positionRelative_ +(double)temps*vitesse_;

	// Calcul de la nouvelle vitesse. Ici, je fais une gestion elementaire de collision,
	// cette gestion devrait/pourrait probablement etre faite ailleur dans le code.
	glm::dvec3 nouvelleVitesse;
	if (positionRelative_.y < -190 && vitesse_.y < 0) // A faire avec des boites englobantes
	{
		glm::dvec3 normale = glm::normalize(glm::dvec3{ 0, 1, 0 });
		glm::dvec3 composanteNormale = glm::dot(normale, vitesse_)*normale;
		glm::dvec3 composanteTangentielle = vitesse_ - composanteNormale;

		nouvelleVitesse = (-composanteNormale + composanteTangentielle) + (double)temps * forceTotale / masse_;
	}
	else
		nouvelleVitesse = vitesse_ + (double)temps * forceTotale / masse_;

	// Calcul de la rotation
	// C'est pas la bonne facon de calculer la rotation a appliquer a la boule,
	// C'est pas un bug, j'ai just pas encore trouve la bonne facon de le faire.
	double constanteACalculer{ 0.1 }; // Depend du rayon de la boule, mais avec 0.1, ca parait deja bien.
	glm::dvec3 rotation{ 0, 0, 0 };
	rotation.x = constanteACalculer * -vitesse_.y;
	rotation.y = constanteACalculer * vitesse_.x;

	// Assignation des nouvelles valeurs.
	assignerRotation(rotation);
	positionRelative_ = nouvellePosition;
	vitesse_ = nouvelleVitesse;
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudBille::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudBille::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

