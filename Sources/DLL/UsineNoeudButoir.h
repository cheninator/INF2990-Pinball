///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudButoir.h
/// @author Yonni Chen
/// @date 2015-01-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDBUTOIR_H__
#define __ARBRE_USINES_USINENOEUDBUTOIR_H__

#include "UsineNoeud.h"
#include "NoeudButoir.h"



class UsineNoeudButoir : public UsineNoeud
{
public:
	// Contrusteur par paramètre
	inline UsineNoeudButoir(const std::string& nom);
	
	/// Fonction à surcharger pour la création d'un noeud.
	inline virtual NoeudAbstrait* creerNoeud() const;
	
	
	
	~UsineNoeudButoir();
};

#endif // __ARBRE_USINES_USINENOEUDBUTOIR_H__