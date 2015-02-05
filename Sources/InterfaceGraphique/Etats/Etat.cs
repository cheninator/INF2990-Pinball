using System;
using System.Drawing;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    abstract class Etat
    {
        protected Exemple form_;

        public Etat(Exemple form) { form_ = form;}

        public virtual bool traiterClavier(KeyEventArgs e) 
        {  
            return true;
        }

        public virtual bool traiterSouris(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
        }

        public virtual bool traiterRoulette(MouseEventArgs e)
        {
            return true;
        }
        
    }

    class EtatDeplacement : Etat
    {
        public EtatDeplacement(Exemple form) : base(form) { }

        public override bool traiterClavier(KeyEventArgs e)
        {

            // Traiter le déplacement par clavier
            return base.traiterClavier(e);
        }

        public override bool traiterSouris(MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Left)
                form_.deplacementSouris(e);
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
           
        }

    }

 

    class EtatSelection : Etat 
    {
        public EtatSelection(Exemple form) : base(form) { }

        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);

        }

        public override bool traiterSouris(MouseEventArgs e)
        {
            if(e.Button== MouseButtons.Left)
                form_.selection(e);
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
           
        }
    }

    class EtatRotation : Etat
    {

        public EtatRotation(Exemple form) : base(form) { }

        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        public override bool traiterSouris(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            if (e.Button == MouseButtons.Left)
                form_.tournerSelectionSouris(e);
            return true;
        }
    }

    class EtatScale : Etat
    {

        public EtatScale(Exemple form) : base(form) { }

        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        public override bool traiterSouris(MouseEventArgs e)
        {
           if(e.Button == MouseButtons.Left)
                form_.scaleSouris(e);
           if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
            
        }
    }

    class EtatCreation : Etat
    {

        public EtatCreation(Exemple form) : base(form) { }

        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        public override bool traiterSouris(MouseEventArgs e)
        {

            if (e.Button == MouseButtons.Left)
                form_.creationObjet(e);
            else if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
           
           // form_.creationObjet(e);
            return true;
        }
    }

    class EtatZoom : Etat
    {

        public EtatZoom(Exemple form) : base(form) { }


        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        public override bool traiterSouris(MouseEventArgs e)
        {

            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
        }

        public override bool traiterRoulette(MouseEventArgs e)
        {
            form_.zoomRoulette(e);
            
            return true;
        }
    }

    class EtatDuplication : Etat
    {
        public EtatDuplication(Exemple form) : base(form) { }

        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        public override bool traiterSouris(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
        }
    }

    class EtatNone : Etat
    {

        public EtatNone(Exemple form) : base(form) { }

        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        public override bool traiterSouris(MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;
        }
    }
    class EtatSelectionMultiple : Etat
    {
        public EtatSelectionMultiple(Exemple form) : base(form) { }

        public override bool traiterClavier(KeyEventArgs e)
        {

            // Traiter le déplacement par clavier
            return base.traiterClavier(e);
        }

        public override bool traiterSouris(MouseEventArgs e)
        {
            
            if (e.Button == MouseButtons.Left)
            {
               
             /*
             * TO DO
             * Vous pouvez faire form_.selectionMultiple(e); ou le nom de la fonction voulue
             * 
             * 
             * 
             */
            }
                
            if (e.Button == MouseButtons.Right)
                form_.deplacementVueSouris(e);
            return true;

          

        }

    }
}

