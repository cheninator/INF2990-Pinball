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

private:
	GLuint handle_;

	glm::fvec4 ambient_{ 1.0f, 1.0f, 1.0f, 1.0f },    // GL_AMBIENT
		diffuse_{ 1.0f, 1.0f, 1.0f, 1.0f },           // GL_DIFFUSE
		specular_{ 1.0f, 1.0f, 1.0f, 1.0f };          // GL_SPECULAR

	glm::fvec3 spotPosition_{ 190.0f, -47.0f, 30.0f }, // GL_POSITION
		spotDirection_{ 1.0f, 0.0f, 1.0f };           // GL_SPOT_DIRECTION

	GLfloat spotExponent_{ 0.0f },			               // GL_SPOT_EXPONENT
		spotCutoffAngle_{ 30.0f },                     // GL_SPOT_CUTOFF 
		constantAttenuation_{ 1.0f },	               // GL_CONSTANT_ATTENUATION
		linearAttenuation_{ 0.0f },	               // GL_LINEAR_ATTENUATION
		quadraticAttenuation_{ 0.0f };               // GL_QUADRATIC_ATTENUATION

};


#endif //  __ECLAIRAGE_LUMIERE_H__
