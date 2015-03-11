////////////////////////////////////////////////
/// @file   NoeudComposite.cpp
/// @author DGI-2990
/// @date   2007-01-25
///
/// @ingroup Noeud
////////////////////////////////////////////////

#include "NoeudComposite.h"	
#include "../../Global/SingletonGlobal.h"
#include <cassert>

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudComposite::NoeudComposite(const std::string& type)
///
/// Ne fait qu'appeler la version de la classe de base.
///
/// @param[in] type               : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudComposite::NoeudComposite(
	const std::string& type //= std::string{ "" }
	) :
	NoeudAbstrait{ type }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudComposite::~NoeudComposite()
///
/// Destructeur qui detruit tous les enfants du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudComposite::~NoeudComposite()
{
	vider();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudComposite::calculerProfondeur() const
///
/// Cette fonction calcule la profondeur de l'arbre incluant le noeud
/// courant ainsi que tous ses enfants.
///
/// Cette fonction retourne toujours 1 de plus que la profondeur de son
/// enfants le plus profond.
///
/// @return La profondeur de l'arbre sous ce noeud.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudComposite::calculerProfondeur() const
{
	unsigned int profondeurEnfantMax{ 0 };

	for (NoeudAbstrait const* enfant : enfants_)
	{
		const unsigned int profondeurEnfant{ enfant->calculerProfondeur() };
		if (profondeurEnfantMax < profondeurEnfant)
			profondeurEnfantMax = profondeurEnfant;
	}

	return profondeurEnfantMax + 1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::vider()
///
/// Cette fonction vide le noeud de tous ses enfants.  Elle effectue une
/// iteration prudente sur les enfants afin d'etre assez robuste pour
/// supporter la possibilite qu'un enfant en efface un autre dans son
/// destructeur, par exemple si deux objets ne peuvent pas exister l'un
/// sans l'autre.  Elle peut toutefois entrer en boucle infinie si un
/// enfant ajoute un nouveau noeud lorsqu'il se fait effacer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::vider()
{
	// L'iteration doit etre faite ainsi pour eviter les problemes lorsque
	// le desctructeur d'un noeud modifie l'arbre, par exemple en retirant
	// d'autres noeuds.  Il pourrait y avoir une boucle infinie si la
	// desctruction d'un enfant entraînerait l'ajout d'un autre.
	while (!enfants_.empty()) {
		NoeudAbstrait* enfantAEffacer{ enfants_.front() };
		enfants_.erase(enfants_.begin());
		delete enfantAEffacer;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::effacer( const NoeudAbstrait* noeud )
///
/// Efface un noeud qui est un enfant ou qui est contenu dans un des
/// enfants.
///
/// @param[in] noeud : Le noeud a effacer.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::effacer(const NoeudAbstrait* noeud)
{
	for (conteneur_enfants::iterator it{ enfants_.begin() };
		it != enfants_.end();
		it++) {
		if (*it == noeud) {
			// On a trouve le noeud a effacer
			if (noeud->obtenirType() == "bille")
				SingletonGlobal::obtenirInstance()->retirerBille();
			NoeudAbstrait* noeudAEffacer{ (*it) };
			enfants_.erase(it);
			delete noeudAEffacer;
			return;
		}
		else {
			// On cherche dans les enfants.
			(*it)->effacer(noeud);
		}
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudComposite::chercher( const std::string& typeNoeud ) const
///
/// Recherche un noeud d'un type donne parmi le noeud courant et ses
/// enfants.  Version constante de la fonction.
///
/// @param[in] typeNoeud : Le type du noeud cherche.
///
/// @return Noeud recherche ou 0 si le noeud n'est pas trouve.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudComposite::chercher(
	const std::string& typeNoeud
	) const
{
	if (typeNoeud == type_) {
		return this;
	}
	else {
		for (NoeudAbstrait const* enfant : enfants_)
		{
			NoeudAbstrait const* noeud{ enfant->chercher(typeNoeud) };
			if (noeud != nullptr) {
				return noeud;
			}
		}
	}

	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudComposite::chercher( const std::string& typeNoeud )
///
/// Recherche un noeud d'un type donne parmi le noeud courant et ses
/// enfants.
///
/// @param[in] typeNoeud : Le type du noeud cherche.
///
/// @return Noeud recherche ou 0 si le noeud n'est pas trouve.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudComposite::chercher(const std::string& typeNoeud)
{
	if (typeNoeud == type_) {
		return this;
	}
	else {
		for (NoeudAbstrait * enfant : enfants_)
		{
			NoeudAbstrait * noeud{ enfant->chercher(typeNoeud) };
			if (noeud != nullptr) {
				return noeud;
			}
		}
	}

	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudComposite::chercher( unsigned int indice ) const
///
/// Retourne le i-eme enfant, ou i est l'indice passe a la fonction.
/// Version constante de la fonction.
///
/// @param[in] indice : L'indice de l'enfant cherche.
///
/// @return Noeud recherche ou 0 si le noeud n'est pas trouve.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudComposite::chercher(unsigned int indice) const
{
	if ((indice >= 0) && (indice < enfants_.size())) {
		return enfants_[indice];
	}
	else {
		return nullptr;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudComposite::chercher( unsigned int indice )
///
/// Retourne le i-eme enfant, ou i est l'indice passe a la fonction.
///
/// @param[in] indice : L'indice de l'enfant cherche.
///
/// @return Noeud recherche ou 0 si le noeud n'est pas trouve.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudComposite::chercher(unsigned int indice)
{
	if ((indice >= 0) && (indice < enfants_.size())) {
		return enfants_[indice];
	}
	else {
		return nullptr;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudComposite::ajouter( NoeudAbstrait* enfant )
///
/// Ajoute un noeud enfant au noeud courant.
///
/// @param[in] enfant: Noeud a ajouter.
///
/// @return Vrai si l'ajout a reussi, donc en tout temps pour cette classe.
///
////////////////////////////////////////////////////////////////////////
bool NoeudComposite::ajouter(NoeudAbstrait* enfant)
{
	enfant->assignerParent(this);
	enfants_.push_back(enfant);

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudComposite::obtenirDernierNoeud()
///
/// Cette fonction retourne le plus recent objet rajouter.
///
/// @return this.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudComposite::obtenirDernierNoeud()
{
	return this;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudComposite::obtenirNombreEnfants() const
///
/// Retourne le nombre d'enfants directement sous ce noeud.  Elle ne
/// donne pas le nombre total de descendants, mais bien le nombre de
/// ceux qui sont directement sous ce noeud.
///
/// @return Le nombre d'enfants directement sous ce noeud.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudComposite::obtenirNombreEnfants() const
{
	// La taille ne doit jamais etre negative, sinon le cast plus bas
	// donnera un resultat errone.
	assert(enfants_.size() >= 0);

	return static_cast<unsigned int> (enfants_.size());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudComposite::obtenirNombreEnfants() const
///
/// Retourne le nombre d'enfants directement sous ce noeud.  Elle ne
/// donne pas le nombre total de descendants, mais bien le nombre de
/// ceux qui sont directement sous ce noeud.
///
/// @return Le nombre d'enfants directement sous ce noeud.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudComposite::getEnfant(int i)
{ 
	if (enfants_.size() > i)
		return enfants_[i];
	else
		return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::selectionnerTout()
///
/// Selectionne tous les noeuds qui sont selectionnes parmis les
/// les descendants de ce noeud, lui-meme etant inclus.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::selectionnerTout()
{
	NoeudAbstrait::selectionnerTout();

	for (NoeudAbstrait * enfant : enfants_){
		enfant->selectionnerTout();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::deselectionnerTout()
///
/// Deselectionne tous les noeuds qui sont selectionnes parmis les
/// les descendants de ce noeud, lui-meme etant inclus.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::deselectionnerTout()
{
	selectionne_ = false;

	for (NoeudAbstrait * enfant : enfants_){
		enfant->deselectionnerTout();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudComposite::selectionExiste() const
///
/// Verifie si le noeud ou un de ses descendants est selectionne en
/// s'appelant de maniere recursive sur les enfants du noeud.
///
/// @return Vrai s'il existe un noeud selectionne, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudComposite::selectionExiste() const
{
	if (selectionne_) {
		return true;
	}

	for (NoeudAbstrait const* enfant : enfants_){
		if (enfant->selectionExiste())
			return true;
	}

	return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::changerModePolygones( bool estForce )
///
/// Change le mode d'affichage des polygones pour ce noeud et ses
/// enfants.
///
/// @param[in] estForce : Si vrai, le mode est change pour ce noeud et
///                       tous ses descendants.  Sinon, seuls les noeuds
///                       selectionnes verront leur mode changer.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::changerModePolygones(bool estForce)
{
	NoeudAbstrait::changerModePolygones(estForce);
	const bool forceEnfant = ((estForce) || (estSelectionne()));

	// Applique le changement recursivement aux enfants.
	for (NoeudAbstrait * enfant : enfants_){
		enfant->changerModePolygones(forceEnfant);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::assignerModePolygones( GLenum modePolygones )
///
/// Cette fonction assigne le mode de rendu des polygones du noeud et
/// de ses enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::assignerModePolygones(GLenum modePolygones)
{
	// Appel a la version de la classe de base.
	NoeudAbstrait::assignerModePolygones(modePolygones);

	// Applique le changement recursivement aux enfants.
	for (NoeudAbstrait * enfant : enfants_){
		enfant->assignerModePolygones(modePolygones);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.  Elle est
/// appelee par la template method (dans le sens du patron de conception,
/// et non des template C++) afficher() de la classe de base.
///
/// Pour cette classe, elle affiche chacun des enfants du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::afficherConcret() const
{
	NoeudAbstrait::afficherConcret();

	for (NoeudAbstrait const* enfant : enfants_){
		enfant->afficher();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudComposite::animer( float dt )
///
/// Anime tous les enfants de ce noeud.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudComposite::animer(float dt)
{
	for (NoeudAbstrait * enfant : enfants_){
		enfant->animer(dt);
	}
	positionRelative_.z = abs(obtenirVecteursEnglobants()[0].z);
}


////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
