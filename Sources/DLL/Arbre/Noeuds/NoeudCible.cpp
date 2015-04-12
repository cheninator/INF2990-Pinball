///////////////////////////////////////////////////////////////////////////
/// @file NoeudCible.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudCible.h"
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
/// @fn NoeudCible::NoeudCible(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCible::NoeudCible(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCible::~NoeudCible()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCible::~NoeudCible()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCible::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCible::afficherConcret() const
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
/// @fn void NoeudCible::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCible::animer(float temps)
{
	NoeudComposite::animer(temps);
	if (!animer_)
		return;
	//positionRelative_.z = (boite_.coinMax.y - boite_.coinMin.y) / 2.0;
	rotation_.x += temps * VITESSE_NOEUD_CIBLE;
	// Pour ne pas overflow le double un jour
	if (rotation_.x > 360)
		rotation_.x = rotation_.x - 360;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudCible::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudCible::accepterVisiteur(VisiteurAbstrait* vis)
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
/// Cette fonction effectue la réaction a la collision de la bille sur 
/// l'objet courant. Cette fonction est a reimplementer si on veut autre 
/// chose qu'un rebondissement ordinaire.
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudCible::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float facteurRebond)
{
	NoeudAbstrait::traiterCollisions(details, bille);
	this->assignerAffiche(false);
	SingletonGlobal::obtenirInstance()->collisionButoirCible();
	SoundControl->jouerSon("cible.wav");
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille)
///
/// Reimplementation de detecterCollisions pour la cible.  Si la cible 
/// a etee frappee elle disparait (affiche_  devient false).  Si la cible
/// est affichee, on fait le comportement par defaut donne dans NoeudAbstrait,
/// sinon, or retourne un DetailCollisions avec type COLLISION_AUCUNE.
/// 
/// @return details contient l'information sur la collision de la bille avec *this.
/// 
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudCible::detecterCollisions(NoeudAbstrait* noeud)
{
	aidecollision::DetailsCollision detailsAucune;
	detailsAucune.type = aidecollision::COLLISION_AUCUNE;
	if (affiche_)
		return NoeudAbstrait::detecterCollisions(noeud);
	else
		return detailsAucune;
}
