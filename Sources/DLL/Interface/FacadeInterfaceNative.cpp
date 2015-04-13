////////////////////////////////////////////////
/// @file FacadeInterfaceNative.cpp
/// @author INF2990
/// @date 2014-08-16
///
/// @ingroup Interface
////////////////////////////////////////////////

// pour que ca arrete de chialer que gl.h est included avant glew.h
// Ca leur tenter pas de faire include glew.h dans gl.h ???
#include "GL/glew.h"
#include <gl/GLU.h>
#include <gl/GL.h>

#include "FacadeInterfaceNative.h"
#include "FacadeModele.h"
#include "../Text/ControleurTexte.h"

#include "glm\glm.hpp"
#include "FacadeModele.h"
#include "AideGL.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"

#include <string>	
#include <iomanip>
#include <iostream>

#include <ctime> // std::time
#include <cstdlib> // std::rand, std::srand
#include <windows.h>
#include "BancTests.h"
// SingletonGlobal::obtenirInstance()->outPutStream_
BSTR stringToBSTR(std::string str) {
	// http://www.sluse.com/view/6284524
	int wslen = ::MultiByteToWideChar(CP_ACP, 0 /* no flags */,
		str.data(), (int)str.length(),
		NULL, 0);

	BSTR wsdata = ::SysAllocStringLen(NULL, wslen);
	::MultiByteToWideChar(CP_ACP, 0 /* no flags */,
		str.data(), (int)str.length(),
		wsdata, wslen);
	return wsdata;
}

