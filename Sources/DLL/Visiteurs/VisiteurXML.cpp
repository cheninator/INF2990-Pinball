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


VisiteurXML::VisiteurXML(std::string nom)
{
	nomFichier = nom;
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

bool VisiteurXML::traiter(NoeudAbstrait* noeud, tinyxml2::XMLElement* parent)
{
	// Connaitre le type du noeud
	std::string nom = noeud->obtenirType();

	// Créer le noeud 'element'
	tinyxml2::XMLElement* element{ document.NewElement(nom.c_str()) };

	// Si l'élément est une table, visiter ses enfants
	if (nom == "table")
	{
		element->SetAttribute("posX", noeud->obtenirPositionRelative().x);
		element->SetAttribute("posY", noeud->obtenirPositionRelative().y);
		element->SetAttribute("posZ", noeud->obtenirPositionRelative().z);

		
		element->SetAttribute("scaleX", noeud->obtenirAgrandissement().x);
		element->SetAttribute("scaleY", noeud->obtenirAgrandissement().y);
		element->SetAttribute("scaleZ", noeud->obtenirAgrandissement().z);
		element->SetAttribute("angleX", noeud->obtenirRotation().x);
		element->SetAttribute("angleY", noeud->obtenirRotation().y);
		element->SetAttribute("angleZ", noeud->obtenirRotation().z);
		

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			traiter(noeud->chercher(i), element);
		}

		parent->LinkEndChild(element);
	}

	else
	{
		element->SetAttribute("posX", noeud->obtenirPositionRelative().x);
		element->SetAttribute("posY", noeud->obtenirPositionRelative().y);
		element->SetAttribute("posZ", noeud->obtenirPositionRelative().z);
		
		element->SetAttribute("scaleX", noeud->obtenirAgrandissement().x);
		element->SetAttribute("scaleY", noeud->obtenirAgrandissement().y);
		element->SetAttribute("scaleZ", noeud->obtenirAgrandissement().z);
		element->SetAttribute("angleX", noeud->obtenirRotation().x);
		element->SetAttribute("angleY", noeud->obtenirRotation().y);
		element->SetAttribute("angleZ", noeud->obtenirRotation().z);
		

		parent->LinkEndChild(element);
	}
		
	return true;
}