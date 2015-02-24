////////////////////////////////////////////////
/// @file QuadTree.cpp
/// @author The Ballers
/// @date 2015-02-24
///
/// @ingroup QuadTree
////////////////////////////////////////////////

#include "QuadTree.h"


QuadTree::QuadTree(glm::ivec3 inferieurGauche, glm::ivec3 superieurDroit)
{
	niveauCourant_ = 0;
	inferieurGauche_ = inferieurGauche;
	superieurDroit_ = superieurDroit;

	nordEst_ = nullptr;
	nordOuest_ = nullptr;
	sudEst_ = nullptr;
	sudOuest_ = nullptr;

}

QuadTree::QuadTree(int level, glm::ivec3 inferieurGauche, glm::ivec3 superieurDroit)
{
	QuadTree(inferieurGauche, superieurDroit);
	niveauCourant_ = level;
}

QuadTree::~QuadTree()
{
	clear();
}

void QuadTree::divide()
{
	//					+------+------+  superieurDroit
	//					|	   |      |
	//					|  NO  |  NE  |
	//					+------+------+
	//					|      |      |
	//					|  SO  |  SE  |
	//					+------+------+
	//	inférieurGauche

	int centreX = (superieurDroit_.x - inferieurGauche_.x) / 2;
	int centreY = (superieurDroit_.y - inferieurGauche_.y) / 2;

	nordEst_ =		new QuadTree(niveauCourant_ + 1, { centreX, centreY, 0 }, superieurDroit_);
	nordOuest_ =	new QuadTree(niveauCourant_ + 1, { inferieurGauche_.x, centreY, 0 }, { centreX, superieurDroit_.y, 0} );
	sudEst_ =		new QuadTree(niveauCourant_ + 1, { centreX, inferieurGauche_.y, 0 }, { superieurDroit_.x, centreY, 0 });
	sudOuest_ =		new QuadTree(niveauCourant_ + 1, inferieurGauche_, { centreX, centreY, 0 } );

}

void QuadTree::clear()
{
	objets_.clear();
	
	if (nordEst_ != nullptr)
	{
		nordEst_->clear();
		nordOuest_->clear();
		sudEst_->clear();
		sudOuest_->clear();

		delete nordEst_;
		delete nordOuest_;
		delete sudEst_;
		delete sudOuest_;
	}

}

bool QuadTree::insert(NoeudAbstrait* noeud)
{
	// Obtenir la position du noeud
	glm::ivec3 positionNoeud = (glm::ivec3)noeud->obtenirPositionRelative();

	// Insérer le noeud seulement si le noeud est dans le Quadtree
	if (positionNoeud.x < superieurDroit_.x && positionNoeud.x > inferieurGauche_.x
		&& positionNoeud.y < superieurDroit_.y && positionNoeud.y > inferieurGauche_.y)
	{

		// Insérer l'objet dans le QuadTree courant
		if (objets_.size() < MAX_CAPACITY && niveauCourant_ < MAX_LEVEL)
		{
			objets_.push_back(noeud);
			return true;
		}

		// Subdiviser et reassigner les objets déjà existants
		if (nordEst_ == nullptr)
		{
			divide();

			// Repositionner les objets déjà existants du parent
			for (unsigned int i = 0; i < objets_.size(); i++)
			{
				// Si l'objet se trouve dans plus qu'un seul QuadTree, son parent le possèdera
				if (!nordEst_->insert(objets_.back()))
					insert(objets_.back());

				else if (!nordOuest_->insert(objets_.back()))
					insert(objets_.back());

				else if (!sudEst_->insert(objets_.back()))
					insert(objets_.back());

				else if (!sudOuest_->insert(objets_.back()))
					insert(objets_.back());

				objets_.pop_back();
			}

		}

		else if (nordEst_ != nullptr)
		{
			// Si le nouveau noeud a ajouter se retrouve dans plus qu'un seul QuadTree, son parent le traitera
			if (!nordEst_->insert(noeud))
				insert(noeud);

			if (!nordOuest_->insert(noeud))
				insert(noeud);

			if (!sudEst_->insert(noeud))
				insert(noeud);

			if (!sudOuest_->insert(noeud))
				insert(noeud);

			return true;
		}

		// Ne devrait jamais se rendre jusqu'ici
		return false;

	}

	else
		return false;

}

std::vector<NoeudAbstrait*> QuadTree::retrieve(NoeudAbstrait* noeud)
{
	std::vector<NoeudAbstrait*> resultat;

	// Obtenir la position du noeud
	glm::ivec3 positionNoeud = (glm::ivec3)noeud->obtenirPositionRelative();

	// Insérer le noeud seulement si le noeud est dans le Quadtree
	if (positionNoeud.x < superieurDroit_.x && positionNoeud.x > inferieurGauche_.x
		&& positionNoeud.y < superieurDroit_.y && positionNoeud.y > inferieurGauche_.y)
	{




	}
	
	return resultat;
}