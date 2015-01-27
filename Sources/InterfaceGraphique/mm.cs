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
    public partial class mm : Form
    {
        public Exemple a;
        public mm()
        {
            InitializeComponent();
        }

        private void mm_Load(object sender, EventArgs e)
        {
          
        }

        private void button1_Click(object sender, EventArgs e)
        {
            a = new Exemple();
            a.ShowDialog();
            
        }
    }
}
