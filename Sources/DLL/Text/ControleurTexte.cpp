#include "ControleurTexte.h"

#include "../Application/FacadeModele.h"

ControleurTexte::ControleurTexte()
{
	TCHAR buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring wBuffer(buffer);
	std::string currentFolder(wBuffer.begin(), wBuffer.end());
	std::string::size_type position = currentFolder.find_last_of("\\/");
	std::string targetPath = std::string(currentFolder).substr(0, position);
	targetPath += "\\media\\Fonts\\";
	populateFontVector(targetPath);
	//populateFontVector("C:\\Windows\\Fonts\\");
}

ControleurTexte::~ControleurTexte()
{
	for (unsigned int i = 0; i < fontTable.size(); i++)
		delete fontTable[i].second;
}

void ControleurTexte::populateFontVector(std::string targetPath)
{
	const char* d = targetPath.c_str();
	std::vector<std::string> f;

	FILE* pipe = NULL;
	std::string pCmd = "dir /B /S " + std::string(d);
	char buf[256];

	if (NULL == (pipe = _popen(pCmd.c_str(), "rt")))
	{
		return;
	}

	while (!feof(pipe))
	{
		if (fgets(buf, 256, pipe) != NULL)
		{
			f.push_back(std::string(buf));
		}
	}
	_pclose(pipe);
	for (unsigned int i = 0; i < f.size(); i++)
	{
		std::string name = f[i];
		name.erase(0, targetPath.length());
		name.erase(name.length() - 1);
		creeTexte((char*)name.c_str());
	}
}

void ControleurTexte::creeTexte(char* sName)
{
	std::string name(sName);
	bool fontGenerated = true;

	// Check if already created
	for (unsigned int i = 0; i < fontTable.size(); i++)
		if (fontTable[i].first == name)
			return;

	std::string path = getPath(sName);
	const char* sPath = path.c_str();
	std::cout << "\tAdding " << name << "..." << std::setw(40 - name.length());
	FTGLPixmapFont* someFont = new FTGLPixmapFont(sPath);
	if(someFont->Error() == 1)
		fontGenerated = false;
	std::cout << (fontGenerated ? "OK" : "FAILED") << std::endl;
	if (fontGenerated)
	{
		std::pair<char*, FTGLPixmapFont*> aPair;
		aPair.first = sName;
		aPair.second = someFont;
		fontTable.push_back(aPair);
	}
}

void ControleurTexte::afficherTexte(char* texte, bool pause, char* useFont)
{
	int i = lookUp(std::string(useFont));
	if (i < 0)
		i = 0;
	if (fontTable.size() <= 0)
		return;
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	fontTable[i].second->FaceSize(size_);

	//Dark red text
	glPixelTransferf(GL_RED_BIAS, -red_);
	glPixelTransferf(GL_GREEN_BIAS, -green_);
	glPixelTransferf(GL_BLUE_BIAS, -blue_);

	FTBBox boiteText = fontTable[i].second->BBox(texte);
	FTPoint boiteTextLower = boiteText.Lower();
	FTPoint boiteTextUpper = boiteText.Upper();
	FTPoint positionTexte = FTPoint(position_.x - (boiteTextUpper.X() - boiteTextLower.X()),
									position_.y - (boiteTextUpper.Y() - boiteTextLower.Y()));
	fontTable[i].second->Render(texte, -1, positionTexte);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

std::string ControleurTexte::getPath(char* sName)
{
	std::string soundPath = "media/Fonts/" + std::string(sName);
	return soundPath;
}

void ControleurTexte::changerCouleur(float rouge, float vert, float bleu)
{
	red_ = 1 - rouge;
	green_ = 1 - vert;
	blue_ = 1 - bleu;
}

void ControleurTexte::repositionner(float posX, float posY)
{
	position_ = glm::ivec2(posX, posY);
}

int ControleurTexte::lookUp(std::string fileName)
{
	for (unsigned int i = 0; i < fontTable.size(); i++)
		if (fontTable[i].first == fileName)
			return i;

	/*creeTexte((char*)fileName.c_str());

	for (unsigned int i = 0; i < fontTable.size(); i++)
		if (fontTable[i].first == fileName)
			return i;

	//std::cout << "ERROR: " << fileName << " not found !"*/;
	return -1;
}