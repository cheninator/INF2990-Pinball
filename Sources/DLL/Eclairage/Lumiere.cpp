#include "Lumiere.h"
#include <cassert>
#include <iostream>

Lumiere::Lumiere(GLuint handle)
{
	assert(GL_LIGHT1 <= handle && handle <= GL_LIGHT7);
	handle_ = handle;

	ambient_ = glm::fvec4{ 0.0f, 1.0f, 1.0f, 1.0f };
	diffuse_ = glm::fvec4{ 1.0f, 0.0f, 1.0f, 1.0f };
	specular_ = glm::fvec4{ 1.0f, 1.0f, 0.0f, 1.0f };

	spotPosition_ = glm::fvec3{ 50.0f, -47.0f, 30.0f };
	spotDirection_ = glm::fvec3{ 0.5f, .0f, -1.0f };

	spotExponent_ = 1.0f;			               // GL_SPOT_EXPONENT
	spotCutoffAngle_ = 15.0f;                    // GL_SPOT_CUTOFF 
	constantAttenuation_ = 1.0f;              // GL_CONSTANT_ATTENUATION
	linearAttenuation_ = 0.0f;              // GL_LINEAR_ATTENUATION
	quadraticAttenuation_ = 0.0f;
}


void Lumiere::definir()
{
	// vec4
	glLightfv(handle_, GL_AMBIENT, glm::value_ptr(ambient_));
	glLightfv(handle_, GL_DIFFUSE, glm::value_ptr(diffuse_));
	glLightfv(handle_, GL_SPECULAR, glm::value_ptr(specular_));

	// vec3
	glLightfv(handle_, GL_POSITION, glm::value_ptr(spotPosition_));
	glLightfv(handle_, GL_SPOT_DIRECTION, glm::value_ptr(spotDirection_));

	// Floats
	glLightf(handle_, GL_SPOT_EXPONENT, spotExponent_);
	glLightf(handle_, GL_SPOT_CUTOFF, spotCutoffAngle_);
	glLightf(handle_, GL_CONSTANT_ATTENUATION, constantAttenuation_);
	glLightf(handle_, GL_LINEAR_ATTENUATION, linearAttenuation_);
	glLightf(handle_, GL_QUADRATIC_ATTENUATION, quadraticAttenuation_);


}

void Lumiere::enable()
{
	std::cout << "Lumiere a la position ( " << spotPosition_.x << " , " << spotPosition_.y << " , " << spotPosition_.z << " )." << std::endl;
	glEnable(handle_);

}