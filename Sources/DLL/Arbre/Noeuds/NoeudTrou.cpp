///////////////////////////////////////////////////////////////////////////
/// @file NoeudTrou.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudTrou.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "../../Application/FacadeModele.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTrou::NoeudTrou(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTrou::NoeudTrou(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTrou::~NoeudTrou()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTrou::~NoeudTrou()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTrou::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTrou::afficherConcret() const
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
/// @fn void NoeudTrou::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTrou::animer(float temps)
{
	NoeudComposite::animer(temps);
	positionRelative_.z = 0;
	if (!animer_)
		return;
	rotation_.z += temps * VITESSE_NOEUD_TROU;
	// Pour ne pas overflow le double un jour
	if (rotation_.z > 360)
		rotation_.z -= 360;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTrou::accepterVisiteur(VisiteurAbstrait* vis)
///
/// @brief Cette fonction appelle la methode traiter du visiteur.
///
/// @param[in] vis Pointeur sur le visiteur a accepter
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudTrou::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<glm::dvec3> NoeudTrou::obtenirVecteursEnglobants()
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
std::vector<glm::dvec3> NoeudTrou::obtenirVecteursEnglobants()
{
	double rayonModele = (boite_.coinMax.x - boite_.coinMin.x) / 2.0;
	return{ glm::dvec3{ rayonModele * scale_.x, 0, 0 } };
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTrou::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille)
///
/// Cette fonction effectue la reaction a la collision de la bille sur 
/// un trou.  C'est-a-dire effacer la bille.  
///
/// @remark un pointeur vers la bille effacee existe encore dans la
/// liste des noeuds et liste des billes.  Voir FacadeModele::traiterCollisions()
/// pour voir les etapes supplementaires que l'effacement d'une bille necessite.
/// 
////////////////////////////////////////////////////////////////////////
void NoeudTrou::traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille, float facteurRebond)
{
	SoundControl->jouerSon("hole2");
	// bille->obtenirParent()->effacer(bille);
}