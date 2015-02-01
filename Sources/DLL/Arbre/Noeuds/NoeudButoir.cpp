#include "NoeudButoir.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudButoir::NoeudButoir(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

NoeudButoir::~NoeudButoir()
{
}

void NoeudButoir::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du modèle.
	liste_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudButoir::animer(float temps)
{
}

bool NoeudButoir::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

