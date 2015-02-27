///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurXML.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURXML_H__
#define __VISITEURS_VISITEURXML_H__

#include "VisiteurAbstrait.h"
#include "tinyxml2.h"
#include <string>


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurXML
/// @brief Classe pour enregistrer l'information de la zone de jeu
///		   dans un fichier XML.
///
///        Instancier cette classe avec en parametre le nom du fichier avec
///		   l'extension .xml . Ensuite, appeler la methode accepterVisiteur()
///		   de l'arbre de rendu et lui fournir CE visiteur en parametre
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurXML : public VisiteurAbstrait
{
public:

	/// Constructeur par parametre : fournir le nom du fichier de sauvegarde et les proprietes du jeu
	VisiteurXML(std::string nomFichier, int proprietes[]);

	/// Destructeur
	~VisiteurXML();

	/// Traiter un arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudAbstrait* noeud);

private:

	VisiteurXML();					/// Constructeur par defaut
	bool traiterProprietes();		/// Methode pour enregistrer les proprietes de la zone de jeu

	tinyxml2::XMLDocument document; ///< Document XML pour l'ecriture
	std::string nomFichier;			///< Nom du fichier a ecrire.
	int* proprietes_ = new int[6];	///< Proprietes de la partie a ecrire
	
	tinyxml2::XMLElement* elementArbreRendu;
	tinyxml2::XMLElement* elementTable;

	void enregistrerBinaire();

};

#endif //__VISITEURS_VISITEURXML_H__