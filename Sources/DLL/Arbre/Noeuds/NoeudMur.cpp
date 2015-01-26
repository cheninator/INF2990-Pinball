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
}

void NoeudMur::animer(float temps)
{
}

