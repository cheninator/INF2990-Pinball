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

class Lumiere{

public:

	Lumiere(GLenum handle_);

	void definir();
	void enable();
	void disable();

	// TODO ajouter get, set,
	inline void setAmbientColor(glm::fvec4 ambientColor);
	inline void setDiffuseColor(glm::fvec4 diffuseColor);
	inline void setSpecurlarColor(glm::fvec4 specularColor);
	inline void setPosition(glm::fvec4 position);
	inline void setDirection(glm::fvec4 direction);

	inline void setExponent( float exponent );
	inline void setCutoffAngle( float cutoffAngle );
	inline void setAttenuation( glm::fvec3 attenuation );

	inline const glm::fvec4& getAmbientColor() const;
	inline const glm::fvec4& getDiffuseColor() const;
	inline const glm::fvec4& getSpecularColor() const;
	inline const glm::fvec4& getPosition() const;
	inline const glm::fvec4& getDirection() const;

	inline const float& getExponent() const;
	inline const float& getCutoffAngle() const;
	inline const glm::fvec3& getAttenuation() const;

private:
	GLuint handle_;

	glm::fvec4 ambient_{ 1.0f, 1.0f, 1.0f, 1.0f },    // GL_AMBIENT
		diffuse_{ 1.0f, 1.0f, 1.0f, 1.0f },           // GL_DIFFUSE
		specular_{ 1.0f, 1.0f, 1.0f, 1.0f };          // GL_SPECULAR

	glm::fvec3 spotPosition_{ 190.0f, -47.0f, 30.0f }, // GL_POSITION
		spotDirection_{ 1.0f, 0.0f, 1.0f };           // GL_SPOT_DIRECTION

	GLfloat spotExponent_{ 0.0f },			               // GL_SPOT_EXPONENT
		spotCutoffAngle_{ 30.0f };                   // GL_SPOT_CUTOFF 
	glm::fvec3 attenuation_{ 1.0, 0.0, 0.0 };               // GL_CONSTANT_ATTENUATION, GL_LINEAR_ATTENUATION, GL_QUADRATIC_ATTENUATION

};



	// TODO ajouter get, set,
	inline void Lumiere::setAmbientColor(glm::fvec4 ambientColor);
		{ ambient_ = ambientColor; }
	inline void Lumiere::setDiffuseColor(glm::fvec4 diffuseColor);
		{ diffuse_ = diffuseColor; }
	inline void Lumiere::setSpecurlarColor(glm::fvec4 specularColor);
		{ specular_ = specularColor; }
	inline void Lumiere::setPosition(glm::fvec4 position);
		{ position_ = position; }
	inline void Lumiere::setDirection(glm::fvec4 direction);
		{ direction_ = direction; }
	inline void Lumiere::setExponent( float exponent );
		{ spotExponent_ = exponent; }
	inline void Lumiere::setCutoffAngle( float cutoffAngle );
		{ spotCutoffAngle_ = cutoffAngle; }
	inline void Lumiere::setAttenuation( glm::fvec3 attenuation );
		{ attenuation_ = attenuation; }


	inline const glm::fvec4& Lumiere::getAmbientColor() const;
		{ return ambient_; }
	inline const glm::fvec4& Lumiere::getDiffuseColor() const;
		{ return diffuse_; }
	inline const glm::fvec4& Lumiere::getSpecularColor() const;
		{ return specular_; }
	inline const glm::fvec4& Lumiere::getPosition() const;
		{ return position_; }
	inline const glm::fvec4& Lumiere::getDirection() const;
		{ return direction_; }
	inline const float& getExponent() const;
		{ return spotExponent_; }
	inline const float& getCutoffAngle() const;
		{ return spotCutoffAngle_; }
	inline const glm::fvec3& getAttenuation() const;
		{ return attenuation_; }

#endif //  __ECLAIRAGE_LUMIERE_H__
