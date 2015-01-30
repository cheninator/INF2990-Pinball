#ifndef  __ARBRE_NOEUDS_NOEUDTABLE_H__
#define  __ARBRE_NOEUDS_NOEUDTABLE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

class NoeudTable : public NoeudComposite
{
public:
	// Constructeur
	NoeudTable(const std::string& typeNoeud);

	// Destructeur 
	~NoeudTable();

	// Surchage de la méthode qui affiche l'objet
	virtual void afficherConcret() const;
	// Surchage de la méthode qui anime l'objet
	virtual void animer(float temps);

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

#endif // __ARBRE_NOEUDS_NOEUDTROU_H__