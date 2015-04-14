////////////////////////////////////////////////////////////////////////////////////
/// @file ControleurTexte.cpp
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Texte
///
////////////////////////////////////////////////////////////////////////////////////


#include "ControleurTexte.h"

#include "../Application/FacadeModele.h"
#include "../Global/SingletonGlobal.h"
#define MARGE_X 5
#define MARGE_Y 5


////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurTexte::ControleurTexte()
///
/// Constructeur
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurTexte::~ControleurTexte()
///
/// Vide la table des fonts
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ControleurTexte::~ControleurTexte()
{
	// Si je fais delete ici, ca shie...
	for (unsigned int i = 0; i < fontTable_.size(); i++)
		fontTable_[i].second = nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::populateFontVector(std::string targetPath)
///
/// Methode qui va chercher les fichiers ttf depuis un dossier
///
/// @param[in] targetPath : Le path du dossier
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurTexte::populateFontVector(std::string targetPath)
{
	const char* d = targetPath.c_str();
	std::vector<std::string> f;

	FILE* pipe = NULL;
	std::string pCmd = "dir /B /S \"" + std::string(d) + char(34);
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
		char* fileName = (char*)name.c_str();
		creeFont(fileName);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::creeFont(std::string sName)
///
/// Cree la font
///
/// @param[in] sName : Le nom de la font
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurTexte::creeFont(std::string sName)
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
		std::pair<std::string, FTGLPixmapFont*> aPair;
		aPair.first = name;
		aPair.second = someFont;
		fontTable_.push_back(aPair);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::updateText(std::string oldText, std::string newText)
///
/// Modifie un texte
///
/// @param[in] oldText : Le texte afficher en ce moment
/// @param[in] newText : Le texte qui modifiera le vieu
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurTexte::updateText(std::string oldText, std::string newText)
{
	int textIndex = lookUpText(oldText);
	texts_[textIndex].first = newText;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::suprimerText(std::string text)
///
/// Suprime un texte
///
/// @param[in] text : Le texte afficher en ce moment
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurTexte::suprimerText(std::string  text)
{
	int textIndex = lookUpText(text);
	texts_.erase(texts_.begin() + textIndex);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::creeTexte(std::string texte, std::string font)
///
/// Cree un texte
///
/// @param[in] texte : Le texte a cree
/// @param[in] font : La font qu'on dois lier avec le texte
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurTexte::creeTexte(std::string texte, std::string font)
{
	int textIndex = lookUpText(texte);
	std::get<3>(texts_[textIndex].second) = font;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::refreshAffichage()
///
/// Refresh tout les affichages (oblige un reRender)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurTexte::refreshAffichage()
{
	if (fontTable_.size() <= 0 || !afficher_)
		return;
	for (unsigned int i = 0; i < texts_.size(); i++)
		renderText(i);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::renderText(int textIndex)
///
/// Affiche un texte
/// @param[in] textIndex : la position du texte dans le vecteur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurTexte::renderText(int textIndex)
{
	char* useFont = (char*)(std::get<3>(texts_[textIndex].second)).c_str();
	unsigned int size = std::get<2>(texts_[textIndex].second);
	glm::fvec3 color = std::get<1>(texts_[textIndex].second);
	char* texte = (char*)texts_[textIndex].first.c_str();
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


////////////////////////////////////////////////////////////////////////
///
/// @fn std::string ControleurTexte::getFontPath(std::string sName)
///
/// @remark ajout media/Fonts/ au string qu'il recoit 
///
/// @param[in] sName : un string
///
/// @return le nouveau string.
///
////////////////////////////////////////////////////////////////////////
std::string ControleurTexte::getFontPath(std::string sName)
{
	std::string soundPath = "media/Fonts/" + std::string(sName);
	return soundPath;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::changerCouleur(std::string text, float rouge, float vert, float bleu)
///
/// @remark Change la couleur
///
/// @param[in] text : le string
/// @param[in] rouge : la couleur rouge
/// @param[in] vert : la couleur vert
/// @param[in] bleu : la couleur bleu
///
/// @return Rien.
///
////////////////////////////////////////////////////////////////////////
void ControleurTexte::changerCouleur(std::string text, float rouge, float vert, float bleu)
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


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::changerCouleurV(std::string text, glm::fvec3 couleur)
///
/// @remark Change la couleur via un vecteur
///
/// @param[in] text : le string
/// @param[in] couleur : vecteur de couleur
///
/// @return Rien.
///
////////////////////////////////////////////////////////////////////////
void ControleurTexte::changerCouleurV(std::string text, glm::fvec3 couleur)
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


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::repositionner(std::string text, float posX, float posY)
///
/// @remark Changer la position du texte
///
/// @param[in] text : le string
/// @param[in] posX : position x
/// @param[in] posY : position y
///
/// @return Rien.
///
////////////////////////////////////////////////////////////////////////
void ControleurTexte::repositionner(std::string text, float posX, float posY)
{
	unsigned int textIndex = lookUpText(text);
	char* myFont = (char*)(std::get<3>(texts_[textIndex].second)).c_str();
	int textSize = std::get<2>(texts_[textIndex].second);
	unsigned int fontIndex = lookUpFont(std::string(myFont));
	if (fontTable_.size() == 0)
		return;
	fontTable_[fontIndex].second->FaceSize(textSize);
	FTBBox boiteText = fontTable_[fontIndex].second->BBox((char*)text.c_str());
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
	if (posX == 0)
	{
		if (posY == 0)			// A
			std::get<4>(texts_[textIndex].second) = Position::A;
		else if (posY == 1)		// B
			std::get<4>(texts_[textIndex].second) = Position::B;
	}
	else if (posX == 1)
	{
		if (posY == 0)			// D
			std::get<4>(texts_[textIndex].second) = Position::D;
		else if (posY == 1)		// C
			std::get<4>(texts_[textIndex].second) = Position::C;
	}
	else
		std::get<4>(texts_[textIndex].second) = Position::E;
	
	FTPoint positionTexte;
	float decalage = obtenirDecalageY(textIndex);
	switch (std::get<4>(texts_[textIndex].second))
	{
		case Position::A:
			positionTexte = FTPoint(0 + MARGE_X,
									0 + decalage);
			break;
		case Position::B:
			positionTexte = FTPoint(posMax_.x - abs(boiteTextUpper.X() - boiteTextLower.X()) - MARGE_X,
									0 + decalage);
			break;
		case Position::C:
			positionTexte = FTPoint(posMax_.x - abs(boiteTextUpper.X() - boiteTextLower.X()) - MARGE_X,
									posMax_.y - abs(boiteTextUpper.Y() - boiteTextLower.Y()) - decalage);
			break;
		case Position::D:
			positionTexte = FTPoint(0 + MARGE_X,
									posMax_.y - abs(boiteTextUpper.Y() - boiteTextLower.Y()) - decalage);
			break;
		case Position::E:
			positionTexte = FTPoint(posX, posY);
			break;
	}
	std::get<0>(texts_[textIndex].second) = positionTexte;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::refresh(int x, int y)
///
/// @remark Repositionne les texte pour une continuitee
///
/// @param[in] x : position x
/// @param[in] y : position y
///
/// @return Rien.
///
////////////////////////////////////////////////////////////////////////
void ControleurTexte::refresh(int x, int y)
{
	posMax_ = glm::ivec2(x, y);
	for (unsigned int i = 0; i < texts_.size(); i++)
	{
		switch (std::get<4>(texts_[i].second))
		{
			case Position::A:
				repositionner(texts_[i].first, 0, 0);
				break;
			case Position::B:
				repositionner(texts_[i].first, 0, 1);
				break;
			case Position::C:
				repositionner(texts_[i].first, 1, 1);
				break;
			case Position::D:
				repositionner(texts_[i].first, 1, 0);
				break;
			default:
				break;
		}
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::obtenirDecalageY(unsigned int objectIndex)
///
/// @remark Obtiens le decalage en Y du string
///
/// @param[in] objectIndex : index du string
///
/// @return le decalage en y de l'objet.
///
////////////////////////////////////////////////////////////////////////
float ControleurTexte::obtenirDecalageY(unsigned int objectIndex)
{
	// Foutre de quoi ici, je sais pas encore quoi	TODO
	float decalage = MARGE_Y;
	Position p = std::get<4>(texts_[objectIndex].second);
	if (p == Position::E)
		return 0;

	for (unsigned int i = 0; i < objectIndex; i++)
	{
		if (std::get<4>(texts_[i].second) != p)
			continue;
		unsigned int fontIndex = lookUpFont(std::get<3>(texts_[i].second));
		int textSize = std::get<2>(texts_[i].second);
		fontTable_[fontIndex].second->FaceSize(textSize);
		FTBBox boiteText = fontTable_[fontIndex].second->BBox((char*)texts_[i].first.c_str());
		FTPoint boiteTextLower = boiteText.Lower();
		FTPoint boiteTextUpper = boiteText.Upper();
		decalage += abs(boiteTextUpper.Yf() - boiteTextLower.Yf()) + MARGE_Y;
	}
 	return abs(decalage);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::resize(std::string text, unsigned int size)
///
/// @remark Modifie la taille du string
///
/// @param[in] text : le string
/// @param[in] size : taille du texte
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurTexte::resize(std::string text, unsigned int size)
{
	unsigned int textIndex = lookUpText(text);
	std::get<2>(texts_[textIndex].second) = size;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::lookUpFont(std::string fileName)
///
/// @remark cherche l'indexe d'une font
///
/// @param[in] fileName : le string du font
///
/// @return la position dans le vecteur du font.
///
////////////////////////////////////////////////////////////////////////
unsigned int ControleurTexte::lookUpFont(std::string fileName)
{
	for (unsigned int i = 0; i < fontTable_.size(); i++)
		if (fontTable_[i].first == fileName)
			return i;
	return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurTexte::lookUpText(std::string textString)
///
/// @remark cherche l'indexe d'un string
///
/// @param[in] textString : le string de text
///
/// @return la position dans le vecteur du text.
///
////////////////////////////////////////////////////////////////////////
unsigned int ControleurTexte::lookUpText(std::string textString)
{
	for (unsigned int i = 0; i < texts_.size(); i++)
		if (std::string(texts_[i].first) == textString)
			return i;
	texts_.push_back(std::make_pair(textString, defaultObject_));
	return (int)texts_.size() - 1;
}