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
#include "glm/glm.hpp"

class NoeudAbstrait;
class ArbreRenduINF2990;
class ConfigScene;

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
   static FacadeModele* obtenirInstance();

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
   bool verifierCliqueDansTable(int x, int y);

   /// Pour la duplication d'objets selectionnes
   void dupliquerSelection(int i, int j);

   /// Pour la sauvegarde de fichier XML
   int creerXML(char* path, int prop[6]);

   /// Verifier si un point clique est dans la table 
   bool estDansTable(glm::dvec3 pointDuMonde);

   /// Pour la suppression des objets selectionnes
   bool supprimer();

   /// Obtenir le facteur de zoom applique
   double obtenirZoomCourant();

   /// Obtenir la taille de la fenetre
   glm::ivec2 FacadeModele::obtenirTailleFenetre();

   /// Obtenir le centre de masse en X
   int obtenirCentreMasseX();

   /// Obtenir le centre de masse en Y
   int obtenirCentreMasseY();

   /// Selectionner les objets sous un point clique
   int selectionnerObjetSousPointClique(int i, int j, int largeur, int hauteur, bool ctrlDown = false);

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

   ///verifie si la selection est hors table lors de la duplication
   bool duplicationEstHorsTable();


   void sauvegarderConfig(int config[12]);

   int* obtenirConfiguration();

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

   HWND  hWnd_{ nullptr };	///< Poignee ("handle") vers la fenetre ou l'affichage se fait.
   HGLRC hGLRC_{ nullptr }; ///< Poignee ("handle") vers le contexte OpenGL.
   HDC   hDC_{ nullptr };	///< Poignee ("handle") vers le "device context".

   vue::Vue* vue_{ nullptr };				/// Vue courante de la scene.
   ArbreRenduINF2990* arbre_{ nullptr };	/// Arbre de rendu contenant les differents objets de la scene.
   ConfigScene* configuration_{ nullptr };

   glm::dvec3 selectionBasGauche_, selectionHautDroit_;
   glm::ivec2 pointInitial_, pointAvant_;

   static const int coinGaucheTableX;
   static const int coinGaucheTableY;
   static const int coinDroitTableX;
   static const int coinDroitTableY;

   bool duplicationHorsTable_;
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
