//////////////////////////////////////////////////////////////////////////////
/// @file Lumiere.cpp
/// @author The Ballers
/// @date 2015-03-27
/// @version 1.0 
///
/// @ingroup Eclairage
//////////////////////////////////////////////////////////////////////////////


#include "Lumiere.h"
#include <cassert>
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn Lumiere::Lumiere(GLuint handle)
///
/// @brief Construit un objet Lumiere avec un handle OpenGL
///
/// @param[in] handle openGL assignee par le controleur de lumieres.
///
/// @remarks Doit être un handle entre GL_LIGHT1 et GL_LIGHT7
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
Lumiere::Lumiere(GLuint handle)
{
	assert(GL_LIGHT1 <= handle && handle <= GL_LIGHT7);
	handle_ = handle;

	ambient_ = glm::fvec4{ 1.0f, 1.0f, 1.0f, 1.0f };		// GL_AMBIENT
	diffuse_ = glm::fvec4{ 1.0f, 1.0f, 1.0f, 1.0f };		// GL_DIFFUSE
	specular_ = glm::fvec4{ 1.0f, 1.0f, 1.0f, 1.0f };		// GL_SPECULAR

	position_ = glm::fvec4{ 50.0f, -47.0f, 30.0f ,1.0};		// GL_SPOT_POSITION
	direction_ = glm::fvec4{ 0.5f, .0f, -1.0f, 1.0 };		// GL_SPOT_DIRECTION

	spotExponent_ = 1.0f;			// GL_SPOT_EXPONENT
	spotCutoffAngle_ = 30.0f;		// GL_SPOT_CUTOFF 
	attenuation_[0] = 1.0f;			// GL_CONSTANT_ATTENUATION
	attenuation_[1] = 0.0f;			// GL_LINEAR_ATTENUATION
	attenuation_[2] = 0.0f;			// GL_QUADRATI_ATTENUATION
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Lumiere::definir() 
/// 
/// @brief Envoi les attributs de la lumiere au serveur OpenGL.
/// 
/// @remark Les coordonnees sont multiplies automatiquement par la 
/// matrice de modelisation courrante.  On doit donc definir la lumiere
/// apres avoir defini la camera.
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
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

	
#if(0)
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(50.0f);
	glColor4f(1.0f, 1.0f, 0.7f, 1.0f);
	glBegin(GL_POINTS);
		glVertex3f(position_.x, position_.y, position_.z);
	glEnd();
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
#endif

}
