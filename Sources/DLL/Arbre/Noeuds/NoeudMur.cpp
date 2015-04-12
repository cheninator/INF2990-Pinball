///////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudMur.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::NoeudMur(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::NoeudMur(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::~NoeudMur()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::~NoeudMur()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::afficherConcret() const
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
/// @fn void NoeudMur::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::animer(float temps)
{
	NoeudComposite::animer(temps);
	if (!animer_)
		return;
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
void NoeudMur::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float facteurRebond)
{
	NoeudAbstrait::traiterCollisions(details, bille);
	SoundControl->jouerSon("wall.wav");
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudMur::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudMur::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

