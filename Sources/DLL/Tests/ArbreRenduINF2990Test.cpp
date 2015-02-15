////////////////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990Test.cpp
/// @author Samuel Millette
/// @date 2015-02-12
/// @version 1.0
///
/// @ingroup Test
////////////////////////////////////////////////////////////////////////////////////

#include "ArbreRenduINF2990Test.h"
#include "../Visiteurs/VisiteurAbstrait.h"
#include "../Visiteurs/VisiteurRotationPoint.h"
#include "../Visiteurs/VisiteurDeselectionnerTout.h"
#include "../Visiteurs/VisiteurSelectionMultiple.h"
#include "../Visiteurs/VisiteurDuplication.h"
#include "../Visiteurs/VisiteurSelectionInverse.h"
#include "../Visiteurs/VisiteurListeEnglobante.h"
#include "../Visiteurs/VisiteurCentreDeMasse.h"
#include "NoeudAbstrait.h"
#include "NoeudComposite.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(ArbreRenduINF2990Test);

using conteneur_boite_englobante = std::pair<std::vector<glm::dvec3>, NoeudAbstrait*>;

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::setUp()
///
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::setUp()
{
	// Nous pourrions initialiser l'objet, mais puisqu'il s'agit d'un singleton,
	// aucune initialisation n'est requise.

	arbre = std::make_unique<ArbreRenduINF2990>();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::tearDown()
///
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::tearDown()
{
	// Nous pourrions libérer l'objet, mais puisqu'il s'agit d'un singleton,
	// aucune libération n'est requise.
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testArbreDefaut()
///
/// Cas de test: Test de chargement d'un arbre par défaut à l'ouverture
///	de l'éditeur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testArbreDefaut()
{
	// On initialise l'arbre avec le fichier XML par défaut
	arbre->initialiser();

	// On vérifie que les éléments par défaut sont dans l'arbre.
	CPPUNIT_ASSERT(arbre->estDefaut() == true);
	
	// L'arbre devrait avoir des enfants
	CPPUNIT_ASSERT(arbre->obtenirNombreEnfants() > 0);

	// On vérifie que la table contient une table de manière alternative
	bool trouve = false;

	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		if (arbre->getEnfant(i)->obtenirType() == ArbreRenduINF2990::NOM_TABLE)
			trouve = true;

	}
	CPPUNIT_ASSERT(trouve == true);

	// Les propriétés de jeu ne sont pas négatives
	for (int i = 0; i < 5; i++)
		CPPUNIT_ASSERT(arbre->obtenirProprietes()[i] > 0);

	// On vide l'arbre
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testXmlInexistant()
///
/// Cas de test: Ouverture d'un fichier XML inexistant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testXmlInexistant()
{
	// On ouvre un fichier inexistant
	bool test = arbre->initialiserXML("zones/?.xml");
	CPPUNIT_ASSERT(!test);

	// On ouvre un fichier qui existe
	bool test2 = arbre->initialiserXML("zones/default.xml");
	CPPUNIT_ASSERT(test2);

	// On vide l'arbre
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testPortails()
///
/// Cas de test: Test de jumelage des portails.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testPortails()
{
	// On initialise une zone de jeu avec des portails
	bool test = arbre->initialiserXML("zones/test.xml");
	CPPUNIT_ASSERT(test);

	// On cherche un portail.
	NoeudAbstrait* portail1 = arbre->chercher(ArbreRenduINF2990::NOM_PORTAIL);

	// On obtient le noeud lié au portail obtenu.
	NoeudAbstrait* portail2 = portail1->getTwin();

	// L'objet lié est un autre portail.
	CPPUNIT_ASSERT(portail2->obtenirType() == ArbreRenduINF2990::NOM_PORTAIL);

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::creerNoeudParUsine()
///
/// Cas de test: Création de noeuds avec les usines.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::creerNoeudParUsine()
{
	// On crée un noeud de type non reconnu par les usines.
	NoeudAbstrait* noeudVide = arbre->creerNoeud("NOM_CIBLE");

	// On crée un nom de type reconnu par une usine.
	NoeudAbstrait* noeudCible = arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE);
	
	// Le noeud non reconnu est un nulptr
	CPPUNIT_ASSERT(noeudVide == NULL);

	// Le noeud reconnu par l'usine est du bon type.
	CPPUNIT_ASSERT(noeudCible->obtenirType() == ArbreRenduINF2990::NOM_CIBLE);

	// Nettoyage.
	delete noeudVide;
	delete noeudCible;

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::boiteEnglobante()
///
/// Cas de test: Test des limites de la boîte englobante d'un noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::boiteEnglobante()
{
	// On crée une cible.
	NoeudAbstrait* noeudCible = arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE);

	// On obtient sa position.
	glm::dvec3 vecteur{ noeudCible->obtenirPositionRelative() };

	// On vérifie que le noeud est en position relative (0,0,0).
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2]));

	// On crée un point à (0,0,0)
	glm::dvec3 point;
	point[0] = 0;
	point[1] = 0;
	point[2] = 0;

	// On vérifie qu'il est dans la boîte englobante de la cible.
	CPPUNIT_ASSERT(noeudCible->pointEstDansBoite(point));

	// On déplace le point en X.
	point[0] = 100;
	point[1] = 0;
	point[2] = 0;

	// On vérifie qu'il n'est plus dans la boîte englobante de la cible.
	CPPUNIT_ASSERT(!noeudCible->pointEstDansBoite(point));

	// Nettoyage.
	delete noeudCible;

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::selectionTable()
///
/// Cas de test: On s'assure qu'un table n'est pas sélectionnable.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::selectionTable()
{
	// On initialise l'arbre avec le fichier XML par défaut
	arbre->initialiser();

	// On vérifie que les éléments par défaut sont dans l'arbre.
	CPPUNIT_ASSERT(arbre->estDefaut() == true);

	// On cherche une table.
	NoeudAbstrait* noeudTable = arbre->chercher(ArbreRenduINF2990::NOM_TABLE);

	CPPUNIT_ASSERT(!noeudTable->estSelectionnable());

	// On cherche un ressort.
	NoeudAbstrait* noeudRessort = arbre->chercher(ArbreRenduINF2990::NOM_RESSORT);

	CPPUNIT_ASSERT(noeudRessort->estSelectionnable());

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testDeselection()
///
/// Cas de test: Test du visiteur de désélection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testDeselection()
{
	// On initialise l'arbre avec le fichier XML par défaut
	arbre->initialiser();

	// On cherche un ressort.
	NoeudAbstrait* noeudRessort = arbre->chercher(ArbreRenduINF2990::NOM_RESSORT);

	// Sélectionner l'objet
	noeudRessort->assignerSelection(true);
	VisiteurDeselectionnerTout* visiteurDeselection = new VisiteurDeselectionnerTout();

	// Test du visiteur de déselection
	arbre->accepterVisiteur(visiteurDeselection);


	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
		CPPUNIT_ASSERT(arbre->getEnfant(i)->estSelectionne() == false);


	// Nettoyage.
	delete visiteurDeselection;

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testRotation()
///
/// Cas de test: Test du visiteur de rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testRotation()
{
	// On initialise l'arbre avec le fichier XML par défaut
	arbre->initialiser();

	// On cherche un ressort.
	NoeudAbstrait* noeudRessort = arbre->chercher(ArbreRenduINF2990::NOM_RESSORT);

	// Sélectionner l'objet
	noeudRessort->assignerSelection(true);

	// Rotation originale.
	glm::dvec3 rotOriginale = noeudRessort->obtenirRotation();

	// Vecteur de rotation
	glm::dvec3 vecteur = { 0, 0, 30 };

	// Trouver le centre de masse de la selection
	VisiteurCentreDeMasse visCM;
	arbre->accepterVisiteur(&visCM);
	glm::dvec3 centreRotation = visCM.obtenirCentreDeMasse();

	// Appeler le visiteur de rotation
	VisiteurRotationPoint* visiteurRot = new VisiteurRotationPoint(vecteur, centreRotation);

	// Test du visiteur.
	CPPUNIT_ASSERT(arbre->accepterVisiteur(visiteurRot));

	// Nouvelle valeur de rotation.
	glm::dvec3 nouvRotation = noeudRessort->obtenirRotation();

	// Il y a eu une rotation.
	CPPUNIT_ASSERT(rotOriginale != nouvRotation);

	// Nettoyage.
	delete visiteurRot;

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testSelectionMultiple()
///
/// Cas de test: Test du visiteur de sélection multiple.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testSelectionMultiple()
{
	// On initialise l'arbre avec le fichier XML par défaut.
	arbre->initialiser();

	CPPUNIT_ASSERT(arbre->getEnfant(0)->obtenirType() == ArbreRenduINF2990::NOM_TABLE);

	// On accède à la table et on ajoute une cible.
	bool ajout1 = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };
	bool ajout2 = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };

	// Les deux cibles ont été ajoutées.
	CPPUNIT_ASSERT(ajout1 == true);
	CPPUNIT_ASSERT(ajout2 == true);

	// Une cible est bien crée en position {0,0,0}.
	NoeudAbstrait* cible = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_CIBLE);
	glm::dvec3 position = cible->obtenirPositionRelative();
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(position[0]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(position[1]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(position[2]));

	// On crée un visiteur dans une boite de 10x10 autour du point central avec les deux cibles.
	VisiteurSelectionMultiple* visSelecMult = new VisiteurSelectionMultiple({ -10.0, -10.0, 0.0 }, { 10.0, 10.0, 0.0 });

	// On visite les éléments.
	arbre->getEnfant(0)->accepterVisiteur(visSelecMult);

	// Deux objets sont sélectionnés
	CPPUNIT_ASSERT(visSelecMult->obtenirNbObjetsSelectionne() == 2);

	// Nettoyage.
	delete visSelecMult;

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testSelectionInverse()
///
/// Cas de test: Test du visiteur de sélection inverse.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testSelectionInverse()
{
	// On initialise l'arbre avec le fichier XML par défaut.
	arbre->initialiser();

	// On accède à la table et on ajoute une cible.
	bool ajout = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };

	// La cible a été ajoutée.	
	CPPUNIT_ASSERT(ajout == true);

	// On sélectionne la cible.
	NoeudAbstrait* noeudCible = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_CIBLE);
	noeudCible->assignerSelection(true);

	VisiteurSelectionInverse* visSelInv = new VisiteurSelectionInverse({0.0,0.0,0.0}, noeudCible->getNumero());

	// On desélectionne la cible avec la sélection inverse.
	noeudCible->accepterVisiteur(visSelInv);

	CPPUNIT_ASSERT(noeudCible->estSelectionne() == false);

	// Nettoyage.
	delete visSelInv;

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::______()
///
/// Cas de test: Test du visiteur de duplication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testDuplication()
{
	// On initialise l'arbre avec le fichier XML par défaut.
	arbre->initialiser();

	// On accède à la table et on ajoute une cible.
	bool ajout = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };

	// La cible a été ajoutée.	
	CPPUNIT_ASSERT(ajout == true);

	// On sélectionne la cible.
	NoeudAbstrait* noeudCible = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_CIBLE);
	noeudCible->assignerSelection(true);

	// Nombre d'enfants avant la duplication.
	int enfantsAvant = arbre->getEnfant(0)->obtenirNombreEnfants();

	// Visiteur Duplication fait sa job (on l'espère).
	VisiteurDuplication* visiteurDup = new VisiteurDuplication();
	arbre->accepterVisiteur(visiteurDup);

	// Nombre d'enfants après la duplication
	int enfantsApres = arbre->getEnfant(0)->obtenirNombreEnfants();

	// std::cout << enfantsApres << " > " << enfantsAvant << "!!!";

	CPPUNIT_ASSERT(enfantsApres > enfantsAvant);
	
	// Nettoyage.
	delete visiteurDup;

	// On vide l'arbre.
	arbre->vider();

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testBoiteEnglobante()
///
/// Cas de test: Test du visiteur qui crée une liste des boîtes
/// englobantes.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testBoiteEnglobante()
{
	// On initialise l'arbre avec le fichier XML par défaut.
	arbre->initialiser();

	// On accède à la table et on ajoute une cible.
	bool ajout = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };

	// La cible a été ajoutée.	
	CPPUNIT_ASSERT(ajout == true);

	// On sélectionne la cible.
	NoeudAbstrait* noeudCible = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_CIBLE);
	noeudCible->assignerSelection(true);

	// Visiteur Liste Englobante.
	VisiteurListeEnglobante* visBoiteEngl = new VisiteurListeEnglobante();
	noeudCible->accepterVisiteur(visBoiteEngl);

	// On obtient l'attribut du visiteur.
	std::vector<conteneur_boite_englobante> liste = visBoiteEngl->obtenirListeEnglobante();

	// Le bon noeud est inséré.
	CPPUNIT_ASSERT(liste[0].second == noeudCible);

	glm::dvec3 coinsEnglobant[4];
	noeudCible->obtenirVecteursBoite(coinsEnglobant[0], coinsEnglobant[1], coinsEnglobant[2], coinsEnglobant[3]);

	// Les coins de la boite matchent.
	CPPUNIT_ASSERT(liste[0].first[0] == coinsEnglobant[0]);
	CPPUNIT_ASSERT(liste[0].first[1] == coinsEnglobant[1]);
	CPPUNIT_ASSERT(liste[0].first[2] == coinsEnglobant[2]);
	CPPUNIT_ASSERT(liste[0].first[3] == coinsEnglobant[3]);

	// Nettoyage.
	delete visBoiteEngl;

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testPalettes()
///
/// Cas de test: Couleur des palettes joueur 1 et 2.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testPalettes()
{
	// On initialise l'arbre avec le fichier XML par défaut.
	arbre->initialiser();

	// On accède à la table et on ajoute une cible.
	bool ajout = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_PALETTED)) };

	// La cible a été ajoutée.	
	CPPUNIT_ASSERT(ajout == true);

	// On sélectionne la cible.
	NoeudAbstrait* noeudCible = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_PALETTED);
	noeudCible->assignerSelection(true);
	CPPUNIT_ASSERT(noeudCible->estSelectionne());
	arbre->vider();
	arbre->initialiser();
	arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_PALETTED));
	arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_PALETTEG));
	CPPUNIT_ASSERT(arbre->getEnfant(0)->obtenirNombreEnfants() == 2+3);
	// On trouve les palettes de J1 et J2 (il y a une palette différente par joueur)
	NoeudAbstrait* paletteDJ1 = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_PALETTED);
	NoeudAbstrait* paletteGJ2 = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_PALETTEG);
	arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_PALETTED)->setColorShift(false);
	arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_PALETTEG)->setColorShift(true);

	CPPUNIT_ASSERT(paletteDJ1->getColorShift() != paletteGJ2->getColorShift());
}	