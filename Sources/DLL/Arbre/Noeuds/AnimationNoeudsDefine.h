///////////////////////////////////////////////////////////////////////////////
/// @file AnimationNoeudsDefine.h
/// @author The Ballers
/// @date 2015-03-14
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////////

#ifndef __ANIMATION_NOEUDS_DEFINE_H__
#define __ANIMATION_NOEUDS_DEFINE_H__

#include "Utilitaire.h"

#define REFRESH_RATE 1./600.	// 600 fps

enum Etat { ALLER, RETOUR, INITIAL };
enum Direction { dirY, dirYX, dirX, dirXY, dirZ }; // Pour fonctionner avec le srand

// Composite
#define HAUTEUR_TABLE_NOEUD_COMPOSITE 10

// ButoirCirculaire
#define SCALE_MAX_NOEUD_BUTOIRCIRCULAIRE 8./100.	// Pourcentage d'augmentation/raptissement maximal
#define TEMPS_DEMI_ANIMATION_NOEUD_BUTOIRCIRCULAIREE .5		// L'animation d'une demi animation dure 1/2 sec

// Cible
#define VITESSE_NOEUD_CIBLE 360./4.	// 1 tour toute les 4 secondes

// Couvercle
#define MARGE_NOEUD_COUVERCLE 20.				// Une marge pour que le couvercle touche encore un peu a la table
#define INCLINAISON_NOEUD_COUVERCLE 45./2.	// Le niveau d'inclinaison (22.5 degrees)
#define TEMPS_ANIMATION_NOEUD_COUVERCLE 2.		// L'animation dure 2 sec

// GenerateurBille
#define TEMPS_ANIMATION_NOEUD_GENERATEURBILLE 2.	// L'animation dure 3 
#define TEMPS_ANIMATION_MOUVEMENT_NOEUD_GENERATEURBILLE .01	// L'animation par mouvement dure 0.2 sec
#define DISTANCE_MAX_NOEUD_GENERATEURBILLE	5		// Distance maximale de translation

// Trou
#define VITESSE_NOEUD_TROU 360./4.	// 1 tour toute les 4 secondes

#endif //__ANIMATION_NOEUDS_DEFINE_H__