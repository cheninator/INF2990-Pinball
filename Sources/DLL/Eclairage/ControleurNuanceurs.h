///////////////////////////////////////////////////////////////////////////////
/// @file ControleurNuanceurs.h
/// @author The ballers
/// @date 2015-03-20
/// @version 1.0
///
/// @ingroup Eclairage
///////////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>

#include "../../Commun/Utilitaire/OpenGL/OpenGL_Programme.h"
#include "../../Commun/Utilitaire/OpenGL/OpenGL_Nuanceur.h"


////////////////////////////////////////////////////////////////////////////////
///
/// @class ControleurNuanceurs
/// @brief TODO PHIL
///
/// @author The ballers
/// @date 2015-04-02
////////////////////////////////////////////////////////////////////////////////
class ControleurNuanceurs 
{

public:
	static ControleurNuanceurs* obtenirInstance();
	static void libererInstance();
	~ControleurNuanceurs();

	void initialiser(); 
	
	void activer();
	void desactiver();

	void assignerColorShift(int);
	void assignerEtatNoeud(int etat);
	void assignerNumeroNoeud(int numero);

	void assignerEtatAmbiante(int etat);
	void assignerEtatDirectionnelle(int etat);
	void assignerEtatSpot(int etat);

private:

	static ControleurNuanceurs* instance_;
	ControleurNuanceurs() = default;

	bool EstInitialise_{ false };

	opengl::Programme* programme_{ nullptr };
	opengl::Nuanceur* nuanceurSommets_{ nullptr };
	opengl::Nuanceur* nuanceurFragments_{ nullptr };

};