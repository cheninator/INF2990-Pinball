#include "NoeudGenerateurBille.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudGenerateurBille::NoeudGenerateurBille(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

NoeudGenerateurBille::~NoeudGenerateurBille()
{
}

void NoeudGenerateurBille::afficherConcret() const
{
}

void NoeudGenerateurBille::animer(float temps)
{
}

