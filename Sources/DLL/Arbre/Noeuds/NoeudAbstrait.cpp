	////////////////////////////////////////////////
/// @file   NoeudAbstrait.cpp
/// @author DGI-2990
/// @date   2007-01-24
///
/// @ingroup Noeud
////////////////////////////////////////////////

#include "NoeudAbstrait.h"
#include "Utilitaire.h"
#include "../../Commun/Externe/glm/include/glm/gtx/Projection.hpp"

#include "NoeudBille.h"

unsigned int NoeudAbstrait::compteurNoeuds_ = 0;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::NoeudAbstrait(const std::string& type)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] type               : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::NoeudAbstrait(
	const std::string& type //= std::string{ "" }
	) :
	vitesse_{ 0.0, 0.0, 0.0 },
	type_(type)
{
	colorShift_ = false;
	compteurNoeuds_ += 1;
	numeroNoeud_ = compteurNoeuds_;
	scale_ = { 1.0, 1.0, 1.0 };
	twin_ = nullptr;
	transparent_ = false;
	impossible_ = false;
	animer_ = SingletonGlobal::obtenirInstance()->obtenirAnimation();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::~NoeudAbstrait()
///
/// Destructeur vide declare virtuel pour les classes derivees.  La
/// liberation des afficheurs n'est pas la responsabilite de cette
/// classe.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::~NoeudAbstrait()
{
	this->vider();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::calculerProfondeur() const
///
/// Cette fonction calcule la profondeur de l'arbre incluant le noeud
/// courant ainsi que tous ses enfants.
///
/// Cette fonction retourne toujours 1 pour un noeud sans enfant.
///
/// @return La profondeur de l'arbre sous ce noeud, donc toujours 1.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::calculerProfondeur() const
{
	return 1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::vider()
///
/// Cette fonction vide le noeud de tous ses enfants.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par defaut de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::vider()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacer( const NoeudAbstrait* noeud )
///
/// Cette fonction efface le noeud s'il fait partie des enfants de
/// ce noeud.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par defaut de la classe de base.
///
/// @param[in] noeud : Le noeud a effacer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacer(const NoeudAbstrait* noeud)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud ) const
///
/// Cette fonction cherche un noeud d'un type donne parmi le noeud
/// lui-meme et ses enfants.
///
/// Elle retourne donc le noeud lui-meme si son type est celui passe en
/// parametre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud a trouver.
///
/// @return Le pointeur vers le noeud s'il est trouve.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher(const std::string& typeNoeud) const
{
	if (typeNoeud == type_)
		return this;
	else
		return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud )
///
/// Cette fonction cherche un noeud d'un type donne parmi le noeud
/// lui-meme et ses enfants.
///
/// Elle retourne donc le noeud lui-meme si son type est celui passe en
/// parametre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud a trouver.
///
/// @return Le pointeur vers le noeud s'il est trouve.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher(const std::string& typeNoeud)
{
	if (typeNoeud == type_)
		return this;
	else
		return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice ) const
///
/// Cette fonction cherche le i-eme enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// derniere ne possede pas d'enfant.
///
/// @param[in] indice : L'indice du noeud a trouver.
///
/// @return Le pointeur vers le noeud s'il est trouve.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher(unsigned int indice) const
{
	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice )
///
/// Cette fonction cherche le i-eme enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// derniere ne possede pas d'enfant.
///
/// @param[in] indice : L'indice du noeud a trouver.
///
/// @return Le pointeur vers le noeud s'il est trouve.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher(unsigned int indice)
{
	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
///
/// Cette fonction ajoute un enfant a ce noeud.
///
/// Elle retourne toujours faux et ne fait rien, car ce type de noeud
/// abstrait ne peut pas avoir d'enfant.
///
/// @param[in] enfant: Le noeud a ajouter.
///
/// @return Vrai si l'ajout a bien ete effectue, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
{
	return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::obtenirDernierNoeud()
///
/// Cette fonction retourne le plus recent objet rajouter.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::obtenirDernierNoeud()
{
	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::getEnfant(int position)
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// derniere ne possede pas d'enfant.
///
/// @param[in] position: position a obtenir
///
/// @return Le nombre d'enfants directement sous ce noeud.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::getEnfant(int position)
{
	return nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::obtenirNombreEnfants() const
///
/// Cette fonction retourne le nombre d'enfants de ce noeud.
///
/// Elle retourne toujours 0, car ce type de noeud abstrait ne peut pas
/// avoir d'enfant.
///
/// @return Vrai si l'ajout a bien ete effectue, faux autrement.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::obtenirNombreEnfants() const
{
	return 0;
}

// Aucune idee pk c'est ici
modele::Modele3D const* NoeudAbstrait::obtenirModele() const
{
	return modele_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::inverserSelection()
///
/// Cette fonction inverse l'etat de selection de ce noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::inverserSelection()
{
	selectionne_ = !selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::selectionnerTout()
///
/// Cette fonction selectionne le noeud et ses enfants.
///
/// Elle ne fait que selectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::selectionnerTout()
{
	assignerSelection(true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::deselectionnerTout()
///
/// Cette fonction deselectionne le noeud et ses enfants.
///
/// Elle ne fait que deselectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::deselectionnerTout()
{
	selectionne_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::selectionExiste() const
///
/// Cette fonction verifie si le noeud ou un de ses enfants est
/// selectionne.
///
/// Elle ne fait que regarder si le noeud est selectionne, car ce type
/// de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Vrai s'il existe un noeud selectionne, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::selectionExiste() const
{
	return selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::changerModePolygones( bool estForce )
///
/// Cette fonction change le mode de rendu des polygones du noeud s'il
/// est selectionne ou si on le force.
///
/// @param[in] estForce: Vrai si on veut changer le mode meme si le
///                      noeud n'est pas selectionne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::changerModePolygones(bool estForce)
{
	if ((estForce) || (estSelectionne())) {
		if (modePolygones_ == GL_FILL)
			modePolygones_ = GL_LINE;
		else if (modePolygones_ == GL_LINE)
			modePolygones_ = GL_POINT;
		else
			modePolygones_ = GL_FILL;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerModePolygones( GLenum modePolygones )
///
/// Cette fonction assigne le mode de rendu des polygones du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerModePolygones(GLenum modePolygones)
{
	// Le mode par defaut si on passe une mauvaise valeur est GL_FILL
	if ((modePolygones != GL_FILL) &&
		(modePolygones != GL_LINE) &&
		(modePolygones != GL_POINT)) {
		modePolygones = GL_FILL;
	}

	modePolygones_ = modePolygones;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficher() const
///
/// Cette fonction affiche le noeud comme tel.
///
/// Elle consiste en une template method (dans le sens du patron de
/// conception, et non les template C++) qui effectue ce qui est
/// generalement a faire pour l'affichage, c'est-a-dire:
/// - Mise en pile de la matrice de transformation
/// - Translation du noeud pour qu'il soit a sa position relative
/// - Utilisation du mode d'affichage des polygones
/// - ...
/// - Restauration de l'etat.
///
/// L'affichage comme tel est confie a la fonction afficherConcret(),
/// appelee par la fonction afficher().
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficher() const
{
	if (affiche_) {
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT);

		// La translation de la position relative
		glTranslated(
			positionRelative_[0], positionRelative_[1], positionRelative_[2]
			);
		
		glRotated(rotation_[2], 0.0F, 0.0F, 1.0F);
		glRotated(rotation_[0], 1.0F, 0.0F, 0.0F);
		glRotated(rotation_[1], 0.0F, 1.0F, 0.0F);

		glScaled(scale_[0], scale_[1], scale_[2]);

		// Assignation du mode d'affichage des polygones
		glPolygonMode(GL_FRONT_AND_BACK, modePolygones_);

		// Affichage concret
		glStencilFunc(GL_ALWAYS, numeroNoeud_, -1);

		afficherConcret();

		// Restauration
		glPopAttrib();
		glPopMatrix();
	}
}

void NoeudAbstrait::appliquerAfficher() const
{
	if (colorShift_)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	if (impossible_)
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
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.  Elle est
/// appelee par la template method (dans le sens du patron de conception,
/// et non des template C++) afficher() de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficherConcret() const
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::animer( float dt )
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// Elle ne fait rien pour cette classe et vise a etre surchargee par
/// les classes derivees.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::animer(float dt)
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerAnimer(bool animer)
///
/// @param[in] animer : valeur a mettre dans animer_.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerAnimer(bool animer)
{
	animer_ = animer;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::obtenirAnimer()
///
/// @return Retourne si le noeud est animer.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::obtenirAnimer()
{
	return animer_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::accepterVisiteur(VisiteurAbstrait* vis)
///
///
/// Cette fonction permet d'accepter un visiteur (voir le livre de Gamma)
///
/// @param[in] vis : Prend un visiteur abstrait.
///
/// @return Reusite ou echec.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::accepterVisiteur(VisiteurAbstrait* vis) 
{
	vis->traiter(this); 
	return false; 
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::accepterJoueurVirtuel(JoueurVirtuel* joueur)
///
///
/// Cette fonction permet d'accepter un joueur virtuel
///
/// @param[in] joueur : Prend un JoueurVirtuel
///
/// @return Reusite ou echec.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::accepterJoueurVirtuel(JoueurVirtuel* joueur)
{
	joueur->traiter(this);
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::getTwin()
///
/// Retourne le noeud jumueau
///
/// @return NoeudAbstrait jumeau.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::getTwin()
{
	return twin_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::setTwin()
///
/// Cette fonction permet de definir un noeud jumeau
///
/// @param[in] twin : Prend un noeud abstrait.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::setTwin(NoeudAbstrait* twin)
{
	twin_ = twin;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::obtenirVecteursBoite(glm::dvec3 &v1, glm::dvec3 &v2, glm::dvec3 &v3, glm::dvec3 &v4)
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
void NoeudAbstrait::obtenirVecteursBoite(glm::dvec3 &v1, glm::dvec3 &v2, glm::dvec3 &v3, glm::dvec3 &v4)
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
		glm::dvec3{ 0.0, 0.0, scale_.z } };

	//mise a l'echelle des vecteurs
	v1 = echelle * v1;
	v2 = echelle * v2;
	v3 = echelle * v3;
	v4 = echelle * v4;

	//calcul matrice de rotation
	double angleEnRadian = -rotation_[2] * utilitaire::PI_180;
	glm::dmat3 transform = glm::dmat3{ glm::dvec3{ cos(angleEnRadian), -sin(angleEnRadian), 0.0 },
										 glm::dvec3{ sin(angleEnRadian), cos(angleEnRadian), 0.0f },
										 glm::dvec3{ 0.0, 0.0, 1.0 } };
	
	//applique la rotation aux vecteurs
	v1 = transform * v1;
	v2 = transform * v2;
	v3 = transform * v3;
	v4 = transform * v4;
}

void NoeudAbstrait::obtenirBoiteModele(glm::dvec3 &v1, glm::dvec3 &v2, glm::dvec3 &v3, glm::dvec3 &v4)
{
	//initialiser les vecteurs
	v1 = boite_.coinMin;
	v2.x = boite_.coinMin.x;
	v2.y = boite_.coinMax.y;
	v3 = boite_.coinMax;
	v4.x = boite_.coinMax.x;
	v4.y = boite_.coinMin.y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<glm::dvec3> NoeudAbstrait::obtenirVecteursEnglobants()
/// 
/// Implementation par defaut de la boite englobante.
///
/// @return Un vector<glm::dvec3> contenant 4 vecteurs allant de la position
/// du noeud aux coins de sa boite englobante
/// 
////////////////////////////////////////////////////////////////////////
std::vector<glm::dvec3> NoeudAbstrait::obtenirVecteursEnglobants()
{
	glm::dvec3 tableauVect[4];
	obtenirVecteursBoite(tableauVect[0], tableauVect[1], tableauVect[2], tableauVect[3]);
	return{ tableauVect[0], tableauVect[1], tableauVect[2], tableauVect[3] };
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::getColorShift()
///
/// Retourne si la couleur est modifier ou non
///
/// @return Bool.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::getColorShift()
{
	return colorShift_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::setColorShift(bool colorShift)
///
/// Change de couleur
///
/// @param[in] colorShift: activer ou desactiver le changement de couleur
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::setColorShift(bool colorShift)
{
	colorShift_ = colorShift;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::getTransparent()
///
/// Retourne si l'objet est transparent ou non
///
/// @return Bool de transparence.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::getTransparent()
{
	return transparent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::setTransparent(bool transparent)
///
/// Change de transparence
///
/// @param[in] transparent: activer ou desactiver la transparence
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::setTransparent(bool transparent)
{
	transparent_ = transparent;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::getImpossible()
///
/// Retourne si l'objet rouge (impossible de poser) ou non
///
/// @return Bool impossible a mettre.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::getImpossible()
{
	return impossible_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::setImpossible(bool transparent)
///
/// Change de transparence
///
/// @param[in] transparent: activer ou desactiver le rouge (impossible de poser)
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::setImpossible(bool impossible)
{
	impossible_ = impossible;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::pointEstDansBoite(glm::dvec3 point)
/// @brief Cette fonction teste si un point se trouve dans la boîte englobante.
///
/// @param[in] point : Point a tester.
///
/// @return True si le test reussit, false sinon
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::pointEstDansBoite(glm::dvec3 point)
{
	glm::dvec3 vecOP = point - positionRelative_;

	//calcul matrice de rotation inverse
	double angleEnRadian = rotation_[2] * utilitaire::PI_180;
	glm::dmat3 transform = glm::dmat3{ glm::dvec3{ cos(angleEnRadian), -sin(angleEnRadian), 0.0 },
		glm::dvec3{ sin(angleEnRadian), cos(angleEnRadian), 0.0f },
		glm::dvec3{ 0.0, 0.0, 1.0 } };

	//appliquer rotation inverse au vecteur
	vecOP = transform * vecOP;

	//appliquer la mise a l'echelle inverse
	glm::dmat3 echelle = glm::dmat3{ glm::dvec3{ 1/scale_.x, 0, 0.0 },
		glm::dvec3{ 0, 1/scale_.y, 0.0f },
		glm::dvec3{ 0.0, 0.0,1/ scale_.z } };
	vecOP = echelle * vecOP;

	//verifie si le vecteur est dans la boite
	if (vecOP.x > boite_.coinMin.x && vecOP.x < boite_.coinMax.x &&
		vecOP.y > boite_.coinMin.y && vecOP.y < boite_.coinMax.y)
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::setDebug(bool debug)
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::setDebug(bool debug)
{
	debug_ = debug;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::setSpotLight(bool debug)
///
/// Cette fonction change la valeur du mode spotLight
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::setSpotLight(bool debug)
{
	spotLight_ = debug;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void aidecollision::DetailsCollision NoeudAbstrait::detecterCollisions(NoeudAbstrait* bille)
///
/// Cette fonction retourne un objet detail collision pour la 
/// collision de la bille sur l'objet courant.
///
/// @return details contient l'information sur la collision de la bille avec *this.
///
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudAbstrait::detecterCollisions(NoeudAbstrait* bille)
{
	std::vector<glm::dvec3> boite = obtenirVecteursEnglobants();
	double rayonBille = bille->obtenirVecteursEnglobants()[0].x;
	aidecollision::DetailsCollision details;
	if (boite.size() > 1)
	{
		for (unsigned int i = 0; i < boite.size(); i++)
			boite[i] += obtenirPositionRelative();
		// Considerer tous les segments boite[i] --- boite[i+1 % size] 
		aidecollision::DetailsCollision detailsRetour;
		detailsRetour.type = aidecollision::COLLISION_AUCUNE;
		for (unsigned int i = 0; i < boite.size(); i++)
		{
			// On veut calculer la collision en 2D et caster les paramêtres en glm::dvec2 "oublie" leur composante en Z et choisi la bonne surcharge de calculerCollisionSegment.
			details = aidecollision::calculerCollisionSegment((glm::dvec2)boite[i], (glm::dvec2)boite[(i + 1) % boite.size()], (glm::dvec2)bille->obtenirPositionRelative(), rayonBille, true);
			if (details.type != aidecollision::COLLISION_AUCUNE)
			{
				// Donner priorité aux collision sur les segments plutot que sur les points.
				if (details.type == aidecollision::COLLISION_SEGMENT)
					return details;
				else
					detailsRetour = details;
			}
		}
		return details;
	}
	else if (boite.size() == 1)// a mettre dans la reimplementation pour les objets circulaires.
	{
		double rayon = boite[0].x;
		details = aidecollision::calculerCollisionCercle((glm::dvec2)obtenirPositionRelative(), rayon, (glm::dvec2)bille->obtenirPositionRelative(), rayonBille);
		if (details.type != aidecollision::COLLISION_AUCUNE)
		{
			return details;
		}
	}
	return details;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille)
///
/// Cette fonction effectue la réaction a la collision de la bille sur 
/// l'objet courant. Cette fonction est a reimplementer si on veut autre 
/// chose qu'un rebondissement ordinaire.
///
/// @return details contient l'information sur la collision de la bille avec *this.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float facteurRebond)
{

	assert(bille->obtenirType() == "bille");

	if (details.type == aidecollision::COLLISION_AUCUNE)
		return;
	if (bille == this)
		return;

	// Modifier la vitesse de la bille en fonction de bille reçue en paramètre 
	glm::dvec3 vitesseInitiale = bille->obtenirVitesse();
	glm::dvec3 vitesseNormaleInitiale = glm::proj(vitesseInitiale, details.direction); // Necessaire pour connaitre la vitesse tangentielle.
	glm::dvec3 vitesseTangentielle = vitesseInitiale - vitesseNormaleInitiale;
	glm::dvec2 vitesseNormaleFinale2D = aidecollision::calculerForceAmortissement2D(details, (glm::dvec2)vitesseInitiale, facteurRebond);
	glm::dvec3 vitesseFinale = vitesseTangentielle + glm::dvec3{ vitesseNormaleFinale2D.x, vitesseNormaleFinale2D.y, 0.0 };
		((NoeudBille*)bille)->afficherVitesse(vitesseFinale); // Que Dieu me pardonne


	glm::dvec3 positionFinale = bille->obtenirPositionRelative() + details.enfoncement * glm::normalize(details.direction);
	bille->assignerPositionRelative(positionFinale);

	bille->assignerVitesse(vitesseFinale);
	bille->assignerImpossible(true);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerPortailDorigine(NoeudAbstrait* portail)
///
/// Assigne l'attribut portailDorigine avec un portail.  Ce portail ne causera pas
/// de force sur la bille.  Une fois que la bille s'est assez eloignee du
/// portail, on remet cet attirbut a nullptr.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerPortailDorigine(NoeudAbstrait* portail)
{
	portailDorigine_ = portail;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerPortailDorigine(NoeudAbstrait* portail)
///
/// Obtient l'attribut portailDorigine_ pour le comparer avec les portails.
/// Si un portail est le portail d'origine, il ne cree pas de force sur 
/// la bille.
/// 
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::obtenirPortailDorigine()
{
	return portailDorigine_;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::genererBille()
///
/// Ne fais rien
/// 
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::genererBille()
{
	return;
}