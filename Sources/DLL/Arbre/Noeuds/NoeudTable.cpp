#include "NoeudTable.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudTable::NoeudTable(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

NoeudTable::~NoeudTable()
{
}

void NoeudTable::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	glTranslatef(200, -50, 0);
	//glRotatef(180, 0, 0, 1);
	// Affichage du modèle.
	glStencilFunc(GL_ALWAYS, 0, -1);
	liste_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudTable::animer(float temps)
{
}

bool NoeudTable::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

