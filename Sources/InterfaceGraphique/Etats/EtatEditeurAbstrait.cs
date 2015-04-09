//////////////////////////////////////////////////////////////////////////////
/// @file EtatEditeurAbstrait.cs
/// @author Ballers
/// @date 2015-17-02
/// @version 1.0 
///
/// @ingroup Etats
//////////////////////////////////////////////////////////////////////////////

/** @defgroup Etats Etats
*	@ingroup InterfaceGraphique
*/

using System;
using System.Drawing;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditeurAbstrait
    /// @brief EtatEditeurAbstrait abstrait du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    abstract class EtatEditeurAbstrait : EtatAbstrait
    {
        protected Editeur form_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurAbstrait(Editeur form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurAbstrait(Editeur form) { 
            form_ = form;
            form_.Cursor = Cursors.Arrow;
            form_.enableZoom(true);
            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public virtual bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {  
            return true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public virtual bool traiterSouris(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public virtual bool traiterRoulette(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterRoulette(MouseEventArgs e)
        {
            return true;
        }
        
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatDeplacement
    /// @brief EtatEditeurAbstrait Deplacement du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditeurDeplacement : EtatEditeurAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurDeplacement(Editeur form) : base(form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurDeplacement(Editeur form) : base(form) {
            form_.outilCourant("Deplacement");
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {

            // Traiter le deplacement par clavire
            return base.traiterClavier(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Left)
                form_.deplacementSouris(e);
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
           
        }

    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditeurPortail
    /// @brief EtatEditeurAbstrait Portail du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditeurPortail : EtatEditeurAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurPortail(Editeur form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurPortail(Editeur form) : base(form) { }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {

            // Traiter le deplacement par clavier
            return base.traiterClavier(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {
            form_.deplacementSouris(e);
           
            return true;

        }

    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditeurMur
    /// @brief EtatEditeurAbstrait Mur du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditeurMur : EtatEditeurAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurMur(Editeur form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurMur(Editeur form) : base(form) { }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {

            // Traiter le deplacement par clavier
            return base.traiterClavier(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {
           if( e.Button != MouseButtons.Right)
                form_.creationMur();
           if (e.Button == MouseButtons.Left)
           {
               form_.trackCursor(false);
               form_.deselection();
           }
          
            return true;

        }

    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditeurSelection
    /// @brief EtatEditeurAbstrait Selection du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditeurSelection : EtatEditeurAbstrait 
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurSelection(Editeur form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurSelection(Editeur form) : base(form) {
            form_.outilCourant("Selection");
            }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {
            if(e.Button== MouseButtons.Left)
                form_.selection(e);
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
           
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditeurRotation
    /// @brief EtatEditeurAbstrait Rotation du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditeurRotation : EtatEditeurAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurRotation(Editeur form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurRotation(Editeur form) : base(form) {
            form_.outilCourant("Rotation");
            }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            else if (e.Button == MouseButtons.Left)
                form_.tournerSelectionSouris(e);
            return true;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditeurScale
    /// @brief EtatEditeurAbstrait Scale du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditeurScale : EtatEditeurAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurScale(Editeur form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurScale(Editeur form) : base(form) {
            form_.Cursor = Cursors.Arrow;
            form_.outilCourant("Mise a Echelle");
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {
           if(e.Button == MouseButtons.Left)
                form_.scaleSouris(e);
           if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
            
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditeurCreation
    /// @brief EtatEditeurAbstrait Creation du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditeurCreation : EtatEditeurAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurCreation(Editeur form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurCreation(Editeur form) : base(form) {
            form_.deselection();
            form_.outilCourant("Creation");
            form_.trackCursor(true);
            form_.creationObjet();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {            
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            else
                form_.deplacementSouris(e);
            
            return true;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditeurZoom
    /// @brief EtatEditeurAbstrait Zoom du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditeurZoom : EtatEditeurAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurZoom(Editeur form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurZoom(Editeur form) : base(form) {
            form_.enableZoom(true);
            form_.outilCourant("Zoom");
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                //form_.zoomElastique();
                //form_.terminerRectangleElastique();
            }
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterRoulette(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterRoulette(MouseEventArgs e)
        {
            form_.zoomRoulette(e);
            
            return true;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditeurDuplication
    /// @brief EtatEditeurAbstrait Duplication du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditeurDuplication : EtatEditeurAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurDuplication(Editeur form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurDuplication(Editeur form) : base(form) {
            form_.outilCourant("Duplication");
            form_.trackCursor(true);
            form_.dupliquerSelection();  
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {            
            form_.deplacementSouris(e);

            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);

            return true;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditeurNone
    /// @brief EtatEditeurAbstrait Nul du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditeurNone : EtatEditeurAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurNone(Editeur form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurNone(Editeur form) : base(form) 
        {
            form_.outilCourant("");
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditeurSelectionMultiple
    /// @brief EtatEditeurAbstrait Selection multiple du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditeurSelectionMultiple : EtatEditeurAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurSelectionMultiple(Editeur form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurSelectionMultiple(Editeur form) : base(form) {
        
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                form_.terminerRectangleElastique();
                form_.selectionMultiple();
            }
                

            return true;
        }
    }
    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditeurZoomElastique
    /// @brief EtatEditeurAbstrait Zoom Elastique du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditeurZoomElastique : EtatEditeurAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurZoomElastique(Editeur form) : base(form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurZoomElastique(Editeur form) : base(form)
        {
 
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                form_.terminerRectangleElastique();
                form_.zoomElastique();
            }
            return true;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditeurZoomElastique
    /// @brief EtatEditeurAbstrait Test du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-02-25
    /// 
    /// @ingroup EtatEditeurAbstrait
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditeurTest : EtatEditeurAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurTest(Editeur form) : base(form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurTest(Editeur form): base(form)
        {

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
        }
    }

    class EtatEditeurPause : EtatEditeurAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatEditeurPause(Editeur form) : base(form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatEditeurPause(Editeur form): base(form)
        {
            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterClavier(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement du clavier qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterSouris(MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier
        /// 
        /// param[in] e : evenement de la souris qui lance la fonction
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterSouris(MouseEventArgs e)
        {
            return base.traiterSouris(e);
        }
    }
}

