////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.h
/// @author DGI
/// @date 2006-12-15
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
	/// Cette classe implante l'interface de projection d�finie par la
	/// classe de base Projection et ajoute certaines fonctionnalit�es
	/// sp�cifiques � la projection perspective, comme le zoom autour d'un
	/// point en particulier et le zoom �lastique.
	///
	/// @author Martin Bisson
	/// @date 2006-12-15
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


		/// Zoom in, c'est-�-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-�-dire un rapetissement.
		virtual void zoomerOut();
		/// Modification de la cl�ture.
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

		void tiltLeft(double deplacement);
		void tiltRight(double deplacement);


		/// Obtenir la dimension de la fen�tre virtuelle
		virtual inline glm::ivec2 obtenirDimensionFenetreVirtuelle() const;

	private:
		double ratio_;
		double fovy_;
		double near_;
		double far_;
	};
};


#endif // _UTILITAIRE_PROJECTIONPERSPECTIVE_H__