#include <windows.h>
#include <GL/gl.h>
#include "ProjectionPerspective.h"

#include <iostream>

namespace vue {

	ProjectionPerspective::ProjectionPerspective(int xMinCloture, int xMaxCloture,
		int yMinCloture, int yMaxCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double left, double right,
		double bottom, double top,
		double Znear, double Zfar) :
		Projection{ xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, true },
		left_(left), right_(right),
		bottom_(bottom), top_(top),
		near_(Znear), far_(Zfar)
	{

	}

	void ProjectionPerspective::appliquer() const
	{
		glFrustum(left_, right_,
			bottom_, top_,
			near_, far_);
	}

	void ProjectionPerspective::zoomerIn()
	{
		return;
	}

	void ProjectionPerspective::zoomerOut()
	{
		return;
	}

};