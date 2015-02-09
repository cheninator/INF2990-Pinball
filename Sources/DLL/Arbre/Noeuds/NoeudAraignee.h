///////////////////////////////////////////////////////////////////////////
/// @file NoeudAraignee.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDARAIGNEE_H__
#define __ARBRE_NOEUDS_NOEUDARAIGNEE_H__


#include "NoeudComposite.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudAraignee
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudAraignee : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudAraignee(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudAraignee();

   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );

   bool NoeudAraignee::accepterVisiteur(VisiteurAbstrait* vis);

private:
   /// Angle dans le sinus de l'oscillation
   float angle_{ 0 };

};


#endif // __ARBRE_NOEUDS_NOEUDARAIGNEE_H__