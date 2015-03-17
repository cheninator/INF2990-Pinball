///////////////////////////////////////////////////////////////////////////
/// @file NoeudGate.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudGate.h"
#include "Utilitaire.h"
#include "../../Global/SingletonGlobal.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudGate::NoeudGate(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudGate::NoeudGate(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudGate::~NoeudGate()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudGate::~NoeudGate()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudGate::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudGate::afficherConcret() const
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
/// @fn void NoeudGate::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudGate::animer(float temps)
{
	NoeudComposite::animer(temps);
	if (!animer_)
		return;
	/* Animer ici */
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudGate::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudGate::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille)
///
/// Cette fonction effectue la r�action a la collision de la bille sur 
/// l'objet courant. Cette fonction est a reimplementer si on veut autre 
/// chose qu'un rebondissement ordinaire.
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudGate::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float facteurRebond)
{
	/* Traiter collision one way ici */
	NoeudAbstrait::traiterCollisions(details, bille);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille)
///
/// Reimplementation de detecterCollisions pour la Gate.  Si la Gate 
/// a etee frappee elle disparait (affiche_  devient false).  Si la Gate
/// est affichee, on fait le comportement par defaut donne dans NoeudAbstrait,
/// sinon, or retourne un DetailCollisions avec type COLLISION_AUCUNE.
/// 
/// @return details contient l'information sur la collision de la bille avec *this.
/// 
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudGate::detecterCollisions(NoeudAbstrait* noeud)
{
	/* Traiter collision one way ici */
	aidecollision::DetailsCollision detailsAucune;
	detailsAucune.type = aidecollision::COLLISION_AUCUNE;
	if (affiche_)
		return NoeudAbstrait::detecterCollisions(noeud);
	else
		return detailsAucune;
}
