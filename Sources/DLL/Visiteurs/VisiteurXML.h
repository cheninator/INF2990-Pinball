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

class NoeudCouvercle;

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurXML
/// @brief Classe pour enregistrer l'information de l'arbre de rendu
///		   dans un fichier XML.
///
///        Instancier cette classe avec en paramètre le nom du fichier avec
///		   l'extension .xml . Ensuite, appelee la méthode accepterVisiteur()
///		   de l'arbre de rendu et lui fournir CE visiteur en paramètre
///
/// @author Yonni Chen
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurXML : public VisiteurAbstrait
{
public:

	/// Constructeur par paramètre : fournir le nom du fichier de sauvegarde et les propriétés du jeu
	VisiteurXML(std::string nomFichier, int proprietes[]);

	/// Destructeur
	~VisiteurXML();

	/// Traiter un arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudAbstrait* noeud);

private:

	VisiteurXML();					/// Constructeur par défaut

	tinyxml2::XMLDocument document; ///< Document XML pour l'écriture
	std::string nomFichier;			///< Nom du fichier à écrire.
	int* proprietes_ = new int[6];	///< Propriétés de la partie à écrire
	
	tinyxml2::XMLElement* elementArbreRendu;
	tinyxml2::XMLElement* elementTable;

	bool traiterProprietes();

};

#endif //__VISITEURS_VISITEURXML_H__