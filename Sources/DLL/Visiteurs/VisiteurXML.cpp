////////////////////////////////////////////////
/// @file   VisiteurXML.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#include "VisiteurXML.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurXML::VisiteurXML(std::string nomFichier)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] nomFichier : Le nom de sauvegarde du fichier
/// @param[in] proprietes : Les prorietes de la partie
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurXML::VisiteurXML(std::string nom, int proprietes[])
{
	nomFichier = nom;

	for (int i = 0; i < 6; i++)
		proprietes_[i] = proprietes[i];
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurXML::~VisiteurXML()
///
/// Destructeur vide.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurXML::~VisiteurXML()
{
	delete proprietes_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurXML::traiter(ArbreRenduINF2990* arbre)
///
/// Cette fonction traite l'arbre de rendu pour enregistrer ses enfants
/// dans un fichier XML. Cette fonction retourne true pour dire que l'opération s'est
/// faite correctement, ou false si on ne permet pas la sauvegarde
///
/// @return Retourne true ou false.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurXML::traiter(ArbreRenduINF2990* arbre)
{
	// Enregistrer les propriétés de la zone de jeu
	traiterProprietes();

	// ElementArbre sera la racine
	elementArbreRendu = document.NewElement("arbreRenduINF2990");

	// Traiter les enfants de l'arbre
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	// Lier la racine au document XML
	document.LinkEndChild(elementArbreRendu);

	// Enregistrer le document
	document.SaveFile(nomFichier.c_str());

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurXML::traiter(NoeudTable* table)
///
/// Cette fonction traite la table pour enregistrer ses enfants
/// dans un fichier XML. Cette fonction retourne true pour dire que l'opération s'est
/// faite correctement, ou false si on ne permet pas la sauvegarde
///
/// @return Retourne true ou false.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurXML::traiter(NoeudTable* table)
{
	// ElementTable sera un enfant de ElementArbreRendu
	elementTable = document.NewElement("table");
	elementTable->SetAttribute("nbEnfants", table->obtenirNombreEnfants());

	// Traiter les enfants de la table
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}

	// Lier l'arbre à la table
	elementArbreRendu->LinkEndChild(elementTable);

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurXML::traiter(NoeudAbstrait* noeud)
///
/// Cette fonction traite les enfants de l'arbre de rendu. Si ses enfants ont des enfants
/// ils seront aussi traités.Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement.
///
/// @param[in] noeud : Le noeud à traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurXML::traiter(NoeudAbstrait* noeud)
{
	std::string nom = noeud->obtenirType();

	// Créer le noeud
	tinyxml2::XMLElement* element{ document.NewElement(nom.c_str()) };

	if (nom != "couvercle")
	{
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

		if (nom == "paletted" || nom == "paletteg")
			element->SetAttribute("color", noeud->getColorShift());

		elementTable->LinkEndChild(element);
	}

	else
		elementArbreRendu->LinkEndChild(element);

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurXML::traiterProprietes()
///
/// Cette fonction enregistre les propriétés de la zone de jeu
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurXML::traiterProprietes()
{
	// Creer le noeud propriété
	tinyxml2::XMLElement* elementPropriete{ document.NewElement("Proprietes") };

	tinyxml2::XMLElement* elementButoir{ document.NewElement("PointsButoir") };
	elementButoir->SetAttribute("Nombre", proprietes_[0]);
	elementPropriete->LinkEndChild(elementButoir);

	tinyxml2::XMLElement* elementTriangulaire{ document.NewElement("PointsTriangulaire") };
	elementTriangulaire->SetAttribute("Nombre", proprietes_[1]);
	elementPropriete->LinkEndChild(elementTriangulaire);

	tinyxml2::XMLElement* elementCible{ document.NewElement("PointsCible") };
	elementCible->SetAttribute("Nombre", proprietes_[2]);
	elementPropriete->LinkEndChild(elementCible);

	tinyxml2::XMLElement* elementVictoire{ document.NewElement("PointsVictoire") };
	elementVictoire->SetAttribute("Nombre", proprietes_[3]);
	elementPropriete->LinkEndChild(elementVictoire);

	tinyxml2::XMLElement* elementBille{ document.NewElement("PointsBilleGratuite") };
	elementBille->SetAttribute("Nombre", proprietes_[4]);
	elementPropriete->LinkEndChild(elementBille);

	tinyxml2::XMLElement* elementDifficulte{ document.NewElement("Difficulte") };
	elementDifficulte->SetAttribute("Nombre", proprietes_[5]);
	elementPropriete->LinkEndChild(elementDifficulte);

	document.LinkEndChild(elementPropriete);

	return true;
}

