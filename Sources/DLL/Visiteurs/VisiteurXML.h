///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurXML.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURXML_H__
#define __VISITEURS_VISITEURXML_H__

#include "VisiteurAbstrait.h"
#include "tinyxml2.h"
#include <string>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurXML
/// @brief Classe pour enregistrer l'information de l'arbre de rendu
///		¸  dans un fichier XML.
///
///        Instancier cette classe avec en paramètre le nom du fichier avec
///		   l'extension .xml . Ensuite, appelez la méthode accepterVisiteur()
///		   de l'arbre de rendu et lui fournir CE visiteur en paramètre
///
/// @author Yonni Chen
/// @date 2015-02-02
///////////////////////////////////////////////////////////////////////////
class VisiteurXML : public VisiteurAbstrait
{
public:

	// Constructeur par paramètre : fournir le nom du fichier de sauvegarde
	VisiteurXML(std::string nomFichier);

	// Destructeur
	~VisiteurXML();

	// Traiter un arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud, tinyxml2::XMLElement* parent);

private:

	// Ne touchez pas au constructeur par défaut
	VisiteurXML();

	tinyxml2::XMLDocument document;
	std::string nomFichier;
	
};


#endif //__VISITEURS_VISITEURXML_H__