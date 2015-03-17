using System;
using System.Drawing;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace InterfaceGraphique
{
    public abstract class EtatAbstrait
    {
        public static CustomConsole cConsole = new CustomConsole(); 
        public virtual bool traiterClavier(KeyEventArgs e)
        {
            return false;
        }
        public virtual bool traiterSouris(MouseEventArgs e)
        {
            return false;
        }
        public virtual bool traiterRoulette(MouseEventArgs e)
        {
            return false;
        }
    }
}
