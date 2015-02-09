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

extern "C" {

	__declspec(dllexport) void initialiserOpenGL(int * handle);
	__declspec(dllexport) void libererOpenGL();
	__declspec(dllexport) void dessinerOpenGL();
	__declspec(dllexport) void redimensionnerFenetre(int largeur, int hauteur);
	__declspec(dllexport) void animer(double temps);
	__declspec(dllexport) void zoomIn();
	__declspec(dllexport) void zoomOut();
	__declspec(dllexport) int  obtenirAffichagesParSeconde();
	__declspec(dllexport) bool executerTests();
	__declspec(dllexport) void creerObjet(char* value, int length, bool isTwin = false);
	__declspec(dllexport) void positionObjet(int x, int y, int z = 0);
	__declspec(dllexport) void translateObjet(int x, int y, int z = 0);
	__declspec(dllexport) void scaleObjet(double scale);
	__declspec(dllexport) void addScaleObjet(int myScale);
	__declspec(dllexport) void scaleXYZObjet(double x, double y, double z);
	__declspec(dllexport) void rotate(float angle, char direction = 'x');
	__declspec(dllexport) void resetObject(void);
	__declspec(dllexport) void removeObject(void);
	__declspec(dllexport) void purgeAll(void);
	__declspec(dllexport) void deselectAll(void);
	__declspec(dllexport) int getPositionX(void);
	__declspec(dllexport) int getPositionY(void);
	__declspec(dllexport) int getAngle(void);
	__declspec(dllexport) double getScale(void);
	__declspec(dllexport) void translater(double deplacementX, double deplacementY);
	__declspec(dllexport) int creerXML(char* path, int length, int prop[6]);
	__declspec(dllexport) int* ouvrirXML(char* path, int length);
	__declspec(dllexport) int selectionnerObjetSousPointClique(int i, int j, int largeur, int hauteur, bool ctrlDown = false);
	__declspec(dllexport) void agrandirSelection(int x1, int y1, int x2, int y2);
	__declspec(dllexport) void orbite(double phi, double theta);
	__declspec(dllexport) void deplacerSelection(int x1, int y1, int x2, int y2);
	__declspec(dllexport) void tournerSelectionSouris(int x1, int y1, int x2, int y2);
	__declspec(dllexport) void zoomInElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2);
	__declspec(dllexport) void zoomOutElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2);
	__declspec(dllexport) float currentZoom(void);
	__declspec(dllexport) void rectangleElastique(int x1, int y1, int x2, int y2);
	__declspec(dllexport) int selectionMultiple(void);
	__declspec(dllexport) bool verifierCliqueDansTable(int x, int y);
	__declspec(dllexport) void dupliquerSelection(int i, int j);

}

#endif // __FACADE_INTERFACE_NATIVE_H__
