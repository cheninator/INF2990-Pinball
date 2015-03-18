////////////////////////////////////////////////
/// @file QuadTree.cpp
/// @author The Ballers
/// @date 2015-02-24
///
/// @ingroup QuadTree
////////////////////////////////////////////////

#include "QuadTree.h"
#include <algorithm>


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

	double centreX = ((superieurDroit_.x - inferieurGauche_.x) / 2.0) + inferieurGauche_.x;
	double centreY = ((superieurDroit_.y - inferieurGauche_.y) / 2.0) + inferieurGauche_.y;

	nordEst_ = new QuadTree(niveauCourant_ + 1, { centreX, centreY, 0 }, superieurDroit_);
	nordOuest_ = new QuadTree(niveauCourant_ + 1, { inferieurGauche_.x, centreY, 0 }, { centreX, superieurDroit_.y, 0 });
	sudEst_ = new QuadTree(niveauCourant_ + 1, { centreX, inferieurGauche_.y, 0 }, { superieurDroit_.x, centreY, 0 });
	sudOuest_ = new QuadTree(niveauCourant_ + 1, inferieurGauche_, { centreX, centreY, 0 });

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
		nordEst_ = nullptr;

		delete nordOuest_;
		nordOuest_ = nullptr;

		delete sudEst_;
		sudEst_ = nullptr;

		delete sudOuest_;
		sudOuest_ = nullptr;
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

	std::vector<glm::dvec3> points;

	// Obtenir les 4 points de la boite englobante
	points = noeud->obtenirVecteursEnglobants();

	// Le cas ou ce n'est pas un objet qui a une forme circulaire
	if (points.size() > 1)
	{
		for (int i = 0; i < points.size(); i++)
			points[i] += noeud->obtenirPositionRelative();

		// Si un des points n'est pas dans le QuadTree, retourner false
		for (unsigned int i = 0; i < points.size(); i++)
		{
			if (!(estDansQuadTree(points[i], quad)))
				return false;
		}

		// Le point est dans le QuadTree
		return true;
	}

	// Le cas ou c'est un objet qui a une forme circulaire
	else if (points.size() == 1)
	{
		glm::dvec3 position = noeud->obtenirPositionRelative();
		double rayon = points[0].x;

		glm::dvec3 nord = { position.x, position.y + rayon, position.z };
		glm::dvec3 sud = { position.x, position.y - rayon, position.z };
		glm::dvec3 est = { position.x + rayon, position.y, position.z };
		glm::dvec3 ouest = { position.x - rayon, position.y, position.z };

		if (estDansQuadTree(nord, quad) && estDansQuadTree(sud, quad)
			&& estDansQuadTree(est, quad) && estDansQuadTree(ouest, quad))
			return true;

		else
			return false;
	}

	else
		return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool QuadTree::estDansQuadTree(glm::dvec3 points, QuadTree* quad)
