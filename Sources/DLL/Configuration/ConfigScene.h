//////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.h
/// @author Jean-François Pérusse
/// @date 2007-01-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __CONFIGURATION_CONFIGSCENE_H__
#define __CONFIGURATION_CONFIGSCENE_H__

#include "tinyxml2.h"
#include <string>

///////////////////////////////////////////////////////////////////////////
/// @class ConfigScene
/// @brief Les variables de configuration de la classe CScene.
///        C'est une classe singleton.
///
/// @author Jean-François Pérusse
/// @date 2007-01-10
///////////////////////////////////////////////////////////////////////////
class ConfigScene
{

public:

	ConfigScene();
	~ConfigScene();

	void sauvegarderConfiguration();

	bool lireConfiguration();

	void modifierConfiguration(int config[12]);

private:

	int* config_;

	std::string fichierDefaut_, derniereSauvegarde_;
	tinyxml2::XMLDocument document_;

	void lireXML();

};


#endif // __CONFIGURATION_CONFIGSCENE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
