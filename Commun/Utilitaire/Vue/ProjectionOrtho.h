////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.h
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_PROJECTIONORTHO_H__
#define __UTILITAIRE_PROJECTIONORTHO_H__


#include "Projection.h"

enum DirectionZoom { IN_ = 1, OUT_= -1 };
namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class ProjectionOrtho
	/// @brief Classe implantant une projection orthogonale.
	///
	/// Cette classe implante l'interface de projection définie par la
	/// classe de base Projection et ajoute certaines fonctionnalitées
	/// spécifiques à la projection orthogonale, comme le zoom autour d'un
	/// point en particulier et le zoom élastique.
	///
	/// @author Martin Bisson
	/// @date 2006-12-15
	////////////////////////////////////////////////////////////////////////
	class ProjectionOrtho : public Projection
	{
	public:
		/// Constructeur.
		ProjectionOrtho(double xMinCloture, double xMaxCloture,
			double yMinCloture, double yMaxCloture,
			double zAvant, double zArriere,
			double zoomInMax, double zoomOutMax,
			double incrementZoom,
			double xMinFenetre, double xMaxFenetre,
			double yMinFenetre, double yMaxFenetre);

		/// Assignation par copie non-nécessaire dans le contexte
		ProjectionOrtho& operator=(ProjectionOrtho const&) = delete;

		/// Zoom in, c'est-à-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-à-dire un rapetissement.
		virtual void zoomerOut();
		/// Modification de la clôture.
		virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
			const glm::ivec2& coinMax);
		/// Application de la projection.
		virtual void appliquer() const;


		/// Zoom out élastique, sur un rectangle.
		void zoomerOut(const glm::dvec2& coin1, const glm::dvec2& coin2);
		/// Zoom in élatique, sur un rectangle.
		void zoomerIn(const glm::ivec2& coin1, const glm::ivec2& coin2);

		/// Translater la fenêtre virtuelle d'un pourcentage en @a X ou en @a Y
		void translater(double deplacementX, double deplacementY);
		/// Translater la fenêtre virtuelle d'un vecteur
		void translater(const glm::ivec2& deplacement);
		/// Centrer la fenêtre virtuelle sur un point
		void centrerSurPoint(const glm::dvec2& pointCentre);

		/// Obtenir les coordonnées de la fenêtre virtuelle.
		virtual inline void obtenirCoordornneesFenetreVirtuelle(
			double& xMin, double& xMax, double& yMin, double& yMax
			) const;

		/// Obtenir la dimension de la fenêtre virtuelle
		virtual inline glm::dvec2 obtenirDimensionFenetreVirtuelle() const;
		
		virtual void conserverRapportAspect();

	private:

		/// Vérifie que la translation ne dépasse pas les bordures maximales du centre du jeu
		bool translationDepasseBordure(double xBorneMin, double xBorneMax, double yBorneMin, double yBorneMax);

		/// Décide la direction de correction en fonction du zoom.
		void ajusterRapportAspect(DirectionZoom dir);

		/// Ajuste la fenêtre en modifiant la portée verticale
		void ajusterRapportAspectY(double rapportAspect, DirectionZoom dir);

		/// Ajuste la fenêtre en modifiant la portée horizontale
		void ajusterRapportAspectX(double rapportAspect, DirectionZoom dir);

		/// Vérifie si les nouvelles bornes de la fanêtre viole les bornes des facteurs de zoom
		bool zoomInValide(double xBorneMin, double xBorneMax, double yBorneMin, double yBorneMax);

		/// Vérifie si les nouvelles bornes de la fanêtre viole les bornes des facteurs de zoom
		bool zoomOutValide(double xBorneMin, double xBorneMax, double yBorneMin, double yBorneMax);

		/// Borne inférieure en X de la fenêtre virtuelle.
		double xMinFenetre_;
		/// Borne supérieure en X de la fenêtre virtuelle.
		double xMaxFenetre_;
		/// Borne inférieure en Y de la fenêtre virtuelle.
		double yMinFenetre_;
		/// Borne supérieure en Y de la fenêtre virtuelle.
		double yMaxFenetre_;

	};




	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void ProjectionOrtho::obtenirCoordonneesFenetreVirtuelle(double& xMin, double& xMax, double& yMin, double& yMax) const
	///
	/// Cette fonction retourne les coordonnées de la fenêtre virtuelle
	/// associée à cette projection.
	///
	/// @param[out]  xMin : La variable qui contiendra l'abcsisse minimale.
	/// @param[out]  xMax : La variable qui contiendra l'abcsisse maximale.
	/// @param[out]  yMin : La variable qui contiendra l'ordonnée minimale.
	/// @param[out]  yMax : La variable qui contiendra l'ordonnée maximale.
	///
	/// @return Les coordonnées de la fenêtre virtuelle.
	///
	////////////////////////////////////////////////////////////////////////
	inline void ProjectionOrtho::obtenirCoordornneesFenetreVirtuelle(
		double& xMin, double& xMax, double& yMin, double& yMax
		) const
	{
		xMin = xMinFenetre_;
		xMax = xMaxFenetre_;
		yMin = yMinFenetre_;
		yMax = yMaxFenetre_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline glm::dvec2 ProjectionOrtho::obtenirDimensionFenetreVirtuelle() const
	///
	/// Cette fonction retourne les dimensions de la fenêtre virtuelle
	/// associée à cette projection orthographique.
	///
	/// @return Les dimensions de la fenêtre de virtuelle.
	///
	////////////////////////////////////////////////////////////////////////
	inline glm::dvec2 ProjectionOrtho::obtenirDimensionFenetreVirtuelle() const
	{
		return glm::dvec2{ xMaxFenetre_ - xMinFenetre_, yMaxFenetre_ - yMinFenetre_ };
	}
}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_PROJECTIONORTHO_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
