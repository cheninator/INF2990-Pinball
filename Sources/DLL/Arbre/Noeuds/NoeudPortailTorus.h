///////////////////////////////////////////////////////////////////////////
/// @file NoeudPortailTorus.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef  __ARBRE_NOEUDS_NOEUDPORTAILTORUS_H__
#define  __ARBRE_NOEUDS_NOEUDPORTAILTORUS_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPortailTorus
/// @brief Classe qui represente un portailTorus.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudPortailTorus : public NoeudComposite
{
public:
	/// Constructeur
	NoeudPortailTorus(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudPortailTorus();

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);
};

#endif // __ARBRE_NOEUDS_NOEUDPORTAILTORUS_H__