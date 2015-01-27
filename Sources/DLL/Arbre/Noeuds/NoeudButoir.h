///////////////////////////////////////////////////////////////////////////
/// @file NoeudButoir.h
/// @author Yonni Chen
/// @date 2015-01-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBUTOIR_H__
#define __ARBRE_NOEUDS_NOEUDBUTOIR_H__


#include "NoeudComposite.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudButoir
/// @brief Classe qui représente un butoir
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudButoir : public NoeudComposite
{
public:

	/// Constructeur à partir du type du noeud.
	NoeudButoir(const std::string& typeNoeud);

	/// Destructeur.
	~NoeudButoir();

	/// Affiche le butoir.
	virtual void afficherConcret() const;

	/// Effectue l'animation du butoir.
	virtual void animer(float temps);

	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

private:

	/// Angle dans le sinus de l'oscillation
	float angle_{ 0 };

};

#endif // __ARBRE_NOEUDS_NOEUDBUTOIR_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////