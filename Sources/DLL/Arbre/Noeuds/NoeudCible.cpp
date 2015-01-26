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
}

void NoeudCible::animer(float temps)
{
}

