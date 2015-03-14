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
	//NoeudComposite::animer(temps);
	for (NoeudAbstrait * enfant : enfants_) {
		enfant->animer(temps);
	}
	positionRelative_.z = abs(obtenirVecteursEnglobants()[0].z);
	// Au lieu de rajouter une condition "parkinson" fais juste return;
	// Mais la je vais juste faire du parkinson pour quelques ssecodne puis s'arrete
	if (compteurAnimation_ >= TEMPS_ANIMATION_NOEUD_GENERATEURBILLE && etatGenerateur_ == INITIAL)
		return;
	
	if (etatGenerateur_ == INITIAL) {
		if (selectionne_ || impossible_ || transparent_)
			return;
		int direction = std::rand() % 4; // pcq ca me tente pas de dynamic cast un rand en Enum
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
			positionRelative_ = positionPreDeplacement_;
		}
	}

	compteurAnimation_ += temps;
	compteurAnimationBouger_ += temps;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudGenerateurBille::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
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

