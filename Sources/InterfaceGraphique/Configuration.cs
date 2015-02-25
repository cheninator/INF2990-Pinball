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
        string maTouche;
        bool mediaPlaying = false;
        System.Media.SoundPlayer p = new System.Media.SoundPlayer(Properties.Resources.touche_invalide);
        public Configuration()
        {
            InitializeComponent();
            comboBoxBilles.Text = "3";
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
                p.Stop(); 
                mediaPlaying = false;
                return true;
            }
            else
            {
                label_Rebind.Text = "Touche invalide";
                Console.WriteLine("Touche invalide");
                if (!mediaPlaying)
                {
                    p.Stream = Properties.Resources.touche_invalide;
                    p.PlayLooping();
                    mediaPlaying = true;
                }
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
            currentValues[0] = 65;
            PDJ1_bouton.Text = defaultValues[1].ToString();
            currentValues[1] = 83;
            PGJ2_bouton.Text = defaultValues[2].ToString();
            currentValues[2] = 52;
            PDJ2_bouton.Text = defaultValues[3].ToString();
            currentValues[3] = 53;
            Ressort_bouton.Text = "Espace";
            currentValues[4] = 32;
        }

        private void LabelChange(string message)
        {
            label_Rebind.Text = "Appuyez sur une touche pour changer la touche de " + message;

        }

       

        private void PGJ1_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            
           // Console.WriteLine("KeyCode :" + e.KeyCode);
           // Console.WriteLine("KeyData : " + e.KeyData);
           // Console.WriteLine("KeyValue : " + e.KeyValue);
            
            int touche = e.KeyValue;
            if( this.isValid(touche) == true)
            {
                currentValues[0] = touche;
                maTouche = char.ConvertFromUtf32(touche);
                if (maTouche == " ")
                    maTouche = "Espace";
                PGJ1_bouton.Text = maTouche;
            }
                   

        }

        private void PDJ1_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            int touche = e.KeyValue;
            if (this.isValid(touche) == true)
            {
                currentValues[1] = touche;
                maTouche = char.ConvertFromUtf32(touche);
                if (maTouche == " ")
                    maTouche = "Espace";
                PDJ1_bouton.Text = maTouche;
            }
        }

        private void PGJ2_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            int touche = e.KeyValue;
            if (this.isValid(touche) == true)
            {
                maTouche = char.ConvertFromUtf32(touche);
                if (maTouche == " ")
                    maTouche = "Espace";
                PGJ2_bouton.Text = maTouche;
            }
        }

        private void PDJ2_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            int touche = e.KeyValue;
            if (this.isValid(touche) == true)
            {
                currentValues[3] = touche;
                maTouche = char.ConvertFromUtf32(touche);
                if (maTouche == " ")
                    maTouche = "Espace";
                PDJ2_bouton.Text = maTouche;
            }
        }

        private void Ressort_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            int touche = e.KeyValue;
            if (this.isValid(touche) == true)
            {
                currentValues[4] = touche;
                maTouche = char.ConvertFromUtf32(touche);
                if (maTouche == " ")
                    maTouche = "Espace";
                Ressort_bouton.Text = maTouche;
            }
        }

        private void PGJ1_bouton_Click(object sender, EventArgs e)
        {
           // PGJ1_bouton.ForeColor = Color.Red;
            LabelChange("palette gauche de Joueur 1");
        }

        private void PDJ1_bouton_Click(object sender, EventArgs e)
        {
           // PDJ1_bouton.ForeColor = Color.Red;
            LabelChange("palette droite de Joueur 1");
        }

        private void PGJ2_bouton_Click(object sender, EventArgs e)
        {
            //PGJ2_bouton.ForeColor = Color.Red;
            LabelChange("palette gauche de Joueur 2");
        }

        private void PDJ2_bouton_Click(object sender, EventArgs e)
        {
            //PDJ2_bouton.ForeColor = Color.Red;
            LabelChange("palette droite de Joueur 2");
        }

        private void Ressort_bouton_Click(object sender, EventArgs e)
        {
            //Ressort_bouton.ForeColor = Color.Red;
            LabelChange("Ressorts");
        }

        private void OK_bouton_Click(object sender, EventArgs e)
        {
           // Console.WriteLine(MDB_OK.Checked);
        }

        
    }
}
