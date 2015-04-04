///////////////////////////////////////////////////////////////////////////////
/// @file ProgrammeINF2990.h
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
/// @class ProgrammeINF2990
/// @brief TODO PHIL
///
/// @author The ballers
/// @date 2015-04-02
////////////////////////////////////////////////////////////////////////////////
class ProgrammeINF2990 
{

public:
	static ProgrammeINF2990* obtenirInstance();
	static void libererInstance();
	~ProgrammeINF2990();

	void initialiser(); 
	
	void activer();
	void desactiver();

	void assignerColorShift(int);
	void assignerEtatNoeud(int etat);
	void assignerNumeroNoeud(int numero);

private:

	static ProgrammeINF2990* instance_;
	ProgrammeINF2990() = default;

	bool EstInitialise_{ false };

	opengl::Programme* programme_{ nullptr };
	opengl::Nuanceur* nuanceurSommets_{ nullptr };
	opengl::Nuanceur* nuanceurFragments_{ nullptr };

};