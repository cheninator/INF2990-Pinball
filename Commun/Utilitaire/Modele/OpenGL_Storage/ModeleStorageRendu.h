///////////////////////////////////////////////////////////////////////////////
/// @file ModeleStorageRendu.h
/// @author Martin Paradis
/// @date 2014-08-16
/// @version 1.0
///
/// @addtogroup modele Modele
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef __MODELE_STORAGE_RENDU_H__
#define __MODELE_STORAGE_RENDU_H__

namespace modele{

	///////////////////////////////////////////////////////////////////////////
	/// @class ModeleStorageRendu
	/// @brief Interface pour les classes permettant de charger de données sur
	/// la carte graphique en vue d'effectuer le rendu de modeèles 3D.
	///
	/// @author Martin Paradis
	/// @date 2014-08-16
	///////////////////////////////////////////////////////////////////////////
	class ModeleStorageRendu{
	public:
		/// Destructeur
		virtual ~ModeleStorageRendu() = default;

		/// Permet de charger les données/commandes sur la carte graphique
		virtual void storageCharger() = 0;
		/// Permet d'effectuer le dessin du modèle 3D
		virtual void dessiner() const = 0;
		/// Permet de relâcher les données/commandes sur la crate graphique
		virtual void storageRelacher() = 0;
	protected:
		ModeleStorageRendu() = default;
	};
}
#endif ///__MODELE_STORAGE_RENDU_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////