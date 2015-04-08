/*
//////////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990Test.h
/// @author The Ballers
/// @date 2015-02-12
/// @version 1.0
///
/// @ingroup Test
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_ARBRERENDUINF2990TEST_H
#define _TESTS_ARBRERENDUINF2990TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>

class VisiteurAbstrait;
class ArbreRenduINF2990;
#include "ArbreRenduINF2990.h"


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990Test
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        methodes de la classe ArbreRenduINF2990.
///
/// @author The Ballers
/// @date 2015-02-12
/// @ingroup Test
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990Test : public CppUnit::TestFixture
{

	// =================================================================
	// Declaration de la suite de tests et des methodes de tests
	//
	// Important, vous devez definir chacun de vos cas de tests a l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas execute !
	// =================================================================
	CPPUNIT_TEST_SUITE(ArbreRenduINF2990Test);
	CPPUNIT_TEST(testArbreDefaut);
	CPPUNIT_TEST(testXmlInexistant);
	CPPUNIT_TEST(testPortails);
	CPPUNIT_TEST(creerNoeudParUsine);
	CPPUNIT_TEST(boiteEnglobante);
	CPPUNIT_TEST(selectionTable);
	CPPUNIT_TEST(testDeselection);
	CPPUNIT_TEST(testRotation);
	CPPUNIT_TEST(testSelectionMultiple);
	CPPUNIT_TEST(testSelectionInverse);
	CPPUNIT_TEST(testDuplication);
	CPPUNIT_TEST(testBoiteEnglobante);
	CPPUNIT_TEST(testPalettes);
	CPPUNIT_TEST(testAgrandissement);
	CPPUNIT_TEST(testAgrandissementMur);
	CPPUNIT_TEST(testSelection);
	CPPUNIT_TEST(testPossibilite);
	CPPUNIT_TEST(testDeplacement);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Methodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement a effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement a effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// Definissez ici les differents cas de tests...
	// =================================================================

	/// Cas de test: Initialiser l'arbre par defaut.
	void testArbreDefaut();

	/// Cas de test: Le fichier XML charge est n'existe pas.
	void testXmlInexistant();

	/// Cas de test: Suppression simple et multiple par le visiteur
	void testPortails();

	/// Cas de test: Creer un noeud de type inexistant.
	void creerNoeudParUsine();

	/// Cas de test: Test boîte englobante.
	void boiteEnglobante();

	/// Cas de test: Selectionner un objet non selectionnable (table).
	void selectionTable();

	/// Cas de test: Deselectionner tout.
	void testDeselection();

	/// Cas de test: Rotation en x / y / z
	void testRotation();

	/// Cas de test: Selection multiple.
	void testSelectionMultiple();

	/// Cas de test: Selection inverse.
	void testSelectionInverse();

	/// Cas de test: Duplication.
	void testDuplication();

	/// Cas de test: Limite selection.
	void testBoiteEnglobante();

	/// Cas de test : Couleur des palettes des joueurs.
	void testPalettes();

	/// Cas de test : Agrandissement.
	void testAgrandissement();

	/// Cas de test : Agrandissement d'un mur.
	void testAgrandissementMur();

	/// Cas de test : Selection.
	void testSelection();
	
	/// Cas de test : Possibilite
	void testPossibilite();

	/// Cas de test : Deplacement
	void testDeplacement();

private:
	/// Instance d'un arbre
	std::unique_ptr<ArbreRenduINF2990> arbre;
};

#endif // _TESTS_ARBRERENDUINF2990_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
*/