/*
////////////////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990Test.cpp
/// @author The Ballers
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
#include "../Visiteurs/VisiteurAgrandissement.h"
#include "../Visiteurs/VisiteurSelection.h"
#include "../Visiteurs/VisiteurPossibilite.h"
#include "../Visiteurs/VisiteurDeplacement.h"
#include "../Visiteurs/VisiteurSuppression.h"
#include "NoeudAbstrait.h"
#include "NoeudComposite.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(ArbreRenduINF2990Test);
using conteneur_boite_englobante = std::pair<std::vector<glm::dvec3>, NoeudAbstrait*>;

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::setUp()
///
/// Effectue l'initialisation prealable a l'execution de l'ensemble des
/// cas de tests de cette suite de tests (si necessaire).
/// 
/// Si certains objets doivent etre construits, il est conseille de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::setUp()
{
	// Nous pourrions initialiser l'objet, mais puisqu'il s'agit d'un singleton,
	// aucune initialisation n'est requise.

	arbre = std::make_unique<ArbreRenduINF2990>(false);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::tearDown()
///
/// Effectue les operations de finalisation necessaires suite a l'execution
/// de l'ensemble des cas de tests de cette suite de tests (si necessaire).
/// 
/// Si certains objets ont ete alloues a l'initialisation, ils doivent etre
/// desalloues, et il est conseille de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::tearDown()
{
	// Nous pourrions liberer l'objet, mais puisqu'il s'agit d'un singleton,
	// aucune liberation n'est requise.
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testArbreDefaut()
///
/// Cas de test: Test de chargement d'un arbre par defaut a l'ouverture
///	de l'editeur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testArbreDefaut()
{
	// On initialise l'arbre avec le fichier XML par defaut
	arbre->initialiser();

	// On verifie que les elements par defaut sont dans l'arbre.
	//CPPUNIT_ASSERT(arbre->estDefaut() == true);
	
	// L'arbre devrait avoir des enfants
	CPPUNIT_ASSERT(arbre->obtenirNombreEnfants() > 0);

	// On verifie que la table contient une table de maniere alternative
	bool trouve = false;

	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		if (arbre->getEnfant(i)->obtenirType() == ArbreRenduINF2990::NOM_TABLE)
			trouve = true;

	}
	CPPUNIT_ASSERT(trouve == true);

	// Les proprietes de jeu ne sont pas negatives
	for (int i = 0; i < 5; i++)
		CPPUNIT_ASSERT(arbre->obtenirProprietes()[i] > 0);

	// On vide l'arbre
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testXmlInexistant()
///
/// Cas de test: Ouverture de fichier XML et initialisation de l'arbre
///	a partir de ce que contient le fichier.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testXmlInexistant()
{
	// On ouvre un fichier inexistant
	bool test = arbre->initialiserXML("zones/.xml");
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

	// On obtient le noeud lie au portail obtenu.
	NoeudAbstrait* portail2 = portail1->getTwin();

	// L'objet lie est un autre portail.
	CPPUNIT_ASSERT(portail2->obtenirType() == ArbreRenduINF2990::NOM_PORTAIL);

	// On vide l'arbre.
	arbre->vider();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::creerNoeudParUsine()
///
/// Cas de test: Creation de noeuds avec les usines.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::creerNoeudParUsine()
{
	// On cree un noeud de type non reconnu par les usines.
	NoeudAbstrait* noeudVide = arbre->creerNoeud("NOM_CIBLE");

	// On cree un nom de type reconnu par une usine.
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
/// Cas de test: Test des limites de la boite englobante d'un noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::boiteEnglobante()
{
	// On cree une cible.
	NoeudAbstrait* noeudCible = arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE);

	// On obtient sa position.
	glm::dvec3 vecteur{ noeudCible->obtenirPositionRelative() };

	// On verifie que le noeud est en position relative (0,0,0).
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2]));

	// On cree un point a (0,0,0)
	glm::dvec3 point;
	point[0] = 0;
	point[1] = 0;
	point[2] = 0;

	// On verifie qu'il est dans la boite englobante de la cible.
	CPPUNIT_ASSERT(noeudCible->pointEstDansBoite(point));

	// On deplace le point en X.
	point[0] = 100;
	point[1] = 0;
	point[2] = 0;

	// On verifie qu'il n'est plus dans la boite englobante de la cible.
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
/// Cas de test: On s'assure qu'un table n'est pas selectionnable.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::selectionTable()
{
	// On initialise l'arbre avec le fichier XML par defaut
	arbre->initialiser();

	// On verifie que les elements par defaut sont dans l'arbre.
	//CPPUNIT_ASSERT(arbre->estDefaut() == true);

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
/// Cas de test: Test du visiteur de deselection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testDeselection()
{
	// On initialise l'arbre avec le fichier XML par defaut
	arbre->initialiser();

	// On cherche un ressort.
	NoeudAbstrait* noeudRessort = arbre->chercher(ArbreRenduINF2990::NOM_RESSORT);

	// Selectionner l'objet
	noeudRessort->assignerSelection(true);
	VisiteurDeselectionnerTout* visiteurDeselection = new VisiteurDeselectionnerTout();

	// Test du visiteur de deselection
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
	// On initialise l'arbre avec le fichier XML par defaut
	arbre->initialiser();

	// On cherche un ressort.
	NoeudAbstrait* noeudRessort = arbre->chercher(ArbreRenduINF2990::NOM_RESSORT);

	// Selectionner l'objet
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
/// Cas de test: Test du visiteur de selection multiple.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testSelectionMultiple()
{
	// On initialise l'arbre avec le fichier XML par defaut.
	arbre->initialiser();

	CPPUNIT_ASSERT(arbre->getEnfant(0)->obtenirType() == ArbreRenduINF2990::NOM_TABLE);

	// On accede a la table et on ajoute deux cibles.
	bool ajout1 = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };
	bool ajout2 = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };

	// Les deux cibles ont ete ajoutees.
	CPPUNIT_ASSERT(ajout1 == true);
	CPPUNIT_ASSERT(ajout2 == true);

	// Une cible est bien creee en position {0,0,0}.
	NoeudAbstrait* cible = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_CIBLE);
	glm::dvec3 position = cible->obtenirPositionRelative();
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(position[0]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(position[1]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(position[2]));

	// On cree un visiteur dans une boite de 10x10 autour du point central avec les deux cibles.
	VisiteurSelectionMultiple* visSelecMult = new VisiteurSelectionMultiple({ -10.0, -10.0, 0.0 }, { 10.0, 10.0, 0.0 });

	// On visite les elements.
	arbre->getEnfant(0)->accepterVisiteur(visSelecMult);

	// Deux objets sont selectionnes
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
/// Cas de test: Test du visiteur de selection inverse.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testSelectionInverse()
{
	// On initialise l'arbre avec le fichier XML par defaut.
	arbre->initialiser();

	// On accede a la table et on ajoute une cible.
	bool ajout = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };

	// La cible a ete ajoutee.	
	CPPUNIT_ASSERT(ajout == true);

	// On selectionne la cible.
	NoeudAbstrait* noeudCible = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_CIBLE);
	noeudCible->assignerSelection(true);

	VisiteurSelectionInverse* visSelInv = new VisiteurSelectionInverse({0.0,0.0,0.0}, noeudCible->getNumero());

	// On deselectionne la cible avec la selection inverse.
	noeudCible->accepterVisiteur(visSelInv);

	CPPUNIT_ASSERT(noeudCible->estSelectionne() == false);

	// Nettoyage.
	delete visSelInv;

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testDuplication()
///
/// Cas de test: Test du visiteur de duplication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testDuplication()
{
	// On initialise l'arbre avec le fichier XML par defaut.
	arbre->initialiser();

	// On accede a la table et on ajoute une cible.
	bool ajout = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };

	// La cible a ete ajoutee.	
	CPPUNIT_ASSERT(ajout == true);

	// On selectionne la cible.
	NoeudAbstrait* noeudCible = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_CIBLE);
	noeudCible->assignerSelection(true);

	// Nombre d'enfants avant la duplication.
	int enfantsAvant = arbre->getEnfant(0)->obtenirNombreEnfants();

	// Visiteur Duplication fait sa job (on l'espere).
	VisiteurDuplication* visiteurDup = new VisiteurDuplication();
	arbre->accepterVisiteur(visiteurDup);

	// Nombre d'enfants apres la duplication
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
/// Cas de test: Test du visiteur qui cree une liste des boites
/// englobantes.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testBoiteEnglobante()
{
	// On initialise l'arbre avec le fichier XML par defaut.
	arbre->initialiser();

	// On accede a la table et on ajoute une cible.
	bool ajout = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };

	// La cible a ete ajoutee.	
	CPPUNIT_ASSERT(ajout == true);

	// On selectionne la cible.
	NoeudAbstrait* noeudCible = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_CIBLE);
	noeudCible->assignerSelection(true);

	// Visiteur Liste Englobante.
	VisiteurListeEnglobante* visBoiteEngl = new VisiteurListeEnglobante();
	noeudCible->accepterVisiteur(visBoiteEngl);

	// On obtient l'attribut du visiteur.
	std::vector<conteneur_boite_englobante> liste = visBoiteEngl->obtenirListeEnglobante();

	// Le bon noeud est insere.
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
	// On initialise l'arbre avec le fichier XML par defaut.
	arbre->initialiserXML("zones/testcouleurs.xml");

	// On trouve les palettes de J1 et J2 (il y a une palette differente par joueur).
	NoeudAbstrait* paletteDJ1 = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_PALETTED);
	NoeudAbstrait* paletteGJ2 = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_PALETTEG);
	
	// On s'assure que leur couleur est differente.
	CPPUNIT_ASSERT(paletteDJ1->getColorShift() != paletteGJ2->getColorShift());

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testAgrandissement()
///
/// Cas de test: Test du visiteur d'agrandissement des noeuds dans le
/// cas general.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testAgrandissement()
{
	// On initialise l'arbre avec le fichier XML par defaut.
	arbre->initialiser();

	// On accede a la table et on ajoute une cible.
	bool ajout = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };

	// La cible a ete ajoutee.	
	CPPUNIT_ASSERT(ajout == true);

	// On selectionne la cible.
	NoeudAbstrait* noeudCible = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_CIBLE);
	noeudCible->assignerSelection(true);

	// Agrandissement de depart.
	glm::dvec3 agrandissementOriginal = noeudCible->obtenirAgrandissement();

	glm::dvec3 homothetie = { 10.0, 10.0, 10.0 };

	// Visiteur Agrandissement.
	VisiteurAgrandissement* visAgrand = new VisiteurAgrandissement(homothetie);
	noeudCible->accepterVisiteur(visAgrand);

	// Agrandissement apres la visite.
	glm::dvec3 agrandissementFinal = noeudCible->obtenirAgrandissement();

	// L'agrandissement a ete effectue correctement.
	CPPUNIT_ASSERT(agrandissementFinal.x = agrandissementOriginal.x * homothetie.x);
	CPPUNIT_ASSERT(agrandissementFinal.y = agrandissementOriginal.y * homothetie.y);
	CPPUNIT_ASSERT(agrandissementFinal.z = agrandissementOriginal.z * homothetie.z);

	// Nettoyage.
	delete visAgrand;

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testAgrandissementMur()
///
/// Cas de test: Test du visiteur d'agrandissement des noeuds dans le
/// cas d'un mur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testAgrandissementMur()
{
	// On initialise l'arbre avec le fichier XML par defaut.
	arbre->initialiser();

	// On accede a la table et on ajoute un mur.
	bool ajout = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_MUR)) };

	// Le mur a ete ajoute.	
	CPPUNIT_ASSERT(ajout == true);

	// On selectionne le mur.
	NoeudAbstrait* noeudMur = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_MUR);
	noeudMur->assignerSelection(true);

	// Agrandissement de depart.
	glm::dvec3 agrandissementOriginal = noeudMur->obtenirAgrandissement();

	glm::dvec3 homothetie = { 10.0, 10.0, 10.0 };

	// Visiteur Agrandissement.
	VisiteurAgrandissement* visAgrand = new VisiteurAgrandissement(homothetie);
	noeudMur->accepterVisiteur(visAgrand);

	// Agrandissement apres la visite.
	glm::dvec3 agrandissementFinal = noeudMur->obtenirAgrandissement();

	// L'agrandissement a ete effectue correctement.
	CPPUNIT_ASSERT(agrandissementFinal.x = agrandissementOriginal.x);
	CPPUNIT_ASSERT(agrandissementFinal.y = agrandissementOriginal.y * homothetie.y);
	CPPUNIT_ASSERT(agrandissementFinal.z = agrandissementOriginal.z);

	// Nettoyage.
	delete visAgrand;

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testSelection()
///
/// Cas de test: Test du visiteur de selection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testSelection()
{
	// On initialise l'arbre avec le fichier XML par defaut.
	arbre->initialiser();

	// On accede a la table et on ajoute une cible.
	bool ajout = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };

	// La cible a ete ajoutee.	
	CPPUNIT_ASSERT(ajout == true);

	// On cherche la cible
	NoeudAbstrait* noeudCible = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_CIBLE);
	CPPUNIT_ASSERT(noeudCible->estSelectionne() == false);

	// Visiteur Selection.
	VisiteurSelection* visSel = new VisiteurSelection({ 0.0, 0.0, 0.0 }, noeudCible->getNumero());

	// On visite le noeud.
	noeudCible->accepterVisiteur(visSel);

	// Le noeud est maintenant selectionne.
	CPPUNIT_ASSERT(noeudCible->estSelectionne() == true);

	// Nettoyage.
	delete visSel;

	// On vide l'arbre.
	arbre->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::testSelection()
///
/// Cas de test: Test du visiteur de possibilite. Un noeud est detecte
/// comme aberrant lorsque sa position se trouve en dehors des limties
/// de la table.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testPossibilite()
{
	// On initialise l'arbre avec le fichier XML par defaut.
	arbre->initialiser();

	// Visiteur Possibilite.
	VisiteurPossibilite* visPos = new VisiteurPossibilite();

	// On visite l'arbre.
	CPPUNIT_ASSERT(arbre->accepterVisiteur(visPos));

	// On accede a la table et on ajoute une cible.
	bool ajout = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };

	// La cible a ete ajoutee.	
	CPPUNIT_ASSERT(ajout == true);

	// On cherche la cible et on la deplace hors de la table.
	NoeudAbstrait* noeudCible = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_CIBLE);
	noeudCible->assignerPositionRelative({ 1000.0, 1000.0, 1000.0 });

	// On revisite l'arbre.
	arbre->accepterVisiteur(visPos);

	// Un noeud impossible est detecte.
	CPPUNIT_ASSERT(noeudCible->estImpossible());

	// Nettoyage.
	delete visPos;

	// On vide l'arbre.
	arbre->vider();
}

void ArbreRenduINF2990Test::testDeplacement()
{
	// On initialise l'arbre avec le fichier XML par defaut.
	arbre->initialiser();

	// On accede a la table et on ajoute une cible.
	bool ajout = { arbre->getEnfant(0)->ajouter(arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE)) };

	// La cible a ete ajoutee.	
	CPPUNIT_ASSERT(ajout == true);

	// On selectionne la cible.
	NoeudAbstrait* noeudCible = arbre->getEnfant(0)->chercher(ArbreRenduINF2990::NOM_CIBLE);
	noeudCible->assignerSelection(true);

	// Position de depart.
	glm::dvec3 posOriginal = noeudCible->obtenirPositionRelative();

	glm::dvec3 deplacement = { 10.0, 10.0, 10.0 };

	// Visiteur Deplacement.
	VisiteurDeplacement* visDeplac = new VisiteurDeplacement(deplacement);
	noeudCible->accepterVisiteur(visDeplac);

	// Position apres la visite.
	glm::dvec3 posFinal = noeudCible->obtenirPositionRelative();

	// Le deplacement a ete effectue correctement.
	CPPUNIT_ASSERT(posFinal.x = posOriginal.x + deplacement.x);
	CPPUNIT_ASSERT(posFinal.y = posOriginal.y + deplacement.y);
	CPPUNIT_ASSERT(posFinal.z = posOriginal.z + deplacement.z);

	// Nettoyage.
	delete visDeplac;

	// On vide l'arbre.
	arbre->vider();
}
*/