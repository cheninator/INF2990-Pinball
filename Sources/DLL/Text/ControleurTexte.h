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

class ControleurTexte
{
public:
	// Pointer to the FMOD instance

	ControleurTexte();
	~ControleurTexte();
	void creeTexte(std::string text, std::string font = "");
	void updateText(std::string oldText, std::string newText);
	void suprimerText(std::string text);
	void afficherTextes(bool afficher = true) { afficher_ = afficher;};
	void refreshAffichage();
	void changerCouleur(std::string text, float rouge, float vert, float bleu);
	void changerCouleurV(std::string text, glm::fvec3 couleur);
	void repositionner(std::string text, float posX, float posY);
	void resize(std::string text, unsigned int size);
	void refresh(int x, int y);

private:
	void creeFont(std::string path);
	std::string getFontPath(std::string sName);
	void populateFontVector(std::string targetPath);
	unsigned int lookUpFont(std::string fileName);
	unsigned int lookUpText(std::string textString);
	void renderText(int i);
	float obtenirDecalageY(unsigned int objectIndex);

	std::vector<std::pair<std::string, FTGLPixmapFont*>> fontTable_;
	std::vector<std::pair<std::string, textContainer>> texts_;

	bool afficher_{ false };

	// default const
	textContainer const defaultObject_{	{ 500, 500 }, { .5f, 1.f, 1.f }, { 32 },  { "arial.tff" }, Position::E };
	glm::ivec2 posMax_{ 500, 500 };
};

#endif //__FACADE_TEXT_CONTROLLER_CLASS_H__