///////////////////////////////////////////////////////////////////////////
/// @file NoeudPortail.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudPortailTorus.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortailTorus::NoeudPortailTorus(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortailTorus::NoeudPortailTorus(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	scaleTorus_ = 1.0;
	
	direction_ = 0.995;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortailTorus::~NoeudPortailTorus()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortailTorus::~NoeudPortailTorus()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortailTorus::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortailTorus::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du modele.
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	if (pause_) {
		glBlendFunc(GL_SRC_ALPHA, GL_ZERO); // Set The Blending Function For Translucency
		glEnable(GL_BLEND);
	}
	else if (transparent_) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	liste_->dessiner();
	glPopAttrib();
	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortailTorus::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortailTorus::animer(float temps)
{
	NoeudComposite::animer(temps);

	if (scaleTorus_ < 0.5)
		direction_ = 1.007;
	else if (scaleTorus_ > 1)
		direction_ = 0.993;
	scaleTorus_ = scaleTorus_ * direction_;
	assignerEchelle({ scaleTorus_, scaleTorus_, 1 });

}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPortailTorus::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudPortailTorus::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	//if (vis->traiter(this))
	//	reussi = true;

	return reussi;

}