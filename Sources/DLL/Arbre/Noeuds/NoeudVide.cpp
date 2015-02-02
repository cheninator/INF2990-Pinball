#include "NoeudVide.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudVide::NoeudVide(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
}

NoeudVide::~NoeudVide()
{
}

void NoeudVide::afficherConcret() const
{
}

void NoeudVide::animer(float temps)
{
}


bool NoeudVide::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;
	
	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

