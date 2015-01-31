#include "VisiteurXML.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudButoir.h"
#include "../Arbre/Noeuds/NoeudCible.h"
#include "../Arbre/Noeuds/NoeudGenerateurBille.h"
#include "../Arbre/Noeuds/NoeudMur.h"
#include "../Arbre/Noeuds/NoeudPalette.h"
#include "../Arbre/Noeuds/NoeudPortail.h"
#include "../Arbre/Noeuds/NoeudRessort.h"
#include "../Arbre/Noeuds/NoeudTrou.h"
#include "../Arbre/Noeuds/NoeudTable.h"


VisiteurXML::VisiteurXML()
{

}

VisiteurXML::~VisiteurXML()
{

}

bool VisiteurXML::traiter(ArbreRenduINF2990* arbre)
{
	// Créer le noeud 'elementArbreRendu'
	tinyxml2::XMLElement* elementArbreRendu{ document.NewElement("arbreRenduINF2990") };

	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		traiter(arbre->getEnfant(i), elementArbreRendu);
	}

	document.LinkEndChild(elementArbreRendu);
	document.SaveFile(nomFichier.c_str());

	return true;
}

bool VisiteurXML::traiter(NoeudTable* noeud, tinyxml2::XMLElement* parent)
{
	// Créer le noeud 'elementTable'
	tinyxml2::XMLElement* elementTable{ document.NewElement("table") };
	elementTable->SetAttribute("posX", noeud->obtenirPositionRelative().x);
	elementTable->SetAttribute("posY", noeud->obtenirPositionRelative().y);
	elementTable->SetAttribute("posZ", noeud->obtenirPositionRelative().z);

	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		traiter(noeud->getEnfant(i), elementTable);
	}

	parent->LinkEndChild(elementTable);

	return true;
}

bool VisiteurXML::traiter(NoeudAbstrait* noeud, tinyxml2::XMLElement* parent)
{
	return false;
}

bool VisiteurXML::traiter(NoeudButoir* noeud, tinyxml2::XMLElement* parent)
{
	// Créer le noeud 'elementButoir'
	tinyxml2::XMLElement* elementButoir{ document.NewElement("butoir") };
	elementButoir->SetAttribute("posX", noeud->obtenirPositionRelative().x);
	elementButoir->SetAttribute("posY", noeud->obtenirPositionRelative().y);
	elementButoir->SetAttribute("posZ", noeud->obtenirPositionRelative().z);

	parent->LinkEndChild(elementButoir);


	return true;
}

bool VisiteurXML::traiter(NoeudCible* noeud, tinyxml2::XMLElement* parent)
{
	// Créer le noeud 'element'
	tinyxml2::XMLElement* element{ document.NewElement("cible") };
	element->SetAttribute("posX", noeud->obtenirPositionRelative().x);
	element->SetAttribute("posY", noeud->obtenirPositionRelative().y);
	element->SetAttribute("posZ", noeud->obtenirPositionRelative().z);

	parent->LinkEndChild(element);

	return true;
}

bool VisiteurXML::traiter(NoeudGenerateurBille* noeud, tinyxml2::XMLElement* parent)
{
	// Créer le noeud 'element'
	tinyxml2::XMLElement* element{ document.NewElement("GenerateurBille") };
	element->SetAttribute("posX", noeud->obtenirPositionRelative().x);
	element->SetAttribute("posY", noeud->obtenirPositionRelative().y);
	element->SetAttribute("posZ", noeud->obtenirPositionRelative().z);

	parent->LinkEndChild(element);

	return true;
}

bool VisiteurXML::traiter(NoeudMur* noeud, tinyxml2::XMLElement* parent)
{
	// Créer le noeud 'element'
	tinyxml2::XMLElement* element{ document.NewElement("mur") };
	element->SetAttribute("posX", noeud->obtenirPositionRelative().x);
	element->SetAttribute("posY", noeud->obtenirPositionRelative().y);
	element->SetAttribute("posZ", noeud->obtenirPositionRelative().z);

	parent->LinkEndChild(element);

	return true;
}

bool VisiteurXML::traiter(NoeudPalette* noeud, tinyxml2::XMLElement* parent)
{
	// Créer le noeud 'element'
	tinyxml2::XMLElement* element{ document.NewElement("palette") };
	element->SetAttribute("posX", noeud->obtenirPositionRelative().x);
	element->SetAttribute("posY", noeud->obtenirPositionRelative().y);
	element->SetAttribute("posZ", noeud->obtenirPositionRelative().z);

	parent->LinkEndChild(element);

	return true;
}

bool VisiteurXML::traiter(NoeudPortail* noeud, tinyxml2::XMLElement* parent)
{
	// Créer le noeud 'element'
	tinyxml2::XMLElement* element{ document.NewElement("portail") };
	element->SetAttribute("posX", noeud->obtenirPositionRelative().x);
	element->SetAttribute("posY", noeud->obtenirPositionRelative().y);
	element->SetAttribute("posZ", noeud->obtenirPositionRelative().z);

	parent->LinkEndChild(element);

	return true;
}

bool VisiteurXML::traiter(NoeudRessort* noeud, tinyxml2::XMLElement* parent)
{
	// Créer le noeud 'element'
	tinyxml2::XMLElement* element{ document.NewElement("ressort") };
	element->SetAttribute("posX", noeud->obtenirPositionRelative().x);
	element->SetAttribute("posY", noeud->obtenirPositionRelative().y);
	element->SetAttribute("posZ", noeud->obtenirPositionRelative().z);

	parent->LinkEndChild(element);

	return true;
}

bool VisiteurXML::traiter(NoeudTrou* noeud, tinyxml2::XMLElement* parent)
{
	// Créer le noeud 'element'
	tinyxml2::XMLElement* element{ document.NewElement("trou") };
	element->SetAttribute("posX", noeud->obtenirPositionRelative().x);
	element->SetAttribute("posY", noeud->obtenirPositionRelative().y);
	element->SetAttribute("posZ", noeud->obtenirPositionRelative().z);

	parent->LinkEndChild(element);

	return true;
}
