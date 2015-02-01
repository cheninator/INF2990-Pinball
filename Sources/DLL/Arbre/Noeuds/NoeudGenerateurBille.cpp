#include "NoeudGenerateurBille.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudGenerateurBille::NoeudGenerateurBille(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

NoeudGenerateurBille::~NoeudGenerateurBille()
{
}

void NoeudGenerateurBille::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du modèle.
	liste_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudGenerateurBille::animer(float temps)
{
}

bool NoeudGenerateurBille::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

