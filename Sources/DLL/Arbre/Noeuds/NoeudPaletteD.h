///////////////////////////////////////////////////////////////////////////
/// @file NoeudPaletteD.h
/// @author Yonni Chen
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef  __ARBRE_NOEUDS_NOEUDPALETTED_H__
#define  __ARBRE_NOEUDS_NOEUDPALETTED_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPaletteD
/// @brief Classe qui représente une palette.
///
/// @author Yonni Chen
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudPaletteD : public NoeudComposite
{
public:
	/// Constructeur
	NoeudPaletteD(const std::string& typeNoeud);
	/// Destructeur 
	~NoeudPaletteD();

	/// Surchage de la méthode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la méthode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

private:
	// TODO(Emilio): Insérer les attributs propres à chaque type d'objet
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };
};

#endif // __ARBRE_NOEUDS_NOEUDPALETTED_H__