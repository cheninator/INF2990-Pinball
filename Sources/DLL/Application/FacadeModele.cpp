///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @ingroup Application
///////////////////////////////////////////////////////////////////////////////

// Commentaire Doxygen mis sur la premiere page de la documentation Doxygen.
/**

@mainpage Projet integrateur de deuxieme annee -- INF2990

PAINBALL
<BR>
<BR>
Auteurs:<BR>
Aymen Dje <BR>
Nikolay Radoev <BR>
Yonni Chen <BR>
Emilio Rivera <BR>
Philippe Carpin <BR>
Kim Piche <BR>
Samuel Millette <BR>

*/

#include <windows.h>
#include <cassert>
#include <iostream>

#include "GL/glew.h"
#include "FreeImage.h"

#include "FacadeModele.h"

#include "../Visiteurs/VisiteurAbstrait.h"
#include "../Visiteurs/VisiteurSelection.h"
#include "../Visiteurs/VisiteurSelectionInverse.h"
#include "../Visiteurs/VisiteurSelectionMultiple.h"
#include "../Visiteurs/VisiteurSelectionInverseMultiple.h"
#include "../Visiteurs/VisiteurDeplacement.h"
#include "../Visiteurs/VisiteurCentreDeMasse.h"
#include "../Visiteurs/VisiteurRotationPoint.h"
#include "../Visiteurs/VisiteurAgrandissement.h"
#include "../Visiteurs/VisiteurDuplication.h"
#include "../Visiteurs/VisiteurLimitesSelection.h"
#include "../Visiteurs/VisiteurListeEnglobante.h"
#include "../Visiteurs/VisiteurPossibilite.h"
#include "../Visiteurs/VisiteurSuppression.h"
#include "../Visiteurs/VisiteurXML.h"
#include "../Visiteurs/VisiteurConstruireListes.h"

#include "VueOrtho.h"
#include "Camera.h"
#include "Projection.h"

#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"

#include "CompteurAffichage.h"
#include "../Configuration/ConfigScene.h"

// Remplacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, ete 2011
#include "tinyxml2.h"

#include "glm/gtc/type_ptr.hpp"

#define M_PI	3.141592653589793238462643383279502884

/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_{ nullptr };

const int FacadeModele::coinGaucheTableX= 108;
const int FacadeModele::coinGaucheTableY = -190;
const int FacadeModele::coinDroitTableX = 272;
const int FacadeModele::coinDroitTableY = 96;

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas ete creee, elle la cree.  Cette
/// creation n'est toutefois pas necessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa creation.
///
/// @return Un pointeur vers l'instance unique de cette classe.
///
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new FacadeModele();
		instance_->configuration_ = new ConfigScene();
	}



	return instance_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererInstance()
