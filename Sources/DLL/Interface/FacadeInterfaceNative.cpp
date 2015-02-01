////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.cpp
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
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
	static NoeudAbstrait* objet = new NoeudAbstrait();
	static double facteurDeTransition; // DONT ASK WHY


	////////////////////////////////////////////////////////////////////////
	///
	/// static void calculerTransition(void)
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
	static void calculerTransition(void)
	{
		glm::dvec3 positionZero;
		glm::dvec3 positionUn;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(0, 0, positionZero);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(100, 100, positionUn);
		facteurDeTransition = (((positionUn.y - positionZero.y) / 100 ) + ((positionUn.y - positionZero.y)/100))/(-2);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
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

		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND) handle);
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
	/// __declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
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
		FacadeModele::obtenirInstance()->animer((float) temps);
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
	///
	/// Cette fonction permet de cree un objet 3D
	///
	/// @return Aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl creerObjet(char* value, int length)
	{
		std::string nomObjet (value);
		objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(nomObjet);
		if (objet == nullptr)
			return;
		// Ca ne sert a rien de rajouter un Node "vide" dans l'arbre
		else if (nomObjet == "vide")
			return;
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(objet);
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
		glm::dvec3 maPosition;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, maPosition);
		objet->assignerPositionRelative({ maPosition.x, maPosition.y, z });
		std::cout << std::endl << "x: " << maPosition.x << "y: " << maPosition.y << "z: " << maPosition.z << std::endl;
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
		calculerTransition();
		glm::dvec3 maPositionPresente;
		maPositionPresente = objet->obtenirPositionRelative();
		objet->assignerPositionRelative({ maPositionPresente.x + x * facteurDeTransition ,
										  maPositionPresente.y + y * facteurDeTransition ,
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
		calculerTransition();

		glm::dvec3 monScalePresent;
		float deltaScale = (float)myScale;
		monScalePresent = objet->obtenirAgrandissement();
		monScalePresent.x += myScale * facteurDeTransition;
		monScalePresent.y += myScale * facteurDeTransition;
		monScalePresent.z += myScale * facteurDeTransition;
		if (monScalePresent.x <= 0)
			monScalePresent.x -= myScale * facteurDeTransition;
		if (monScalePresent.y <= 0)
			monScalePresent.y -= myScale * facteurDeTransition;
		if (monScalePresent.z <= 0)
			monScalePresent.z -= myScale * facteurDeTransition;
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
		objet->~NoeudAbstrait();
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
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
