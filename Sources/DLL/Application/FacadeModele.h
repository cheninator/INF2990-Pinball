//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @ingroup Application
//////////////////////////////////////////////////////////////////////////////

/**
*  @defgroup INF2990 INF2990
* Painball
*/

/**
*	@defgroup Noyau Noyau
*	@ingroup INF2990
*  Ce module contient le coeur de l'application.
*/

/** @defgroup Application Application
*	@ingroup Noyau
*/

#ifndef __APPLICATION_FACADEMODELE_H__
#define __APPLICATION_FACADEMODELE_H__

#include <windows.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <vector>
#include "glm/glm.hpp"

namespace utilitaire{
	class BoiteEnvironnement;
}
class NoeudAbstrait;
class ArbreRenduINF2990;
class ConfigScene;
class NoeudPaletteG;
class NoeudPaletteD;
class NoeudRessort;
class JoueurVirtuel;
//class QuadTree;
class ControleurLumieres;
class Originator;
class ControleurTexte;

namespace vue {
   class Vue;
}
///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une facade) sur l'ensemble
///        du modele et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
/// @ingroup Application
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:

	/// Obtient l'instance unique de la classe.
	static FacadeModele* obtenirInstance(bool console = false);

	/// Libere l'instance unique de la classe.
	static void libererInstance();

	/// Cree un contexte OpenGL et initialise celui-ci.
	void initialiserOpenGL(HWND hWnd);

	/// Libere le contexte OpenGL.
	void libererOpenGL();

	/// Affiche le contenu du modele.
	void afficher() const;

	/// Affiche la base du contenu du modele.
	void afficherBase() const;

	/// Retourne la vue courante.
	inline vue::Vue* obtenirVue();

	/// Retourne l'arbre de rendu.
	inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;

	/// Retourne l'arbre de rendu.
	inline ArbreRenduINF2990* obtenirArbreRenduINF2990();

	/// Reinitialise la scene.
	void reinitialiser();

	/// Anime la scene.
	void animer(float temps);

	/// Deplacement des noeuds selectionnes dans l'arbre de rendu.
	void deplacerSelection(int x1, int y1, int x2, int y2, bool duplication);

	/// Rotation des noeuds selectionnes
	void tournerSelectionSouris(int x1, int y1, int x2, int y2);

	/// Scale de la selection
	void agrandirSelection(int x1, int y1, int x2, int y2);

	/// Verifier si un point clique est dans la table
	static bool verifierCliqueDansTable(int x, int y);

	/// Pour la duplication d'objets selectionnes
	void dupliquerSelection(int i, int j);

	/// Pour la sauvegarde de fichier XML
	static int creerXML(std::string path, int prop[6], bool force = false);

	/// Retourne true si la sauvegarde est autorise
	static int peutSauvegarder();

	/// Verifier si un point clique est dans la table 
	static bool estDansTable(glm::dvec3 pointDuMonde);

	/// Pour la suppression des objets selectionnes
	static bool supprimer();

	/// Obtenir le facteur de zoom applique
	double obtenirZoomCourant()  const;

	/// Obtenir la taille de la fenetre
	glm::ivec2 obtenirTailleFenetre() const;

	/// Obtenir le centre de masse en X
	static int obtenirCentreMasseX();

	/// Obtenir le centre de masse en Y
	static int obtenirCentreMasseY();

	/// Selectionner les objets sous un point clique
	int selectionnerObjetSousPointClique(int i, int j, int hauteur, int largeur, bool ctrlDown = false, bool gaucheEnfonce = false, bool sourisSurSelection = false);

	//Verifier si la souris est situe sur un objet
	bool sourisEstSurObjet(int i, int j, int hauteur, int largeur, bool& estSelectionne);

	/// Pour le rectangle elastique
	void rectangleElastique(int i, int j);

	/// Pour la selection multiple d'objets
	int selectionMultiple(bool c);

	/// Initialisation du rectangle elastique
	void initialiserRectangleElastique(int i, int j);

	/// Fin du rectangle elastique
	void terminerRectangleElastique();

	/// Appliquer le zoom initial
	bool appliquerZoomInitial();

	/// Position du mur
	static void positionnerMur(int originX, int originY, int x1, int y1, int x2, int y2, NoeudAbstrait* noeud);

	/// Verifie si la selection est hors table lors de la duplication
	bool duplicationEstHorsTable() const;

	/// Sauvegarde la derniere configuration valide et confirmee par l'usager
	void sauvegarderConfig(int config[13]);

	/// Obtenir toutes les proprietes sans initialiser l'arbre de rendu
	int* obtenirProprietes(char* nomFichier);

	/// Obtenir la difficulte du nom de la carte passe en parametre
	static int obtenirDifficulte(char* nomFichier);

	/// Sauvegarder la derniere campagne jouee par l'usager
	void sauvegarderCampagne(char* nomFichier);

	/// Obtenir les informations de derniere campagne jouee par l'usager
	std::string obtenirDerniereCampagne() const;

	/// Compresser un ressort
	void compresserRessort() const;

	/// Relacher le ressort
	void relacherRessort() const;

	//void construireQuadTree();


	int* obtenirConfiguration();
	int	obtenirTouchePGJ1() const;
	int  obtenirTouchePGJ2() const;
	int  obtenirTouchePDJ1() const;
	int  obtenirTouchePDJ2() const;
	int  obtenirToucheRessort() const;
	int  obtenirNombreDeBilles() const;
	int  obtenirModeDoubleBille() const;
	int  obtenirModeForceRebond() const;
	int  obtenirAffichageGlobal() const;
	void bloquerAffichageGlobal(int active);
	bool obtenirAI() const;

	/// Construire des les 4 listes de palettes GJ1,DJ1, GJ2,DJ2
	void construireListesPalettes();

	/// Activer les palettes de chaque joueur
	void activerPalettesGJ1() const;
	void desactiverPalettesGJ1() const;
	void activerPalettesDJ1() const;
	void desactiverPalettesDJ1() const;

	void activerPalettesGJ2() const;
	void desactiverPalettesGJ2() const;
	void activerPalettesDJ2() const;
	void desactiverPalettesDJ2() const;

	void supprimerBille();

	void setPause(bool pause);
	void setDebug(bool valeurSpotLight = false);

	// Traiter l'ensemble des collisions
	void traiterCollisions(float temps);
	//void traiterCollisionsAvecQuadTree(float temps);
	void updateForcesExternes() const;

	void mettreAJourListeBillesEtNoeuds();
	void mettreAJourListeNoeuds();
	void mettreAJourListeRessorts();

	// Assigner la valeur de l'animation a un objet
	void assignerAnimer(bool animer, NoeudAbstrait* noeud);
	void assignerAI(bool actif);

	/// Preare la creation de la bille (choisis le portail d'ou elle sera generee)
	static bool preparerBille();
	/// Cree une bille a la position et scale demande
	void creeBille(glm::dvec3 position, glm::dvec3 echelle);

	static void printCurrentTime();
	static double obtenirScaleMinMax();

	void utiliserCameraOrbite(bool utiliseOrbite);
	bool cameraEstOrbite() const;
	void toggleStereo();


	ControleurTexte* obtenircontroleurTexte();

	std::string obtenirCout();


	/// Pour transmettre les appels de lumiere du C# au controleur de Lumieres
	void setLight(int lum, bool state);

	static glm::ivec2 obteniCoordonneeMax();

	/// Journal des modifications
	void sauvegarderHistorique();
	void annulerModifications();
	void retablirModifications();
	void viderHistorique();

	/// Obtient le nombre d'objets selectionnes 
	int obtenirNombreSelection() const;

	bool possedeSuivant() const;
	bool possedePrecedent() const;

	/// Dessiner le skybox
	void dessinerSkybox(double demiLargeur = 1000, bool vueOrtho = false, glm::dvec3 pointMilieu = { 0.0, 0.0, 0.0 }) const;

