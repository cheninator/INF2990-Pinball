//////////////////////////////////////////////////////////////////////////////
/// @file TestUtilitaire.h
/// @author Samuel Millette
/// @date 2012-02-12
/// @version 1.0
///
/// @ingroup Test
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_TESTUTILITAIRE_H
#define _TESTS_TESTUTILITAIRE_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>

class ArbreRenduINF2990;
#include "ArbreRenduINF2990.h"

///////////////////////////////////////////////////////////////////////////
/// @class TestUtilitaire
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe Utilitaire.
///
/// @author Samuel Millette
/// @date 2012-02-12
/// @ingroup Test
///////////////////////////////////////////////////////////////////////////
class TestUtilitaire : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(TestUtilitaire);
	CPPUNIT_TEST(testIntersection);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// Définissez ici les différents cas de tests...
	// =================================================================


	/// Cas de test: s'assurer que le noeud abstrait n'a pas d'enfant
	void testIntersection();

private:

};

#endif // _TESTS_TESTUTILITAIRE_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
