#ifndef __ARBRES_NOEUDS_NOEUDBUTOIR_H__
#define __ARBRES_NOEUDS_NOEUDBUTOIR_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

class NoeudButoir : public NoeudComposite
{
public:
	// Constructeur
	NoeudButoir(const std::string& typeNoeud);
	// Destructeur 
	~NoeudButoir();

	// Surchage de la méthode qui affiche l'objet
	virtual void afficherConcret() const;
	// Surchage de la méthode qui anime l'objet
	virtual void animer(float temps);

private:
	// TODO(Emilio): Insérer les attributs propres à chaque type d'objet
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };
};

#endif // __ARBRE_NOEUDS_NOEUDBUTOIR_H__