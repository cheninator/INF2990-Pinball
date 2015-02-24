////////////////////////////////////////////////
/// @file   QuadTree.h
/// @author The Ballers
/// @date   2015-02-24
///
/// @ingroup QuadTree
////////////////////////////////////////////////

#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include "../Arbre/Noeuds/NoeudAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class QuadTree
/// @brief 
///
/// @author The Ballers
/// @date 2015-02-24
///////////////////////////////////////////////////////////////////////////
class QuadTree
{
public:

	QuadTree(glm::ivec3 inferieurGauche, glm::ivec3 superieurDroit);
	~QuadTree();

	bool insert(NoeudAbstrait* noeud);
	std::vector<NoeudAbstrait*> retrieve(NoeudAbstrait* noeud);


private:

	QuadTree(int level, glm::ivec3 inferieurGauche, glm::ivec3 superieurDroit);
	void divide();
	void clear();

	const int MAX_CAPACITY = 10;
	const int MAX_LEVEL = 3;

	int niveauCourant_;
	glm::ivec3 inferieurGauche_, superieurDroit_;
	std::vector<NoeudAbstrait*> objets_;

	QuadTree* nordEst_;
	QuadTree* nordOuest_;
	QuadTree* sudEst_;
	QuadTree* sudOuest_;

};

#endif // __QUADTREE_H__