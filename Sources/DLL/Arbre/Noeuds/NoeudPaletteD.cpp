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

///////////////////////////////////////////////////////////////////////
//  Vecteurs de la boite englobante sur mesure du modèle
///////////////////////////////////////////////////////////////////////
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
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	NoeudAbstrait::appliquerAfficher();
	liste_->dessiner();
	glPopAttrib();
	glPopMatrix();
	// Restauration de la matrice.
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
		case INACTIVE:
		case BLOQUEE:

			vitesseAngulaire_ = 0;
			break;

		case ACTIVE:

			// TODO : Verifier que la rotation que je veux faire est possible,
			// si impossible, la palette est bloquee et doit tomber dans l'etat INACTIVE
			if (angleZOriginal_ - obtenirRotation().z < 60)
			{
				//verifier si la palette entre en collision avec un autre objet
				std::vector<glm::dvec3> boite = obtenirVecteursEnglobants();
				NoeudAbstrait* parent = obtenirParent();
				bool contact = false;
				unsigned int i = 0;
				while (i < parent->obtenirNombreEnfants() && contact == false)
				{
					std::string type = parent->getEnfant(i)->obtenirType();

					if (parent->getEnfant(i) != this && type != "bille" && type != "generateurbille" && parent->getEnfant(i)->estAffiche())
					{
						int j = 0;
						while (j < boite.size() && contact == false)
						{
							if (type != "butoirg" && type != "butoird")
							{
								if (parent->getEnfant(i)->pointEstDansBoite(boite[j] + positionRelative_))
									contact = true;
							}
							else //si butoir triangulaire
							{
								//verifier s'il y a intersection entre un segment de la palette avec
								//un segment du butoir
								std::vector<glm::dvec3> boiteButoir = parent->getEnfant(i)->obtenirVecteursEnglobants();
								int k = 0;
								while (k < boiteButoir.size() && contact == false)
								{
									glm::dvec3 a = boite[j] + positionRelative_;
									glm::dvec3 b = boite[(j + 1) % boite.size()] + positionRelative_;
									glm::dvec3 c = boiteButoir[k] + parent->getEnfant(i)->obtenirPositionRelative();
									glm::dvec3 d = boiteButoir[(k + 1) % boiteButoir.size()] + parent->getEnfant(i)->obtenirPositionRelative();

									if (utilitaire::intersectionDeuxSegments(a, b, c, d))
										contact = true;

									k++;
								}
							}

							j++;
						}
					}

					i++;
				}

				if (!contact)
				{
					assignerRotation(glm::dvec3{ 0, 0, -VITESSE_ANGULAIRE_PALETTE_ACTIVE * temps });
					vitesseAngulaire_ = -VITESSE_ANGULAIRE_PALETTE_ACTIVE * utilitaire::PI_180;
				}
				else
				{
					vitesseAngulaire_ = 0;
					etatPalette_ = BLOQUEE;
				}				
			}
			else
			{
				assignerRotationHard(glm::dvec3{ rotation_.x, rotation_.y, angleZOriginal_ - 60 });
				etatPalette_ = BLOQUEE;
			}

			break;

		case RETOUR:

			if (angleZOriginal_ - obtenirRotation().z > 0)
			{
				assignerRotation(glm::dvec3{ 0, 0, VITESSE_ANGULAIRE_PALETTE_RETOUR * temps });
				vitesseAngulaire_ = VITESSE_ANGULAIRE_PALETTE_RETOUR * utilitaire::PI_180;
			}
			else
			{
				assignerRotationHard(glm::dvec3{ rotation_.x, rotation_.y, angleZOriginal_ });
				etatPalette_ = INACTIVE;
			}

			break;
	}

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPaletteD::accepterVisiteur(VisiteurAbstrait* vis)
///
/// @brief Cette fonction appelle la methode traiter du visiteur.
///
/// @param[in] vis Pointeur sur le visiteur a accepter
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

	if (etatPalette_ != BLOQUEE)
	{
		SoundControl->jouerSon("palette");
		etatPalette_ = ACTIVE;
	}	
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
	glm::dvec3 vecteur = bille->obtenirPositionRelative() - obtenirPositionRelative();
	double distance = glm::length(vecteur);
	
	// Traitement de la collision dans le referentiel de la palette
	glm::dvec3 vitesseReferentielPalette = vitesseAngulaire_ * distance * glm::normalize(glm::dvec3{ -vecteur.y, vecteur.x, 0 });
	glm::dvec3 vitesseInitiale = bille->obtenirVitesse() - vitesseReferentielPalette; // RefPalette
	glm::dvec3 vitesseNormaleInitiale = glm::proj(vitesseInitiale, details.direction); // Necessaire pour connaitre la vitesse tangentielle.
	glm::dvec3 vitesseTangentielle = vitesseInitiale - vitesseNormaleInitiale;
	glm::dvec2 vitesseNormaleFinale2D = aidecollision::calculerForceAmortissement2D(details, (glm::dvec2)vitesseInitiale, 1.0);

	// Calcul de la vitesse finale dans le referentiel de la table
	glm::dvec3 vitesseFinale = vitesseTangentielle + glm::dvec3{ vitesseNormaleFinale2D.x, vitesseNormaleFinale2D.y, 0.0 } + vitesseReferentielPalette; 

	// S'assurer qu'on ne sera pas en collision avec la palette au prochain frame.
	glm::dvec3 positionFinale = bille->obtenirPositionRelative() + details.enfoncement * glm::normalize(details.direction);

	// Faire les assignations
	bille->assignerPositionRelative(positionFinale);
	bille->assignerVitesse(vitesseFinale);
	bille->assignerImpossible(true);

	// Effet sonore
	SoundControl->jouerSon("palette2");

	// Affichage de debogage
	((NoeudBille*)bille)->afficherVitesse(vitesseFinale); // Que Dieu me pardonne
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPaletteD::estActiveeParBille(NoeudAbstrait* bille)
///
/// Cette fonction verifie si une bille passee en parametre est dans une 
/// la zone balayee par la palette.  Cette fonction permet au joueur 
/// virtuel de decider d'activer ses palettes
/// 
/// @param[in] bille : bille l'objet pour lequel on verifie s'il est
/// dans la zone balayee par la palette.
///
/// @return true si la bille est dans la zone balayee par la palette.
///
////////////////////////////////////////////////////////////////////////
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

	//double distanceProjetee = glm::length(vecteurProjete);
	//double distanceNormale = glm::length(vecteurNormal);
	glm::dvec3 produitVectoriel = glm::cross(directionPalette, vecteur);

	if (produitVectoriel.z < 0// << vrai si on la bille est au dessus de la droite definie par la palette. C<est ce qui fait que les palettes n'activent pas par en dessous.
		&& glm::dot(directionPalette, vecteur) > 0
		&& asin(glm::length(produitVectoriel) / glm::length(vecteur)) < sin(60 * utilitaire::PI_180)
		&& distance < longueurPalette)
		return true;
	else
		return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudPaletteD::fonctionDroitePaletteOriginale(NoeudAbstrait* bille)
