///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @ingroup Arbre
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"
#include "FreeImage.h"
#include "../QuadTree/QuadTree.h"
#include "../Global/SingletonGlobal.h"

#include <map>
#include <string>
#include "tinyxml2.h"


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui represente l'arbre de rendu specifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilises par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
/// @ingroup Arbre
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:

   /// Constructeur par defaut.
   ArbreRenduINF2990(bool afficher = true);

   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu a son etat initial.
   void initialiser();

   /// Obtenir le ieme enfant de l'arbre
   NoeudAbstrait* getEnfant(int position) const;

   // /// Methode de test
   //glm::dvec3 getPosRessort() const { return posRessort; };

   /// Accepter un visiteur
   virtual bool accepterVisiteur(VisiteurAbstrait* vis);

   /// Initialiser l'arbre a partir d'un fichier XML
   bool initialiserXML(std::string nomFichier);

   /// Obtenir les proprietes de la zone de jeu
   int* obtenirProprietes() const { return proprietes_; };

   /// Obtenir les éléments de la table
   std::vector<NoeudAbstrait*> obtenirElementsTable();

   // /// Permet de savoir si l'arbre est la zone de jeu par defaut
   //bool estDefaut() const;

   /// Obtenir un noeud selon son numero
   NoeudAbstrait* obtenirNoeudSelonNumero(int numero);

   /// Prend une capture d'ecran de la zone de jeu
   void takeScreenShot(char* path, int width, int height, bool square = false, int maxSize = 0);

   static const std::string NOM_BUTOIRD; ///< Represente le type Butoir droit
   static const std::string NOM_BUTOIRG; ///< Represente le type Butoir gauche
   static const std::string NOM_BUTOIRCIRCULAIRE; ///< Represente le type Butoir circulaire
   static const std::string NOM_CIBLE; ///< Represente le type Cible
   static const std::string NOM_BILLE; ///< Represente le type Bille
   static const std::string NOM_GENERATEURBILLE; ///< Represente le type Generateur bille
   static const std::string NOM_MUR; ///< Represente le type Mur
   static const std::string NOM_PALETTED; ///< Represente le type Palette droite
   static const std::string NOM_PALETTEG; ///< Represente le type Palette gauche
   static const std::string NOM_PORTAIL; ///< Represente le type Portail
   static const std::string NOM_PORTAILTORUS; ///< Represente le type PortailTorus
   static const std::string NOM_RESSORT; ///< Represente le type Ressort
   static const std::string NOM_TROU; ///< Represente le type Trou
   static const std::string NOM_VIDE; ///< Represente le type Vide
   static const std::string NOM_COUVERCLE; ///< Represente le type Couvercle
   static const std::string NOM_TABLE; ///< Represente le type Table
   static const std::string NOM_GATE; ///< Represente le type Table

private:

	/// Lire un fichier XML
	bool lireXML(tinyxml2::XMLDocument& doc);

	// Definir ce qu'est la zone de jeu par defaut
	//void assignerDefaut();

	/// Proprietes de la zone de jeu
	int* proprietes_ = new int[6];
	/*
	// Zone de jeu par defaut
	glm::dvec3 posRessort;
	glm::dvec3 scaleRessort;
	glm::dvec3 angleRessort;
	glm::dvec3 posTrou;
	glm::dvec3 scaleTrou;
	glm::dvec3 angleTrou;
	glm::dvec3 posGenerateur;
	glm::dvec3 scaleGenerateur;
	glm::dvec3 angleGenerateur;
	*/
	std::vector<NoeudAbstrait*> listeNoeuds_;

};


#endif // __ARBRE_ARBRERENDUINF2990_H__
