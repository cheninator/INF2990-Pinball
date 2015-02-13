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

	// DON'T ASK WHY
	static double facteurDeTransition; ///< Facteur de transition

	static double theta = 0; ///< Angle Theta
	static double phi = 0;  /// < angle Phi


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn static void calculerTransition(void)
	///
	/// Cette fonction interne permet d'assigner un facteur de
	/// transition (qui est une variable static interne a la librairie
	/// pour permettre de garder la meme "vitesse" de mouvement entre
	/// le rendu openGL et la fenetre ne pixel C#
	///
	/// @param[in] Aucun
	///
	/// @return Aucune. (assigne une valeur a une variable globale a l'interne)
	///
	////////////////////////////////////////////////////////////////////////
	static double calculerTransition(void)
	{
		glm::dvec3 positionZero;
		glm::dvec3 positionUn;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(0, 0, positionZero);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(100, 100, positionUn);
		facteurDeTransition = (((positionUn.y - positionZero.y) / 100) + ((positionUn.y - positionZero.y) / 100)) / (-2);
		return facteurDeTransition;
	}
	static NoeudAbstrait* objetCourrant = new NoeudAbstrait();


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) float __cdecl currentZoom(void)
	///
	/// Cette fonction interne permet d'assigner un facteur de
	/// transition (qui est une variable static interne a la librairie
	/// pour permettre de garder la meme "vitesse" de mouvement entre
	/// le rendu openGL et la fenetre ne pixel C#
	///
	/// @param[in] Aucun
	///
	/// @return La valeur du facteur de transition courant
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl currentZoom(void)
	{
		return calculerTransition();
	}

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
		calculerTransition();
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
		calculerTransition();
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
		calculerTransition();
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
		calculerTransition();
		if (facteurDeTransition < 0.1)
			zoomOut();
		calculerTransition();
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
		calculerTransition();
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
		calculerTransition();
		if (facteurDeTransition > 1)
			zoomIn();
		calculerTransition();
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
			std::cout << isTwin;
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
				objet->assignerSelection(true);
			}
		}
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->ajouter(objet);
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
		calculerTransition();
		glm::dvec3 maPosition;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, maPosition);
		if (maPosition.x > 108 && maPosition.x < 272 && maPosition.y > -190 && maPosition.y < 96) {
			objet->assignerPositionRelative({ maPosition.x, maPosition.y, z });
			std::cout << std::endl << "x: " << maPosition.x << "y: " << maPosition.y << "z: " << maPosition.z << std::endl;
		}
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
		calculerTransition();
		if (objet == nullptr)
			return;
		glm::dvec3 monScalePresent;
		float deltaScale = (float)myScale;
		monScalePresent = objet->obtenirAgrandissement();
		monScalePresent.x += myScale / 10.0 * facteurDeTransition;
		monScalePresent.y += myScale / 10.0 * facteurDeTransition;
		monScalePresent.z += myScale / 10.0 * facteurDeTransition;
		if (monScalePresent.x < 0)
			monScalePresent.x -= myScale / 10.0 * facteurDeTransition;
		if (monScalePresent.y < 0)
			monScalePresent.y -= myScale / 10.0 * facteurDeTransition;
		if (monScalePresent.z < 0)
			monScalePresent.z -= myScale / 10.0 * facteurDeTransition;
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
		calculerTransition();
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
		calculerTransition();
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
		calculerTransition();
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
		calculerTransition();
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
		calculerTransition();
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
		calculerTransition();
		glm::dvec3 maPosition;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle((int)x, (int)y, maPosition);

		theta += maPosition.x / 100.0;
		phi += maPosition.y / 100.0;
		double dist = 200.0;

		// A revori avec phil
		FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().orbiterXY(phi, theta);
		calculerTransition();
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
		calculerTransition();
		glm::dvec3 positionSouris1(xCoin1, yCoin1, 0.0);
		glm::dvec3 positionSouris2(xCoin2, yCoin2, 0.0);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xCoin1, yCoin1, positionSouris1);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xCoin2, yCoin2, positionSouris2);

		glm::ivec2 coin1(positionSouris1.x, positionSouris1.y);
		glm::ivec2 coin2(positionSouris2.x, positionSouris2.y);
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerInElastique(coin1, coin2);
		calculerTransition();
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
		calculerTransition();
		FacadeModele::obtenirInstance()->rectangleElastique(i, j);
	}

	__declspec(dllexport) int __cdecl selectionMultiple(bool c)
	{
		calculerTransition();
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
		double positionX;
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
		double positionY;
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
		double angle;
		for (unsigned int j = 0; j < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants(); j++)
		{
			if (
				FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j)->estSelectionne()
				) {
				objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j);
				angle = objet->obtenirRotation().z;
			}
		}

		return  -angle;
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
		double scale;
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
			FMOD_ChannelGroup_SetPaused(canal, 1);
			return;
		}
		else {
			FMOD_ChannelGroup_SetPaused(canal, 0);
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

__declspec(dllexport) void creerMur(int x1, int y1, int x2, int y2)
{
	for (unsigned int j = 0; j < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants(); j++)
	{
		if (
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j)->estSelectionne()
			) 
		{
			objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j);
			FacadeModele::FaireQuelquechose(x1, y1, x2, y2, objet);
		}
	}


}

