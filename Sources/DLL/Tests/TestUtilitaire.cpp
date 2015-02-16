////////////////////////////////////////////////////////////////////////////////////
/// @file TestUtilitaire.cpp
/// @author The Ballers
/// @date 2012-02-12
/// @version 1.0
///
/// @ingroup Test
////////////////////////////////////////////////////////////////////////////////////

#include "TestUtilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(TestUtilitaire);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::setUp()
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
void TestUtilitaire::setUp()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::tearDown()
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
void TestUtilitaire::tearDown()
{

}

void TestUtilitaire::testIntersection()
{
	// Deux sections qui s'intersectent.
	glm::dvec3 p1 = { -50.0, 0.0, 0.0 };
	glm::dvec3 p2 = { 50.0, 0.0, 0.0 };
	glm::dvec3 p3 = { 0.0, 50.0, 0.0 };
	glm::dvec3 p4 = { 50.0, -50.0, 0.0 };

	CPPUNIT_ASSERT(utilitaire::intersectionDeuxSegments(p1, p2, p3, p4));

	// Deux sections qui ne s'intersectent pas.
	glm::dvec3 p5 = { -50.0, 0.0, 0.0 };
	glm::dvec3 p6 = { 50.0, 0.0, 0.0 };
	glm::dvec3 p7 = { 0.0, 50.0, 0.0 };
	glm::dvec3 p8 = { 50.0, 50.0, 50.0 };

	CPPUNIT_ASSERT(utilitaire::intersectionDeuxSegments(p5, p6, p7, p8) == false);
}