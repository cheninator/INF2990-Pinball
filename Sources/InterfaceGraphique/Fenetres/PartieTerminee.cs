//////////////////////////////////////////////////////////////////////////////
/// @file PartieTerminee.cs
/// @author Ballers
/// @date 2015-03-16
/// @version 1.0 
///
/// @ingroup Fenetres
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
    /// @class PartieTerminee
    /// @brief Classe d'interface de la fenetre Partie Terminee
    ///
    /// @author Ballers
    /// @date 2015-03-16
    /// 
    /// @ingroup Fenetres
    ///////////////////////////////////////////////////////////////////////////
    public partial class PartieTerminee : Form
    {
        System.Media.SoundPlayer player; ///< Sound Player.

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public PartieTerminee(bool victoire)
        /// @brief Constructeur par parametre de la fenetre Partie Terminee.
        /// @param[in] victoire : Indique si la partie a ete gagnee ou perdue.
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public PartieTerminee(bool victoire)
        {
            InitializeComponent();
            StartPosition = FormStartPosition.CenterScreen;
           
            if (victoire == false)
            {
              //  player = new System.Media.SoundPlayer(Properties.Resources.Trombone);
                player = new System.Media.SoundPlayer(Properties.Resources.gOver);

                labelTermine.Text = "Désolé "+ Program.playerName + ". Vous avez perdu la partie...";
                imageTermine.SizeMode = PictureBoxSizeMode.StretchImage;
                imageTermine.Image = Properties.Resources.Lose;
            }
            else
            {
                labelTermine.Text = "Félicitations " + Program.playerName + ". Vous avez remporté la partie!";

                player = new System.Media.SoundPlayer(Properties.Resources.Fireworks);
                imageTermine.SizeMode = PictureBoxSizeMode.StretchImage;
                imageTermine.Image = Properties.Resources.Win;
            }

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieTerminee_Shown(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on ouvre la fenetre Partie Terminee.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieTerminee_Shown(object sender, EventArgs e)
        {
            player.Play();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void boutonMenuP_Click(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on clique sur le bouton Menu Principal.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void boutonMenuP_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void boutonRecommencer_Click(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on clique sur le bouton Recommencer.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void boutonRecommencer_Click(object sender, EventArgs e)
        {
            ((ModeJeu)this.Owner).RecommencerTout();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieTerminee_FormClosing(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on ferme la fenetre Partie Terminee.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieTerminee_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.None)
            {
                this.Close();
            }
            else if (e.CloseReason == CloseReason.UserClosing)
            {
                ((ModeJeu)this.Owner).Close();
            }
            player.Stop();
        }
    }
}
