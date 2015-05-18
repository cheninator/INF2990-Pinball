///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeud.h
/// @author Martin Bisson
/// @date 2007-01-28
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////

/** @defgroup Usine Usine
*	@ingroup Arbre
*/

#ifndef __ARBRE_USINES_USINENOEUD_H__
#define __ARBRE_USINES_USINENOEUD_H__


#include <string>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"

class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeud
/// @brief Classe de base abstraite des usines qui seront utilisees pour
///        creer les differents noeuds de l'arbre de rendu.
///
/// @author Martin Bisson
/// @date 2007-01-28
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeud
{
public:
   /// Destructeur vide declare virtuel pour les classes derivees.
   inline virtual ~UsineNoeud() {
	   liste_.storageRelacher();
   }

   /// Fonction a surcharger pour la creation d'un noeud.
   virtual NoeudAbstrait* creerNoeud() const = 0;

   /// Retourne le nom associe a l'usine
   inline const std::string& obtenirNom() const;


protected:
   /// Constructeur qui prend le nom associe a l'usine.
	UsineNoeud(const std::string& nomUsine, const std::string& nomModele) : nom_(nomUsine) {
		modele_.charger(nomModele);
		liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
		liste_.storageCharger();
	}

   /// Modele 3D correspondant a ce noeud.
   modele::Modele3D modele_;
   /// Storage pour le dessin du modele
   modele::opengl_storage::OpenGL_Liste liste_;

private:
   /// Le nom associe a l'usine
   std::string nom_;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& UsineNoeud::obtenirNom() const
///
/// Cette fonction retourne une chaine representante le nom associe a
/// l'usine.
///
/// @return Le nom associe a l'usine.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& UsineNoeud::obtenirNom() const
{
   return nom_;
}

#endif // __ARBRE_USINES_USINENOEUD_H__