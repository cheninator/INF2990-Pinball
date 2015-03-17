////////////////////////////////////////////////
/// @file FacadeInterfaceNative.cpp
/// @author INF2990
/// @date 2014-08-16
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

#include <string>
#include <iomanip>
#include <iostream>

#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <windows.h>
#include "BancTests.h"

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

void printCurrentTime() {
	SYSTEMTIME time;
	GetLocalTime(&time);
	std::cout << std::fixed << std::setw(2) << std::setprecision(2) << time.wHour << ":"
		<< std::fixed << std::setfill('0') << std::setw(2) << std::setprecision(2) << time.wMinute << ":"
		<< std::fixed << std::setfill('0') << std::setw(2) << std::setprecision(2) << time.wSecond << ":"
		<< std::fixed << std::setfill('0') << std::setw(3) << std::setprecision(3) << time.wMilliseconds;
}

extern "C"
{
	// TO DO : SUPPRIMER CETTE VARIABLE QUAND PLUS NECESSAIRE
	// Nvm, c'est devenue une necesite, donc garder ces variables absolument
	static NoeudAbstrait* objet = new NoeudAbstrait();
	static NoeudAbstrait* objet_temp = new NoeudAbstrait();

	// Useless, pas d'orbite en ce moment
	static double theta = 0; ///< Angle Theta
	static double phi = 0;  /// < angle Phi

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  trouverObjetSousPointClique(int i, int j)
	///
	/// @param[in] i: valeur en i dans l'ecran
	/// @param[in] j: valeur en j dans l'ecran
	///
	/// @return Aucune.
	///
	/// @remark : Appel la fonction trouverObjetSousPointClique de FacadeModele
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl selectionnerObjetSousPointClique(int i, int j, int hauteur, int largeur, bool ctrlDown)
	{
		return FacadeModele::obtenirInstance()->selectionnerObjetSousPointClique(i, j, hauteur, largeur, ctrlDown);
		
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  initialiserOpenGL(int* handle)
	///
	/// @param[in] handle : Le handle.
	///
	/// @return Aucune.
	///
	/// @remark : Cette fonction initialise un contexte OpenGL dans la fenetre
	/// \remark identifiee par le handle passe en parametre.  Cette fonction doit
	/// \remark etre la premiere a etre appelee, car la creation de l'objet du modele
	/// \remark C++ s'attend a avoir un contexte OpenGL valide.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  initialiserOpenGL(int* handle)
	{
		if (handle == nullptr)
			return;
		std::cout << std::endl << "Initialisation de l'openGL en cours..." << std::endl;
		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND)handle);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  libererOpenGL()
	///
	/// @return Aucune.
	///
	/// @remark : Cette fonction libere le contexte OpenGL. 
	/// \remark Cette fonction doit etre la derniere a etre appelee,
	/// \remark car elle libere egalement l'objet du modele C++
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();

		/// Desinitialisation de la facade.  Le fait de le faire apres la
		/// desinitialisation du contexte OpenGL aura pour consequence que la
		/// liberation des listes d'affichages, par exemple, sera faite une fois que
		/// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  dessinerOpenGL()
	///
	/// @return Aucune.
	///
	/// @remark : Cette fonction affiche la scene.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  dessinerOpenGL()
	{
		// Affiche la scene.
		FacadeModele::obtenirInstance()->afficher();
		// Temporaire: pour detecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();

	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  redimensionnerFenetre(int largeur, int hauteur)
	///
	/// @param[in] largeur : La nouvelle largeur de la fenetre.
	/// @param[in] hauteur : La nouvelle hauteur de la fenetre.
	///
	/// @return Aucune.
	///
	/// @remark :  Cette fonction doit etre appelee lorsque la fenetre est redimensionnee
	/// \remark afin d'ajuster les parametres de la machine a etats
	/// \remark d'OpenGL pour correspondre aux nouvelles dimensions de la fenetre.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  redimensionnerFenetre(int largeur, int hauteur)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(
			glm::ivec2{ 0, 0 },
			glm::ivec2{ largeur, hauteur }
		);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  animer(double temps)
	///
	/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
	///
	/// @return Aucune.
	///
	/// @remark :  Cette fonction effectue les differents calculs d'animations
	/// \remark necessaires pour le mode jeu, tel que les differents calculs de
	/// \remark physique du jeu.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  animer(double temps)
	{
		FacadeModele::obtenirInstance()->animer((float)temps);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  zoomIn()
	///
	/// @return Aucune.
	///
	/// @remark :  Cette fonction applique un zoom avant sur le present volume de vision.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  zoomIn()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  zoomOut()
	///
	/// @return Aucune.
	///
	/// @remark :  Cette fonction applique un zoom arriere sur le present volume de vision.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  zoomOut()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	///
	/// @return Le nombre d'affichage par seconde.
	///
	/// @remark :  Cette fonction permet d'obtenir le nombre d'affichages par seconde.
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
	/// @return 0 si tous les tests ont reussi, 1 si au moins un test a echoue
	///
	/// @remark :  Cette fonction permet d'executer l'ensemble des tests unitaires
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl executerTests()
	{
		bool reussite = BancTests::obtenirInstance()->executer();
		return reussite ? 0 : 1;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  creerObjet()
	///
	///
	/// @param[in]  value : Nom de l'objet
	/// @param[in]  length : Taille du nom de l'objet
	/// @param[in]  twin : si a un jumeau
	/// @param[in]  colorShift : la couleur
	///
	/// @return Aucun
	///
	/// @remark :  Cette fonction permet de cree un objet 3D
	///	\remark Cree un objet sans initialiser ses proprietes.La fonction C# qui
	/// \remark L'appelle est responsable d'attribuer des proprietes.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  creerObjet(char* value, int length, bool isTwin, bool colorShift)
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
			else if (nomObjet == "bille")
			{
				std::vector<int> generateurs;
				int i = 0;
				int nbElements = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants();
				NoeudComposite* noeudTable = new NoeudComposite;
				noeudTable = (dynamic_cast <NoeudComposite*> (
					FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)));
				for (i = 0; i < nbElements; i++)
				{
					
					std::string typeNoeud = noeudTable->getEnfant(i)->obtenirType();

					if (typeNoeud == "generateurbille")
						generateurs.push_back(i);
				}
				if (generateurs.size() == 0)
					return;

				int pos = rand() % generateurs.size();

				NoeudAbstrait* generateur = noeudTable->getEnfant(generateurs[pos]);
					generateur->genererBille();
				glm::dvec3 scale = generateur->obtenirAgrandissement();
				glm::dvec3 position = generateur->obtenirPositionRelative();
				glm::dvec3 rotation = generateur->obtenirRotation();
			
				//objet->assignerRotation({ rotation.x, rotation.y, rotation.z });
				
				double positionX = position.x;
				double positionY = position.y - ((30 * scale.x));

				glm::dvec3 vecteur = { 0, -((30 * scale.x)), 0 };
				double angleEnRadian = -rotation[2] * utilitaire::PI_180;
				glm::dmat3 transform = glm::dmat3{  glm::dvec3{ cos(angleEnRadian), -sin(angleEnRadian), 0.0 },
													glm::dvec3{ sin(angleEnRadian), cos(angleEnRadian), 0.0f },
													glm::dvec3{ 0.0, 0.0, 1.0 } };

				objet->assignerPositionRelative(position + transform * vecteur);
				objet->assignerEchelle(scale);
				//HH:MM:SS:mmm – Nouvelle bille : x: POSX y: POSY
				// http://brian.pontarelli.com/2009/01/05/getting-the-current-system-time-in-milliseconds-with-c/
				if (FacadeModele::obtenirInstance()->obtenirConfiguration()[8] && FacadeModele::obtenirInstance()->obtenirConfiguration()[12]) {
					printCurrentTime();
					std::cout << std::fixed << std::setprecision(2);
					std::cout << " - Nouvelle bille : x: " << positionX << " y: " << positionY << std::endl;;
				}
				noeudTable = NULL;
				delete noeudTable;
			}
		}
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->ajouter(objet);
		FacadeModele::obtenirInstance()->mettreAJourListeBillesEtNoeuds();
		FacadeModele::obtenirInstance()->construireListesPalettes();
		FacadeModele::obtenirInstance()->setDebug();

	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  creerObjetAvecTests()
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
	/// @return True si l'objet a ete cree, false si une des etapes de la creation
	///			a echoue.
	///
	/// @remark :  Cette fonction permet de cree un objet 3D.
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
	/// \remark a l'arbre de rendu comme enfant de la table.  Sinon, on l'efface.
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

		// Voir la fonction rotate, c'est comme ca que les angles sont settes dans cette fonction.
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
			if (nomObjet == "portail")
				FacadeModele::obtenirInstance()->setDebug();
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
	/// @fn __declspec(dllexport) void __cdecl  positionObjet(int x, int y, int z)
	///
	/// @param[in]  x : La positon en x
	/// @param[in]  y : La positon en y
	/// @param[in]  z : La positon en z
	///
	/// @return Aucune.
	///
	/// @remark : Permet de deplacer un objet en x y et/ou z
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  positionObjet(int x, int y, int z)
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
	/// @fn __declspec(dllexport) void __cdecl  translateObjet(int x, int y, int z)
	///
	/// @param[in]  x : La positon en x
	/// @param[in]  y : La positon en y
	/// @param[in]  z : La positon en z
	///
	/// @return Aucune.
	///
	/// @remark : Permet de deplacer un objet en x y et/ou z
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  translateObjet(int x, int y, int z)
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
	/// @fn __declspec(dllexport) void __cdecl  scaleObjet(double scale)
	///
	/// @param[in]  scale : La multiplication en x
	///
	/// @return Aucune.
	///
	/// @remark : Permet de resize un objet uniformement
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  scaleObjet(double scale)
	{
		if (objet == nullptr)
			return;
		objet->assignerEchelle({ scale, scale, scale });

	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  addScaleObjet(int myScale)
	///
	/// @param[in]  myScale : La multiplication en x
	///
	/// @return Aucune.
	///
	/// @remark : Permet de rajouter un resize d'un objet uniformement
	///
	////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) void __cdecl  addScaleObjet(int myScale)
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
	/// @fn __declspec(dllexport) void __cdecl  scaleObjetXYZ(double x, double y, double z)
	///
	/// @param[in]  x : La multiplication en x
	/// @param[in]  y : La multiplication en y
	/// @param[in]  z : La multiplication en z
	///
	/// 
	///
	/// @return Aucune.
	///
	/// @remark : Permet de resize un objet en x y z
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  scaleObjetXYZ(double x, double y, double z)
	{
		if (objet == nullptr)
			return;
		objet->assignerEchelle({ x, y, z });
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  rotate(float angle, char direction)
	///
	/// @param[in]  angle : L'angle de rotation
	/// @param[in]  direction : La direction dans la quel on applique la rotation.
	///
	/// @return Aucune.
	///
	/// @remark : Permet de faire tourner notre objet
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  rotate(float angle, char direction)
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
	/// @fn __declspec(dllexport) void __cdecl  resetObject( void )
	///
	/// @return Aucune.
	///
	/// @remark : Remet les donnees d'un objet a 0
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  resetObject( void )
	{
		if (objet == nullptr)
			return;
		objet->assignerPositionRelative({ 0, 0, 0 });
		objet->assignerEchelle({ 1, 1, 1 });
		objet->resetRotation();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  removeObject( void )
	///
	/// Remet les donnees d'un objet a 0
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  removeObject( void )
	{
		FacadeModele::obtenirInstance()->supprimer();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  purgeAll( void )
	///
	/// @return Aucune.
	///
	/// @remark : Detruit l'arbre de rendu
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  purgeAll( void )
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->initialiser();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  translater(double deplacementX, double deplacementY)
	///
	/// @param[in]  deplacementX : Deplacement en pourcentage de la largeur.
	/// @param[in]  deplacementY : Deplacement en pourcentage de la hauteur.
	///
	/// @return Aucune.
	///
	/// @remark : Permet de faire un "plan" d'un certain pourcentage.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  translater(double deplacementX, double deplacementY)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(deplacementX, deplacementY);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  creerXML(char* path, int length, int prop[6])
	///
	/// @param[in]  position : Nom du path
	/// @param[in]  length : Taille du nom du path
	/// @param[in]  prop : Proprietes de la zone de jeu
	///
	/// @remark : Sauvegarde le path
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl creerXML(char* path, int length, int prop[6], bool force)
	{
		return FacadeModele::obtenirInstance()->creerXML(std::string(path), prop, force);
	}
	__declspec(dllexport) int __cdecl creerXMLString(std::string path, int prop[6], bool force)
	{
		return FacadeModele::obtenirInstance()->creerXML(path, prop, force);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  ouvrirXML(char* path, int length)
	///
	/// @param[in]  position : Nom du path
	/// @param[in]  length : Taille du nom du path
	///
	/// @return Aucun
	///
	/// @remark : Ouvre le path
	/// 
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int* __cdecl ouvrirXML(char* path, int length)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->vider();
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->initialiserXML(std::string(path));
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
	/// @fn __declspec(dllexport) void __cdecl  takeScreenShot(char* path, int length, bool square, int maxSize)
	///
	/// @param[in]  position : Nom du path
	/// @param[in]  length : Taille du nom du path
	/// @param[in] int maxSize : taille maximale (pixel) de l'image
	/// @param[in] bool square : forme de l'image carre
	///
	/// @return Aucun
	///
	/// @remark : Prend un screenshot de la zone de jeu
	/// 
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl takeScreenShot(char* path, int length, bool square, int maxSize)
	{
		glm::ivec2 size = FacadeModele::obtenirInstance()->obtenirTailleFenetre();
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->takeScreenShot(path, size.x, size.y, square, maxSize);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  orbite(double x, double y)
	///
	/// @param[in]  x :	Rotation x
	/// @param[in]  y : Rotation Y
	///
	/// Vue orbite TO DO, INCOMPLETE
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  orbite(double x, double y)
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
	/// @fn __declspec(dllexport) void __cdecl  zoomElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
	///
	/// @param[in]  xCoin1 : Coin initial du zoom elastique en x
	/// @param[in]  yCoin1 : Coin initial du zoom elastique en y
	/// @param[in]  xCoin2 : Coin final du zoom elastique en x
	/// @param[in]  yCoin2 : Coin final du zoom elastique en y
	///
	/// @return Aucun
	///
	/// @remark : Permet de centrer l'ecran sur la region definie par les points passes
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  zoomInElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
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
	/// @fn __declspec(dllexport) void __cdecl  zoomElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
	///
	/// @param[in]  xCoin1 : Coin initial du zoom elastique en x
	/// @param[in]  yCoin1 : Coin initial du zoom elastique en y
	/// @param[in]  xCoin2 : Coin final du zoom elastique en x
	/// @param[in]  yCoin2 : Coin final du zoom elastique en y
	///
	/// Permet de centrer l'ecran sur la region definie par les points passes
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  zoomOutElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
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
	/// @fn __declspec(dllexport) void __cdecl  deplacerSelection(int x1, int y1, int x2, int y2)
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
	__declspec(dllexport) void __cdecl  deplacerSelection(int x1, int y1, int x2, int y2, bool duplication)
	{
		FacadeModele::obtenirInstance()->deplacerSelection(x1, y1, x2, y2, duplication);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  tournerSelectionSouris(int x1, int y1, int x2, int y2)
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
	/// @remark : L'angle de rotation est calcule a partir du deplacement. On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  tournerSelectionSouris(int x1, int y1, int x2, int y2)
	{
		FacadeModele::obtenirInstance()->tournerSelectionSouris(x1, y1, x2, y2);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  agrandirSelection(int x1, int y1, int x2, int y2)
	///
	/// @param[in]  x1 : abcisse du point initial
	/// @param[in]  y1 : ordonnee du point initial
	///
	/// @param[in]  x2 : abcisse du point initial
	/// @param[in]  y2 : ordonnee du point initial
	///
	/// @return Aucun
	///
	/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...). La focntion change l'echelle des objets selectionnes. Chaque deplacement de 1 pixel vers le haut  multiplie l'echelle courrante par 1.003, et chaque deplacement vers le bas divise par 1.003.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  agrandirSelection(int x1, int y1, int x2, int y2)
	{
		FacadeModele::obtenirInstance()->agrandirSelection(x1, y1, x2, y2);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  rectangleElastique(int i, int j)
	///
	/// @param[in]  i : point suivant i de la souris
	/// @param[in]  j : point suivant j de la souris
	///
	/// @return Aucun
	///
	/// @remark : Met a jour le rectangle elastique
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  rectangleElastique(int i, int j)
	{
		FacadeModele::obtenirInstance()->rectangleElastique(i, j);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl selectionMultiple(bool c)
	///
	/// @param[in]  c : Selection inverser ou non
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
	/// @fn __declspec(dllexport) bool __cdecl verifierCliqueDansTable(int x, int y)
	///
	/// @param[in]  x : abcisse du point initial 
	/// @param[in]  y : ordonnee du point initial
	///
	/// @return true si le clic est dans la table, faux sinon.
	///
	/// @remark : Verifie si un clic est dans la table.  On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl verifierCliqueDansTable(int x, int y)
	{
		return FacadeModele::obtenirInstance()->verifierCliqueDansTable(x, y);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  deselectAll( void )
	///
	/// @return Aucun
	///
	/// @remark : Ca deselectionne tout
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  deselectAll( void )
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->deselectionnerTout();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  dupliquerSelection(int i, int j)
	///
	/// @param[in]  i : point suivant i de la souris
	/// @param[in]  j : point suivant j de la souris
	///
	/// @return Aucun
	///
	/// @remark : Permet duplique les objets selectionnes
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  dupliquerSelection(int i, int j)
	{
		FacadeModele::obtenirInstance()->dupliquerSelection(i, j);
		FacadeModele::obtenirInstance()->setDebug();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) double __cdecl getPositionX( void ) 
	///
	/// @return la position en X
	///
	/// @remark : Retourne le x de la position du dernier objet selectionne qu'on a trouve dans l'arbre.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl getPositionX( void ) {
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
	/// @fn __declspec(dllexport) double __cdecl  getPositionY( void )
	///
	/// @return la position en Y
	///
	/// @remark : Retourne le y de la position du dernier objet selectionne qu'on a trouve dans l'arbre.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl getPositionY( void )
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
	/// @fn __declspec(dllexport)  double getAngle( void )
	///
	/// @return l'angle de l'objet
	///
	/// @remark : Retourne l'angleZ du dernier objet selectionne qu'on a trouve dans l'arbre.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getAngle( void )
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
	/// @fn __declspec(dllexport) double getScale( void )
	///
	/// @return la taille de l'objet (Retourne le scale du dernier objet selectionne qu'on a trouve dans l'arbre.)
	///
	/// @remark : Le scale en y est representatif des objets normaux et des murs.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getScale( void )
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
	/// @fn __declspec(dllexport) void __cdecl  playSound()
	///
	/// @param[in]  value : Nom du son
	/// @param[in]  length : Taille du nom
	/// @param[in]  stop : Arret du son
	///
	/// @return Aucun
	///
	/// @remark Cette fonction permet de jouer un son ou de l'arreter
	///
	////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) void __cdecl  playSound(char* value, int length, bool stop)
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
	/// @fn __declspec(dllexport) void __cdecl  obligerTransparence(bool transparence)
	///
	/// @param[in]  transparence : booleen de transparence
	///
	/// @return Aucun
	///
	/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  obligerTransparence(bool transparence)
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
	/// @fn __declspec(dllexport) void __cdecl  initialiserRectangleElastique(int i, int j)
	///
	/// @param[in]  i : coordonnees i de la souris
	/// @param[in]  j : coordonnees j de la souris
	///
	/// @return Aucun
	///
	/// @remark Initialise le rectangle elastique
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  initialiserRectangleElastique(int i, int j)
	{
		FacadeModele::obtenirInstance()->initialiserRectangleElastique(i, j);
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl  terminerRectangleElastique()
	///
	/// @return Aucun
	///
	/// @remark Suprime le rectangle elastique
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  terminerRectangleElastique()
	{
		FacadeModele::obtenirInstance()->terminerRectangleElastique();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl creerMur(int originX, int originY,int x1, int y1, int x2, int y2) 
	///
	///
	/// @param[in]  originX : Position en X ou le bouton a ete appuye
	/// @param[in]  originX : Position en Y ou le bouton a ete appuye
	/// @param[in]  x1 : Position en X precedant un deplacement de la souris
	/// @param[in]  Y1 : Position en Y precedant un deplacement de la souris
	/// @param[in]  x2 : Position en X apres un deplacement de la souris (position actuelle de la souris)
	/// @param[in]  y2 : Position en X apres un deplacement de la souris (position actuelle de la souris)
	///
	/// @return Aucun
	///
	/// @remark : Cette fonction place un mur dont un bout est la ou le bouton gauche de la souris a ete appuye, et l'autre bout est sous le curseur de la souris.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  creerMur(int originX, int originY, int x1, int y1, int x2, int y2)
	{
		FacadeModele::positionnerMur(originX,originY,x1, y1, x2, y2, objet);
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl setProprietesNoeud(int x, int y, int angle, double scale)
	///
	///
	/// @param[in]  x : X en coordonnees du monde qu'on veut donner a notre noeud.
	/// @param[in]  y : Y en coordonnees du monde qu'on veut donner a notre noeud.
	/// @param[in]	angle : angle de rotation
	///	@param[in]	scale: scale de l'objet
	///
	/// @return bool
	///
	/// @remark : La fonction calcule la boite englobante de l'objet transforme, le calcul est differend pour les murs. Il manque quelque chose pour le calcul des boîtes englobantes transformees des objets de type mur.
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl setProprietesNoeud(int x, int y, int angle, double scale)
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
	/// @fn __declspec(dllexport) double __cdecl obtenirZoomCourant( void )
	///
	/// @return : double, valeur du zoom courant	
	///
	/// @remark La valeur du facteur de zoom appliquer sur la fenetre
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl obtenirZoomCourant( void )
	{
		if (FacadeModele::obtenirInstance() == nullptr)
			return -1;
		return FacadeModele::obtenirInstance()->obtenirZoomCourant();
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl obtenirCentreMasseX( void )
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
	/// @fn __declspec(dllexport) int __cdecl obtenirCentreMasseY( void )
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
	/// @fn __declspec(dllexport) bool __cdecl resetZoom()
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
	/// @fn __declspec(dllexport) bool __cdecl duplicationEstHorsTable( void )
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

	__declspec(dllexport) void __cdecl creerFichierConfig(int config[13])
	{
		FacadeModele::obtenirInstance()->sauvegarderConfig(config);
	}
	
	__declspec(dllexport) int* __cdecl chargerFichierConfiguration()
	{
		return FacadeModele::obtenirInstance()->obtenirConfiguration();
	}

	__declspec(dllexport) int __cdecl obtenirDifficulte(char* nomFichier, int length)
	{
		return FacadeModele::obtenirInstance()->obtenirDifficulte(nomFichier, length);
	}

	__declspec(dllexport) int* __cdecl obtenirProprietes(char* nomFichier, int length)
	{
		return FacadeModele::obtenirInstance()->obtenirProprietes(nomFichier, length);
	}
	__declspec(dllexport) void __cdecl creerFichierCampagne(char* listMaps, int length)
	{
		FacadeModele::obtenirInstance()->sauvegarderCampagne(listMaps, length);
	}

	__declspec(dllexport) int __cdecl obtenirTouchePGJ1()
	{
		return FacadeModele::obtenirInstance()->obtenirTouchePGJ1(); 
	}

	__declspec(dllexport) int __cdecl obtenirTouchePGJ2()
	{
		return FacadeModele::obtenirInstance()->obtenirTouchePGJ2(); 
	}

	__declspec(dllexport) int __cdecl obtenirTouchePDJ1()
	{
		return FacadeModele::obtenirInstance()->obtenirTouchePDJ1(); 
	}

	__declspec(dllexport) int __cdecl obtenirTouchePDJ2()
	{
		return FacadeModele::obtenirInstance()->obtenirTouchePDJ2(); 
	}

	__declspec(dllexport) int __cdecl obtenirToucheRessort()
	{
		return FacadeModele::obtenirInstance()->obtenirToucheRessort(); 
	}

	__declspec(dllexport) int __cdecl obtenirNombreDeBilles()
	{
		return FacadeModele::obtenirInstance()->obtenirNombreDeBilles();
	}

	__declspec(dllexport) int __cdecl obtenirModeDoubleBille()
	{
		return FacadeModele::obtenirInstance()->obtenirModeDoubleBille();
	}

	__declspec(dllexport) int __cdecl obtenirAffichageGlobal()
	{
		return FacadeModele::obtenirInstance()->obtenirAffichageGlobal();
	}
	__declspec(dllexport) void __cdecl bloquerAffichageGlobal(int active)
	{
		FacadeModele::obtenirInstance()->bloquerAffichageGlobal(active);
		FacadeModele::obtenirInstance()->setDebug();
	}

	__declspec(dllexport) void __cdecl activerPalettesGJ1()
	{
		FacadeModele::obtenirInstance()->activerPalettesGJ1();
	}

	__declspec(dllexport) void __cdecl desactiverPalettesGJ1()
	{
		FacadeModele::obtenirInstance()->desactiverPalettesGJ1();
	}

	__declspec(dllexport) void __cdecl activerPalettesDJ1()
	{
		FacadeModele::obtenirInstance()->activerPalettesDJ1();
	}

	__declspec(dllexport) void __cdecl desactiverPalettesDJ1()
	{
		FacadeModele::obtenirInstance()->desactiverPalettesDJ1();
	}

	__declspec(dllexport) void __cdecl activerPalettesGJ2()
	{
		FacadeModele::obtenirInstance()->activerPalettesGJ2();
	}
	__declspec(dllexport) void __cdecl desactiverPalettesGJ2()
	{
		FacadeModele::obtenirInstance()->desactiverPalettesGJ2();
	}
	__declspec(dllexport) void __cdecl activerPalettesDJ2()
	{
		FacadeModele::obtenirInstance()->activerPalettesDJ2();
	}
	__declspec(dllexport) void __cdecl desactiverPalettesDJ2()
	{
		FacadeModele::obtenirInstance()->desactiverPalettesDJ2();
	}




	__declspec(dllexport) BSTR obtenirDerniereCampagne()
	{
		// http://stackoverflow.com/questions/6284524/bstr-to-stdstring-stdwstring-and-vice-versa
		std::string str = FacadeModele::obtenirInstance()->obtenirDerniereCampagne();
		return stringToBSTR(str);
	}

	__declspec(dllexport) void __cdecl supprimerBille()
	{
		FacadeModele::obtenirInstance()->supprimerBille();
	}

	__declspec(dllexport) void __cdecl construireListesPalettes()
	{
		FacadeModele::obtenirInstance()->construireListesPalettes();
	}

	__declspec(dllexport) void __cdecl mettreAJourListeBillesEtNoeuds()
	{
		FacadeModele::obtenirInstance()->mettreAJourListeBillesEtNoeuds();
	}

	__declspec(dllexport) void __cdecl modePause(bool pause)
	{
		FacadeModele::obtenirInstance()->setPause(pause);
	}

	__declspec(dllexport) bool __cdecl spotLight(int lum, bool state)
	{
		// See this for light:
		// http://www.gamedev.net/topic/564426-create-glow-with-gl_emission/
		bool debugLumiere = FacadeModele::obtenirInstance()->obtenirConfiguration()[12] && FacadeModele::obtenirInstance()->obtenirConfiguration()[10];

		if (lum > 2 || lum < 0)
			return false;
		if (debugLumiere) {
			printCurrentTime();
			std::cout << " - Lumiere(s) ";
		}
		switch (lum) {
		case 0:
			if (debugLumiere)
				std::cout << "ambiante ";
			// TO DO: the spotlight ambiante
			break;
		case 1:
			if (debugLumiere)
				std::cout << "directionnelle ";
			// TO DO: the spotlight directionnelle
			break;
		case 2:
			if (debugLumiere)
				std::cout << "spot ";
			break;
		default:
			return false;
			break;
		}
		if (debugLumiere)
			if (state == true)
				std::cout << "ouverte(s)" << std::endl;
			else
				std::cout << "fermee(s)" << std::endl;
		return true;
	}

	__declspec(dllexport) void __cdecl initialiserSingleton()
	{
		SingletonGlobal::obtenirInstance();
	}

	__declspec(dllexport) void __cdecl detruireSingleton()
	{
		SingletonGlobal::libererInstance();
	}

	__declspec(dllexport) int __cdecl obtenirPointsGagnerBille()
	{
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirProprietes()[4];
	}

	__declspec(dllexport) int __cdecl obtenirPointsGagnerPartie()
	{
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirProprietes()[3];
	}

	__declspec(dllexport) int __cdecl obtenirNombreDePointsDePartie()
	{
		return SingletonGlobal::obtenirInstance()->getPointsPartie();
	}

	__declspec(dllexport) void __cdecl resetNombreDePointsDePartie()
	{
		SingletonGlobal::obtenirInstance()->setPointsPartie(0);
	}

	__declspec(dllexport) int __cdecl obtenirNombreBillesCourante()
	{
		return SingletonGlobal::obtenirInstance()->obtenirBille();
	}

	__declspec(dllexport) void __cdecl resetNombreBillesCourantes()
	{
		SingletonGlobal::obtenirInstance()->resetBille();
	}

	__declspec(dllexport) void __cdecl compresserRessort()
	{
		return FacadeModele::obtenirInstance()->compresserRessort();
	}

	__declspec(dllexport) void __cdecl relacherRessort()
	{
		return FacadeModele::obtenirInstance()->relacherRessort();
	}

	__declspec(dllexport) void __cdecl animerJeu(bool animer)
	{
		SingletonGlobal::obtenirInstance()->setAnimation(animer);
		for (unsigned int i = 0; i < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants(); i++)
			FacadeModele::obtenirInstance()->assignerAnimer(animer, FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(i));
	}

	__declspec(dllexport) void __cdecl rechargerArbre(bool recharger)
	{
		if (recharger)
			ouvrirXMLString(SingletonGlobal::obtenirInstance()->obtenirPathTemp());
		else
			creerXMLString(SingletonGlobal::obtenirInstance()->obtenirPathTemp(),
				FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirProprietes(), true);
	}

	__declspec(dllexport) void __cdecl activerAI(bool actif)
	{
		FacadeModele::obtenirInstance()->assignerAI(actif);
	}

	//__declspec(dllexport) int __cdecl obtenirNombreDePointsTotals()
	//{
	//	return SingletonGlobal::obtenirInstance()->getPointsTotales();
	//}

	/*
	#include <FTGL/ftgl.h>

	Utile pour écrire du texte si on click pas sur le putin de rendu openGL

	FTGLPixmapFont font("media/fonts/Bloodthirsty.ttf");
	glRasterPos3f(0.0F, 0.0F, 100.F);
	font.FaceSize(50);
	font.Render("Hello World");

	*/

}// FIN DU extern "C"