////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.h
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
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
	__declspec(dllexport) void creerObjet(char* value, int length);
	__declspec(dllexport) void positionObjet(int x, int y, int z = 0);
	__declspec(dllexport) void scaleObjet(double scale);
	__declspec(dllexport) void scaleXYZObjet(double x, double y, double z);
	__declspec(dllexport) void rotate(float angle, char direction);
	__declspec(dllexport) void resetObject(void);
	__declspec(dllexport) void removeObject(void);
	__declspec(dllexport) void purgeAll(void);
	__declspec(dllexport) void translater(double deplacementX, double deplacementY);
}

#endif // __FACADE_INTERFACE_NATIVE_H__
