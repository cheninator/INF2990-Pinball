#include "ControleurLumieres.h"

ControleurLumieres::ControleurLumieres()
{
	lumAmbiante_ = new Lumiere(GL_LIGHT1);
	lumDirectionnelle_ = new Lumiere(GL_LIGHT2);
	lumSpot_ = new Lumiere(GL_LIGHT3);
}

ControleurLumieres::~ControleurLumieres()
{
	lumAmbiante_->disable();
	lumDirectionnelle_->disable();
	lumSpot_->disable();
	delete lumAmbiante_;
	delete lumDirectionnelle_;
	delete lumSpot_;
}

void ControleurLumieres::initialiserLumieres()
{
	// Gros de la job: setter toutes les propriétés des 3 lumieres.
}



void ControleurLumieres::definirLumieres()
{
	lumAmbiante_->definir();
	lumDirectionnelle_->definir();
	lumSpot_->definir();
}

void ControleurLumieres::activerAmbiante()
{
	lumAmbiante_->enable();
}

void ControleurLumieres::desactiverAmbiante()
{
	lumAmbiante_->enable();
}

void ControleurLumieres::activerDirectionnelle()
{
	lumDirectionnelle_->enable();
}
void ControleurLumieres::desactiverDirectionnnelle()
{
	lumDirectionnelle_->enable();
}

void ControleurLumieres::activerSpot()
{
	lumSpot_->enable();
}
void ControleurLumieres::desactiverSpot()
{
	lumSpot_->enable();
}