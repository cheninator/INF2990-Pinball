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


std::vector<glm::dvec3> NoeudGate::boiteEnglobanteModele_{
	{ 2.17, -1.86, 0.0 },
	{ -56.0, -1.86, 0.0 },
	{ -56.0, 1.86, 0.0 },
	{ 2.17, 1.86, 0.0 }
};

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
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	NoeudAbstrait::appliquerAfficher();
	liste_->dessiner();
	glPopAttrib();
	glPopMatrix();
	// Restauration de la matrice.
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
/// @brief Cette fonction appelle la methode traiter du visiteur.
///
/// @param[in] vis Pointeur sur le visiteur a accepter
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
/// Cette fonction effectue la réaction a la collision de la bille sur 
/// l'objet courant. Cette fonction est a reimplementer si on veut autre 
/// chose qu'un rebondissement ordinaire.
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudGate::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float)
{
	glm::dvec3 vitesse = bille->obtenirVitesse();
	double angleGate = rotation_[2] * utilitaire::PI_180;
	glm::dvec3 vitesseEnCoordonneesDuGate = { cos(angleGate) *vitesse.x +sin(angleGate)*vitesse.y,
												-sin(angleGate)*vitesse.x + cos(angleGate)*vitesse.y, 
												0 };
	if (vitesseEnCoordonneesDuGate.y > 0) return;
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
aidecollision::DetailsCollision NoeudGate::detecterCollisions(NoeudAbstrait* bille)
{
	/* Traiter collision one way ici */
	aidecollision::DetailsCollision detailsAucune;
	detailsAucune.type = aidecollision::COLLISION_AUCUNE;
	if (affiche_)
		return NoeudAbstrait::detecterCollisions(bille);
	else
		return detailsAucune;
}


std::vector<glm::dvec3> NoeudGate::obtenirVecteursEnglobants()
{
	std::vector<glm::dvec3> boiteEnglobanteObjet;

	glm::dmat3 echelle = glm::dmat3{ glm::dvec3{ scale_.x, 0, 0.0 },
		glm::dvec3{ 0, scale_.y, 0.0f },
		glm::dvec3{ 0.0, 0.0, scale_.z } };

	double angleEnRadian = -rotation_[2] * utilitaire::PI_180;
	glm::dmat3 transform = glm::dmat3{ glm::dvec3{ cos(angleEnRadian), -sin(angleEnRadian), 0.0 },
		glm::dvec3{ sin(angleEnRadian), cos(angleEnRadian), 0.0f },
		glm::dvec3{ 0.0, 0.0, 1.0 } };

	for (glm::dvec3 vecteur : boiteEnglobanteModele_)
	{
		boiteEnglobanteObjet.push_back(transform * (.7*echelle * vecteur));
	}

	return boiteEnglobanteObjet;
}