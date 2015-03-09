////////////////////////////////////////////////
/// @file SingletonGlobal.cpp
/// @author The Ballers
/// @date 2015-02-24
///
/// @ingroup Global
////////////////////////////////////////////////

#include "SingletonGlobal.h"

SingletonGlobal* SingletonGlobal::singleton_{ nullptr };
////////////////////////////////////////////////////////////////////////
///
/// @fn SingletonGlobal* SingletonGlobal::obtenirInstance()
///
/// Cette fonction retourne l'instance unique de la classe. Si l'instance
/// n'existe pas, elle est créée. Ainsi, une seule instance sera créée.
/// Cette fonction n'est pas "thread-safe".
///
/// @return L'instance unique de la classe.
///
////////////////////////////////////////////////////////////////////////
SingletonGlobal* SingletonGlobal::obtenirInstance()
{
	if (singleton_ == nullptr)
		singleton_ = new SingletonGlobal();
	
	return singleton_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void SingletonGlobal::libererInstance()
///
/// Détruit l'instance unique de la classe.  Cette fonction n'est pas
/// "thread-safe".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SingletonGlobal::libererInstance()
{
	delete singleton_;
	singleton_ = 0;
}