private:

	/// Constructeur par defaut.
	FacadeModele() = default;

	/// Destructeur.
	~FacadeModele();

	/// Constructeur copie desactive.
	FacadeModele(const FacadeModele&) = delete;

	/// Operateur d'assignation desactive.
	FacadeModele& operator =(const FacadeModele&) = delete;

	/// Pointeur vers l'instance unique de la classe.
	static FacadeModele* instance_;
	//static bool useQuadTree_;

	HWND  hWnd_{ nullptr };	///< Poignee ("handle") vers la fenetre ou l'affichage se fait.
	HGLRC hGLRC_{ nullptr }; ///< Poignee ("handle") vers le contexte OpenGL.
	HDC   hDC_{ nullptr };	///< Poignee ("handle") vers le "device context".

	vue::Vue* vue_{ nullptr };				/// Vue courante de la scene.
	ArbreRenduINF2990* arbre_{ nullptr };	/// Arbre de rendu contenant les differents objets de la scene.
	ConfigScene* configuration_{ nullptr };
	int* proprietes_;						/// Pour les proprietes de la zone de jeu
	JoueurVirtuel* joueur_{ nullptr };
	//QuadTree* quad_{ nullptr };
	Originator* originator_{ nullptr };

	std::stringstream oss_;
	std::streambuf* old_;

	glm::dvec3 selectionBasGauche_, selectionHautDroit_;
	glm::ivec2 pointInitial_, pointAvant_;

	bool duplicationHorsTable_;

	bool pause_{ false };
	bool utiliserAI{ false };
	bool vueEstOrbite_{ false };
	bool vueEstStereo_{ false };

   /// Listes de palettes a activer pour chaque touche
   std::set<NoeudPaletteG*> listePalettesGJ1_; ///< Gauche joueur 1
   std::set<NoeudPaletteD*> listePalettesDJ1_; ///< Droite joueur 1
   std::set<NoeudPaletteG*> listePalettesGJ2_; ///< Gauche joueur 2
   std::set<NoeudPaletteD*> listePalettesDJ2_; ///< Droite joueur 2

   std::vector<NoeudAbstrait*> listeBilles_;
   std::vector<NoeudAbstrait*> listeNoeuds_;
   std::vector<NoeudAbstrait*> listeRessorts_;

   ControleurLumieres* controleurLumieres_{ nullptr };
   ControleurTexte* controleurTexte_{ nullptr };
   utilitaire::BoiteEnvironnement* skybox_{ nullptr };
};



////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est presentement utilisee pour
/// voir la scene.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue()
{
   return vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
///
/// Cette fonction retourne l'arbre de rendu de la scene (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scene.
///
////////////////////////////////////////////////////////////////////////
inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la scene (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scene.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}


#endif // __APPLICATION_FACADEMODELE_H__
