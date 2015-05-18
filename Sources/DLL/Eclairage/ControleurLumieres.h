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

class NoeudTable;

////////////////////////////////////////////////////////////////////////////////
///
/// @class ControleurLumieres
/// @brief Cette classe controle les lumieres.  Elle s'occuppe de definir leurs
/// couleurs, position etc. et de les envoyer au serveur OpenGL.
/// 
/// @author The ballers
/// @date 2015-04-02
////////////////////////////////////////////////////////////////////////////////
class ControleurLumieres
{

public:
	
	/// Constructeur
	ControleurLumieres();

	/// Destructeur
	~ControleurLumieres();

	/// Constructeur par copie non-necessaire dans le contexte
	ControleurLumieres(const ControleurLumieres &) = delete;

	/// Assignation par copie non-necessaire dans le contexte
	ControleurLumieres& operator=(ControleurLumieres const&) = delete;

	/// Donne les valeurs choisies par le controleur aux lumieres
	void initialiserLumieres();

	/// Passe les donnees des lumieres au serveur OpenGL
	void definirLumieres();

	/// Activer la lumiere Ambiante
	static void activerAmbiante();
	/// Desactiver la lumiere ambiante
	static void desactiverAmbiante();

	/// Activer la lumiere directionnnelle
	static void activerDirectionnelle();

	/// Desactiver la lumiere directionnelle
	static void desactiverDirectionnelle();

	/// Activer la lumiere spot
	static void activerSpot();
	/// Desactiver la lumiere spot
	static void desactiverSpot();
	/// Pointer les spots sur les billes.
	void trackerLesBilles(NoeudTable* table);

private:

	/// Objet pour la lumiere ambiante
	Lumiere* lumAmbiante_;

	/// Objet pour la lumiere directionnelle
	Lumiere* lumDirectionnelle_;

	/// Objet pour la lumiere spot
	Lumiere* lumSpotA_;
	Lumiere* lumSpotB_;

};

#endif // __ECLAIRAGE_CONTROLEUR_LUMIERES_H__