#include "NoeudCouvercle.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudCouvercle::NoeudCouvercle(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	assignerSelection(false);
	selectionnable_ = false;
	modifiable_ = false;
}

NoeudCouvercle::~NoeudCouvercle()
{
}

void NoeudCouvercle::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	glTranslatef(200, -50, 0);
	// To remove for animation
	//glTranslatef( -117, 0, 0 );
	// glRotatef(-45.0, 0, 1, 0 );
	// Affichage du modèle.
	glStencilFunc(GL_ALWAYS, 0, -1);
	liste_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudCouvercle::animer(float temps)
{
	// Appel à la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);
	if (positionRelative_.x > -130.0) {
		positionRelative_.x -= 1;
		rotation_.y -= 22.5 / (130.0);
		positionRelative_.z -= 0.5;
	}
}

bool NoeudCouvercle::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	//if (vis->traiter(this))
	//	reussi = true;

	return reussi;
}

