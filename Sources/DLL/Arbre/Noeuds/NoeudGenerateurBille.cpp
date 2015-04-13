///////////////////////////////////////////////////////////////////////////
/// @file NoeudGenerateurBille.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudGenerateurBille.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudGenerateurBille::NoeudGenerateurBille(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudGenerateurBille::NoeudGenerateurBille(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudGenerateurBille::~NoeudGenerateurBille()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudGenerateurBille::~NoeudGenerateurBille()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudGenerateurBille::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudGenerateurBille::afficherConcret() const
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
/// @fn void NoeudGenerateurBille::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudGenerateurBille::animer(float temps)
{
	if (positionRelative_.z == -posZinitial)
		affiche_ = false;
	else
		affiche_ = true;
	glm::dvec3 positionRelative = positionRelative_;
	NoeudComposite::animer(temps);
	positionRelative_ = positionRelative;
	if (enCreation_)
	{
		posZinitial = abs(boite_.coinMax.z * scale_.z);
		posZfinal = abs(boite_.coinMin.z * scale_.z);
		positionRelative_.z = posZfinal - posZinitial;;
		if (animer_)
			enCreation_ = false;
	}

	if (obtenirParent()->obtenirParent()->getEnfant(1)->obtenirAnimer())
	{
		positionRelative_.z = posZfinal - posZinitial;;
		return;
	}

	if (!animer_)
	{
		compteurAnimation_ = 0;
		positionRelative_.z = posZfinal - posZinitial;;
		return;
	}

	if (billesGenerer_ == 0)
	{
		positionRelative_.z = -posZinitial;
	}
	else if (billesGenerer_ > 0)
	{
		compteurGeneration_ += temps;
		if (compteurGeneration_ <= TIME_IDLE_NOEUD_BILLE)
			positionRelative_.z += temps * posZfinal / TIME_IDLE_NOEUD_BILLE;
		else if (compteurGeneration_ <= 2 * TIME_IDLE_NOEUD_BILLE)
			positionRelative_.z += temps * -(posZfinal + posZinitial) / TIME_IDLE_NOEUD_BILLE;
		else
		{
			compteurGeneration_ = 0;
			billesGenerer_ = 0;
			SingletonGlobal::obtenirInstance()->finGeneration();
		}
		return;
	}
	else if (billesGenerer_ <= -1)
	{
		compteurGeneration_ += temps;
		if (compteurGeneration_ <= TIME_IDLE_NOEUD_BILLE)
			;
		else if (compteurGeneration_ <= 2 * TIME_IDLE_NOEUD_BILLE)
			positionRelative_.z += temps * -(posZfinal + posZinitial) / TIME_IDLE_NOEUD_BILLE;
		else
		{
			compteurGeneration_ = 0;
			billesGenerer_ = 0;
			SingletonGlobal::obtenirInstance()->finGeneration();
		}
	}
	
	if (compteurAnimation_ >= TEMPS_ANIMATION_NOEUD_GENERATEURBILLE && etatGenerateur_ == INITIAL)
	{

		return;
	}
	shakeHead(temps);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudGenerateurBille::shakeHead(float temps)
///
/// Cette fonction effectue l'animation "shake" 
/// du noeud pour un certain intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudGenerateurBille::shakeHead(float temps)
{
	if (etatGenerateur_ == INITIAL) {
		if (selectionne_ || impossible_ || transparent_)
		{ 
			SoundControl->jouerSon("generateur", "true");
			return;
		}
		int direction = std::rand() % 4;
		switch (direction)
		{
		case 0:
			directionGenerateur_ = dirY;
			break;
		case 1:
			directionGenerateur_ = dirYX;
			break;
		case 2:
			directionGenerateur_ = dirX;
			break;
		case 3:
			directionGenerateur_ = dirXY;
			break;
		}
		distanceBouger_ = fmod(std::rand(), (2 * DISTANCE_MAX_NOEUD_GENERATEURBILLE + 1));
		if (distanceBouger_ > DISTANCE_MAX_NOEUD_GENERATEURBILLE)
			distanceBouger_ = -distanceBouger_ + DISTANCE_MAX_NOEUD_GENERATEURBILLE;
		positionPreDeplacement_ = positionRelative_;
		etatGenerateur_ = ALLER;
	}

	if (etatGenerateur_ != INITIAL)
		switch (directionGenerateur_)
	{
		case dirXY:
			positionRelative_.x += distanceBouger_ * temps / TEMPS_ANIMATION_MOUVEMENT_NOEUD_GENERATEURBILLE;
			positionRelative_.y += distanceBouger_ * temps / TEMPS_ANIMATION_MOUVEMENT_NOEUD_GENERATEURBILLE;
			break;
		case dirX:
			positionRelative_.x += distanceBouger_ * temps / TEMPS_ANIMATION_MOUVEMENT_NOEUD_GENERATEURBILLE;
			break;
		case dirY:
			positionRelative_.y += distanceBouger_ * temps / TEMPS_ANIMATION_MOUVEMENT_NOEUD_GENERATEURBILLE;
			break;
		case dirYX:
			positionRelative_.x -= distanceBouger_ * temps / TEMPS_ANIMATION_MOUVEMENT_NOEUD_GENERATEURBILLE;
			positionRelative_.y += distanceBouger_ * temps / TEMPS_ANIMATION_MOUVEMENT_NOEUD_GENERATEURBILLE;
			break;
		case dirZ:
			break;
	}

	if (etatGenerateur_ == ALLER)
	{
		if (compteurAnimationBouger_ >= TEMPS_ANIMATION_MOUVEMENT_NOEUD_GENERATEURBILLE)
		{
			etatGenerateur_ = RETOUR;
			distanceBouger_ *= -1;
			compteurAnimationBouger_ = 0;
		}
	}
	else if (etatGenerateur_ == RETOUR)
	{
		if (compteurAnimationBouger_ >= TEMPS_ANIMATION_MOUVEMENT_NOEUD_GENERATEURBILLE)
		{
			etatGenerateur_ = INITIAL;
			distanceBouger_ = 0;
			compteurAnimationBouger_ = 0;
			positionRelative_.x = positionPreDeplacement_.x;
			positionRelative_.y = positionPreDeplacement_.y;
		}
	}

	compteurAnimation_ += temps;
	compteurAnimationBouger_ += temps;

	if (leSonJoue == false)
	{
		SoundControl->jouerSon("generateur");
		leSonJoue = true;	
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudGenerateurBille::accepterVisiteur(VisiteurAbstrait* vis)
///
/// @brief Cette fonction appelle la methode traiter du visiteur.
///
/// @param[in] vis Pointeur sur le visiteur a accepter
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudGenerateurBille::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudGenerateurBille::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float facteurRebond)
///
/// @brief Implementation vide pour le generateur de billes.
///
/// @param[in] details Objet contenant les details de la collision a traiter
/// @param bille Objet modifie par la collision
/// @param[in] facteurRebond Facteur par lequel la vitesse normale de la bille sera multipliee
///
/// @return details contient l'information sur la collision de la bille avec *this.
///
////////////////////////////////////////////////////////////////////////
void NoeudGenerateurBille::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float facteurRebond)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn aidecollision::DetailsCollision NoeudGenerateurBille::detecterCollisions(NoeudAbstrait* bille)
///
/// @brief Implementation vide pour le generateur.
///
/// @param[in] bille Objet avec le noeud se compare pour trouver une collision.
///
/// @return details : contient l'information sur la collision de la bille avec *this.
///
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudGenerateurBille::detecterCollisions(NoeudAbstrait* noeud)
{
	aidecollision::DetailsCollision detail;
	return detail;
}