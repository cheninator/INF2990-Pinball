////////////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.cpp
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Configuration
///
////////////////////////////////////////////////////////////////////////////////////

#include "ConfigScene.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn ConfigScene::ConfigScene()
///
/// Assigne les valeurs par défaut des attributs de classe
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ConfigScene::ConfigScene()
{
	derniereSauvegarde_ = "lastSave.xml";
	config_ = new int[12];
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ConfigScene::~ConfigScene()
///
/// Detruit les informations internes relatives à la configuration
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ConfigScene::~ConfigScene()
{
	delete[] config_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::sauvegarderConfiguration()
///
/// Cette fonction écrit les valeurs de la configuration dans un fichier XML.
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
	pGaucheJoueur1->SetAttribute("Touche: ", config_[0]);
	elementTouches->LinkEndChild(pGaucheJoueur1);

	tinyxml2::XMLElement* pDroiteJoueur1{ document_.NewElement("Palette_Droite_J1") };
	pDroiteJoueur1->SetAttribute("Touche: ", config_[1]);
	elementTouches->LinkEndChild(pDroiteJoueur1);

	tinyxml2::XMLElement* pGaucheJoueur2{ document_.NewElement("Palette_Gauche_J2") };
	pGaucheJoueur2->SetAttribute("Touche: ", config_[2]);
	elementTouches->LinkEndChild(pGaucheJoueur2);

	tinyxml2::XMLElement* pDroiteJoueur2{ document_.NewElement("Palette_Droite_J2") };
	pDroiteJoueur2->SetAttribute("Touche: ", config_[3]);
	elementTouches->LinkEndChild(pDroiteJoueur2);

	tinyxml2::XMLElement* elementRessort{ document_.NewElement("Ressort") };
	pDroiteJoueur2->SetAttribute("Touche: ", config_[4]);
	elementTouches->LinkEndChild(elementRessort);

	elementConfiguration->LinkEndChild(elementTouches);

	// Configurations de jeu
	tinyxml2::XMLElement* nombreBille{ document_.NewElement("Nombre de bille ") };
	nombreBille->SetAttribute("Nombre: ", config_[5]);
	elementConfiguration->LinkEndChild(nombreBille);

	tinyxml2::XMLElement* doubleBille{ document_.NewElement("Double bille ") };
	doubleBille->SetAttribute("Activer: ", config_[6]);
	elementConfiguration->LinkEndChild(doubleBille);

	tinyxml2::XMLElement* rebond{ document_.NewElement("Rebond ") };
	rebond->SetAttribute("Activer: ", config_[7]);
	elementConfiguration->LinkEndChild(rebond);


	// Debogage
	tinyxml2::XMLElement* generation{ document_.NewElement("Generation") };
	generation->SetAttribute("Activer: ", config_[8]);
	elementDebug->LinkEndChild(generation);

	tinyxml2::XMLElement* colision{ document_.NewElement("Colision") };
	colision->SetAttribute("Activer: ", config_[9]);
	elementDebug->LinkEndChild(colision);

	tinyxml2::XMLElement* eclairage{ document_.NewElement("Eclairage") };
	eclairage->SetAttribute("Activer: ", config_[10]);
	elementDebug->LinkEndChild(eclairage);

	tinyxml2::XMLElement* champs{ document_.NewElement("Champs de force") };
	champs->SetAttribute("Activer: ", config_[11]);
	elementDebug->LinkEndChild(champs);

	elementConfiguration->LinkEndChild(elementDebug);

	// Enregistrer
	document_.LinkEndChild(elementConfiguration);
	document_.SaveFile(derniereSauvegarde_.c_str());

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool ConfigScene::lireConfiguration()
///
/// Cette fonction lit les valeurs de la configuration à de la dernière
/// configuration de jeu.
///
/// @return True pour indiquer que la lecture s'est bien faite. False autrement
///
////////////////////////////////////////////////////////////////////////
bool ConfigScene::lireConfiguration()
{
	bool lectureOK = false;

	lireXML();
	lectureOK = true;
	
	return lectureOK;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::lireXML()
///
/// Cette fonction lit les valeurs de la configuration à partir d'un élément
/// XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
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
		config_[i] = touches->FirstAttribute()->IntValue();
		touches = touches->NextSiblingElement();
	}
	

	// Lire les autres options de configuration
	config_[5] = elementConfiguration->FirstAttribute()->IntValue();
	config_[6] = elementConfiguration->NextSiblingElement()->FirstAttribute()->IntValue();
	config_[7] = elementConfiguration->NextSiblingElement()->FirstAttribute()->IntValue();


	// Options de debogage
	tinyxml2::XMLElement* elementDebug = document_.FirstChildElement("Touches");
	tinyxml2::XMLElement* debug = elementConfiguration->FirstChildElement("Generation");

	for (int i =8; i < 12; i++)
	{
		config_[i] = debug->FirstAttribute()->IntValue();
		debug = debug->NextSiblingElement();
	}
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::modifierConfiguration(int config[12])
///
/// Cette fonction assigne les nouvelles configurations de zone de jeu.
///
/// @param[in] config[12] : Un tableau contenant les informations de configuration
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::modifierConfiguration(int config[12])
{
	config_[0] = config[0];		// Palette gauche joueur 1
	config_[1] = config[1];		// Palette droite joueur 1
	config_[2] = config[2];		// Palette gauche joueur 2
	config_[3] = config[3];		// Palette droite joueur 2
	config_[4] = config[4];		// Ressort
	config_[5] = config[5];		// Nombre de billes par partie
	config_[6] = config[6];		// Mode double bille
	config_[7] = config[7];		// Mode force de rebond
	config_[8] = config[8];		// Génération d'une bille
	config_[9] = config[9];		// Vitesse après collision
	config_[10] = config[10];	// Activation de l'éclairage
	config_[11] = config[11];	// Champ d'attraction de portail

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