///
/// Traite la droite definie par la palette au repos comme une equation F(x,y) == 0.  La fonction
/// calcule F(x,y) avec le x et le y de la bille passee en parametre.
/// La fonction permet de savoir si la bille est au dessus ou en 
/// dessous de la palette.
///
/// @param[in] bille : bille objet donnant le x et y pour calculer F(x,y)
///
/// @return la valeur de F(x,y) pour le x et le y de la bille
///
/// @remark deprecated. On devrait utiliser le signe de la composante z du produit
/// vectoriel pour determiner si on est au dessus de l'axe de la palette ou en dessous
///
////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudPaletteD::fonctionDroitePaletteEnMouvement(NoeudAbstrait* bille)
///
/// Traite la droite definie par la palette dans sa position courante comme une equation F(x,y) == 0.  La fonction
/// calcule F(x,y) avec le x et le y de la bille passee en parametre.
/// La fonction permet de savoir si la bille est au dessus ou en 
/// dessous de la palette.
///
/// @param[in] bille : bille objet donnant le x et y pour calculer F(x,y)
///
/// @return la valeur de F(x,y) pour le x et le y de la bille
///
/// @remark deprecated. On devrait utiliser le signe de la composante z du produit
/// vectoriel pour determiner si on est au dessus de l'axe de la palette ou en dessous
///
////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<glm::dvec3> NoeudPaletteD::obtenirVecteursEnglobants()
///
/// @brief Retourne la boite englobante de l'objet sous forme d'un vector de vecteurs
///
/// @remark Pour avoir les points de la boite englobante, il faut additionner la position de l'objet.
///
/// @return boiteEnglobanteObjet Vecteur contenant les vecteurs de la boite de l'objet
///
////////////////////////////////////////////////////////////////////////
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