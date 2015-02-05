﻿using System;
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
          
            if( !(int.TryParse(ptsButCirc_Box.Text, out n))){
                isValid = false;
                errorMessage += "\n La valeur de butoir circulaire est invalide";
            }
            else
            {
                if( (n <= 0) || (n > 1000))
                {
                    isValid = false;
                    errorMessage +="\nLa valeur de butoir circulaire est hors la limite ";
                }
                    
            }
            if (!(int.TryParse(ptsButTri_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\n La valeur de butoir triangulaire est invalide";
            }
            else
            {
                if ((n <= 0) || (n > 1000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur de butoir triangulaire est hors la limite ";
                }

            }
            if (!(int.TryParse(ptsCible_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\n La valeur de la cible est invalide";
            }
            else
            {
                if ((n <= 0) || (n > 1000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur de la cible est hors la limite ";
                }

            }
            if (!(int.TryParse(ptsVictoire_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\n La valeur de la victoire est invalide";
            }
            else
            {
                if ((n <= 0) || (n > 1000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur des points de victoire est hors la limite ";
                }

            }
            if (!(int.TryParse(ptsFreeBall_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\n La valeur de la balle gratuite est invalide";
            }
            else
            {
                if ((n <= 0) || (n > 1000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur de points pour une balle gratuite est hors la limite ";
                }

            }
            if (!(int.TryParse(difficulte_ComboBox.Text, out n)))
            {
                isValid = false;
                errorMessage += "\n La valeur de la difficulte est invalide";
            }
            else
            {
                if ((n <= 1) || (n > 10))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur de difficulte est hors la limite ";
                }

            }

            return isValid;
        }
        private void propAnnuler_Bouton_Click(object sender, EventArgs e)
        {
            this.Close();        

        }

        public List<int> getProps()
        {
            return mesProp;
        }
        private void propConfirm_Bouton_Click(object sender, EventArgs e)
        {

            if (checkValue())
            {
                mesProp[0] = Convert.ToInt32(ptsButCirc_Box.Text);
                mesProp[1] = Convert.ToInt32(ptsButTri_Box.Text);
                mesProp[2] = (Convert.ToInt32(ptsCible_Box.Text));
                mesProp[3] =(Convert.ToInt32(ptsVictoire_Box.Text));
                mesProp[4] = (Convert.ToInt32(ptsFreeBall_Box.Text));
                mesProp[5] = (Convert.ToInt32(difficulte_ComboBox.Text));
                this.Hide();
            }
            else
            {
                MessageBox.Show(errorMessage, "messsage d'erreur",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
                errorMessage = "";
            }
           
          // this.Close();
        }

        
    }
}
