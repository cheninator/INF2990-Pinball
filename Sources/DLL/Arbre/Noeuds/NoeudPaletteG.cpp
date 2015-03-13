///////////////////////////////////////////////////////////////////////////
/// @file NoeudPaletteG.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudPaletteG.h"
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
/// @fn NoeudPaletteG::NoeudPaletteG(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPaletteG::NoeudPaletteG(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	ajustable_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPaletteG::~NoeudPaletteG()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPaletteG::~NoeudPaletteG()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPaletteG::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteG::afficherConcret() const
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
/// @fn void NoeudPaletteG::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteG::animer(float temps)
{
	NoeudComposite::animer(temps);

	switch (etatPalette_)
	{
	case ACTIVE:
		// TODO : Verifier que la rotation que je veux faire est possible,
		// si impossible, la palette est bloquee et doit tomber dans l'etat INACTIVE
		if (obtenirRotation().z - angleZOriginal_ < 60)
		{
			assignerRotation(glm::dvec3{ 0, 0, 9 });
		}
		break;
	case RETOUR:
		if (obtenirRotation().z - angleZOriginal_ > 0)
		{
			assignerRotation(glm::dvec3{ 0, 0, -3 });
		}
		else
		{
			assignerRotationHard(glm::dvec3{ rotation_.x, rotation_.y, angleZOriginal_ });
			etatPalette_ = INACTIVE;
		}
		break;
	case ACTIVE_AI:
		if (obtenirRotation().z - angleZOriginal_ < 60)
		{
			assignerRotation(glm::dvec3{ 0, 0, 9 });
		}
		else
		{
			if (timer_ >= 0.25)
			{
				etatPalette_ = RETOUR_AI;
				timer_ = 0;
			}
			else
				timer_ += temps;
		}
		break;
	case RETOUR_AI:
		if (obtenirRotation().z - angleZOriginal_ > 0)
		{
			assignerRotation(glm::dvec3{ 0, 0, -3 });
		}
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
/// @fn bool NoeudPaletteG::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudPaletteG::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPaletteG::activer()
///
/// Cette fonction active l'animation qui fait monter les palettes. On en
/// profite pour sauvegarder l'angle intial des palettes quand la palette est inactive
/// 
/// @remark appelee quand la bonne touche est appuyee.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteG::activer()
{
	if (etatPalette_ == INACTIVE)
		angleZOriginal_ = obtenirRotation().z;
	
	etatPalette_ = ACTIVE;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPaletteG::desactiver()
///
/// Cette fonction active l'animation qui fait revenir les palettes.
///
/// @remark appelee quand la bonne touche est relachee
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteG::desactiver()
{
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
void NoeudPaletteG::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille)
{
	if (1 && (etatPalette_ == ACTIVE || etatPalette_ == ACTIVE_AI) && fonctionDroitePaletteEnMouvement(bille) > 0)
	{
		glm::dvec3 positionPalette = obtenirPositionRelative();
		glm::dvec3 positionBille = bille->obtenirPositionRelative();
		positionPalette.z = 0.0; // Les positions utilisees ici doivent etre en 2D
		positionBille.z = 0.0; // Les positions utilisees ici doivent etre en 2D
		glm::dvec3 vecteur = positionBille - positionPalette;
		double distance = glm::length(vecteur);

		double angleEnRadian = rotation_[2] * utilitaire::PI_180;
		glm::dvec3 directionPalette = { -cos(angleEnRadian), -sin(angleEnRadian), 0 }; // Une palette pas tournee a un axe { - 1, 0, 0}
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
														+  2* vitesseAngulaire * distanceProjetee * glm::normalize(vecteurNormal); // Calcul explique dans le PDF
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


bool NoeudPaletteG::estActiveeParBille(NoeudAbstrait* bille)
{
	assert(bille->obtenirType() == "bille");

	// Si la palette n'a jamais etee activee, elle ne connait pas son angle original.
	if (etatPalette_ == INACTIVE)
		angleZOriginal_ = rotation_[0];

	glm::dvec3 positionPalette = obtenirPositionRelative();
	glm::dvec3 positionBille = bille->obtenirPositionRelative();
	positionPalette.z = 0.0; // Les positions utilisees ici doivent etre en 2D
	positionBille.z = 0.0; // Les positions utilisees ici doivent etre en 2D

	glm::dvec3 vecteur= positionBille - positionPalette;
	double distance = glm::length(vecteur);

	double angleEnRadian = angleZOriginal_ * utilitaire::PI_180;
	glm::dvec3 directionPalette = { -cos(angleEnRadian), -sin(angleEnRadian), 0 }; // Une palette pas tournee a un axe { - 1, 0, 0}
	glm::dvec3 vecteurProjete = glm::proj(vecteur, directionPalette);
	glm::dvec3 vecteurNormal = vecteur - vecteurProjete;
	std::vector<glm::dvec3> boite = obtenirVecteursEnglobants();
	double longueurPalette = boite[0].x - boite[2].x;

	double distanceProjetee = glm::length(vecteurProjete);
	double distanceNormale = glm::length(vecteurNormal);
	glm::dvec3 produitVectoriel;

	if (fonctionDroitePaletteOriginale(bille) > 0// << vrai si on la bille est au dessus de la droite definie par la palette. C<est ce qui fait que les palettes n'activent pas par en dessous.
		&& glm::dot(directionPalette, vecteur) < 0
		&& asin(glm::length(produitVectoriel) / glm::length(vecteur)) < sin(60 * utilitaire::PI_180)
		&& distance < longueurPalette
		)
		return true;
	else
		return false;

	/*
	// positionBille.y > pente * positionBille.x + b <====> la bille est au dessus de la droite definie par la palette au repos.
	if (fonctionDroitePaletteOriginale(bille) > 0// << vrai si on la bille est au dessus de la droite definie par la palette. C<est ce qui fait que les palettes n'activent pas par en dessous.
		&& positionBille.x < positionPalette.x + 80 // << essayer de remplacer par glm::length(glm::proj(vecteur, directionPalette)) < longueurPalette
		&& positionBille.x > positionPalette.x
		&& distanceNormale < 40
		)
		return true;
	else
		return false;
	*/
}

double NoeudPaletteG::fonctionDroitePaletteOriginale(NoeudAbstrait* bille)
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

double NoeudPaletteG::fonctionDroitePaletteEnMouvement(NoeudAbstrait* bille)
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

void NoeudPaletteG::activerAI()
{
	// Les palettesAI doivent pouvoir etre activerAI meme si une bille ne se trouve pas proche
	if (etatPalette_ == INACTIVE)
	{
		angleZOriginal_ = obtenirRotation().z;
		etatPalette_ = ACTIVE_AI;
	}
}

// Pas besoin de NoeudPaletteG::desactiverAI() parce que c'est deja integre a la logique des etats.

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPaletteG::accepterJoueurVirtuel(JoueurVirtuel* joueur)
///
///
/// Cette fonction permet d'accepter un joueur virtuel
///
/// @param[in] joueur : Prend un JoueurVirtuel
///
/// @return Reusite ou echec.
///
////////////////////////////////////////////////////////////////////////
bool NoeudPaletteG::accepterJoueurVirtuel(JoueurVirtuel* joueur)
{
	joueur->traiter(this);
	return true;
}