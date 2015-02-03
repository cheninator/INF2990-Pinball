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
        public List<int> mesProp;
        string errorMessage = "";
        public Proprietes(List<int> a)
        {
            InitializeComponent();
            mesProp = a;
            ptsButCirc_Box.Text = mesProp[0].ToString();
            ptsButTri_Box.Text = mesProp[1].ToString();
            ptsCible_Box.Text = mesProp[2].ToString();
            ptsVictoire_Box.Text = mesProp[3].ToString();
            ptsFreeBall_Box.Text = mesProp[4].ToString();
            difficulte_ComboBox.Text = mesProp[5].ToString();
            
        }
        private bool checkValue()
        {
            int n;
            bool isValid = true;
            DataTable dt = new DataTable();
            //try { ptsButCirc_Box.Text = dt.Compute(ptsButCirc_Box.Text, "").ToString(); }
            //catch { Console.WriteLine("false");; }
            if( !(int.TryParse(ptsButCirc_Box.Text, out n))){
                isValid = false;
                errorMessage += "\n La valeur de butoir circulaire est invalide";
            }
            if (!(int.TryParse(ptsButTri_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\n La valeur de butoir triangulaire est invalide";
            }
            if (!(int.TryParse(ptsCible_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\n La valeur de la cible est invalide";
            }
            if (!(int.TryParse(ptsVictoire_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\n La valeur de la victoire est invalide";
            }
            if (!(int.TryParse(ptsFreeBall_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\n La valeur de la balle gratuite est invalide";
            }
            if (!(int.TryParse(difficulte_ComboBox.Text, out n)))
            {
                isValid = false;
                errorMessage += "\n La valeur de la difficulte est invalide";
            }

            return isValid;
        }
        private void propAnnuler_Bouton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void propConfirm_Bouton_Click(object sender, EventArgs e)
        {

            if (checkValue())
            {
                
                
                mesProp.Add(Convert.ToInt32(ptsButCirc_Box.Text));
                mesProp.Add(Convert.ToInt32(ptsButTri_Box.Text));
                mesProp.Add(Convert.ToInt32(ptsCible_Box.Text));
                mesProp.Add(Convert.ToInt32(ptsVictoire_Box.Text));
                mesProp.Add(Convert.ToInt32(ptsFreeBall_Box.Text));
                mesProp.Add(Convert.ToInt32(difficulte_ComboBox.Text));
                this.Close();
            }
            else
            {
                MessageBox.Show(errorMessage, "messsage d'erreur",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
           
          // this.Close();
        }

        
    }
}
