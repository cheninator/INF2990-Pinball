#include "NoeudButoirCirculaire.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudButoirCirculaire::NoeudButoirCirculaire(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

NoeudButoirCirculaire::~NoeudButoirCirculaire()
{
}

void NoeudButoirCirculaire::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du modèle.
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	if (selectionne_)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
	liste_->dessiner();
	glPopAttrib();
	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudButoirCirculaire::animer(float temps)
{
}

bool  NoeudButoirCirculaire::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

