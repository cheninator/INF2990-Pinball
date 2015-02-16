﻿//////////////////////////////////////////////////////////////////////////////
/// @file Etat.cs
/// @author Ballers
/// @date 2015-17-02
/// @version 1.0 
///
/// @ingroup Etat
//////////////////////////////////////////////////////////////////////////////

/** @defgroup Etat Etat
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
    /// @class Etat
    /// @brief Etat abstrait du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Etat
    ///////////////////////////////////////////////////////////////////////////
    abstract class Etat
    {
        protected Exemple form_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Etat(Exemple form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public Etat(Exemple form) { 
            form_ = form;
            form_.Cursor = Cursors.Arrow;
            form_.enableZoom(false);
            
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
        public virtual bool traiterClavier(KeyEventArgs e)
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
        public virtual bool traiterSouris(MouseEventArgs e)
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
        public virtual bool traiterRoulette(MouseEventArgs e)
        {
            return true;
        }
        
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatDeplacement
    /// @brief Etat Deplacement du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Etat
    ///////////////////////////////////////////////////////////////////////////
    class EtatDeplacement : Etat
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatDeplacement(Exemple form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatDeplacement(Exemple form) : base(form) {
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
            if(e.Button == MouseButtons.Left)
                form_.deplacementSouris(e);
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
           
        }

    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatPortail
    /// @brief Etat Portail du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Etat
    ///////////////////////////////////////////////////////////////////////////
    class EtatPortail : Etat
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatPortail(Exemple form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatPortail(Exemple form) : base(form) { }

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
    /// @class EtatMur
    /// @brief Etat Mur du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Etat
    ///////////////////////////////////////////////////////////////////////////
    class EtatMur : Etat
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatMur(Exemple form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatMur(Exemple form) : base(form) { }

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
    /// @class EtatSelection
    /// @brief Etat Selection du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Etat
    ///////////////////////////////////////////////////////////////////////////
    class EtatSelection : Etat 
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatSelection(Exemple form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatSelection(Exemple form) : base(form) {
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
    /// @class EtatRotation
    /// @brief Etat Rotation du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Etat
    ///////////////////////////////////////////////////////////////////////////
    class EtatRotation : Etat
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatRotation(Exemple form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatRotation(Exemple form) : base(form) {
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
    /// @class EtatScale
    /// @brief Etat Scale du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Etat
    ///////////////////////////////////////////////////////////////////////////
    class EtatScale : Etat
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatScale(Exemple form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatScale(Exemple form) : base(form) {
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
    /// @class EtatCreation
    /// @brief Etat Creation du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Etat
    ///////////////////////////////////////////////////////////////////////////
    class EtatCreation : Etat
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatCreation(Exemple form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatCreation(Exemple form) : base(form) {
            form_.deselection();
            form_.outilCourant("Creation");
            form_.trackCursor(true);
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
                form_.creationObjet(e);
                if (Exemple.myObjectName.ToString() == "portail")
                {
                    form_.creationObjet(e, true);
                    form_.statePortail();
                }
                else if (Exemple.myObjectName.ToString() == "mur")
                {
                    form_.stateMur();
                }
            }
            else if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
           
           // form_.creationObjet(e);
            return true;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatZoom
    /// @brief Etat Zoom du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Etat
    ///////////////////////////////////////////////////////////////////////////
    class EtatZoom : Etat
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatZoom(Exemple form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatZoom(Exemple form) : base(form) {
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
    /// @class EtatDuplication
    /// @brief Etat Duplication du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Etat
    ///////////////////////////////////////////////////////////////////////////
    class EtatDuplication : Etat
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatDuplication(Exemple form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatDuplication(Exemple form) : base(form) {
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
    /// @class EtatNone
    /// @brief Etat Nul du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Etat
    ///////////////////////////////////////////////////////////////////////////
    class EtatNone : Etat
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatNone(Exemple form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatNone(Exemple form) : base(form) 
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
    /// @class EtatSelectionMultiple
    /// @brief Etat Selection multiple du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Etat
    ///////////////////////////////////////////////////////////////////////////
    class EtatSelectionMultiple : Etat
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatSelectionMultiple(Exemple form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatSelectionMultiple(Exemple form) : base(form) {
        
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
    /// @class EtatZoomElastique
    /// @brief Etat Zoom Elastique du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Etat
    ///////////////////////////////////////////////////////////////////////////
    class EtatZoomElastique : Etat
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatZoomElastique(Exemple form) : base(form)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] form : Form associee a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatZoomElastique(Exemple form) : base(form)
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
}

