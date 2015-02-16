////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstraitTest.cpp
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @ingroup Test
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudAbstraitTest.h"
#include "NoeudVide.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudAbstraitTest);

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
void NoeudAbstraitTest::setUp()
{
	noeud = std::make_unique<NoeudVide>( ArbreRenduINF2990::NOM_VIDE );
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
void NoeudAbstraitTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testPositionRelative()
///
/// Cas de test: ecriture/lecture de la position relative
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testPositionRelative()
{
	// Premier test : on verifie que la position initiale est un vector nul
	glm::dvec3 vecteur{ noeud->obtenirPositionRelative() };
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2]));

	// On modifie la position
	noeud->assignerPositionRelative(glm::dvec3{ 2.2, 3.3, 4.4 });

	// Second test : on verifie que la position a ete modifiee
	vecteur = noeud->obtenirPositionRelative();
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0] - 2.2));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1] - 3.3));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2] - 4.4));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testType()
///
/// Cas de test: type de noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testType()
{
	CPPUNIT_ASSERT(noeud->obtenirType() == ArbreRenduINF2990::NOM_VIDE);
	CPPUNIT_ASSERT(noeud->obtenirType() != ArbreRenduINF2990::NOM_TABLE);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testSelection()
///
/// Cas de test: definition/obtention des etats de selection du noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testSelection()
{
	// Cas 1 : non selectionnable, non selectionne
	noeud->assignerEstSelectionnable(false);
	noeud->assignerSelection(false);
	CPPUNIT_ASSERT(noeud->estSelectionnable() == false);
	CPPUNIT_ASSERT(noeud->estSelectionne() == false);

	// Cas 2 : non selectionnable, selectionne
	noeud->assignerEstSelectionnable(false);
	noeud->assignerSelection(true);
	CPPUNIT_ASSERT(noeud->estSelectionnable() == false);
	CPPUNIT_ASSERT(noeud->estSelectionne() == false);

	// Cas 3 : selectionnable, non selectionne
	noeud->assignerEstSelectionnable(true);
	noeud->assignerSelection(false);
	CPPUNIT_ASSERT(noeud->estSelectionnable() == true);
	CPPUNIT_ASSERT(noeud->estSelectionne() == false);

	// Cas 4 : non selectionnable, selectionne
	noeud->assignerEstSelectionnable(true);
	noeud->assignerSelection(true);
	CPPUNIT_ASSERT(noeud->estSelectionnable() == true);
	CPPUNIT_ASSERT(noeud->estSelectionne() == true);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testEnfants()
///
/// Cas de test: s'assurer que le noeud abstrait n'a pas d'enfant
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testEnfants()
{
	// On verifie qu'initialement, le noeud n'a pas d'enfant
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeud->calculerProfondeur() == 1);

	// Essaie d'ajouter un noeud
	NoeudAbstrait* nouveauNoeud{ new NoeudVide{ ArbreRenduINF2990::NOM_VIDE } };
	bool ajout{ noeud->ajouter(nouveauNoeud) };

	// L'ajout devrait avoir echoue puisqu'il s'agit d'un noeud abstrait...
	CPPUNIT_ASSERT(ajout == false);

	// Assurons-nous que le noeud ne possede pas d'enfant...
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeud->calculerProfondeur() == 1);

	// Nettoyage
	delete nouveauNoeud;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
