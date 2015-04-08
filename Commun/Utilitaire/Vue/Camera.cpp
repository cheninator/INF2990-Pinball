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
	/// Constructeur de la caméra à partir des coordonnées cartésiennes.
	///
	/// @param[in]  position            : position de la caméra.
	/// @param[in]  pointVise           : point visé.
	/// @param[in]  directionHautCamera : direction du haut de la caméra.
	/// @param[in]  directionHautMonde  : direction du haut du monde de la
	///                                   caméra.
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
		dist_ = 100.0;
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::deplacerXY( double deplacementX, double deplacementY )
	///
	/// Déplace la caméra dans le plan perpendiculaire à la direction visée
	///
	/// @param[in]  deplacementX : Déplacement sur l'axe horizontal du plan de
	///                            la caméra.
	/// @param[in]  deplacementY : Déplacement sur l'axe vertical du plan de la
	///                            caméra.
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
	/// Déplace la caméra dans l'axe de la direction visée.
	///
	/// @param[in]  deplacement    : Déplacement sur l'axe de la direction visée
	/// @param[in]  bougePointVise : Si vrai, le point de visé est également
	///                              déplacé.
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
	/// Rotation de la caméra autour de sa position (et donc déplacement du
	/// point visé en gardant la position fixe.
	///
	/// @param[in] rotationX        : Modification de l'angle de rotation du
	///                               point visé par rapport à la position.
	/// @param[in] rotationY        : Modification de l'angle d'élévation du
	///                               point visé par rapport à la position.
	/// @param[in] empecheInversion : Si vrai, la rotation n'est pas effectuée
	///                               si elle amènerait une inversion de la
	///                               caméra.
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
	/// Rotation de la caméra autour de son point de visé (et donc déplacement
	/// de la position en gardant le point de visé fixe.
	///
	/// @param[in]  rotationX        : Modification de l'angle de rotation de la
	///                                position par rapport au point de visé.
	/// @param[in]  rotationY        : Modification de l'angle d'élévation de la
	///                                position par rapport au point de visé.
	/// @param[in]  empecheInversion : Si vrai, la rotation n'est pas effectué
	///                                si elle amènerait une inversion de la
	///                                caméra.
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
#if 0
		else if (phi_ + rotationY >= utilitaire::PI)  
		{
			std::cout << "Angle phi trop grand : on le remet à PI \n";
			phi_ = utilitaire::PI - 0.0001;	
		}
		else if (phi_ + rotationY <= 0.0)
		{
			std::cout << "Angle phi trop petit : on le remet à 0 \n";
			phi_ = 0.0001;
		}
#endif
		/* Les angles doivent être en radian*/
		float dist = glm::distance(position_, pointVise_);
		float deltaTheta = utilitaire::DEG_TO_RAD(rotationX);
		float deltaPhi   = utilitaire::DEG_TO_RAD(rotationY);
		/*std::string ancienTexte;
		std::string informationAngle = "Phi | Theta" + std::to_string(theta_)
			+ " | " + std::to_string(phi_) + " \n";
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->updateText(ancienTexte, );*/
		std::cout << "RECU --- deltaPhi | deltaTheta" + std::to_string(deltaPhi)
			+ " | " + std::to_string(deltaTheta) + " \n";
		std::cout << "Distance : " << dist << std::endl;

		// Assignation des nouveaux angles
		theta_ += deltaTheta;
		phi_ += deltaPhi;

		std::cout << "Nouveau Phi | Theta" + std::to_string(phi_)
			+ " | " + std::to_string(theta_) + " \n";

		// On calcule la bonne position en fonction des angles 
		calculerPositionOrbite();
		positionner();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::positionner() const
	///
	/// Positionne la caméra dans la scène à l'aide de gluLookAt().
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Camera::positionner() const
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(position_[0], position_[1], position_[2],
			pointVise_[0], pointVise_[1], pointVise_[2],
			directionHaut_[0], directionHaut_[1], directionHaut_[2]);
	}

	void Camera::calculerPositionOrbite()
	{
		//gluLookAt( dist*cos(theta)*sin(phi), dist*sin(theta)*sin(phi), dist*cos(phi),   <--- TP3 INF2705
		//gluLookAt( dist*sin(phi)*sin(theta), dist*cos(phi), dist*sin(phi)*cos(theta), 0, 1, 0, 0, 2, 0 ); <---TP4 INF2705
#if 1 /* Version du TP3*/
		position_.x = dist_ * sin(phi_) * cos(theta_);
		position_.y = dist_ * sin(phi_) * sin(theta_);
		position_.z = dist_ * cos(phi_);
#else /*Version du TP4*/
		position_.x = dist_ * sin(phi_) * sin(theta_);
		position_.y = dist_ * cos(phi_);
		position_.z = dist_ * sin(phi_) * cos(theta_);
#endif

	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
