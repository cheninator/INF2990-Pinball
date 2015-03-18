using System.Windows.Forms;
namespace InterfaceGraphique
{
    public abstract class EtatAbstrait
    {
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
