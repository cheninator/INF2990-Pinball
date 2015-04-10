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

# define deplacementCouvercle abs(SingletonGlobal::obtenirInstance()->obtenirBoiteTable().coinMax.x - SingletonGlobal::obtenirInstance()->obtenirBoiteTable().coinMin.x + MARGE_NOEUD_COUVERCLE)
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
	//glPushAttrib(GL_ALL_ATTRIB_BITS);
	glTranslatef(TRANSLATE_X_NOEUD_TABLE + translateX, TRANSLATE_Y_NOEUD_TABLE, 0);
	//NoeudAbstrait::appliquerAfficher();
	glStencilFunc(GL_ALWAYS, 0, -1);
	liste_->dessiner();
	//glPopAttrib();
	glPopMatrix();
	// Restauration de la matrice.
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
	static bool firstTime = true;
	if (firstTime || translateX == 0)
	{
		// Appel a la version de la classe de base pour l'animation des enfants.
		double tableZ = SingletonGlobal::obtenirInstance()->obtenirBoiteTable().coinMax.z
			- obtenirParent()->getEnfant(0)->obtenirPositionRelative().z;
		double couvercleZ = boite_.coinMin.z;
		// pourquoi 3 ? AUCUNE IDEE
		positionRelative_.z = 3*(tableZ - couvercleZ);
		firstTime = false;
	}
	for (NoeudAbstrait * enfant : enfants_) {
		enfant->animer(temps);
	}
	//if (!animer_)
	//	return;

	if (translateX > -deplacementCouvercle) {
		translateX -= temps * (deplacementCouvercle / TEMPS_ANIMATION_NOEUD_COUVERCLE);
		rotation_.y -= INCLINAISON_NOEUD_COUVERCLE / (TEMPS_ANIMATION_NOEUD_COUVERCLE / temps);
		//positionRelative_.z = temps * (deplacement / TEMPS_ANIMATION_NOEUD_COUVERCLE);
	}
	else
		animer_ = false;
	double useless = positionRelative_.z;
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

