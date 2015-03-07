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
	direction_ = 0;
	power_ = 0;
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
	NoeudComposite::animer(temps);
	
	// Au lieu de rajouter une condition "parkinson" fais juste return;
	// Mais la je vais juste faire du parkinson pour quelques ssecodne puis s'arrete
	static int compteur = 200;
	compteur--;
	if (compteur <= 0)
		return;
	
	if (direction_ == 0) {
		if (selectionne_ || impossible_ || transparent_)
			return;
		direction_ = std::rand() % 4 + 1;
		power_ = std::rand() % 11;
		if (power_ > 5)
			power_ = -power_ + 5;
	}
	else if (direction_ > 0) {
		direction_ *= -1;
		power_ *= -1;
	}
	else
		direction_ = 0;


	switch (abs(direction_))
	{
	case 1:
		positionRelative_.x += power_;
		positionRelative_.y += power_;
		break;
	case 2:
		positionRelative_.x += power_;
		break;
	case 3:
		positionRelative_.y += power_;
		break;
	case 4:
		positionRelative_.x -= power_;
		positionRelative_.y += power_;
		break;
	default:
		break;
	}
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

