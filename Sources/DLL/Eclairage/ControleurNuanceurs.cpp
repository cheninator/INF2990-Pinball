///////////////////////////////////////////////////////////////////////////////
/// @file ControleurNuanceurs.cpp
/// @author The ballers
/// @date 2015-03-20
/// @version 1.0
///
/// @ingroup Eclairage
///////////////////////////////////////////////////////////////////////////////

#include "ControleurNuanceurs.h"
#include "../../Commun/Utilitaire/OpenGL/OpenGL_Programme.h"

#include <iostream>

ControleurNuanceurs* ControleurNuanceurs::instance_{ nullptr };

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurNuanceurs* ControleurNuanceurs::obtenirInstance() 
/// 
/// @brief Accesseur de l'instance unique du singleton
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
ControleurNuanceurs* ControleurNuanceurs::obtenirInstance()
{
	if (instance_ == nullptr)
		instance_ = new ControleurNuanceurs();

	return instance_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::libererInstance() 
/// 
/// @brief Liberateur de l'instance unique
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::libererInstance()
{
	delete instance_;
	instance_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurNuanceurs::~ControleurNuanceurs()
/// 
/// @brief Destructeur prive
/// 
/// @remark Les destructeurs s'occuppent de relacher les ressources
/// OpenGL lies aux objets.
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
ControleurNuanceurs::~ControleurNuanceurs()
{
	desactiver();
	delete programme_;
	delete nuanceurSommets_;
	delete nuanceurFragments_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::initialiser() 
/// 
/// @brief Charge les fichiers .glsl contenant le code des nuanceurs,
/// les compile et les lient a des nuanceurs dans le serveur OpenGL.
/// Ensuite les nuanceurs sont lies au programme.
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::initialiser()
{
	// Initialiser le nuanceur de sommets
	nuanceurSommets_ = new opengl::Nuanceur();
	nuanceurSommets_->initialiser(opengl::Nuanceur::Type::NUANCEUR_VERTEX, "Nuanceurs/NuanceurSommetsINF2990.glsl");
	
	// Initialiser le nuanceur de fragments
	nuanceurFragments_ = new opengl::Nuanceur();
	nuanceurFragments_->initialiser(opengl::Nuanceur::Type::NUANCEUR_FRAGMENT, "Nuanceurs/NuanceurFragmentsINF2990.glsl");

	// Initialiser le programme
	programme_ = new opengl::Programme();
	programme_->initialiser();
	programme_->attacherNuanceur(*nuanceurSommets_);
	programme_->attacherNuanceur(*nuanceurFragments_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::activer()
/// 
/// @brief Active le programme de nuanceurs
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::activer()
{
	assert(programme_ != nullptr && "Activation d'un programme de nuanceurs pas initialise");
	opengl::Programme::Start(*programme_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::desactiver() 
/// 
/// @brief Desactive le programme de nuanceurs
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::desactiver()
{
	assert(programme_ != nullptr && "Desactivation d'un programme de nuanceurs pas initialise");
	opengl::Programme::Stop(*programme_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::assignerColorShift(int colorShift)
/// 
/// @brief Assigne la variable uniforme colorShift qui sert pour 
/// distinguer visuellement les palettes du joueur 2.
/// 
/// @param[in] colorShift 1 pour true, 0 pour false
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::assignerColorShift(int colorShift)
{
	programme_->assignerUniforme("colorShift", colorShift);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurNuanceurs::assignerEtatNoeud(int etat)
/// 
/// @brief Assigne la variable uniforme etatNoeud qui sert pour les 
/// etats selectionne, impossible, transparent, illumine.
/// 
/// @param[in] etat Voir animationNoeudsDefine.h pour les macros
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::assignerEtatNoeud(int etat)
{
	programme_->assignerUniforme("etatNoeud", etat);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::assignerNumeroNoeud(int numero) 
/// 
/// @brief Assigne la variable uniforme numeroNoeud qui pourrait servir
/// si on decidait de faire la selection par couleur.
/// 
/// @param[in] numero Numero du noeud pour selection par couleur
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::assignerNumeroNoeud(int numero)
{
	programme_->assignerUniforme("numeroNoeud", numero);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::assignerEtatAmbiante(int etat)
/// 
/// @brief Assigne la variable uniforme etatAmbiante qui sert a 
/// activer/desactiver la lumiere ambiante.
/// 
/// @param[in] etat : 1 pour ON, 0 pour OFF
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::assignerEtatAmbiante(int etat)
{
	programme_->assignerUniforme("etatAmbiante", etat);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::assignerEtatDirectionnelle(int etat)
/// 
/// @brief Assigne la variable uniforme etatDirectionnelle qui sert a 
/// activer/desactiver la lumiere directionnelle.
/// 
/// @param[in] etat : 1 pour ON, 0 pour OFF
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////	
void ControleurNuanceurs::assignerEtatDirectionnelle(int etat)
{
	programme_->assignerUniforme("etatDirectionnelle", etat);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::assignerEtatSpot(int etat)
/// 
/// @brief Assigne la variable uniforme etatSpot qui sert a 
/// activer/desactiver la lumiere spot.
/// 
/// @param[in] etat : 1 pour ON, 0 pour OFF
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////	
void ControleurNuanceurs::assignerEtatSpot(int etat)
{
	programme_->assignerUniforme("etatSpot", etat);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::assignerSkybox(int skybox)
/// 
/// @brief Dit au nuanceur si le fragment vient de la scene ou du skybox.
/// 
/// @param[in] skybox : 1 skybox, 0 pour pas skybox
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////	
void ControleurNuanceurs::assignerSkybox(int skybox)
{
	programme_->assignerUniforme("skybox", skybox);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::assignerEstTable(int estTable)
/// 
/// @brief Dit au nuanceur si le fragment vient de la scene ou du skybox.
///
/// @param[in] estTable : Si la noeud est une table
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////	
void ControleurNuanceurs::assignerEstTable(int estTable)
{
	programme_->assignerUniforme("estTable", estTable);
}