﻿//////////////////////////////////////////////////////////////////////////////
/// @file Exemple.cs
/// @author Ballers
/// @date 2015-01-13
/// @version 1.0 
///
/// @ingroup InterfaceGraphique
//////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Media;
using System.IO;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Exemple
    /// @brief Main window de l'éditeur du jeu.
    ///
    /// @author The Ballers
    /// @date 2015-01-13
    /// 
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    public partial class Exemple : Form
    {
        FullScreen fs = new FullScreen();
        static public StringBuilder myObjectName = new StringBuilder("vide");
   
        public Point origin;
        
        public Point previousP, currentP;
        
        public int panelHeight; ///< Hauteur de la fenetre
        public int panelWidth; ///< Largeur de la fenetre
        private bool ctrlDown = false;
        private bool altDown = false;
        public List<int> propZJ = new List<int> { 10, 10, 10, 10, 10, 1 }; ///< Une liste de choses
        private float angleX = 0F; ///< Position en X
        private float angleY = 0F; ///< Position en Y
        private float angleZ = 0F; ///< Position en Z
        private float scale = 1F; ///< Mise a echelle
        private int currentZoom = 5; ///< Zoom courant
        private int previousZoom = 5; ///< Zoom precedent
        private int nbSelection;
        private bool colorShift = false;
        private StringBuilder pathXML = new StringBuilder(""); ///< Chemin pour la lecture/sauvegarde XML
        private Etat etat { get; set; } ///< Machine a etat
        private int[] prop = new int[6]; ///< Proprietes du jeu a sauvegarder

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn static public Exemple()
        /// @brief Constructeur de la fenêtre.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public Exemple()
        {
            this.KeyPreview = true;
            this.KeyPress += new KeyPressEventHandler(ToucheEnfonce);
            // Pour le deplacement de la vue
            // besoin de nouveau event parce que C#....
            this.KeyDown += new KeyEventHandler(ToucheDown);
            this.KeyUp += new KeyEventHandler(ToucheUp);
            this.Icon = Properties.Resources.Pinball;
            InitializeComponent();
            Program.peutAfficher = true;
            etat = new EtatNone(this);
            panel_GL.Select();
            
            InitialiserAnimation();
            
            panelHeight = panel_GL.Size.Height;
            panelWidth = panel_GL.Size.Width;
            etat = new EtatNone(this);

            //Musique
            playSound("music");
            playSound("stone"); // Pause probleme quand on ferme puis rouvre la fenetre
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
            FonctionsNatives.dessinerOpenGL();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void MettreAJour(double tempsInterAffichage)
        /// @brief Taches effectuées lors d'un rafraichissement d'écran.
        /// 
        /// @param[in] tempsInterAffichage : Temps entre deux affichages.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    if (etat is EtatSelectionMultiple)
                        rectangleElastique();

                    else if (etat is EtatZoomElastique)
                        rectangleElastique();
                    else
                    {
                        FonctionsNatives.animer(tempsInterAffichage);
                        FonctionsNatives.dessinerOpenGL();
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
        /// @brief Gestion des états lorsqu'une touche est enfoncée.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ToucheDown(Object o, KeyEventArgs e)
        {
            if (etat is EtatZoom)
            {
                if ((e.KeyData == Keys.Subtract ||
                   e.KeyCode == Keys.OemMinus)
                   && zoom_Bar.Value > 0)
                {
                    FonctionsNatives.zoomOut();
                    zoom_Bar.Value -= 1;
                    currentZoom = zoom_Bar.Value;
                    previousZoom = zoom_Bar.Value;
                }
                if ((e.KeyData == Keys.Add ||
                    e.KeyCode == Keys.Oemplus && e.Modifiers == Keys.Shift)
                    && zoom_Bar.Value < 12)
                {
                    FonctionsNatives.zoomIn();
                    zoom_Bar.Value += 1;
                    currentZoom = zoom_Bar.Value;
                    previousZoom = zoom_Bar.Value;
                }
                if (e.KeyData == Keys.Alt)
                    altDown = true;

            }
               
                if (e.KeyData == Keys.Left)
                    FonctionsNatives.translater(-10, 0);

                if (e.KeyData == Keys.Right)
                    FonctionsNatives.translater(10, 0);

                if (e.KeyData == Keys.Up)
                    FonctionsNatives.translater(0, 10);

                if (e.KeyData == Keys.Down)
                    FonctionsNatives.translater(0, -10);
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
        /// @fn private void ToucheUp(Object o, KeyEventArgs e)
        /// @brief Gestion des états lorsqu'une touche est relâchée.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
            if (e.KeyData.ToString() == "ControlKey")
            {
                ctrlDown = false;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ToucheEnfonce(Object o, KeyPressEventArgs e)
        /// @brief Gestion des états lorsqu'une touche est enfoncée.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ToucheEnfonce(Object o, KeyPressEventArgs e)
        {

            if( e.KeyChar == (char)Keys.Escape)
            {
                if (etat is EtatPortail)
                {
                    FonctionsNatives.removeObject();
                }
                etat = null;
                etat = new EtatNone(this);
                deselection();
            }
            if (e.KeyChar == 'f')
            {
                if (fs.IsFullScreen(this))
                {
                    fs.LeaveFullScreenMode(this);
                }
                else
                    fs.EnterFullScreenMode(this);
            }
            if (e.KeyChar == 's')
            {
                Selection_MenuItem_Click(this, e);
       
            }
            if( e.KeyChar == 'd')
            {
                etat = null;
                etat = new EtatDeplacement(this);
         
                
              
            }
            if (e.KeyChar == 'e')
            {
                etat = null;
                etat = new EtatScale(this);
        
                
              
            }
            if( e.KeyChar == 'r')
            {
                etat = null;
                etat = new EtatRotation(this);
           
            }
           
            if (e.KeyChar == 'z')
            {
                etat = null;
                etat = new EtatZoom(this);
          
                
            }
            if (e.KeyChar == 'c')
            {
                bouton_Duplication_Click(this, e);
               
            }
            if (e.KeyChar == 'h')
            {
                if (label1.Visible)
                    label1.Hide();
                else
                    label1.Show();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn  private void Exemple_FormClosing(object sender, FormClosingEventArgs e)
        /// @brief Gestion des événements lorsque la fenêtre est fermée.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Exemple_FormClosing(object sender, FormClosingEventArgs e)
        {
            lock (Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;
            }
            playSound("", true);    // Stop le son
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Aide_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Aide.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Aide_MenuItem_Click(object sender, EventArgs e)
        {
            BackgroundWorker bw = new BackgroundWorker();
            bw.WorkerReportsProgress = true;
            bw.DoWork += new DoWorkEventHandler(
            delegate (object o, DoWorkEventArgs args)
            {
                Aide aide = new Aide();
                aide.StartPosition = FormStartPosition.CenterScreen;
                aide.ShowDialog();
            });
            bw.RunWorkerAsync();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Ouvrir_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Ouvrir.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Ouvrir_MenuItem_Click(object sender, EventArgs e)
        {

            OpenFileDialog ouvrir_fichier = new OpenFileDialog();
            ouvrir_fichier.Filter = "Fichier XML(*.xml)| *.xml| All files(*.*)|*.*";
            string initPath = Application.StartupPath + @"\Zones_de_jeu";
            ouvrir_fichier.InitialDirectory = Path.GetFullPath(initPath);
            ouvrir_fichier.RestoreDirectory = true;
            if (ouvrir_fichier.ShowDialog() == DialogResult.OK)
            {
               
                    pathXML = new StringBuilder(ouvrir_fichier.FileName);

                    IntPtr prop = FonctionsNatives.ouvrirXML(pathXML, pathXML.Capacity);
                    int[] result = new int[6];
                    Marshal.Copy(prop, result, 0, 6);

                    for (int i = 0; i < 6; i++)
                        propZJ[i] = result[i];
               
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void EnregistrerS_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Enregistrer.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Enregistrement des propriétés de la partie en format XML.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void EnregistrerSous()
        {
            int sauvegarde = FonctionsNatives.creerXML(pathXML, pathXML.Capacity, prop);

            if (sauvegarde == 0)
            {
                MessageBox.Show("Il doit avoir au moins un trou, un générateur de bille et un ressort dans la zone de jeu!", "ERREUR DE SAUVEGARDE",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            else if (sauvegarde == 2)
            {
                SaveFileDialog enregistrer_fichier = new SaveFileDialog();
                enregistrer_fichier.Filter = "Fichier XML(*.xml)| *.xml| All files(*.*)|*.*";
                
                //Console.WriteLine(initial);
                string initPath = Application.StartupPath + @"\Zones_de_jeu";
                enregistrer_fichier.InitialDirectory = Path.GetFullPath(initPath);
                enregistrer_fichier.RestoreDirectory = true;
                enregistrer_fichier.OverwritePrompt = false;
                enregistrer_fichier.ShowDialog();
                
                string fileName = Path.GetFileName(enregistrer_fichier.FileName);
                Console.WriteLine(fileName);

                if (!(fileName == "default.xml"))
                {
                    enregistrer_fichier.OverwritePrompt = true;
                    pathXML = new StringBuilder(enregistrer_fichier.FileName);
                    for (int i = 0; i < 6; i++)
                        prop[i] = propZJ[i];

                    FonctionsNatives.creerXML(pathXML, pathXML.Capacity, prop);
                }

                else
                {
                    MessageBox.Show("Vous ne pouvez pas sauvegarder sur la zone de jeu par défaut!", "ERREUR DE SAUVEGARDE",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }

            else
            {
                MessageBox.Show("Vous ne pouvez pas sauvegarder la zone de jeu par défaut!", "ERREUR DE SAUVEGARDE",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void helpToolStripButton_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        l'outil Aide.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Creation.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le panel1 (écriture des coord. sur la console).
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel1_Click(object sender, EventArgs e)
        {
            Console.Write(this.PointToClient(MousePosition));
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Selection_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Sélection.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Sélection.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Rotation.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Rotation.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Sélection.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Selection_Click(object sender, EventArgs e)
        {
            etat = new EtatSelection(this);

            Console.WriteLine("Outil Selection.");
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Creation_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Création.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Creation_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Creation.");
            if (Creation_Panel.Visible)
                Creation_Panel.Visible = false;
            else
                Creation_Panel.Visible = true;

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_MouseClick(object sender, MouseEventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le panel GL (écriture des coord. sur la console).
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseClick(object sender, MouseEventArgs e)
        {
            Console.Write(panel_GL.PointToClient(MousePosition));
            panel_GL.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void butourCirc_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Butoir Circulaire.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void butourCirc_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("ButoirCirculaire");
            myObjectName = new StringBuilder("butoircirculaire");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Proprietes_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Propriétés.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Butoir Gauche.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void butoirG_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Butoir Gauche.");
            myObjectName = new StringBuilder("butoir");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 180;

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void OK_prop_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton OK des propriétés.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void OK_prop_bouton_Click(object sender, EventArgs e)
        {
          
            /*  FonctionsNatives.deplacerSelection(
                FonctionsNatives.getPositionX(),
                FonctionsNatives.getPositionY(),
                Convert.ToInt32(Xbox.Text), 
                Convert.ToInt32(Ybox.Text));
            
                (Ajuste le header s'il y a lieu.)
            */
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void afficher_Objet(bool twin)
        /// @brief Affiche et crée un objet jumeau.
        /// 
        /// @param[in] bool : Objet jumeau.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void afficher_Objet(bool twin)
        {
            Console.WriteLine(myObjectName);
            FonctionsNatives.creerObjet(myObjectName, myObjectName.Capacity, twin, colorShift);
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
        /// @fn public void Scale_Objet()
        /// @brief Logique de mise à échelle d'un objet par les text boxes.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Scale_Objet()
        {
            string scalingRead = FMEbox.Text;
            scalingRead = scalingRead.Replace(",", ".");
            float scale;

            if (FMEbox.Text == "")
                FMEbox.Text = "1"; ;

            DataTable dt = new DataTable();
            try { scalingRead = dt.Compute(scalingRead, "").ToString(); }
            catch { return; }

            if (!float.TryParse(scalingRead, out scale))
                return;

            if (scale < 0)
                return;

            FonctionsNatives.scaleObjet(scale);
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
        /// @brief Gestion des événements lorsque l'utilisateur redimensionne
        ///        la fenêtre.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Fenetre_Redimension(object sender, EventArgs e)
        {
            Console.Write("Width to send : " + panel_GL.Width.ToString() + "\n" + "Height to send : " + panel_GL.Height.ToString() + "\n");
            FonctionsNatives.redimensionnerFenetre(panel_GL.Width == 0 ? 1 : panel_GL.Width, panel_GL.Height == 0 ? 1 : panel_GL.Height);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Annuler_prop_boutn_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Annuler des propriétés.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Annuler_prop_boutn_Click(object sender, EventArgs e)
        {
            Xbox.Text = Math.Round(FonctionsNatives.getPositionX()).ToString();
            Ybox.Text = Math.Round(FonctionsNatives.getPositionY()).ToString();
            Anglebox.Text = Math.Round(FonctionsNatives.getAngle()).ToString();
            FMEbox.Text = FonctionsNatives.getScale().ToString();
        }


        private void Exemple_Load(object sender, EventArgs e)
        {

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Ressort_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Ressort.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Ressort_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Ressort");
            myObjectName = new StringBuilder("ressort");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Generateur_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Générateur de bille.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Generateur_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Generateur");
            myObjectName = new StringBuilder("generateurbille");
            colorShift = false;
            angleX = 0;
            angleY = 0;// 90;
            angleZ = 0;//180;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Trou_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Trou.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Trou_bouton_Click(object sender, EventArgs e)
        {
            
            etat = new EtatCreation(this);
            Console.WriteLine("Trou");
            myObjectName = new StringBuilder("trou");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Deplacement_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Déplacement.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Deplacement_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Deplacement.");
            // TO DO
            etat = null;
            etat = new EtatDeplacement(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Deplacement_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Déplacement.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Deplacement_MenuItem_Click(object sender, EventArgs e)
        {
            bouton_Deplacement_Click(this, e);
        }

        private void MenuP_MenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Rotation_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Rotation.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Rotation_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Rotation.");
            // TO DO
            etat = null;
            etat = new EtatRotation(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Scaling_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Scaling.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Scaling_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Mise a echelle.");
            // TO DO
            etat = null;
            etat = new EtatScale(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MiseE_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu MiseE.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Zoom.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Zoom_MenuItem_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Zoom.");
            
            etat = null;
            etat = new EtatZoom(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Duplication_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Duplication.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Duplication_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Duplication.");
            // TO DO
            etat = null;
            etat = new EtatDuplication(this);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Duplication_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Duplication.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Création.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Creation_MenuItem_Click(object sender, EventArgs e)
        {
            bouton_Creation_Click(this, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void BC_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu BC.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void BC_MenuItem_Click(object sender, EventArgs e)
        {
            butourCirc_bouton_Click(this, e);
        }

        private void Orthographique_MenuItem_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Vue Orthoraphique.");
            // TO DO
        }

        private void Orbite_MenuItem_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Vue Orbitale.");
            // TO DO
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Supprimer_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Supprimer.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Supprimer_MenuItem_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Supprimer.");
            FonctionsNatives.removeObject();
            // TO DO
        }

        private void ModeTest_MenuItem_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Mode Test.");
            // TO DO
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PGJ1_bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Palette Gauche J1.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PGJ1_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Palette gauche J1.");
            myObjectName = new StringBuilder("palette");
            angleX = 180;
            angleY = 0;
            angleZ = 180;
            colorShift = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PG_J1_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Palette Gauche J1.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Palette Droite J1.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PDJ1_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Palette droite J1.");
            myObjectName = new StringBuilder("palette");
            angleX = 180;
            angleY = 0;
            angleZ = 0;
            colorShift = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PD_J1_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Palette Droite J1.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Palette Gauche J2.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PGJ2_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Palette gauche J2.");
            myObjectName = new StringBuilder("palette");
            colorShift = true;
            angleX = 180;
            angleY = 0;
            angleZ = 180;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PG_J2_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Palette Gauche J2.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Palette Droite J2.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PDJ2_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Palette droite J2.");
            myObjectName = new StringBuilder("palette");
            colorShift = true;
            angleX = 180;
            angleY = 0;
            angleZ = 0;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PD_J2_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Palette Droite J2.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Butoir Gauche.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Butoir Droit.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void butoirD_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Butoir Droit.");
            myObjectName = new StringBuilder("butoir");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void BTD_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Butoir Droit.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Cible.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Cible_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Cible.");
            myObjectName = new StringBuilder("cible");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Cible_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Cible.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Portail.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Portails_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Portail");
            myObjectName = new StringBuilder("portail");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Portails_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Portail.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le bouton Mur.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Mur_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Mur");
            myObjectName = new StringBuilder("mur");
            colorShift = false;
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Mur_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Mur.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Ressort.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Générateur de bille.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Trou.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Nouveau (suppression des éléments de la table).
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Nouveau_MenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.purgeAll();
            propZJ = new List<int> { 10, 10, 10, 10, 10, 1 };
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Nouveau_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des états lorsque l'utilisateur garde un clic 
        ///        enfoncé dans le panel GL.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseDown(object sender, MouseEventArgs e)
        {
            origin = panel_GL.PointToClient(MousePosition);
            //if( !(etat is EtatCreation))
            //    panel_GL.MouseMove += new MouseEventHandler(panel_MouseMove);   
            if (etat is EtatPortail && e.Button == MouseButtons.Left)
            {
              etat = new EtatNone(this);
              FonctionsNatives.obligerTransparence(false);
             deselection();
            }
          
               
            if (e.Button == MouseButtons.Left)
                sourisBoutonGaucheActive = true;

            previousP.X = e.X;
            previousP.Y = e.Y;
            currentP.X = e.X;
            currentP.Y = e.Y;

            if (e.Button == MouseButtons.Left &&
            (etat is EtatSelection || etat is EtatDeplacement || etat is EtatRotation
                    || etat is EtatScale || etat is EtatZoom || etat is EtatDuplication)
            )
                {
                    panel_GL.MouseMove += new MouseEventHandler(panel_MouseMove);
                }
                
            
            if (e.Button == MouseButtons.Right)
            {
                panel_GL.MouseMove += new MouseEventHandler(panel_MouseMove);


            }

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_MouseMove(object sender, EventArgs e)
        /// @brief Gestion des états lorsque l'utilisateur bouge la souris
        ///        sur le panel.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_MouseMove(object sender, MouseEventArgs e)
        {
            currentP = panel_GL.PointToClient(MousePosition);
            if (e.Button == MouseButtons.Right)
            {
                deplacementVueSouris(e);
            }
          
            if (etat is EtatCreation)
            {
                if (!(FonctionsNatives.verifierCliqueDansTable(e.X, e.Y)))
                {
                    Cursor = Cursors.No;

                }
                else
                {
                    Cursor = Cursors.Arrow;

                }
                if (e.Button == MouseButtons.Right)
                {
                    deplacementVueSouris(e);
                }

            }

            if (etat is EtatDeplacement && nbSelection == 1) 
            {
                Xbox.Text = Math.Round(FonctionsNatives.getPositionX()).ToString();
                Ybox.Text = Math.Round(FonctionsNatives.getPositionY()).ToString();
                
            }
            if (etat is EtatRotation && nbSelection == 1)
            {
                Anglebox.Text = Math.Round(FonctionsNatives.getAngle()).ToString();
            }
            if ( etat is EtatScale && nbSelection == 1)
            {
                FMEbox.Text = FonctionsNatives.getScale().ToString();
            }
            if (!(clickValide(origin, currentP)) && (etat is EtatSelection) && e.Button == MouseButtons.Left)
            {
                etat = new EtatSelectionMultiple(this);
                FonctionsNatives.initialiserRectangleElastique(origin.X, origin.Y);
            }
            if (!(clickValide(origin, currentP)) && (etat is EtatZoom) && e.Button == MouseButtons.Left)
            {
                etat = new EtatZoomElastique(this);
                FonctionsNatives.initialiserRectangleElastique(origin.X, origin.Y);
            }
            if (!(etat is EtatSelectionMultiple ) && !(etat is EtatCreation) && !(etat is EtatSelection)  && !(etat is EtatZoomElastique))              
                etat.traiterSouris(e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_MouseUp(object sender, EventArgs e)
        /// @brief Gestion des états lorsque l'utilisateur relâche un clic de souris
        ///        dans le panel GL.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseUp(object sender, MouseEventArgs e)
        {
            if (!(etat is EtatCreation))
            {
                panel_GL.MouseMove -= panel_MouseMove;
            }           
            if (e.Button == MouseButtons.Left)
            {
               Point destination = panel_GL.PointToClient(MousePosition);
               if (etat is EtatZoomElastique)
               {
                   etat.traiterSouris(e);
                   etat = new EtatZoom(this);
               }
               if (etat is EtatSelectionMultiple)
               {                   
                   etat.traiterSouris(e);
                   etat = new EtatSelection(this);
               }
               else if(clickValide(origin,destination)) 
                {
                    etat.traiterSouris(e);
                 //   etat = new EtatSelection(this);
                }
                /*else if(clickValide(origin,destination))
                {                    
                    etat.traiterSouris(e);
                }
                 * */
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_MouseUp(object sender, EventArgs e)
        /// @brief Gestion des états lorsque l'utilisateur utilise la roulette
        ///        de la souris dans le panel GL.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseWheel(object sender, MouseEventArgs e)
        {
            etat.traiterRoulette(e);
            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void label1_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur
        ///        le label des infos sur les raccourcis.
        /// 
        /// @param[in] sender : Objet duquel provient un événement
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void label1_Click(object sender, EventArgs e)
        {
            label1.Hide();
            
        }

        /* Fonctionnalités des états */

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void deplacementSouris(MouseEventArgs e)
        /// @brief Gestion des états lorsque l'utilisateur déplace la souris.
        /// 
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void deplacementSouris(MouseEventArgs e)
        {
            // On va calculer un point precedent et un point courrant pour faire le deplacement.

            // Ce point est dans les coordonnees d'affichage d'openGL pour pouvoir calculer un deplacement
            // en coordonnees du monde en utilisant convertirClotureAVirtuelle(...) comme ça on n'a pas 
            // besoin de ce facteur mistérieux.  Et aussi, cette technique devrait bien marcher 
            // quand on sera rendu avec la vue orbite.
            FonctionsNatives.deplacerSelection(previousP.X, previousP.Y, currentP.X, currentP.Y);
            //Xbox.Text = currentP.X.ToString();
            previousP = currentP;
            currentP = panel_GL.PointToClient(MousePosition);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void deplacementVueSouris(MouseEventArgs e)
        /// @brief Gestion du déplacement de la vue avec la souris.
        /// 
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void scaleSouris(MouseEventArgs e)
        {
            //int deltaY = -(currentP.Y - previousP.Y);
            //FonctionsNatives.addScaleObjet(deltaY);
            //previousP.Y = currentP.Y;
            //currentP.Y = e.Y;

            FonctionsNatives.agrandirSelection(previousP.X, previousP.Y, currentP.X, currentP.Y);
            previousP = currentP;
            currentP = panel_GL.PointToClient(MousePosition);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void zoomRoulette(MouseEventArgs e)
        /// @brief Gestion du zoom avec la roulette de la souris.
        /// 
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void zoomRoulette(MouseEventArgs e)
        {
            if (e.Delta > 0 && zoom_Bar.Value < zoom_Bar.Maximum)
            {
                FonctionsNatives.zoomIn();
                zoom_Bar.Value += 1;
            }
            else if (e.Delta < 0 && zoom_Bar.Value > zoom_Bar.Minimum)
            {
                FonctionsNatives.zoomOut();
                zoom_Bar.Value -= 1;
            }
            currentZoom = zoom_Bar.Value;
            previousZoom = zoom_Bar.Value;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selection(EventArgs e)
        /// @brief Gestion de la sélection d'objet avec la souris.
        /// 
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void selection(MouseEventArgs e) 
        {
            int x = panel_GL.PointToClient(MousePosition).X;
            int y = panel_GL.PointToClient(MousePosition).Y;
         
            int h = panel_GL.Height;
            int w = panel_GL.Width;

            bool c = ctrlDown;
            int isSelected = nbSelection;
            // TODO PHIL : Faire que ceci n'arrive que quand on relâche le bouton de gauche et qu'on n'a pas bougé de plus de 3 pixels.
            nbSelection = FonctionsNatives.selectionnerObjetSousPointClique( x, y, h, w, c);
            Console.WriteLine("SELECTION: " + nbSelection);
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
               

                FMEbox.Text = FonctionsNatives.getScale().ToString();
           

            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void rectangleElastique()
        /// @brief Création d'un rectangle élastique.
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
        /// @brief Effacement d'un rectangle élastique.
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
        /// @brief Sélection multiple avec un rectangle élastique.
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
                    FMEbox.Text = FonctionsNatives.getScale().ToString();
                   
                }
                outilsEnable(true);
            }
        }


        public void zoomElastique()
        {
            Point destination = panel_GL.PointToClient(MousePosition);
            if (!altDown)
                FonctionsNatives.zoomInElastique(origin.X, origin.Y, destination.X, destination.Y);
            else if (altDown)
                FonctionsNatives.zoomOutElastique(origin.X, origin.Y, destination.X, destination.Y);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void dupliquerSelection()
        /// @brief Duplication des objets sélectionnés.
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
        /// @fn public void creationObjet(MouseEventArgs e, bool twin = false)
        /// @brief Création d'un objet.
        /// 
        /// @param[in] e : L'événement qui lance la fonction.
        /// @param[in] twin : Indique que l'objet n'est jumeau.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void creationObjet(MouseEventArgs e, bool twin = false)
        {

            if (FonctionsNatives.verifierCliqueDansTable(origin.X, origin.Y))
            {
                afficher_Objet(twin);
                FonctionsNatives.positionObjet(panel_GL.PointToClient(MousePosition).X, panel_GL.PointToClient(MousePosition).Y, 0);
                FonctionsNatives.rotate(angleX, 'x');
                FonctionsNatives.rotate(angleY, 'y');
                FonctionsNatives.rotate(angleZ, 'z');
                FonctionsNatives.scaleObjet(scale);
                previousP.X = panel_GL.PointToClient(MousePosition).X;
                previousP.Y = panel_GL.PointToClient(MousePosition).Y;

                if (FonctionsNatives.verifierCliqueDansTable(panel_GL.PointToClient(MousePosition).X, panel_GL.PointToClient(MousePosition).Y))
                    Console.WriteLine("Click dans la table");
                else
                    Console.WriteLine("Click hors de la table");
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Enregistrer_MenuItem_Click(object sender, EventArgs e)
        /// @brief Gestion des événements lorsque l'utilisateur clique sur 
        ///        le menu Enregistrer.
        /// 
        /// @param[in] sender : Objet duquel provient un événement.
        /// @param[in] e : Événement qui lance la fonction.
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
                    FonctionsNatives.creerXML(pathXML, pathXML.Capacity, prop);
                }
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void proprietesEnable(bool active)
        /// @brief Active ou désactive les labels de propriétés spatiales des objets.
        /// 
        /// @param[in] active : Indique si les labels de propriétés spatiales seront accessibles.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void proprietesEnable(bool active)
        {
            Xbox.Enabled = active;
            Ybox.Enabled = active;
            Anglebox.Enabled = active;
            FMEbox.Enabled = active;
            OK_prop_bouton.Enabled = active;
            Annuler_prop_boutn.Enabled = active;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void outilsEnable(bool active)
        /// @brief Active ou désactive les boutons d'outils de modification de la table.
        /// 
        /// @param[in] active : Indique si les boutons d'outils de modification seront accessibles.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void outilsEnable(bool active)
        {
            bouton_Deplacement.Enabled = active;
            bouton_Rotation.Enabled = active;
            bouton_Scaling.Enabled = active;
            bouton_Duplication.Enabled = active;
            Duplication_MenuItem.Enabled = active;
            Rotation_MenuItem.Enabled = active;
            MiseE_MenuItem.Enabled = active;
            Deplacement_MenuItem.Enabled = active;
            Supprimer_MenuItem.Enabled = active;


        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private bool clickValide(Point origin, Point destination)
        /// @brief Indique si un click est considéré comme valide.
        /// 
        /// @param[in] origin : Point d'origine du clic
        /// @param[in] destination : Position après le clic. 
        /// 
        /// @return True si le click est valide (déplacement < 3pixels), False sinon.
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
        /// @fn public void tournerSelectionSouris(MouseEventArgs e)
        /// @brief Tourne les objets sélectionnés.
        /// 
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @fn private void zoom_Bar_Scroll(object sender, EventArgs e)
        /// @brief Gestion des événements de zoom lorsque l'utilisateur utilise la barre de zoom.
        /// 
        /// @param[in] sender : Objet duquel provient un événement.
        /// @param[in] e : Événement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void zoom_Bar_Scroll(object sender, EventArgs e)
        {
            previousZoom = currentZoom;
            currentZoom = zoom_Bar.Value;
            int deltaZoom = currentZoom - previousZoom;
            if (deltaZoom < 0)
                FonctionsNatives.zoomOut();
            else
                FonctionsNatives.zoomIn();
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void deselection()
        /// @brief Désélectionne tous les objets.
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
        /// @brief Active ou désactive le tracking de la souris.
        /// 
        /// @param[in] enable : Détermine si le tracking est activé ou désactivé.
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
        /// @param[in] name : Nom du média.
        /// @param[in] stop : (false) La lecture n'arrête pas.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        private void playSound(String name, bool stop = false)
        {
            String path;
            if (name == "")
                path = "";
            else
                path = "media/SFX/" + name + ".wav";
            StringBuilder music = new StringBuilder(path);
            FonctionsNatives.playSound(music, music.Capacity, stop);
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Creation_Panel_MouseEnter(object sender, EventArgs e)
        /// @brief Gestion des événements de zoom lorsque la souris entre dans le panel de création.
        /// 
        /// @param[in] sender : Objet duquel provient un événement.
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Gestion des événements de zoom lorsque la souris quitte le panel GL.
        /// 
        /// @param[in] sender : Objet duquel provient un événement.
        /// @param[in] e : Événement qui lance la fonction.
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
        /// @brief Active ou désactive le zoom.
        /// 
        /// @param[in] active : Indique si le zoom est accessible.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void enableZoom(bool active)
        {
            zoom_Bar.Enabled = active;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void statePortail()
        /// @brief Entre en état Portail.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void statePortail()
        {
            etat = new EtatPortail(this);
            panel_GL.MouseMove += new MouseEventHandler(panel_MouseMove);


        }

    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class FullScreen
    /// @brief Gestion du mode Plein Écran.
    ///
    /// @author The Ballers
    /// @date 2015-01-13
    /// 
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    class FullScreen
    {
        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void EnterFullScreenMode(Form targetForm)
        /// @brief Entre en mode Plein Écran.
        /// 
        /// @param[in] active : La form qui passe en mode Plein Écran.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void EnterFullScreenMode(Form targetForm)
        {

            targetForm.WindowState = FormWindowState.Normal;
            targetForm.FormBorderStyle = FormBorderStyle.None;
            targetForm.WindowState = FormWindowState.Maximized;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void LeaveFullScreenMode(Form targetForm)
        /// @brief Quitte le mode Plein Écran.
        /// 
        /// @param[in] active : La form qui quitte le mode Plein Écran.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void LeaveFullScreenMode(Form targetForm)
        {
            targetForm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable;
            targetForm.WindowState = FormWindowState.Normal;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public bool IsFullScreen(Form targetForm)
        /// @brief Indique si une form est en mode Plein Écran.
        /// 
        /// @param[in] active : La form qui quitte le mode Plein Écran.
        /// 
        /// @return True si la form est en Plein Écran, false sinon.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public bool IsFullScreen(Form targetForm)
        {
            return (targetForm.WindowState == FormWindowState.Maximized);
        }
    }


    ///////////////////////////////////////////////////////////////////////////
    /// @class FonctionsNatives
    /// @brief Importation des fonctions natives (logique C++).
    ///
    /// @author Inconnu
    /// @date Incconue
    /// 
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserOpenGL(IntPtr handle);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void libererOpenGL();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void dessinerOpenGL();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animer(double temps);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void redimensionnerFenetre(int largeur, int hauteur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void creerObjet(StringBuilder value, int length, bool isTwin = false, bool colorShift = false);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void positionObjet(int x, int y, int z = 0);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void translateObjet(int x, int y, int z = 0);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void scaleObjet(double scale);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void addScaleObjet(int myScale);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void scaleXYZObjet(double x, double y, double z);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void rotate(float angle, char direction = 'x');

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void resetObject();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void removeObject();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void purgeAll();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void translater(double deplacementX, double deplacementY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int creerXML(StringBuilder path, int taille, int[] prop);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ouvrirXML(StringBuilder path, int taille);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int selectionnerObjetSousPointClique(int i, int j,int hauteur, int largeur, bool ctrlDown = false);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomIn();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomOut();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void orbite(double phi, double theta);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerSelection(int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void tournerSelectionSouris(int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomInElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomOutElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void agrandirSelection(int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void rectangleElastique(int i, int j);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int selectionMultiple(bool c);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool verifierCliqueDansTable(int x, int y);
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deselectAll();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getPositionX();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getPositionY();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getAngle();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getScale();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void dupliquerSelection(int i, int j);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void playSound(StringBuilder value, int length, bool stop = false);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void obligerTransparence(bool transparence);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserRectangleElastique(int i, int j);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void terminerRectangleElastique();
    }
}
