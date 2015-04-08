//////////////////////////////////////////////////////////////////////////////
/// @file Lumiere.h
/// @author The Ballers
/// @date 2015-03-27
/// @version 1.0 
///
/// @ingroup Eclairage
//////////////////////////////////////////////////////////////////////////////

#ifndef __ECLAIRAGE_LUMIERE_H__
#define __ECLAIRAGE_LUMIERE_H__

#define GL_GLEXT_PROTOTYPES 1
#include "GL/glew.h"
#include <GL/gl.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

////////////////////////////////////////////////////////////////////////////////
///
/// @class Lumiere
/// @brief TODO PHIL
///
/// @author The ballers
/// @date 2015-04-02
////////////////////////////////////////////////////////////////////////////////
class Lumiere{

public:
	/// Constructeur
	Lumiere(GLenum handle_);

	/// Passer les attributs au serveur OpenGL
	void definir();

	/// Assignations de la couleur ambiante
	inline void setAmbientColor(glm::fvec4 ambientColor);

	/// Assignations de la couleur diffuse
	inline void setDiffuseColor(glm::fvec4 diffuseColor);
	/// Assignations de la couleur speculaire
	inline void setSpecularColor(glm::fvec4 specularColor);
	/// Assignations de la position
	inline void setPosition(glm::fvec4 position);
	/// Assignations de la direction
	inline void setDirection(glm::fvec4 direction);
	/// Assignations de l'exposant du spot
	inline void setExponent(float exponent);
	/// Assignations de l'angle d'ouverture du spot
	inline void setCutoffAngle(float cutoffAngle);
	/// Assignations des coefficients d'attenuation
	inline void setAttenuation(glm::fvec3 attenuation);

	/// Accesseur de la couleur ambiante
	inline const glm::fvec4& getAmbientColor() const;
	/// Accesseur de la couleur diffuse
	inline const glm::fvec4& getDiffuseColor() const;
	/// Accesseur de la couleur speculaire
	inline const glm::fvec4& getSpecularColor() const;
	/// Accesseur de la position
	inline const glm::fvec4& getPosition() const;
	/// Accesseur de la direction
	inline const glm::fvec4& getDirection() const;
	/// Accesseur de l'exposant du spot
	inline const float& getExponent() const;
	/// Accesseur de l'angle d'ouverture du spot
	inline const float& getCutoffAngle() const;
	/// Accesseur des coefficients d'attenuation
	inline const glm::fvec3& getAttenuation() const;

private:

	/// Poigee OpenGL 
	GLuint handle_;

	/// Couleurs de lumieres reflechie pour les differents modeles de reflection
	glm::fvec4	ambient_{ 1.0f, 1.0f, 1.0f, 1.0f };           // GL_AMBIENT
	glm::fvec4	diffuse_{ 1.0f, 1.0f, 1.0f, 1.0f };           // GL_DIFFUSE
	glm::fvec4	specular_{ 1.0f, 1.0f, 1.0f, 1.0f };          // GL_SPECULAR

	/// Position de la source de lumiere dans les coordonnees du modele
	glm::fvec4	position_{ 190.0f, -47.0f, 30.0f, 1.0 };       // GL_POSITION

	/// Direction de la lumiere
	glm::fvec4  direction_{ 1.0f, 0.0f, 1.0f, 1.0 };           // GL_SPOT_DIRECTION

	/// Exposant du spot (controle l'attenuation proche des bords du spot
	GLfloat spotExponent_{ 0.0f };			                  // GL_SPOT_EXPONENT

	/// Angle d'ouverture du spot
	GLfloat spotCutoffAngle_{ 30.0f };                        // GL_SPOT_CUTOFF 

	/// Coefficients Constant, Lineaire, Quadratiques (respectivement) d'attenuation en fonction de la distance
	glm::fvec3 attenuation_{ 1.0, 0.0, 0.0 };                 // GL_CONSTANT_ATTENUATION, // GL_LINEAR_ATTENUATION, // GL_QUADRATIC_ATTENUATION

};



