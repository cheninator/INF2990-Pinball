////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.cpp
/// @author INF2990
/// @date   2014-08-16
///
/// @ingroup Interface
////////////////////////////////////////////////
#include <fmod.h>

#include "FacadeInterfaceNative.h"
#include "FacadeModele.h"

#include "glm\glm.hpp"
#include "FacadeModele.h"
#include "AideGL.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"

#include <iostream>
#include "BancTests.h"



extern "C"
{
	// TO DO : SUPPRIMER CETTE VARIABLE QUAND PLUS NECESSAIRE
	static NoeudAbstrait* objet = new NoeudAbstrait();
	static NoeudAbstrait* objet_temp = new NoeudAbstrait();

	static double theta = 0; ///< Angle Theta
	static double phi = 0;  /// < angle Phi

	static NoeudAbstrait* objetCourrant = new NoeudAbstrait();

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl trouverObjetSousPointClique(int i, int j)
	///
	/// Appel la fonction trouverObjetSousPointClique
	///
	/// @param[in] i: valeur en i dans l'ecran
	/// @param[in] j: valeur en j dans l'ecran
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl selectionnerObjetSousPointClique(int i, int j, int hauteur, int largeur, bool ctrlDown)
	{
		return FacadeModele::obtenirInstance()->selectionnerObjetSousPointClique(i, j, hauteur, largeur, ctrlDown);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	///
	/// Cette fonction initialise un contexte OpenGL dans la fenêtre
	/// identifiée par le handle passé en paramètre.  Cette fonction doit
	/// être la première à être appelée, car la création de l'objet du modèle
	/// C++ s'attend à avoir un contexte OpenGL valide.
	///
	/// @param[in] handle : Le handle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	{
		if (handle == nullptr)
			return;

		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND)handle);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl libererOpenGL()
	///
	/// Cette fonction libère le contexte OpenGL. Cette fonction doit être la
	/// dernière à être appelée, car elle libère également l'objet du modèle
	/// C++.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();

		// Désinitialisation de la façade.  Le fait de le faire après la
		// désinitialisation du contexte OpenGL aura pour conséquence que la
		// libération des listes d'affichages, par exemple, sera faite une fois que
		// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl dessinerOpenGL()
	///
	/// Cette fonction affiche la scène.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dessinerOpenGL()
	{
		// Affiche la scène.
		FacadeModele::obtenirInstance()->afficher();
		// Temporaire: pour détecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	///
	/// Cette fonction doit être appelée lorsque la fenêtre est
	/// redimensionnée afin d'ajuster les paramètres de la machine à états
	/// d'OpenGL pour correspondre aux nouvelles dimensions de la fenêtre.
	///
	/// @param[in] largeur : La nouvelle largeur de la fenêtre.
	/// @param[in] hauteur : La nouvelle hauteur de la fenêtre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(
			glm::ivec2{ 0, 0 },
			glm::ivec2{ largeur, hauteur }
		);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl animer(double temps)
	///
	/// Cette fonction effectue les différents calculs d'animations
	/// nécessaires pour le mode jeu, tel que les différents calculs de
	/// physique du jeu.
	///
	/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animer(double temps)
	{
		FacadeModele::obtenirInstance()->animer((float)temps);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomIn()
	///
	/// Cette fonction applique un zoom avant sur le présent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomIn()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomOut()
	///
	/// Cette fonction applique un zoom arrière sur le présent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOut()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	///
	/// Cette fonction permet d'obtenir le nombre d'affichages par seconde.
	///
	/// @return Le nombre d'affichage par seconde.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	{
		return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl executerTests()
	{
		bool reussite = BancTests::obtenirInstance()->executer();
		return reussite ? 0 : 1;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl creerObjet()
	///
	/// @param[in]  value : Nom de l'objet
	/// @param[in]  length : Taille du nom de l'objet
	/// @param[in]  twin : si a un jumeau
	/// @param[in]  colorShift : la couleur
	///
	/// Cette fonction permet de cree un objet 3D
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl creerObjet(char* value, int length, bool isTwin, bool colorShift)
	{
		
		std::string nomObjet(value);
		if (isTwin == true) {
			objet_temp = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(nomObjet);
			objet_temp->setColorShift(colorShift);
			if (objet == nullptr)
				return;
			objet_temp->setTwin(objet);
			objet->setTwin(objet_temp);
			objet->assignerSelection(true);
			objet->setTransparent(true);
			objet = objet_temp;
		}
		else 
		{
			objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(nomObjet);
			if (objet == nullptr)
				return;
			objet->setColorShift(colorShift);
			if (nomObjet == "mur")
			{
				objet->assignerSelection(false);
			}
		}
		
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->ajouter(objet);

	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl creerObjetAvecTests()
	///
	/// @param[in]  value : Nom de l'objet
	/// @param[in]  length : Taille du nom de l'objet
	/// @param[in]  twin : si a un jumeau
	/// @param[in]  colorShift : la couleur
	/// @param[in]  posX : la position en X de l'objet a créer.
	/// @param[in]  posY : la position en Y de l'objet a créer.
	/// @param[in]  posZ : la position en Z de l'objet a créer.
	/// @param[in]  angleX : l'angle en X de l'objet a créer.
	/// @param[in]  angleY : l'angle en Y de l'objet a créer.
	/// @param[in]  angleZ : l'angle en Z de l'objet a créer.
	///
	/// Cette fonction permet de cree un objet 3D
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl creerObjetAvecTests(char* value, int length, bool isTwin, bool colorShift, 
															int posX, int posY, int posZ, 
															float angleX, float angleY, float angleZ)
	{
		// Même chose que dans creer objet, sauf que je test le nouvel objet avant de l'ajouter à l'arbre.
		// Pour pouvoir tester l'objet avant de l'ajouter, je dois setter ses propriétés

		// Comme avant
		// ============
		std::string nomObjet(value);
		if (isTwin == true) {
			objet_temp = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(nomObjet);
			objet_temp->setColorShift(colorShift);
			if (objet == nullptr)
				return false;
			objet_temp->setTwin(objet);
			objet->setTwin(objet_temp);
			objet->assignerSelection(true);
			objet->setTransparent(true);
			objet = objet_temp;
		}
		else
		{
			objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(nomObjet);
			if (objet == nullptr)
				return false;
			objet->setColorShift(colorShift);
			if (nomObjet == "mur")
			{
				objet->assignerSelection(true);
			}
		}
		

		// Assigner les propriétés à l'objet
		// =================================
		
		// Assigner position et angles à l'objet.
		glm::dvec3 positionObjet;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(posX, posY, positionObjet);
		objet->assignerPositionRelative(positionObjet);

		// Voir la fonction rotate, c'est comme ça que les angles sont settés dans cette fonction.
		// if('Y') if (direction == 'y' || direction == 'Y' || direction == '1')
		// objet->assignerRotation({ angle, 0.0, 0.0 });
		// et en effet, si je mettais {angleX,angleY,angleZ} les palettes n'apparaiteraient pas.
		glm::dvec3 anglesObjet{ angleY, angleZ, angleX };
		objet->assignerRotation(anglesObjet);
		

		// Tester si l'objet est légal.
		// =============================
		bool objetEstLegal = true;
		glm::dvec3 boite[4];
		objet->obtenirVecteursBoite(boite[0], boite[1], boite[2], boite[3]);
		glm::dvec3 pointATester;
		for (int i = 0; i < 4; i++)
		{
			pointATester = positionObjet + boite[i];
			if (!FacadeModele::obtenirInstance()->estDansTable(pointATester))
			{
				objetEstLegal = false;
			}

		}

		// Ajouter l'objet s'il est légal
		// ==============================

		if (objetEstLegal)
		{
			// Si l'objet est légal, l'ajouter à la table, sinon, on le scrap
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->ajouter(objet);
			return true;
		}
		else
		{
			// delete objet;
			// objet = nullptr;
			return false;
		}
		return true;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl positionObjet(int x, int y, int z)
	///
	/// @param[in]  x : La positon en x
	/// @param[in]  y : La positon en y
	/// @param[in]  z : La positon en z
	///
	/// Permet de deplacer un objet en x y et/ou z
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl positionObjet(int x, int y, int z)
	{
		if (objet == nullptr)
			return;
		glm::dvec3 maPosition;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, maPosition);
		if (maPosition.x > 108 && maPosition.x < 272 && maPosition.y > -190 && maPosition.y < 96) {
			objet->assignerPositionRelative({ maPosition.x, maPosition.y, z });
			std::cout << std::endl << "x: " << maPosition.x << "y: " << maPosition.y << "z: " << maPosition.z << std::endl;
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl translateObjet(int x, int y, int z)
	///
	/// @param[in]  x : La positon en x
	/// @param[in]  y : La positon en y
	/// @param[in]  z : La positon en z
	///
	/// Permet de deplacer un objet en x y et/ou z
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl translateObjet(int x, int y, int z)
	{
		if (objet == nullptr)
			return;
		glm::dvec3 maPositionPresente;
		maPositionPresente = objet->obtenirPositionRelative();
		objet->assignerPositionRelative({ maPositionPresente.x + x,
			maPositionPresente.y + y,
			0 });

	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::scaleObjet(double scale)
	///
	/// @param[in]  scale : La multiplication en x
	///
	/// Permet de resize un objet uniformement
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl scaleObjet(double scale)
	{
		if (objet == nullptr)
			return;
		objet->assignerEchelle({ scale, scale, scale });

	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::scaleObjet(double scale)
	///
	/// @param[in]  scale : La multiplication en x
	///
	/// Permet de resize un objet uniformement
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) void __cdecl addScaleObjet(int myScale)
	{
		if (objet == nullptr)
			return;
		glm::dvec3 monScalePresent;
		float deltaScale = (float)myScale;
		monScalePresent = objet->obtenirAgrandissement();
		monScalePresent.x += myScale / 10.0;
		monScalePresent.y += myScale / 10.0;
		monScalePresent.z += myScale / 10.0;
		if (monScalePresent.x < 0)
			monScalePresent.x -= myScale / 10.0;
		if (monScalePresent.y < 0)
			monScalePresent.y -= myScale / 10.0;
		if (monScalePresent.z < 0)
			monScalePresent.z -= myScale / 10.0;
		objet->assignerEchelle({ monScalePresent.x, monScalePresent.y, monScalePresent.z });
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::scaleObjetXYZ(double x, double y, double z)
	///
	/// @param[in]  x : La multiplication en x
	/// @param[in]  y : La multiplication en y
	/// @param[in]  z : La multiplication en z
	///
	/// Permet de resize un objet en x y z
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl scaleObjetXYZ(double x, double y, double z)
	{
		if (objet == nullptr)
			return;
		objet->assignerEchelle({ x, y, z });
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::rotate(float angle, char direction)
	///
	/// @param[in]  angle : L'angle de rotation
	/// @param[in]  direction : La direction dans la quel on applique la rotation.
	///
	/// Permet de faire tourner notre objet
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl rotate(float angle, char direction)
	{
		if (objet == nullptr)
			return;
		std::cout << direction;
		if (direction == 'x' || direction == 'X' || direction == '0')
			objet->assignerRotation({ 0.0, 0.0, angle });
		else if (direction == 'y' || direction == 'Y' || direction == '1')
			objet->assignerRotation({ angle, 0.0, 0.0 });
		else if (direction == 'z' || direction == 'Z' || direction == '2')
			objet->assignerRotation({ 0.0, angle, 0.0 });
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::resetObject(void)
	///
	/// Remet les donnees d'un objet a 0
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void resetObject(void)
	{
		if (objet == nullptr)
			return;
		objet->assignerPositionRelative({ 0, 0, 0 });
		objet->assignerEchelle({ 1, 1, 1 });
		objet->resetRotation();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::removeObject(void)
	///
	/// Remet les donnees d'un objet a 0
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void removeObject(void)
	{
		FacadeModele::obtenirInstance()->supprimer();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::purgeAll(void)
	///
	/// Detruit l'arbre de rendu
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void purgeAll(void)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->initialiser();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::translater(double deplacementX, double deplacementY)
	///
	/// @param[in]  deplacementX : Déplacement en pourcentage de la largeur.
	/// @param[in]  deplacementY : Déplacement en pourcentage de la hauteur.
	///
	/// Permet de faire un "pan" d'un certain pourcentage.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl translater(double deplacementX, double deplacementY)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(deplacementX, deplacementY);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl creerXML(char* path, int length)
	///
	/// @param[in]  position : Nom du path
	/// @param[in]  length : Taille du nom du path
	///
	/// Sauvegarde le path
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl creerXML(char* path, int length, int prop[6])
	{
		return FacadeModele::obtenirInstance()->creerXML(path, prop);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl ouvrirXML(char* path, int length)
	///
	/// @param[in]  position : Nom du path
	/// @param[in]  length : Taille du nom du path
	///
	/// Sauvegarde le path
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int* __cdecl ouvrirXML(char* path, int length)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->vider();
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->initialiserXML(std::string(path));

		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirProprietes();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl orbite(double x, double y)
	///
	/// @param[in]  x :
	/// @param[in]  y : 
	///
	/// Vue orbite TO DO, INCOMPLETE
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl orbite(double x, double y)
	{
		glm::dvec3 maPosition;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle((int)x, (int)y, maPosition);

		theta += maPosition.x / 100.0;
		phi += maPosition.y / 100.0;
		double dist = 200.0;

		// A revori avec phil
		FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().orbiterXY(phi, theta);
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void zoomElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
	///
	/// @param[in]  xCoin1 :
	/// @param[in]  yCoin1 :
	/// @param[in]  xCoin2 :
	/// @param[in]  yCoin2 : 
	///
	/// Permet de centrer l'écran sur la région définie par les points passés
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void zoomInElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
	{
		glm::dvec3 positionSouris1(xCoin1, yCoin1, 0.0);
		glm::dvec3 positionSouris2(xCoin2, yCoin2, 0.0);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xCoin1, yCoin1, positionSouris1);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xCoin2, yCoin2, positionSouris2);

		glm::ivec2 coin1(positionSouris1.x, positionSouris1.y);
		glm::ivec2 coin2(positionSouris2.x, positionSouris2.y);
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerInElastique(coin1, coin2);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void zoomElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
	///
	/// @param[in]  xCoin1 :
	/// @param[in]  yCoin1 :
	/// @param[in]  xCoin2 :
	/// @param[in]  yCoin2 : 
	///
	/// Permet de centrer l'écran sur la région définie par les points passés
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void zoomOutElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
	{
		glm::dvec3 positionSouris1(xCoin1, yCoin1, 0.0);
		glm::dvec3 positionSouris2(xCoin2, yCoin2, 0.0);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xCoin1, yCoin1, positionSouris1);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xCoin2, yCoin2, positionSouris2);

		glm::dvec2 coin1(positionSouris1.x, positionSouris1.y);
		glm::dvec2 coin2(positionSouris2.x, positionSouris2.y);
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOutElastique(coin1, coin2);
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl deplacerSelection(int x1, int y1, int x2, int y2)
	///		deplace les noeuds selectionnes d'un déplacement calculé en coordonnées du monde
	///		à partir des points initiaux et terminaux dans les coordonnées d'affichage OpenGL
	///
	///
	/// @param[in]  x1 : abcisse du point initial
	/// @param[in]  y1 : ordonnee du point initial
	///
	/// @param[in]  x2 : abcisse du point initial
	/// @param[in]  y2 : ordonnee du point initial
	///
	/// @return Aucun
	///
	/// @remark : On doit donner des x,y qui ont été transformés par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deplacerSelection(int x1, int y1, int x2, int y2)
	{
		FacadeModele::obtenirInstance()->deplacerSelection(x1, y1, x2, y2);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl tournerSelectionSouris(int x1, int y1, int x2, int y2)
	///		L'angle de rotation est calculé à partir du déplacement
	///
	/// @param[in]  x1 : abcisse du point initial
	/// @param[in]  y1 : ordonnee du point initial
	///
	/// @param[in]  x2 : abcisse du point initial
	/// @param[in]  y2 : ordonnee du point initial
	///
	/// @return Aucun
	///
	/// @remark : On doit donner des x,y qui ont été transformés par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl tournerSelectionSouris(int x1, int y1, int x2, int y2)
	{
		FacadeModele::obtenirInstance()->tournerSelectionSouris(x1, y1, x2, y2);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl agrandirSelection(int x1, int y1, int x2, int y2)
	///
	/// @param[in]  x1 : abcisse du point initial
	/// @param[in]  y1 : ordonnee du point initial
	///
	/// @param[in]  x2 : abcisse du point initial
	/// @param[in]  y2 : ordonnee du point initial
	///
	/// @return Aucun
	///
	/// @remark : On doit donner des x,y qui ont été transformés par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl agrandirSelection(int x1, int y1, int x2, int y2)
	{
		FacadeModele::obtenirInstance()->agrandirSelection(x1, y1, x2, y2);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl 
	///
	/// @return Aucun
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl rectangleElastique(int i, int j)
	{
		FacadeModele::obtenirInstance()->rectangleElastique(i, j);
	}

	__declspec(dllexport) int __cdecl selectionMultiple(bool c)
	{
		return FacadeModele::obtenirInstance()->selectionMultiple(c);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl verifierCliqueDansTable(int x, int y)
	///
	/// @param[in]  x : abcisse du point initial 
	/// @param[in]  y : ordonnee du point initial
	///
	/// @return Aucun
	///
	/// @remark : On doit donner des x,y qui ont été transformés par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool verifierCliqueDansTable(int x, int y)
	{
		return FacadeModele::obtenirInstance()->verifierCliqueDansTable(x, y);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport)  void deselectAll(void)
	/// @return Aucun
	///
	/// @remark : Ca deselectionne tout
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void deselectAll(void)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->deselectionnerTout();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport)  void dupliquer(void)
	/// @return Aucun
	///
	/// @remark : Ça duplique les objets selectionnés
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dupliquerSelection(int i, int j)
	{
		FacadeModele::obtenirInstance()->dupliquerSelection(i, j);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport)  int getPositionX(void)
	/// @return la position en X
	///
	/// @remark : 
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getPositionX(void) {
		double positionX = 0;
		if (objet == nullptr)
			return false;
		
		for (unsigned int j = 0; j < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants(); j++)
		{
			if (
				FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j)->estSelectionne()
				) {
				objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j);
				positionX = objet->obtenirPositionRelative().x;
			}
		}
		
		return positionX;
	}



	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport)  int getPositionY(void)
	/// @return la position en Y
	///
	/// @remark : 
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getPositionY(void) {
		double positionY = 0;
		if (objet == nullptr)
			return false;
		for (unsigned int j = 0; j < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants(); j++)
		{
			if (
				FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j)->estSelectionne()
				) {
				objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j);
				positionY = objet->obtenirPositionRelative().y;
				
			}
		}

		return positionY;
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport)  int getAngle(void)
	/// @return l'angle de l'objet
	///
	/// @remark : 
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getAngle(void)
	{
		if (objet == nullptr)
			return false;
		double angle=0;
		for (unsigned int j = 0; j < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants(); j++)
		{
			if (
				FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j)->estSelectionne()
				) {
				objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j);
				angle = objet->obtenirRotation().z;
			}
		}

		return  angle;
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport)  int getScale(void)
	/// @return la taille de l'objet
	///
	/// @remark : 
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getScale(void)
	{
		double scale =0;
		if (objet == nullptr)
			return false;
		for (unsigned int j = 0; j < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants(); j++)
		{
			if (
				FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j)->estSelectionne()
				) {
				objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j);
				scale = objet->obtenirAgrandissement().y;
			}
		}

		return  scale;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl playSound()
	///
	/// @param[in]  value : Nom du son
	/// @param[in]  length : Taille du nom
	///
	/// Cette fonction permet de jouer un son ou de l'arreter
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) void __cdecl playSound(char* value, int length, bool stop)
	{
		// MERCI
		// http://openclassrooms.com/courses/apprenez-a-programmer-en-c/jouer-du-son-avec-fmod
		// MUCH LOVE
		static FMOD_SYSTEM* system;
		static bool init = false;
		static std::vector< std::pair<std::string, FMOD_SOUND *> > soundTable;
		std::string playing(value) ;

		if (init == false)
		{
			FMOD_System_Create(&system);
			FMOD_System_Init(system, 1024, FMOD_INIT_NORMAL, NULL);
			init = true;

			// Initialiser tout les bruits (fuck off, je fais pas d'usine);
			// Au debut, je voulais les initialiser au fur et a mesure des call
			// Mais ils prennent 3-4 sec a etre cree, a chaque fois, faik tu avais
			//  d'énorme delay c'etais chiant...
			std::pair<std::string, FMOD_SOUND *> apair0("media/SFX/ambiant.wav", NULL);
			soundTable.push_back(apair0);
			FMOD_System_CreateSound(system, "media/SFX/ambiant.wav", FMOD_CREATESAMPLE, 0, &soundTable.back().second);

			std::pair<std::string, FMOD_SOUND *> apair1("media/SFX/music.wav", NULL);
			soundTable.push_back(apair1);
			FMOD_System_CreateSound(system, "media/SFX/music.wav", FMOD_LOOP_NORMAL, 0, &soundTable.back().second);

			std::pair<std::string, FMOD_SOUND *> apair2("media/SFX/no.wav", NULL);
			soundTable.push_back(apair2);
			FMOD_System_CreateSound(system, "media/SFX/no.wav", FMOD_CREATESAMPLE, 0, &soundTable.back().second);

			std::pair<std::string, FMOD_SOUND *> apair3("media/SFX/stone.wav", NULL);
			soundTable.push_back(apair3);
			FMOD_System_CreateSound(system, "media/SFX/stone.wav", FMOD_CREATESAMPLE, 0, &soundTable.back().second);
		}


		FMOD_CHANNELGROUP *canal;
		FMOD_System_GetMasterChannelGroup(system, &canal);
		if (stop) {
			FMOD_ChannelGroup_SetMute(canal, 1);
			return;
		}
		else {
			FMOD_ChannelGroup_SetMute(canal, 0);
			if (playing == "")
				return;
		}

		int i;
		for (i = 0; i < soundTable.size(); i++) {		
			if (soundTable[i].first == std::string(value)) {
					FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, soundTable[i].second, 0, NULL);

				return;
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl verifierCliqueDansTable(int x, int y)
	///
	/// @param[in]  x : abcisse du point initial 
	/// @param[in]  y : ordonnee du point initial
	///
	/// @return Aucun
	///
	/// @remark : On doit donner des x,y qui ont été transformés par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl obligerTransparence(bool transparence)
	{
		if (objet == nullptr)
			return;
		// Il faut faire un visiteur par contre
		objet->setTransparent(transparence);
		if (objet->getTwin() != NULL && objet->getTwin() != nullptr){
			objet->getTwin()->setTransparent(transparence);
			if (objet->getTwin()->getTwin() != NULL  && objet->getTwin() != nullptr)
				objet->getTwin()->getTwin()->setTransparent(transparence);
		}
	}

	__declspec(dllexport) void __cdecl initialiserRectangleElastique(int i, int j)
	{
		FacadeModele::obtenirInstance()->initialiserRectangleElastique(i, j);
	}

	__declspec(dllexport) void __cdecl terminerRectangleElastique()
	{
		FacadeModele::obtenirInstance()->terminerRectangleElastique();
	}
}

__declspec(dllexport) void creerMur(int originX, int originY,int x1, int y1, int x2, int y2)
{
	FacadeModele::positionnerMur(originX,originY,x1, y1, x2, y2, objet);
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) bool __cdecl setProprietesNoeud(int x, int y, int angle, double scale)
///
///	La fonction calcule la boite englobante de l'objet transformé, le calcul est différend pour les murs.
/// Il manque quelque chose pour le calcul des boîtes englobantes transformées des objets de type mur.
///
/// @param[in]  x : X en coordonnées du monde qu'on veut donner à notre noeud.
/// @param[in]  y : Y en coordonnées du monde qu'on veut donner à notre noeud.
/// @param[in]	angle : angle de rotation
///	@param[in]	scale: scale de l'objet
/// @return bool
///
///////////////////////////////////////////////////////////////////////////////
__declspec(dllexport) bool setProprietesNoeud(int x, int y, int angle, double scale)
{
	std::cout << "Appel de setProprietesNoeud(" << x << ", " << y << ", " << angle << ", " << scale << ")" << std::endl;
	// Obtenir la boite du modele
	// =============================

	// Calculer la position a assigner en coordonnées du monde.
	glm::dvec3 nouvellePosition{ x, y, 0 };
	// FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, nouvellePosition);
	bool nouvellesProprietesSontLegales = true;
	glm::dvec3 boite[4];
	glm::dvec3 positionObjet = objet->obtenirPositionRelative();
	objet->obtenirBoiteModele(boite[0], boite[1], boite[2], boite[3]);

	// Appliquer les nouvelles propriétés.
	glm::dmat3 echelle;
	glm::dvec3 scaleInitial = objet->obtenirAgrandissement();
	if (objet->getType() == "mur")
	{
		echelle = glm::dmat3{	glm::dvec3{ scaleInitial.x,	0,		0.0 },
								glm::dvec3{		 0,			scale,	0.0f },
								glm::dvec3{		0.0,		0.0,	scaleInitial.z } };
	}
	else
		echelle = glm::dmat3{ glm::dvec3{ scale, 0, 0.0 },
								glm::dvec3{ 0, scale, 0.0f },
								glm::dvec3{ 0.0, 0.0, scale } };
	double angleRadian = angle * 2 * 3.14156 /360 ;

	// Des "-" ici aussi... voir plus bas.
	glm::dmat3 rotation = glm::dmat3{	glm::dvec3{ cos(angleRadian), -sin(angleRadian), 0.0 },
										glm::dvec3{ sin(angleRadian), cos(angleRadian), 0.0f },
										glm::dvec3{		0.0,	0.0,		1.0 } };

	glm::dvec3 pointATester;
	
	if (1) // Pour désactiver le test pendant qu'on fait des expériences
	{
		for (int i = 0; i < 4; i++)
		{
			pointATester = nouvellePosition + rotation * ( echelle * boite[i]);
			if (!FacadeModele::obtenirInstance()->estDansTable(pointATester))
			{
				nouvellesProprietesSontLegales = false;
				std::cout << "L'application des proprietes refusee, on sortirait de la table" << std::endl;
				return false;
			}
		}
	}

	if (nouvellesProprietesSontLegales)
	{
		glm::dvec3 angles = objet->obtenirRotation();
		// J'ai l'impression que la fonction qui permet de get l'angle z du C# retourne -1*l'angle, essayez d'enlever le "-" dans la ligne suivante.
		// EXPÉRIENCE A FAIRE:  enlever le "-", placer un mur incliné pas trop long, 
		// Sélectionner le mur, et faire accepter tout de suite, 
		// revenir à l'outil selection, constater que le nouvel angle est -l'angle qu'on a setté avec assignerAngles()
		// Ou carrément, remplace l'angle par disons 25,
		// glm::dvec3 nouveauxAngles = glm::dvec3{ angles.x, angles.y, 25 }; // <========= DÉCOMMENTER ICI
		// Donc maintenant, tu sais que l'attribut angles est { qqch, qqch, 25 } 
		// mais si tu sélectionnes l'objet apres avoir setté son angle à 25, tu va voir -25 dans le textbox.
		glm::dvec3 nouveauxAngles = glm::dvec3{ angles.x, angles.y, angle }; // <========= ET COMMENTER ICI
		objet->assignerPositionRelative(nouvellePosition);
		objet->assignerRotationHard(nouveauxAngles);

		// traiter le mur de façon spéciale.
		if (objet->getType() == "mur")
			objet->assignerEchelle(glm::dvec3{ scaleInitial.x, scale, scaleInitial.z });
		else
			objet->assignerEchelle(glm::dvec3{ scale, scale, scale });

	}
	
	return true;

}

///////////////////////////////////////////////////////////////////////////////
///
/// @fn _declspec(dllexport) double obtenirZoomCourant(void)
///
/// @return La valeur du facteur de zoom appliquer sur la fenêtre
///
///////////////////////////////////////////////////////////////////////////////
__declspec(dllexport) double obtenirZoomCourant(void)
{
	if (FacadeModele::obtenirInstance() == nullptr)
		return -1;
	return FacadeModele::obtenirInstance()->obtenirZoomCourant();
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn _declspec(dllexport) int obtenirCentreMasseX(void) 
///
/// @return La valeur en X de centre de masse
///
///////////////////////////////////////////////////////////////////////////////
__declspec(dllexport) int obtenirCentreMasseX(void)
{
	return FacadeModele::obtenirInstance()->obtenirCentreMasseX();
}

///////////////////////////////////////////////////////////////////////////////
///
/// @fn _declspec(dllexport) int obtenirCentreMasseY(void) 
///
/// @return La valeur en Y de centre de masse
///
///////////////////////////////////////////////////////////////////////////////
__declspec(dllexport) int obtenirCentreMasseY(void)
{
	return FacadeModele::obtenirInstance()->obtenirCentreMasseY();
}


__declspec(dllexport) bool resetZoom(void)
{
	return FacadeModele::obtenirInstance()->appliquerZoomInitial();
}