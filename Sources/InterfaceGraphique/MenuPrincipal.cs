//////////////////////////////////////////////////////////////////////////////
/// @file MenuPrincipal.cs
/// @author Ballers
/// @date 2015-01-18
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
using System.Threading;
using System.Threading.Tasks;
using System.Media;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class MainMenu
    /// @brief Main Menu du jeu.
    ///
    /// @author The Ballers
    /// @date 2015-01-18
    /// 
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    public partial class MainMenu : Form
    {
        System.Media.SoundPlayer player = new System.Media.SoundPlayer(Properties.Resources.button_29); ///< Sound player
        public Exemple modeEdit; ///< Form du mode édition
        private Thread myThread; ///< Une thread

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public MainMenu()
        /// @brief Constructeur de la fenêtre.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public MainMenu()
        {
            this.KeyPress += new KeyPressEventHandler(Form1_KeyPress);
            InitializeComponent();
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.Image = Properties.Resources.pinball1;
            this.KeyPreview = true;
            StartPosition = FormStartPosition.CenterScreen;
            StringBuilder initSound = new StringBuilder("");
       }

       private void Form1_KeyPress(object sender, KeyPressEventArgs e)
       {
   
       }

       ////////////////////////////////////////////////////////////////////////
       ///
       /// @fn private void bouton_quit_Click(object sender, EventArgs e)
       /// @brief Gestion des événements lorsque l'utilisateur clique sur 
       ///        le bouton Quitter.
       /// 
       /// @param[in] sender : Objet duquel provient un événement
       /// @param[in] e : Événement qui lance la fonction.
       /// 
       /// @return Aucune.
       ///
       ////////////////////////////////////////////////////////////////////////
       private void bouton_quit_Click(object sender, EventArgs e)
        {
          this.Dispose();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_edit_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Editeur.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_edit_Click(object sender, EventArgs e)
        {
            while (myThread.IsAlive)
            {
                Thread.Sleep(1500);
                Console.WriteLine("Loading...");
            }
            this.Hide();
            modeEdit = new Exemple();
            modeEdit.ShowDialog();
            this.Show();
            
           }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_edit_MouseEnter(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur place la 
        ///        souris sur le bouton Editeur.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_edit_MouseEnter(object sender, EventArgs e)
        {
            bouton_edit.ForeColor = Color.Green;
            bouton_edit.FlatAppearance.BorderColor = Color.Black;
            bouton_edit.FlatAppearance.BorderSize = 1;
            player.Play();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_edit_MouseLeave(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur enlève la 
        ///        souris du bouton Editeur.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_edit_MouseLeave(object sender, EventArgs e)
        {
            bouton_edit.ForeColor = Color.Black;
            bouton_edit.FlatAppearance.BorderSize = 0;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_quit_MouseEnter(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur place la 
        ///        souris sur le bouton Quitter.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_quit_MouseEnter(object sender, EventArgs e)
        {
            bouton_quit.FlatAppearance.BorderSize = 1;
            bouton_quit.ForeColor = Color.Red;
            bouton_quit.FlatAppearance.BorderColor = Color.Black;
            player.Play();
            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_quit_MouseLeave(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur enlève la 
        ///        souris du bouton Quitter.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_quit_MouseLeave(object sender, EventArgs e)
        {
            bouton_quit.FlatAppearance.BorderSize = 0;
            bouton_quit.ForeColor = Color.Black;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MainMenu_Shown(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque le menu s'ouvre. La musique
        ///        joue sur un autre Thread.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MainMenu_Shown(object sender, EventArgs e)
        {
            myThread = new Thread(new ThreadStart(initMusic));
            myThread.Start();

        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void initMusic()
        /// @brief Joue un son.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void initMusic()
        {
            StringBuilder initSound = new StringBuilder("");
            InterfaceGraphique.FonctionsNatives.playSound(initSound, initSound.Capacity, true); // Initialise le son
        }

        private void bouton_campagne_Click(object sender, EventArgs e)
        {

        } 
    }                                  
}
