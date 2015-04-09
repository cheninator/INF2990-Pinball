#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "ProjectionPerspective.h"

#include <iostream>

namespace vue {

	ProjectionPerspective::ProjectionPerspective(double xMinCloture, double xMaxCloture,
		double yMinCloture, double yMaxCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double ratio, double fovy) :
		Projection{ xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, true },
		ratio_(ratio), fovy_(fovy)
	{
		appliquer();
	}

	void ProjectionPerspective::appliquer() const
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, 1.6, zAvant_, zArriere_);
	}

	void ProjectionPerspective::zoomerIn()
	{
		return;
	}

	void ProjectionPerspective::zoomerOut()
	{
		return;
	}

	inline glm::ivec2 ProjectionPerspective::obtenirDimensionFenetreVirtuelle() const
	{
		return glm::ivec2(-1); // À changer
	}

	void ProjectionPerspective::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		std::cout << " Redimension de fenetre non implémenté \n";
		
		/* Portion qui provient de la projection orthographique*/

		// coinMax contient les dimensions de la nouvelle fenêtree, car coinMin
		// est essentiellement tout le temps à zéro. on établi le facteur qu'il
		// faut élargir le viewport vers la gauche et la droite en fonction des
		// valeurs précédentes: 
		double xScaleFactor = coinMax[0] * 1.0 / ((xMaxCloture_ - xMinCloture_) * 1.0);
		double yScaleFactor = coinMax[1] * 1.0 / ((yMaxCloture_ - yMinCloture_) * 1.0);

		// On sauvegarde la nouvelle taille de la clotûre : 
		if (xScaleFactor > 1)
			xMaxCloture_ += (xScaleFactor - 1.0) * (xMaxCloture_ - xMinCloture_);
		else if (xScaleFactor < 1)
			xMaxCloture_ -= (1.0 - xScaleFactor) * (xMaxCloture_ - xMinCloture_);

		if (yScaleFactor > 1)
			yMaxCloture_ += (yScaleFactor - 1.0) * (yMaxCloture_ - yMinCloture_);
		else if (yScaleFactor < 1)
			yMaxCloture_ -= (1.0 - yScaleFactor) * (yMaxCloture_ - yMinCloture_);

		/* Calculer le nouvel angle*/
		double nouveauRatio = abs(coinMax.x - coinMin.x) * 1.0 / abs(coinMax.y - coinMin.y);
		ratio_ = nouveauRatio;

		// On update le rendu
		appliquer();
		mettreAJourCloture();
	}

	double ProjectionPerspective::obtenirZoomOutMax() const
	{
		return zoomOutMax_;
	}

	double ProjectionPerspective::obtenirZoomInMax() const
	{
		return zoomInMax_;
	}

	double ProjectionPerspective::obtenirIncrementZoom() const
	{
		// S'assurer de ne pas renvoyer une valeur nulle
		return (incrementZoom_ != 0.0 ? incrementZoom_ : 1);
	}
};