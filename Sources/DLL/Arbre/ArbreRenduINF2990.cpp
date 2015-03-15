///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @ingroup Arbre
///////////////////////////////////////////////////////////////////////////
#include "ArbreRenduINF2990.h"

#include "Usines/UsineNoeudButoirD.h"
#include "Usines/UsineNoeudButoirG.h"
#include "Usines/UsineNoeudButoirCirculaire.h"
#include "Usines/UsineNoeudCible.h"
#include "Usines/UsineNoeudBille.h"
#include "Usines/UsineNoeudGenerateurBille.h"
#include "Usines/UsineNoeudMur.h"
#include "Usines/UsineNoeudPaletteD.h"
#include "Usines/UsineNoeudPaletteG.h"
#include "Usines/UsineNoeudPortail.h"
#include "Usines/UsineNoeudPortailTorus.h"
#include "Usines/UsineNoeudRessort.h"
#include "Usines/UsineNoeudTrou.h"
#include "Usines/UsineNoeudVide.h"
#include "Usines/UsineNoeudCouvercle.h"
#include "Usines/UsineNoeudTable.h"

#include "EtatOpenGL.h"
#include <iomanip>


const std::string ArbreRenduINF2990::NOM_BUTOIRD{ "butoird" };
const std::string ArbreRenduINF2990::NOM_BUTOIRG{ "butoirg" };
const std::string ArbreRenduINF2990::NOM_BUTOIRCIRCULAIRE{ "butoircirculaire" };
const std::string ArbreRenduINF2990::NOM_CIBLE{ "cible" };
const std::string ArbreRenduINF2990::NOM_BILLE{ "bille" };
const std::string ArbreRenduINF2990::NOM_GENERATEURBILLE{ "generateurbille" };
const std::string ArbreRenduINF2990::NOM_MUR{ "mur" };
const std::string ArbreRenduINF2990::NOM_PALETTED{ "paletted" };
const std::string ArbreRenduINF2990::NOM_PALETTEG{ "paletteg" };
const std::string ArbreRenduINF2990::NOM_PORTAIL{ "portail" };
const std::string ArbreRenduINF2990::NOM_PORTAILTORUS{ "portailtorus" };
const std::string ArbreRenduINF2990::NOM_RESSORT{ "ressort" };
const std::string ArbreRenduINF2990::NOM_TROU{ "trou" };
const std::string ArbreRenduINF2990::NOM_VIDE{ "vide" };
const std::string ArbreRenduINF2990::NOM_COUVERCLE{ "couvercle" };
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur cree toutes les usines qui seront utilisees par le
/// projet de INF2990et les enregistre aupres de la classe de base.
/// Il cree egalement la structure de base de l'arbre de rendu, c'est-a-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990(bool afficher)
{
	// Construction des usines
	int i = 16;
	int j = 0;
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Boutoire Droit" << std::endl;
	ajouterUsine(NOM_BUTOIRD, new UsineNoeudButoirD{ NOM_BUTOIRD });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Boutoire Gauche" << std::endl;
	ajouterUsine(NOM_BUTOIRG, new UsineNoeudButoirG{ NOM_BUTOIRG });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Boutoire Circulaire" << std::endl;
	ajouterUsine(NOM_BUTOIRCIRCULAIRE, new UsineNoeudButoirCirculaire{ NOM_BUTOIRCIRCULAIRE });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Cible" << std::endl;
	ajouterUsine(NOM_CIBLE, new UsineNoeudCible{ NOM_CIBLE });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Bille" << std::endl;
	ajouterUsine(NOM_BILLE, new UsineNoeudBille{ NOM_BILLE });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Generateur Bille" << std::endl;
	ajouterUsine(NOM_GENERATEURBILLE, new UsineNoeudGenerateurBille{ NOM_GENERATEURBILLE });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Mur" << std::endl;
	ajouterUsine(NOM_MUR, new UsineNoeudMur{ NOM_MUR });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Palette Droite" << std::endl;
	ajouterUsine(NOM_PALETTED, new UsineNoeudPaletteD{ NOM_PALETTED });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Palette Gauche" << std::endl;
	ajouterUsine(NOM_PALETTEG, new UsineNoeudPaletteG{ NOM_PALETTEG });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Portail" << std::endl;
	ajouterUsine(NOM_PORTAIL, new UsineNoeudPortail{ NOM_PORTAIL });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine PortailTorus" << std::endl;
	ajouterUsine(NOM_PORTAILTORUS, new UsineNoeudPortailTorus{ NOM_PORTAILTORUS });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Ressort" << std::endl;
	ajouterUsine(NOM_RESSORT, new UsineNoeudRessort{ NOM_RESSORT });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Trou" << std::endl;
	ajouterUsine(NOM_TROU, new UsineNoeudTrou{ NOM_TROU });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Tampon" << std::endl;
	ajouterUsine(NOM_VIDE, new UsineNoeudVide{ NOM_VIDE });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Couvercle" << std::endl;
	ajouterUsine(NOM_COUVERCLE, new UsineNoeudCouvercle{ NOM_COUVERCLE });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... ajout de l'usine Table" << std::endl;
	ajouterUsine(NOM_TABLE, new UsineNoeudTable{ NOM_TABLE });
	if (afficher) std::cout << std::fixed << std::setw(2) << std::setprecision(2) << j++ * 100.0 / i << "%... toute les usines sont genere" << std::endl;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
///
/// Ce destructeur ne fait rien pour le moment.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
	delete proprietes_;
	listeNoeuds_.clear();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction cree la structure de base de l'arbre de rendu, c'est-a-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
	// On vide l'arbre
	vider();

	// Charger la zone de jeu par defaut
	initialiserXML("zones/default.xml");
	SingletonGlobal::obtenirInstance()->resetConfigurationCollision(proprietes_[0], proprietes_[1], proprietes_[2], proprietes_[3], proprietes_[4]);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* ArbreRenduINF2990::getEnfant(int position)
///
/// Cette fonction retourne un NoeudAbstrait* qui correspond
///	a l'enfant de la position passe en parametre.
///
/// @return NoeudAbstrait* L'enfant en question.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* ArbreRenduINF2990::getEnfant(int position) const
{
	if (position > enfants_.size() || position < 0)
		return nullptr;
	else
		return enfants_[position];
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool ArbreRenduINF2990::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur
///
/// @return operationReussie (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool ArbreRenduINF2990::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool operationReussie = false;

	if (vis->traiter(this))
		operationReussie = true;

	return operationReussie;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool ArbreRenduINF2990::initialiserXML(std::string nomFichier)
///
/// @param[in] nomFichier : Le nom du fichier XML a ouvrir
///
/// Cette fonction cree la structure de base de l'arbre de rendu, c'est-a-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.) en lisant un fichier XML
///
/// @return TRUE : fichier trouve. Autrement, FALSE
////////////////////////////////////////////////////////////////////////
bool ArbreRenduINF2990::initialiserXML(std::string nomFichier)
{
	bool fichierTrouve = false;
	tinyxml2::XMLDocument document;

	// Si le fichier n'existe pas, envoyer une erreur
	if (nomFichier == "zones/.xml")
		;
	else if (!utilitaire::fichierExiste(nomFichier))
		std::cout << "Le fichier n'existe pas. " << std::endl;
		
	else
	{
		document.LoadFile(nomFichier.c_str());
		lireXML(document);
		fichierTrouve = true;
	}
	SingletonGlobal::obtenirInstance()->resetConfigurationCollision(proprietes_[0], proprietes_[1], proprietes_[2], proprietes_[3], proprietes_[4]);

	return fichierTrouve;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool ArbreRenduINF2990::lireXML(tinyxml2::XMLDocument& doc)
///
/// @param[in] doc : un document XML
///
/// Cette fonction lit un fichier XML et creer les objets de l'arbre.
///	Il lit egalement les proprietes de la zone de jeu.
///
/// @return TRUE : lecture correcte. Autrement, FALSE
///
////////////////////////////////////////////////////////////////////////
bool ArbreRenduINF2990::lireXML(tinyxml2::XMLDocument& doc)
{
	bool lecture = false;

	const char* positionX = "posX";
	const char* positionY = "posY";
	const char* positionZ = "posZ";
	const char* scaleX = "scaleX";
	const char* scaleY = "scaleY";
	const char* scaleZ = "scaleZ";
	const char* angleX = "angleX";
	const char* angleY = "angleY";
	const char* angleZ = "angleZ";

	// Charger les proprietes de la zone de jeu
	tinyxml2::XMLElement* elementPropriete = doc.FirstChildElement("Proprietes");
	tinyxml2::XMLElement* element = elementPropriete->FirstChildElement("PointsButoir");

	for (int i = 0; i < 6; i++)
	{
		proprietes_[i] = element->FirstAttribute()->IntValue();
		element = element->NextSiblingElement();
	}

	// Obtenir l'element "arbreRenduINF2990"
	tinyxml2::XMLElement* elementArbre = doc.FirstChildElement("arbreRenduINF2990");

	if (elementArbre != nullptr) 
	{
		// Vider l'ancien arbre de rendu
		vider();

		// Tenter d'obtenir l'element table, puis l'attribut nbEnfants
		const tinyxml2::XMLElement* elementTable{ elementArbre->FirstChildElement("table") };
		
		if (elementTable != nullptr)
		{
			// Creer la table et l'ajouter a l'arbre de rendu
			NoeudAbstrait* table{ creerNoeud(elementTable->Name()) };
			this->ajouter(table);

			// Recuperer le nombre d'enfants
			int nombreEnfants = elementTable->FirstAttribute()->IntValue();

			// Premier enfant de la table
			const tinyxml2::XMLElement* enfant{ elementTable->FirstChildElement() };

			// Creer les enfants et les ajouter a la table
			for (int i = 0; i < nombreEnfants; i++)
			{
				// Construire le noeud concret
				NoeudAbstrait* noeudConcret{ creerNoeud(enfant->Name()) };

				// Assigner les proprietes de l'enfant
				noeudConcret->assignerPositionRelative({ enfant->FindAttribute(positionX)->DoubleValue(),
					enfant->FindAttribute(positionY)->DoubleValue(),
					enfant->FindAttribute(positionZ)->DoubleValue() });

				noeudConcret->assignerEchelle({ enfant->FindAttribute(scaleX)->DoubleValue(),
					enfant->FindAttribute(scaleY)->DoubleValue(),
					enfant->FindAttribute(scaleZ)->DoubleValue() });

				noeudConcret->assignerRotation({ enfant->FindAttribute(angleX)->DoubleValue(),
					enfant->FindAttribute(angleY)->DoubleValue(),
					enfant->FindAttribute(angleZ)->DoubleValue() });

				// Pour la couleur des palettes
				if (noeudConcret->obtenirType() == "paletted" || noeudConcret->obtenirType() == "paletteg")
					noeudConcret->setColorShift(enfant->FindAttribute("color")->BoolValue());

				// Ajouter l'enfant a la table
				table->ajouter(noeudConcret);

				// Le cas ou le noeud cree est un portail
				if (noeudConcret->obtenirType() == "portail")
				{
					// Nombre actuel d'enfants de la table
					unsigned int enfantsTable = getEnfant(0)->obtenirNombreEnfants();

					// Interroger l'enfant au dessus de lui
					if (table->chercher(enfantsTable - 2)->obtenirType() == "portail"
						&& table->chercher(enfantsTable - 2)->getTwin() == nullptr)
					{
						// Si c'est un portail et qu'il n'est pas relie, les relier tous les deux
						noeudConcret->setTwin(table->chercher(enfantsTable - 2 ));
						table->chercher(enfantsTable - 2)->setTwin(noeudConcret);
					}
				}

				// Traiter le frere de droite de l'enfant
				enfant = enfant->NextSiblingElement();
			}

			lecture = true;
		}
		
		// Tenter d'obtenir l'element couvercle
		const tinyxml2::XMLElement* elementCouvercle{ elementArbre->LastChildElement("couvercle")};

		if (elementCouvercle != nullptr)
		{
			NoeudAbstrait* couvercle{ creerNoeud(elementCouvercle->Name()) };
			this->ajouter(couvercle);
		}

	}

	assignerDefaut();

	return lecture;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool ArbreRenduINF2990::estDefaut()
///
/// Cette fonction dit si les elements de l'arbre constituent la 
///	zone de jeu par defaut
///
/// @return TRUE : la zone est une zone par defaut. Autrement, FALSE
///
////////////////////////////////////////////////////////////////////////
bool ArbreRenduINF2990::estDefaut() const
{
	if (   posRessort == chercher("ressort")->obtenirPositionRelative()
		&& angleRessort == chercher("ressort")->obtenirRotation()
		&& scaleRessort == chercher("ressort")->obtenirAgrandissement()
		&& posTrou == chercher("trou")->obtenirPositionRelative()
		&& angleTrou == chercher("trou")->obtenirRotation()
		&& scaleTrou == chercher("trou")->obtenirAgrandissement()
		&& posGenerateur == chercher("generateurbille")->obtenirPositionRelative()
		&& angleGenerateur == chercher("generateurbille")->obtenirRotation()
		&& scaleGenerateur == chercher("generateurbille")->obtenirAgrandissement()
		)
		return true;

	else
		return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool ArbreRenduINF2990::assignerDefaut()
///
/// Cette fonction definit ce qu'est une zone de jeu par defaut
///
/// @return VOID
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::assignerDefaut()
{
	posRessort = chercher("ressort")->obtenirPositionRelative();
	angleRessort = chercher("ressort")->obtenirRotation();
	scaleRessort = chercher("ressort")->obtenirAgrandissement();
	posTrou = chercher("trou")->obtenirPositionRelative();
	angleTrou = chercher("trou")->obtenirRotation();
	scaleTrou = chercher("trou")->obtenirAgrandissement();
	posGenerateur = chercher("generateurbille")->obtenirPositionRelative();
	angleGenerateur = chercher("generateurbille")->obtenirRotation();
	scaleGenerateur = chercher("generateurbille")->obtenirAgrandissement();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool ArbreRenduINF2990::takeScreenShot(std::string path)
///
/// @param[in] char* path : le chemin ou enregistrer
/// @param[in] int width : largeur de la fenetre
/// @param[in] int height : hauteur de la fenetre
/// @param[in] int maxSize : taille maximale (pixel) de l'image
/// @param[in] bool square : forme de l'image carre
///
/// Cette fonction recoit un path vers le disque dur
///	et renregistre l'ecran afficher
///
/// @return : Aucun.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::takeScreenShot(char* path, int width, int height, bool square, int maxSize)
{
	if (maxSize != 0 || square == true)
		width > height ? width = height : height = width;
	// Make the BYTE array, factor of 3 because it's RBG.
	// Facteur Debug ? sert a ne pas avoir de corruption de heap, dont ask.
	int FACTEUR_DEBUG = 2;
	BYTE* pixels = new BYTE[3 * FACTEUR_DEBUG * width * height];
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// On semble etre en BGR plus tot qu'en RGB
	glReadPixels(0, 0, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);

	// Convert to FreeImage format & save to file
	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height, ((((24 * width) + 31) / 32) * 4), 24,
		0x000000, 0x000000, 0x000000, false);
	// La couleur ici semble... useless (le 0x000000)

	// La on rescale a 100px*100px
	if (maxSize != 0)
		image = FreeImage_Rescale(image, maxSize, maxSize, FILTER_BOX);

	FreeImage_Save(FIF_JPEG, image, path, 0);

	// Free resources
	FreeImage_Unload(image);
	delete[] pixels;
}


std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirElementsTable()
{
	listeNoeuds_.clear();

	for (unsigned int i = 0; i < getEnfant(0)->obtenirNombreEnfants(); i++)
		listeNoeuds_.push_back(getEnfant(0)->getEnfant(i));

	return listeNoeuds_;
}