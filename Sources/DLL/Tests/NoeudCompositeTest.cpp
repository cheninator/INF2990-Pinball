/*
////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.cpp
/// @author The Ballers
/// @date 2015-02-10
/// @version 1.0
///
/// @ingroup Test
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudCompositeTest.h"
#include "NoeudCible.h"
#include "NoeudTable.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudCompositeTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::setUp()
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
void NoeudCompositeTest::setUp()
{
	noeud = std::make_unique<NoeudTable>(ArbreRenduINF2990::NOM_TABLE);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::tearDown()
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
void NoeudCompositeTest::tearDown()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testEnfants()
///
/// Cas de test: s'assurer que le noeud composite peut posseder des enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEnfants()
{
	// On verifie qu'initialement, le noeud n'a pas d'enfant
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeud->calculerProfondeur() == 1);

	// Essaie d'ajout d'un noeud
	NoeudComposite* nouveauNoeud{ new NoeudCible{ ArbreRenduINF2990::NOM_CIBLE } };
	bool ajout{ noeud->ajouter(nouveauNoeud) };

	// L'ajout devrait avoir reussi, puisqu'il s'agit d'un noeud composite.
	CPPUNIT_ASSERT(ajout == true);

	// Assurons-nous que le noeud possede un enfant.
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeud->calculerProfondeur() == 2);

	// Nettoyage
	noeud->effacer(nouveauNoeud);

	// Assurons-nous que le noeud ne possede plus d'enfants.
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeud->calculerProfondeur() == 1);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
*/