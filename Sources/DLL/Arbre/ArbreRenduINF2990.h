///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
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

   // Obtenir le ième enfant de l'arbre
   NoeudAbstrait* getEnfant(int position);

   // Accepter un visiteur
   virtual bool accepterVisiteur(VisiteurAbstrait* vis);

   // Initialiser l'arbre avec un fichier XML
   bool initialiserXML(std::string nomFichier);

	/// La chaîne représentant les types
   static const std::string NOM_ARAIGNEE;
   static const std::string NOM_BUTOIR;
   static const std::string NOM_BUTOIRCIRCULAIRE;
   static const std::string NOM_CIBLE;
   static const std::string NOM_CONECUBE;
   static const std::string NOM_BILLE;
   static const std::string NOM_GENERATEURBILLE;
   static const std::string NOM_MUR;
   static const std::string NOM_PALETTE;
   static const std::string NOM_PORTAIL;
   static const std::string NOM_RESSORT;
   static const std::string NOM_TROU;	
   static const std::string NOM_VIDE;
   static const std::string NOM_TABLE;

   int* obtenirProprietes() { return proprietes_; };

private:

	// Lire un fichier XML
	bool lireXML(tinyxml2::XMLDocument& doc);

	int* proprietes_ = new int[6];

};


#endif // __ARBRE_ARBRERENDUINF2990_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
