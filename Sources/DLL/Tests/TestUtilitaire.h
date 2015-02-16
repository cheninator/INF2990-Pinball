//////////////////////////////////////////////////////////////////////////////
/// @file TestUtilitaire.h
/// @author The Ballers
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
///        methodes de la classe Utilitaire.
///
/// @author The Ballers
/// @date 2012-02-12
/// @ingroup Test
///////////////////////////////////////////////////////////////////////////
class TestUtilitaire : public CppUnit::TestFixture
{

	// =================================================================
	// Declaration de la suite de tests et des methodes de tests
	//
	// Important, vous devez definir chacun de vos cas de tests a l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas execute !
	// =================================================================
	CPPUNIT_TEST_SUITE(TestUtilitaire);
	CPPUNIT_TEST(testIntersection);
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


	/// Cas de test: s'assurer que le noeud abstrait n'a pas d'enfant
	void testIntersection();

private:

};

#endif // _TESTS_TESTUTILITAIRE_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
