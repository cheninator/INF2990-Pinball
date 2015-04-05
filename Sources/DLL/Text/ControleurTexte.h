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
#include <algorithm>

class ControleurTexte
{
public:
	// Pointer to the FMOD instance

	ControleurTexte();
	~ControleurTexte();
	void populateFontVector(std::string targetPath);
	void creeTexte(char* path);
	void afficherTexte(char* texte = "Hello World", bool afficher = false, char* useFont = "arial.tff");

	void changerCouleur(float rouge, float vert, float bleu);
	void repositionner(float posX, float posY);
	void resize(float size) { size_ = size; }

private:
	std::string getPath(char* sName);
	int lookUp(std::string fileName);
	std::vector<std::pair<std::string, FTGLPixmapFont*>> fontTable;

	float red_{ .5f };
	float green_{ 1.f };
	float blue_{ 1.f };

	float size_{ 32.f };
	glm::ivec2 position_{ 500, 500 };
};

#endif //__FACADE_TEXT_CONTROLLER_CLASS_H__