////////////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.cpp
/// @author Jean-François Pérusse
/// @date 2007-01-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "ConfigScene.h"
#include <iostream>
#include "../../Commun/Utilitaire/Utilitaire.h"


ConfigScene::ConfigScene()
{
	fichierDefaut_ = "defaultConfig.xml";
	derniereSauvegarde_ = "lastSave.xml";

	touches_ = new int[5];
	doubleBille_ = false;
	rebond_ = false;
	debogage_ = new bool[4];
}


ConfigScene::~ConfigScene()
{
	delete[] touches_;
	delete[] debogage_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::creerDOM () const
///
/// Cette fonction écrit les valeurs de la configuration dans un élément XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::sauvegarderConfiguration()
{
	tinyxml2::XMLElement* elementConfiguration{ document_.NewElement("Configuration") };
	tinyxml2::XMLElement* elementTouches{ document_.NewElement("Touches") };
	tinyxml2::XMLElement* elementDebug{ document_.NewElement("Debogage") };

	// Touches
	tinyxml2::XMLElement* pGaucheJoueur1{ document_.NewElement("Palette_Gauche_J1") };
	pGaucheJoueur1->SetAttribute("Touche: ", touches_[0]);
	elementTouches->LinkEndChild(pGaucheJoueur1);

	tinyxml2::XMLElement* pDroiteJoueur1{ document_.NewElement("Palette_Droite_J1") };
	pDroiteJoueur1->SetAttribute("Touche: ", touches_[1]);
	elementTouches->LinkEndChild(pDroiteJoueur1);

	tinyxml2::XMLElement* pGaucheJoueur2{ document_.NewElement("Palette_Gauche_J2") };
	pGaucheJoueur2->SetAttribute("Touche: ", touches_[2]);
	elementTouches->LinkEndChild(pGaucheJoueur2);

	tinyxml2::XMLElement* pDroiteJoueur2{ document_.NewElement("Palette_Droite_J2") };
	pDroiteJoueur2->SetAttribute("Touche: ", touches_[3]);
	elementTouches->LinkEndChild(pDroiteJoueur2);

	tinyxml2::XMLElement* elementRessort{ document_.NewElement("Ressort") };
	pDroiteJoueur2->SetAttribute("Touche: ", touches_[4]);
	elementTouches->LinkEndChild(elementRessort);

	elementConfiguration->LinkEndChild(elementTouches);

	// Configurations de jeu
	tinyxml2::XMLElement* doubleBille{ document_.NewElement("Double bille : ") };
	doubleBille->SetAttribute("Activer: ", doubleBille_);
	elementConfiguration->LinkEndChild(doubleBille);

	tinyxml2::XMLElement* rebond{ document_.NewElement("Rebond : ") };
	rebond->SetAttribute("Activer: ", rebond_);
	elementConfiguration->LinkEndChild(rebond);


	// Debogage
	tinyxml2::XMLElement* generation{ document_.NewElement("Generation:") };
	generation->SetAttribute("Activer: ", debogage_[0]);
	elementDebug->LinkEndChild(generation);

	tinyxml2::XMLElement* colision{ document_.NewElement("Colision:") };
	colision->SetAttribute("Activer: ", debogage_[1]);
	elementDebug->LinkEndChild(colision);

	tinyxml2::XMLElement* eclairage{ document_.NewElement("Eclairage:") };
	eclairage->SetAttribute("Activer: ", debogage_[2]);
	elementDebug->LinkEndChild(eclairage);

	tinyxml2::XMLElement* champs{ document_.NewElement("Champs de force:") };
	champs->SetAttribute("Activer: ", debogage_[3]);
	elementDebug->LinkEndChild(champs);

	elementConfiguration->LinkEndChild(elementDebug);

	// Enregistrer
	document_.LinkEndChild(elementConfiguration);
	document_.SaveFile(derniereSauvegarde_.c_str());

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::lireDOM( const TiXmlNode& node )
///
/// Cette fonction lit les valeurs de la configuration à partir d'un élément
/// XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool ConfigScene::lireConfiguration()
{
	bool lectureOK = false;

	// Charger le fichier par défaut si c'est la première fois
	if (!(utilitaire::fichierExiste(derniereSauvegarde_)))
	{
		document_.LoadFile(fichierDefaut_.c_str());
		lectureOK = true;
	}

	// Sinon, toujours charger la dernière sauvegarde
	else
		lireXML();
	
	return lectureOK;
}

void ConfigScene::lireXML()
{
	// Ouvrir le fichier XML
	document_.LoadFile(derniereSauvegarde_.c_str());

	// Racine
	tinyxml2::XMLElement* elementConfiguration = document_.FirstChildElement("Configuration");

	// Options Touches
	tinyxml2::XMLElement* elementTouches = elementConfiguration->FirstChildElement("Touches");
	tinyxml2::XMLElement* touches = elementConfiguration->FirstChildElement("Palette_Gauche_J1");

	for (int i = 0; i < 5; i++)
	{
		touches_[i] = touches->FirstAttribute()->IntValue();
		touches = touches->NextSiblingElement();
	}
	

	// Lire les autres options de configuration
	doubleBille_ = elementConfiguration->FirstAttribute()->BoolValue();
	rebond_ = elementConfiguration->NextSiblingElement()->FirstAttribute()->BoolValue();


	// Options de debogage
	tinyxml2::XMLElement* elementDebug = document_.FirstChildElement("Touches");
	tinyxml2::XMLElement* debug = elementConfiguration->FirstChildElement("Generation:");

	for (int i = 0; i < 4; i++)
	{
		debogage_[i] = debug->FirstAttribute()->IntValue();
		debug = debug->NextSiblingElement();
	}
	
}

void ConfigScene::modifierConfiguration(int touche[5], bool doubleBille, bool rebond, int debogage[4])
{
	for (unsigned i = 0; i < 5; i++)
	{
		touches_[i] = touche[i];
	}

	doubleBille_ = doubleBille;
	rebond_ = rebond;

	for (unsigned int i = 0; i < 4; i++)
	{
		debogage_[i] = debogage[i];
	}

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
