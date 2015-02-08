#include "NoeudRessort.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudRessort::NoeudRessort(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

NoeudRessort::~NoeudRessort()
{
}

void NoeudRessort::afficherConcret() const
{
	NoeudComposite::afficherConcret();
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

void NoeudRessort::animer(float temps)
{
}

bool NoeudRessort::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