///
/// Cette fonction libere l'instance unique de cette classe.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererInstance()
{
	delete instance_;
	instance_ = nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::~FacadeModele()
///
/// Ce destructeur libere les objets du modele.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::~FacadeModele()
{
	delete arbre_;
	delete vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserOpenGL(HWND hWnd)
///
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle cree
/// un contexte OpenGL sur la fenetre passee en parametre, initialise
/// FreeImage (utilisee par le chargeur de modeles) et assigne des 
/// parametres du contexte OpenGL.
///
/// @param[in] hWnd : La poignee ("handle") vers la fenetre a utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu etre cree.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// FreeImage, utilisee par le chargeur, doit etre initialisee
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.7843f, 0.7843f, 0.7843f, 0.0f);

	// Initialiser le stencil a 0.
	glClearStencil(0);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP,GL_KEEP,  GL_REPLACE);

	// Les lumieres
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);

	// Blending
	glEnable(GL_BLEND);

	// Qualite
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// Le cull face
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	// Creation de l'arbre de rendu.  a moins d'etre completement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de creer
	// l'arbre apres avoir cree le contexte OpenGL.
	std::cout << "Creation de l'arbre de rendu..." << std::endl;
	arbre_ = new ArbreRenduINF2990;
	std::cout << "Initialisation de l'arbre de rendu..." << std::endl;
	arbre_->initialiser();
	// On cree une vue par defaut.
	vue_ = new vue::VueOrtho{
		vue::Camera{ 
			glm::dvec3(0, 0, 200), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 1, 0),   glm::dvec3(0, 1, 0)},
		vue::ProjectionOrtho{ 
				0, 500, 0, 500,
				1, 1000, 50, 5000, 1.25,
				double(coinGaucheTableX), double(coinGaucheTableY),
				double(coinDroitTableX), double(coinDroitTableY)}
	};
	std::cout << "Arbre de rendu generer !" << std::endl << std::endl << std::endl;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction libere le contexte OpenGL et desinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu etre detruit.");

	FreeImage_DeInitialise();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la scene.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher() const
{
	// Efface l'ancien rendu
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Ne devrait pas etre necessaire
	vue_->appliquerProjection();

	// Positionne la camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	vue_->appliquerCamera();

	// Afficher la scene
	afficherBase();

	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

	// echange les tampons pour que le resultat du rendu soit visible.
	::SwapBuffers(hDC_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// @remark Cette fonction affiche la base du contenu de la scene, c'est-a-dire
/// \remark qu'elle met en place l'eclairage et affiche les objets.
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	// Positionner la lumiere.
	glm::vec4 position{ 0, 0, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(position));

	// Afficher la scene.
	arbre_->afficher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// @remark Cette fonction reinitialise la scene a un etat "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// Reinitialisation de la scene.
	arbre_->initialiser();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// @remark Cette fonction effectue les differents calculs d'animations
/// \remark necessaires pour le mode jeu, tel que les differents calculs de
/// \remark physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	// Mise a jour des objets.
	arbre_->animer(temps);

	// Mise a jour de la vue.
	vue_->animer(temps);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::selectionnerObjetSousPointClique(int i, int j, int hauteur, int largeur, bool ctrlDown)
///
/// @remark Cette fonction permet de selectionner un objet. La methode regarde la valeur
/// \remark du stencil et la donne a un visiteurSelection qui compare cette valeur
/// \remark aux numeros des noeuds et change les met selectionnes ou pas selon le resultat
/// \remark de la comparaison et selon qu'on a clique avec CTRL.
///
/// @param[in] i : Position souris i
/// @param[in] j : Position souris j
/// @param[in] hauteur : Hauteur de la fenetre
/// @param[in] largeur : Largeur de la fenetre
/// @param[in] ctrlDown : Si le bouton ctrl est appuie
///
/// @return NoeudAbstrait.
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::selectionnerObjetSousPointClique(int i, int j, int hauteur, int largeur, bool ctrlDown)
{
	glm::dvec3 pointDansLeMonde;
	vue_->convertirClotureAVirtuelle(i, j, pointDansLeMonde);

	int valeurStencil = 0;
	glReadPixels(i ,hauteur -j , 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &valeurStencil);
	
	if (!ctrlDown)
	{
		VisiteurSelection visSel(pointDansLeMonde, valeurStencil);
		arbre_->accepterVisiteur(&visSel);

		// Demander au visiteur ce qu'il a trouve et faire quelque chose en consequence
		return visSel.obtenirNbObjetsSelectionne();
	}
	else
	{
		VisiteurSelectionInverse visSelInverse(pointDansLeMonde, valeurStencil);
		arbre_->accepterVisiteur(&visSelInverse);

		// Demander au visiteur ce qu'il a trouve et faire quelque chose en consequence
		return visSelInverse.obtenirNbObjetsSelectionne();
	}

}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacerSelection(int x1, int y1, int x2, int y2, bool duplication)
///		@remark deplace les noeuds selectionnes d'un deplacement calcule en coordonnees du monde
///		\remark a partir des points initiaux et terminaux dans les coordonnees d'affichage OpenGL
///
/// @param[in]  x1 : abcisse du point initial
/// @param[in]  y1 : ordonnee du point initial
///
/// @param[in]  x2 : abcisse du point initial
/// @param[in]  y2 : ordonnee du point initial
///
/// @param[in]  duplication : Logique de deplacement lors de l'etat de duplication
///
/// @return Aucune.
///
/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
///
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerSelection(int x1, int y1 ,int x2, int y2, bool duplication)
{
	glm::dvec3 positionInitiale, positionFinale;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x1, y1, positionInitiale);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x2, y2, positionFinale);

	// Visiter l'arbre pour trouver les limites d'une boite
	// minX, minY, maxX, maxY
	VisiteurLimitesSelection VisLimSel;
	arbre_->accepterVisiteur(&VisLimSel);
	glm::dvec3 pointMax{ VisLimSel.getXMax(), VisLimSel.getYMax(), 0 };
	glm::dvec3 pointMin{ VisLimSel.getXMin(), VisLimSel.getYMin(), 0 };

	// Logique de deplacement lors de l'etat de duplication
	if (duplication)
	{
		// Trouver le centre de masse de la selection
		VisiteurCentreDeMasse visCM;
		arbre_->accepterVisiteur(&visCM);
		glm::dvec3 centreMasse = visCM.obtenirCentreDeMasse();

		// Calculer le delta des limites de la boite englobant la selection par rapport au centre de masse
		glm::dvec3 pointMaxDelta{ pointMax.x - centreMasse.x, pointMax.y - centreMasse.y, 0 };
		glm::dvec3 pointMinDelta{ pointMin.x - centreMasse.x, pointMin.y - centreMasse.y, 0 };

		// La selection suit le curseur de la souris en tout temps, mais s'affiche en rouge lorsqu'a 
		// l'exterieur de la table
		glm::dvec3 deplacement{positionFinale - centreMasse};
	    VisiteurDeplacement visDep(deplacement);
		visDep.setEstDuplication(true);

		if (estDansTable(positionFinale + pointMaxDelta) && estDansTable(positionFinale + pointMinDelta))
		{
			visDep.setEstDansLaTable(true);
			duplicationHorsTable_ = false;
		}

		else
			duplicationHorsTable_ = true;

		arbre_->accepterVisiteur(&visDep);
	}

	//Logique de deplacement lors de l'etat de deplacement
	else
	{
		//calculer le deplacement
		glm::dvec3 deplacement{ positionFinale - positionInitiale };

		//le deplacement s'applique s'il ne fait pas sortir la selection en dehors de la table
		if (estDansTable(pointMax + deplacement) && estDansTable(pointMin + deplacement))
		{
			VisiteurDeplacement visDep(deplacement);
			arbre_->accepterVisiteur(&visDep);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::tournerSelectionSouris(int x1, int y1, int x2, int y2)
///	@remark 	Fait une rotation des objets selectionnes autour de leur centre de masse.
///	\remark  	L'angle est calcule en fonction du deplacement de (x1,y1) a (x2,y2):
///	\remark 	Presentement, l'angle est proportionnel a (y1 - y2).
///	\remark 	
///	\remark 	Pour tester si la rotation est faisable, on prend tous les points des bo�tes
///	\remark 	englobantes.  Si un seul de ces points, une fois transforme, n'est pas dans la 
///	\remark 	table, on ne fait pas la rotation.
///		
/// @param[in]  x1 : abcisse du point initial
/// @param[in]  y1 : ordonnee du point initial
///
/// @param[in]  x2 : abcisse du point initial
/// @param[in]  y2 : ordonnee du point initial
///
/// @return Aucune.
///
/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
///
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::tournerSelectionSouris(int x1, int y1, int x2, int y2)
{
	// Visiter l'arbre pour trouver le centre de masse des noeuds selectionnes
	VisiteurCentreDeMasse visCM;
	arbre_->accepterVisiteur(&visCM);
	glm::dvec3 centreRotation = visCM.obtenirCentreDeMasse();

	// On calcule l'angle de la rotation:
	double angle = (y2 - y1) / 3.0;
	double angleEnRadian = angle * 2 * 3.1415926535897932384626433832795 / 360;
	glm::dmat3 transform = glm::dmat3{ glm::dvec3{ cos(-angleEnRadian), -sin(-angleEnRadian), 0 },
		glm::dvec3{ sin(-angleEnRadian), cos(-angleEnRadian), 0 },
		glm::dvec3{ 0, 0, 1 } };

	// On decide si la rotation peut se faire
	bool onTourne = true;

	// Obtenir une liste des points englobants des noeud selectionnes
	VisiteurListeEnglobante visLE;
	arbre_->accepterVisiteur(&visLE);
	
	glm::dvec3 pointTransforme;
	for (conteneur_boite_englobante boite : visLE.obtenirListeEnglobante())
	{
		for (glm::dvec3 vecteur : boite.first)
		{
			glm::dvec3 point = boite.second->obtenirPositionRelative() + vecteur ;
			pointTransforme = centreRotation + transform *(point - centreRotation);
			if (!estDansTable(pointTransforme))
				return;
		}
	}

	// Visiter l'arbre et faire la rotation.
	if (onTourne)
	{
		VisiteurRotationPoint visSP(glm::dvec3{ 0, 0, angle }, centreRotation);
		arbre_->accepterVisiteur(&visSP);
	}

}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::agrandirSelection(int x1, int y1, int x2, int y2)
///	@remark 	Fait un agrandissement des objets selectionnes.
///	\remark 	L'agrandissement est calcule en fonction du deplacement de (x1,y1) a (x2,y2)
///
/// @param[in]  x1 : abcisse du point initial
/// @param[in]  y1 : ordonnee du point initial
///
/// @param[in]  x2 : abcisse du point initial
/// @param[in]  y2 : ordonnee du point initial
///
/// @return Aucune.
///
/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
///
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::agrandirSelection(int x1, int y1, int x2, int y2)
{
	double scale = glm::exp((y1 - y2) * glm::log(1.003)); // exp(b log(a)) = a^b
	// Pour agrandir on multiplie le scale courrant par 1.003 et ce une fois pour chaque deplacement en y
	// donc on multiplie par 1.003^(y1-y2).
	// Si (y1-y2) est negatif, ceci va nous faire diviser par 1.003, donc l'objet va rapetisser.
	
	// Au final, on multiplie le scale courrant par 1.003 une fois pour chaque deplacement elementaire vers le haut,
	// On divise par 1.003 pour chaque deplacement elementaire vers le bas.
	double distanceConstante = 1.0;
	double correctionZ = (1 - scale) * distanceConstante;

	VisiteurListeEnglobante visLE;
	arbre_->accepterVisiteur(&visLE);

	glm::dvec3 pointTransforme;
	for (conteneur_boite_englobante boite : visLE.obtenirListeEnglobante())
	{
		for (glm::dvec3 vecteur : boite.first)
		{
			glm::dvec3 point = boite.second->obtenirPositionRelative();
			pointTransforme = point + scale*vecteur;
			if (!estDansTable(pointTransforme))
				return;
		}
	}

	VisiteurAgrandissement visAgr(glm::dvec3{ scale, scale, scale });
	arbre_->accepterVisiteur(&visAgr);

	VisiteurDeplacement visDep(glm::dvec3{ 0, 0, correctionZ });
	arbre_->accepterVisiteur(&visDep);

}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserRectangleElastique(int i, int j) A COMMENTER KIM
///	
///	@remark Initialise un rectangle elastique
///
/// @param[in]  i : 
/// @param[in]  j : 
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserRectangleElastique(int i, int j)
{
	pointInitial_.x = i;
	pointInitial_.y = j;
	pointAvant_.x = i;
	pointAvant_.y = j;
	aidegl::initialiserRectangleElastique(pointAvant_, 0x3333, 5);
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::rectangleElastique(int i, int j) A COMMENTER KIM
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::rectangleElastique(int i, int j)
{
	glm::ivec2 pointApres(i, j);
	aidegl::mettreAJourRectangleElastique(pointInitial_, pointAvant_, pointApres);
	pointAvant_.x = pointApres.x;
	pointAvant_.y = pointApres.y;
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::terminerRectangleElastique() A COMMENTER KIM
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::terminerRectangleElastique()
{
	aidegl::terminerRectangleElastique(pointInitial_, pointAvant_);

	glm::dvec3 positionInitiale, positionActuelle;
	vue_->convertirClotureAVirtuelle(pointInitial_.x, pointInitial_.y, positionInitiale);
	vue_->convertirClotureAVirtuelle(pointAvant_.x, pointAvant_.y, positionActuelle);

	if (positionInitiale.x < positionActuelle.x && positionInitiale.y < positionActuelle.y)
	{
		selectionBasGauche_ = positionInitiale;
		selectionHautDroit_ = positionActuelle;
	}
	else if (positionInitiale.x > positionActuelle.x && positionInitiale.y > positionActuelle.y)
	{
		selectionBasGauche_ = positionActuelle;
		selectionHautDroit_ = positionInitiale;
	}
	else if (positionInitiale.x < positionActuelle.x && positionInitiale.y > positionActuelle.y)
	{
		selectionBasGauche_.x = positionInitiale.x;
		selectionBasGauche_.y = positionActuelle.y;
		selectionHautDroit_.x = positionActuelle.x;
		selectionHautDroit_.y = positionInitiale.y;
	}
	else if (positionInitiale.x > positionActuelle.x && positionInitiale.y < positionActuelle.y)
	{
		selectionBasGauche_.x = positionActuelle.x;
		selectionBasGauche_.y = positionInitiale.y;
		selectionHautDroit_.x = positionInitiale.x;
		selectionHautDroit_.y = positionActuelle.y;
	}
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectionMultiple(bool c) A COMMENTER KIM
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::selectionMultiple(bool c)
{
	if (c)
	{
		VisiteurSelectionInverseMultiple visSelInvMul(selectionBasGauche_, selectionHautDroit_);
		arbre_->accepterVisiteur(&visSelInvMul);

		return visSelInvMul.obtenirNbObjetsSelectionne();
	}
	else
	{
		VisiteurSelectionMultiple visSelMul(selectionBasGauche_, selectionHautDroit_);
		arbre_->accepterVisiteur(&visSelMul);

		return visSelMul.obtenirNbObjetsSelectionne();
	}
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::verifierCliqueDansTable(int x, int y)
///	@remark 	Verifie si le point du monde correspondant a (x,y) est dans la table de
///	\remark 	facon empirique ou heuristique.
///
/// @param[in]  x : abcisse du point clique
/// @param[in]  y : ordonnee du point clique
///
/// @return Aucune.
///
/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
///
///////////////////////////////////////////////////////////////////////////////
bool FacadeModele::verifierCliqueDansTable(int x, int y)
{
	glm::dvec3 positionDansLeMonde;
	obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionDansLeMonde);
	if (   coinGaucheTableX < positionDansLeMonde.x && positionDansLeMonde.x < coinDroitTableX
		&& coinGaucheTableY < positionDansLeMonde.y && positionDansLeMonde.y < coinDroitTableY)
		return true;
	else
		return false;
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::estDansTable(glm::dvec3 pointDuMonde)
///
/// @param[in]  pointDuMonde : Point dont on veut verifier qu'il est dans la table
///
/// @return Aucune.
///
/// @remark : Verifie si le point du monde est dans la table.
///
///////////////////////////////////////////////////////////////////////////////
bool FacadeModele::estDansTable(glm::dvec3 pointDuMonde)
{
	if (coinGaucheTableX < pointDuMonde.x && pointDuMonde.x < coinDroitTableX
		&& coinGaucheTableY < pointDuMonde.y && pointDuMonde.y < coinDroitTableY)
		return true;
	else
		return false;
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::dupliquerSelection(int i, int j)
///
/// @param[in]  i : Cordonees du centre de duplication en i de la souris
/// @param[in]  j : Cordonees du centre de duplication en j de la souris
///
/// @return Aucune.
///
/// @remark : Duplique les objets selectionnes.
///
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::dupliquerSelection(int i, int j)
{
	// Visiter l'arbre et faire la duplication.
	VisiteurDuplication* visiteur = new VisiteurDuplication();
	arbre_->accepterVisiteur(visiteur);
	duplicationHorsTable_ = false;
	delete visiteur;
	deplacerSelection(i, j, i, j, true);
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::creerXML(char* path, int prop[6])
///	@remark	Enregistre une zone de jeu en fichier XML
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::creerXML(char* path, int prop[6])
{
	int sauvegardeAutorise;

	// Ne pas permettre la sauvegarde si la zone ne contient pas au minimum  3 objets
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants() < 3)
	{
		sauvegardeAutorise = 0;
	}

	// Ne pas permettre de sauvegarder la zone de jeu par defaut
	else if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher("generateurbille")
		&& FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher("trou")
		&& FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher("ressort")
		&& FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants() == 3)
	{
		if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estDefaut())
			sauvegardeAutorise = 1;

		else
		{
			VisiteurXML* visiteur = new VisiteurXML(std::string(path), prop);
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur);
			sauvegardeAutorise = 2;

			delete visiteur;
		}
	}

	// Permettre la sauvegarde que lorsque il y a les 3 objets obligatoires + d'autres objets
	else if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher("generateurbille")
		&& FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher("trou")
		&& FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher("ressort")
		&& FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants() > 3)
	{
		VisiteurXML* visiteur = new VisiteurXML(std::string(path), prop);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur);
		sauvegardeAutorise = 2;

		delete visiteur;
	}
	else
	{
		sauvegardeAutorise = 3;
	}

	return sauvegardeAutorise;
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::positionnerMur(int originX, int originY,int x1, int y1, int x2, int y2, NoeudAbstrait* noeud)
///	
/// @param[in]  originX : Position en X ou le bouton a ete appuye
/// @param[in]  originY : Position en Y ou le bouton a ete appuye
/// @param[in]  x1 : Position en X precedant un deplacement de la souris
/// @param[in]  y1 : Position en Y precedant un deplacement de la souris
/// @param[in]  x2 : Position en X apres un deplacement de la souris (position actuelle de la souris)
/// @param[in]  y2 : Position en X apres un deplacement de la souris (position actuelle de la souris)
/// @param[in]  noeud : Noeud sur le quel appliquer les transformations
///
/// @return Aucune.
///
///	@remark	Positionne un mur pour qu'il soit une ligne entre ou on a appuye le bouton de gauche de la 
///	\remark	souris et la position actuelle de la souris.
///	\remark	La methode verifie aussi la boite englobante du mur pour ne pas qu'il depasse de la table.
///
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::positionnerMur(int originX, int originY,int x1, int y1, int x2, int y2, NoeudAbstrait* noeud)
{
	glm::dvec3 positionOriginale,positionInitiale, positionFinale;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(originX, originY, positionOriginale);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x2, y2, positionFinale);

	glm::dvec3 vecteur = positionFinale - positionOriginale;

	// Proprietes a appliquer:
	glm::dvec3 scaleFinal{ 1, 1, 1 };
	glm::dvec3 angles{ 0, 0, 0 };
	glm::dvec3 position = positionOriginale;

	double angleRadian;

	// Les calculs sont fait seulement si la souris est assez loin de ou on a cree le noeud.
	if (glm::length(vecteur) > 0.1)
	{
		// CALCUL DE L'ANGLE
		// =================
		glm::dvec3 axe{ 0, 1, 0 }; // On va travailler avec l'angle entre le vecteur allant de origin a la position du curseur, et l'axe Y.
		glm::dvec3 produitVectoriel = glm::cross(axe, vecteur);
		double sinAngle = glm::length(produitVectoriel) / glm::length(axe) / glm::length(vecteur);
		angleRadian = produitVectoriel.z > 0 ? asin(sinAngle) : -asin(sinAngle);

		// Prendre l'angle complementaire si on est en dessous de l'axe X.
		if (vecteur.y < 0)
			angleRadian = M_PI - angleRadian;// A passer en parametre a assignerRotation

		angles = glm::dvec3{ 0, 0, 360.0 / 2.0 / M_PI * angleRadian };
	}
		// Calcul de la translation
		// ========================
		// position = positionOriginale + vecteur / 2.0; // Le centre du mur est a mi-chemin entre origin et le point du curseur. 
	if (glm::length(vecteur) > .1)
		position = positionOriginale + vecteur / 2.0;
	else if (glm::length(vecteur) != 0)
		position = positionOriginale + 8.0 *glm::normalize(vecteur); // 
	// else
		// position = positionOriginale + glm::dvec3{ 0, 8, 0 };

	
	if (glm::length(vecteur) > 0.1)
	{
		// Calcul du scale
		// ===============
		double scale = glm::length(vecteur) / 16; //  16.0 est la longueur originale du mur. 
		scaleFinal = glm::dvec3{ 1, scale, 1 };
	}
	else
		scaleFinal = glm::dvec3{ 1, 0.1, 1 };


	// Tester la transformation
	// ========================
	glm::dvec3 boite[4];
	noeud->obtenirBoiteModele(boite[0], boite[1], boite[2], boite[3]);
	glm::dmat3 echelle = glm::dmat3{	glm::dvec3{ 1,				0,				0.0 },
										glm::dvec3{ 0,			scaleFinal.y,		0.0f },
										glm::dvec3{ 0.0,			0.0,			1 } };

	glm::dmat3 rotation = glm::dmat3{	glm::dvec3{ cos(angleRadian), sin(angleRadian), 0.0 },
										glm::dvec3{ -sin(angleRadian),	 cos(angleRadian), 0.0f },
										glm::dvec3{		 0.0,				0.0,			1.0 } };
	glm::dvec3 pointATester;
	for (int i = 0; i < 4; i++)
	{
		pointATester = position + rotation * (echelle * boite[i]);
		if (!obtenirInstance()->estDansTable(pointATester))
		{
			return;
		}
	}

	// Si on s'est rendu ici, c'est qu'on peut faire l'assignation des proprietes.
	noeud->assignerEchelle(scaleFinal);
	noeud->assignerRotationHard(angles);
	noeud->assignerPositionRelative(position);

}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::supprimer()
///  Parcours l'arbre et supprime les objets selectionnes.
/// 
/// @return La valeur du zoom courant
///
///////////////////////////////////////////////////////////////////////////////
bool FacadeModele::supprimer()
{
	VisiteurSuppression* visiteur = new VisiteurSuppression();
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur);
	delete visiteur;

	return true;
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirZoomCourant();
/// Obtient la valeur deu zoom applique
///
/// @return La valeur du zoom courant
///
/// @remark : la comparaison est faite entre les dimensions de la cloture et celles de la fenetre courante
///
///////////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirZoomCourant()
{
	double zoom = -1;
	glm::ivec2 dimClot = vue_->obtenirProjection().obtenirDimensionCloture();
	glm::ivec2 dimFenV = vue_->obtenirProjection().obtenirDimensionFenetreVirtuelle();
	double surfaceFen = dimFenV.x * dimFenV.y;
	if (surfaceFen != 0.0)
		zoom = (dimClot.x * dimClot.y) / surfaceFen;
	return zoom;
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirTailleFenetre();
/// Obtient la taille de la fenetre courante
///
/// @return un vecteur de 2 int qui sont la taille de la fenetre courante
///
///////////////////////////////////////////////////////////////////////////////
glm::ivec2 FacadeModele::obtenirTailleFenetre()
{
	return vue_->obtenirProjection().obtenirDimensionCloture();
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirCentreMasseX()
///  Obtient le x du centre de masse des objets selectionnes
/// 
/// @return La composante en x du centre de masse
///
/// @remark Perte de precision lors de la convertion du centre de masse (double) en int.
///
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirCentreMasseX()
{
	int centreMasseX = 0;
	VisiteurCentreDeMasse* visiteur = new VisiteurCentreDeMasse();
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur);
	centreMasseX = (int) visiteur->obtenirCentreDeMasse().x;
	return centreMasseX;
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirCentreMasseY()
///  Obtient le y du centre de masse des objets selectionnes
/// 
/// @return La composante en y du centre de masse
///
/// @remark Perte de precision lors de la convertion du centre de masse (double) en int.
///
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirCentreMasseY()
{
	int centreMasseY = 0;
	VisiteurCentreDeMasse* visiteur = new VisiteurCentreDeMasse();
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur);
	centreMasseY = (int) visiteur->obtenirCentreDeMasse().y;
	return centreMasseY;
}

///////////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::appliquerZoomInitial()
/// 
/// @return Le y du centre de masse
///
///////////////////////////////////////////////////////////////////////////////
bool FacadeModele::appliquerZoomInitial()
{
	bool applique = false;
	if (obtenirInstance() != nullptr)
	{
		vue_->zoomerInElastique(glm::dvec2(coinGaucheTableX, coinGaucheTableY), glm::ivec2(coinDroitTableX, coinDroitTableY));
		applique = true;
	}
	return applique;
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::duplicationEstHorsTable()
/// 
/// @return true si la duplication est hors table
///
///////////////////////////////////////////////////////////////////////////////
bool FacadeModele::duplicationEstHorsTable()
{
	return duplicationHorsTable_;
}


void FacadeModele::sauvegarderConfig(int config[12])
{
	configuration_->modifierConfiguration(config);
	configuration_->sauvegarderConfiguration();
}


int* FacadeModele::obtenirConfiguration()
{
	return configuration_->obtenirConfiguration();
}

int	 FacadeModele::obtenirTouchePGJ1(){ return configuration_->obtenirRaccourciPGJ1(); }
int  FacadeModele::obtenirTouchePGJ2(){ return configuration_->obtenirRaccourciPGJ2(); }
int  FacadeModele::obtenirTouchePDJ1(){ return configuration_->obtenirRaccourciPDJ1(); }
int  FacadeModele::obtenirTouchePDJ2(){ return configuration_->obtenirRaccourciPDJ2(); }
int  FacadeModele::obtenirToucheRessort(){ return configuration_->obtenirRaccourciRessort(); }


int FacadeModele::obtenirDifficulte(char* nomFichier, int length)
{
	int niveau;
	tinyxml2::XMLDocument* fichierXML = new tinyxml2::XMLDocument();
	fichierXML->LoadFile(nomFichier);

	tinyxml2::XMLElement* elementPropriete = fichierXML->FirstChildElement("Proprietes");
	tinyxml2::XMLElement* element = elementPropriete->LastChildElement("Difficulte");
	niveau = element->FirstAttribute()->IntValue();

	return niveau;
}

void FacadeModele::sauvegarderCampagne(char* nomMap, int length)
{
	configuration_->modifierCampagne(nomMap, length);
	configuration_->sauvegarderCampagne();
}

std::string FacadeModele::obtenirDerniereCampagne()
{
	return configuration_->obtenirCampagne();
}

void FacadeModele::construireListesPalettes()
{
	VisiteurConstruireListes visCL(&listePalettesGJ1_, &listePalettesDJ1_, &listePalettesGJ2_, &listePalettesDJ2_);
	arbre_->accepterVisiteur(&visCL);


}

void FacadeModele::activerPalettesGJ1()//Appel�e quand on pese la touche
{
	construireListesPalettes(); // Normalement, on n'appellerait pas cette m�thode � chaque fois, elle devrait �tre appel�e une fois lorsqu'on a load� la map.
	for (NoeudPaletteG* palette : listePalettesGJ1_)
		palette->activer();
}

void FacadeModele::desactiverPalettesGJ1() // Appelee quand on lache la touche
{
	construireListesPalettes(); // Normalement, on n'appellerait pas cette m�thode � chaque fois, elle devrait �tre appel�e une fois lorsqu'on a load� la map.
	for (NoeudPaletteG* palette : listePalettesGJ1_)
		palette->desactiver();

}

void FacadeModele::supprimerBille()
{
	arbre_->effacer(arbre_->chercher(ArbreRenduINF2990::NOM_BILLE));
}