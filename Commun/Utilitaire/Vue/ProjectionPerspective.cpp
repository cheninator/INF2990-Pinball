#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "ProjectionPerspective.h"

#include <iostream>

namespace vue {

	ProjectionPerspective::ProjectionPerspective(int xMinCloture, int xMaxCloture,
		int yMinCloture, int yMaxCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double ratio, double fovy,
		double Znear, double Zfar) :
		Projection{ xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, true },
		ratio_(ratio), fovy_(fovy),
		near_(Znear), far_(Zfar)
	{
		appliquer();
	}

	void ProjectionPerspective::appliquer() const
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, 1.6, near_, far_);
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