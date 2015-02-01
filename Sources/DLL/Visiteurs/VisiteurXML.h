#ifndef __VISITEURS_VISITEURXML_H__
#define __VISITEURS_VISITEURXML_H__

#include "VisiteurAbstrait.h"
#include "tinyxml2.h"
#include <iostream>

class VisiteurXML : public VisiteurAbstrait
{
public:

	// Constructeur par défaut : aucun déplacement
	VisiteurXML(std::string nomFichier);

	// Destructeur
	~VisiteurXML();

	// Traiter un arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud, tinyxml2::XMLElement* parent);

private:

	tinyxml2::XMLDocument document;
	std::string nomFichier;
	
};


#endif //__VISITEURS_VISITEURSELECTION_H__