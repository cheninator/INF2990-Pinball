using System;
using System.Drawing;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    /*
    public static class CustomConsoleThread
    {
        static bool alreadyGenerated = false;
        public static void generateForm()
        {
            if (alreadyGenerated == true)
                return;
            EtatAbstrait.cConsole = new CustomConsole();

            alreadyGenerated = true;
        }
        public static void stopForm()
        {
            EtatAbstrait.cConsole.Dispose();
            EtatAbstrait.cConsole.Close();
            alreadyGenerated = false;
        }
        public static void Show()
        {
            EtatAbstrait.cConsole.Show();
        }
        public static void Hide()
        {
            EtatAbstrait.cConsole.Hide();
        }
    }
    */
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
