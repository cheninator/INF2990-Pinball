//////////////////////////////////////////////////////////////////////////////
/// @file Proprietes.cs
/// @author Ballers
/// @date 2015-01-27
/// @version 1.0 
///
/// @ingroup InterfaceGraphique
//////////////////////////////////////////////////////////////////////////////

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
    ///////////////////////////////////////////////////////////////////////////
    /// @class Proprietes
    /// @brief Fenêtre des propriétés de la partie.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    public partial class Proprietes : Form
    {
        public List<int> mesProp; ///< Liste des propriétés
        string errorMessage = "";

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Proprietes(List<int> a)
        /// @brief Constructeur par paramèetre de la fenêtre.
        /// 
        /// param[in] a : liste des propriétés à instancier.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private bool checkValue()
        /// @brief Vérifie que les valeurs entrées par l'utilisateur sont valides.
        /// 
        /// @return True si les valeurs entrées sont valides, false sinon.
        ///
        ////////////////////////////////////////////////////////////////////////
        private bool checkValue()
        {
            int n;
            bool isValid = true;
          
            if( !(int.TryParse(ptsButCirc_Box.Text, out n))){
                isValid = false;
                errorMessage += "\nLa valeur de butoir circulaire est invalide";
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
                errorMessage += "\nLa valeur de butoir triangulaire est invalide";
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
                errorMessage += "\nLa valeur de la cible est invalide";
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
                errorMessage += "\nLa valeur de la victoire est invalide";
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
                errorMessage += "\nLa valeur de la balle gratuite est invalide";
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
                errorMessage += "\nLa valeur de la difficulte est invalide";
            }
            else
            {
                if ((n < 1) || (n > 10))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur de difficulte est hors la limite ";
                }

            }

            return isValid;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void propAnnuler_Bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Annuler.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void propAnnuler_Bouton_Click(object sender, EventArgs e)
        {
            this.Close();        

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public List<int> getProps()
        /// @brief Accesseur de l'attribut des propriétés.
        /// 
        /// @return La liste des propriétés de jeu.
        ///
        ////////////////////////////////////////////////////////////////////////
        public List<int> getProps()
        {
            return mesProp;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void propConfirm_Bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Confirmer.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
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
