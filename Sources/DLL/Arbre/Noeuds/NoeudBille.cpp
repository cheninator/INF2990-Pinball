#include "NoeudBille.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudBille::NoeudBille(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

NoeudBille::~NoeudBille()
{
}

void NoeudBille::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du modèle.
	liste_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudBille::animer(float temps)
{
}

bool NoeudBille::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(*this))
		reussi = true;

	return reussi;
}

