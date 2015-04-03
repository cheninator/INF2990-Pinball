///////////////////////////////////////////////////////////////////////////////
/// @file ControleurLumieres.h
/// @author The ballers
/// @date 2015-03-20
/// @version 1.0
///
/// @ingroup Eclairage
///////////////////////////////////////////////////////////////////////////////

#ifndef __ECLAIRAGE_CONTROLEUR_LUMIERES_H__
#define __ECLAIRAGE_CONTROLEUR_LUMIERES_H__

#include "Lumiere.h"


////////////////////////////////////////////////////////////////////////////////
///
/// @class ControleurLumieres
/// @brief TODO PHIL
///
/// @author The ballers
/// @date 2015-04-02
////////////////////////////////////////////////////////////////////////////////
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
	void desactiverDirectionnelle();

	void activerSpot();
	void desactiverSpot();

	void touche1();
	void touche2();
	void touche3();

private:

	Lumiere* lumAmbiante_;
	Lumiere* lumDirectionnelle_;
	Lumiere* lumSpot_;

};

#endif // __ECLAIRAGE_CONTROLEUR_LUMIERES_H__