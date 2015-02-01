#include "NoeudTrou.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudTrou::NoeudTrou(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

NoeudTrou::~NoeudTrou()
{
}

void NoeudTrou::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du modèle.
	liste_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudTrou::animer(float temps)
{
}

bool NoeudTrou::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

