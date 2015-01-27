using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class Proprietes : Form
    {
        public Proprietes()
        {
            InitializeComponent();
        }

        private void propAnnuler_Bouton_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
