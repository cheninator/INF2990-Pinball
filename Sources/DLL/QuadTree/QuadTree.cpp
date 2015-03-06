////////////////////////////////////////////////
/// @file QuadTree.cpp
/// @author The Ballers
/// @date 2015-02-24
///
/// @ingroup QuadTree
////////////////////////////////////////////////

#include "QuadTree.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn QuadTree::QuadTree()
///
/// 
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
QuadTree::QuadTree(glm::dvec3 inferieurGauche, glm::dvec3 superieurDroit)
{
	niveauCourant_ = 0;
	inferieurGauche_ = inferieurGauche;
	superieurDroit_ = superieurDroit;

	nordEst_ = nullptr;
	nordOuest_ = nullptr;
	sudEst_ = nullptr;
	sudOuest_ = nullptr;

	std::cout << "Creation d'un QuadTree " << std::endl;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn QuadTree::QuadTree()
///
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
QuadTree::QuadTree(int level, glm::dvec3 inferieurGauche, glm::dvec3 superieurDroit)
{
	inferieurGauche_ = inferieurGauche;
	superieurDroit_ = superieurDroit;
	niveauCourant_ = level;

	nordEst_ = nullptr;
	nordOuest_ = nullptr;
	sudEst_ = nullptr;
	sudOuest_ = nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn QuadTree::~QuadTree()
///
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
QuadTree::~QuadTree()
{
	clear();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::divide()
///
///
/// @return NoeudAbstrait* L'enfant en question.
///
////////////////////////////////////////////////////////////////////////
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

	double centreX = ((superieurDroit_.x - inferieurGauche_.x) / 2.0 ) + inferieurGauche_.x;
	double centreY = ((superieurDroit_.y - inferieurGauche_.y) / 2.0 ) + inferieurGauche_.y;

	nordEst_ =		new QuadTree(niveauCourant_ + 1, { centreX, centreY, 0 }, superieurDroit_);
	nordOuest_ =	new QuadTree(niveauCourant_ + 1, { inferieurGauche_.x, centreY, 0 }, { centreX, superieurDroit_.y, 0});
	sudEst_ =		new QuadTree(niveauCourant_ + 1, { centreX, inferieurGauche_.y, 0 }, { superieurDroit_.x, centreY, 0 });
	sudOuest_ =		new QuadTree(niveauCourant_ + 1, inferieurGauche_, { centreX, centreY, 0 });

	std::cout << "Subdivision en cours... " << std::endl;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::divide()
///
///
/// @return NoeudAbstrait* L'enfant en question.
///
////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::divide()
///
///
/// @return NoeudAbstrait* L'enfant en question.
///
////////////////////////////////////////////////////////////////////////
bool QuadTree::estDansQuadTree(NoeudAbstrait* noeud, QuadTree* quad) const
{
	if (quad == nullptr)
		return false;

	bool estPresent = false;
	std::vector<glm::dvec3> points;

	points.push_back({ 0.0, 0.0, 0.0});
	points.push_back({ 0.0, 0.0, 0.0 });
	points.push_back({ 0.0, 0.0, 0.0 });
	points.push_back({ 0.0, 0.0, 0.0 });

	noeud->obtenirVecteursBoite(points[0], points[1], points[2], points[3]);

	points[0].x += noeud->obtenirPositionRelative().x;
	points[0].y += noeud->obtenirPositionRelative().y;
	points[1].x += noeud->obtenirPositionRelative().x;
	points[1].y += noeud->obtenirPositionRelative().y;
	points[2].x += noeud->obtenirPositionRelative().x;
	points[2].y += noeud->obtenirPositionRelative().y;
	points[3].x += noeud->obtenirPositionRelative().x;
	points[3].y += noeud->obtenirPositionRelative().y;

	if (   points[0].x > quad->inferieurGauche_.x && points[0].x < quad->superieurDroit_.x
		&& points[0].y > quad->inferieurGauche_.y && points[0].y < quad->superieurDroit_.y
		&& points[1].x > quad->inferieurGauche_.x && points[1].x < quad->superieurDroit_.x
		&& points[1].y > quad->inferieurGauche_.y && points[1].y < quad->superieurDroit_.y
		&& points[2].x > quad->inferieurGauche_.x && points[2].x < quad->superieurDroit_.x
		&& points[2].y > quad->inferieurGauche_.y && points[2].y < quad->superieurDroit_.y
		&& points[3].x > quad->inferieurGauche_.x && points[3].x < quad->superieurDroit_.x
		&& points[3].y > quad->inferieurGauche_.y && points[3].y < quad->superieurDroit_.y)
		estPresent = true;

	return estPresent;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::divide()
///
///
/// @return NoeudAbstrait* L'enfant en question.
///
////////////////////////////////////////////////////////////////////////
QuadTree* QuadTree::obtenirQuadrant(NoeudAbstrait* noeud)
{
	glm::dvec3 position = noeud->obtenirPositionRelative();

	// Si le noeud est complètement dans le quadrant Nord-Est
	if (estDansQuadTree(noeud, nordEst_))
		return nordEst_;

	// Si le noeud est complètement dans le quadrant Nord-Ouest
	if (estDansQuadTree(noeud, nordOuest_))
		return nordOuest_;

	// Si le noeud est complètement dans le quadrant Sud-Ouest
	if (estDansQuadTree(noeud, sudOuest_))
		return sudOuest_;

	// Si le noeud est complètement dans le quadrant Sud-Est
	if (estDansQuadTree(noeud, sudEst_))
		return sudEst_;

	// Si le noeud est à l'intersection de deux quadrants et plus
	else
		return this;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::divide()
///
///
/// @return NoeudAbstrait* L'enfant en question.
///
////////////////////////////////////////////////////////////////////////
bool QuadTree::insert(NoeudAbstrait* noeud)
{
	// Obtenir la position du noeud
	glm::ivec3 positionNoeud = (glm::ivec3)noeud->obtenirPositionRelative();

	// Insérer le noeud seulement si le noeud est dans le Quadtree
	if (estDansQuadTree(noeud, this))
	{

		// Insérer l'objet dans le QuadTree courant
		if (objets_.size() < MAX_CAPACITY && niveauCourant_ < MAX_LEVEL)
		{
			if (obtenirQuadrant(noeud) == this)
			{
				std::cout << " INSERTION " << std::endl;
				objets_.push_back(noeud);
				return true;
			}
		}

		// Subdiviser et reassigner les objets déjà existants
		if (nordEst_ == nullptr)
		{
			divide();
			std::cout << " SUBDIVISION REUSSI " << std::endl;
			
			std::vector<NoeudAbstrait*> copy = objets_;
			objets_.clear();

			for (int i = 0; i < copy.size(); i++)
				obtenirQuadrant(copy[i])->insert(copy[i]);

			obtenirQuadrant(noeud)->insert(noeud);

		}

		// Si le QuadTree contient déjà des sous QuadTree
		else if (nordEst_ != nullptr)
		{
			obtenirQuadrant(noeud)->insert(noeud);
			return true;
		}
		
	}

	// Ne pas insérer le noeud, il n'est pas dans les limites
	else
		return false;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::divide()
///
///
/// @return NoeudAbstrait* L'enfant en question.
///
////////////////////////////////////////////////////////////////////////
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