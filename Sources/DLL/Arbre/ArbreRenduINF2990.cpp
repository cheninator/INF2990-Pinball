///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @ingroup Arbre
///////////////////////////////////////////////////////////////////////////
#include "ArbreRenduINF2990.h"

#include "Usines/UsineNoeudAraignee.h"
#include "Usines/UsineNoeudButoir.h"
#include "Usines/UsineNoeudButoirCirculaire.h"
#include "Usines/UsineNoeudCible.h"
#include "Usines/UsineNoeudConeCube.h"
#include "Usines/UsineNoeudBille.h"
#include "Usines/UsineNoeudGenerateurBille.h"
#include "Usines/UsineNoeudMur.h"
#include "Usines/UsineNoeudPalette.h"
#include "Usines/UsineNoeudPortail.h"
#include "Usines/UsineNoeudRessort.h"
#include "Usines/UsineNoeudTrou.h"
#include "Usines/UsineNoeudVide.h"
#include "Usines/UsineNoeudCouvercle.h"
#include "Usines/UsineNoeudTable.h"

#include "EtatOpenGL.h"


const std::string ArbreRenduINF2990::NOM_BUTOIR{ "butoir" };
const std::string ArbreRenduINF2990::NOM_BUTOIRCIRCULAIRE{ "butoircirculaire" };
const std::string ArbreRenduINF2990::NOM_CIBLE{ "cible" };
const std::string ArbreRenduINF2990::NOM_BILLE{ "bille" };
const std::string ArbreRenduINF2990::NOM_GENERATEURBILLE{ "generateurbille" };
const std::string ArbreRenduINF2990::NOM_MUR{ "mur" };
const std::string ArbreRenduINF2990::NOM_PALETTE{ "palette" };
const std::string ArbreRenduINF2990::NOM_PORTAIL{ "portail" };
const std::string ArbreRenduINF2990::NOM_RESSORT{ "ressort" };
const std::string ArbreRenduINF2990::NOM_TROU{ "trou" };
const std::string ArbreRenduINF2990::NOM_VIDE{ "vide" };
const std::string ArbreRenduINF2990::NOM_COUVERCLE{ "couvercle" };
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur crée toutes les usines qui seront utilisées par le
/// projet de INF2990et les enregistre auprès de la classe de base.
/// Il crée également la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
	// Construction des usines
	ajouterUsine(NOM_BUTOIR, new UsineNoeudButoir{ NOM_BUTOIR });
	ajouterUsine(NOM_BUTOIRCIRCULAIRE, new UsineNoeudButoirCirculaire{ NOM_BUTOIRCIRCULAIRE });
	ajouterUsine(NOM_CIBLE, new UsineNoeudCible{ NOM_CIBLE });
	ajouterUsine(NOM_BILLE, new UsineNoeudBille{ NOM_BILLE });
	ajouterUsine(NOM_GENERATEURBILLE, new UsineNoeudGenerateurBille{ NOM_GENERATEURBILLE });
	ajouterUsine(NOM_MUR, new UsineNoeudMur{ NOM_MUR });
	ajouterUsine(NOM_PALETTE, new UsineNoeudPalette{ NOM_PALETTE });
	ajouterUsine(NOM_PORTAIL, new UsineNoeudPortail{ NOM_PORTAIL });
	ajouterUsine(NOM_RESSORT, new UsineNoeudRessort{ NOM_RESSORT });
	ajouterUsine(NOM_TROU, new UsineNoeudTrou{ NOM_TROU });
	ajouterUsine(NOM_VIDE, new UsineNoeudVide{ NOM_VIDE });
	ajouterUsine(NOM_COUVERCLE, new UsineNoeudCouvercle{ NOM_COUVERCLE });
	ajouterUsine(NOM_TABLE, new UsineNoeudTable{ NOM_TABLE });
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
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
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

	// Charger la zone de jeu par défaut
	initialiserXML("Zones_de_jeu/default.xml");
	/*NoeudAbstrait* noeud = creerNoeud("couvercle");
	ajouter(noeud);*/

}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* ArbreRenduINF2990::getEnfant(int position)
///
/// Cette fonction retourne un NoeudAbstrait* qui correspond
///	à l'enfant de la position passé en paramètre.
///
/// @return NoeudAbstrait*
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
/// Cette fonction appelle la méthode traiter du visiteur
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
/// @param[in] nomFichier : Le nom du fichier XML à ouvrir
///
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.) en lisant un fichier XML
///
/// @return TRUE : fichier trouvé. Autrement, FALSE
////////////////////////////////////////////////////////////////////////
bool ArbreRenduINF2990::initialiserXML(std::string nomFichier)
{
	bool fichierTrouve = false;
	tinyxml2::XMLDocument document;

	// Si le fichier n'existe pas, envoyer une erreur
	if (!utilitaire::fichierExiste(nomFichier))
		std::cout << "Fichier n'existe pas. ";
		
	else
	{
		document.LoadFile(nomFichier.c_str());
		lireXML(document);
		fichierTrouve = true;
	}

	return fichierTrouve;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool ArbreRenduINF2990::lireXML(tinyxml2::XMLDocument& doc)
///
/// @param[in] doc : un document XML
///
/// Cette fonction lit un fichier XML et créer les objets de l'arbre.
///	Il lit également les propriétés de la zone de jeu.
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


	// Charger les propriétés de la zone de jeu
	tinyxml2::XMLElement* elementPropriete = doc.FirstChildElement("Proprietes");
	tinyxml2::XMLElement* element = elementPropriete->FirstChildElement("PointsButoir");

	for (int i = 0; i < 6; i++)
	{
		proprietes_[i] = element->FirstAttribute()->IntValue();
		element = element->NextSiblingElement();
	}

	//////////////////////////////////////////////////
	// Lecture de l'arbre ainsi que ses enfants
	//////////////////////////////////////////////////

	// Obtenir l'élément "arbreRenduINF2990"
	tinyxml2::XMLElement* elementArbre = doc.FirstChildElement("arbreRenduINF2990");

	if (elementArbre != nullptr) 
	{
		// Tenter d'obtenir l'élément table, puis l'attribut nbEnfants
		const tinyxml2::XMLElement* elementTable{ elementArbre->FirstChildElement("table") };
		
		if (elementTable != nullptr)
		{
			// Créer la table et l'ajouter à l'arbre de rendu
			NoeudAbstrait* table{ creerNoeud(elementTable->Name()) };
			this->ajouter(table);

			// Récupérer le nombre d'enfants
			int nombreEnfants = elementTable->FirstAttribute()->IntValue();

			// Premier enfant de la table
			const tinyxml2::XMLElement* enfant{ elementTable->FirstChildElement() };

			// Créer les enfants et les ajouter à la table
			for (int i = 0; i < nombreEnfants; i++)
			{
				// Construire le noeud concret
				NoeudAbstrait* enfantTable{ creerNoeud(enfant->Name()) };

				// Assigner les propriétés de l'enfant
				enfantTable->assignerPositionRelative({ enfant->FindAttribute(positionX)->DoubleValue(),
					enfant->FindAttribute(positionY)->DoubleValue(),
					enfant->FindAttribute(positionZ)->DoubleValue() });

				enfantTable->assignerEchelle({ enfant->FindAttribute(scaleX)->DoubleValue(),
					enfant->FindAttribute(scaleY)->DoubleValue(),
					enfant->FindAttribute(scaleZ)->DoubleValue() });

				enfantTable->assignerRotation({ enfant->FindAttribute(angleX)->DoubleValue(),
					enfant->FindAttribute(angleY)->DoubleValue(),
					enfant->FindAttribute(angleZ)->DoubleValue() });

				// Ajouter l'enfant à la table
				table->ajouter(enfantTable);

				// Traiter le frère de droite de l'enfant
				enfant = enfant->NextSiblingElement();
			}

			lecture = true;
		}
		
		// Tenter d'obtenir l'élément table, puis l'attribut nbEnfants
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



bool ArbreRenduINF2990::estDefaut() const
{
	if (posRessort == chercher("ressort")->obtenirPositionRelative()
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