//////////////////////////////////////////////////////////////////////////////
/// @file VuePerspective.h
/// @author The Ballers
/// @date 2015-04-01
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VUEPERSPECTIVE_H__
#define __UTILITAIRE_VUEPERSPECTIVE_H__


#include "Vue.h"
#include "Camera.h"
#include "ProjectionPerspective.h"

namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class VuePerspective
	/// @brief Classe concrète de vue perspective.
	///
	/// Cette classe implante le comportement attendu d'une vue perspective.
	///
	////////////////////////////////////////////////////////////////////////
	class VuePerspective : public Vue
	{
	public:
		// Constructeur.
		VuePerspective(Camera const& camera, ProjectionPerspective const& projection);

		/// Obtention de la projection.
		virtual const ProjectionPerspective& obtenirProjection() const;
		/// Application de la projection.
		virtual void appliquerProjection() const;
		/// Application de la caméra.
		virtual void appliquerCamera() const;

		/// Modification de la clotûre.
		virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
			const glm::ivec2& coinMax);

		/// Centre la vue sur un point
		virtual void centrerSurPoint(glm::ivec2 pointCentre);
		/// Zoom in, c'est-à-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-à-dire un rapetissement.
		virtual void zoomerOut();
		/// Zoom in élastique.
		virtual void zoomerInElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2);
		/// Zoom out élastique.
		virtual void zoomerOutElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2);

		/// Déplacement dans le plan XY par rapport à la vue.
		virtual void deplacerXY(double deplacementX, double deplacementY);
		/// Déplacement dans le plan XY par rapport à la vue.
		virtual void deplacerXY(const glm::ivec2& deplacement);
		/// Déplacement selon l'axe des Z par rapport à la vue.
		virtual void deplacerZ(double deplacement);
		/// Rotation selon les axes des X et des Y par rapport à la vue.
		virtual void rotaterXY(double rotationX, double rotationY);
		/// Rotation selon les axes des X et des Y par rapport à la vue.
		virtual void rotaterXY(const glm::ivec2& rotation);
		/// Rotation selon l'axe des Z par rapport à la vue.
		virtual void rotaterZ(double rotation);


	private:
		/// Projection utilisée pour cette vue.
		ProjectionPerspective projection_;

	};


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_VUEPERSPECTIVE_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
