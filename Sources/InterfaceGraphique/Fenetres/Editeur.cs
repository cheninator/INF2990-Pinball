﻿//////////////////////////////////////////////////////////////////////////////
/// @file Editeur.cs
/// @author Ballers
/// @date 2015-01-13
/// @version 1.0 
///
/// @ingroup Fenetres
//////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Editeur
    /// @brief Main window de l'editeur du jeu.
    ///
    /// @author The Ballers
    /// @date 2015-01-13
    /// 
    /// @ingroup Fenetres
    ///////////////////////////////////////////////////////////////////////////
    public partial class Editeur : Form
    {
        private bool updateFrame = false;
        FullScreen fs = new FullScreen();
        static public StringBuilder myObjectName = new StringBuilder("vide");
        private Touches touches;
        public Point origin;
        string output = "";
        public Point previousP, currentP;
        double mouvementX, mouvementY;
        public int panelHeight; ///< Hauteur de la fenetre
        public int panelWidth; ///< Largeur de la fenetre
        private bool ctrlDown = false;
        private bool altDown = false;
        public List<int> propZJ = new List<int> { 100, 100, 100, 1000, 500, 1 }; ///< Une liste de choses
        private float angleX = 0F; ///< Position en X
        private float angleY = 0F; ///< Position en Y
        private float angleZ = 0F; ///< Position en Z
        private double currentZoom = -1; ///< Zoom courant
        private int nbSelection;
        private bool colorShift = false;
        private StringBuilder pathXML = new StringBuilder(""); ///< Chemin pour la lecture/sauvegarde XML
        private char POINT1 = ',';
        private char POINT2 = '.';
        private EtatEditeurAbstrait etat { get; set; } ///< Machine a etat
        private int[] prop = new int[6]; ///< Proprietes du jeu a sauvegarder
        private bool activateAmbianteLight = false; ///< EtatEditeurAbstrait de la lumiere ambiante
        private bool activateDirectLight = false; ///< EtatEditeurAbstrait de la lumiere directe
        private bool activateSpotLight = false; ///< EtatEditeurAbstrait de la lumiere spot
        //public void deselection();               ///< Fonction de deselection
        private bool etaitEtatPortail = false;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn static public Editeur()
        /// @brief Constructeur de la fenetre.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public Editeur()
        {
            updateFrame = false;
            this.KeyPreview = true;
            this.KeyPress += new KeyPressEventHandler(ToucheEnfonce);
            // Pour le deplacement de la vue
            // besoin de nouveau event parce que C#....
            this.KeyDown += new KeyEventHandler(ToucheDown);
            this.KeyUp += new KeyEventHandler(ToucheUp);
            this.Icon = Properties.Resources.Pinball;
            InitializeComponent();
            // ON joue en mode Solo
            touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                  FonctionsNatives.obtenirTouchePGJ1(),
                                  FonctionsNatives.obtenirTouchePDJ1(),
                                  FonctionsNatives.obtenirTouchePDJ1(),
                                  FonctionsNatives.obtenirToucheRessort());
            Program.peutAfficher = true;
            mouvementX = 100 * (double)(this.flowLayoutPanel1.Width) / (double)this.panel1.Width;
            mouvementY = 100 * (double)(this.menuStrip1.Height+this.toolStrip1.Height) / (double)this.panel1.Width;
            InitialiserAnimation();

            panelHeight = panel_GL.Size.Height;
            panelWidth = panel_GL.Size.Width;
            ReinitialiserTout();
            fs.EnterFullScreenMode(this);
            FonctionsNatives.animerJeu(false);
        
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ReinitialiserTout()
        /// @brief Reinitialisela vue.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ReinitialiserTout()
        {

            Program.peutAfficher = true;
            pathXML = new StringBuilder("");
            this.Text = "Mode Edition - Nouvelle Zone";
            panel_GL.Select();
            etat = new EtatEditeurSelection(this);
            deselection();
            ctrlDown = false;
            altDown = false;

            FonctionsNatives.resetZoom();
            currentZoom = -1;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn static public void InitialiserAnimation()
        /// @brief Initialise openGL et l'animation.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            this.StartPosition = FormStartPosition.WindowsDefaultBounds;
            FonctionsNatives.initialiserOpenGL(panel_GL.Handle);
            FonctionsNatives.populateUsines();
            FonctionsNatives.dessinerOpenGL();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void MettreAJour(double tempsInterAffichage)
        /// @brief Taches effectuees lors d'un rafraichissement d'ecran.
        /// 
        /// @param[in] tempsInterAffichage : Temps entre deux affichages.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void MettreAJour(double tempsInterAffichage)
        {
            if (updateFrame == false)
                return;
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    FonctionsNatives.refreshText(panel_GL.Size.Width, panel_GL.Size.Height);
                    if (etat is EtatEditeurSelectionMultiple || etat is EtatEditeurZoomElastique)
                    {
                        if (Program.compteurFrames == 0)
                            rectangleElastique();
                    }
                    else
                    {
                        if (currentZoom <= 0)
                        {
                            FonctionsNatives.resetZoom();
                            currentZoom = FonctionsNatives.obtenirZoomCourant();
                            Creation_Panel.Visible = true;
                        }

                        if (etat is EtatEditeurTest && FonctionsNatives.obtenirNombreBillesCourante() == 0)
                        {
                            StringBuilder bille = new StringBuilder("bille");
                            FonctionsNatives.creerObjet(bille, bille.Capacity);
                        }
                        if (Program.compteurFrames == 0)
                        {
                            FonctionsNatives.dessinerOpenGL();
                        }
                        FonctionsNatives.animer(tempsInterAffichage);
                    }
                });
            }
            catch (Exception)
            {
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ToucheDown(Object o, KeyEventArgs e)
        /// @brief Gestion des etats lorsqu'une touche est enfoncee.
        /// 
        /// @param[in] o : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ToucheDown(Object o, KeyEventArgs e)
        {
           // if (etat is EtatEditeurZoom || etat is EtatEditeurTest)
            if(true)
            {
                if ((e.KeyData == Keys.Subtract ||
                   e.KeyCode == Keys.OemMinus))
                {
                    FonctionsNatives.zoomOut();
                    currentZoom = FonctionsNatives.obtenirZoomCourant();
                }
                if ((e.KeyData == Keys.Add ||
                    e.KeyCode == Keys.Oemplus && e.Modifiers == Keys.Shift))
                {
                    FonctionsNatives.zoomIn();
                    currentZoom = FonctionsNatives.obtenirZoomCourant();
                }
                if (e.KeyData == Keys.Alt)
                    altDown = true;

            }
            if (panel_GL.Focused == true)
            {

                if (e.KeyData == Keys.Left)
                    FonctionsNatives.translater(-10, 0);

                else if (e.KeyData == Keys.Right)
                    FonctionsNatives.translater(10, 0);

                else if (e.KeyData == Keys.Up)
                    FonctionsNatives.translater(0, 10);

                else if (e.KeyData == Keys.Down)
                    FonctionsNatives.translater(0, -10);
                else if (e.KeyData == Keys.Delete)
                {
                    bouton_Suppression.PerformClick();
                }
                else if (e.KeyData == Keys.D1)
                {
                    Orthographique_MenuItem.PerformClick();
                }
                else if (e.KeyData == Keys.D2)
                {
                    Orbite_MenuItem.PerformClick();
                }
                if (etat is EtatEditeurTest)
                {
                    ToucheDownTest(o, e);
                }

            }
            if (e.Modifiers == Keys.Control)
            {
                ctrlDown = true;

            }
            if (e.Alt)
            {
                e.Handled = true;

                altDown = true;
            }

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ToucheDownTest(Object o, KeyEventArgs e)
        /// @brief Gestion des etats lorsqu'une touche est appuye dans le mode Test.
        /// 
        /// @param[in] o : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ToucheDownTest(Object o, KeyEventArgs e)
        {
            if (e.KeyValue == touches.PGJ1)
            {
                FonctionsNatives.activerPalettesGJ1();
            }

            if (e.KeyValue == touches.PGJ2)
            {
                // TODO: palette gauche joueur 2
                FonctionsNatives.activerPalettesGJ2();
            }
            if (e.KeyValue == touches.PDJ1)
            {
                FonctionsNatives.activerPalettesDJ1();
            }
            if (e.KeyValue == touches.PDJ2)
            {
                FonctionsNatives.activerPalettesDJ2();
            }
            else if (e.KeyValue == touches.Ressort)
            {
                FonctionsNatives.compresserRessort();
            }

        
            // TODO
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ToucheUpTest(Object o, KeyEventArgs e)
        /// @brief Gestion des etats lorsqu'une touche est relâchee en mode Test.
        /// 
        /// @param[in] o : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ToucheUpTest(Object o, KeyEventArgs e)
        {
            if (e.KeyValue == touches.PGJ1)
            {
                FonctionsNatives.desactiverPalettesGJ1();
            }
            if (e.KeyValue == touches.PGJ2)
            {
                // TO DO: palette gauche joueur 1
                FonctionsNatives.desactiverPalettesGJ2();
            }
            if (e.KeyValue == touches.PDJ1)
            {
                FonctionsNatives.desactiverPalettesDJ1();
            }
            if (e.KeyValue == touches.PDJ2)
            {
                FonctionsNatives.desactiverPalettesDJ2();
            }
            if (e.KeyValue == touches.Ressort)
            {
                FonctionsNatives.relacherRessort();
            }
            // TO DO
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ToucheUp(Object o, KeyEventArgs e)
        /// @brief Gestion des etats lorsqu'une touche est relâchee.
        /// 
        /// @param[in] o : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ToucheUp(Object o, KeyEventArgs e)
        {

            if (e.KeyData.ToString() == "Menu")
            {
                altDown = false;
            }
            if (e.KeyData.ToString() == "ControlKey") // == Keys.Control ?
            {
                ctrlDown = false;
            }
            if (etat is EtatEditeurTest)
            {
                ToucheUpTest(o, e);
            }


        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ToucheEnfonce(Object o, KeyPressEventArgs e)
        /// @brief Gestion des etats lorsqu'une touche est enfoncee.
        /// 
        /// @param[in] o : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ToucheEnfonce(Object o, KeyPressEventArgs e)
        {
            if ((etat is EtatEditeurZoomElastique) || (etat is EtatEditeurSelectionMultiple))
            {
                return;
            }
            if (etat is EtatEditeurTest)
            {
                if (Char.ToLower(e.KeyChar) == 't')
                {
                    FonctionsNatives.arreterToutSons();
                    FonctionsNatives.jouerSon(Program.couvercle, Program.couvercle.Length);
                    if (Program.mMenu.modeEdit != null)
                    {
                        Program.myCustomConsole.Show();
                        Program.mMenu.modeEdit.Focus();
                    }
                    testRetourModeEdition.PerformClick();
                    OnSizeChanged(e);

                    Annuler_ToolStrip.Enabled = FonctionsNatives.possedePrecedent();
                    Retablir_ToolStrip.Enabled = FonctionsNatives.possedeSuivant();
                }
                else if (Char.ToLower(e.KeyChar) == 'b')
                {
                    if (FonctionsNatives.obtenirAffichageGlobal() == 0)
                    {
                        FonctionsNatives.WriteLine("Affichage bloque. On debloque");
                        FonctionsNatives.bloquerAffichageGlobal(1);
                        if (Program.mMenu.modeEdit != null)
                        {
                            Program.myCustomConsole.Show();
                            Program.mMenu.modeEdit.Focus();
                        }
                    }
                    else
                    {
                        FonctionsNatives.WriteLine("Affichage permis. On bloque");
                        FonctionsNatives.bloquerAffichageGlobal(0);
                        Program.myCustomConsole.Hide();
                    }
                }

                /*else if (e.KeyChar == 'n')
                {
                    StringBuilder bille = new StringBuilder("bille");
                   FonctionsNatives.creerObjet(bille, bille.Capacity);
                }
                */
                else if (Char.ToLower(e.KeyChar) == 'j')
                {
                    //Console.WriteLine("LUMIERE AMBIANTE");
                    activateAmbianteLight = !activateAmbianteLight;
                    FonctionsNatives.spotLight(0, activateAmbianteLight);
                }
                else if (Char.ToLower(e.KeyChar) == 'k')
                {
                    //Console.WriteLine("LUMIERE DIRECTE");
                    activateDirectLight = !activateDirectLight;
                    FonctionsNatives.spotLight(1, activateDirectLight);
                }
                else if (Char.ToLower(e.KeyChar) == 'l')
                {
                    //Console.WriteLine("LUMIERE SPOTS");
                    activateSpotLight = !activateSpotLight;
                    FonctionsNatives.spotLight(2, activateSpotLight);
                }
                else if (e.KeyChar == (char)Keys.Escape)
                {
                    menuStrip3.Show();
                    FonctionsNatives.animerJeu(false);
                    FonctionsNatives.modePause(true);
                    etat = null;
                    etat = new EtatEditeurPause(this);
                }
                else if (e.KeyChar == (char)Keys.Back)
                {
                    FonctionsNatives.rechargerArbre(true);
                    FonctionsNatives.resetNombreBillesCourantes();
                }
            }
            else if (etat is EtatEditeurPause)
            {
                if (e.KeyChar == (char)Keys.Escape)
                {
                    menuStrip3.Hide();
                    FonctionsNatives.animerJeu(true);
                    FonctionsNatives.modePause(false);
                    etat = null;
                    etat = new EtatEditeurTest(this);
                }
                if (Char.ToLower(e.KeyChar) == 't')
                {
                    testRetourModeEdition.PerformClick();
                    OnSizeChanged(e);
                }
            }
            else
            {
                if (e.KeyChar == (char)Keys.Escape)
                {
                    if (etat is EtatEditeurPortail || etat is EtatEditeurMur || etat is EtatEditeurDuplication || etat is EtatEditeurCreation)
                    {
                        FonctionsNatives.removeObject();                        
                    }

                    panel_GL.MouseMove -= panel_MouseMove;                  
                    deselection();
                    etat = new EtatEditeurSelection(this);                   

                }
                else if (Char.ToLower(e.KeyChar) == 't')
                {
                    FonctionsNatives.arreterToutSons();
                    FonctionsNatives.jouerSon(Program.couvercle, Program.couvercle.Length);
                    deselection();
                    ModeTest_MenuItem.PerformClick();
                    panel_GL.Focus();
                }
                else if (Char.ToLower(e.KeyChar) == 'f')
                {
                    if (fs.IsFullScreen(this))
                    {
                        fs.LeaveFullScreenMode(this);
                    }
                    else
                        fs.EnterFullScreenMode(this);
                    // A modifier si on veut            
                    //  FonctionsNatives.resetZoom();
                }
                else if (Char.ToLower(e.KeyChar) == 's')
                {
                    Selection_MenuItem_Click(this, e);
                }
               
                else if (Char.ToLower(e.KeyChar) == 'p')
                {
                    bouton_Creation_Click(this, e);
                }
              
                else if (e.KeyChar == 'h')
                {
                    /*if (richTextBox1.Visible)
                        richTextBox1.Hide();
                    else
                        richTextBox1.Show();
                    */
                }
                else if (Char.ToLower(e.KeyChar) == 'z')
                {
                    Zoom_MenuItem_Click(this, e);

                }
                else if (nbSelection != 0)
                {
                    if (Char.ToLower(e.KeyChar) == 'd')
                    {
                        bouton_Deplacement_Click(this, e);
                    }
                    else if (Char.ToLower(e.KeyChar) == 'e')
                    {
                        bouton_Scaling_Click(this, e);
                    }
                    else if (Char.ToLower(e.KeyChar) == 'r')
                    {
                        bouton_Rotation_Click(this, e);
                    }
                    else if (Char.ToLower(e.KeyChar) == 'c')
                    {
                        bouton_Duplication_Click(this, e);
                    }
                }
             
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn  private void Editeur_FormClosing(object sender, FormClosingEventArgs e)
        /// @brief Gestion des evenements lorsque la fenetre est fermee.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Editeur_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!(etat is EtatEditeurTest))
            {
                DialogResult dRes= MessageBox.Show("Voulez vous sauvegarder avant de quitter? Tout changement non-sauvegardé sera oublié.", "Fermeture d'application", MessageBoxButtons.YesNoCancel);
                if (dRes == DialogResult.Cancel)
                {
                    e.Cancel = true;
                    this.Activate();
                }
                else if (dRes == DialogResult.Yes)
                    EnregistrerSous();
                
               
                    lock (Program.unLock)
                    {
                        Program.peutAfficher = false;
                        FonctionsNatives.libererOpenGL();
                    }
                    FonctionsNatives.arreterToutSons();
                    Program.myCustomConsole.Hide();
               
               
             
            }
            else
            {
                lock (Program.unLock)
                {
                    Program.peutAfficher = false;
                    FonctionsNatives.libererOpenGL();
                }
                FonctionsNatives.arreterToutSons();
                Program.myCustomConsole.Hide();
            }
            
         
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Aide_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Aide.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Aide_MenuItem_Click(object sender, EventArgs e)
        {
         //   BackgroundWorker bw = new BackgroundWorker();
         //   bw.WorkerReportsProgress = true;
         //   bw.DoWork += new DoWorkEventHandler(
         //   delegate(object o, DoWorkEventArgs args)
         //   {
             
         //   });
         //   bw.RunWorkerAsync();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Ouvrir_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Ouvrir.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Ouvrir_MenuItem_Click(object sender, EventArgs e)
        {

            OpenFileDialog ouvrir_fichier = new OpenFileDialog();
            ouvrir_fichier.Filter = "Fichier XML(*.xml)| *.xml| All files(*.*)|*.*";
            string initPath = Application.StartupPath + @"\zones";
            ouvrir_fichier.InitialDirectory = Path.GetFullPath(initPath);
            ouvrir_fichier.RestoreDirectory = true;
            if (ouvrir_fichier.ShowDialog() == DialogResult.OK)
            {
                ReinitialiserTout();

                pathXML = new StringBuilder(ouvrir_fichier.FileName);
                //Console.Write(Path.GetFileName(ouvrir_fichier.FileName));

                output = Path.GetFileName(pathXML.ToString());
                output = output.Remove(output.Length - 4);
                this.Text = "Mode Edition - " + output;
                IntPtr prop = FonctionsNatives.ouvrirXML(pathXML, pathXML.Capacity);
                int[] result = new int[6];
                Marshal.Copy(prop, result, 0, 6);

                for (int i = 0; i < 6; i++)
                    propZJ[i] = result[i];


            }
            FonctionsNatives.viderHistorique();
            Annuler_ToolStrip.Enabled = false;
            Retablir_ToolStrip.Enabled = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void EnregistrerS_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Enregistrer Sous.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void EnregistrerS_MenuItem_Click(object sender, EventArgs e)
        {
            EnregistrerSous();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void EnregistrerSous()
        /// @brief Enregistrement des proprietes de la partie en format XML.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void EnregistrerSous()
        {

            SaveFileDialog enregistrer_fichier = new SaveFileDialog();
            enregistrer_fichier.Filter = "Fichier XML(*.xml)| *.xml| All files(*.*)|*.*";
            // Utilise string au lieu de String stp
            String initPath = Application.StartupPath + @"\zones";
            enregistrer_fichier.InitialDirectory = Path.GetFullPath(initPath);
            enregistrer_fichier.RestoreDirectory = true;
            enregistrer_fichier.OverwritePrompt = false;
            String fileName = Path.GetFileName(enregistrer_fichier.FileName);
            //Console.WriteLine(fileName);
            if (fileName == "default.xml")
            {
                MessageBox.Show("Vous ne pouvez pas sauvegarder sur la zone de jeu par defaut!", "ERREUR DE SAUVEGARDE",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            else
                if (enregistrer_fichier.ShowDialog() == DialogResult.OK)
                {
                    enregistrer_fichier.OverwritePrompt = true;
                    //ReinitialiserTout();
                    pathXML = new StringBuilder(enregistrer_fichier.FileName.Replace(' ', '_'));
                    for (int i = 0; i < 6; i++)
                        prop[i] = propZJ[i];


                    int sauvegarde = FonctionsNatives.creerXML(pathXML, pathXML.Capacity, prop);
                    
                    FonctionsNatives.viderHistorique();
                    Annuler_ToolStrip.Enabled = false;
                    Retablir_ToolStrip.Enabled = false;

                    //Console.WriteLine(sauvegarde);
                    if (sauvegarde == 1)
                    {
                        MessageBox.Show("Vous ne pouvez pas sauvegarder la zone de jeu par defaut!", "ERREUR DE SAUVEGARDE",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        pathXML = new StringBuilder("");
                    }
                    else if (sauvegarde == 3 || sauvegarde == 0)
                    {
                        MessageBox.Show("Il doit avoir au moins un trou, un generateur de bille et un ressort dans la zone de jeu!", "ERREUR DE SAUVEGARDE",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        pathXML = new StringBuilder("");
                    }
                    else if (sauvegarde == 4)
                    {
                        MessageBox.Show("Tout les trous doivent etre au minimum de la taille de la plus grande bille (le plus gros generateur de billes) !", "ERREUR DE SAUVEGARDE",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        pathXML = new StringBuilder("");
                    }
                    else
                    {
                        takeScreenShot();
                    }
                }
        }


        private void takeScreenShot()
        {
            if (pathXML.Capacity == 0)
                return;
            // Well shit, well need to call a DLL function in csharp again !
            string pathJPG = pathXML.ToString();
            pathJPG = pathJPG.Remove(pathJPG.Length - 3, 3);
            pathJPG = pathJPG.Insert(pathJPG.Length, "jpg");
            StringBuilder pathToPicture = new StringBuilder(pathJPG);
            output = Path.GetFileName(pathXML.ToString());
            output = output.Remove(output.Length - 4);
            this.Text = "Mode Edition - " + output;
            FonctionsNatives.takeScreenShot(pathToPicture, pathToPicture.Capacity, true, 408);
            // Si on veut une fenetre carree, alors on met true, si on veutu nrectangle, false
            // Si on veut limiter la taille maximale de la fenetre (un resize du screenshot), on met la valeur d'un cote
            // example:
            //FonctionsNatives.takeScreenShot(pathToPicture, pathToPicture.Capacity, true, 350);
            // ou encore, si on veut rien appliquer de precis:
            //FonctionsNatives.takeScreenShot(pathToPicture, pathToPicture.Capacity);
        }





        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void helpToolStripButton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        l'outil Aide.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void helpToolStripButton_Click(object sender, EventArgs e)
        {
            Aide_MenuItem_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Selectionner_BO_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Creation.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Selectionner_BO_Click(object sender, EventArgs e)
        {
            if (Creation_Panel.Visible)
                Creation_Panel.Hide();
            else
                Creation_Panel.Show();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel1_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le panel1 (ecriture des coord. sur la console).
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel1_Click(object sender, EventArgs e)
        {
            //Console.Write(this.PointToClient(MousePosition));
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Selection_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Selection.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Selection_MenuItem_Click(object sender, EventArgs e)
        {
            bouton_Selection_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Selection_BO_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Selection.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Selection_BO_Click(object sender, EventArgs e)
        {
            Selection_MenuItem_Click(this, e);

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Rotation_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Rotation.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Rotation_MenuItem_Click(object sender, EventArgs e)
        {
            bouton_Rotation_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Rotation_BO_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Rotation.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Rotation_BO_Click(object sender, EventArgs e)
        {
            Rotation_MenuItem_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Selection_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Selection.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Selection_Click(object sender, EventArgs e)
        {
            annulerModif();
            etat = new EtatEditeurSelection(this);

            //Console.WriteLine("Outil Selection.");
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Creation_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Creation.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Creation_Click(object sender, EventArgs e)
        {
            annulerModif();
            if (etat is EtatEditeurMur)
            {
                etat = new EtatEditeurSelection(this);
            }
            //Console.WriteLine("Outil Creation.");
            if (Creation_Panel.Visible)
            {
                bouton_Creation.Text = "<<<";            
                Creation_Panel.Visible = false;
                this.OnSizeChanged(e);

            }
            else
            {
                Creation_Panel.Visible = true;
                bouton_Creation.Text = ">>>";

            }
            panel_GL.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_MouseClick(object sender, MouseEventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le panel GL (ecriture des coord. sur la console).
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseClick(object sender, MouseEventArgs e)
        {
            //Console.Write(panel_GL.PointToClient(MousePosition));
            panel_GL.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void butourCirc_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Butoir Circulaire.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void butourCirc_bouton_Click(object sender, EventArgs e)
        {
            butoirCirc_bouton.FlatAppearance.BorderColor = Color.DarkOrange;
            
            //Console.WriteLine("ButoirCirculaire");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("butoircirculaire");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Proprietes_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Proprietes.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Proprietes_MenuItem_Click(object sender, EventArgs e)
        {
            Proprietes proprietes = new Proprietes(this.propZJ);
            //proprietes.Parent = this;
            proprietes.StartPosition = FormStartPosition.CenterScreen;
            proprietes.ShowDialog();
            propZJ = proprietes.getProps();
            proprietes.Close();

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void butoirG_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Butoir Gauche.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void butoirG_bouton_Click(object sender, EventArgs e)
        {
            butoirG_bouton.FlatAppearance.BorderColor = Color.DarkOrange;
            
            //Console.WriteLine("Butoir Gauche.");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("butoirg");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void OK_prop_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton OK des proprietes.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void OK_prop_bouton_Click(object sender, EventArgs e)
        {
            if ((Math.Round(FonctionsNatives.getScale() * 100) / 100).ToString().Contains(","))
            {
                POINT1 = '.';
                POINT2 = ',';
            }
            else
            {
                POINT2 = '.';
                POINT1 = ',';
            }
            annulerModif();
            int positionX;
            int positionY;
            int angle;
            double echelle;
            DataTable dt = new DataTable();

            if (Xbox.Text == "")
                Xbox.Text = "0";
            if (Ybox.Text == "")
                Ybox.Text = "0";
            if (Anglebox.Text == "")
                Anglebox.Text = "0";
            if (FMEbox.Text == "")
                FMEbox.Text = "1";

            FMEbox.Text = FMEbox.Text.Replace(POINT1, POINT2);

            if (!int.TryParse(Xbox.Text, out positionX))
                Xbox.Text = "ERREUR";
            if (!int.TryParse(Ybox.Text, out positionY))
                Ybox.Text = "ERREUR";

            try
            {
                double value = ((double)dt.Compute(Anglebox.Text, ""));
                Anglebox.Text = Convert.ToInt32(Math.Round(value)).ToString();
            }
            catch { }
            try
            {
                double value = ((double)dt.Compute(FMEbox.Text, ""));
                FMEbox.Text = (Convert.ToInt32(Math.Round(value * 100)) / 100.0).ToString();
            }
            catch { }

            if (!int.TryParse(Anglebox.Text, out angle))
                Anglebox.Text = "ERREUR";
            if (!double.TryParse(FMEbox.Text, out echelle))
                FMEbox.Text = "ERREUR";

            if (Xbox.Text == "ERREUR" ||
                Ybox.Text == "ERREUR" ||
                 Anglebox.Text == "ERREUR" ||
                FMEbox.Text == "ERREUR"
               )
            {
                return;
            }
            else
            {
                if (FonctionsNatives.setProprietesNoeud(positionX, positionY, angle, echelle) == false)
                {
                    MessageBox.Show("Les modifications feront sortir l'objet de la table.", "ERREUR DE PROPRIETES",
               MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }


        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void Positionner_Objet()
        /// @brief Logique de positionnement d'un objet par les text boxes.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Positionner_Objet()
        {

            int positionX;
            int positionY;

            if (Xbox.Text == "")
                Xbox.Text = "0"; ;
            if (Ybox.Text == "")
                Ybox.Text = "0"; ;

            if (!int.TryParse(Xbox.Text, out positionX))
                return;
            if (!int.TryParse(Ybox.Text, out positionY))
                return;

            if (positionX < 0 || positionY < 0)
                return;

            FonctionsNatives.positionObjet(positionX, positionY);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void Rotate_Object()
        /// @brief Logique de rotation d'un objet par les text boxes.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Rotate_Object()
        {
            string angleRead = Anglebox.Text;
            angleRead = angleRead.Replace(",", ".");
            float angle;

            if (Anglebox.Text == "")
                Anglebox.Text = "0.0"; ;

            DataTable dt = new DataTable();
            try { angleRead = dt.Compute(angleRead, "").ToString(); }
            catch { return; }

            if (!float.TryParse(angleRead, out angle))
                return;

            FonctionsNatives.rotate(angle);
            //Anglebox.Text = "0.0";
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Fenetre_Redimension(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur redimensionne
        ///        la fenetre.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Fenetre_Redimension(object sender, EventArgs e)
        {
            // Console.Write("Width to send : " + panel_GL.Width.ToString() + "\n" + "Height to send : " + panel_GL.Height.ToString() + "\n");
            FonctionsNatives.redimensionnerFenetre(panel_GL.Width == 0 ? 1 : panel_GL.Width, panel_GL.Height == 0 ? 1 : panel_GL.Height);

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Annuler_prop_boutn_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Annuler des proprietes.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Annuler_prop_boutn_Click(object sender, EventArgs e)
        {
            annulerModif();
            Xbox.Text = Math.Round(FonctionsNatives.getPositionX()).ToString();
            Ybox.Text = Math.Round(FonctionsNatives.getPositionY()).ToString();
            Anglebox.Text = Math.Round(FonctionsNatives.getAngle()).ToString();
            FMEbox.Text = (Math.Round(FonctionsNatives.getScale() * 100) / 100).ToString();
        }


        private void Editeur_Load(object sender, EventArgs e)
        {

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Ressort_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Ressort.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Ressort_bouton_Click(object sender, EventArgs e)
        {
            Ressort_bouton.FlatAppearance.BorderColor = Color.DarkOrange;
            
            //Console.WriteLine("Ressort");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("ressort");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Generateur_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Generateur de bille.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Generateur_bouton_Click(object sender, EventArgs e)
        {
            Generateur_bouton.FlatAppearance.BorderColor = Color.DarkOrange;
            
            //Console.WriteLine("Generateur");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("generateurbille");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Trou_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Trou.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Trou_bouton_Click(object sender, EventArgs e)
        {
            Trou_bouton.FlatAppearance.BorderColor = Color.DarkOrange;
            
            //Console.WriteLine("Trou");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("trou");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Deplacement_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Deplacement.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Deplacement_Click(object sender, EventArgs e)
        {
            //Console.WriteLine("Outil Deplacement.");
            // TO DO
            annulerModif();

            if(etat is EtatEditeurSelection)
                sauvegarderHistorique();

            etat = null;
            etat = new EtatEditeurDeplacement(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Deplacement_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Deplacement.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Deplacement_MenuItem_Click(object sender, EventArgs e)
        {
            bouton_Deplacement_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MenuP_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu MenuPrincipal.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MenuP_MenuItem_Click(object sender, EventArgs e)
        {
            Program.myCustomConsole.Hide();
            this.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Rotation_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Rotation.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Rotation_Click(object sender, EventArgs e)
        {
            //Console.WriteLine("Outil Rotation.");
            // TO DO
            annulerModif();

            if (etat is EtatEditeurSelection)
                sauvegarderHistorique();

            etat = null;
            etat = new EtatEditeurRotation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Scaling_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Scaling.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Scaling_Click(object sender, EventArgs e)
        {
            //Console.WriteLine("Outil Mise a echelle.");
            // TO DO
            annulerModif();

            if(etat is EtatEditeurSelection)
                sauvegarderHistorique();

            etat = null;
            etat = new EtatEditeurScale(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MiseE_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu MiseE.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MiseE_MenuItem_Click(object sender, EventArgs e)
        {
            bouton_Scaling_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Zoom_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Zoom.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Zoom_MenuItem_Click(object sender, EventArgs e)
        {
            //Console.WriteLine("Outil Zoom.");
            annulerModif();
            etat = null;
            etat = new EtatEditeurZoom(this);

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Duplication_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Duplication.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Duplication_Click(object sender, EventArgs e)
        {
            //Console.WriteLine("Outil Duplication.");

            annulerModif();

            if (etat is EtatEditeurSelection)
                sauvegarderHistorique();

            etat = null;
            etat = new EtatEditeurDuplication(this);




        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Duplication_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Duplication.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Duplication_MenuItem_Click(object sender, EventArgs e)
        {
            bouton_Duplication_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Creation_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Creation.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Creation_MenuItem_Click(object sender, EventArgs e)
        {
            if (!Creation_Panel.Visible)
                Creation_Panel.Visible = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void BC_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu BC.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void BC_MenuItem_Click(object sender, EventArgs e)
        {
            butourCirc_bouton_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Orthographique_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Vue Orthographique.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Orthographique_MenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.utiliserCameraOrbite(false);
            ZoomElastique_ToolStrip.Enabled = true;
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Orbite_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Vue Orbite.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Orbite_MenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.utiliserCameraOrbite(true);
            ZoomElastique_ToolStrip.Enabled = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Supprimer_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Supprimer.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Supprimer_MenuItem_Click(object sender, EventArgs e)
        {
            //Console.WriteLine("Supprimer.");
            FonctionsNatives.removeObject();
            deselection();

            etat = new EtatEditeurSelection(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ModeTest_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Mode Test.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ModeTest_MenuItem_Click(object sender, EventArgs e)
        {
            //Console.WriteLine("Mode Test.");
            etat = null;
            etat = new EtatEditeurTest(this);
            menuStrip1.Hide();
            toolStrip1.Hide();
            Annuler_ToolStrip.Enabled = false;
            Retablir_ToolStrip.Enabled = false;
            SelectAll_MenuItem.Enabled = false;
            bouton_Creation.Hide();
            FonctionsNatives.animerJeu(true);
            FonctionsNatives.rechargerArbre(false);
            FonctionsNatives.resetNombreBillesCourantes();
            FonctionsNatives.rechargerArbre(true);

            if (Creation_Panel.Visible)
                Creation_Panel.Hide();
            flowLayoutPanel1.Hide();

            menu1Enable(false);
         

            panel_GL.BringToFront();
            panel_GL.Anchor = AnchorStyles.None;
            panel_GL.Location = new Point(163, 24);
            panel_GL.Dock = DockStyle.Fill;
            this.OnSizeChanged(e);
            if (!FonctionsNatives.cameraEstOrbite())
                FonctionsNatives.translater(-mouvementX, mouvementY);
            FonctionsNatives.construireListesPalettes();
            FonctionsNatives.mettreAJourListeBillesEtNoeuds();
            if (FonctionsNatives.obtenirAffichageGlobal() == 1)
            {
                if (Program.mMenu.modeEdit != null)
                {
                    Program.myCustomConsole.Show();
                    Program.mMenu.modeEdit.Focus();
                }
            }
       
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PGJ1_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Palette Gauche J1.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PGJ1_bouton_Click(object sender, EventArgs e)
        {
            PGJ1_bouton.FlatAppearance.BorderColor = Color.DarkOrange;
            //Console.WriteLine("Palette gauche J1.");
            colorShift = false;
            angleX = 180;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("paletteg");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PG_J1_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Palette Gauche J1.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PG_J1_MenuItem_Click(object sender, EventArgs e)
        {
            PGJ1_bouton_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PDJ1_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Palette Droite J1.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PDJ1_bouton_Click(object sender, EventArgs e)
        {
            PDJ1_bouton.FlatAppearance.BorderColor = Color.DarkOrange;
            
            //Console.WriteLine("Palette droite J1.");
            colorShift = false;
            angleX = 180;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("paletted");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PD_J1_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Palette Droite J1.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PD_J1_MenuItem_Click(object sender, EventArgs e)
        {
            PDJ1_bouton_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PGJ2_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Palette Gauche J2.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PGJ2_bouton_Click(object sender, EventArgs e)
        {
            PGJ2_bouton.FlatAppearance.BorderColor = Color.DarkOrange;
            
            //Console.WriteLine("Palette gauche J2.");
            colorShift = true;
            angleX = 180;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("paletteg");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PG_J2_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Palette Gauche J2.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PG_J2_MenuItem_Click(object sender, EventArgs e)
        {
            PGJ2_bouton_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PDJ2_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Palette Droite J2.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PDJ2_bouton_Click(object sender, EventArgs e)
        {
            PDJ2_bouton.FlatAppearance.BorderColor = Color.DarkOrange;
            
            //Console.WriteLine("Palette droite J2.");
            colorShift = true;
            angleX = 180;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("paletted");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PD_J2_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Palette Droite J2.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PD_J2_MenuItem_Click(object sender, EventArgs e)
        {
            PDJ2_bouton_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void BTG_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Butoir Gauche.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void BTG_MenuItem_Click(object sender, EventArgs e)
        {
            butoirG_bouton_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void butoirD_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Butoir Droit.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void butoirD_bouton_Click(object sender, EventArgs e)
        {
            butoirD_bouton.FlatAppearance.BorderColor = Color.DarkOrange;
            //Console.WriteLine("Butoir Droit.");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("butoird");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void BTD_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Butoir Droit.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void BTD_MenuItem_Click(object sender, EventArgs e)
        {
            butoirD_bouton_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Cible_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Cible.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Cible_bouton_Click(object sender, EventArgs e)
        {
            Cible_bouton.FlatAppearance.BorderColor = Color.DarkOrange;
            
            //Console.WriteLine("Cible.");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("cible");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Cible_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Cible.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Cible_MenuItem_Click(object sender, EventArgs e)
        {
            Cible_bouton_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Portails_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Portail.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Portails_bouton_Click(object sender, EventArgs e)
        {
            Portails_bouton.FlatAppearance.BorderColor = Color.DarkOrange;
            
            //Console.WriteLine("Portail");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("portail");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Portails_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Portail.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Portails_MenuItem_Click(object sender, EventArgs e)
        {
            Portails_bouton_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Mur_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Mur.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Mur_bouton_Click(object sender, EventArgs e)
        {
            Mur_bouton.FlatAppearance.BorderColor = Color.DarkOrange;
           
            //Console.WriteLine("Mur");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("mur");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Gate_Button_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Gate.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Gate_Button_Click(object sender, EventArgs e)
        {
            Gate.FlatAppearance.BorderColor = Color.DarkOrange;
            
            //Console.WriteLine("Gate");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            myObjectName = new StringBuilder("gate");
            etat = new EtatEditeurCreation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Mur_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Mur.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Mur_MenuItem_Click(object sender, EventArgs e)
        {
            Mur_bouton_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Ressort_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Ressort.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Ressort_MenuItem_Click(object sender, EventArgs e)
        {
            Ressort_bouton_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Ressort_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Generateur de bille.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void GB_MenuItem_Click(object sender, EventArgs e)
        {
            Generateur_bouton_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Trou_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Trou.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Trou_MenuItem_Click(object sender, EventArgs e)
        {
            Trou_bouton_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Nouveau_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Nouveau (suppression des elements de la table).
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Nouveau_MenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.purgeAll();
            propZJ = new List<int> { 10, 10, 10, 10, 10, 1 };
            ReinitialiserTout();
            FonctionsNatives.viderHistorique();
            Annuler_ToolStrip.Enabled = false;
            Retablir_ToolStrip.Enabled = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Nouveau_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des etats lorsque l'utilisateur garde un clic 
        ///        enfonce dans le panel GL.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseDown(object sender, MouseEventArgs e)
        {
            origin = panel_GL.PointToClient(MousePosition);
            previousP.X = e.X;
            previousP.Y = e.Y;
            currentP.X = e.X;
            currentP.Y = e.Y;

            if (etat is EtatEditeurSelection)
            {
                if (e.Button == MouseButtons.Left)
                {                    
                    int h = panel_GL.Height;
                    int w = panel_GL.Width;
                    bool b;
                    ((EtatEditeurSelection)etat).SourisSurObjet = FonctionsNatives.sourisEstSurObjet(currentP.X, currentP.Y, h, w, out b);
                    ((EtatEditeurSelection)etat).SourisSurSelection = b;
                    ((EtatEditeurSelection)etat).GaucheEnfonce = true;
                    etat.traiterSouris(e);              

                    panel_GL.MouseMove += new MouseEventHandler(panel_MouseMove);                   
                }
                else if (e.Button == MouseButtons.Right)
                    panel_GL.MouseMove += new MouseEventHandler(panel_MouseMove);                               
                
            }
            else if (etat is EtatEditeurPortail && e.Button == MouseButtons.Left)
            {
                sauvegarderHistorique();                
                FonctionsNatives.obligerTransparence(false);
                panel_GL.MouseMove -= panel_MouseMove;
                deselection();
                etaitEtatPortail = false;
                etat = new EtatEditeurSelection(this);
            }
            else if (etat is EtatEditeurMur)
            {
                sauvegarderHistorique();
                etat = new EtatEditeurSelection(this);
                deselection();
            }
            else if ((e.Button == MouseButtons.Left && (etat is EtatEditeurRotation ||
                                                        etat is EtatEditeurScale ||
                                                        etat is EtatEditeurZoom ||
                                                        etat is EtatEditeurDeplacement
                                                       )
                     )
                     || e.Button == MouseButtons.Right)
            {
                panel_GL.MouseMove += new MouseEventHandler(panel_MouseMove);
             
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_MouseMove(object sender, EventArgs e)
        /// @brief Gestion des etats lorsque l'utilisateur bouge la souris
        ///        sur le panel.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_MouseMove(object sender, MouseEventArgs e)
        {      
            currentP = panel_GL.PointToClient(MousePosition);

            if (nbSelection == 1 && !(etat is EtatEditeurDuplication) && (e.Button == MouseButtons.Left || e.Button == MouseButtons.Middle))
            {
                Xbox.Text = Math.Round(FonctionsNatives.getPositionX()).ToString();
                Ybox.Text = Math.Round(FonctionsNatives.getPositionY()).ToString();
                Anglebox.Text = Math.Round(FonctionsNatives.getAngle()).ToString();
                FMEbox.Text = (Math.Round(FonctionsNatives.getScale() * 100) / 100).ToString();
            }

            if (etat is EtatEditeurCreation || etat is EtatEditeurDuplication || etat is EtatEditeurDeplacement)
            {
                if (FonctionsNatives.duplicationEstHorsTable())
                    Cursor = Cursors.No;
                else
                    Cursor = Cursors.Arrow;
            }

            if (e.Button == MouseButtons.Right)
            {
                deplacementVueSouris(e);

            }          
            else if (!(clickValide(origin, currentP)) && etat is EtatEditeurSelection)
            {
                if (etaitEtatPortail)
                {
                    etaitEtatPortail = false;
                    panel_GL.MouseMove -= panel_MouseMove;
                }
                else
                {
                    int h = panel_GL.Height;
                    int w = panel_GL.Width;
                    bool b;
                    ((EtatEditeurSelection)etat).SourisSurObjet = FonctionsNatives.sourisEstSurObjet(origin.X, origin.Y, h, w, out b);
                    ((EtatEditeurSelection)etat).SourisSurSelection = b;
                    ((EtatEditeurSelection)etat).GaucheEnfonce = true;
                    etat.traiterSouris(e);

                    if (nbSelection > 0 && ((EtatEditeurSelection)etat).SourisSurSelection == true)
                    {
                        sauvegarderHistorique();
                        etat = new EtatEditeurDeplacement(this);
                    }
                    else if (!((EtatEditeurSelection)etat).SourisSurObjet)
                    {
                        etat = new EtatEditeurSelectionMultiple(this);
                        FonctionsNatives.initialiserRectangleElastique(origin.X, origin.Y);
                    }
                }
            }            
            else if (!(clickValide(origin, currentP)) && (etat is EtatEditeurZoom) && e.Button == MouseButtons.Left && ZoomElastique_ToolStrip.Enabled == true)
            {
                etat = new EtatEditeurZoomElastique(this);
                FonctionsNatives.initialiserRectangleElastique(origin.X, origin.Y);
            }

            if (!(etat is EtatEditeurSelectionMultiple) &&
                !(etat is EtatEditeurSelection) &&
                !(etat is EtatEditeurZoomElastique)
               )
            {
                etat.traiterSouris(e);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_MouseUp(object sender, EventArgs e)
        /// @brief Gestion des etats lorsque l'utilisateur relâche un clic de souris
        ///        dans le panel GL.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseUp(object sender, MouseEventArgs e)
        {
            Point destination = panel_GL.PointToClient(MousePosition);

            if (!(etat is EtatEditeurCreation) && !(etat is EtatEditeurDuplication))
            {
                panel_GL.MouseMove -= panel_MouseMove;               
            }

            if (etat is EtatEditeurDeplacement || etat is EtatEditeurScale || etat is EtatEditeurRotation)
                sauvegarderHistorique();

            if (etat is EtatEditeurDeplacement)
            {
                if (FonctionsNatives.duplicationEstHorsTable())
                    Annuler_ToolStrip_Click(sender, e);

                etat = new EtatEditeurSelection(this);
            }
            else if (etat is EtatEditeurSelection)
            {
                ((EtatEditeurSelection)etat).GaucheEnfonce = false;
                etat.traiterSouris(e);                
            }
            else if (etat is EtatEditeurDuplication && e.Button == MouseButtons.Left)
            {
                if (FonctionsNatives.duplicationEstHorsTable())
                    FonctionsNatives.removeObject();

                FonctionsNatives.sauvegarderHistorique();
                deselection();
                panel_GL.MouseMove -= panel_MouseMove;
                etat = new EtatEditeurSelection(this);
            }
            else if (etat is EtatEditeurCreation && e.Button == MouseButtons.Left)
            {    
                if (FonctionsNatives.duplicationEstHorsTable())
                {
                    FonctionsNatives.removeObject();
                    deselection();
                    panel_GL.MouseMove -= panel_MouseMove;
                    etat = new EtatEditeurSelection(this);
                }
                else
                {
                    if (myObjectName.ToString() == "portail")
                    {
                        creationObjet(true);
                        statePortail();
                    }
                    else if (myObjectName.ToString() == "mur")
                        stateMur();
                    else
                    {
                        sauvegarderHistorique();
                        deselection();
                        panel_GL.MouseMove -= panel_MouseMove;
                        etat = new EtatEditeurSelection(this);
                    }
                }       
            }
            else if (etat is EtatEditeurMur && (clickExtraValide(origin, destination)))
            {                
                deselection();                
                etat = new EtatEditeurSelection(this);
                return;
            }
            else if (e.Button == MouseButtons.Left)
            {
                if (etat is EtatEditeurZoomElastique)
                {
                    etat.traiterSouris(e);
                    etat = new EtatEditeurZoom(this);
                }
                else if (etat is EtatEditeurSelectionMultiple)
                {
                    etat.traiterSouris(e);
                    etat = new EtatEditeurSelection(this);
                }
                else if (clickValide(origin, destination) && !(etat is EtatEditeurSelection))
                {
                    etat.traiterSouris(e);
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_MouseUp(object sender, EventArgs e)
        /// @brief Gestion des etats lorsque l'utilisateur utilise la roulette
        ///        de la souris dans le panel GL.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseWheel(object sender, MouseEventArgs e)
        {
           // etat.traiterRoulette(e);
           // On peut zoomer avec la Roulette en tout temps
            zoomRoulette(e);

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void richTextBox1_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur
        ///        le label des infos sur les raccourcis.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void richTextBox1_Click(object sender, EventArgs e)
        {
            //Aide_MenuItem_Click(sender, e);
        }

        /* Fonctionnalites des etats */

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void deplacementSouris(MouseEventArgs e)
        /// @brief Gestion des etats lorsque l'utilisateur deplace la souris.
        /// 
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void deplacementSouris(MouseEventArgs e)
        {
            // On va calculer un point precedent et un point courrant pour faire le deplacement.

            // Ce point est dans les coordonnees d'affichage d'openGL pour pouvoir calculer un deplacement
            // en coordonnees du monde en utilisant convertirClotureAVirtuelle(...) comme ça on n'a pas 
            // besoin de ce facteur misterieux.  Et aussi, cette technique devrait bien marcher 
            // quand on sera rendu avec la vue orbite.
            if (etat is EtatEditeurDuplication || etat is EtatEditeurCreation)
                FonctionsNatives.deplacerSelection(previousP.X, previousP.Y, currentP.X, currentP.Y, true);
            else
                FonctionsNatives.deplacerSelection(previousP.X, previousP.Y, currentP.X, currentP.Y, true);
            
            previousP = currentP;
            currentP = panel_GL.PointToClient(MousePosition);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void deplacementVueSouris(MouseEventArgs e)
        /// @brief Gestion du deplacement de la vue avec la souris.
        /// 
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void deplacementVueSouris(MouseEventArgs e)
        {
            double deltaX = (-(currentP.X - previousP.X)) * 100.0 / panel_GL.Size.Width;
            double deltaY = ((currentP.Y - previousP.Y)) * 100.0 / panel_GL.Size.Height;
            FonctionsNatives.translater(deltaX, deltaY);

            previousP.X = currentP.X;
            previousP.Y = currentP.Y;
            currentP.X = e.X;
            currentP.Y = e.Y;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void scaleSouris(MouseEventArgs e)
        /// @brief Gestion du scaling d'un objet avec la souris.
        /// 
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void scaleSouris(MouseEventArgs e)
        {
            FonctionsNatives.agrandirSelection(previousP.X, previousP.Y, currentP.X, currentP.Y);
            previousP = currentP;
            currentP = panel_GL.PointToClient(MousePosition);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void zoomRoulette(MouseEventArgs e)
        /// @brief Gestion du zoom avec la roulette de la souris.
        /// 
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void zoomRoulette(MouseEventArgs e)
        {
            if (e.Delta > 0)
                FonctionsNatives.zoomIn();
            else if (e.Delta < 0)
                FonctionsNatives.zoomOut();
            currentZoom = FonctionsNatives.obtenirZoomCourant();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selection(EventArgs e)
        /// @brief Gestion de la selection d'objet avec la souris.
        /// 
        /// @param[in] e : evenement qui lance la fonction.
        /// @param[in] gaucheEnfonce : true si le bouton gauche de la souris est enfonce.
        /// @param[in] sourisSurSelection : true si la souris est sue la selection.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public int selection(MouseEventArgs e, bool gaucheEnfonce, bool sourisSurSelection)
        {
            int x = panel_GL.PointToClient(MousePosition).X;
            int y = panel_GL.PointToClient(MousePosition).Y;

            int h = panel_GL.Height;
            int w = panel_GL.Width;

            bool c = ctrlDown;
            int isSelected = nbSelection;

            nbSelection = FonctionsNatives.selectionnerObjetSousPointClique(x, y, h, w, c, gaucheEnfonce, sourisSurSelection);
            
            if (nbSelection != 1)
            {
                if (nbSelection == 0)
                {
                    outilsEnable(false);
                }
                else
                {
                    outilsEnable(true);
                }

                proprietesEnable(false);

                if (isSelected == 0)
                    playSound("no");
            }
            else
            {
                outilsEnable(true);
                proprietesEnable(true);
                Xbox.Text = Math.Round(FonctionsNatives.getPositionX()).ToString();
                Ybox.Text = Math.Round(FonctionsNatives.getPositionY()).ToString();
                Anglebox.Text = Math.Round(FonctionsNatives.getAngle()).ToString();
                FMEbox.Text = (Math.Round(FonctionsNatives.getScale() * 100) / 100).ToString();
            }

            return nbSelection;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void rectangleElastique()
        /// @brief Creation d'un rectangle elastique.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void rectangleElastique()
        {
            FonctionsNatives.rectangleElastique(currentP.X, currentP.Y);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void terminerRectangleElastique()
        /// @brief Effacement d'un rectangle elastique.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void terminerRectangleElastique()
        {
            FonctionsNatives.terminerRectangleElastique();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void selectionMultiple()
        /// @brief Selection multiple avec un rectangle elastique.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void selectionMultiple()
        {
            nbSelection = FonctionsNatives.selectionMultiple(ctrlDown);
            proprietesEnable(false);
            if (nbSelection == 0)
            {
                outilsEnable(false);
            }
            else
            {
                if (nbSelection == 1)
                {
                    proprietesEnable(true);
                    Xbox.Text = Math.Round(FonctionsNatives.getPositionX()).ToString();
                    Ybox.Text = Math.Round(FonctionsNatives.getPositionY()).ToString();
                    Anglebox.Text = Math.Round(FonctionsNatives.getAngle()).ToString();
                    FMEbox.Text = (Math.Round(FonctionsNatives.getScale() * 100) / 100).ToString();

                }
                outilsEnable(true);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void zoomElastique()
        /// @brief Selection multiple avec un rectangle elastique.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void zoomElastique()
        {
            Point destination = panel_GL.PointToClient(MousePosition);
            if (!altDown)
                FonctionsNatives.zoomInElastique(origin.X, origin.Y, destination.X, destination.Y);
            else if (altDown)
                FonctionsNatives.zoomOutElastique(origin.X, origin.Y, destination.X, destination.Y);
            currentZoom = FonctionsNatives.obtenirZoomCourant();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void dupliquerSelection()
        /// @brief Duplication des objets selectionnes.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void dupliquerSelection()
        {
            currentP = panel_GL.PointToClient(MousePosition);
            FonctionsNatives.dupliquerSelection(currentP.X, currentP.Y);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void creationObjet(bool twin = false)
        /// @brief Creation d'un objet.
        /// 
        /// @param[in] twin : Indique que l'objet n'est jumeau.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void creationObjet(bool twin = false)
        {
            FonctionsNatives.creerObjetAvecTests(myObjectName, myObjectName.Capacity, twin, colorShift,
                                                 panel_GL.PointToClient(MousePosition).X, panel_GL.PointToClient(MousePosition).Y, 
                                                 0, angleX, angleY, angleZ);      
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Enregistrer_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le menu Enregistrer.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Enregistrer_MenuItem_Click(object sender, EventArgs e)
        {
            if (pathXML.ToString() == "")
                EnregistrerSous();
            else
            {
                if (pathXML.ToString().Substring(pathXML.ToString().Length - 11) == "default.xml")
                {
                    MessageBox.Show("Il ne faut pas sauvegarder par dessus la zone par defaut", "ERREUR DE SAUVEGARDE",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    for (int i = 0; i < 6; i++)
                        prop[i] = propZJ[i];

                    int sauvegarde = FonctionsNatives.creerXML(pathXML, pathXML.Capacity, prop);
                    //Console.WriteLine(sauvegarde);
                    if (sauvegarde == 1)
                    {
                        MessageBox.Show("Vous ne pouvez pas sauvegarder la zone de jeu par defaut!", "ERREUR DE SAUVEGARDE",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        pathXML = new StringBuilder("");
                    }
                    else if (sauvegarde == 3 || sauvegarde == 0)
                    {
                        MessageBox.Show("Il doit avoir au moins un trou, un generateur de bille et un ressort dans la zone de jeu!", "ERREUR DE SAUVEGARDE",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        pathXML = new StringBuilder("");
                    }
                    else if (sauvegarde == 4)
                    {
                        MessageBox.Show("Tout les trous doivent etre au minimum de la taille de la plus grande bille (le plus gros generateur de billes) !", "ERREUR DE SAUVEGARDE",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        pathXML = new StringBuilder("");
                    }
                    else
                    {
                        takeScreenShot();
                    }

                    FonctionsNatives.viderHistorique();
                    Annuler_ToolStrip.Enabled = false;
                    Retablir_ToolStrip.Enabled = false;
                }
            }

            


        }



        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void proprietesEnable(bool active)
        /// @brief Active ou desactive les labels de proprietes spatiales des objets.
        /// 
        /// @param[in] active : Indique si les labels de proprietes spatiales seront accessibles.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void proprietesEnable(bool active)
        {
            Groupe_Proprietes.Visible = active;
            Xbox.Enabled = active;
            Ybox.Enabled = active;
            Anglebox.Enabled = active;
            FMEbox.Enabled = active;
            OK_prop_bouton.Enabled = active;
            Annuler_prop_boutn.Enabled = active;
            if (!active)
            {
                Xbox.Text = "";
                Ybox.Text = "";
                Anglebox.Text = "";
                FMEbox.Text = "";
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void outilsEnable(bool active)
        /// @brief Active ou desactive les boutons d'outils de modification de la table.
        /// 
        /// @param[in] active : Indique si les boutons d'outils de modification seront accessibles.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void outilsEnable(bool active)
        {
            bouton_Deplacement.Enabled = active;
            bouton_Suppression.Enabled = active;
            bouton_Rotation.Enabled = active;
            bouton_Scaling.Enabled = active;
            bouton_Duplication.Enabled = active;
            Duplication_MenuItem.Enabled = active;
            Rotation_MenuItem.Enabled = active;
            MiseE_MenuItem.Enabled = active;
            Deplacement_MenuItem.Enabled = active;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void menu1Enable(bool active)
        /// @brief Active ou desactive les menus.
        /// 
        /// @param[in] active : Indique si les menus seront accessibles.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void menu1Enable(bool active)
        {
            Nouveau_MenuItem.Enabled = active;
            Ouvrir_MenuItem.Enabled = active;
            Enregistrer_MenuItem.Enabled = active;
            EnregistrerS_MenuItem.Enabled = active;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private bool clickValide(Point origin, Point destination)
        /// @brief Indique si un click est considere comme valide.
        /// 
        /// @param[in] origin : Point d'origine du clic
        /// @param[in] destination : Position apres le clic. 
        /// 
        /// @return True si le click est valide (deplacement < 3pixels), False sinon.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private bool clickValide(Point origin, Point destination)
        {
            return ((Math.Abs(destination.X - origin.X) < 3)
                     &&
                    (Math.Abs(destination.Y - origin.Y) < 3));

        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private bool clickExtraValide(Point origin, Point destination)
        /// @brief Indique si un click est considere comme valide pour le mur avec plus grande marge de liberte.
        /// 
        /// @param[in] origin : Point d'origine du clic
        /// @param[in] destination : Position apres le clic. 
        /// 
        /// @return True si le click est valide (deplacement < 3pixels), False sinon.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private bool clickExtraValide(Point origin, Point destination)
        {
            return ((Math.Abs(destination.X - origin.X) < 30)
                     &&
                    (Math.Abs(destination.Y - origin.Y) < 30));

        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void tournerSelectionSouris(MouseEventArgs e)
        /// @brief Tourne les objets selectionnes.
        /// 
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void tournerSelectionSouris(MouseEventArgs e)
        {
            FonctionsNatives.tournerSelectionSouris(previousP.X, previousP.Y, currentP.X, currentP.Y);
            previousP = currentP;
            currentP = panel_GL.PointToClient(MousePosition);
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void deselection()
        /// @brief Deselectionne tous les objets.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void deselection()
        {
            FonctionsNatives.deselectAll();

            nbSelection = 0;
            proprietesEnable(false);
            outilsEnable(false);
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void trackCursor(bool enable)
        /// @brief Active ou desactive le tracking de la souris.
        /// 
        /// @param[in] enable : Determine si le tracking est active ou desactive.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void trackCursor(bool enable)
        {
            if (enable)
            {
                panel_GL.MouseMove += new MouseEventHandler(panel_MouseMove);
            }
            else
            {
                panel_GL.MouseMove -= new MouseEventHandler(panel_MouseMove);
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void playSound(String name, bool stop = false)
        /// @brief Joue un son.
        /// 
        /// @param[in] name : Nom du media.
        /// @param[in] stop : (false) La lecture n'arrete pas.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void playSound(String name, bool stop = false)
        {
            StringBuilder music = new StringBuilder(name);
            FonctionsNatives.jouerSon(music, music.Capacity, stop);
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Creation_Panel_MouseEnter(object sender, EventArgs e)
        /// @brief Gestion des evenements de zoom lorsque la souris entre dans le panel de creation.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Creation_Panel_MouseEnter(object sender, EventArgs e)
        {
            Cursor = Cursors.Arrow;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_MouseLeave(object sender, EventArgs e)
        /// @brief Gestion des evenements de zoom lorsque la souris quitte le panel GL.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseLeave(object sender, EventArgs e)
        {
            Cursor = Cursors.Arrow;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void enableZoom(bool active)
        /// @brief Active ou desactive le zoom.
        /// 
        /// @param[in] active : Indique si le zoom est accessible.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void enableZoom(bool active)
        {
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void statePortail()
        /// @brief Entre en etat Portail.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void statePortail()
        {
            etat = new EtatEditeurPortail(this);
            panel_GL.MouseMove += new MouseEventHandler(panel_MouseMove);
            etaitEtatPortail = true;
        }
        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void stateMur()
        /// @brief Entre en etat Mur.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void stateMur()
        {
            etat = new EtatEditeurMur(this);
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void creationMur()
        /// @brief Fonction qui s'assure de la bonne creation des murs.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void creationMur()
        {
            FonctionsNatives.creerMur(origin.X, origin.Y, previousP.X, previousP.Y, currentP.X, currentP.Y);
            //  Console.WriteLine(FonctionsNatives.getScale());
            previousP = currentP;
            currentP = panel_GL.PointToClient(MousePosition);
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void IncreaseZoomButton_Click(object sender, EventArgs e) 
        /// @brief Fonction qui incremente le Zoom.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void IncreaseZoomButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.zoomIn();
            currentZoom = FonctionsNatives.obtenirZoomCourant();

        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void DecreaseZoomButton_Click(object sender, EventArgs e)
        /// @brief Fonction qui decremente le Zoom.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void DecreaseZoomButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.zoomOut();
            currentZoom = FonctionsNatives.obtenirZoomCourant();
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void annulerModif()
        /// @brief Fonction qui detruit un objet si on change d'etat pendant la modification
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void annulerModif()
        {
            if (etat is EtatEditeurPortail ||  etat is EtatEditeurCreation || etat is EtatEditeurDuplication)
            {
                FonctionsNatives.removeObject();
                panel_GL.MouseMove -= panel_MouseMove;
                deselection();
                etat = new EtatEditeurSelection(this);
            }
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void label_Zoom_Click(object sender, EventArgs e)
        /// @brief Fonction qui selectionne le mode Zoom
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void label_Zoom_Click(object sender, EventArgs e)
        {
            Zoom_MenuItem_Click(this, e);
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void label_Zoom_MouseEnter(object sender, EventArgs e)
        /// @brief Fonction qui change la couleur du label quand on est pardessus
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void label_Zoom_MouseEnter(object sender, EventArgs e)
        {
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void label_Zoom_MouseLeave(object sender, EventArgs e)
        /// @brief Fonction qui change la couleur du label quand on sort du label
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void label_Zoom_MouseLeave(object sender, EventArgs e)
        {
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void outilCourant(string outil)
        /// @brief Ecrit le nom de l'outil courant dans le label prevu a cet effet.
        /// @param[in] outil : Nom de l'outil selectionne.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void outilCourant(string outil)
        {
            labelOCourant.Text = outil;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void flowLayoutPanel1_SizeChanged(object sender, EventArgs e)
        /// @brief Ajustement des dimensions lorsque la taille du flowlayout panel est changee.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : Evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void flowLayoutPanel1_SizeChanged(object sender, EventArgs e)
        {
            richTextBox1.Height = flowLayoutPanel1.Height - 500;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_SizeChanged(object sender, EventArgs e)
        /// @brief Ajustement des dimensions du UI lorsque la taille du panel GL change.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : Evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void panel_GL_SizeChanged(object sender, EventArgs e)
        {
            mouvementX = 100 * (double)(this.flowLayoutPanel1.Width) / (double)this.panel1.Width;
            mouvementY = 100 * (double)(this.menuStrip1.Height+this.toolStrip1.Height) / (double)this.panel1.Width;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void toolStripMenuItem1_Click(object sender, EventArgs e)
        /// @brief Retourne au mode d'edition a partir du mode test.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            etat = null;
            etat = new EtatEditeurSelection(this);

            FonctionsNatives.animerJeu(false);
            FonctionsNatives.rechargerArbre(true);
            FonctionsNatives.supprimerBille();
            FonctionsNatives.resetNombreBillesCourantes();

            if (menuStrip3.Visible)
                menuStrip3.Hide();
            menuStrip1.Show();
            toolStrip1.Show();
            Annuler_ToolStrip.Enabled = true;
            Retablir_ToolStrip.Enabled = true;
            SelectAll_MenuItem.Enabled = true;
            bouton_Creation.Show();
            menu1Enable(true);
            Creation_Panel.Show();
            flowLayoutPanel1.Show();
            panel_GL.Anchor = (AnchorStyles.Top | AnchorStyles.Left);
            panel_GL.Location = new Point(163, 24);
            panel_GL.Dock = DockStyle.Fill;
            if (!FonctionsNatives.cameraEstOrbite())
                FonctionsNatives.translater(mouvementX, -mouvementY);
            FonctionsNatives.mettreAJourListeBillesEtNoeuds();
            FonctionsNatives.modePause(false);
            Program.myCustomConsole.Hide();
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void testRetourMenuPrincipal_Click(object sender, EventArgs e)
        /// @brief Retour au menu principal a partir du mode test.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void testRetourMenuPrincipal_Click(object sender, EventArgs e)
        {
            Program.myCustomConsole.Hide();
            this.Close();
        }
        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Editeur_Shown(object sender, EventArgs e)
        /// @brief Affichage de console custom lorsqu'on entre en mode Editeur.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Editeur_Shown(object sender, EventArgs e)
        {
            updateFrame = true;
            Program.myCustomConsole.reStart();
            Program.myCustomConsole.Update();
            if (Program.mMenu.modeEdit != null)
                Program.mMenu.modeEdit.Focus();

          
            
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Enregistrer_ToolStrip_Click(object sender, EventArgs e)
        /// @brief Appel de la fonction d'enregistrement.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Enregistrer_ToolStrip_Click(object sender, EventArgs e)
        {
            Enregistrer_MenuItem.PerformClick();
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Information_MenuItem_Click(object sender, EventArgs e)
        /// @brief Affichage du menu aide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Information_MenuItem_Click(object sender, EventArgs e)
        {
            Aide aide = new Aide();
            aide.StartPosition = FormStartPosition.CenterScreen;
            aide.ShowDialog();
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void button_delete_Click(object sender, EventArgs e)
        /// @brief Affichage de la fonction supprimer.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void button_delete_Click(object sender, EventArgs e)
        {

        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MenuP_ToolStrip_Click(object sender, EventArgs e)
        /// @brief Appel de la fonction MenuPrincipal.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void MenuP_ToolStrip_Click(object sender, EventArgs e)
        {
            MenuP_MenuItem.PerformClick();
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Nouveau_Click(object sender, EventArgs e)
        /// @brief Appel de la fonction Nouveau.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Nouveau_Click(object sender, EventArgs e)
        {
            Nouveau_MenuItem.PerformClick();
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Ouvrir_Click(object sender, EventArgs e)
        /// @brief Appel de la fonction Ouvrir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Ouvrir_Click(object sender, EventArgs e)
        {
            Ouvrir_MenuItem.PerformClick();
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void EnregistrerSous_ToolStrip_Click(object sender, EventArgs e)
        /// @brief Appel de la fonction Enregistrer Sous.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void EnregistrerSous_ToolStrip_Click(object sender, EventArgs e)
        {
            EnregistrerS_MenuItem.PerformClick();
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Proprietes_ToolStrip_Click(object sender, EventArgs e)
        /// @brief Appel des Proprietes de la zone de jeu.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Proprietes_ToolStrip_Click(object sender, EventArgs e)
        {
            Proprietes_MenuItem.PerformClick();
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ModeTest_ToolStrip_Click(object sender, EventArgs e)
        /// @brief Passage au mode Test.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void ModeTest_ToolStrip_Click(object sender, EventArgs e)
        {
            ModeTest_MenuItem.PerformClick();
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ZoomIn_ToolStrip_Click(object sender, EventArgs e)
        /// @brief Zoom in.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void ZoomIn_ToolStrip_Click(object sender, EventArgs e)
        {
            FonctionsNatives.zoomIn();
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ZoomOut_ToolStrip_Click(object sender, EventArgs e)
        /// @brief Zoom out.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void ZoomOut_ToolStrip_Click(object sender, EventArgs e)
        {
            FonctionsNatives.zoomOut();
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Suppression_Click(object sender, EventArgs e)
        /// @brief Appel de la fonction Supprimer.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void bouton_Suppression_Click(object sender, EventArgs e)
        {
            if (etat is EtatEditeurSelection)
                sauvegarderHistorique();

            FonctionsNatives.removeObject();
            deselection();

            sauvegarderHistorique();
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Group_Butoir_Enter(object sender, EventArgs e)
        /// @brief Rien.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Group_Butoir_Enter(object sender, EventArgs e)
        {

        }


        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Group_Elements_Enter(object sender, EventArgs e)
        /// @brief Rien.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Group_Elements_Enter(object sender, EventArgs e)
        {

        }


        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Groupe_Proprietes_Enter(object sender, EventArgs e)
        /// @brief Rien.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Groupe_Proprietes_Enter(object sender, EventArgs e)
        {

        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ZoomElastique_ToolStrip_Click(object sender, EventArgs e)
        /// @brief Passage au mode Zoom.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void ZoomElastique_ToolStrip_Click(object sender, EventArgs e)
        {
            Zoom_MenuItem.PerformClick();
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Annuler_ToolStrip_Click(object sender, EventArgs e)
        /// @brief Appel a la fonction Annuler( UNDO ).
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Annuler_ToolStrip_Click(object sender, EventArgs e)
        {
            deselection();
            FonctionsNatives.annulerModifications();
            nbSelection = FonctionsNatives.obtenirNombreSelection();
            outilsEnable(true);

            if (nbSelection == 1)
            {
                proprietesEnable(true);
                Xbox.Text = Math.Round(FonctionsNatives.getPositionX()).ToString();
                Ybox.Text = Math.Round(FonctionsNatives.getPositionY()).ToString();
                Anglebox.Text = Math.Round(FonctionsNatives.getAngle()).ToString();
                FMEbox.Text = (Math.Round(FonctionsNatives.getScale() * 100) / 100).ToString();
            }

            else
                proprietesEnable(false);

            etat = new EtatEditeurSelection(this);

            Annuler_ToolStrip.Enabled = (FonctionsNatives.possedePrecedent());
            Retablir_ToolStrip.Enabled = (FonctionsNatives.possedeSuivant());
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Retablir_ToolStrip_Click(object sender, EventArgs e)
        /// @brief Appel a la fonction Retablir( REDO ).
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Retablir_ToolStrip_Click(object sender, EventArgs e)
        {
            deselection();
            FonctionsNatives.retablirModifications();
            nbSelection = FonctionsNatives.obtenirNombreSelection();
            outilsEnable(true);

            if (nbSelection == 1)
            {
                proprietesEnable(true);
                Xbox.Text = Math.Round(FonctionsNatives.getPositionX()).ToString();
                Ybox.Text = Math.Round(FonctionsNatives.getPositionY()).ToString();
                Anglebox.Text = Math.Round(FonctionsNatives.getAngle()).ToString();
                FMEbox.Text = (Math.Round(FonctionsNatives.getScale() * 100) / 100).ToString();
            }

            else
                proprietesEnable(false);

            etat = new EtatEditeurSelection(this);

            Annuler_ToolStrip.Enabled = (FonctionsNatives.possedePrecedent());
            Retablir_ToolStrip.Enabled = (FonctionsNatives.possedeSuivant());
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Supprimer_MenuItem_Click_1(object sender, EventArgs e)
        /// @brief Appel a la fonction Supprimer.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Supprimer_MenuItem_Click_1(object sender, EventArgs e)
        {
            bouton_Suppression.PerformClick();
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Annuler_MenuItem_Click(object sender, EventArgs e)
        /// @brief Appel a la fonction Annuler.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Annuler_MenuItem_Click(object sender, EventArgs e)
        {
            Annuler_ToolStrip.PerformClick();
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Retablir_MenuItem_Click(object sender, EventArgs e)
        /// @brief Appel a la fonction Retablir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Retablir_MenuItem_Click(object sender, EventArgs e)
        {
            Retablir_ToolStrip.PerformClick();
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void sauvegarderHistorique()
        /// @brief Sauvegarde l'historique des manipulations.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void sauvegarderHistorique()
        {
            FonctionsNatives.sauvegarderHistorique();
            Annuler_ToolStrip.Enabled = true;
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void SelectAll_MenuItem_Click(object sender, EventArgs e)
        /// @brief Appel a la fonction Selectionner Tout.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void SelectAll_MenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.selectAll();
            nbSelection = FonctionsNatives.obtenirNombreSelection();
            outilsEnable(true);
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PGJ1_bouton_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void PGJ1_bouton_Leave(object sender, EventArgs e)
        {
            PGJ1_bouton.FlatAppearance.BorderColor = Color.Black;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PDJ1_bouton_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void PDJ1_bouton_Leave(object sender, EventArgs e)
        {
            PDJ1_bouton.FlatAppearance.BorderColor = Color.Black;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PGJ2_bouton_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void PGJ2_bouton_Leave(object sender, EventArgs e)
        {
            PGJ2_bouton.FlatAppearance.BorderColor = Color.Black;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PDJ1_bouton_Leave_1(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void PDJ1_bouton_Leave_1(object sender, EventArgs e)
        {
            PDJ1_bouton.FlatAppearance.BorderColor = Color.Black;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PGJ2_bouton_Leave_1(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void PGJ2_bouton_Leave_1(object sender, EventArgs e)
        {
            PGJ2_bouton.FlatAppearance.BorderColor = Color.Black;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PDJ2_bouton_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void PDJ2_bouton_Leave(object sender, EventArgs e)
        {
            PDJ2_bouton.FlatAppearance.BorderColor = Color.Black;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void butoirG_bouton_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void butoirG_bouton_Leave(object sender, EventArgs e)
        {
            butoirG_bouton.FlatAppearance.BorderColor = Color.Black;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void butoirD_bouton_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void butoirD_bouton_Leave(object sender, EventArgs e)
        {
            butoirD_bouton.FlatAppearance.BorderColor = Color.Black;

        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void butoirCirc_bouton_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void butoirCirc_bouton_Leave(object sender, EventArgs e)
        {
            butoirCirc_bouton.FlatAppearance.BorderColor = Color.Black;

        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Cible_bouton_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Cible_bouton_Leave(object sender, EventArgs e)
        {
            Cible_bouton.FlatAppearance.BorderColor = Color.Black;

        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Mur_bouton_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Mur_bouton_Leave(object sender, EventArgs e)
        {
            Mur_bouton.FlatAppearance.BorderColor = Color.Black;

        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Portails_bouton_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Portails_bouton_Leave(object sender, EventArgs e)
        {
            Portails_bouton.FlatAppearance.BorderColor = Color.Black;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Gate_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Gate_Leave(object sender, EventArgs e)
        {
            Gate.FlatAppearance.BorderColor = Color.Black;

        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Ressort_bouton_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Ressort_bouton_Leave(object sender, EventArgs e)
        {
            Ressort_bouton.FlatAppearance.BorderColor = Color.Black;

        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Generateur_bouton_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Generateur_bouton_Leave(object sender, EventArgs e)
        {
            Generateur_bouton.FlatAppearance.BorderColor = Color.Black;

        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Trou_bouton_Leave(object sender, EventArgs e)
        /// @brief Remet la bordure a noir.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Trou_bouton_Leave(object sender, EventArgs e)
        {
            Trou_bouton.FlatAppearance.BorderColor = Color.Black;

        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            Orthographique_MenuItem_Click(sender, e);
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            Orbite_MenuItem_Click(sender, e);
        }

    }
}
