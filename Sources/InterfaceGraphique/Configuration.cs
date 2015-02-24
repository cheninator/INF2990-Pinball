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
    public partial class Configuration : Form
    {
        char[] defaultValues = { 'A', 'S', '4', '5' };
        int[] currentValues = {65,83,52,53,32,49,50,74,75,76,66 };
        public Configuration()
        {
            InitializeComponent();
            KeyPreview = true;
            // TO DO : LIRE UN XML ET PRENDRE LES VALEURS

        }
        private bool isValid(int touche)
        {
            if( (touche >= 65 && touche <= 90) || (touche >= 48 && touche <= 57) || (touche == 32) )
            {
                foreach (int x in currentValues)
                {
                    if (x.Equals(touche))
                    {
                        label_Rebind.Text = "Touche deja utilisée";
                        Console.WriteLine("Touche deja utilise");

                        return false;
                    }
                }
                return true;
            }
            else
            {
                label_Rebind.Text = "Touche invalide";
                Console.WriteLine("Touche invalide");

                return false;
            }

        }
        private void Annuler_bouton_Click(object sender, EventArgs e)
        {
            this.Close();
        }


        private void Default_bouton_Click(object sender, EventArgs e)
        {
            PGJ1_bouton.Text = defaultValues[0].ToString();
            PDJ1_bouton.Text = defaultValues[1].ToString();
            PGJ2_bouton.Text = defaultValues[2].ToString();
            PDJ2_bouton.Text = defaultValues[3].ToString();
            Ressort_bouton.Text = "Espace";
        }

        private void LabelChange(string message)
        {
            label_Rebind.Text = "Appuyez sur une touche pour changer la touche de " + message;

        }

        private void PGJ1_bouton_Click(object sender, EventArgs e)
        {
            PGJ1_bouton.ForeColor = Color.Red;
            LabelChange("palette gauche de Joueur 1");
        }

        private void PGJ1_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            
            Console.WriteLine("KeyCode :" + e.KeyCode);
            Console.WriteLine("KeyData : " + e.KeyData);
            Console.WriteLine("KeyValue : " + e.KeyValue);
            // if (e.KeyCode == Keys.Escape) { label_Rebind.Text = ""; } 
            
            int touche = e.KeyValue;
            if( this.isValid(touche) == true)
            {
                currentValues[0] = touche;
                PGJ1_bouton.Text = e.KeyCode.ToString();
            }
            else
            {
            }
           

        }

        
    }
}
