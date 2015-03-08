////////////////////////////////////////////////
/// @file   SingletonGlobal.h
/// @author The Ballers
/// @date   2015-02-24
///
/// @ingroup SingletonGlobal
////////////////////////////////////////////////

#ifndef __SINGLETONGLOBAL_H__
#define __SINGLETONGLOBAL_H__


///////////////////////////////////////////////////////////////////////////
/// @class SingletonGlobal
/// @brief 
///
/// @author The Ballers
/// @date 2015-02-24
///////////////////////////////////////////////////////////////////////////
class SingletonGlobal
{

public:

	/// Obtient l'instance unique de la classe.
	static SingletonGlobal* obtenirInstance();

	/// Libère l'instance unique de la classe.
	static void libererInstance();

	/// AJOUTER VOS GET/SET sur les variables ici

protected:

	/// Constructeur vide déclaré protected.
	SingletonGlobal() {};

	/// Destructeur vide déclaré protected.
	~SingletonGlobal() {};

private:

	static SingletonGlobal* singleton_;

	/// Constructeur par copie déclaré mais non défini.
	SingletonGlobal(const SingletonGlobal&) = delete;

	/// Opérateur d'assignation déclaré mais non défini.
	SingletonGlobal& operator=(const SingletonGlobal&) = delete;

	/// AJOUTER VOS VARIABLES GLOBAL ICI


};

#endif // __SINGLETONGLOBAL_H__