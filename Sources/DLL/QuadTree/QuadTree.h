////////////////////////////////////////////////
/// @file   QuadTree.h
/// @author The Ballers
/// @date   2015-02-24
///
/// @ingroup QuadTree
////////////////////////////////////////////////

#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <list>
#include "../Arbre/Noeuds/NoeudAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class QuadTree
/// @brief Cette classe permet de reduire le nombre de calcul/comparaisons
///			à effectuer pour la gestion de la physique.
///
/// @author The Ballers
/// @date 2015-02-24
///////////////////////////////////////////////////////////////////////////
class QuadTree
{
public:

	/// Constructeur pour le 1er QuadTree
	QuadTree(glm::dvec3 inferieurGauche, glm::dvec3 superieurDroit);

	/// Destructeur
	~QuadTree();

	/// Inserer des noeuds dans le QuadTree
	bool insert(NoeudAbstrait* noeud);

	/// Retourne la liste des objets se trouvant dans le même quand que le noeud passe en paramètre
	std::list<NoeudAbstrait*> retrieve(NoeudAbstrait* noeud);

	/// Retirer un noeud du QuadTree
	bool remove(NoeudAbstrait* noeud);

	/// Vider le QuadTree et les sous QuadTree
	void clear();

private:

	/// Constructeur pour les sous QuadTree
	QuadTree(int level, glm::dvec3 inferieurGauche, glm::dvec3 superieurDroit);

	/// Diviser le QuadTree lorsque la capacite maximale est atteinte
	void divide();

	/// Verifier si l'objet est dans le QuadTree
	bool estDansQuadTree(NoeudAbstrait* noeud, QuadTree* quad) const;

	/// Verifier si un point est dans le QuadTree
	bool estDansQuadTree(glm::dvec3 point, QuadTree* quad) const;

	/// Retourne le QuadTree dans lequel il faut faire l'insertion
	QuadTree* obtenirQuadrant(NoeudAbstrait* noeud);

	// Propriétés du QuadTree
	const int MAX_CAPACITY = 10;
	const int MAX_LEVEL = 3;
	int niveauCourant_;

	/// Pour delimiter l'espace du QuadTree
	glm::dvec3 inferieurGauche_, superieurDroit_;

	/// Contient la liste des objets appartenant au QuadTree
	std::list<NoeudAbstrait*> objets_;

	/// Pour la subdivision du QuadTree en sous QuadTree
	QuadTree* nordEst_;
	QuadTree* nordOuest_;
	QuadTree* sudEst_;
	QuadTree* sudOuest_;

};

#endif // __QUADTREE_H__