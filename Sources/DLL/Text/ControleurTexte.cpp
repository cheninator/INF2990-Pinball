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
	std::cout << "Debut de la generation des fonts: " << std::endl;
	populateFontVector(targetPath);
	//populateFontVector("C:\\Windows\\Fonts\\");
	std::cout << "Fin de la generation des fonts." << std::endl;
}

ControleurTexte::~ControleurTexte()
{
	// Si je fais delete ici, ca shie...
	for (unsigned int i = 0; i < fontTable_.size(); i++)
		fontTable_[i].second = nullptr;
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
		creeFont((char*)name.c_str());
	}
}

void ControleurTexte::creeFont(char* sName)
{
	std::string name(sName);
	bool fontGenerated = true;

	// Check if already created
	for (unsigned int i = 0; i < fontTable_.size(); i++)
		if (fontTable_[i].first == name)
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
		fontTable_.push_back(aPair);
	}
}

void ControleurTexte::creeTexte(char* texte, char* font)
{
	int textIndex = lookUpText(texte);
	std::get<3>(texts_[textIndex].second) = font;
}

void ControleurTexte::afficherTexte(bool pause)
{	
	if (fontTable_.size() <= 0 || pause)
		return;
	for (unsigned int i = 0; i < texts_.size(); i++)
		renderText(i);
}

void ControleurTexte::renderText(int textIndex)
{
	char* useFont = std::get<3>(texts_[textIndex].second);
	unsigned int size = std::get<2>(texts_[textIndex].second);
	glm::fvec3 color = std::get<1>(texts_[textIndex].second);
	char* texte = texts_[textIndex].first;
	FTPoint position = std::get<0>(texts_[textIndex].second);

	int fontIndex = lookUpFont(std::string(useFont));
	if (fontIndex < 0)
		fontIndex = 0;

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	fontTable_[fontIndex].second->FaceSize(size);

	//Dark red text
	glPixelTransferf(GL_RED_BIAS, -color.x);
	glPixelTransferf(GL_GREEN_BIAS, -color.y);
	glPixelTransferf(GL_BLUE_BIAS, -color.z);

	fontTable_[fontIndex].second->Render(texte, -1, position);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}


std::string ControleurTexte::getPath(char* sName)
{
	std::string soundPath = "media/Fonts/" + std::string(sName);
	return soundPath;
}

// TODO cree une enum de couleur
void ControleurTexte::changerCouleur(char* text, float rouge, float vert, float bleu)
{
	if (rouge > 1)
		rouge = 1;
	else if (rouge < 0)
		rouge = 0;
	if (vert > 1)
		vert = 1;
	else if (vert < 0)
		vert = 0;
	if (bleu > 1)
		bleu = 1;
	else if (bleu < 0)
		bleu = 0;
	
	int textIndex = lookUpText(text);
	std::get<1>(texts_[textIndex].second) = {1 - rouge, 1 - vert, 1 - bleu};
}

void ControleurTexte::changerCouleur(char* text, glm::fvec3 couleur)
{
	if (couleur.x > 1)
		couleur.x /= 255;
	else if (couleur.x < 0)
		couleur.x = 0;
	if (couleur.y > 1)
		couleur.y /= 255;
	else if (couleur.y < 0)
		couleur.y = 0;
	if (couleur.z > 1)
		couleur.z /= 255;
	else if (couleur.z < 0)
		couleur.z = 0;

	int textIndex = lookUpText(text);
	std::get<1>(texts_[textIndex].second) = { 1 - couleur.x, 1 - couleur.y, 1 - couleur.z };
}
// TODO cree une enum de position (comme au theatre)
void ControleurTexte::repositionner(char* text, float posX, float posY)
{
	int textIndex = lookUpText(text);
	char* myFont = std::get<3>(texts_[textIndex].second);
	int fontIndex = lookUpFont(std::string(myFont));
	if (fontIndex < 0)
		fontIndex = 0;
	FTBBox boiteText = fontTable_[fontIndex].second->BBox(text);
	FTPoint boiteTextLower = boiteText.Lower();
	FTPoint boiteTextUpper = boiteText.Upper();

	// TODO Revoir le calcul ici
	FTPoint positionTexte = FTPoint(posX - (boiteTextUpper.X() - boiteTextLower.X()),
		posY - (boiteTextUpper.Y() - boiteTextLower.Y()));
	
	std::get<0>(texts_[textIndex].second) = FTPoint(posX, posY);
}

void ControleurTexte::resize(char* text, unsigned int size)
{
	int textIndex = lookUpText(text);
	std::get<2>(texts_[textIndex].second) = size;
}

int ControleurTexte::lookUpFont(std::string fileName)
{
	for (unsigned int i = 0; i < fontTable_.size(); i++)
		if (fontTable_[i].first == fileName)
			return i;
	return -1;
}


int ControleurTexte::lookUpText(char* textString)
{
	for (unsigned int i = 0; i < texts_.size(); i++)
		if (texts_[i].first == textString)
			return i;
	std::pair<char*, textContainer> newDefaultText;
	newDefaultText.first = textString;
	newDefaultText.second = defaultObject_;
	texts_.push_back(newDefaultText);
	return (int)texts_.size() - 1;
}