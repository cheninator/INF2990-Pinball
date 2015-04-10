///////////////////////////////////////////////////////////////////////////
/// @file NoeudCouvercle.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudCouvercle.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"

# define deplacementCouvercle (abs(SingletonGlobal::obtenirInstance()->obtenirBoiteTable().coinMax.x - SingletonGlobal::obtenirInstance()->obtenirBoiteTable().coinMin.x) - MARGE_NOEUD_COUVERCLE)
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCouvercle::NoeudCouvercle(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCouvercle::NoeudCouvercle(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	assignerSelection(false);
	selectionnable_ = false;
	modifiable_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCouvercle::~NoeudCouvercle()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCouvercle::~NoeudCouvercle()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCouvercle::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCouvercle::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	//glPushAttrib(GL_ALL_ATTRIB_BITS);

	//NoeudAbstrait::appliquerAfficher();
	glStencilFunc(GL_ALWAYS, 0, -1);
	liste_->dessiner();
	//glPopAttrib();
	glPopMatrix();
	// Restauration de la matrice.
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCouvercle::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCouvercle::animer(float temps)
{
	// On anime les enfants
	for (NoeudAbstrait * enfant : enfants_) {
		enfant->animer(temps);
	}

	// Si on as pas besoin de s'animer, alors en quite
	if (!animer_)
		return;

	glm::dvec3 v1, v2, v3, v4;
	obtenirVecteursBoite(v1, v2, v3, v4);

	glm::dvec3 v5, v6, v7, v8;
	obtenirBoiteModele(v5, v6, v7, v8);


	const double HAUTEUR_ORIGINALE = 30.0;
	const double DEMIE_LARGEUR = abs(v5.x - v3.x) / 2.0;
	// Tant que on as pas deplacer de la largeur de la table, on continue a se deplacer
	if (positionRelative_.x > -deplacementCouvercle + TRANSLATE_X_NOEUD_TABLE) {
		// On se deplace en prenant en compte le temps de deplacement
		positionRelative_.x -= temps * (deplacementCouvercle / TEMPS_ANIMATION_NOEUD_COUVERCLE);
		// Maintenir la hauteur du cote droit du couvercle.
		positionRelative_.z = HAUTEUR_ORIGINALE + sin(utilitaire::DEG_TO_RAD(rotation_.y))*DEMIE_LARGEUR;
		// On tourne sur soit en meme temps
		rotation_.y -= INCLINAISON_NOEUD_COUVERCLE / (TEMPS_ANIMATION_NOEUD_COUVERCLE / temps);
	}
	else
		// On arrete de se deplacer
		animer_ = false;


	// On calcule a boite englobante (prenant en compte les rotations


	// On calcule la hauteur de la table
	// float translateZ = SingletonGlobal::obtenirInstance()->obtenirBoiteTable().coinMin.z;
	// On se deplace pour que notre coin superieur gauche soit a la meme hauteur que la table
	// positionRelative_.z = translateZ - v1.z; // Ici devrais etre la boite tenant compte des rotations en z
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool bool NoeudCouvercle::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudCouvercle::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCouvercle::obtenirVecteursBoite(glm::dvec3 &v1, glm::dvec3 &v2, glm::dvec3 &v3, glm::dvec3 &v4)
///
/// Cette fonction obtient les vecteurs de la boite.
///
/// @param[out] v1 : Vecteur 1.
/// @param[out] v2 : Vecteur 2.
/// @param[out] v3 : Vecteur 3.
/// @param[out] v4 : Vecteur 4.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudCouvercle::obtenirVecteursBoite(glm::dvec3 &v1, glm::dvec3 &v2, glm::dvec3 &v3, glm::dvec3 &v4)
{
	//initialiser les vecteurs
	v1 = boite_.coinMin;
	v2.x = boite_.coinMin.x;
	v2.y = boite_.coinMax.y;
	v3 = boite_.coinMax;
	v4.x = boite_.coinMax.x;
	v4.y = boite_.coinMin.y;

	glm::dmat3 echelle = glm::dmat3{ glm::dvec3{ scale_.x, 0, 0.0 },
		glm::dvec3{ 0, scale_.y , 0.0f },
		glm::dvec3{ 0.0, 0.0, scale_.z } };	//TODO something for the z

	//mise a l'echelle des vecteurs
	v1 = echelle * v1;
	v2 = echelle * v2;
	v3 = echelle * v3;
	v4 = echelle * v4;

	//calcul matrice de rotation
	double angleEnRadian = -rotation_[2] * utilitaire::PI_180;
	glm::dmat3 transform =	glm::dmat3{ glm::dvec3{ cos(angleEnRadian), -sin(angleEnRadian),	0.0 },
										glm::dvec3{ sin(angleEnRadian), cos(angleEnRadian),		0.0f },
										glm::dvec3{			0.0,				0.0,			1.0 } };

	//calcul matrice de rotation
	angleEnRadian = -rotation_[1] * utilitaire::PI_180;
	glm::dmat3 transformY = glm::dmat3{	glm::dvec3{ cos(angleEnRadian),		0.0f,	sin(angleEnRadian)	},
										glm::dvec3{			0.0f,			1.0,			0.0f		},
										glm::dvec3{ -sin(angleEnRadian),	0.0,	cos(angleEnRadian)	} };

	//applique la rotation aux vecteurs
	v1 = transformY*transform * v1;
	v2 = transformY*transform * v2;
	v3 = transformY*transform * v3;
	v4 = transformY*transform * v4;
}