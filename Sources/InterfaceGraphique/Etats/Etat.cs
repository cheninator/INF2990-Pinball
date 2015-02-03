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
            form_.deplacementSouris(e);

            return true;
        }

    }

    class EtatDeplacementVue : Etat
    {

        public EtatDeplacementVue(Exemple form) : base(form) { }

        public override bool traiterClavier(KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }

        public override bool traiterSouris(MouseEventArgs e)
        {
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
            return base.traiterSouris(e);
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
            return base.traiterSouris(e);
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
            form_.scaleSouris(e);

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
            return base.traiterSouris(e);
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

            return base.traiterSouris(e);
        }

        public override bool traiterRoulette(MouseEventArgs e)
        {
            form_.zoomRoulette(e);
            
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
            return base.traiterSouris(e);
        }
    }

}
