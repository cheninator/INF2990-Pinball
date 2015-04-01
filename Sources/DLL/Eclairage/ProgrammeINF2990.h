#include <GL/glew.h>

#include "../../Commun/Utilitaire/OpenGL/OpenGL_Programme.h"
#include "../../Commun/Utilitaire/OpenGL/OpenGL_Nuanceur.h"



class ProgrammeINF2990 
{

public:
	ProgrammeINF2990() = default;

	void initialiser();
	
	void activer();
	void desactiver();

private:

	bool EstInitialise_{ false };

	opengl::Programme* programme_;
	opengl::Nuanceur* nuanceurSommets_;
	opengl::Nuanceur* nuanceurFragments_;

};