#include "NoeudMur.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudMur::NoeudMur(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

NoeudMur::~NoeudMur()
{
}

void NoeudMur::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du modèle.
	liste_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudMur::animer(float temps)
{
}

bool NoeudMur::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

