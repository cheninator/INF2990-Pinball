////////////////////////////////////////////////
/// @file QuadTree.cpp
/// @author The Ballers
/// @date 2015-02-24
///
/// @ingroup QuadTree
////////////////////////////////////////////////

#include "QuadTree.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn QuadTree::QuadTree(glm::dvec3 inferieurGauche, glm::dvec3 superieurDroit)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] inferieurGauche, inferieurDroit : Les limites du QuadTree
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

}


////////////////////////////////////////////////////////////////////////
///
/// @fn QuadTree::QuadTree(glm::dvec3 inferieurGauche, glm::dvec3 superieurDroit)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] level : le niveau du QuadTree
/// @param[in] inferieurGauche, inferieurDroit : Les limites du QuadTree
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
/// Le destructeur desalloue l'espace attribué dynamiquement. Il appelle
///	la méthode clear().
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
/// Cette méthode alloue dynamiquement les sous QuadTree avec les bonnes
///	limites spaciales. 
///
/// @return Aucune
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

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::clear()
///
///	Cette méthode vide la liste des noeuds d'un QuadTree et s'occupe de
///	la désallocation de mémoire de ses sous QuadTree.
///
/// @return Aucune
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
/// @fn bool QuadTree::estDansQuadTree(NoeudAbstrait* noeud, QuadTree* quad)
///
/// Cette méthode permet de savoir si un noeud est complétement contenu dans
///	un QuadTree.
///
/// @param[in] noeud : le noeud à insérer
/// @param[in] quad : le quad dans lequel on veut insérer
///
/// @return True lorsque le noeud est dans le QuadTree passé en paramètre. False autrement
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
/// @fn QuadTree* QuadTree::obtenirQuadrant(NoeudAbstrait* noeud)
///
/// Cette méthode retourne le quadrant dans lequel il faudra insérer
/// un noeud. Retourne le parent des quadrants si le noeud est à l'intersection
///	de plusieurs quadrants
///
/// @param[in] noeud : le noeud à insérer
///
/// @return QuadTree*, le quadTree dans lequel il faudra insérer le noeud
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
/// @fn void QuadTree::insert(NoeudAbstrait* noeud)
///
/// Cette méthode insère un noeud dans le QuadTree
///
/// @param[in] noeud : le noeud à insérer
///
/// @return True lorsque le noeud a été insérer, false autrement
///
////////////////////////////////////////////////////////////////////////
bool QuadTree::insert(NoeudAbstrait* noeud)
{
	// Insérer le noeud seulement si le noeud est dans le Quadtree
	if (estDansQuadTree(noeud, this))
	{
		// Insérer l'objet dans le QuadTree courant
		if (objets_.size() < MAX_CAPACITY && niveauCourant_ < MAX_LEVEL)
		{
			// Seulement si aucun de ses sous QuadTree ne peut le recevoir
			if (obtenirQuadrant(noeud) == this)
			{
				objets_.push_back(noeud);
				return true;
			}
		}

		// Subdiviser et reassigner les objets déjà existants
		if (nordEst_ == nullptr)
		{
			divide();
			
			std::vector<NoeudAbstrait*> copy = objets_;
			objets_.clear();

			// Reassigner les objets qui étaient précédemment insérés 
			for (int i = 0; i < copy.size(); i++)
				obtenirQuadrant(copy[i])->insert(copy[i]);

			// Ajouter le nouveau noeud
			obtenirQuadrant(noeud)->insert(noeud);

			return true;
		}

		// Si le QuadTree contient déjà des sous QuadTree, insérer le noeud dans le bon QuadTree
		else if (nordEst_ != nullptr)
		{
			obtenirQuadrant(noeud)->insert(noeud);
			return true;
		}

		// Ne devrait JAMAIS se rendre jusqu'ici
		else
			return false;
		
	}

	// Ne pas insérer le noeud, il n'est pas dans les limites
	else
		return false;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<NoeudAbstrait*> QuadTree::retrieve(NoeudAbstrait* noeud)
///
/// Cette méthode retourne la liste des noeuds qui sont dans le même QuadTree que
/// le noeud passé en paramètre.
///
/// @param[in] noeud : le noeud pour lequel on désire ses voisins
///
/// @return l'ensemble des noeuds qui sont dans le même QuadTree que le noeud passé
///			en paramètre
///
////////////////////////////////////////////////////////////////////////
std::vector<NoeudAbstrait*> QuadTree::retrieve(NoeudAbstrait* noeud)
{
	std::vector<NoeudAbstrait*> listeNoeuds;

	if (estDansQuadTree(noeud, this))
	{
		// Le quad n'a pas de sous QuadTree
		if (nordEst_ == nullptr)
			return objets_;

		// Le quad a un sous QuadTree et le parent de ce dernier ne contient aucun noeud
		else if (nordEst_ != nullptr && objets_.size() == 0)
			return obtenirQuadrant(noeud)->retrieve(noeud);

		// Le quad a un sous QuadTree et le parent de ce dernier contient des noeuds
		else if (nordEst_ != nullptr && objets_.size() != 0)
		{
			if (obtenirQuadrant(noeud) != this)
			{
				std::vector<NoeudAbstrait*> sousQuad = obtenirQuadrant(noeud)->retrieve(noeud);

				// Ajouter d'abord les noeuds du parent
				listeNoeuds = objets_;

				// Ajouter les noeuds du sous QuadTree
				for (int i = 0; i < sousQuad.size(); i++)
					listeNoeuds.push_back(sousQuad[i]);

				sousQuad.clear();

				return listeNoeuds;
			}

			// Retourner tous les objets du QuadTree, incluant les objets de ses sous QuadTree
			else if (obtenirQuadrant(noeud) == this)
			{
				std::vector<NoeudAbstrait*> nordEst = nordEst_->objets_;
				std::vector<NoeudAbstrait*> nordOuest = nordOuest_->objets_;
				std::vector<NoeudAbstrait*> sudEst = sudEst_->objets_;
				std::vector<NoeudAbstrait*> sudOuest = sudOuest_->objets_;

				listeNoeuds = objets_;

				for (int i = 0; i < nordEst.size(); i++)
					listeNoeuds.push_back(nordEst[i]);

				for (int i = 0; i < nordEst.size(); i++)
					listeNoeuds.push_back(nordOuest[i]);

				for (int i = 0; i < nordEst.size(); i++)
					listeNoeuds.push_back(sudEst[i]);

				for (int i = 0; i < nordEst.size(); i++)
					listeNoeuds.push_back(sudOuest[i]);

				return listeNoeuds;
			}

		}

	}

	// Liste vide si le noeud n'est pas dans le QuadTree
	else
		return listeNoeuds;
}