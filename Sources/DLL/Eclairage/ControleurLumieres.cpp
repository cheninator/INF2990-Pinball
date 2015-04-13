///////////////////////////////////////////////////////////////////////////////
/// @file ControleurLumieres.cpp
/// @author The ballers
/// @date 2015-03-20
/// @version 1.0
///
/// @ingroup Eclairage
///////////////////////////////////////////////////////////////////////////////


#include "ControleurLumieres.h"
#include "ControleurNuanceurs.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include <iostream>

#define LUMIERE_OFF 0 /// Sigale une lumiere eteinte au nuanceur
#define LUMIERE_ON 1 /// Sigale une lumiere allumee au nuanceur


////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurLumieres::ControleurLumieres()
/// 
/// @brief Assigne des poignees openGL choisies aux trois lumieres
///
////////////////////////////////////////////////////////////////////////
ControleurLumieres::ControleurLumieres()
{
	lumAmbiante_ = new Lumiere(GL_LIGHT1);
	lumDirectionnelle_ = new Lumiere(GL_LIGHT2);
	lumSpotA_ = new Lumiere(GL_LIGHT3);
	lumSpotB_ = new Lumiere(GL_LIGHT4);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurLumieres::~ControleurLumieres()
///
/// @brief Destructeur, detruit les lumieres.
///
////////////////////////////////////////////////////////////////////////
ControleurLumieres::~ControleurLumieres()
{
	delete lumAmbiante_;
	delete lumDirectionnelle_;
	delete lumSpotA_;
	delete lumSpotB_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::initialiserLumieres() 
/// 
/// @brief Place les lumieres et definit leur proprietes.
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::initialiserLumieres()
{
// Si 1, normal.
// Si 0, les spots suiveurs de bille sont un bleu, un rouge.
#if(1)
	// Initialiser lumAmbiante
	lumAmbiante_->setAmbientColor({ 0.3f, 0.3f, 0.3f, 1.0f });
	lumAmbiante_->setDiffuseColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	lumAmbiante_->setSpecularColor({ 0.0f, 0.0f, 0.0f, 1.0f });

	// Initialiser lumDirectionnelle
	lumDirectionnelle_->setAmbientColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	lumDirectionnelle_->setDiffuseColor({ 0.3f, 0.3f, 0.3f, 1.0f });
	lumDirectionnelle_->setSpecularColor({ 0.6f, 0.6f, 0.7f, 1.0f });

	lumDirectionnelle_->setPosition({ 200.0f, -47.0f, 110.0f, 1.0f });
	lumDirectionnelle_->setDirection({ 0.1f, 0.0f, -1.0f, 1.0f });

	// Inisialiser lumSpot
	lumSpotA_->setAmbientColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	lumSpotA_->setDiffuseColor({ 0.4f, 0.4f, 0.3f, 1.0f });
	lumSpotA_->setSpecularColor({ 0.9f, 0.9f, 0.9f, 1.0f });
	   	   
	lumSpotA_->setPosition({ 50.0f, -47.0f, 200.0f, 1.0f });
	lumSpotA_->setDirection({ 0.0f, 0.0f, -1.0f, 1.0f });

	lumSpotA_->setCutoffAngle(8.0f);
	lumSpotA_->setExponent(0.2f);
		   
	lumSpotA_->setAttenuation({ 1.0f, 1.0f, 0.1f });

	// Inisialiser lumSpot
	lumSpotB_->setAmbientColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	lumSpotB_->setDiffuseColor({ 0.4f, 0.4f, 0.3f, 1.0f });
	lumSpotB_->setSpecularColor({ 0.9f, 0.9f, 0.9f, 1.0f });
		   
	lumSpotB_->setPosition({ -50.0f, -47.0f, 200.0f, 1.0f });
	lumSpotB_->setDirection({ 0.0f, 0.0f, -1.0f, 1.0f }); 

	lumSpotB_->setCutoffAngle(8.0f);
	lumSpotB_->setExponent(0.2f);
		   
	lumSpotB_->setAttenuation({ 1.0f, 1.0f, 0.1f });
#else
	// Initialiser lumAmbiante
	lumAmbiante_->setAmbientColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	lumAmbiante_->setDiffuseColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	lumAmbiante_->setSpecularColor({ 0.0f, 0.0f, 0.0f, 1.0f });

	// Initialiser lumDirectionnelle
	lumDirectionnelle_->setAmbientColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	lumDirectionnelle_->setDiffuseColor({ 0.3f, 0.3f, 0.3f, 1.0f });
	lumDirectionnelle_->setSpecularColor({ 0.6f, 0.6f, 0.7f, 1.0f });

	lumDirectionnelle_->setPosition({ 200.0f, -47.0f, 110.0f, 1.0f });
	lumDirectionnelle_->setDirection({ 0.1f, 0.0f, -1.0f, 1.0f });

	// Inisialiser lumSpot
	lumSpotA_->setAmbientColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	lumSpotA_->setDiffuseColor({ 0.1f, 0.1f, 0.8f, 1.0f });
	lumSpotA_->setSpecularColor({ 0.9f, 0.9f, 0.9f, 1.0f });

	lumSpotA_->setPosition({ 250.0f, -47.0f, 200.0f, 1.0f });
	lumSpotA_->setDirection({ 0.0f, 0.0f, -1.0f, 1.0f });

	lumSpotA_->setCutoffAngle(8.0f);
	lumSpotA_->setExponent(0.2f);

	lumSpotA_->setAttenuation({ 1.0f, 1.0f, 0.1f });

	// Inisialiser lumSpot
	lumSpotB_->setAmbientColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	lumSpotB_->setDiffuseColor({ 0.8f, 0.1f, 0.1f, 1.0f });
	lumSpotB_->setSpecularColor({ 0.9f, 0.9f, 0.9f, 1.0f });

	lumSpotB_->setPosition({ 150.0f, -47.0f, 200.0f, 1.0f });
	lumSpotB_->setDirection({ 0.0f, 0.0f, -1.0f, 1.0f });

	lumSpotB_->setCutoffAngle(8.0f);
	lumSpotB_->setExponent(0.2f);

	lumSpotB_->setAttenuation({ 1.0f, 1.0f, 0.1f });
#endif
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::definirLumieres()
/// 
/// @brief Envoi les donnees des lumieres au serveur openGL
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::definirLumieres()
{
	lumAmbiante_->definir();
	lumDirectionnelle_->definir();
	lumSpotA_->definir();
	lumSpotB_->definir();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::activerAmbiante() 
/// 
/// @brief Active le calcul de lumiere ambiante dans le nuanceur
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::activerAmbiante()
{
	ControleurNuanceurs::obtenirInstance()->assignerEtatAmbiante(LUMIERE_ON);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::desactiverAmbiante() // TODO PHIL
///
/// @brief Desactive le calcul de lumiere ambiante dans le nuanceur
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::desactiverAmbiante()
{
	ControleurNuanceurs::obtenirInstance()->assignerEtatAmbiante(LUMIERE_OFF);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::activerDirectionnelle() 
/// 
/// @brief Active le calcul de lumiere directionnelle dans le nuanceur
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::activerDirectionnelle()
{
	ControleurNuanceurs::obtenirInstance()->assignerEtatDirectionnelle(LUMIERE_ON);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::desactiverDirectionnelle() 
///
/// @brief Desactive le calcul de lumiere directionnelle dans le nuanceur
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::desactiverDirectionnelle()
{
	ControleurNuanceurs::obtenirInstance()->assignerEtatDirectionnelle(LUMIERE_OFF);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::activerSpot() 
///
/// @brief Active le calcul de lumiere spot dans le nuanceur
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::activerSpot()
{
	ControleurNuanceurs::obtenirInstance()->assignerEtatSpot(LUMIERE_ON);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::desactiverSpot()
///
/// @brief Desactive le calcul de lumiere spot dans le nuanceur
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::desactiverSpot()
{
	ControleurNuanceurs::obtenirInstance()->assignerEtatSpot(LUMIERE_OFF);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::trackerLesBilles()
///
/// @brief Pointe deux spotslights sur les billes de la zone de jeu. 
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::trackerLesBilles(NoeudTable* table)
{
	int spotsLeft = 2;

	const unsigned int n = table->obtenirNombreEnfants();
	for (unsigned int i = 0; i < n; i++)
	{
		NoeudAbstrait* noeud = table->chercher(i);
		if (noeud->obtenirType() == "bille")
		{
			glm::fvec3 positionBille{ noeud->obtenirPositionRelative() };
			if (spotsLeft == 2)
			{
				glm::fvec3 direction3D = { positionBille - (glm::fvec3)lumSpotA_->getPosition() };
				lumSpotA_->setDirection(glm::fvec4{ direction3D, 1.0 });
			}

			if (spotsLeft == 1)
			{
				glm::fvec3 direction3D1 = { positionBille - (glm::fvec3)lumSpotB_->getPosition() };
				lumSpotB_->setDirection(glm::fvec4{ direction3D1, 1.0 });
			}

			spotsLeft--;
			if (spotsLeft == 0) return;
		}

		if (spotsLeft == 2)
		{
			lumSpotA_->setDirection({ 0.0, 0.0, 1.0, 1.0 });
			lumSpotB_->setDirection({ 0.0, 0.0, 1.0, 1.0 });
		}
		else if (spotsLeft == 1)
		{
			lumSpotB_->setDirection({ 0.0, 0.0, 1.0, 1.0 });
		}
	}
}
