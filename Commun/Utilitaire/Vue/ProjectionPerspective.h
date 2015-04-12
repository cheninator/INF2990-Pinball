////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.h
/// @author The Ballers
/// @date 2015-04-01
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_PROJECTIONPERSPECTIVE_H__
#define __UTILITAIRE_PROJECTIONPERSPECTIVE_H__


#include "Projection.h"

namespace vue {

	////////////////////////////////////////////////////////////////////////
	/// @class ProjectionPerspective
	/// @brief Classe implantant une projection perspective.
	///
	/// Cette classe implante l'interface de projection définie par la
	/// classe de base Projection et ajoute certaines fonctionnalitées
	/// spécifiques à la projection perspective, comme le zoom autour d'un
	/// point en particulier.
	///
	////////////////////////////////////////////////////////////////////////
	class ProjectionPerspective : public Projection
	{

	public:
		/// Constructeur.
		ProjectionPerspective(double xMinCloture, double xMaxCloture,
			double yMinCloture, double yMaxCloture,
			double zAvant, double zArriere,
			double zoomInMax, double zoomOutMax,
			double incrementZoom,
			double ratio, double fovy
			);


		/// Zoom in, c'est-à-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-à-dire un rapetissement.
		virtual void zoomerOut();
		/// Modification de la clôture.
		virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
			const glm::ivec2& coinMax);
		/// Application de la projection.
		virtual void appliquer() const;
		/// Obtenir la valeur minimale du zoom
		double obtenirZoomOutMax() const;
		/// Obtenir la valeur maximale du zoom
		double obtenirZoomInMax() const;
		/// Obtenir le facteur de zoom
		double obtenirIncrementZoom() const;
		
		/// Obtenir la dimension de la fenêtre virtuelle
		virtual inline glm::dvec2 obtenirDimensionFenetreVirtuelle() const;
		/// Obtenir les coordonnées de la fenêtre virtuelle
		virtual inline void obtenirCoordornneesFenetreVirtuelle(
			double& xMin, double& xMax, double& yMin, double& yMax
			) const;
	private:
		/// Le rapport d'aspect du plan avant de la projection perspective
		double ratio_;
		/// L'angle de visionnement de la projection perspective
		double fovy_;
	};
};


#endif // _UTILITAIRE_PROJECTIONPERSPECTIVE_H__