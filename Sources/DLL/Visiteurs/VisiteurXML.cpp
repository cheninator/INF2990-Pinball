////////////////////////////////////////////////
/// @file   VisiteurXML.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "VisiteurXML.h"
#include "../Arbre/ArbreRenduINF2990.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurXML::VisiteurXML(std::string nomFichier)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] nomFichier : Le nom de sauvegarde du fichier
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurXML::VisiteurXML(std::string nom)
{
	nomFichier = nom;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurXML::~VisiteurXML()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurXML::~VisiteurXML()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurXML::traiter(ArbreRenduINF2990* arbre)
///
/// Cette fonction traite l'arbre de rendu pour enregistrer ses enfants
/// dans un fichier XML.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurXML::traiter(NoeudAbstrait* noeud, tinyxml2::XMLElement* parent)
///
/// Cette fonction traite les enfants de l'arbre de rendu. Si ses enfants ont des enfants
/// ils seront aussi traités.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurXML::traiter(NoeudAbstrait* noeud, tinyxml2::XMLElement* parent)
{
	// Connaitre le type du noeud
	std::string nom = noeud->obtenirType();

	// Créer le noeud 'element'
	tinyxml2::XMLElement* element{document.NewElement(nom.c_str())};

	// Attributs pour la position du noeud
	element->SetAttribute("posX", noeud->obtenirPositionRelative().x);
	element->SetAttribute("posY", noeud->obtenirPositionRelative().y);
	element->SetAttribute("posZ", noeud->obtenirPositionRelative().z);

	// Attributs pour le scale
	element->SetAttribute("scaleX", noeud->obtenirAgrandissement().x);
	element->SetAttribute("scaleY", noeud->obtenirAgrandissement().y);
	element->SetAttribute("scaleZ", noeud->obtenirAgrandissement().z);

	// Attributs pour l'angle
	element->SetAttribute("angleX", noeud->obtenirRotation().x);
	element->SetAttribute("angleY", noeud->obtenirRotation().y);
	element->SetAttribute("angleZ", noeud->obtenirRotation().z);

	// Si l'élément est une table, visiter ses enfants
	if (nom == "table")
	{
		// Traiter les enfants de la table
		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			traiter(noeud->chercher(i), element);
		}
		// Attacher la table à son parent. Ici le parent est l'arbre de rendu
		parent->LinkEndChild(element);
	}

	else
	{
		parent->LinkEndChild(element);
	}

	return true;
}