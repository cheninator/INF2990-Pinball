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
#include <vector>

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

	/// Constructeur par copie non-necessaire dans le contexte
	ConfigScene(const ConfigScene &) = delete;

	/// Assignation par copie non-necessaire dans le contexte
	ConfigScene& operator=(ConfigScene const&) = delete;

	// Sauvegarder derniere configuration en fichier binaire
	void sauvegarderConfiguration();

	// Sauvegarder derniere campagne en fichier texte
	void sauvegarderCampagne();

	// Lire le fichier de la derniere configuration
	bool lireConfiguration();

	// Lire le fichier de la derniere campagne
	bool lireCampagne();

	// Modifier les variables de configuration
	void modifierConfiguration(int config[12]);

	// Modifier la liste des cartes de campagne
	void modifierCampagne(char* maps);

	// Retourne les configurations de l'objets
	int* obtenirConfiguration() const { return config_; };

	// Retourne les informations de la derniere campagne
	std::string obtenirCampagne() const;

	// Fonctions de retour des configurations
	int obtenirRaccourciPGJ1()		const{ return config_[0]; };
	int obtenirRaccourciPDJ1()		const{ return config_[1]; };
	int obtenirRaccourciPGJ2()		const{ return config_[2]; };
	int obtenirRaccourciPDJ2()		const{ return config_[3]; };
	int obtenirRaccourciRessort()	const{ return config_[4]; };
	int obtenirNombreBilles()		const{ return config_[5]; };
	int obtenirModeDoubleBille()	const{ return config_[6]; };
	int obtenirModeForceRebond()	const{ return config_[7]; };
	int obtenirAfficherGeneration() const{ return config_[8]; };
	int obtenirAfficherVitesse()	const{ return config_[9]; };
	int obtenirAfficherEclairage()	const{ return config_[10]; };
	int obtenirAfficherChampForce() const{ return config_[11]; };
	int obtenirAffichageGlobal()    const{ return config_[12]; };
	void bloquerAffichageGlobal(int active)   { config_[12] = active; };

private:

	// Lis un fichier binaire
	void lireFichierBinaire();

	// Nom de la derniere sauvegarde de configuration
	std::string derniereConfiguration_{ "lastConfig.bin" };
	std::string derniereCampagne_{ "lastCampaign.txt" };

	// Contient toutes les informations relative a la configuration du jeu
	int* config_;

	// Liste des cartes de la derniere partie de campagne
	std::vector<std::string> listeCartes_;

};


#endif // __CONFIGURATION_CONFIGSCENE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
