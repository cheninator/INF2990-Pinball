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
	glTranslatef( -117, 0, 0 );
	glRotatef(-45.0, 0, 1, 0 );
	// Affichage du modèle.
	glStencilFunc(GL_ALWAYS, 0, -1);
	liste_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudCouvercle::animer(float temps)
{
	/* Animation ici 
	// Le cube effectue un tour à toutes les 7 secondes sur l'axe des X.
	angleX_ = fmod(angleX_ + temps / 7.0f * 360.0f, 360.0f);
	// Le cube effectue un tour à toutes les 3 secondes sur l'axe des Y.
	angleY_ = fmod(angleY_ + temps / 3.0f * 360.0f, 360.0f);
	// Le cube effectue une révolution à toutes les 15 secondes.
	angleRotation_ = fmod(angleRotation_ + temps / 15.0f * 360.0f, 360.0f);
	//	glTranslatef( -117, 0, 0 );
	//	glRotatef(-45.0, 0, 1, 0 );
	*/
	positionRelative_.x++;
	positionRelative_.y++;
	
	

}

bool NoeudCouvercle::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

