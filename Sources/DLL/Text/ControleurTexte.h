//////////////////////////////////////////////////////////////////////////////
/// @file ControleurTexte.h
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Texte
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __FACADE_TEXT_CONTROLLER_CLASS_H__
#define __FACADE_TEXT_CONTROLLER_CLASS_H__

#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <FTGL/ftgl.h>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "ControleurTexteDefine.h"
#include <algorithm>

typedef std::tuple<FTPoint, glm::fvec3, unsigned int, std::string, Position > textContainer;

///////////////////////////////////////////////////////////////////////////
/// @class ControleurTexte
/// @brief Structure de donnee qui contient des textes et des fonts. Offre des interfaces utiles.
///
/// @author The Ballers
/// @date 2015-02-24
///////////////////////////////////////////////////////////////////////////
class ControleurTexte
{
public:
	/// Constructeur
	ControleurTexte();

	/// Destructeur
	~ControleurTexte();

	/// On ne construit pas par copie
	ControleurTexte& operator=(ControleurTexte const&) = delete;

	///  On cree du texte
	void creeTexte(std::string text, std::string font = "");

	/// Met a jour le texte
	void updateText(std::string oldText, std::string newText);
	
	/// Suprime le texte
	void suprimerText(std::string text);
	
	/// Affiche les textes
	void afficherTextes(bool afficher = true) { afficher_ = afficher;};
	
	/// Met a jour l'affichage
	void refreshAffichage();
	
	/// Changer la couleur du texte
	void changerCouleur(std::string text, float rouge, float vert, float bleu);
	
	/// Changer la couleur du texte via vecteur
	void changerCouleurV(std::string text, glm::fvec3 couleur);
	
	/// Repositionner le string
	void repositionner(std::string text, float posX, float posY);
	
	/// Adapter la taille du string
	void resize(std::string text, unsigned int size);
	
	/// Rafraichis les position du texte
	void refresh(int x, int y);

private:
	/// Cree une font
	void creeFont(std::string path);

	/// Obtiens le path vers la font
	std::string getFontPath(std::string sName);

	/// populate le vecteur de font
	void populateFontVector(std::string targetPath);

	/// Cherche une font
	unsigned int lookUpFont(std::string fileName);

	/// Cherche un string
	unsigned int lookUpText(std::string textString);

	/// Affice le texte
	void renderText(int i);

	/// Donne le decalage en y
	float obtenirDecalageY(unsigned int objectIndex);
	
	/// Contient tout les fonts
	std::vector<std::pair<std::string, FTGLPixmapFont*>> fontTable_;


	/// Contiens tout les texts strings
	std::vector<std::pair<std::string, textContainer>> texts_;

	/// Affichage
	bool afficher_{ false };

	/// Contenur des objets, cosntant par defaut
	textContainer const defaultObject_{	{ 500, 500 }, { .5f, 1.f, 1.f }, { 32 },  { "arial.tff" }, Position::E };
	
	/// Position maximale (qui sera modifier au moment de la creation openGL)
	glm::ivec2 posMax_{ 500, 500 };
};

#endif //__FACADE_TEXT_CONTROLLER_CLASS_H__