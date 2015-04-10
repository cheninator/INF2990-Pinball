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
/// @brief Cette classe sert d'interface entre le programme et le serveur OpenGL.
///
/// @author The ballers
/// @date 2015-04-02
////////////////////////////////////////////////////////////////////////////////
class ControleurNuanceurs 
{

public:

	/// Accesseur de l'instance unique
	static ControleurNuanceurs* obtenirInstance();

	/// Liberateur de l'instance unique;
	static void libererInstance();

	/// Initialise le programme de nuanceurs
	void initialiser(); 
	
	/// Active le programme
	void activer();
	/// Desactive le programme
	void desactiver();

	/// Assignation de colorshift pour les palettes du joueur 2
	void assignerColorShift(int);
	/// Assignation de l'etat d'affichage (selectionne, transparent impossible, illumine)
	void assignerEtatNoeud(int etat);
	/// Assignation du numero du noeud au cas ou on voudrait faire la selection par couleurs
	void assignerNumeroNoeud(int numero);

	/// Assignation de l'etat (actif/inactif) de la lumiere ambiante
	void assignerEtatAmbiante(int etat);
	/// Assignation de l'etat (actif/inactif) de la lumiere directionnelle
	void assignerEtatDirectionnelle(int etat);
	/// Assignation de l'etat (actif/inactif) de la lumiere spot
	void assignerEtatSpot(int etat);
	/// Dire au nuanceur de fragments si on est en train de dessiner le skybox ou la scene.
	void assignerSkybox(int skybox);
	/// Dire au nuanceur de fragments que je suis la table
	void assignerEstTable(int estTable);

private:

	/// Pointeur vers l'instance unique
	static ControleurNuanceurs* instance_;
	/// Constructeur prive
	ControleurNuanceurs() = default;
	/// Destructeur prive
	~ControleurNuanceurs();

	/// Bool pour s'assurer qu'on n'essaye pas d'activer un programme pas initialiser
	bool EstInitialise_{ false };

	/// Programme openGL constitue de deux nuanceurs
	opengl::Programme* programme_{ nullptr };
	/// Nuanceur de sommets
	opengl::Nuanceur* nuanceurSommets_{ nullptr };
	/// Nuanceur de fragments
	opengl::Nuanceur* nuanceurFragments_{ nullptr };

};