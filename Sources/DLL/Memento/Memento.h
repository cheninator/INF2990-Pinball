////////////////////////////////////////////////
/// @file   Memento.h
/// @author The Ballers
/// @date   2015-02-24
///
/// @ingroup Memento
////////////////////////////////////////////////

#ifndef __MEMENTO_H__
#define __MEMENTO_H__


#include "../Arbre/ArbreRenduINF2990.h"

///////////////////////////////////////////////////////////////////////////
/// @class Originator
/// @brief 
///
/// @author The Ballers
/// @date 2015-02-24
///////////////////////////////////////////////////////////////////////////
class Memento
{

public:

	virtual ~Memento();

private:

	friend class Originator;

	/// Constructeur
	Memento(ArbreRenduINF2990* arbreAEnregistrer) { arbreEnregistrer_ = arbreAEnregistrer; };

	/// Obtenir l'arbre sauvegarde
	ArbreRenduINF2990* obtenirArbreEnregistrer() const { return arbreEnregistrer_; };

	ArbreRenduINF2990* arbreEnregistrer_;

};




#endif