#ifndef __ECLAIRAGE_CONTROLEUR_LUMIERES_H__
#define __ECLAIRAGE_CONTROLEUR_LUMIERES_H__

#include "Lumiere.h"

class ControleurLumieres
{

public:
	
	ControleurLumieres();
	~ControleurLumieres();

	void initialiserLumieres();
	void definirLumieres();

	void activerAmbiante();
	void desactiverAmbiante();

	void activerDirectionnelle();
	void desactiverDirectionnnelle();

	void activerSpot();
	void desactiverSpot();

private:

	Lumiere* lumAmbiante_;
	Lumiere* lumDirectionnelle_;
	Lumiere* lumSpot_;

};

#endif // __ECLAIRAGE_CONTROLEUR_LUMIERES_H__