extern "C"
{
	// TO DO : SUPPRIMER CETTE VARIABLE QUAND PLUS NECESSAIRE
	// Nvm, c'est devenue une necesite, donc garder ces variables absolument
	static NoeudAbstrait* objet = new NoeudAbstrait();
	static NoeudAbstrait* objet_temp = new NoeudAbstrait();

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn int selectionnerObjetSousPointClique(int i, int j, int hauteur, int largeur, bool ctrlDown)
	///
	/// @remark Cette fonction permet de selectionner un objet. La methode regarde la valeur
	/// \remark du stencil et la donne a un visiteurSelection qui compare cette valeur
	/// \remark aux numeros des noeuds et change les met selectionnes ou pas selon le resultat
	/// \remark de la comparaison et selon qu'on a clique avec CTRL.
	///
	/// @param[in] i : Position souris i
	/// @param[in] j : Position souris j
	/// @param[in] hauteur : Hauteur de la fenetre
	/// @param[in] largeur : Largeur de la fenetre
	/// @param[in] ctrlDown : Si le bouton ctrl est appuie
	///
	/// @return NoeudAbstrait.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl selectionnerObjetSousPointClique(int i, int j, int hauteur, int largeur, bool ctrlDown, bool gaucheEnfonce, bool sourisSurSelection)
	{
		return FacadeModele::obtenirInstance()->selectionnerObjetSousPointClique(i, j, hauteur, largeur, ctrlDown, gaucheEnfonce, sourisSurSelection);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void initialiserOpenGL(int* handle)
	///
	/// @param[in] handle : Le handle.
	///
	/// @return Aucune.
	///
	/// @remark : Cette fonction initialise un contexte OpenGL dans la fenetre
	/// \remark identifiee par le handle passe en parametre. Cette fonction doit
	/// \remark etre la premiere a etre appelee, car la creation de l'objet du modele
	/// \remark C++ s'attend a avoir un contexte OpenGL valide.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	{
		if (handle == nullptr)
			return;
		std::cout << std::endl << "Initialisation de l'openGL en cours..." << std::endl;
		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND)handle);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void libererOpenGL()
	///
	/// @return Aucune.
	///
	/// @remark : Cette fonction libere le contexte OpenGL. 
	/// \remark Cette fonction doit etre la derniere a etre appelee,
	/// \remark car elle libere egalement l'objet du modele C++
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();

		/// Desinitialisation de la facade. Le fait de le faire apres la
		/// desinitialisation du contexte OpenGL aura pour consequence que la
		/// liberation des listes d'affichages, par exemple, sera faite une fois que
		/// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void dessinerOpenGL()
	///
	/// @return Aucune.
	///
	/// @remark : Cette fonction affiche la scene.
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
	/// @fn void redimensionnerFenetre(int largeur, int hauteur)
	///
	/// @param[in] largeur : La nouvelle largeur de la fenetre.
	/// @param[in] hauteur : La nouvelle hauteur de la fenetre.
	///
	/// @return Aucune.
	///
	/// @remark : Cette fonction doit etre appelee lorsque la fenetre est redimensionnee
	/// \remark afin d'ajuster les parametres de la machine a etats
	/// \remark d'OpenGL pour correspondre aux nouvelles dimensions de la fenetre.
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
	/// @fn void animer(double temps)
	///
	/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
	///
	/// @return Aucune.
	///
	/// @remark : Cette fonction effectue les differents calculs d'animations
	/// \remark necessaires pour le mode jeu, tel que les differents calculs de
	/// \remark physique du jeu.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animer(double temps)
	{
		FacadeModele::obtenirInstance()->animer((float)temps);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void zoomIn()
	///
	/// @return Aucune.
	///
	/// @remark : Cette fonction applique un zoom avant sur le present volume de vision.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomIn()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void zoomOut()
	///
	/// @return Aucune.
	///
	/// @remark : Cette fonction applique un zoom arriere sur le present volume de vision.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOut()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirAffichagesParSeconde()
	///
	/// @return Le nombre d'affichage par seconde.
	///
	/// @remark : Cette fonction permet d'obtenir le nombre d'affichages par seconde.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	{
		return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
	}

	/*
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool executerTests()
	///
	/// @return 0 si tous les tests ont reussi, 1 si au moins un test a echoue
	///
	/// @remark : Cette fonction permet d'executer l'ensemble des tests unitaires
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl executerTests()
	{
		bool reussite = BancTests::obtenirInstance()->executer();
		return reussite ? 0 : 1;
	}
	*/
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void creerObjet()
	///
	///
	/// @param[in] value : Nom de l'objet
	/// @param[in] length : Taille du nom de l'objet
	/// @param[in] twin : si a un jumeau
	/// @param[in] colorShift : la couleur
	///
	/// @return Aucun
	///
	/// @remark : Cette fonction permet de cree un objet 3D
	///	\remark Cree un objet sans initialiser ses proprietes.La fonction C# qui
	/// \remark L'appelle est responsable d'attribuer des proprietes.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl creerObjet(char* value, int, bool isTwin, bool colorShift)
	{
		std::string nomObjet(value);
		if (nomObjet == "bille")
		{
			if(FacadeModele::obtenirInstance()->preparerBille())
				SingletonGlobal::obtenirInstance()->ajouterBille();
			return;
		}
		if (isTwin == true) {
			if (objet == nullptr)
				return;
			objet_temp = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(nomObjet);
			objet_temp->setColorShift(colorShift);
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
		FacadeModele::obtenirInstance()->mettreAJourListeBillesEtNoeuds();
		FacadeModele::obtenirInstance()->construireListesPalettes();
		FacadeModele::obtenirInstance()->setDebug();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void creerObjetAvecTests()
	///
	/// @param[in] value : Nom de l'objet
	/// @param[in] length : Taille du nom de l'objet
	/// @param[in] twin : si a un jumeau
	/// @param[in] colorShift : la couleur
	/// @param[in] posX : la position en X de l'objet a creer.
	/// @param[in] posY : la position en Y de l'objet a creer.
	/// @param[in] posZ : la position en Z de l'objet a creer.
	/// @param[in] angleX : l'angle en X de l'objet a creer.
	/// @param[in] angleY : l'angle en Y de l'objet a creer.
	/// @param[in] angleZ : l'angle en Z de l'objet a creer.
	///
	/// @return True si l'objet a ete cree, false si une des etapes de la creation
	///			a echoue.
	///
	/// @remark : Cette fonction permet de cree un objet 3D.
	/// \remark Cette fonction contient toutes les etapes de la creation d'objet.
	/// \remark Premierement, on fait quelques assignations specifiques aux portails et 
	/// \remark aux murs. A la fin de ceci, l'objet est cree et on retient un pointeur
	/// \remark vers celui ci dans la variable statique NoeudAbstrait* objet.
	/// \remark 
	/// \remark Ensuite, avant d'ajouter l'objet a l'arbre de rendu, on verifie qu'il 
	/// \remark serait entierement dans la table en faisant un test sur les points
	/// \remark de sa boite englobante.
	/// \remark 
	/// \remark Si chaque point de la boite englobante passe le test, on ajoute l'objet
	/// \remark a l'arbre de rendu comme enfant de la table. Sinon, on l'efface.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl creerObjetAvecTests(char* value, int, bool isTwin, bool colorShift, 
															int posX, int posY, int, 
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
			objet->assignerSelection(false);
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

		// Voir la fonction rotate, c'est comme ca que les angles sont settes dans cette fonction.
		// if('Y') if (direction == 'y' || direction == 'Y' || direction == '1')
		// objet->assignerRotation({ angle, 0.0, 0.0 });
		// et en effet, si je mettais {angleX,angleY,angleZ} les palettes n'apparaiteraient pas.
		glm::dvec3 anglesObjet{ angleY, angleZ, angleX };
		objet->assignerRotation(anglesObjet);
		

		// Tester si l'objet est legal.
		// =============================
		bool objetEstLegal = true;
		/*glm::dvec3 boite[4];
		objet->obtenirVecteursBoite(boite[0], boite[1], boite[2], boite[3]);
		glm::dvec3 pointATester;
		for (int i = 0; i < 4; i++)
		{
			pointATester = positionObjet + boite[i];
			if (!FacadeModele::obtenirInstance()->estDansTable(pointATester))
			{
				objetEstLegal = false;
			}

		}*/

		// Ajouter l'objet s'il est legal
		// ==============================

		if (objetEstLegal)
		{
			// Si l'objet est legal, l'ajouter a la table, sinon, on le scrap
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->ajouter(objet);
			if (nomObjet == "portail")
				FacadeModele::obtenirInstance()->setDebug();

			objet->assignerSelection(true);

			return true;
		}
		else
		{
			// delete objet;
			// objet = nullptr;
			return false;
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void positionObjet(int x, int y, int z)
	///
	/// @param[in] x : La positon en x
	/// @param[in] y : La positon en y
	/// @param[in] z : La positon en z
	///
	/// @return Aucune.
	///
	/// @remark : Permet de deplacer un objet en x y et/ou z
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
	/// @fn void translateObjet(int x, int y, int z)
	///
	/// @param[in] x : La positon en x
	/// @param[in] y : La positon en y
	/// @param[in] z : La positon en z
	///
	/// @return Aucune.
	///
	/// @remark : Permet de deplacer un objet en x y et/ou z
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl translateObjet(int x, int y, int)
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
	/// @fn void scaleObjet(double scale)
	///
	/// @param[in] scale : La multiplication en x
	///
	/// @return Aucune.
	///
	/// @remark : Permet de resize un objet uniformement
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
	/// @fn void addScaleObjet(int myScale)
	///
	/// @param[in] myScale : La multiplication en x
	///
	/// @return Aucune.
	///
	/// @remark : Permet de rajouter un resize d'un objet uniformement
	///
	////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) void __cdecl addScaleObjet(int myScale)
	{
		if (objet == nullptr)
			return;
		glm::dvec3 monScalePresent;
		//float deltaScale = (float)myScale;
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
	/// @fn void scaleObjetXYZ(double x, double y, double z)
	///
	/// @param[in] x : La multiplication en x
	/// @param[in] y : La multiplication en y
	/// @param[in] z : La multiplication en z
	///
	/// 
	///
	/// @return Aucune.
	///
	/// @remark : Permet de resize un objet en x y z
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
	/// @fn void rotate(float angle, char direction)
	///
	/// @param[in] angle : L'angle de rotation
	/// @param[in] direction : La direction dans la quel on applique la rotation.
	///
	/// @return Aucune.
	///
	/// @remark : Permet de faire tourner notre objet
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
	/// @fn void resetObject( void )
	///
	/// @return Aucune.
	///
	/// @remark : Remet les donnees d'un objet a 0
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl resetObject( void )
	{
		if (objet == nullptr)
			return;
		objet->assignerPositionRelative({ 0, 0, 0 });
		objet->assignerEchelle({ 1, 1, 1 });
		objet->resetRotation();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void removeObject( void )
	///
	/// Remet les donnees d'un objet a 0
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl removeObject( void )
	{
		FacadeModele::obtenirInstance()->supprimer();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void purgeAll( void )
	///
	/// @return Aucune.
	///
	/// @remark : Detruit l'arbre de rendu
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl purgeAll( void )
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->initialiser();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void translater(double deplacementX, double deplacementY)
	///
	/// @param[in] deplacementX : Deplacement en pourcentage de la largeur.
	/// @param[in] deplacementY : Deplacement en pourcentage de la hauteur.
	///
	/// @return Aucune.
	///
	/// @remark : Permet de faire un "plan" d'un certain pourcentage.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl translater(double deplacementX, double deplacementY)
	{
		// Notez bien que cette valeur transmise est d'habitude de 10 depuis le C#

		/* Si la camera est orbite, on redirige la methode vers celle appropriee*/
		if (FacadeModele::obtenirInstance()->cameraEstOrbite())
			orbite(deplacementX/3.0, deplacementY/3.0);
		else
		{
			FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(deplacementX, deplacementY);
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void creerXML(char* path, int length, int prop[6])
	///
	/// @param[in] position : Nom du path
	/// @param[in] length : Taille du nom du path
	/// @param[in] prop : Proprietes de la zone de jeu
	///
	/// @remark : Sauvegarde le path
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl creerXML(char* path, int, int prop[6], bool force)
	{
		return FacadeModele::obtenirInstance()->creerXML(std::string(path), prop, force);
	}

	__declspec(dllexport) int __cdecl creerXMLString(std::string path, int prop[6], bool force)
	{
		 int valeur = FacadeModele::obtenirInstance()->creerXML(path, prop, force);
//		 FacadeModele::obtenirInstance()->construireQuadTree();
		 return valeur;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ouvrirXML(char* path, int length)
	///
	/// @param[in] path : Chemin du path
	/// @param[in] length : Taille du path
	///
	/// @return Aucun
	///
	/// @remark : Ouvre le path
	/// 
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int* __cdecl ouvrirXML(char* path, int)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->vider();
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->initialiserXML(std::string(path));
//		FacadeModele::obtenirInstance()->construireQuadTree();
		FacadeModele::obtenirInstance()->setDebug();
		FacadeModele::obtenirInstance()->construireListesPalettes();
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirProprietes();
	}
	__declspec(dllexport) int* __cdecl ouvrirXMLString(std::string path)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->vider();
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->initialiserXML(path);
		FacadeModele::obtenirInstance()->setDebug();
		FacadeModele::obtenirInstance()->construireListesPalettes();
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirProprietes();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void takeScreenShot(char* path, int length, bool square, int maxSize)
	///
	/// @param[in] path : Nom du path
	/// @param[in] length : Taille du nom du path
	/// @param[in] square : forme de l'image carre
	/// @param[in] maxSize : taille maximale (pixel) de l'image
	///
	/// @return Aucun
	///
	/// @remark : Prend un screenshot de la zone de jeu
	/// 
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl takeScreenShot(char* path, int, bool square, int maxSize)
	{
		glm::ivec2 size = FacadeModele::obtenirInstance()->obtenirTailleFenetre();
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->takeScreenShot(path, size.x, size.y, square, maxSize);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void orbite(double x, double y)
	///
	/// @param[in] x :	Rotation x
	/// @param[in] y : Rotation Y
	///
	/// Vue orbite TO DO, INCOMPLETE
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl orbite(double x, double y)
	{
		// Habituellement la valeur de x et y est de 10 depuis le C#
		/// En theta, pour correspondre a une rotation dans le sens de la fleche il faut envoyer l'oppose
		FacadeModele::obtenirInstance()->obtenirVue()->rotaterXY( -1 * x, y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void zoomInElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
	///
	/// @param[in] xCoin1 : Coin initial du zoom elastique en x
	/// @param[in] yCoin1 : Coin initial du zoom elastique en y
	/// @param[in] xCoin2 : Coin final du zoom elastique en x
	/// @param[in] yCoin2 : Coin final du zoom elastique en y
	///
	/// @return Aucun
	///
	/// @remark : Permet de centrer l'ecran sur la region definie par les points passes
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomInElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
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
	/// @fn void zoomOutElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
	///
	/// @param[in] xCoin1 : Coin initial du zoom elastique en x
	/// @param[in] yCoin1 : Coin initial du zoom elastique en y
	/// @param[in] xCoin2 : Coin final du zoom elastique en x
	/// @param[in] yCoin2 : Coin final du zoom elastique en y
	///
	/// Permet de centrer l'ecran sur la region definie par les points passes
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOutElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
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
	/// @fn void deplacerSelection(int x1, int y1, int x2, int y2)
	///		deplace les noeuds selectionnes d'un deplacement calcule en coordonnees du monde
	///		a partir des points initiaux et terminaux dans les coordonnees d'affichage OpenGL
	///
	///
	/// @param[in] x1 : abcisse du point initial
	/// @param[in] y1 : ordonnee du point initial
	///
	/// @param[in] x2 : abcisse du point initial
	/// @param[in] y2 : ordonnee du point initial
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
	/// @fn void tournerSelectionSouris(int x1, int y1, int x2, int y2)
	///		
	///
	/// @param[in] x1 : abcisse du point initial
	/// @param[in] y1 : ordonnee du point initial
	///
	/// @param[in] x2 : abcisse du point initial
	/// @param[in] y2 : ordonnee du point initial
	///
	/// @return Aucun
	///
	/// @remark : L'angle de rotation est calcule a partir du deplacement. On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl tournerSelectionSouris(int x1, int y1, int x2, int y2)
	{
		FacadeModele::obtenirInstance()->tournerSelectionSouris(x1, y1, x2, y2);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void agrandirSelection(int x1, int y1, int x2, int y2)
	///
	/// @param[in] x1 : abcisse du point initial
	/// @param[in] y1 : ordonnee du point initial
	///
	/// @param[in] x2 : abcisse du point initial
	/// @param[in] y2 : ordonnee du point initial
	///
	/// @return Aucun
	///
	/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...). La focntion change l'echelle des objets selectionnes. Chaque deplacement de 1 pixel vers le haut multiplie l'echelle courrante par 1.003, et chaque deplacement vers le bas divise par 1.003.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl agrandirSelection(int x1, int y1, int x2, int y2)
	{
		FacadeModele::obtenirInstance()->agrandirSelection(x1, y1, x2, y2);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void rectangleElastique(int i, int j)
	///
	/// @param[in] i : point suivant i de la souris
	/// @param[in] j : point suivant j de la souris
	///
	/// @return Aucun
	///
	/// @remark : Met a jour le rectangle elastique
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl rectangleElastique(int i, int j)
	{
		FacadeModele::obtenirInstance()->rectangleElastique(i, j);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int selectionMultiple(bool c)
	///
	/// @param[in] c : Selection inverser ou non
	///
	/// @return Aucun
	///
	/// @remark : Active la selection multiple, cherche si les objets sont dans le rectangle elastique.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl selectionMultiple(bool c)
	{
		return FacadeModele::obtenirInstance()->selectionMultiple(c);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool verifierCliqueDansTable(int x, int y)
	///
	/// @param[in] x : abcisse du point initial 
	/// @param[in] y : ordonnee du point initial
	///
	/// @return true si le clic est dans la table, faux sinon.
	///
	/// @remark : Verifie si un clic est dans la table. On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl verifierCliqueDansTable(int x, int y)
	{
		return FacadeModele::obtenirInstance()->verifierCliqueDansTable(x, y);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void deselectAll( void )
	///
	/// @return Aucun
	///
	/// @remark : Ca deselectionne tout
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deselectAll( void )
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->deselectionnerTout();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void selectAll( void )
	///
	/// @return Aucun
	///
	/// @remark : Ca deselectionne tout
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl selectAll(void)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->selectionnerTout();
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void dupliquerSelection(int i, int j)
	///
	/// @param[in] i : point suivant i de la souris
	/// @param[in] j : point suivant j de la souris
	///
	/// @return Aucun
	///
	/// @remark : Permet duplique les objets selectionnes
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dupliquerSelection(int i, int j)
	{
		FacadeModele::obtenirInstance()->dupliquerSelection(i, j);
		FacadeModele::obtenirInstance()->setDebug();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn getPositionX() 
	///
	/// @return la position en X
	///
	/// @remark : Retourne le x de la position du dernier objet selectionne qu'on a trouve dans l'arbre.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl getPositionX() 
	{
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
	/// @fn double getPositionY()
	///
	/// @return la position en Y
	///
	/// @remark : Retourne le y de la position du dernier objet selectionne qu'on a trouve dans l'arbre.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl getPositionY()
	{
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
	/// @fn double getAngle()
	///
	/// @return l'angle de l'objet
	///
	/// @remark : Retourne l'angleZ du dernier objet selectionne qu'on a trouve dans l'arbre.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getAngle()
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
		return angle;
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn double getScale()
	///
	/// @return la taille de l'objet (Retourne le scale du dernier objet selectionne qu'on a trouve dans l'arbre.)
	///
	/// @remark : Le scale en y est representatif des objets normaux et des murs.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getScale()
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
		return scale;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void creeSon()
	///
	/// @param[in] value : Nom du son
	/// @param[in] length : Taille du nom
	///
	/// @return Aucun
	///
	/// @remark Cette fonction permet de cree un son (le charger en memoire)
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl creeSon(char* value, int)
	{
		SoundControl->creeSon(value);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void jouerSon()
	///
	/// @param[in] value : Nom du son
	/// @param[in] length : Taille du nom
	/// @param[in] pause : Arret du son
	///
	/// @return Aucun
	///
	/// @remark Cette fonction permet de jouer un son ou de l'arreter
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl jouerSon(char* value, int, bool pause)
	{
		SoundControl->jouerSon(value, pause);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void bouclerSon()
	///
	/// @param[in] value : Nom du son
	/// @param[in] length : Taille du nom
	/// @param[in] loop : Faire boucler le son en continue ou non
	///
	/// @return Aucun
	///
	/// @remark Cette fonction permet de jouer un son en boucle
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl bouclerSon(char* value, int, bool loop)
	{
		SoundControl->bouclerSon(value, loop);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void sourdine()
	///
	/// @param[in] mute : Mute or unmute the sound
	///
	/// @return Aucun
	///
	/// @remark Cette fonction controle le canal de son global et l'active ou le desactive
	/// @remark Attention, cette fonction ne fais pas de pause, elle coupe le son
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl sourdine(bool mute)
	{
		SoundControl->sourdine(mute);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void arreterSon(char* value, int length)
	///
	/// @param[in] value : Nom du son
	/// @param[in] length : Taille du nom
	///
	/// @return Aucun
	///
	/// @remark Permet d'arreter un son completement (mais ne le detruit pas)
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl arreterSon(char* value, int)
	{
		SoundControl->arreterSon(value);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void arreterToutSon()
	///
	/// @return Aucun
	///
	/// @remark Permet d'arreter completement tout les sons (mais ne le detruit pas)
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl arreterToutSons()
	{
		SoundControl->arreterSon();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ajusterBGM()
	///
	/// @param[in] pourcentage : Valeur entre 0 et 100 pour ajuster le volume
	///
	/// @return Aucun
	///
	/// @remark Cette fonction permet de jouer modifier le volume des son en
	/// @remark boucle (background music looping)
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl ajusterBGM(float pourcentage)
	{
		SoundControl->ajusterBGM(pourcentage);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ajusterVolume(char* value, float pourcentage)
	///
	/// @param[in] value : Nom du son
	/// @param[in] length : Taille du nom
	/// @param[in] pourcentage : Valeur entre 0 et 100 pour ajuster le volume
	///
	/// @return Aucun
	///
	/// @remark Cette fonction permet d'ajuster le volume d'un son precis
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl ajusterVolume(char* value, float pourcentage)
	{
		SoundControl->ajusterVolume(value, pourcentage);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ajusterSFX()
	///
	/// @param[in] pourcentage : Valeur entre 0 et 100 pour ajuster le volume
	///
	/// @return Aucun
	///
	/// @remark Cette fonction permet de jouer modifier le volume des son
	/// @remark bref (evenement ponctuel)
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl ajusterSFX(float pourcentage)
	{
		SoundControl->ajusterSFX(pourcentage);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void  initialiserSon();
	///
	///
	/// @return Aucun
	///
	/// @remark Cette fonction permet d'initialiser les sons
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserSon()
	{
#if !(_DEBUG)
		SingletonGlobal::obtenirInstance()->activerSon();
		std::cout << "Initialisation des sons ..." << std::endl;
		SoundControl;
		std::cout << "Sons initialiser." << std::endl;
#endif
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void obligerTransparence(bool transparence)
	///
	/// @param[in] transparence : booleen de transparence
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
			if (objet->getTwin()->getTwin() != NULL && objet->getTwin() != nullptr)
				objet->getTwin()->getTwin()->setTransparent(transparence);
		}
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void initialiserRectangleElastique(int i, int j)
	///
	/// @param[in] i : coordonnees i de la souris
	/// @param[in] j : coordonnees j de la souris
	///
	/// @return Aucun
	///
	/// @remark Initialise le rectangle elastique
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserRectangleElastique(int i, int j)
	{
		FacadeModele::obtenirInstance()->initialiserRectangleElastique(i, j);
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void terminerRectangleElastique()
	///
	/// @return Aucun
	///
	/// @remark Suprime le rectangle elastique
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl terminerRectangleElastique()
	{
		FacadeModele::obtenirInstance()->terminerRectangleElastique();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void creerMur(int originX, int originY,int x1, int y1, int x2, int y2) 
	///
	///
	/// @param[in] originX : Position en X ou le bouton a ete appuye
	/// @param[in] originY : Position en Y ou le bouton a ete appuye
	/// @param[in] x1 : Position en X precedant un deplacement de la souris
	/// @param[in] y1 : Position en Y precedant un deplacement de la souris
	/// @param[in] x2 : Position en X apres un deplacement de la souris (position actuelle de la souris)
	/// @param[in] y2 : Position en X apres un deplacement de la souris (position actuelle de la souris)
	///
	/// @return Aucun
	///
	/// @remark : Cette fonction place un mur dont un bout est la ou le bouton gauche de la souris a ete appuye, et l'autre bout est sous le curseur de la souris.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl creerMur(int originX, int originY, int x1, int y1, int x2, int y2)
	{
		FacadeModele::positionnerMur(originX,originY,x1, y1, x2, y2, objet);
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool setProprietesNoeud(int x, int y, int angle, double scale)
	///
	///
	/// @param[in] x : X en coordonnees du monde qu'on veut donner a notre noeud.
	/// @param[in] y : Y en coordonnees du monde qu'on veut donner a notre noeud.
	/// @param[in]	angle : angle de rotation
	///	@param[in]	scale: scale de l'objet
	///
	/// @return bool
	///
	/// @remark : La fonction calcule la boite englobante de l'objet transforme, le calcul est differend pour les murs. Il manque quelque chose pour le calcul des boites englobantes transformees des objets de type mur.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl setProprietesNoeud(int x, int y, int angle, double scale)
	{
		// Calculer la position a assigner en coordonnees du monde. Elle est deja en
		// coordonnees du monde car ce qui est dans les textBox, c'est l'attribut position du noeud.
		glm::dvec3 nouvellePosition{ x, y, 0 };
		bool nouvellesProprietesSontLegales = true;
		glm::dvec3 boite[4];
		glm::dvec3 positionObjet = objet->obtenirPositionRelative();
		objet->obtenirBoiteModele(boite[0], boite[1], boite[2], boite[3]);

		glm::dmat3 echelle;
		glm::dvec3 scaleInitial = objet->obtenirAgrandissement();
		if (objet->obtenirType() == "mur")
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
				//std::cout << "L'application des proprietes refusee, on sortirait de la table" << std::endl;
				return false;
			}
		}

		if (nouvellesProprietesSontLegales)
		{
			glm::dvec3 angles = objet->obtenirRotation();
			glm::dvec3 nouveauxAngles = glm::dvec3{ angles.x, angles.y, angle }; 
			objet->assignerPositionRelative(nouvellePosition);
			objet->assignerRotationHard(nouveauxAngles);

			// traiter le mur de facon speciale.
			if (objet->obtenirType() == "mur")
				objet->assignerEchelle(glm::dvec3{ scaleInitial.x, scale, scaleInitial.z });
			else
				objet->assignerEchelle(glm::dvec3{ scale, scale, scale });
		}
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn obtenirZoomCourant()
	///
	/// @return : valeur du zoom courant	
	///
	/// @remark La valeur du facteur de zoom appliquer sur la fenetre
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl obtenirZoomCourant()
	{
		if (FacadeModele::obtenirInstance() == nullptr)
			return -1;
		return FacadeModele::obtenirInstance()->obtenirZoomCourant();
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirCentreMasseX( void )
	///
	/// @return : int, le centre de masse en x
	///
	/// @remark La valeur en X de centre de masse
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirCentreMasseX( void )
	{
		return FacadeModele::obtenirInstance()->obtenirCentreMasseX();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirCentreMasseY( void )
	///
	/// @return le centre de masse en y
	///
	/// @remark La valeur en Y de centre de masse
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirCentreMasseY( void )
	{
		return FacadeModele::obtenirInstance()->obtenirCentreMasseY();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool resetZoom()
	///
	/// @return : booleen de reussite
	///
	/// @remark Remet a 0 le centre du zoom
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl resetZoom()
	{
		return FacadeModele::obtenirInstance()->appliquerZoomInitial();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool duplicationEstHorsTable( void )
	///
	/// @return bool d'etat si hors table
	///
	/// @remark true si la souris la selection est hors table lors de la duplication
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl duplicationEstHorsTable( void )
	{
		return FacadeModele::obtenirInstance()->duplicationEstHorsTable();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void creerFichierConfig(int config[13])
	/// @brief Cree un fichier de sauvegarde de configuration.
	/// @param[in] config : Valeurs de la configuration de partie.
	/// @return Aucune
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl creerFichierConfig(int config[13])
	{
		FacadeModele::obtenirInstance()->sauvegarderConfig(config);
	}
	
	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int* chargerFichierConfiguration()
	/// @brief Charger un fichier de sauvegarde de configuration.
	/// @return Les valeurs de configuration.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int* __cdecl chargerFichierConfiguration()
	{
		return FacadeModele::obtenirInstance()->obtenirConfiguration();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirDifficulte(char* nomFichier, int length)
	/// @brief Obtenir le niveau de difficulte de la zone.
	/// @param[in] nomFichier : Mom du fichier de la zone.
	/// @param[in] length : Longueur du fichier.
	/// @return Le niveau de difficulte de la zone.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirDifficulte(char* nomFichier, int)
	{
		return FacadeModele::obtenirInstance()->obtenirDifficulte(nomFichier);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int* obtenirProprietes(char* nomFichier, int length)
	/// @brief Obtenir les proprietes de la zone.
	/// @param[in] nomFichier : Mom du fichier de la zone.
	/// @param[in] length : Longueur du fichier.
	/// @return Les proprietes de difficulte de la zone.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int* __cdecl obtenirProprietes(char* nomFichier, int)
	{
		return FacadeModele::obtenirInstance()->obtenirProprietes(nomFichier);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void creerFichierCampagne(char* listMaps, int length)
	/// @brief Creer un fichier contenant les zones de la campagne.
	/// @param[in] listMaps : Liste des zones de jeu.
	/// @param[in] length : Longueur de la liste.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl creerFichierCampagne(char* listMaps, int)
	{
		FacadeModele::obtenirInstance()->sauvegarderCampagne(listMaps);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirTouchePGJ1()
	/// @brief Retourne la touche associee a Palette Gauche J1.
	/// @return La touche associee.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirTouchePGJ1()
	{
		return FacadeModele::obtenirInstance()->obtenirTouchePGJ1(); 
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirTouchePGJ2()
	/// @brief Retourne la touche associee a Palette Gauche J2.
	/// @return La touche associee.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirTouchePGJ2()
	{
		return FacadeModele::obtenirInstance()->obtenirTouchePGJ2(); 
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirTouchePDJ1()
	/// @brief Retourne la touche associee a Palette Droite J1.
	/// @return La touche associee.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirTouchePDJ1()
	{
		return FacadeModele::obtenirInstance()->obtenirTouchePDJ1(); 
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirTouchePDJ2()
	/// @brief Retourne la touche associee a Palette Droite J2.
	/// @return La touche associee.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirTouchePDJ2()
	{
		return FacadeModele::obtenirInstance()->obtenirTouchePDJ2(); 
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirToucheRessort()
	/// @brief Retourne la touche associee au ressort.
	/// @return La touche associee.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirToucheRessort()
	{
		return FacadeModele::obtenirInstance()->obtenirToucheRessort(); 
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirNombreDeBilles()
	/// @brief Retourne le nombre de billes
	/// @return Le nombre de billes.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirNombreDeBilles()
	{
		return FacadeModele::obtenirInstance()->obtenirNombreDeBilles();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirNombreBillesPerdus()
	/// @brief Retourne le nombre de billes detruite
	/// @return Le nombre de billes.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirNombreBillesPerdus()
	{
		return SingletonGlobal::obtenirInstance()->obtenirNombreDeBillesPerdus();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirModeDoubleBille()
	/// @brief Retourne la valeur d'activation du mode correspondant.
	/// @return 1 si le mode double bille est actif, 0 sinon.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirModeDoubleBille()
	{
		return FacadeModele::obtenirInstance()->obtenirModeDoubleBille();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirNombreDeBilles()
	/// @brief Retourne la valeur d'activation du mode correspondant.
	/// @return 1 si l'affichage global est actif, 0 sinon.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirAffichageGlobal()
	{
		return FacadeModele::obtenirInstance()->obtenirAffichageGlobal();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void bloquerAffichageGlobal(int active)
	/// @brief Active ou desactive l'affichage global.
	/// @param[in] active : Valeur d'activation.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl bloquerAffichageGlobal(int active)
	{
		FacadeModele::obtenirInstance()->bloquerAffichageGlobal(active);
		FacadeModele::obtenirInstance()->setDebug();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void activerPalettesGJ1()
	/// @brief Active la Palette Gauche J1.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl activerPalettesGJ1()
	{
		FacadeModele::obtenirInstance()->activerPalettesGJ1();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void desactiverPalettesGJ1()
	/// @brief Desactive la Palette Gauche J1.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl desactiverPalettesGJ1()
	{
		FacadeModele::obtenirInstance()->desactiverPalettesGJ1();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void activerPalettesDJ1()
	/// @brief Active la Palette Droite J1.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl activerPalettesDJ1()
	{
		FacadeModele::obtenirInstance()->activerPalettesDJ1();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void desactiverPalettesDJ1()
	/// @brief Desactive la Palette Droite J1.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl desactiverPalettesDJ1()
	{
		FacadeModele::obtenirInstance()->desactiverPalettesDJ1();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void activerPalettesGJ2()
	/// @brief Active la Palette Gauche J2.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl activerPalettesGJ2()
	{
		FacadeModele::obtenirInstance()->activerPalettesGJ2();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void desactiverPalettesGJ2()
	/// @brief Desactive la Palette Gauche J2.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl desactiverPalettesGJ2()
	{
		FacadeModele::obtenirInstance()->desactiverPalettesGJ2();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void activerPalettesDJ2()
	/// @brief Active la Palette Droite J2.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl activerPalettesDJ2()
	{
		FacadeModele::obtenirInstance()->activerPalettesDJ2();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void desactiverPalettesDJ2()
	/// @brief Desactive la Palette Droite J2.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl desactiverPalettesDJ2()
	{
		FacadeModele::obtenirInstance()->desactiverPalettesDJ2();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn BSTR obtenirDerniereCampagne()
	/// @brief Retourne la derniere campagne.
	/// @return La liste d'info de la derniere campagne.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) BSTR obtenirDerniereCampagne()
	{
		// http://stackoverflow.com/questions/6284524/bstr-to-stdstring-stdwstring-and-vice-versa
		std::string str = FacadeModele::obtenirInstance()->obtenirDerniereCampagne();
		return stringToBSTR(str);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void supprimerBille()
	/// @brief Supprime la bille en jeu (mode test).
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl supprimerBille()
	{
		FacadeModele::obtenirInstance()->supprimerBille();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void construireListesPalettes()
	/// @brief Construit une liste des palettes dans FacadeModele.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl construireListesPalettes()
	{
		FacadeModele::obtenirInstance()->construireListesPalettes();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void mettreAJourListeBillesEtNoeuds()
	/// @brief Met a jour la liste des billes et des noeuds dans FacadeModele.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl mettreAJourListeBillesEtNoeuds()
	{
		FacadeModele::obtenirInstance()->mettreAJourListeBillesEtNoeuds();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void modePause(bool pause)
	/// @brief Active ou desactive le mode pause.
	/// @param[in] pause : Activation ou desactivation.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl modePause(bool pause)
	{
		FacadeModele::obtenirInstance()->setPause(pause);
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool spotLight(int lum, bool state)
	/// @brief Active ou desactive la lumiere
	/// @param[in] lum : Type de lumiere
	/// @param[in] state : Activation ou desactivation.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl spotLight(int lum, bool state)
	{
		// See this for light:
		// http://www.gamedev.net/topic/564426-create-glow-with-gl_emission/
		bool debugLumiere = FacadeModele::obtenirInstance()->obtenirConfiguration()[12] && FacadeModele::obtenirInstance()->obtenirConfiguration()[10];

		if (lum > 2 || lum < 0)
			return false;
		if (debugLumiere) {
			FacadeModele::obtenirInstance()->printCurrentTime();
			std::cout << " - Lumiere(s) ";
		}
		
		if (debugLumiere)
		{
			if (state == true)
			{
				std::cout << "ouverte(s)" << std::endl;
			}
			else
			{
				std::cout << "fermee(s)" << std::endl;
			}
		}

		FacadeModele::obtenirInstance()->setLight(lum, state);

		return true;
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void initialiserSingleton()
	/// @brief Initialise le singleton global.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserSingleton()
	{
		SingletonGlobal::obtenirInstance();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void detruireSingleton()
	/// @brief Detruit le singleton global.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl detruireSingleton()
	{
		SingletonGlobal::libererInstance();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirPointsGagnerBille()
	/// @brief Retourne le nombre de points pour gagner une bille.
	/// @return Le nombre de points pour gagner une bille.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirPointsGagnerBille()
	{
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirProprietes()[4];
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirPointsGagnerPartie()
	/// @brief Retourne le nombre de points pour gagner la partie.
	/// @return Le nombre de points pour gagner la partie.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirPointsGagnerPartie()
	{
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirProprietes()[3];
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirNombreDePointsDePartie()
	/// @brief Retourne le nombre de points courant dans la partie.
	/// @return Le nombre de points courant dans la partie.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirNombreDePointsDePartie()
	{
		return SingletonGlobal::obtenirInstance()->getPointsPartie();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void resetNombreDePointsDePartie()
	/// @brief Reinitialise le nombre de points dans la partie.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl resetNombreDePointsDePartie()
	{
		SingletonGlobal::obtenirInstance()->setPointsPartie(0);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirNombreBillesCourante()
	/// @brief Retourne le nombre de billes courantes.
	/// @return Le nombre de billes courantes.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirNombreBillesCourante()
	{
		return SingletonGlobal::obtenirInstance()->obtenirBille();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void resetNombreBillesCourantes()
	/// @brief Reinitialise le nombre de billes courantes.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl resetNombreBillesCourantes()
	{
		SingletonGlobal::obtenirInstance()->resetBille();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void compresserRessort()
	/// @brief Compresser le ressort.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl compresserRessort()
	{
		return FacadeModele::obtenirInstance()->compresserRessort();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void relacherRessort()
	/// @brief Relacher le ressort.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl relacherRessort()
	{
		return FacadeModele::obtenirInstance()->relacherRessort();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void animerJeu(bool animer)
	/// @brief Active ou desactive l'animation du jeu.
	/// @param[in] animer : Valeur d'ativation ou de desactivation.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animerJeu(bool animer)
	{
		SingletonGlobal::obtenirInstance()->setAnimation(animer);
		for (unsigned int i = 0; i < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants(); i++)
			FacadeModele::obtenirInstance()->assignerAnimer(animer, FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(i));
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void rechargerArbre(bool recharger)
	/// @brief Recharge l'arbre de rendu.
	/// @param[in] recharger : Recharge ou non l'arbre.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl rechargerArbre(bool recharger)
	{
		if (recharger)
			ouvrirXMLString(SingletonGlobal::obtenirInstance()->obtenirPathTemp());
		else
			creerXMLString(SingletonGlobal::obtenirInstance()->obtenirPathTemp(),
				FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirProprietes(), true);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void activerAI(bool actif)
	/// @brief Active ou desactive le joueur virtuel (AI).
	/// @param[in] actif : Valeur d'ativation ou de desactivation.
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl activerAI(bool actif)
	{
		FacadeModele::obtenirInstance()->assignerAI(actif);
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void activerCustomConsole()
	/// @brief Active la deviation du cout vers un sstream
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl activerCustomConsole()
	{
		FacadeModele::obtenirInstance(true);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void obtenirCout()
	/// @return Retourne la valeur du string qui serais dans la console.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) BSTR __cdecl obtenirCout()
	{
		return stringToBSTR(FacadeModele::obtenirInstance()->obtenirCout());
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void refreshText(int x, int y)
	/// @brief Rafraichit la position du texte
	/// @param[in] x : Taille max de la fenetre en x
	/// @param[in] y : Taille max de la fenetre en y
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl refreshText(int x, int y)
	{
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->refresh(x, y);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void creeTexte(char* text, char* font)
	/// @brief Cree le texte
	/// @param[in] text : Le texte a modifier
	/// @param[in] font : La font a utiliser
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl creeTexte(char* text, int, char* font, int)
	{
		std::string myText = std::string(text);
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->creeTexte(myText, font);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void updateText(char* oldText, int lengthO, char* newText, int lengthN)
	/// @brief Modifie un texte existant
	/// @param[in] oldText : Le texte a modifier
	/// @param[in] newText : La texte apres modification
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl updateText(char* oldText, int, char* newText, int)
	{
		std::string myOldText = std::string(oldText);
		std::string myNewText = std::string(newText);
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->updateText(myOldText, myNewText);
	}
	
	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void resize(char* text, int length, unsigned int size)
	/// @brief Modifie la taille du texte
	/// @param[in] text : Le texte a modifier
	/// @param[in] size : La taille a appliquer au text
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl resize(char* text, int, int size)
	{
			std::string myText = std::string(text);
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->resize(myText, (unsigned int)size);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void changerCouleur(char* text, int length, float rouge, float vert, float bleu)
	/// @brief Change la couleur du texte
	/// @param[in] text : Le texte a modifier
	/// @param[in] rouge : La couleur rouge a appliquer (en RGB)
	/// @param[in] vert : La couleur vert a appliquer (en RGB)
	/// @param[in] bleu : La couleur bleu a appliquer (en RGB)
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl changerCouleur(char* text, int, float rouge, float vert, float bleu)
	{
		std::string myText = std::string(text);
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->changerCouleur(myText, rouge, vert, bleu);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void changerCouleurV(char* text, int length, float couleur[3])
	/// @brief Change la couleur du texte
	/// @param[in] text : Le texte a modifier
	/// @param[in] couleur : La couleur a appliquer (en RGB)
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl changerCouleurV(char* text, int, float couleur[3])
	{
		std::string myText = std::string(text);
		glm::fvec3 couleurV(couleur[0], couleur[1], couleur[2]);
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->changerCouleurV(myText, couleurV);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void repositionner(char* text, int length, int x, int y)
	/// @brief Modifie la position du texte
	/// @param[in] text : Le texte a modifier
	/// @param[in] x : La position du texte en x
	/// @param[in] y : La position du texte en y
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl repositionner(char* text, int, float x, float y)
	{
		std::string myText = std::string(text);
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->repositionner(myText, x, y);
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void suprimerText(char* text, int length)
	/// @brief Efface un texte du rendu
	/// @param[in] text : Le texte a effacer
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl suprimerText(char* text, int)
	{
		std::string myText = std::string(text);
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->suprimerText(myText);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void afficherTextes(bool afficher)
	/// @brief Affiche ou non tout les textes
	/// @param[in] afficher : L'etat d'affichage
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl afficherTextes(bool afficher)
	{
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->afficherTextes(afficher);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void preparerUsineArbre(char* text, int length)
	/// @brief Cree une usine
	/// @param[in] text L'usine a cree
	/// @param[in] length Taille d string de l'usine
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl preparerUsineArbre(char* text, int)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->preparerUsine(std::string(text));
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void initialiserArbre()
	/// @brief initialise l'arbre
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserArbre()
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->initialiser();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void utiliserCameraOrbite(bool utiliseOrbite)
	/// @brief Change l'etat de la camera
	/// @param[in] utiliseOrbite : La valeur de l'etat a utiliser
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void utiliserCameraOrbite(bool utiliseOrbite)
	{
		FacadeModele::obtenirInstance()->utiliserCameraOrbite(utiliseOrbite);
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void sauvegarderHistorique()
	/// @brief Sauvegarde l'etat de l'arbre de rendu
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void sauvegarderHistorique()
	{
		FacadeModele::obtenirInstance()->sauvegarderHistorique();
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void annulerModifications()
	/// @brief Annule les modifications et restaure l'arbre de rendu
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void annulerModifications()
	{
		FacadeModele::obtenirInstance()->annulerModifications();
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void retablirModifications()
	/// @brief Retablit les modifications et restaure l'arbre de rendu
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void retablirModifications()
	{
		FacadeModele::obtenirInstance()->retablirModifications();
	}
	

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void viderHistorique()
	/// @brief Vide l'historique des dernieres modifications
	/// @return Aucune.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void viderHistorique()
	{
		FacadeModele::obtenirInstance()->viderHistorique();
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void obtenirNombreSelection()
	/// @brief Retourne le nombre d'objets de l'arbre de rendu qui sont selectionnes
	/// @return int, le nombre d'objets selectiones.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int obtenirNombreSelection()
	{
		return FacadeModele::obtenirInstance()->obtenirNombreSelection();
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool possedeSuivant()
	/// @brief Retourne vrai s'il existe une sauvegarde suivante dans l'historique
	/// @return bool, true s'il existe une sauvegarde suivante dans l'historique.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool possedeSuivant()
	{
		return FacadeModele::obtenirInstance()->possedeSuivant();
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool possedePrecedent()
	/// @brief Retourne vrai s'il existe une sauvegarde precedente dans l'historique
	/// @return bool, true s'il existe une sauvegarde precedente dans l'historique.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool possedePrecedent()
	{
		return FacadeModele::obtenirInstance()->possedePrecedent();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool sourisEstSurObjet(int i, int j, int hauteur, int largeur, bool& estSelectionne)
	/// @brief Retourne vrai si la souris se situe sur un objet deja selectionne.
	/// @return bool, true si la souris se situe sur un objet deja selectionne.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool sourisEstSurObjet(int i, int j, int hauteur, int largeur, bool& estSelectionne)
	{
		return FacadeModele::obtenirInstance()->sourisEstSurObjet(i, j, hauteur, largeur, estSelectionne);
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool cameraEstOrbite()
	/// @brief Retourne vrai si la ve est en perspective / la camera est orbite
	/// @return bool, true si la camera est en mode orbite
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool cameraEstOrbite()
	{
		return FacadeModele::obtenirInstance()->cameraEstOrbite();
	}


}// FIN DU extern "C"