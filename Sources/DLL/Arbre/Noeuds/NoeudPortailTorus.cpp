///////////////////////////////////////////////////////////////////////////
/// @file NoeudPortail.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudPortailTorus.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortailTorus::NoeudPortailTorus(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortailTorus::NoeudPortailTorus(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortailTorus::~NoeudPortailTorus()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortailTorus::~NoeudPortailTorus()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortailTorus::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortailTorus::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	NoeudAbstrait::appliquerAfficher();
	liste_->dessiner();
	glPopAttrib();
	glPopMatrix();
	// Restauration de la matrice.
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortailTorus::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortailTorus::animer(float temps)
{
	glm::dvec3 positionRelative = positionRelative_;
	NoeudComposite::animer(temps);
	positionRelative_ = positionRelative;
	if (!animer_)
		return;

	int direction = std::rand() % 2; // pcq ca me tente pas de dynamic cast un rand en Enum
	switch (direction)
	{
	case 0:
		rotation_.x += temps * VITESSE_NOEUD_PORTAIL_TORUS;
		break;
	case 1:
		rotation_.y += temps * VITESSE_NOEUD_PORTAIL_TORUS;
		break;
	case 2:
		rotation_.z += temps * VITESSE_NOEUD_PORTAIL_TORUS;
		break;
	}

	// Pour ne pas overflow le double un jour
	if (rotation_.x > 360)
		rotation_.x -= 360;
	if (rotation_.y > 360)
		rotation_.y -= 360;
	if (rotation_.z > 360)
		rotation_.z -= 360;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPortailTorus::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudPortailTorus::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	//if (vis->traiter(this))
	//	reussi = true;

	return reussi;

}