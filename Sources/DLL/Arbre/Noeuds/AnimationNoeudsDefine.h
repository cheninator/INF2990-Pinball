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
#define EPSILON_ANIMATION_NOEUD_COMPOSITE 1./30. + .1/30. * .1	// Si en dessous de 30fps (+10%), on n'anime plus
#define HAUTEUR_TABLE_NOEUD_COMPOSITE 0
#define TEMPS_ILLUMINATION_NOEUD_BUTOIR .5		// Temsp pendant le quel un butoir s'illumine

//Table
#define TRANSLATE_X_NOEUD_TABLE 200
#define TRANSLATE_Y_NOEUD_TABLE -50
#define TRANSLATE_Z_NOEUD_TABLE SingletonGlobal::obtenirInstance()->obtenirBoiteTable().coinMin.z

// Bille
#define VITESSE_MAX_NOEUD_BILLE 400.		// Vitesse maximale de la bille
#define MASSE_NOEUD_BILLE 30.				// Poids (en kg?) de la bille
#define FROTTEMENT_NOEUD_BILLE 10.		// Constante de frottement
#define GRAVITE_NOEUD_BILLE glm::dvec3{ 0, -utilitaire::GRAVITE  * MASSE_NOEUD_BILLE, 0 }	// Force de la gravite appliquer sur la bille
#define VITESSE_INITIALE_NORUD_BILLE { 0, 0, 0 }	// Vitesse initiale
#define TIME_IDLE_NOEUD_BILLE .5		// Temps que la bille ne bouge pas apres spawn

// Butoirs
#define FACTEUR_REBOND_BUTOIRE 1.3f

// ButoirCirculaire
#define SCALE_MAX_NOEUD_BUTOIRCIRCULAIRE 8./100.	// Pourcentage d'augmentation/raptissement maximal
#define TEMPS_DEMI_ANIMATION_NOEUD_BUTOIRCIRCULAIREE .5		// L'animation d'une demi animation dure 1/2 sec

// Cible
#define VITESSE_NOEUD_CIBLE 360./4.	// 1 tour toute les 4 secondes

// Couvercle
#define MARGE_NOEUD_COUVERCLE 6*2				// Une marge pour que le couvercle touche encore un peu a la table
#define INCLINAISON_NOEUD_COUVERCLE 90./6.	// Le niveau d'inclinaison (15 degrees)
#define TEMPS_ANIMATION_NOEUD_COUVERCLE 2.	// L'animation dure 2 sec
#define DEPLACEMENT_NOEUD_COUVERCLE (abs(SingletonGlobal::obtenirInstance()->obtenirBoiteTable().coinMax.x - SingletonGlobal::obtenirInstance()->obtenirBoiteTable().coinMin.x) - MARGE_NOEUD_COUVERCLE)
#define DEMIE_LARGEUR_NOEUD_COUVERCLE (abs(boite_.coinMax.x - boite_.coinMin.x) / 2.0)

// GenerateurBille
#define TEMPS_ANIMATION_NOEUD_GENERATEURBILLE 2.	// L'animation dure 2 sec (le shake)
#define TEMPS_ANIMATION_MOUVEMENT_NOEUD_GENERATEURBILLE .01	// L'animation par mouvement dure 0.2 sec
#define DISTANCE_MAX_NOEUD_GENERATEURBILLE	5		// Distance maximale de translation

// PortailTorus
#define VITESSE_NOEUD_PORTAIL_TORUS 360./2.	// 1 tour toute les 2 secondes

// Trou
#define VITESSE_NOEUD_TROU 360./4.	// 1 tour toute les 4 secondes

// Palettes
#define VITESSE_ANGULAIRE_PALETTE_ACTIVE 700 // 500 degres par seconde approximativement 9 degres par 60ieme de seconde.
#define VITESSE_ANGULAIRE_PALETTE_RETOUR 150 

// Portails
#define MASSE_NOEUD_PORTAIL 1000.0 // possiblement redefinir pour chaque portail dependant de leur scale

#endif //__ANIMATION_NOEUDS_DEFINE_H__