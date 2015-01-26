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
}

void NoeudButoir::animer(float temps)
{
}