///
/// Cette méthode permet de savoir si un point est complétement contenu dans
///	un QuadTree.
///
/// @param[in] points : le point à vérifier
/// @param[in] quad : le quad dans lequel on veut insérer
///
/// @return True lorsque le point est dans le QuadTree passé en paramètre. False autrement
///
////////////////////////////////////////////////////////////////////////
bool QuadTree::estDansQuadTree(glm::dvec3 points, QuadTree* quad) const
{
	if ( (points.x > quad->inferieurGauche_.x) && (points.x < quad->superieurDroit_.x)
	  && (points.y > quad->inferieurGauche_.y) && (points.y < quad->superieurDroit_.y))
		return true;

	else
		return false;
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
	if (!noeud->estAffiche())
		return false;

	objets_.push_back(noeud); // On insere dans objets_ et si MAX_CAPACITY est atteint, on essai de replacer les trucs.

	if (objets_.size() < MAX_CAPACITY && niveauCourant_ < MAX_LEVEL)
		return true;
	else
	{
		// Si les enfants du quad n'existent pas, les creer.
		if (nordEst_ == nullptr)
			divide();

		// Redistribuer les objets dans les quads enfants si possible
		for (auto it = objets_.begin(); it != objets_.end();)
		{
			// Les noeuds à mettre dans les sous quads, c'est les noeuds pour lesquels obtenirQuadrant != this 
			// car si obtenirQuandrant == this, ça veut dire qu'on est obligés de mettre le noeud dans le quad courant même si capacity est dépassé
			// donc c<est pas la peine d'essayer, de plus, a cause de la recursivite, re-essayer pourrait nous mettre dasn 
			// une situation de stack overflow.
			if (obtenirQuadrant(*it) != this)
			{
				// Insérer dans le bon sous-quad
				obtenirQuadrant(*it)->insert(*it);
				// le noeud va peut-être se ramasser dans un sous-sous-quad par récursivité
				// Enlever du quad courant.
				it = objets_.erase(it);
			}
			else
				++it;
		} // En passant, j'ai lu que ceci ^^^^ est la façon standart d'effacer des éléments d'une std::list pendant qu'on itère dessus.

		return true;
	}
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
std::list<NoeudAbstrait*> QuadTree::retrieve(NoeudAbstrait* noeud)
{
	std::list<NoeudAbstrait*> listeNoeuds;

	// Si le noeud en question est dans plusieurs des sous-quad tree, on doit tout retourner.
	if (obtenirQuadrant(noeud) == this)
	{
		return obtenirContenu();
	}

	if (estDansQuadTree(noeud, this))
	{
		for (auto iter = objets_.begin(); iter != objets_.end(); iter++)
			listeNoeuds.push_back(*iter);
	}

	if (nordEst_ != nullptr)
	{
		// Ajouter les du sous-quad qui contient le noeud.
		std::list<NoeudAbstrait*> objets = obtenirQuadrant(noeud)->retrieve(noeud);

		for (auto iter = objets.begin(); iter != objets.end(); iter++)
			listeNoeuds.push_back(*iter);
	}
	// Liste vide si le noeud n'est pas dans le QuadTree
	return listeNoeuds;
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
bool QuadTree::remove(NoeudAbstrait* noeud)
{
	if (noeud == nullptr)
	{
		rafraichir();
		return false;
	}

	if (estDansQuadTree(noeud, this))
	{
		std::list<NoeudAbstrait*>::iterator iter;

		// On vérifie s'il est dans un sous QuadTree
		if (obtenirQuadrant(noeud) != this)
		{
			obtenirQuadrant(noeud)->remove(noeud);
			return true;
		}

		else
		{
			objets_.remove(noeud);
			return true;
		}
	}

	else
		return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<NoeudAbstrait*> QuadTree::retrieve(NoeudAbstrait* noeud)
///
////////////////////////////////////////////////////////////////////////
void QuadTree::rafraichir()
{
	std::list<NoeudAbstrait*>::iterator iter = objets_.begin();
	bool suspect = false;

	for (; iter != objets_.end() && !suspect; iter++)
	{
		if (*iter == nullptr)
			suspect = true;
	}

	if (suspect)
	{
		objets_.erase(iter);
		return;
	}


	if (nordEst_ != nullptr)
	{
		nordEst_->rafraichir();
		nordOuest_->rafraichir();
		sudEst_->rafraichir();
		sudOuest_->rafraichir();
	}

}


std::list<NoeudAbstrait*> QuadTree::obtenirContenu()
{
	std::list<NoeudAbstrait*> listeNoeuds = objets_;

	if (nordEst_ != nullptr)
	{
		std::list<NoeudAbstrait*> nordEstTemp = nordEst_->obtenirContenu();
		std::list<NoeudAbstrait*> nordOuestTemp = nordOuest_->obtenirContenu();
		std::list<NoeudAbstrait*> sudEstTemp = sudEst_->obtenirContenu();
		std::list<NoeudAbstrait*> sudOuestTemp = sudOuest_->obtenirContenu();
		
		for (auto it = nordEstTemp.begin(); it != nordEstTemp.end(); it++)
			listeNoeuds.push_back(*it);
		for (auto it = nordOuestTemp.begin(); it != nordOuestTemp.end(); it++)
			listeNoeuds.push_back(*it);
		for (auto it = sudEstTemp.begin(); it != sudEstTemp.end(); it++)
			listeNoeuds.push_back(*it);
		for (auto it = sudOuestTemp.begin(); it != sudOuestTemp.end(); it++)
			listeNoeuds.push_back(*it);
	}

	return listeNoeuds;
}