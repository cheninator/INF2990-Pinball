///////////////////////////////////////////////////////////////////////////////
/// @file Camera.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <GL/glu.h>
#include "Utilitaire.h"
#include "Camera.h"
#include <iostream>
#include "../Utilitaire.h"
//#include "../../Sources/DLL/Application/FacadeModele.h"
//#include "../../Sources/DLL/Text/ControleurTexte.h"

namespace vue {


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn Camera::Camera(const glm::dvec3& position, const glm::dvec3& pointVise, const glm::dvec3& directionHautCamera, const glm::dvec3& directionHautMonde)
	///
	/// Constructeur de la cam�ra � partir des coordonn�es cart�siennes.
	///
	/// @param[in]  position            : position de la cam�ra.
	/// @param[in]  pointVise           : point vis�.
	/// @param[in]  directionHautCamera : direction du haut de la cam�ra.
	/// @param[in]  directionHautMonde  : direction du haut du monde de la
	///                                   cam�ra.
	///
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////////
	Camera::Camera(const glm::dvec3& position,
		const glm::dvec3& pointVise,
		const glm::dvec3& directionHautCamera,
		const glm::dvec3& directionHautMonde,
		float angleTheta,
		float anglePhi
		)
		: position_{ position },
		pointVise_{ pointVise },
		directionHaut_{ directionHautCamera },
		directionHautMonde_{ directionHautMonde },
		theta_{angleTheta},
		phi_{anglePhi}
	{
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::deplacerXY( double deplacementX, double deplacementY )
	///
	/// D�place la cam�ra dans le plan perpendiculaire � la direction vis�e
	///
	/// @param[in]  deplacementX : D�placement sur l'axe horizontal du plan de
	///                            la cam�ra.
	/// @param[in]  deplacementY : D�placement sur l'axe vertical du plan de la
	///                            cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::deplacerXY(double deplacementX, double deplacementY)
	{
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::deplacerZ( double deplacement, bool bougePointVise )
	///
	/// D�place la cam�ra dans l'axe de la direction vis�e.
	///
	/// @param[in]  deplacement    : D�placement sur l'axe de la direction vis�e
	/// @param[in]  bougePointVise : Si vrai, le point de vis� est �galement
	///                              d�plac�.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::deplacerZ(double deplacement, bool bougePointVise)
	{
		/*TODO : Tenir du bougePointVise*/
		this->position_.z += deplacement;
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::tournerXY( double rotationX, double rotationY, bool empecheInversion )
	///
	/// Rotation de la cam�ra autour de sa position (et donc d�placement du
	/// point vis� en gardant la position fixe.
	///
	/// @param[in] rotationX        : Modification de l'angle de rotation du
	///                               point vis� par rapport � la position.
	/// @param[in] rotationY        : Modification de l'angle d'�l�vation du
	///                               point vis� par rapport � la position.
	/// @param[in] empecheInversion : Si vrai, la rotation n'est pas effectu�e
	///                               si elle am�nerait une inversion de la
	///                               cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::tournerXY(double rotationX,
		double rotationY,
		bool   empecheInversion //=true
		)
	{
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::orbiterXY( double rotationX, double rotationY, bool empecheInversion )
	///
	/// Rotation de la cam�ra autour de son point de vis� (et donc d�placement
	/// de la position en gardant le point de vis� fixe.
	///
	/// @param[in]  rotationX        : Modification de l'angle de rotation de la
	///                                position par rapport au point de vis�.
	/// @param[in]  rotationY        : Modification de l'angle d'�l�vation de la
	///                                position par rapport au point de vis�.
	/// @param[in]  empecheInversion : Si vrai, la rotation n'est pas effectu�
	///                                si elle am�nerait une inversion de la
	///                                cam�ra.
	///
	///  @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::orbiterXY(double rotationX,
		double rotationY,
		bool   empecheInversion //=true
		)
	{
		if (empecheInversion)
			return;

		/* Les angles doivent �tre en radian*/
		float dist = glm::distance(position_, pointVise_);
		//float deltaTheta = utilitaire::DEG_TO_RAD(rotationX);
		//float deltaPhi   = utilitaire::DEG_TO_RAD(rotationY);
		float deltaTheta = utilitaire::DEG_TO_RAD(1.0);
		float deltaPhi = utilitaire::DEG_TO_RAD(1.0);
		/*std::string ancienTexte;
		std::string informationAngle = "Phi | Theta" + std::to_string(theta_)
			+ " | " + std::to_string(phi_) + " \n";
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->updateText(ancienTexte, );*/
		std::cout << "Phi | Theta" + std::to_string(theta_)
			+ " | " + std::to_string(phi_) + " \n";
		std::cout << "Distance : " << dist << std::endl;

		theta_ += deltaPhi;
		phi_ += deltaPhi;

		position_.x = dist * sin(phi_) * sin(theta_);
		position_.y = dist * cos(phi_);
		position_.z = dist * sin(phi_) * cos(theta_);

		positionner();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::positionner() const
	///
	/// Positionne la cam�ra dans la sc�ne � l'aide de gluLookAt().
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Camera::positionner() const
	{
		gluLookAt(position_[0], position_[1], position_[2],
			pointVise_[0], pointVise_[1], pointVise_[2],
			directionHaut_[0], directionHaut_[1], directionHaut_[2]);
	}


}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
