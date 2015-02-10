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

#include <map>
#include <string>
#include "tinyxml2.h"


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui représente l'arbre de rendu spécifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilisés par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
/// @ingroup Arbre
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:
   /// Constructeur par défaut.
   ArbreRenduINF2990();
   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu à son état initial.
   void initialiser();

   /// Obtenir le ième enfant de l'arbre
   NoeudAbstrait* getEnfant(int position) const;

   /// Accepter un visiteur
   virtual bool accepterVisiteur(VisiteurAbstrait* vis);

   /// Initialiser l'arbre avec un fichier XML
   bool initialiserXML(std::string nomFichier);

   /// Obtenir les propriétés de la zone de jeu
   int* obtenirProprietes() const { return proprietes_; };

   static const std::string NOM_BUTOIR; ///< Représente le type Butoir
   static const std::string NOM_BUTOIRCIRCULAIRE; ///< Représente le type Butoir circulaire
   static const std::string NOM_CIBLE; ///< Représente le type Cible
   static const std::string NOM_BILLE; ///< Représente le type Bille
   static const std::string NOM_GENERATEURBILLE; ///< Représente le type Generateur bille
   static const std::string NOM_MUR; ///< Représente le type Mur
   static const std::string NOM_PALETTE; ///< Représente le type Palette
   static const std::string NOM_PORTAIL; ///< Représente le type Portail
   static const std::string NOM_RESSORT; ///< Représente le type Ressort
   static const std::string NOM_TROU; ///< Représente le type Trou
   static const std::string NOM_VIDE; ///< Représente le type Vide
   static const std::string NOM_COUVERCLE; ///< Représente le type Couvercle
   static const std::string NOM_TABLE; ///< Représente le type Table

   bool estDefaut() const;

private:

	/// Lire un fichier XML
	bool lireXML(tinyxml2::XMLDocument& doc);

	/// Propriétés de la zone de jeu
	int* proprietes_ = new int[6];

	// Zone de jeu par défaut
	glm::dvec3 posRessort;
	glm::dvec3 scaleRessort;
	glm::dvec3 angleRessort;
	glm::dvec3 posTrou;
	glm::dvec3 scaleTrou;
	glm::dvec3 angleTrou;
	glm::dvec3 posGenerateur;
	glm::dvec3 scaleGenerateur;
	glm::dvec3 angleGenerateur;

	void assignerDefaut();

};


#endif // __ARBRE_ARBRERENDUINF2990_H__
