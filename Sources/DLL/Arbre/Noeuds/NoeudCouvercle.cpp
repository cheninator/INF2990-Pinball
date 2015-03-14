///////////////////////////////////////////////////////////////////////////
/// @file NoeudCouvercle.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudCouvercle.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCouvercle::NoeudCouvercle(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCouvercle::NoeudCouvercle(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	assignerSelection(false);
	selectionnable_ = false;
	modifiable_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCouvercle::~NoeudCouvercle()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCouvercle::~NoeudCouvercle()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCouvercle::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCouvercle::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	glTranslatef(200, -50, 0);
	// To remove for animation
	//glTranslatef( -117, 0, 0 );
	// glRotatef(-45.0, 0, 1, 0 );
	// Affichage du modele.
	glStencilFunc(GL_ALWAYS, 0, -1);
	liste_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCouvercle::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCouvercle::animer(float temps)
{
	static const double deplacement = abs(abs(boite_.coinMax.y - boite_.coinMin.y) * scale_.x * sin(INCLINAISON_NOEUD_COUVERCLE)) - MARGE_NOEUD_COUVERCLE;
	// Appel a la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);
	if (positionRelative_.x > -deplacement) {
		positionRelative_.x -= temps * (deplacement / TEMPS_ANIMATION_NOEUD_COUVERCLE);
		rotation_.y -= INCLINAISON_NOEUD_COUVERCLE / (TEMPS_ANIMATION_NOEUD_COUVERCLE / temps);
		positionRelative_.z -= temps * (deplacement / TEMPS_ANIMATION_NOEUD_COUVERCLE);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool bool NoeudCouvercle::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudCouvercle::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

