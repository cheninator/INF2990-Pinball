#include "Lumiere.h"
#include <cassert>
#include <iostream>

Lumiere::Lumiere(GLuint handle)
{
	assert(GL_LIGHT1 <= handle && handle <= GL_LIGHT7);
	handle_ = handle;

	// Couleurs qui font pas de sens mais sont utiles pour tester
	ambient_ = glm::fvec4{ 1.0f, 0.0f, 0.0f, 1.0f };
	diffuse_ = glm::fvec4{ 0.0f, 1.0f, 0.0f, 1.0f };
	specular_ = glm::fvec4{ 0.0f, 0.0f, 1.0f, 1.0f };

	position_ = glm::fvec4{ 50.0f, -47.0f, 30.0f ,1.0};
	direction_ = glm::fvec4{ 0.5f, .0f, -1.0f, 1.0 };

	spotExponent_ = 1.0f;			               // GL_SPOT_EXPONENT
	spotCutoffAngle_ = 15.0f;                    // GL_SPOT_CUTOFF 
	attenuation_[0] = 1.0f;              // GL_CONSTANT_ATTENUATION
	attenuation_[1] = 0.0f;              // GL_LINEAR_ATTENUATION
	attenuation_[2] = 0.0f;
}


void Lumiere::definir()
{
	// vec4
	glLightfv(handle_, GL_AMBIENT, glm::value_ptr(ambient_));
	glLightfv(handle_, GL_DIFFUSE, glm::value_ptr(diffuse_));
	glLightfv(handle_, GL_SPECULAR, glm::value_ptr(specular_));

	// vec3
	glLightfv(handle_, GL_POSITION, glm::value_ptr(position_));
	glLightfv(handle_, GL_SPOT_DIRECTION, glm::value_ptr(direction_));

	// Floats
	glLightf(handle_, GL_SPOT_EXPONENT, spotExponent_);
	glLightf(handle_, GL_SPOT_CUTOFF, spotCutoffAngle_);
	glLightf(handle_, GL_CONSTANT_ATTENUATION, attenuation_[0]);
	glLightf(handle_, GL_LINEAR_ATTENUATION, attenuation_[1]);
	glLightf(handle_, GL_QUADRATIC_ATTENUATION, attenuation_[2]);


}

void Lumiere::enable()
{
	glEnable(handle_);

}