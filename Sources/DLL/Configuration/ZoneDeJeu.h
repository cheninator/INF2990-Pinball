//////////////////////////////////////////////////////////////////////////////
/// @file ZoneDeJeu.h
/// @author The Ballers
/// @date 2015-01-31
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __CONFIGURATION_ZONEDEJEU_H__
#define __CONFIGURATION_ZONEDEJEU_H__


#include "Singleton.h"
#include "tinyxml2.h"
#include <string>

///////////////////////////////////////////////////////////////////////////
/// @class ZoneDeJeu
/// @brief Les éléments de la zone de jeu
///        C'est une classe singleton.
///
/// @author Jean-François Pérusse
/// @date 2007-01-10
///////////////////////////////////////////////////////////////////////////
class ZoneDeJeu : public Singleton<ZoneDeJeu>
{
	SINGLETON_DECLARATION_CLASSE(ZoneDeJeu);

public:

	/// Créer le DOM avec les valeurs.
	void creerDOM(tinyxml2::XMLDocument& document) const;

	/// Lire les valeurs du DOM.
	void lireDOM(tinyxml2::XMLDocument const& document);

private:

	std::string  

};


#endif // __CONFIGURATION_ZONEDEJEU_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
