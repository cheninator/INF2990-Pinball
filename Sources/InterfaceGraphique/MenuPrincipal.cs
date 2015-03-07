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
using System.Drawing;
using System.Text;
using System.Threading;
using System.Windows.Forms;

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
        public Editeur modeEdit; ///< Form du mode edition
        private Thread myThread; ///< Une thread
        public Campagne campagne;
        public PartieRapide pRapide;
        private Configuration configuration;
        public ModeJeu modeJeuMain;


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public MainMenu()
        /// @brief Constructeur de la fenetre.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public MainMenu()
        {

            Console.WriteLine(FonctionsNatives.obtenirDerniereCampagne());
            this.KeyPress += new KeyPressEventHandler(Form1_KeyPress);
            InitializeComponent();
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.Image = Properties.Resources.pinball1;
            this.KeyPreview = true;
            StartPosition = FormStartPosition.CenterScreen;
            StringBuilder initSound = new StringBuilder("");
            configuration = new Configuration();
            FonctionsNatives.consolDebug(configuration.getConfig(0), configuration.getConfig(1), configuration.getConfig(2), configuration.getConfig(3));
        }

        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
       {
   
       } 

       ////////////////////////////////////////////////////////////////////////
       ///
       /// @fn private void bouton_quit_Click(object sender, EventArgs e)
       /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
       ///        le bouton Quitter.
       /// 
       /// @param[in] sender : Objet duquel provient un evenement
       /// @param[in] e : evenement qui lance la fonction.
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
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Editeur.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_edit_Click(object sender, EventArgs e)
        {
            while (myThread.IsAlive)
            {
               Thread.Sleep(100);
            }
            this.Hide();
            modeEdit = new Editeur();
            modeEdit.ShowDialog();
            if (modeEdit != null)
            {
                modeEdit = null;
            }
            this.Show();
            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_edit_MouseEnter(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur place la 
        ///        souris sur le bouton Editeur.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
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
        /// @brief Gestion des evenements lorsque l'utilisateur enleve la 
        ///        souris du bouton Editeur.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
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
        /// @brief Gestion des evenements lorsque l'utilisateur place la 
        ///        souris sur le bouton Quitter.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
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
        /// @brief Gestion des evenements lorsque l'utilisateur enleve la 
        ///        souris du bouton Quitter.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
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
        /// @brief Gestion des evenements lorsque le menu s'ouvre. La musique
        ///        joue sur un autre Thread.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
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
            campagne = new Campagne();
            this.Hide();
            campagne.ShowDialog(this);
            this.Show();
        }

        private void bouton_config_MouseEnter(object sender, EventArgs e)
        {
            bouton_config.ForeColor = Color.Green;
            bouton_config.FlatAppearance.BorderColor = Color.Black;
            bouton_config.FlatAppearance.BorderSize = 1;
            player.Play();
        }

        private void bouton_config_MouseLeave(object sender, EventArgs e)
        {
            bouton_config.FlatAppearance.BorderSize = 0;
            bouton_config.ForeColor = Color.Black;
        }

        private void bouton_campagne_MouseEnter(object sender, EventArgs e)
        {
            bouton_campagne.ForeColor = Color.Green;
            bouton_campagne.FlatAppearance.BorderColor = Color.Black;
            bouton_campagne.FlatAppearance.BorderSize = 1;
            player.Play();
        }

        private void bouton_campagne_MouseLeave(object sender, EventArgs e)
        {
            bouton_campagne.FlatAppearance.BorderSize = 0;
            bouton_campagne.ForeColor = Color.Black;
        }

        private void bouton_pRapide_MouseEnter(object sender, EventArgs e)
        {
            bouton_pRapide.ForeColor = Color.Green;
            bouton_pRapide.FlatAppearance.BorderColor = Color.Black;
            bouton_pRapide.FlatAppearance.BorderSize = 1;
            player.Play();
        }

        private void bouton_pRapide_MouseLeave(object sender, EventArgs e)
        {
            bouton_pRapide.FlatAppearance.BorderSize = 0;
            bouton_pRapide.ForeColor = Color.Black;
        }

        private void pictureBox1_MouseEnter(object sender, EventArgs e)
        {
            pictureBox1.Image = Properties.Resources.newScary;
            player.Stream = Properties.Resources.scary;
            player.Play();
        }

        private void pictureBox1_MouseLeave(object sender, EventArgs e)
        {
            pictureBox1.Image = Properties.Resources.pinball1;
            player.Stream = Properties.Resources.button_29;
        }

        private void bouton_pRapide_Click(object sender, EventArgs e)
        {
            while (myThread.IsAlive)
            {
               // Thread.Sleep(100);
            }
            this.Hide();
            pRapide = new PartieRapide();
            pRapide.ShowDialog(this);
            this.Show();
            
        }

        private void bouton_config_Click(object sender, EventArgs e)
        {
            configuration.ShowDialog();
        }

        public void LancerModeJeu(List<string> zones) 
        { 
            modeJeuMain = new ModeJeu(zones); 
            modeJeuMain.ShowDialog(this);
            if (campagne != null)
            {
                campagne.Close();
            }
            else if (pRapide != null)
            {
                pRapide.Close();
            }
            this.Show(); 
        }
    }                                  
}
