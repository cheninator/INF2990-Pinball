////////////////////////////////////////////////////////////////////////////////////
/// @file VuePerspective.cpp
/// @author The Ballers
/// @date 2015-04-01
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "Utilitaire.h"
#include "VuePerspective.h"
#include <iostream>

namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VuePerspective::VuePerspective(const Camera& camera, int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une vue perspective.  Ne fait que créer les objets
	/// Projection et Camera correspondant.
	///
	/// @param[in] camera        : Caméra à utiliser au départ pour cette vue.
	/// @param[in] xMinCloture   : coordonnée minimale en @a x de la clôture.
	/// @param[in] xMaxCloture   : coordonnée maximale en @a x de la clôture.
	/// @param[in] yMinCloture   : coordonnée minimale en @a y de la clôture.
	/// @param[in] yMaxCloture   : coordonnée maximale en @a y de la clôture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arrière (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arrière (en @a z).
	/// @param[in] ratio         : Le rapport d'aspect du plan avant du volume de visualisation 
	/// @param[in] fovy          : L'angle de visionnement de la projection perspective
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	VuePerspective::VuePerspective(Camera const& camera, ProjectionPerspective const& projection) :
		Vue{ camera },
		projection_{ projection }
	{
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn const ProjectionPerspective& VuePerspective::obtenirProjection() const
	///
	/// Retourne la projection perspective associée à cette vue.
	///
	/// @return La projection perspective associée à cette vue.
	///
	////////////////////////////////////////////////////////////////////////
	const ProjectionPerspective& VuePerspective::obtenirProjection() const
	{
		return projection_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::appliquerProjection() const
	///
	/// Applique la matrice de projection correspondant à cette vue.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::appliquerProjection() const
	{
		projection_.mettreAJourProjection();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::appliquerCamera() const
	///
	/// Applique la matrice correspondant à cette vue selon la position de
	/// la caméra (eventuellement un gluLookAt()).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::appliquerCamera() const
	{
		camera_.positionnerOrbite();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// d'un redimensionnement de la fenêtre.
	///
	/// @param[in]  coinMin : Coin contenant les coordonnées minimales de la
	///                       nouvelle clôture.
	/// @param[in]  coinMax : Coin contenant les coordonnées maximales de la
	///                       nouvelle clôture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		projection_.redimensionnerFenetre(coinMin, coinMax);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incrément de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::zoomerIn()
	{
		
		double nouvelleDistance =camera_.obtenirDistance() /  projection_.obtenirIncrementZoom();
		if (nouvelleDistance >= projection_.obtenirZoomInMax())
			camera_.assignerDistance(nouvelleDistance);
		
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incrément de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::zoomerOut()
	{
		/*Obtenir l'incrément de zoom à partir de la projection plus tard*/

		double nouvelleDistance = camera_.obtenirDistance() * projection_.obtenirIncrementZoom();
		if (nouvelleDistance <= projection_.obtenirZoomOutMax())
			camera_.assignerDistance(nouvelleDistance);

	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::zoomerInElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom in élastique.
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonnées du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonnées du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::zoomerInElastique(const glm::ivec2&,
		const glm::ivec2&)
	{
		/// Not implemented for the moment was : projection_.zoomerIn(coin1, coin2)
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::zoomerOutElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom out élastique.
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonnées du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonnées du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::zoomerOutElastique(const glm::ivec2&,
		const glm::ivec2&)
	{
		/// Not implemented for the moment was : projection_.zoomerOut(coin1, coin2)
	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::deplacerZ(double deplacement)
	///
	/// Ne fait rien, car se déplacer dans l'axe de la profondeur n'a pas
	/// vraiment de signification avec une vue perspective.
	///
	/// @param[in]  deplacement : Déplacement selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::deplacerZ(double)
	{
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::rotaterXY(double rotationX, double rotationY)
	///
	/// Permet de faire une rotation de la caméra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'élévation.
	///
	/// Une rotation de 100% correspondant à 360 degrés en X (angle de
	/// rotation) ou 180 degrés en Y (angle d'élévation).
	///
	/// @param[in]  rotationX : Rotation en pourcentage de la largeur.
	/// @param[in]  rotationY : Rotation en pourcentage de la hauteur.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::rotaterXY(double rotationX, double rotationY)
	{
		// On veut une rotation entre 0.0 et 1.0. COmme déjà expliqué, 
		// les valeurs habituelles de rotationX et rotationY sont 
		// de 10.0 avec le signe correspondant
		rotationX /= 100.0; rotationY /= 100.0;
		camera_.orbiterXY(rotationX * 360, rotationY * 180, false);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::rotaterXY(const glm::ivec2& rotation)
	///
	/// Permet de faire une rotation de la caméra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'élévation.
	///
	/// Un déplacement de la taille de la fenêtre correspond à 100%.
	///
	/// @param[in]  rotation : Rotation en coordonnées de clotûre (pixels).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::rotaterXY(const glm::ivec2& rotation)
	{
		const glm::ivec2 dimensions{ projection_.obtenirDimensionCloture() };
		rotaterXY(rotation[0] / (double)dimensions[0],
			rotation[1] / (double)dimensions[1]);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::rotaterZ(double rotation)
	///
	/// Ne fait rien, car tourner autour de l'axe de la profondeur
	/// correspondrait à un rouli et n'est pas souhaitable pour cette vue.
	///
	/// @param[in]  rotation : Rotation selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::rotaterZ(double)
	{
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::centrerSurPoint(glm::ivec2 pointCentre)
	///
	/// Modifie les bornes de la fenêtre virtuelle afin de se placer sur le
	/// point passé en paramètre.
	///
	/// @param[in]  rotation : Le point milieu désiré de la nouvelle fenêtre
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::centrerSurPoint(glm::ivec2)
	{
		//projection_.centrerSurPoint(pointCentre);
	}

	void VuePerspective::deplacerXY(double deplacementX, double deplacementY)
	{
		camera_.orbiterXY(deplacementX, deplacementY, false);
	}

	void VuePerspective::deplacerXY(const glm::ivec2& deplacement)
	{
		camera_.orbiterXY(deplacement.x, deplacement.y, false);
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
