using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    class EtatJeuAbstrait : EtatAbstrait
    {
        public override bool traiterClavier(System.Windows.Forms.KeyEventArgs e)
        {
            return base.traiterClavier(e);
        }
        public override bool traiterRoulette(System.Windows.Forms.MouseEventArgs e)
        {
            return base.traiterRoulette(e);
        }
        public override bool traiterSouris(System.Windows.Forms.MouseEventArgs e)
        {
            return base.traiterSouris(e);
        }
    }

    class EtatJeuPause : EtatJeuAbstrait
    {
        // On ne override pas les traiterSouris
    }

    class EtatJeuJouer : EtatJeuAbstrait
    {
        
    }

    class EtatJeuDebutDePartie : EtatJeuAbstrait
    {
        
    }

    class EtatJeuFinDePartie : EtatJeuAbstrait
    {

    }

}
