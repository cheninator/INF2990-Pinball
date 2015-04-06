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

typedef std::tuple<FTPoint, glm::fvec3, unsigned int, char*, Position > textContainer;

class ControleurTexte
{
public:
	// Pointer to the FMOD instance

	ControleurTexte();
	~ControleurTexte();
	void creeFont(char* path);
	void creeTexte(char* text, char* font = "");
	void updateText(char* oldText, char* newText);
	void suprimerText(char* text);
	void afficherTexte(bool afficher = false);
	void changerCouleur(char* text, float rouge, float vert, float bleu);
	void changerCouleur(char* text, glm::fvec3 couleur);
	void repositionner(char* text, float posX, float posY);
	void resize(char* text, unsigned int size);
	void refresh(int x, int y);

private:
	std::string getFontPath(char* sName);
	void populateFontVector(std::string targetPath);
	unsigned int lookUpFont(std::string fileName);
	unsigned int lookUpText(char* textString);
	void renderText(int i);
	float obtenirDecalageY(unsigned int objectIndex);

	std::vector<std::pair<std::string, FTGLPixmapFont*>> fontTable_;
	std::vector<std::pair<char*, textContainer>> texts_;

	// default const
	textContainer const defaultObject_{	{ 500, 500 }, { .5f, 1.f, 1.f }, { 32 },  { "arial.tff" }, Position::E };
	glm::ivec2 posMax { 500, 500 };
};

#endif //__FACADE_TEXT_CONTROLLER_CLASS_H__