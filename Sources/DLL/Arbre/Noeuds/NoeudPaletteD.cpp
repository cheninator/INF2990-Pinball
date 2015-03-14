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
	estActive = false;
	estJoueurVirtuel = true;
	initial_ = true;

	vitesseMonteAngulaire_ = { 0, 0, 9 };
	vitesseDescenteAngulaire_ = { 0, 0, -3 };
	angleZOriginal_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPaletteD::~NoeudPaletteD()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
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

	if (initial_)
	{
		angleZOriginal_ = obtenirRotation().z;
		initial_ = false;
	}

	/// Lorsque le joueur active la palette
	if (estActive)
	{
		/// Faire pivoter la palette tant que le déplacement angulaire n'est pas égal à 60 degrés
		if (obtenirRotation().z - angleZOriginal_ < 60)
			assignerRotation(vitesseMonteAngulaire_);

		/// Comportement du joueur virtuel
		if (estJoueurVirtuel)
		{
			/// Faire redescendre la palette du joueur virtuel apres un certain temps
			if (timer_ >= 0.25)
			{
				desactiver();
				timer_ = 0;
			}
			else
				timer_ += temps;
		}
	}

	/// Lorsque le joueur desactive le mouvement de la palette
	else
	{
		/// Faire redescendre la palette à son etat initial
		if (obtenirRotation().z - angleZOriginal_ > 0)
			assignerRotation(vitesseDescenteAngulaire_);

		/// Reassigner les valeurs initiales
		else
			assignerRotationHard(glm::dvec3{ rotation_.x, rotation_.y, angleZOriginal_ });
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
	estActive = true;
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
	estActive = false;
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
void NoeudPaletteD::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille)
{
	if (fonctionDroitePaletteEnMouvement(bille) > 0)
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
			+ details.enfoncement * glm::normalize(details.direction)
			+ 1.1*deltaAngle*distanceProjetee*glm::normalize(vecteurNormal);

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
