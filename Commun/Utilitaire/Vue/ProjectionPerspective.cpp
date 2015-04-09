///////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionPerspective.cpp
/// @author The Ballers
/// @date 2015-04-01
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
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
		gluPerspective(fovy_, ratio_, zAvant_, zArriere_);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspective::zoomerIn()
	///
	/// Pour un vue perspective, cette fonctionnalité n'est pas contrôlée
	/// par la projection.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionPerspective::zoomerIn()
	{
		return;
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspective::zoomerOut()
	///
	/// Pour un vue perspective, cette fonctionnalité n'est pas contrôlée
	/// par la projection.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionPerspective::zoomerOut()
	{
		return;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline glm::ivec2 ProjectionPerspective::obtenirDimensionFenetreVirtuelle() const
	///
	/// Cette fonction ne devrait pas exister, pour l'instant il faut
	/// l'implanter pour éviter des erreurs de méthodes virtuelles pure
	/// non implémentées.
	/// Cette fonction retourne les dimensions de la fenêtre virtuelle.
	/// 
	/// @return Les dimensions de la fenêtre virtuellle
	///
	////////////////////////////////////////////////////////////////////////
	inline glm::ivec2 ProjectionPerspective::obtenirDimensionFenetreVirtuelle() const
	{
		return glm::ivec2(-1); // À changer
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionPerspective::redimensionnerFenetre()const glm::ivec2& coinMin , const glm::ivec2& coinMax)
	///
	/// Cette fonction fait repositionne le Viewport pour que la caméra orbite
	/// soit correctement placée avec les bons attributs lors d'un 
	/// redimensionnement de fenêtre
	///
	/// @param[in]  coinMin : Coin contenant les coordonnées minimales de la
	///                       nouvelle clôture
	/// @param[in]  coinMax : Coin contenant les coordonnées maximales de la
	///                       nouvelle clôture
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionPerspective::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		
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

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double ProjectionPerspective::obtenirZoomOutMax() const
	///
	/// Cette fonction retourne la distance maximale à laquelle la caméra 
	/// devrait pouvoir se positionner.
	///
	/// @return La valeur du zoomOutMax
	///
	////////////////////////////////////////////////////////////////////////
	double ProjectionPerspective::obtenirZoomOutMax() const
	{
		return zoomOutMax_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double ProjectionPerspective::obtenirZoomOutMin() const
	///
	/// Cette fonction retourne la distance minimale à laquelle la caméra 
	/// devrait pouvoir se positionner.
	///
	/// @return La valeur du zoomInMax
	///
	////////////////////////////////////////////////////////////////////////
	double ProjectionPerspective::obtenirZoomInMax() const
	{
		return zoomInMax_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double ProjectionPerspective::obtenirZoomOutMax() const
	///
	/// Cette fonction retourne le facteur de zoom que la projection établie.
	/// 
	/// @remark : Cette fonction s'assure de ne pas pouvoir renvoyer une 
	/// \remark négative. De plus, il ne s'agit pas d'un incrément, mais bien
	/// \remark d'un facteur qui est multiplié.
	///
	/// @return La valeur de l'incrément de zoom.
	///
	////////////////////////////////////////////////////////////////////////
	double ProjectionPerspective::obtenirIncrementZoom() const
	{
		// S'assurer de ne pas renvoyer une valeur nulle
		return (incrementZoom_ != 0.0 ? incrementZoom_ : 1);
	}
};