////////////////////////////////////////////////////////////////////////
///
/// @fn inline void Lumiere::setAmbientColor(glm::fvec4 ambientColor)  
/// 
/// @brief Cette fonction assigne la couleur ambiante de la lumiere
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void Lumiere::setAmbientColor(glm::fvec4 ambientColor)
{
	ambient_ = ambientColor;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void Lumiere::setDiffuseColor(glm::fvec4 diffuseColor) 
/// 
/// @brief Cette fonction assigne la couleur diffuse de la lumiere
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void Lumiere::setDiffuseColor(glm::fvec4 diffuseColor)
{
	diffuse_ = diffuseColor;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void Lumiere::setSpecularColor(glm::fvec4 specularColor)	
/// 
/// @brief Cette fonction assigne la couleur speculaire de la lumiere
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void Lumiere::setSpecularColor(glm::fvec4 specularColor)
{
	specular_ = specularColor;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void Lumiere::setPosition(glm::fvec4 position)
/// 
/// @brief Cette fonction assigne la possition de la source lumineuse
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void Lumiere::setPosition(glm::fvec4 position)
{
	position_ = position;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void Lumiere::setDirection(glm::fvec4 direction)  
/// 
/// @brief Cette fonction assigne la direction du cone de lumiere 
/// pour un spot et la direction de la lumiere pour une lumiere 
/// directionnelle
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void Lumiere::setDirection(glm::fvec4 direction)
{
	direction_ = direction;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void Lumiere::setExponent( float exponent )
/// 
/// @brief Cette fonction assinge l'exposant utilise dans le calcul
/// d'attenuation proche des bords du cpot             
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void Lumiere::setExponent(float exponent)
{
	spotExponent_ = exponent;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void Lumiere::setCutoffAngle( float cutoffAngle )     
/// 
/// @brief Cette fonction assigne l'angle d'ouverture du spot. 
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void Lumiere::setCutoffAngle(float cutoffAngle)
{
	if (cutoffAngle > 0.1) spotCutoffAngle_ = cutoffAngle;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void Lumiere::setAttenuation( glm::fvec3 attenuation )  
/// 
/// @brief Cette fonction assigne les coefficients d'attenuation 
/// utilises dans le calcul de l'atenuation due a la distance.
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void Lumiere::setAttenuation(glm::fvec3 attenuation)
{
	attenuation_ = attenuation;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::fvec4& Lumiere::getAmbientColor() const  
///
/// @brief Cette fonction retourne la couleur ambiante de la lumiere
///
/// @return Couleur ambiante de la lumiere
///
////////////////////////////////////////////////////////////////////////
inline const glm::fvec4& Lumiere::getAmbientColor() const
{
	return ambient_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::fvec4& Lumiere::getDiffuseColor() const 
///
/// @brief Cette fonction retourne la couleur diffuse de la lumiere
///
/// @return 
///
////////////////////////////////////////////////////////////////////////
inline const glm::fvec4& Lumiere::getDiffuseColor() const
{
	return diffuse_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::fvec4& Lumiere::getSpecularColor() const 
///
/// @brief Cette fonction retourne la couleur speculaire de la lumiere
///
/// @return Couleur speculaire de la lumiere
///
////////////////////////////////////////////////////////////////////////
inline const glm::fvec4& Lumiere::getSpecularColor() const
{
	return specular_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::fvec4& Lumiere::getPosition() const
///
/// @brief Cette fonction retourne la position de la source de lumiere
/// 
/// @return Position de la source de lumiere
///
////////////////////////////////////////////////////////////////////////
inline const glm::fvec4& Lumiere::getPosition() const
{
	return position_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::fvec4& Lumiere::getDirection() const
///
/// @brief Cette fonction retourne direction du cone de lumiere pour un 
/// spot et la direction de la lumiere pour une lumiere directionnelle
///
/// @return direction
///
////////////////////////////////////////////////////////////////////////
inline const glm::fvec4& Lumiere::getDirection() const
{
	return direction_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const float& Lumiere::getExponent() const
///
/// @brief Cette fonction retourne l'exposant du spot
///
/// @return Exposant du spot
///
////////////////////////////////////////////////////////////////////////
inline const float& Lumiere::getExponent() const
{
	return spotExponent_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const float& Lumiere::getCutoffAngle() const 
///
/// @brief Cette fonction retourne l'angle d'ouverture du spot
///
/// @return Angle d'ouverture
///
////////////////////////////////////////////////////////////////////////
inline const float& Lumiere::getCutoffAngle() const
{
	return spotCutoffAngle_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::fvec3& Lumiere::getAttenuation() const
///
/// @brief Cette fonction retourne un fvec3 avec contenant les coefficients
/// de l'attenuation due a la distance
///
/// @return Coefficients d'attenuation
///
////////////////////////////////////////////////////////////////////////
inline const glm::fvec3& Lumiere::getAttenuation() const
{
	return attenuation_;
}

#endif //  __ECLAIRAGE_LUMIERE_H__
