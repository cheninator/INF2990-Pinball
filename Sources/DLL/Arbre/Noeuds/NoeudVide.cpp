///////////////////////////////////////////////////////////////////////////
/// @file NoeudVide.cpp
/// @author Yonni Chen
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudVide.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBille::NoeudBille(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud � cr�er.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudVide::NoeudVide(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudVide::~NoeudVide()
///
/// Ce destructeur d�sallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudVide::~NoeudVide()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudVide::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudVide::afficherConcret() const
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudVide::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudVide::animer(float temps)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudVide::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la m�thode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudVide::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;
	
	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

