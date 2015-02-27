//////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.h
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Configuration
///
//////////////////////////////////////////////////////////////////////////////
#ifndef __CONFIGURATION_CONFIGSCENE_H__
#define __CONFIGURATION_CONFIGSCENE_H__

#include <string>

///////////////////////////////////////////////////////////////////////////
/// @class ConfigScene
/// @brief Les variables de configuration de la classe CScene.
///
/// @author The Ballers
/// @date 2015-02-25
///////////////////////////////////////////////////////////////////////////
class ConfigScene
{

public:

	// Constructeur
	ConfigScene();

	// Destructeur
	~ConfigScene();

	// Sauvegarder en fichier binaire
	void sauvegarderConfiguration();

	// Lire le fichier de la dernière configuration
	bool lireConfiguration();

	// Modifier les variables de configuration
	void modifierConfiguration(int config[12]);

	// Retourne les configurations de l'objets
	int* obtenirConfiguration() const { return config_; };

	// Fonctions de retour des configurations
	int obtenirRaccourciPGJ1() const{ return config_[0]; };
	int obtenirRaccourciPDJ1() const{ return config_[1]; };
	int obtenirRaccourciPGJ2() const{ return config_[2]; };
	int obtenirRaccourciPDJ2() const{ return config_[3]; };
	int obtenirRaccourciRessort() const{ return config_[4]; };
	int obtenirNombreBilles() const{ return config_[5]; };
	int obtenirModeDoubleBille() const{ return config_[6]; };
	int obtenirModeForceRebond() const{ return config_[7]; };
	int obtenirAfficherGeneration() const{ return config_[8]; };
	int obtenirAfficherVitesse() const{ return config_[9]; };
	int obtenirAfficherEclairage() const{ return config_[10]; };
	int obtenirAfficherChampForce() const{ return config_[11]; };

private:

	// Lis un fichier binaire
	void lireFichierBinaire();

	// Contient toutes les informations relative à la configuration du jeu
	int* config_;

	// Nom de la dernière sauvegarde
	std::string derniereSauvegarde_;

};


#endif // __CONFIGURATION_CONFIGSCENE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
