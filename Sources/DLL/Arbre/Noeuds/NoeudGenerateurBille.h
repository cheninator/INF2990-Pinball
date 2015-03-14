///////////////////////////////////////////////////////////////////////////
/// @file NoeudGenerateurBille.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRES_NOEUDS_NOEUDGENERATEURBILLE_H__
#define __ARBRES_NOEUDS_NOEUDGENERATEURBILLE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudGenerateurBille
/// @brief Classe qui represente un generateur de bille.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudGenerateurBille : public NoeudComposite
{
public:
	/// Constructeur
	NoeudGenerateurBille(const std::string& typeNoeud);

	// Destructeur 
	~NoeudGenerateurBille();

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);
	
	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

private:
	Etat etatGenerateur_ { INITIAL };
	Direction directionGenerateur_ { dirZ };
	bool inverserDirection_ { false };
	float compteurAnimation_ { 0 };
	float compteurAnimationBouger_{ 0 };
	float distanceBouger_ { 0 };
	// Vu que le temps n'est pas constant, on dois remettre la table a sa position par defaut
	glm::dvec3 positionPreDeplacement_{ 0 };	
};

#endif // __ARBRE_NOEUDS_NOEUDGENERATEURBILLE_H__