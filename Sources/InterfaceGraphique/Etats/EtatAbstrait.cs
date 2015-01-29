using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    abstract class EtatAbstrait
    {
        public EtatAbstrait() { }
        ~EtatAbstrait() { }

        virtual public bool traiterSelection() { return false; }
        virtual public bool traiterCreation() { return false; }
        virtual public bool traiterDeplacement() { return false; }
        virtual public bool traiterRotation() { return false; }
        virtual public bool traiterEchelle() { return false; }
    }

    class EtatDeplacement : EtatAbstrait
    {
        public EtatDeplacement() { }
        ~EtatDeplacement() { }

        virtual public bool traiterSelection() { return false; }
        virtual public bool traiterCreation() { return false; }

        virtual public bool traiterDeplacement() 
        {

            // Appeler les bonnes méthodes du noyau
            return true;
        }

        virtual public bool traiterRotation() { return false; }
        virtual public bool traiterEchelle() { return false; }

    }




}
