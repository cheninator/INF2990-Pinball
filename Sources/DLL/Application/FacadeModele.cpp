///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @ingroup Application
///////////////////////////////////////////////////////////////////////////////

// Commentaire Doxygen mis sur la première page de la documentation Doxygen.
/**

@mainpage Projet intégrateur de deuxième année -- INF2990

PAINBALL
<BR>
<BR>
Auteurs:<BR>
Aymen Dje <BR>
Nikolay Radoev <BR>
Yonni Chen <BR>
Emilio Rivera <BR>
Philippe Carpin <BR>
Kim Piché <BR>
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

#include "VueOrtho.h"
#include "Camera.h"
#include "Projection.h"

#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"

#include "CompteurAffichage.h"

// Remplacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, été 2011
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
/// classe.  Si cette instance n'a pas été créée, elle la crée.  Cette
/// création n'est toutefois pas nécessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa création.
///
/// @return Un pointeur vers l'instance unique de cette classe.
///
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
	if (instance_ == nullptr)
		instance_ = new FacadeModele;

	return instance_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererInstance()
///
/// Cette fonction libère l'instance unique de cette classe.
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
/// Ce destructeur libère les objets du modèle.
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
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle crée
/// un contexte OpenGL sur la fenêtre passée en paramètre, initialise
/// FreeImage (utilisée par le chargeur de modèles) et assigne des 
/// paramètres du contexte OpenGL.
///
/// @param[in] hWnd : La poignée ("handle") vers la fenêtre à utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu être créé.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// FreeImage, utilisée par le chargeur, doit être initialisée
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.7843f, 0.7843f, 0.7843f, 0.0f);

	// Initialiser le stencil a 0.
	glClearStencil(0);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP,GL_KEEP,  GL_REPLACE);

	// Les lumières
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);

	// Qualité
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// Le cull face
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	// Création de l'arbre de rendu.  À moins d'être complètement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de créer
	// l'arbre après avoir créé le contexte OpenGL.
	arbre_ = new ArbreRenduINF2990;
	arbre_->initialiser();

	// On crée une vue par défaut.
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

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction libère le contexte OpenGL et désinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu être détruit.");

	FreeImage_DeInitialise();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la scène.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher() const
{
	// Efface l'ancien rendu
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Ne devrait pas être nécessaire
	vue_->appliquerProjection();

	// Positionne la caméra
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	vue_->appliquerCamera();

	// Afficher la scène
	afficherBase();

	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

	// Échange les tampons pour que le résultat du rendu soit visible.
	::SwapBuffers(hDC_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la scène, c'est-à-dire
/// qu'elle met en place l'éclairage et affiche les objets.
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	// Positionner la lumière.
	glm::vec4 position{ 0, 0, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(position));

	// Afficher la scène.
	arbre_->afficher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction réinitialise la scène à un état "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// Réinitialisation de la scène.
	arbre_->initialiser();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// Cette fonction effectue les différents calculs d'animations
/// nécessaires pour le mode jeu, tel que les différents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	// Mise à jour des objets.
	arbre_->animer(temps);

	// Mise à jour de la vue.
	vue_->animer(temps);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::selectionnerObjetSousPointClique(int i, int j, int hauteur, int largeur, bool ctrlDown)
///
/// Cette fonction permet de selectionner un objet. La méthode regarde la valeur
/// du stencil et la donne à un visiteurSelection qui compare cette valeur
/// aux numéros des noeuds et change les met sélectionnés ou pas selon le résultat
/// de la comparaison et selon qu'on a cliqué avec CTRL.
///
/// @param[in] i : Position souris i
/// @param[in] j : Position souris j
///
/// @return NoeudAbstrait.
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::selectionnerObjetSousPointClique(int i, int j, int hauteur, int largeur, bool ctrlDown)
{
	glm::dvec3 pointDansLeMonde;
	vue_->convertirClotureAVirtuelle(i, j, pointDansLeMonde);
	// std::cout << "Position du click dans l'ecran : (" << i << ", " << j << ")" << std::endl;
	// std::cout << "Position du click dans le monde : (" << pointDansLeMonde.x << ", " << pointDansLeMonde.y << ", 0)" << std::endl;

	int valeurStencil = 0;
	glReadPixels(i ,hauteur -j , 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &valeurStencil);

	// std::cout << "Valeur du stencil:" << valeurStencil << std::endl;

	
	if (!ctrlDown)
	{
		// std::cout << "FacadeModele::selectionnerObjetSousPointClique( ) avec ctrlDown = FALSE" << std::endl;
		VisiteurSelection visSel(pointDansLeMonde, valeurStencil);
		arbre_->accepterVisiteur(&visSel);
		// Demander au visiteur ce qu'il a trouvé et faire quelque chose en conséquence
		// std::cout << "Nombre d'objets selectionnes: " << visSel.obtenirNbObjetsSelectionne() << std::endl;

		return visSel.obtenirNbObjetsSelectionne();
	}
	else
	{
		// std::cout << "FacadeModele::selectionnerObjetSousPointClique() avec ctrlDown = TRUE" << std::endl;
		VisiteurSelectionInverse visSelInverse(pointDansLeMonde, valeurStencil);
		arbre_->accepterVisiteur(&visSelInverse);
		// Demander au visiteur ce qu'il a trouvé et faire quelque chose en conséquence
		// std::cout << "Nombre d'objets selectionnes: " << visSelInverse.obtenirNbObjetsSelectionne() << std::endl;

		return visSelInverse.obtenirNbObjetsSelectionne();
	}

}

///////////////////////////////////////////////////////////////////////////////
///
/// @fn void deplacerSelection(int x1, int y1, int x2, int y2)
///		deplace les noeuds selectionnes d'un déplacement calculé en coordonnées du monde
///		à partir des points initiaux et terminaux dans les coordonnées d'affichage OpenGL
///
///
/// @param[in]  x1 : abcisse du point initial
/// @param[in]  y1 : ordonnee du point initial
///
/// @param[in]  x2 : abcisse du point initial
/// @param[in]  y2 : ordonnee du point initial
///
/// @return Aucune.
///
/// @remark : On doit donner des x,y qui ont été transformés par panel_GL.PointToClient(...)
///
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerSelection(int x1, int y1 ,int x2, int y2)
{
	glm::dvec3 positionInitiale, positionFinale;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x1, y1, positionInitiale);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x2, y2, positionFinale);

	glm::dvec3 deplacement{ positionFinale - positionInitiale };

	// Visiter l'arbre pour trouver les limites d'une boite
	// minX, minY, maxX, maxY
	VisiteurLimitesSelection VisLimSel;
	arbre_->accepterVisiteur(&VisLimSel);

	// Comparer le Deplacement et minX,maxX... aux limites de la table.

	// LOGIQUE DE DÉPLACEMENT
	glm::dvec3 pointMax{ VisLimSel.getXMax(), VisLimSel.getYMax(), 0 };
	glm::dvec3 pointMin{ VisLimSel.getXMin(), VisLimSel.getYMin(), 0 };
	if (estDansTable(pointMax + deplacement) && estDansTable(pointMin + deplacement))
	{
		VisiteurDeplacement visDep(deplacement);
		arbre_->accepterVisiteur(&visDep);
	}
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn void tournerSelectionSouris(int x1, int y1, int x2, int y2)
///		Fait une rotation des objets sélectionnés autour de leur centre de masse.
///		L'angle est calculé en fonction du déplacement de (x1,y1) à (x2,y2):
///		Présentement, l'angle est proportionnel à (y1 - y2).
///		
///		Pour tester si la rotation est faisable, on prend tous les points des boîtes
///		englobantes.  Si un seul de ces points, une fois transformé, n'est pas dans la 
///		table, on ne fait pas la rotation.
///		
///		
/// @param[in]  x1 : abcisse du point initial
/// @param[in]  y1 : ordonnee du point initial
///
/// @param[in]  x2 : abcisse du point initial
/// @param[in]  y2 : ordonnee du point initial
///
/// @return Aucune.
///
/// @remark : On doit donner des x,y qui ont été transformés par panel_GL.PointToClient(...)
///
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::tournerSelectionSouris(int x1, int y1, int x2, int y2)
{
	// Visiter l'arbre pour trouver le centre de masse des noeuds selectionnés
	VisiteurCentreDeMasse visCM;
	arbre_->accepterVisiteur(&visCM);
	glm::dvec3 centreRotation = visCM.obtenirCentreDeMasse();

	// On calcule l'angle de la rotation:
	double angle = (y2 - y1) / 3.0;
	double angleEnRadian = angle * 2 * 3.1415926535897932384626433832795 / 360;
	glm::dmat3 transform = glm::dmat3{ glm::dvec3{ cos(-angleEnRadian), -sin(-angleEnRadian), 0 },
		glm::dvec3{ sin(-angleEnRadian), cos(-angleEnRadian), 0 },
		glm::dvec3{ 0, 0, 1 } };

	// On décide si la rotation peut se faire
	bool onTourne = true;
	// Obtenir une liste des points englobants des noeud sélectionnés
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
/// @fn void agrandirSelection(int x1, int y1, int x2, int y2)
///		Fait un agrandissement des objets sélectionnés.
///		L'agrandissement est calculé en fonction du déplacement de (x1,y1) à (x2,y2)
///
/// @param[in]  x1 : abcisse du point initial
/// @param[in]  y1 : ordonnee du point initial
///
/// @param[in]  x2 : abcisse du point initial
/// @param[in]  y2 : ordonnee du point initial
///
/// @return Aucune.
///
/// @remark : On doit donner des x,y qui ont été transformés par panel_GL.PointToClient(...)
///
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::agrandirSelection(int x1, int y1, int x2, int y2)
{
	double scale = glm::exp((y1 - y2) * glm::log(1.003)); // exp(b log(a)) = a^b
	// Pour agrandir on multiplie le scale courrant par 1.003 et ce une fois pour chaque déplacement en y
	// donc on multiplie par 1.003^(y1-y2).
	// Si (y1-y2) est négatif, ceci va nous faire diviser par 1.003, donc l'objet va rapetisser.
	
	// Au final, on multiplie le scale courrant par 1.003 une fois pour chaque déplacement élémentaire vers le haut,
	// On divise par 1.003 pour chaque déplacement élémentaire vers le bas.

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

}

///////////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserRectangleElastique(int i, int j) A COMMENTER KIM
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
/// @fn bool verifierCliqueDansTable(int x, int y)
///		Vérifie si le point du monde correspondant à (x,y) est dans la table de
///		façon empirique ou heuristique.
///
/// @param[in]  x : abcisse du point cliqué
/// @param[in]  y : ordonnee du point cliqué
///
/// @return Aucune.
///
/// @remark : On doit donner des x,y qui ont été transformés par panel_GL.PointToClient(...)
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
///		Vérifie si le point du monde est dans la table
///
/// @param[in]  pointDuMonde : Point dont on veut vérifier qu'il est dans la table
///
/// @return Aucune.
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
/// @fn void dupliquerSelection(int i, int j)
///		Duplique les objets selectionnés
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::dupliquerSelection(int i, int j)
{
	// Visiter l'arbre et faire la duplication.
	VisiteurDuplication* visiteur = new VisiteurDuplication();
	arbre_->accepterVisiteur(visiteur);
	delete visiteur;
}


///////////////////////////////////////////////////////////////////////////////
///
/// @fn void creerXML(char* path, int prop[6])
///		Enregistre une zone de jeu en fichier XML
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

	// Ne pas permettre de sauvegarder la zone de jeu par défaut
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
///		Positionne un mur pour qu'il soit une ligne entre où on a appuyé le bouton de gauche de la 
///		souris et la position actuelle de la souris.
///		La méthode vérifie aussi la boite englobante du mur pour ne pas qu'il dépasse de la table.
///	
/// @param[in]  originX : Position en X où le bouton a été appuyé
/// @param[in]  originX : Position en Y où le bouton a été appuyé
/// @param[in]  x1 : Position en X précédant un déplacement de la souris
/// @param[in]  Y1 : Position en Y précédant un déplacement de la souris
/// @param[in]  x2 : Position en X après un déplacement de la souris (position actuelle de la souris)
/// @param[in]  y2 : Position en X après un déplacement de la souris (position actuelle de la souris)
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::positionnerMur(int originX, int originY,int x1, int y1, int x2, int y2, NoeudAbstrait* noeud)
{
	glm::dvec3 positionOriginale,positionInitiale, positionFinale;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(originX, originY, positionOriginale);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x2, y2, positionFinale);

	glm::dvec3 vecteur = positionFinale - positionOriginale;

	// Propriétés à appliquer:
	glm::dvec3 scaleFinal{ 1, 1, 1 };
	glm::dvec3 angles{ 0, 0, 0 };
	glm::dvec3 position = positionOriginale;

	double angleRadian;

	// Les calculs sont fait seulement si la souris est assez loin de ou on a créé le noeud.
	if (glm::length(vecteur) > 0.1)
	{
		// CALCUL DE L'ANGLE
		// =================
		glm::dvec3 axe{ 0, 1, 0 }; // On va travailler avec l'angle entre le vecteur allant de origin à la position du curseur, et l'axe Y.
		glm::dvec3 produitVectoriel = glm::cross(axe, vecteur);
		double sinAngle = glm::length(produitVectoriel) / glm::length(axe) / glm::length(vecteur);
		angleRadian = produitVectoriel.z > 0 ? asin(sinAngle) : -asin(sinAngle);

		// Prendre l'angle complémentaire si on est en dessous de l'axe X.
		if (vecteur.y < 0)
			angleRadian = M_PI - angleRadian;// A passer en paramètre à assignerRotation

		angles = glm::dvec3{ 0, 0, 360.0 / 2.0 / M_PI * angleRadian };
	}
		// Calcul de la translation
		// ========================
		// position = positionOriginale + vecteur / 2.0; // Le centre du mur est à mi-chemin entre origin et le point du curseur. 
	if (glm::length(vecteur) > 16)
		position = positionOriginale + vecteur / 2.0;
	else if (glm::length(vecteur) != 0)
		position = positionOriginale + 8.0 *glm::normalize(vecteur); // 
	else
		position = positionOriginale + glm::dvec3{ 0, 8, 0 };

	
	if (glm::length(vecteur) > 16)
	{
		// Calcul du scale
		// ===============
		double scale = glm::length(vecteur) / 16; //  16.0 est la longueur originale du mur. 
		scaleFinal = glm::dvec3{ 1, scale, 1 };
	}


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

	// Si on s'est rendu ici, c'est qu'on peut faire l'assignation des propriétés.
	noeud->assignerEchelle(scaleFinal);
	noeud->assignerRotationHard(angles);
	noeud->assignerPositionRelative(position);

}

///////////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::supprimer()
///  Parcours l'arbre et supprime les objets sélectionnés.
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
/// @fn double obtenirZoomCourant();
/// Obtient la valeur deu zoom appliqué ; la comparaison est faite entre les dimensions de la clôture et celles de la fenêtre courante
///
/// @return La valeur du zoom courant
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
/// @fn int FacadeModele::obtenirCentreMasseX()
///  Obtient le x du centre de masse des objets sélectionnés
/// 
/// @return Le x du centre de masse
///
/// @remard Perte de précision lors de la convertion du centre de masse (double) en int.
///
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirCentreMasseX(){
	int centreMasseX = 0;
	VisiteurCentreDeMasse* visiteur = new VisiteurCentreDeMasse();
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur);
	centreMasseX = (int) visiteur->obtenirCentreDeMasse().x;
	return centreMasseX;
}

///////////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirCentreMasseY()
///  Obtient le y du centre de masse des objets sélectionnés
/// 
/// @return Le y du centre de masse
///
/// @remard Perte de précision lors de la convertion du centre de masse (double) en int.
///
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirCentreMasseY(){
	int centreMasseY = 0;
	VisiteurCentreDeMasse* visiteur = new VisiteurCentreDeMasse();
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur);
	centreMasseY = (int) visiteur->obtenirCentreDeMasse().y;
	return centreMasseY;
}

///////////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::appliquerZoomInitial()
///  A COMMENTER
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