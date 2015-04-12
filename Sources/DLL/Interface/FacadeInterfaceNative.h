////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.h
/// @author INF2990
/// @date   2014-08-16
///
/// @ingroup Interface
////////////////////////////////////////////////

/** @defgroup Interface Interface
*	@ingroup Noyau
*/

#ifndef __FACADE_INTERFACE_NATIVE_H__
#define __FACADE_INTERFACE_NATIVE_H__

#include "NoeudAbstrait.h"
#include "../Global/SingletonGlobal.h"

extern "C" {

	__declspec(dllexport) void initialiserOpenGL(int * handle);
	__declspec(dllexport) void libererOpenGL();
	__declspec(dllexport) void dessinerOpenGL();

	__declspec(dllexport) void redimensionnerFenetre(int largeur, int hauteur);
	__declspec(dllexport) void translater(double deplacementX, double deplacementY);
	__declspec(dllexport) void animer(double temps);

	__declspec(dllexport) int  obtenirAffichagesParSeconde();

	__declspec(dllexport) void orbite(double phi, double theta);
	__declspec(dllexport) void utiliserCameraOrbite(bool utiliseOrbite);

	/// Pour implementer undo/redo
	__declspec(dllexport) void sauvegarderHistorique();
	__declspec(dllexport) void annulerModifications();
	__declspec(dllexport) void retablirModifications();
	__declspec(dllexport) void viderHistorique();
	__declspec(dllexport) bool possedeSuivant();
	__declspec(dllexport) bool possedePrecedent();
	__declspec(dllexport) int obtenirNombreSelection();

	
	__declspec(dllexport) void preparerUsineArbre(char* text, int length);
	__declspec(dllexport) void initialiserArbre();

	__declspec(dllexport) void supprimerBille();
	__declspec(dllexport) bool spotLight(int lum, bool state);
	__declspec(dllexport) void initialiserSingleton();
	__declspec(dllexport) void detruireSingleton();

	__declspec(dllexport) void animerJeu(bool animer);
	__declspec(dllexport) void rechargerArbre(bool recharger);

	__declspec(dllexport) void activerCustomConsole();
	__declspec(dllexport) BSTR obtenirCout();


	////////////////////////////		EDITION			//////////////////////////////////////////////////


	__declspec(dllexport) void creerObjet(char* value, int length, bool isTwin = false, bool colorShift = false);
	__declspec(dllexport) bool creerObjetAvecTests(char* value, int length, bool isTwin, bool colorShift, int posX, int posY, int posZ, float angleX, float angleY, float angleZ);
	__declspec(dllexport) void creerMur(int originX, int originY, int x1, int y1, int x2, int y2);

	__declspec(dllexport) void positionObjet(int x, int y, int z = 0);
	__declspec(dllexport) double getPositionX(void);
	__declspec(dllexport) double getPositionY(void);

	__declspec(dllexport) void addScaleObjet(int myScale);
	__declspec(dllexport) void scaleXYZObjet(double x, double y, double z);
	__declspec(dllexport) double getScale(void);

	__declspec(dllexport) void rotate(float angle, char direction = 'x');
	__declspec(dllexport) double getAngle(void);

	__declspec(dllexport) void resetObject(void);
	__declspec(dllexport) void removeObject(void);
	__declspec(dllexport) void purgeAll(void);

	__declspec(dllexport) void deselectAll(void);
	__declspec(dllexport) void selectAll(void);
	__declspec(dllexport) int selectionnerObjetSousPointClique(int i, int j, int largeur, int hauteur, bool ctrlDown = false);
	__declspec(dllexport) int selectionMultiple(bool c);

	__declspec(dllexport) void agrandirSelection(int x1, int y1, int x2, int y2);
	__declspec(dllexport) void deplacerSelection(int x1, int y1, int x2, int y2, bool duplication);
	__declspec(dllexport) void tournerSelectionSouris(int x1, int y1, int x2, int y2);
	__declspec(dllexport) void dupliquerSelection(int i, int j);

	__declspec(dllexport) bool verifierCliqueDansTable(int x, int y);
	__declspec(dllexport) void obligerTransparence(bool transparence);
	__declspec(dllexport) int obtenirCentreMasseX(void);
	__declspec(dllexport) int obtenirCentreMasseY(void);
	__declspec(dllexport) bool duplicationEstHorsTable();

	__declspec(dllexport) void rectangleElastique(int i, int j);
	__declspec(dllexport) void initialiserRectangleElastique(int i, int j);
	__declspec(dllexport) void terminerRectangleElastique();

	////////////////////////////////////////////////////////////////////////////////////////////////////////





	////////////////////////////		SAUVEGARDE			////////////////////////////////////////////////


	__declspec(dllexport) int creerXML(char* path, int length, int prop[6], bool force = false);
	__declspec(dllexport) int creerXMLString(std::string path, int prop[6], bool force = false);

	__declspec(dllexport) int* ouvrirXML(char* path, int length);
	__declspec(dllexport) int* ouvrirXMLString(std::string path);

	__declspec(dllexport) void creerFichierConfig(int config[12]);
	__declspec(dllexport) int* chargerFichierConfiguration();
	__declspec(dllexport) void creerFichierCampagne(char* nomFichier, int length);
	__declspec(dllexport) BSTR obtenirDerniereCampagne();

	__declspec(dllexport) void takeScreenShot(char* path, int length, bool square, int maxSize);
	__declspec(dllexport) bool setProprietesNoeud(int x, int y, int angle, double scale);
	__declspec(dllexport) int obtenirDiffulte(char* nomFichier, int length);
	__declspec(dllexport) int* obtenirProprietes(char* nomFichier, int length);

	__declspec(dllexport) int obtenirTouchePGJ1();
	__declspec(dllexport) int obtenirTouchePGJ2();
	__declspec(dllexport) int obtenirTouchePDJ1();
	__declspec(dllexport) int obtenirTouchePDJ2();
	__declspec(dllexport) int obtenirToucheRessort();
	__declspec(dllexport) int obtenirNombreDeBilles();
	__declspec(dllexport) int obtenirNombreDeBillesPerdus();
	__declspec(dllexport) int obtenirModeDoubleBille();
	__declspec(dllexport) int obtenirAffichageGlobal();

	__declspec(dllexport) void bloquerAffichageGlobal(int active);

	__declspec(dllexport) int obtenirPointsGagnerBille();
	__declspec(dllexport) int obtenirPointsGagnerPartie();
	__declspec(dllexport) int obtenirNombreDePointsDePartie();
	__declspec(dllexport) void resetNombreDePointsDePartie();
	__declspec(dllexport) int  obtenirNombreBillesCourante();
	__declspec(dllexport) void resetNombreBillesCourantes();

	///////////////////////////////////////////////////////////////////////////////////////////////





	////////////////////////////		ZOOM			///////////////////////////////////////////


	__declspec(dllexport) void zoomInElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2);
	__declspec(dllexport) void zoomOutElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2);

	__declspec(dllexport) bool resetZoom(void);
	__declspec(dllexport) double currentZoom(void);
	__declspec(dllexport) double obtenirZoomCourant(void);

	__declspec(dllexport) void zoomIn();
	__declspec(dllexport) void zoomOut();

	/////////////////////////////////////////////////////////////////////////////////////////////////





	////////////////////////////		SONS			/////////////////////////////////////////////


	__declspec(dllexport) void initialiserSon();

	__declspec(dllexport) void creeSon(char* value, int length);
	__declspec(dllexport) void jouerSon(char* value, int length, bool pause = false);
	__declspec(dllexport) void bouclerSon(char* value, int length, bool loop = true);

	__declspec(dllexport) void sourdine(bool mute = true);
	__declspec(dllexport) void arreterSon(char* value, int length);
	__declspec(dllexport) void arreterToutSons();

	__declspec(dllexport) void ajusterBGM(float pourcentage);
	__declspec(dllexport) void ajusterSFX(float pourcentage);

	/////////////////////////////////////////////////////////////////////////////////////////////////





	////////////////////////////		TEXTES			///////////////////////////////


	__declspec(dllexport) void refresh(int x, int y);
	__declspec(dllexport) void creeTexte(char* text, int lengthT, char* font, int lengthF);
	__declspec(dllexport) void updateText(char* oldText, int lengthO, char* newText, int lengthN);
	__declspec(dllexport) void resize(char* text, int length, int size);
	__declspec(dllexport) void changerCouleur(char* text, int length, float rouge, float vert, float bleu);
	__declspec(dllexport) void changerCouleurV(char* text, int length, float couleur[3]);
	__declspec(dllexport) void repositionner(char* text, int length, float x, float y);
	__declspec(dllexport) void suprimerText(char* text, int length);
	__declspec(dllexport) void afficherTextes(bool afficher = true);

	/////////////////////////////////////////////////////////////////////////////////////////////////





	////////////////////////////		JOUEURS/ JOUEURS VIRTUELS			///////////////////////////////


	__declspec(dllexport) void activerPalettesGJ1();
	__declspec(dllexport) void desactiverPalettesGJ1();
	__declspec(dllexport) void activerPalettesDJ1();
	__declspec(dllexport) void desactiverPalettesDJ1();

	__declspec(dllexport) void activerPalettesGJ2();
	__declspec(dllexport) void desactiverPalettesGJ2();
	__declspec(dllexport) void activerPalettesDJ2();
	__declspec(dllexport) void desactiverPalettesDJ2();

	__declspec(dllexport) void activerAI(bool actif);

	/////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif // __FACADE_INTERFACE_NATIVE_H__
