///////////////////////////////////////////////////////////////////////////
/// @file NoeudPaletteD.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudPaletteD.h"
#include "Utilitaire.h"
#include "NoeudBille.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include "../../Commun/Externe/glm/include/glm/gtx/Projection.hpp"


std::vector<glm::dvec3> NoeudPaletteD::boiteEnglobanteModele_{
	{ 36.92, 11.96, 0 },
	{ 54.41, 8.04, 0 },
	{ 60.05, 6.97, 0 },
	{ 62.18, 4.85, 0 },
	{ 61.93, 1.58, 0 },
	{ 59.65, -0.22, 0 },
	{ 51.23, 1.25, 0 },
	{ 44.03, 3.62, 0 },
	{ 37.66, 4.69, 0 },
	{ 30.71, 4.36, 0 },
	{ 24.74, 2.89, 0 },
	{ 12.48, -1.69, 0 },
	{ 6.19, -2.75, 0 },
	{ -0.27, -1.69, 0 },
	{ -3.78, 0.11, 0 },
	{ -9.26, 3.30, 0 },
	{ -5.09, 6.73, 0 },
	{ 1.12, 4.60, 0 },
	{ 11.09, 6.07, 0 },
	{ 24.91, 11.14, 0 },
	{ 32.92, 12.53, 0 }
};

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPaletteD::NoeudPaletteD(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPaletteD::NoeudPaletteD(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	ajustable_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPaletteD::~NoeudPaletteD()
///
/// Ce destructeur cllouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPaletteD::~NoeudPaletteD()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPaletteD::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteD::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du modele.
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	if (colorShift_)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	if (pause_) {
		glBlendFunc(GL_SRC_ALPHA, GL_ZERO); // Set The Blending Function For Translucency
		glEnable(GL_BLEND);
	}
	else if (impossible_)
		glColorMask(0, 1, 1, 1);
	else if (selectionne_) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
		if (twin_ != nullptr && twin_ != NULL)
			twin_->setTransparent(true);

	}
	else if (transparent_) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	else
		if (twin_ != nullptr && twin_ != NULL)
			twin_->setTransparent(false);
	if (twin_ != nullptr && twin_ != NULL)
		if (!selectionne_ && !twin_->estSelectionne())
			twin_->setTransparent(false);
	liste_->dessiner();
	glPopAttrib();
	// Restauration de la matrice.
	glPopMatrix();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPaletteD::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteD::animer(float temps)
{
	NoeudComposite::animer(temps);

	if (!animer_)
		return;

	switch (etatPalette_)
	{
		case ACTIVE:

		// TODO : Verifier que la rotation que je veux faire est possible,
		// si impossible, la palette est bloquee et doit tomber dans l'etat INACTIVE

			if (angleZOriginal_ - obtenirRotation().z < 60)
				assignerRotation(glm::dvec3{ 0, 0,- VITESSE_ANGULAIRE_PALETTE_ACTIVE * temps });
			
			break;

		case RETOUR:

			if (angleZOriginal_ - obtenirRotation().z > 0)
				assignerRotation(glm::dvec3{ 0, 0, VITESSE_ANGULAIRE_PALETTE_RETOUR * temps });
			else
			{
				assignerRotationHard(glm::dvec3{ rotation_.x, rotation_.y, angleZOriginal_ });
				etatPalette_ = INACTIVE;
			}

			break;

		case INACTIVE:

			break;
	}

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPaletteD::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudPaletteD::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPaletteD::accepterJoueurVirtuel(JoueurVirtuel* joueur)
///
///
/// Cette fonction permet d'accepter un joueur virtuel
///
/// @param[in] joueur : Prend un JoueurVirtuel
///
/// @return Reusite ou echec.
///
////////////////////////////////////////////////////////////////////////
bool NoeudPaletteD::accepterJoueurVirtuel(JoueurVirtuel* joueur)
{
	return joueur->traiter(this);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPaletteD::activer()
///
/// Cette fonction active l'animation qui fait monter les palettes. On en
/// profite pour sauvegarder l'angle intial des palettes quand la palette est inactive
/// 
/// @remark appelee quand la bonne touche est appuyee.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteD::activer()
{
	if (etatPalette_ == INACTIVE)
		angleZOriginal_ = obtenirRotation().z;

	etatPalette_ = ACTIVE;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPaletteD::desactiver()
///
/// Cette fonction active l'animation qui fait revenir les palettes.
///
/// @remark appelee quand la bonne touche est relachee
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteD::desactiver()
{
	if (etatPalette_ == INACTIVE)
		angleZOriginal_ = obtenirRotation().z;
	etatPalette_ = RETOUR;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPaletteD::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille)
///
/// Cette fonction effectue la réaction a la collision de la bille sur 
/// l'objet courant. Cette fonction est a reimplementer si on veut autre 
/// chose qu'un rebondissement ordinaire.
///
/// @return details contient l'information sur la collision de la bille avec *this.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteD::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float facteurRebond)
{
	if (1 && (etatPalette_ == ACTIVE) && fonctionDroitePaletteEnMouvement(bille) > 0)
	{
		glm::dvec3 positionPalette = obtenirPositionRelative();
		glm::dvec3 positionBille = bille->obtenirPositionRelative();
		positionPalette.z = 0.0; // Les positions utilisees ici doivent etre en 2D
		positionBille.z = 0.0; // Les positions utilisees ici doivent etre en 2D
		glm::dvec3 vecteur = positionBille - positionPalette;
		double distance = glm::length(vecteur);

		double angleEnRadian = rotation_[2] * utilitaire::PI_180;
		glm::dvec3 directionPalette = { cos(angleEnRadian), sin(angleEnRadian), 0 }; // Une palette pas tournee a un axe { 1, 0, 0}
		glm::dvec3 vecteurProjete = glm::proj(vecteur, directionPalette);
		glm::dvec3 vecteurNormal = vecteur - vecteurProjete;

		double distanceProjetee = glm::length(vecteurProjete);
		double distanceNormale = glm::length(vecteurNormal);
		double constanteMystere = 1;
		double deltaAngle = (9 * utilitaire::PI_180);
		double vitesseAngulaire = deltaAngle / 0.016; // 9 degres par 16 msec 


		glm::dvec3 vitesseInitiale = bille->obtenirVitesse();
		glm::dvec3 vitesseNormaleInitiale = glm::proj(vitesseInitiale, details.direction); // Necessaire pour connaitre la vitesse tangentielle.
		glm::dvec3 vitesseTangentielle = vitesseInitiale - vitesseNormaleInitiale;
		glm::dvec2 vitesseNormaleFinale2D = aidecollision::calculerForceAmortissement2D(details, (glm::dvec2)vitesseInitiale, 1.0);

		glm::dvec3 vitesseFinale = vitesseTangentielle + glm::dvec3{ vitesseNormaleFinale2D.x, vitesseNormaleFinale2D.y, 0.0 }
		+2 * vitesseAngulaire * distanceProjetee * glm::normalize(vecteurNormal); // Calcul explique dans le PDF
		// Ajouter a la vitesse de la bille selon ou elle frappe la palette en mouvement

		// S'assurer qu'on ne sera pas en collision avec la palette au prochain frame.
		glm::dvec3 positionFinale = bille->obtenirPositionRelative()
			+ details.enfoncement * glm::normalize(details.direction);

		bille->assignerPositionRelative(positionFinale);
		// Imposer une vitesse maximale
		double MODULE_VITESSE_MAX = 300;
		if (glm::length(vitesseFinale) > MODULE_VITESSE_MAX)
			vitesseFinale = MODULE_VITESSE_MAX * glm::normalize(vitesseFinale); //  Meme Direction mais ramener le module a 30.
		bille->assignerVitesse(vitesseFinale);
		bille->assignerImpossible(true);
		((NoeudBille*)bille)->afficherVitesse(vitesseFinale); // Que Dieu me pardonne
		// C'est la bille qui sait si debug_ == true ou false.
		// donc j'ai mis le if (debug_) dans NoeudBille::afficherVitesse(vitesse).
	}
	else
	{
		NoeudAbstrait::traiterCollisions(details, bille);
	}
}


bool NoeudPaletteD::estActiveeParBille(NoeudAbstrait* bille)
{
	// Si la palette n'a jamais etee activee, elle ne connait pas son angle original.
	if (etatPalette_ == INACTIVE)
		angleZOriginal_ = rotation_[2];

	glm::dvec3 positionPalette = obtenirPositionRelative();
	glm::dvec3 positionBille = bille->obtenirPositionRelative();
	positionPalette.z = 0.0; // Les positions utilisees ici doivent etre en 2D
	positionBille.z = 0.0; // Les positions utilisees ici doivent etre en 2D

	glm::dvec3 vecteur = positionBille - positionPalette;
	double distance = glm::length(vecteur);

	double angleEnRadian = angleZOriginal_ * utilitaire::PI_180;
	glm::dvec3 directionPalette = { cos(angleEnRadian), sin(angleEnRadian), 0 }; // Une palette pas tournee a un axe { 1, 0, 0}
	glm::dvec3 vecteurProjete = glm::proj(vecteur, directionPalette);
	glm::dvec3 vecteurNormal = vecteur - vecteurProjete;
	std::vector<glm::dvec3> boite = obtenirVecteursEnglobants();
	double longueurPalette = scale_.x*(boite_.coinMax.x - boite_.coinMin.x);

	double distanceProjetee = glm::length(vecteurProjete);
	double distanceNormale = glm::length(vecteurNormal);
	glm::dvec3 produitVectoriel;

	if (fonctionDroitePaletteOriginale(bille) > 0// << vrai si on la bille est au dessus de la droite definie par la palette. C<est ce qui fait que les palettes n'activent pas par en dessous.
		&& glm::dot(directionPalette, vecteur) > 0
		&& asin(glm::length(produitVectoriel) / glm::length(vecteur)) < sin(60 * utilitaire::PI_180)
		&& distance < longueurPalette)
		return true;

	else
		return false;
}



double NoeudPaletteD::fonctionDroitePaletteOriginale(NoeudAbstrait* bille)
{
	glm::dvec3 positionBille = bille->obtenirPositionRelative();
	glm::dvec3 positionPalette = obtenirPositionRelative();

	double angleEnRadian = angleZOriginal_ * utilitaire::PI_180;
	glm::dvec3 directionPalette = { -cos(angleEnRadian), -sin(angleEnRadian), 0 };
	double pente = 0;
	if (directionPalette.x != 0)
		pente = directionPalette.y / directionPalette.x;
	double b = positionPalette.y - positionPalette.x * pente;
	return positionBille.y - pente * positionBille.x - b;
}

double NoeudPaletteD::fonctionDroitePaletteEnMouvement(NoeudAbstrait* bille)
{
	glm::dvec3 positionBille = bille->obtenirPositionRelative();
	glm::dvec3 positionPalette = obtenirPositionRelative();

	double angleEnRadian = rotation_[2] * utilitaire::PI_180;
	glm::dvec3 directionPalette = { -cos(angleEnRadian), -sin(angleEnRadian), 0 };
	double pente = 0;
	if (directionPalette.x != 0)
		pente = directionPalette.y / directionPalette.x;
	double b = positionPalette.y - positionPalette.x * pente;
	return positionBille.y - pente * positionBille.x - b;
}



/// Obtenir la premiere boite englobante custom de l'histoire!
std::vector<glm::dvec3> NoeudPaletteD::obtenirVecteursEnglobants()
{
	std::vector<glm::dvec3> boiteEnglobanteObjet;

	glm::dmat3 echelle = glm::dmat3{ glm::dvec3{ scale_.x, 0, 0.0 },
		glm::dvec3{ 0, scale_.y, 0.0f },
		glm::dvec3{ 0.0, 0.0, scale_.z } };

	double angleEnRadian = -rotation_[2] * utilitaire::PI_180;
	glm::dmat3 transform = glm::dmat3{ glm::dvec3{ cos(angleEnRadian), -sin(angleEnRadian), 0.0 },
		glm::dvec3{ sin(angleEnRadian), cos(angleEnRadian), 0.0f },
		glm::dvec3{ 0.0, 0.0, 1.0 } };

	for (glm::dvec3 vecteur : boiteEnglobanteModele_)
	{
		boiteEnglobanteObjet.push_back(transform * (.7*echelle * vecteur));
	}

	return boiteEnglobanteObjet;
}