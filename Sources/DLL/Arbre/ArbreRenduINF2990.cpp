///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
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
#include "Usines/UsineNoeudTable.h"

#include "EtatOpenGL.h"


/// La chaîne représentant les types
const std::string ArbreRenduINF2990::NOM_ARAIGNEE{ "araignee" };
const std::string ArbreRenduINF2990::NOM_BUTOIR{ "butoir" };
const std::string ArbreRenduINF2990::NOM_BUTOIRCIRCULAIRE{ "butoircirculaire" };
const std::string ArbreRenduINF2990::NOM_CIBLE{ "cible" };
const std::string ArbreRenduINF2990::NOM_CONECUBE{ "conecube" };
const std::string ArbreRenduINF2990::NOM_BILLE{ "bille" };
const std::string ArbreRenduINF2990::NOM_GENERATEURBILLE{ "generateurbille" };
const std::string ArbreRenduINF2990::NOM_MUR{ "mur" };
const std::string ArbreRenduINF2990::NOM_PALETTE{ "palette" };
const std::string ArbreRenduINF2990::NOM_PORTAIL{ "portail" };
const std::string ArbreRenduINF2990::NOM_RESSORT{ "ressort" };
const std::string ArbreRenduINF2990::NOM_TROU{ "trou" };
const std::string ArbreRenduINF2990::NOM_VIDE{ "vide" };
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
	ajouterUsine(NOM_ARAIGNEE, new UsineNoeudAraignee{ NOM_ARAIGNEE });
	ajouterUsine(NOM_BUTOIR, new UsineNoeudButoir{ NOM_BUTOIR });
	ajouterUsine(NOM_BUTOIRCIRCULAIRE, new UsineNoeudButoirCirculaire{ NOM_BUTOIRCIRCULAIRE });
	ajouterUsine(NOM_CIBLE, new UsineNoeudCible{ NOM_CIBLE });
	ajouterUsine(NOM_CONECUBE, new UsineNoeudConeCube{ NOM_CONECUBE });
	ajouterUsine(NOM_BILLE, new UsineNoeudBille{ NOM_BILLE });
	ajouterUsine(NOM_GENERATEURBILLE, new UsineNoeudGenerateurBille{ NOM_GENERATEURBILLE });
	ajouterUsine(NOM_MUR, new UsineNoeudMur{ NOM_MUR });
	ajouterUsine(NOM_PALETTE, new UsineNoeudPalette{ NOM_PALETTE });
	ajouterUsine(NOM_PORTAIL, new UsineNoeudPortail{ NOM_PORTAIL });
	ajouterUsine(NOM_RESSORT, new UsineNoeudRessort{ NOM_RESSORT });
	ajouterUsine(NOM_TROU, new UsineNoeudTrou{ NOM_TROU });
	ajouterUsine(NOM_VIDE, new UsineNoeudTrou{ NOM_VIDE });
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

	// On ajoute un noeud bidon seulement pour que quelque chose s'affiche.
	NoeudAbstrait* noeud{ creerNoeud(NOM_TABLE) };
	
	NoeudAbstrait* noeudGenerateur{ creerNoeud(NOM_GENERATEURBILLE) };
	NoeudAbstrait* noeudRessort{ creerNoeud(NOM_RESSORT) };
	NoeudAbstrait* noeudTrou{ creerNoeud(NOM_TROU) };

	noeudGenerateur->assignerPositionRelative({ 247.40, -140.88, 0.0 });
	noeudRessort->assignerPositionRelative({ 247.00, -171.28, 0.0 });
	noeudTrou->assignerPositionRelative({ 184.60, -181.68, 0.0 });

	noeudGenerateur->assignerEstEnregistrable(false);
	noeudRessort->assignerEstEnregistrable(false);
	noeudTrou->assignerEstEnregistrable(false);

	noeud->ajouter(noeudGenerateur);
	noeud->ajouter(noeudRessort);
	noeud->ajouter(noeudTrou);

	ajouter(noeud);

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
NoeudAbstrait* ArbreRenduINF2990::getEnfant(int position)
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
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool ArbreRenduINF2990::accepterVisiteur(VisiteurAbstrait* vis)
{
	vis->traiter(this);
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool ArbreRenduINF2990::initialiserXML(VisiteurAbstrait* vis)
///
/// 
///
/// @return Retourne toujours true
///
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

	// TO DO: Lire les propriétés de la zone de jeu

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

	}

	return lecture;
}




///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////