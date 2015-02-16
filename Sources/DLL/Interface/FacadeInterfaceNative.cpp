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
	/// Appel la fonction trouverObjetSousPointClique de FacadeModele
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
	/// Cette fonction initialise un contexte OpenGL dans la fenetre
	/// identifiee par le handle passe en parametre.  Cette fonction doit
	/// etre la premiere a etre appelee, car la creation de l'objet du modele
	/// C++ s'attend a avoir un contexte OpenGL valide.
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
		std::cout << std::endl << "Initialisatio de l'openGL en cours..." << std::endl;
		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND)handle);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl libererOpenGL()
	///
	/// Cette fonction libere le contexte OpenGL. Cette fonction doit etre la
	/// derniere a etre appelee, car elle libere egalement l'objet du modele
	/// C++.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();

		// Desinitialisation de la façade.  Le fait de le faire apres la
		// desinitialisation du contexte OpenGL aura pour consequence que la
		// liberation des listes d'affichages, par exemple, sera faite une fois que
		// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl dessinerOpenGL()
	///
	/// Cette fonction affiche la scene.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dessinerOpenGL()
	{
		// Affiche la scene.
		FacadeModele::obtenirInstance()->afficher();
		// Temporaire: pour detecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	///
	/// Cette fonction doit etre appelee lorsque la fenetre est
	/// redimensionnee afin d'ajuster les parametres de la machine a etats
	/// d'OpenGL pour correspondre aux nouvelles dimensions de la fenetre.
	///
	/// @param[in] largeur : La nouvelle largeur de la fenetre.
	/// @param[in] hauteur : La nouvelle hauteur de la fenetre.
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
	/// Cette fonction effectue les differents calculs d'animations
	/// necessaires pour le mode jeu, tel que les differents calculs de
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
	/// Cette fonction applique un zoom avant sur le present volume de vision.
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
	/// Cette fonction applique un zoom arriere sur le present volume de vision.
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
	/// Cette fonction permet d'executer l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont reussi, 1 si au moins un test a echoue
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
	///	Cree un objet sans initialiser ses proprietes.  La fonction C# qui
	/// L'appelle est responsable d'attribuer des proprietes.
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
				objet->assignerSelection(true);
			}
		}
		
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->ajouter(objet);

	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl creerObjetAvecTests()
	///
	/// Cette fonction contient toutes les etapes de la creation d'objet.
	/// Premierement, on fait quelques assignations specifiques aux portails et 
	/// aux murs. A la fin de ceci, l'objet est cree et on retient un pointeur
	/// vers celui ci dans la variable statique NoeudAbstrait* objet.
	///
	/// Ensuite, avant d'ajouter l'objet a l'arbre de rendu, on verifie qu'il 
	/// serait entierement dans la table en faisant un test sur les points
	/// de sa boite englobante.
	///
	/// Si chaque point de la boite englobante passe le test, on ajoute l'objet
	/// a l'arbre de rendu comme enfant de la table.  Sinon, on l'efface.
	///
	/// @param[in]  value : Nom de l'objet
	/// @param[in]  length : Taille du nom de l'objet
	/// @param[in]  twin : si a un jumeau
	/// @param[in]  colorShift : la couleur
	/// @param[in]  posX : la position en X de l'objet a creer.
	/// @param[in]  posY : la position en Y de l'objet a creer.
	/// @param[in]  posZ : la position en Z de l'objet a creer.
	/// @param[in]  angleX : l'angle en X de l'objet a creer.
	/// @param[in]  angleY : l'angle en Y de l'objet a creer.
	/// @param[in]  angleZ : l'angle en Z de l'objet a creer.
	///
	/// Cette fonction permet de cree un objet 3D
	///
	/// @return True si l'objet a ete cree, false si une des etapes de la creation
	///			a echoue.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl creerObjetAvecTests(char* value, int length, bool isTwin, bool colorShift, 
															int posX, int posY, int posZ, 
															float angleX, float angleY, float angleZ)
	{
		// Meme chose que dans creer objet, sauf que je test le nouvel objet avant de l'ajouter a l'arbre.
		// Pour pouvoir tester l'objet avant de l'ajouter, je dois setter ses proprietes

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
		

		// Assigner les proprietes a l'objet
		// =================================
		
		// Assigner position et angles a l'objet.
		glm::dvec3 positionObjet;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(posX, posY, positionObjet);
		objet->assignerPositionRelative(positionObjet);

		// Voir la fonction rotate, c'est comme ça que les angles sont settes dans cette fonction.
		// if('Y') if (direction == 'y' || direction == 'Y' || direction == '1')
		// objet->assignerRotation({ angle, 0.0, 0.0 });
		// et en effet, si je mettais {angleX,angleY,angleZ} les palettes n'apparaiteraient pas.
		glm::dvec3 anglesObjet{ angleY, angleZ, angleX };
		objet->assignerRotation(anglesObjet);
		

		// Tester si l'objet est legal.
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

		// Ajouter l'objet s'il est legal
		// ==============================

		if (objetEstLegal)
		{
			// Si l'objet est legal, l'ajouter a la table, sinon, on le scrap
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
		if (FacadeModele::obtenirInstance()->estDansTable(maPosition)) {
			objet->assignerPositionRelative({ maPosition.x, maPosition.y, z });
			// std::cout << std::endl << "x: " << maPosition.x << "y: " << maPosition.y << "z: " << maPosition.z << std::endl;
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
		// std::cout << direction;
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
	/// @param[in]  deplacementX : Deplacement en pourcentage de la largeur.
	/// @param[in]  deplacementY : Deplacement en pourcentage de la hauteur.
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
	/// Permet de centrer l'ecran sur la region definie par les points passes
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
	/// Permet de centrer l'ecran sur la region definie par les points passes
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
	///		deplace les noeuds selectionnes d'un deplacement calcule en coordonnees du monde
	///		a partir des points initiaux et terminaux dans les coordonnees d'affichage OpenGL
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
	/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deplacerSelection(int x1, int y1, int x2, int y2, bool duplication)
	{
		FacadeModele::obtenirInstance()->deplacerSelection(x1, y1, x2, y2, duplication);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl tournerSelectionSouris(int x1, int y1, int x2, int y2)
	///		L'angle de rotation est calcule a partir du deplacement
	///
	/// @param[in]  x1 : abcisse du point initial
	/// @param[in]  y1 : ordonnee du point initial
	///
	/// @param[in]  x2 : abcisse du point initial
	/// @param[in]  y2 : ordonnee du point initial
	///
	/// @return Aucun
	///
	/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl tournerSelectionSouris(int x1, int y1, int x2, int y2)
	{
		FacadeModele::obtenirInstance()->tournerSelectionSouris(x1, y1, x2, y2);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl agrandirSelection(int x1, int y1, int x2, int y2)
	///	Change l'echelle des objets selectionnes.  Chaque deplacement de 1 pixel vers le haut
	/// multiplie l'echelle courrante par 1.003, et chaque deplacement vers le bas divise
	///	par 1.003.
	///
	/// @param[in]  x1 : abcisse du point initial
	/// @param[in]  y1 : ordonnee du point initial
	///
	/// @param[in]  x2 : abcisse du point initial
	/// @param[in]  y2 : ordonnee du point initial
	///
	/// @return Aucun
	///
	/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl agrandirSelection(int x1, int y1, int x2, int y2)
	{
		FacadeModele::obtenirInstance()->agrandirSelection(x1, y1, x2, y2);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl a COMMENTER KIM
	///
	/// @return Aucun
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl rectangleElastique(int i, int j)
	{
		FacadeModele::obtenirInstance()->rectangleElastique(i, j);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl a COMMENTER KIM
	///
	/// @return Aucun
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl selectionMultiple(bool c)
	{
		return FacadeModele::obtenirInstance()->selectionMultiple(c);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl verifierCliqueDansTable(int x, int y)
	/// Verifie si un clic est dans la table.
	///
	/// @param[in]  x : abcisse du point initial 
	/// @param[in]  y : ordonnee du point initial
	///
	/// @return true si le clic est dans la table, faux sinon.
	///
	/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool verifierCliqueDansTable(int x, int y)
	{
		return FacadeModele::obtenirInstance()->verifierCliqueDansTable(x, y);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport)  void deselectAll(void) a COMMENTER
	///
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
	/// @fn __declspec(dllexport)  void dupliquer(void) a COMMENTER YONNI (ET KIM?)
	/// @return Aucun
	///
	/// @remark : Ça duplique les objets selectionnes
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dupliquerSelection(int i, int j)
	{
		FacadeModele::obtenirInstance()->dupliquerSelection(i, j);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport)  int getPositionX(void) 
	/// Retourne le x de la position du dernier objet selectionne qu'on a trouve 
	/// dans l'arbre.
	///
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
	/// Retourne le y de la position du dernier objet selectionne qu'on a trouve 
	/// dans l'arbre.
	///
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
	/// Retourne l'angleZ du dernier objet selectionne qu'on a trouve 
	/// dans l'arbre.
	///
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
	/// Retourne le scale du dernier objet selectionne qu'on a trouve 
	/// dans l'arbre.
	///
	/// @return la taille de l'objet
	///
	/// @remark : Le scale en y est representatif des objets normaux et des murs.
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
	/// @fn __declspec(dllexport) void __cdecl playSound() a COMMENTER?
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
			std::cout << "Chargement du son : " << std::endl;
			FMOD_System_Create(&system);
			FMOD_System_Init(system, 1024, FMOD_INIT_NORMAL, NULL);
			init = true;

			// Initialiser tout les bruits (fuck off, je fais pas d'usine);
			// Au debut, je voulais les initialiser au fur et a mesure des call
			// Mais ils prennent 3-4 sec a etre cree, a chaque fois, faik tu avais
			//  d'enorme delay c'etais chiant...
			std::cout << "  0,00%... ambiant.wav" << std::endl; 
			std::pair<std::string, FMOD_SOUND *> apair0("media/SFX/ambiant.wav", NULL);
			soundTable.push_back(apair0);
			FMOD_System_CreateSound(system, "media/SFX/ambiant.wav", FMOD_CREATESAMPLE, 0, &soundTable.back().second);
			std::cout << " 25,00%... music.wav" << std::endl;
			std::pair<std::string, FMOD_SOUND *> apair1("media/SFX/music.wav", NULL);
			soundTable.push_back(apair1);
			FMOD_System_CreateSound(system, "media/SFX/music.wav", FMOD_LOOP_NORMAL, 0, &soundTable.back().second);
			std::cout << " 50,00%... no.wav" << std::endl;
			std::pair<std::string, FMOD_SOUND *> apair2("media/SFX/no.wav", NULL);
			soundTable.push_back(apair2);
			FMOD_System_CreateSound(system, "media/SFX/no.wav", FMOD_CREATESAMPLE, 0, &soundTable.back().second);
			std::cout << " 75,00%... sound.wav" << std::endl;
			std::pair<std::string, FMOD_SOUND *> apair3("media/SFX/stone.wav", NULL);
			soundTable.push_back(apair3);
			FMOD_System_CreateSound(system, "media/SFX/stone.wav", FMOD_CREATESAMPLE, 0, &soundTable.back().second);
			std::cout << " 100%... tout les sons sont initialise" << std::endl;
			std::cout << "Fin du chargement du son !" << std::endl << std::endl;
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
	/// @fn __declspec(dllexport) void __cdecl obligerTransparence(bool transparence)
	///
	/// @param[in]  transparence : 
	///
	/// @return Aucun
	///
	/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
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


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl initialiserRectangleElastique(int i, int j) a COMMENTER KIM
	///
	/// @return Aucun
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserRectangleElastique(int i, int j)
	{
		FacadeModele::obtenirInstance()->initialiserRectangleElastique(i, j);
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl terminerRectangleElastique() a COMMENTER KIM
	///
	/// @return Aucun
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl terminerRectangleElastique()
	{
		FacadeModele::obtenirInstance()->terminerRectangleElastique();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  creerMur(int originX, int originY,int x1, int y1, int x2, int y2) 
	/// Cette fonction place un mur dont un bout est la où le bouton gauche de la souris a ete appuye, et
	/// l'autre bout est sous le curseur de la souris.
	///
	/// @param[in]  originX : Position en X où le bouton a ete appuye
	/// @param[in]  originX : Position en Y où le bouton a ete appuye
	/// @param[in]  x1 : Position en X precedant un deplacement de la souris
	/// @param[in]  Y1 : Position en Y precedant un deplacement de la souris
	/// @param[in]  x2 : Position en X apres un deplacement de la souris (position actuelle de la souris)
	/// @param[in]  y2 : Position en X apres un deplacement de la souris (position actuelle de la souris)
	///
	/// @return Aucun
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void creerMur(int originX, int originY,int x1, int y1, int x2, int y2)
	{
		FacadeModele::positionnerMur(originX,originY,x1, y1, x2, y2, objet);
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl setProprietesNoeud(int x, int y, int angle, double scale)
	///
	///	La fonction calcule la boite englobante de l'objet transforme, le calcul est differend pour les murs.
	/// Il manque quelque chose pour le calcul des boîtes englobantes transformees des objets de type mur.
	///
	/// @param[in]  x : X en coordonnees du monde qu'on veut donner a notre noeud.
	/// @param[in]  y : Y en coordonnees du monde qu'on veut donner a notre noeud.
	/// @param[in]	angle : angle de rotation
	///	@param[in]	scale: scale de l'objet
	/// @return bool
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool setProprietesNoeud(int x, int y, int angle, double scale)
	{
		// Calculer la position a assigner en coordonnees du monde.  Elle est deja en
		// coordonnees du monde car ce qui est dans les textBox, c'est l'attribut position du noeud.
		glm::dvec3 nouvellePosition{ x, y, 0 };
		bool nouvellesProprietesSontLegales = true;
		glm::dvec3 boite[4];
		glm::dvec3 positionObjet = objet->obtenirPositionRelative();
		objet->obtenirBoiteModele(boite[0], boite[1], boite[2], boite[3]);

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

		glm::dmat3 rotation = glm::dmat3{	glm::dvec3{ cos(angleRadian), -sin(angleRadian), 0.0 },
											glm::dvec3{ sin(angleRadian), cos(angleRadian), 0.0f },
											glm::dvec3{		0.0,	0.0,		1.0 } };

		glm::dvec3 pointATester;
		for (int i = 0; i < 4; i++)
		{
			// Appliquer les nouvelles proprietes.
			pointATester = nouvellePosition + rotation * (echelle * boite[i]);
			// Tester
			if (!FacadeModele::obtenirInstance()->estDansTable(pointATester))
			{
				nouvellesProprietesSontLegales = false;
				std::cout << "L'application des proprietes refusee, on sortirait de la table" << std::endl;
				return false;
			}
		}

		if (nouvellesProprietesSontLegales)
		{
			glm::dvec3 angles = objet->obtenirRotation();
			glm::dvec3 nouveauxAngles = glm::dvec3{ angles.x, angles.y, angle }; 
			objet->assignerPositionRelative(nouvellePosition);
			objet->assignerRotationHard(nouveauxAngles);

			// traiter le mur de façon speciale.
			if (objet->getType() == "mur")
				objet->assignerEchelle(glm::dvec3{ scaleInitial.x, scale, scaleInitial.z });
			else
				objet->assignerEchelle(glm::dvec3{ scale, scale, scale });
		}
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn _declspec(dllexport) double obtenirZoomCourant(void) a COMMENTER
	///
	/// @return La valeur du facteur de zoom appliquer sur la fenetre
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
	/// @fn _declspec(dllexport) int obtenirCentreMasseX(void)  a COMMENTER
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
	/// @fn _declspec(dllexport) int obtenirCentreMasseY(void)  a COMMENTER
	///
	/// @return La valeur en Y de centre de masse
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int obtenirCentreMasseY(void)
	{
		return FacadeModele::obtenirInstance()->obtenirCentreMasseY();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool resetZoom(void) a COMMENTER
	///
	/// @return La valeur en Y de centre de masse
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool resetZoom(void)
	{
		return FacadeModele::obtenirInstance()->appliquerZoomInitial();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool duplicationEstHorsTable() a COMMENTER
	///
	/// @return true si la souris la selection est hors table lors de la duplication
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool duplicationEstHorsTable()
	{
		return FacadeModele::obtenirInstance()->duplicationEstHorsTable();
	}


}// FIN DU extern "C"