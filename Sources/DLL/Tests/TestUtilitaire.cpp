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
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
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
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
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