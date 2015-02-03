////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <GL/gl.h>
#include "ProjectionOrtho.h"

#include <iostream>

namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant,  double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une projection orthogonale.  Ne fait qu'assigner les
	/// variables membres et ajuste ensuite le rapport d'aspect.
	///
	/// @param[in] xMinCloture   : coordonnée minimale en @a x de la clôture.
	/// @param[in] xMaxCloture   : coordonnée maximale en @a x de la clôture.
	/// @param[in] yMinCloture   : coordonnée minimale en @a y de la clôture.
	/// @param[in] yMaxCloture   : coordonnée maximale en @a y de la clôture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arrière (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arrière (en @a z).
	/// @param[in] xMinFenetre   : coordonnée minimale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] xMaxFenetre   : coordonnée maximale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] yMinFenetre   : coordonnée minimale en @a y de la fenêtre
	///                            virtuelle.
	/// @param[in] yMaxFenetre   : coordonnée maximale en @a y de la fenêtre
	///                            virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture,
		int yMinCloture, int yMaxCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double xMinFenetre, double xMaxFenetre,
		double yMinFenetre, double yMaxFenetre) :
		Projection{ xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, false },
		xMinFenetre_{ xMinFenetre },
		xMaxFenetre_{ xMaxFenetre },
		yMinFenetre_{ yMinFenetre },
		yMaxFenetre_{ yMaxFenetre }
	{
		ajusterRapportAspect();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incrément de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn()
	{
		double xMaxCopie = xMaxFenetre_;
		double xMinCopie = xMinFenetre_;
		double yMaxCopie = yMaxFenetre_;
		double yMinCopie = yMinFenetre_;

		// Formules qui proviennent de la résolution d'un système d'équation
		// Bless you, based Wolfram Alpha !
		xMaxFenetre_ = ((xMaxCopie * incrementZoom_) + xMaxCopie + xMinCopie * incrementZoom_ - xMinCopie) / (2 * incrementZoom_);
		xMinFenetre_ = (xMaxCopie * (incrementZoom_ - 1) + xMinCopie * (incrementZoom_ + 1.0)) / (2 * incrementZoom_);

		yMaxFenetre_ = ((yMaxCopie * incrementZoom_) + yMaxCopie + yMinCopie * incrementZoom_ - yMinCopie) / (2 * incrementZoom_);;
		yMinFenetre_ = (yMaxCopie * (incrementZoom_ - 1) + yMinCopie * (incrementZoom_ + 1.0)) / (2 * incrementZoom_);

		std::cout << "Taille de la fenetre virtuelle : " <<
			(xMaxFenetre_ - xMinFenetre_) << "x" << (yMaxFenetre_ - yMinFenetre_) << std::endl;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incrément de zoom.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrtho::zoomerOut()
	{
		double augmentationX = (incrementZoom_ - 1.0) * 0.5 * (xMaxFenetre_ - xMinFenetre_);
		double augmentationY = (incrementZoom_ - 1.0) * 0.5 * (yMaxFenetre_ - yMinFenetre_);
		
		xMinFenetre_ -= augmentationX;
		xMaxFenetre_ += augmentationX;

		yMinFenetre_ -= augmentationY;
		yMaxFenetre_ += augmentationY;
		
		std::cout << "Taille de la fenetre virtuelle : " <<
			(xMaxFenetre_ - xMinFenetre_) << "x" << (yMaxFenetre_ - yMinFenetre_) << std::endl;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// d'un redimensionnement de la fenêtre.
	///
	/// L'agrandissement de la fenêtre virtuelle est proportionnel à
	/// l'agrandissement de la clotûre afin que les objets gardent la même
	/// grandeur apparente lorsque la fenêtre est redimensionnée.
	///
	/// @param[in]  coinMin : Coin contenant les coordonnées minimales de la
	///                       nouvelle clôture
	/// @param[in]  coinMax : Coin contenant les coordonnées maximales de la
	///                       nouvelle clôture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		
		// coinMax contient les dimensions de la nouvelle fenêtree, car coinMin
		// est essentiellement tout le temps à zéro. on établi le facteur qu'il
		// faut élargir le viewport vers la gauche et la droite en fonction des
		// valeurs précédentes: 
		double xScaleFactor = coinMax[0] * 1.0 / ((xMaxCloture_ - xMinCloture_) * 1.0);
		double yScaleFactor = coinMax[1] * 1.0 / ((yMaxCloture_ - yMinCloture_) * 1.0);

		std::cout << "xMin | xMax Cloture : " << xMinCloture_ << " | " << xMaxCloture_ << "\n";
		std::cout << "yMin | yMax Cloture : " << yMinCloture_ << " | " << yMaxCloture_ << "\n";
		
		std::cout << "xMin | xMax Fenetre: " << xMinFenetre_ << " | " << xMaxFenetre_ << "\n";
		std::cout << "yMin | yMax Fenetre: " << yMinFenetre_ << " | " << yMaxFenetre_ << "\n";
		
		// Affichage de débug :
		if (xScaleFactor != 1 || yScaleFactor != 1 )
		std::cout << "xScaleFactor : " << xScaleFactor << std::endl 
			<< "yScaleFactor :" << yScaleFactor << std::endl;

		// On fait en sorte que le rendu soit de la bonne taille en multipliant
		// par le facteur de scale. Puisque la fenêtre virtuelle peut avoir des
		// coordonnées négatives, il faut s'assurer que les calculs mathématiques
		// s'appliquent dans tous les cas. On teste premièrement si on agrandit 
		// ou rapetisse la fenêtre virtuelle : 
		if (xScaleFactor > 1)
			xMaxFenetre_ += (xScaleFactor - 1.0) * (xMaxFenetre_ - xMinFenetre_);
		else if (xScaleFactor < 1)
			xMaxFenetre_ -= (1.0 - xScaleFactor) * (xMaxFenetre_ - xMinFenetre_);
		
		if (yScaleFactor > 1)
			yMinFenetre_ -= (yScaleFactor - 1.0) * (yMaxFenetre_ - yMinFenetre_);
		else if (yScaleFactor < 1)
			yMinFenetre_ += (1.0 - yScaleFactor) * (yMaxFenetre_ - yMinFenetre_);
		//  le (int)( /* ... */  sert a cast en int pour eviter les warnings
		// On sauvegarde la nouvelle taille de la clotûre : 
		if (xScaleFactor > 1)
			xMaxCloture_ += (xScaleFactor - 1.0) * (xMaxCloture_ - xMinCloture_);
		else if (xScaleFactor < 1)
			xMaxCloture_ -= (1.0 - xScaleFactor) * (xMaxCloture_ - xMinCloture_);

		if (yScaleFactor > 1)
			yMaxCloture_ += (yScaleFactor - 1.0) * (yMaxCloture_ - yMinCloture_);
		else if (yScaleFactor < 1)
			yMaxCloture_ -= (1.0 - yScaleFactor) * (yMaxCloture_ - yMinCloture_);

		std::cout << "xMin | xMax Cloture : " << xMinCloture_ << " | " << xMaxCloture_ << "\n";
		std::cout << "yMin | yMax Cloture : " << yMinCloture_ << " | " << yMaxCloture_ << "\n";
		
		std::cout << "xMin | xMax Fenetre: " << xMinFenetre_ << " | " << xMaxFenetre_ << "\n";
		std::cout << "yMin | yMax Fenetre: " << yMinFenetre_ << " | " << yMaxFenetre_ << "\n";
		// On update le rendu
		appliquer();
		mettreAJourCloture();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::appliquer() const
	///
	/// Cette fonction permet d'appliquer la fenêtre virtuelle en appelant les
	/// fonctions d'OpenGL selon le type de projection et les propriétés de la
	/// fenêtre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::appliquer() const
	{
		glOrtho(xMinFenetre_, xMaxFenetre_,
			yMinFenetre_, yMaxFenetre_,
			zAvant_, zArriere_);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom in sur un rectangle déterminé par deux coins.
	/// Ainsi la région délimitée par le rectangle deviendra la fenêtre
	/// virtuelle.  La fenêtre résultante est ajustée pour respecter le rapport
	/// d'aspect.
	/// 
	/// Les coordonnées reçues sont en coordonnées OpenGL (coord. de Fenêtre)
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxième coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn(const glm::ivec2& coin1, const glm::ivec2& coin2)
	{
		// À IMPLANTER.

		// 1) Déterminer quel side est le plus grand (rapport aspect)
		// Si le rapport d'aspect est plus grand que 1 la longueur en x est plus grand que celle en y
		double rapportAspectCourant = (xMaxFenetre_ - xMinFenetre_) / (yMaxFenetre_ - yMinFenetre_);
		double rapportAspectSelection = (abs(coin2.x - coin1.x) / abs(coin2.y - coin1.y));

		double pointMilieuX = (xMaxFenetre_ + xMinFenetre_) / 2.0;
		double pointMilieuY = (yMaxFenetre_ + yMinFenetre_) / 2.0;

		double facteurMultiplication = 0.0;
		double deltaX = 0.0;
		double deltaY = 0.0;

		// On doit voir quel est le ratio le plus grand de la sélection :
		if (rapportAspectSelection > 1) // x est plus long que y
		{
			// On trouve le ratio de la fenêtre courante 
			facteurMultiplication = abs(xMaxFenetre_ - xMinFenetre_) / abs(coin2.x - coin1.x);
		}
		else // y est plus long que x
		{
			facteurMultiplication = abs(yMaxFenetre_ - yMinFenetre_) / abs(coin2.y - coin1.y);
		}
		// Le côté est donc facteurMultiplication x taille de la sélection
		// On doit ajouter une partie en x positive et négative
		deltaX = (facteurMultiplication - 1.0) * abs(coin2.x - coin1.x) / 2.0;
		deltaY = (facteurMultiplication - 1.0) * abs(coin2.y - coin1.y) / 2.0;

		xMinFenetre_ += deltaX;
		xMaxFenetre_ -= deltaX;

		yMinFenetre_ += deltaY;
		yMaxFenetre_ -= deltaY;
		// La fenêtre étant de la bonne taille, on se centre sur le bon point.
		centrerSurPoint(glm::ivec2(pointMilieuX, pointMilieuY));
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom out sur un rectangle délimité par deux coins.
	/// Ainsi la fenêtre virtuelle avant le zoom sera placée à l'interieur de
	/// la région délimité par le rectangle.  La fenêtre résultante est ajustée
	/// pour respecter le rapport d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxième coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerOut(const glm::ivec2& coin1, const glm::ivec2& coin2)
	{
		// À IMPLANTER.
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater( double deplacementX, double deplacementY )
	///
	/// Permet de déplacer la fenêtre virtuelle en @a x et en @a y.  Les
	/// déplacement doivent être exprimés en proportion de la fenêtre virtuelle.
	///
	/// @param[in]  deplacementX : le déplacement en @a x.
	/// @param[in]  deplacementY : le déplacement en @a y.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater(double deplacementX, double deplacementY)
	{
		// À IMPLANTER.
		std::cout << "Facteurs de deplacement : " <<
			"X : " << deplacementX << " Y: " << deplacementY << std::endl;
		double xTailleCourante = xMaxFenetre_ - xMinFenetre_;
		double yTailleCourante = yMaxFenetre_ - yMinFenetre_;

		double deltaX = deplacementX * xTailleCourante / 100.0;
		double deltaY = deplacementY * yTailleCourante / 100.0;

		xMaxFenetre_ += deltaX;
		xMinFenetre_ += deltaX;

		yMaxFenetre_ += deltaY;
		yMinFenetre_ += deltaY;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater(const glm::ivec2& deplacement)
	///
	/// Permet de translater la fenêtre virtuelle en fonction d'un déplacement
	/// en coordonnées de clôture.
	///
	/// @param[in]  deplacement : Le déplacement en coordonnées de clôture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater(const glm::ivec2& deplacement)
	{
		// À IMPLANTER.
		// Il faut calculer la variation que notre déplacement
		// en coordonnées de cloture engendre en coordonnées virtuelles
		//
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::centrerSurPoint( const glm::ivec2& pointCentre )
	///
	/// Permet de centrer la fenêtre virtuelle sur un point de l'écran. Le
	/// point de l'écran est convertit en coordonnées virtuelles et il devient
	/// le centre de la fenêtre virtuelle.
	///
	/// @param[in]  pointCentre : Le point sur lequel on doit centrer.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::centrerSurPoint(const glm::ivec2& pointCentre)
	{
		// À IMPLANTER.
		// N.B: Puisque le fonction existante 'translater' suppose que les 
		// déplacements sont faites à partir des coordonnées de clôtures,
		// je fais le translate ici.
		glm::ivec2 currentPoint((xMinFenetre_ + xMaxFenetre_) / 2.0, (yMinFenetre_ + yMaxFenetre_) / 2.0);
		glm::ivec2 deplacement(pointCentre - currentPoint);

		// Déplacement (en supposant que le vecteur est bon)
		xMinFenetre_ += deplacement.x;
		xMaxFenetre_ += deplacement.x;

		yMinFenetre_ += deplacement.y;
		yMaxFenetre_ += deplacement.y;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspect()
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// de la clôture de façon à ce que le rapport d'aspect soit respecté.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspect()
	{
		// À IMPLANTER.
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
