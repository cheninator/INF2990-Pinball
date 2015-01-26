#include "NoeudPalette.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudPalette::NoeudPalette(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

NoeudPalette::~NoeudPalette()
{
}

void NoeudPalette::afficherConcret() const
{
}

void NoeudPalette::animer(float temps)
{
}

