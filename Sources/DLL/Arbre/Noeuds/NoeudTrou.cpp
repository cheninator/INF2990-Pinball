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
}

void NoeudTrou::animer(float temps)
{
}

