////////////////////////////////////////////////////////////////////////////////////
/// @file BancTests.cpp
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @ingroup Test
////////////////////////////////////////////////////////////////////////////////////

#include "BancTests.h"

// Inclusions cppunit pour l'execution des tests
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

SINGLETON_DECLARATION_CPP(BancTests);

////////////////////////////////////////////////////////////////////////
///
/// @fn bool BancTests::executer()
///
/// Cette fonction execute l'ensemble des tests unitaires definis.
/// La sortie de l'execution des tests se fait dans la console standard
/// d'erreurs 'cerr'. Cette fonction ajuste egalement le format de
/// sortie pour correspondre a celui de Visual Studio afin d'integrer
/// l'execution des tests au processus de compilation ("Post Build Event").
///
/// @return true si l'execution de tous les tests a reussi, sinon false.
///
////////////////////////////////////////////////////////////////////////
bool BancTests::executer()
{
	// Obtenir la suite de tests a haut niveau
	CppUnit::Test *suite{ CppUnit::TestFactoryRegistry::getRegistry().makeTest() };

	// Obtient un environnement d'execution de tests qui imprime les resultats
	// dans une console (cout, cerr, fichier, etc.) et ajoute la suite de tests
	// de base a l'environnement.
	// (Notez qu'il est aussi possible d'obtenir un environnement qui affiche
	// les resultats des tests au sein d'une interface graphique QT ou MFC.
	// Consultez la documentation cppunit pour plus d'informations)
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);

	// Indique que nous souhaitons formatter la sortie selon un format qui
	// s'apparente a la sortie d'un compilateur (MSVC++), et que nous
	// souhaitons que la sortie soit realisee dans le canal standard cerr.
	// Cela permettra a Visual Studio d'interpreter la sortie de cppunit,
	// d'indiquer les erreurs trouvees par les tests et leur numero de ligne
	// en tant qu'erreurs survenant au niveau du processus de compilation.
	runner.setOutputter(new CppUnit::CompilerOutputter{ &runner.result(),
		std::cerr });
	// Executer les tests
	return runner.run();
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
