#include "NoeudCible.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudCible::NoeudCible(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

NoeudCible::~NoeudCible()
{
}

void NoeudCible::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du mod�le.
	liste_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudCible::animer(float temps)
{
}

bool  NoeudCible::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

