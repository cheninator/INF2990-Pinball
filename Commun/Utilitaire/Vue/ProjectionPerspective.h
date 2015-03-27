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
	/// Cette classe implante l'interface de projection définie par la
	/// classe de base Projection et ajoute certaines fonctionnalitées
	/// spécifiques à la projection perspective, comme le zoom autour d'un
	/// point en particulier et le zoom élastique.
	///
	/// @author Martin Bisson
	/// @date 2006-12-15
	////////////////////////////////////////////////////////////////////////
	class ProjectionPerspective : public Projection
	{

	public:
		/// Constructeur.
		ProjectionPerspective(int xMinCloture, int xMaxCloture,
			int yMinCloture, int yMaxCloture,
			double zAvant, double zArriere,
			double zoomInMax, double zoomOutMax,
			double incrementZoom,
			double left  , double right,
			double bottom, double top,
			double Znear , double Zfar);


		/// Zoom in, c'est-à-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-à-dire un rapetissement.
		virtual void zoomerOut();
		/// Modification de la clôture.
		virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
			const glm::ivec2& coinMax);
		/// Application de la projection.
		virtual void appliquer() const;

		void tiltLeft(double deplacement);
		void tiltRight(double deplacement);


		/// Obtenir la dimension de la fenêtre virtuelle
		virtual inline glm::ivec2 obtenirDimensionFenetreVirtuelle() const;

	private:
		double left_;
		double right_;
		double bottom_;
		double top_;
		double near_;
		double far_;
	};
};


#endif // _UTILITAIRE_PROJECTIONPERSPECTIVE_H__