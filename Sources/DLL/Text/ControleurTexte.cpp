#include "ControleurTexte.h"

#include "../Application/FacadeModele.h"
#include "../Global/SingletonGlobal.h"

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

	std::string path = getFontPath(sName);
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

void ControleurTexte::updateText(char* oldText, char* newText)
{
	int textIndex = lookUpText(oldText);
	texts_[textIndex].first = newText;
}
void ControleurTexte::suprimerText(char* text)
{
	int textIndex = lookUpText(text);
	texts_.erase(texts_.begin() + textIndex);
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
	mettreAjourBordures();
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


std::string ControleurTexte::getFontPath(char* sName)
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

	unsigned int textIndex = lookUpText(text);
	std::get<1>(texts_[textIndex].second) = { 1 - couleur.x, 1 - couleur.y, 1 - couleur.z };
}
// TODO cree une enum de position (comme au theatre)
void ControleurTexte::repositionner(char* text, float posX, float posY)
{
	mettreAjourBordures();
	unsigned int textIndex = lookUpText(text);
	char* myFont = std::get<3>(texts_[textIndex].second);
	unsigned int fontIndex = lookUpFont(std::string(myFont));
	if (fontTable_.size() == 0)
		return;
	FTBBox boiteText = fontTable_[fontIndex].second->BBox(text);
	FTPoint boiteTextLower = boiteText.Lower();
	FTPoint boiteTextUpper = boiteText.Upper();

	/* ICI on as 5 cas possible : 
		A: (X = 0, Y = 0) -> coin inferieur gauche
		B: (X = 0, Y = 1) -> coin superieur gauche
		C: (X = 1, Y = 1) -> coin superieur droit
		D: (X = 1, Y = 0) -> coin inferieur droit
		E: (X > 1, Y > 1) -> quelque part dans la map

				   D __________ C
					|		   |
					|		   |
					|	.E	   |
					|__________|
			 (0,0) A			B
	*/
	FTPoint positionTexte = FTPoint(posX, posY);
	float decalage = obtenirDecalageY(textIndex);
	if (posX == 0)
	{
		if (posY == 0)			// A
		{
			positionTexte = FTPoint(0,
									0 + textIndex);
		}
		else if (posY == 1)		// B
		{
			positionTexte = FTPoint(posMax.x - (boiteTextUpper.X() - boiteTextLower.X()),
									0 + textIndex);
		}
	}
	else if (posX == 1)
	{
		if (posY == 0)			// D
		{
			positionTexte = FTPoint(0,
									posMax.y - (boiteTextUpper.Y() - boiteTextLower.Y()) - decalage);
		}
		else if (posY == 1)		// C
		{
			positionTexte = FTPoint(posMax.x - (boiteTextUpper.X() - boiteTextLower.X()),
									posMax.y - (boiteTextUpper.Y() - boiteTextLower.Y()) - decalage);
		}
	}
	
	std::get<0>(texts_[textIndex].second) = positionTexte;
}
float ControleurTexte::obtenirDecalageY(unsigned int objectIndex)
{
	float decalage = 0;
	for (unsigned int i = 0; i < objectIndex; i++)
	{
		unsigned int fontIndex = lookUpFont(std::get<3>(texts_[i].second));
		FTBBox boiteText = fontTable_[fontIndex].second->BBox(texts_[i].first);
		FTPoint boiteTextLower = boiteText.Lower();
		FTPoint boiteTextUpper = boiteText.Upper();
		if (std::get<0>(texts_[i].second).Yf() + boiteTextUpper.Yf() >= posMax.y - 2*posMax.y/100)
			decalage += boiteTextUpper.Yf() - boiteTextLower.Yf();
		else if (std::get<0>(texts_[i].second).Yf() + boiteTextUpper.Yf() <= posMax.y / 100)
			decalage += boiteTextUpper.Yf() - boiteTextLower.Yf();
	}
 	return decalage;
}

void ControleurTexte::resize(char* text, unsigned int size)
{
	unsigned int textIndex = lookUpText(text);
	std::get<2>(texts_[textIndex].second) = size;
}

unsigned int ControleurTexte::lookUpFont(std::string fileName)
{
	for (unsigned int i = 0; i < fontTable_.size(); i++)
		if (fontTable_[i].first == fileName)
			return i;
	return 0;
}

unsigned int ControleurTexte::lookUpText(char* textString)
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

void ControleurTexte::mettreAjourBordures()
{
	posMax = FacadeModele::obtenirInstance()->obteniCoordonneeMax();
}