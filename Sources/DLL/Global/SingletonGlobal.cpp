////////////////////////////////////////////////
/// @file SingletonGlobal.cpp
/// @author The Ballers
/// @date 2015-02-24
///
/// @ingroup Global
////////////////////////////////////////////////

#include "SingletonGlobal.h"


SingletonGlobal* SingletonGlobal::obtenirInstance()
{
	if (singleton_ == nullptr)
		singleton_ = new SingletonGlobal();
	
	return singleton_;
}

SingletonGlobal::~SingletonGlobal()
{
	delete singleton_;
	singleton_ = 0;
}