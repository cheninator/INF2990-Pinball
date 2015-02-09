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

// test
namespace InterfaceGraphique
{
    public partial class Exemple : Form
    {
        FullScreen fs = new FullScreen();
        static public StringBuilder myObjectName = new StringBuilder("vide");
   
        public Point origin;
        
        public Point previousP, currentP;

        public int panelHeight;
        public int panelWidth;
        private bool ctrlDown = false;
        private bool altDown = true;
        // private char state = 's';
        public List<int> propZJ = new List<int>{10,10,10,10,10,1};
        private float angleX = 0F;
        private float angleY = 0F;
        private float angleZ = 0F;
        private float scale = 1F;
        private int currentZoom = 5;
        private int previousZoom = 5;
        private int nbSelection;
        private StringBuilder pathXML = new StringBuilder("");
        private Etat etat {get; set;}

        private int[] prop = new int[6];

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
            panel_GL.Focus();   
            InitialiserAnimation();

            panelHeight = panel_GL.Size.Height;
            panelWidth = panel_GL.Size.Width;
            etat = new EtatNone(this);

            //Musique
            //var bgm = new WMPLib.WindowsMediaPlayer();
            //bgm.URL = @"media/SFX/music.wav";
            System.Media.SoundPlayer player = new System.Media.SoundPlayer(@"media/SFX/stone.wav");
            player.Play();
        }

        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            this.StartPosition = FormStartPosition.WindowsDefaultBounds;
            FonctionsNatives.initialiserOpenGL(panel_GL.Handle);
            FonctionsNatives.dessinerOpenGL();

        }

        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    FonctionsNatives.animer(tempsInterAffichage);
                    FonctionsNatives.dessinerOpenGL();

                    if (etat is EtatSelectionMultiple)
                        rectangleElastique();
                });
            }
            catch (Exception)
            {
            }
        }

       
        private void ToucheDown(Object o, KeyEventArgs e)
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
                    && zoom_Bar.Value < 10)
                {
                    FonctionsNatives.zoomIn();
                    zoom_Bar.Value += 1;
                    currentZoom = zoom_Bar.Value;
                    previousZoom = zoom_Bar.Value;
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
        private void ToucheEnfonce(Object o, KeyPressEventArgs e)
        {

            if( e.KeyChar == (char)Keys.Escape)
            {
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
                
                //state = 'd';
            }
            if (e.KeyChar == 'e')
            {
                etat = null;
                etat = new EtatScale(this);
                
                //state = 'e';
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

                //state = 'z';
            }
            if (e.KeyChar == 'o')
            {
                // state = 'o';
            }
            if (e.KeyChar == 'h')
            {
                if (label1.Visible)
                    label1.Hide();
                else
                    label1.Show();
            }
        }
        private void Exemple_FormClosing(object sender, FormClosingEventArgs e)
        {
            lock (Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;
            }
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

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

        private void Ouvrir_MenuItem_Click(object sender, EventArgs e)
        {

            OpenFileDialog ouvrir_fichier = new OpenFileDialog();
            ouvrir_fichier.Filter = "Fichier XML(*.xml)| *.xml| All files(*.*)|*.*";
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

        private void EnregistrerS_MenuItem_Click(object sender, EventArgs e)
        {
            EnregistrerSous();
        }

        private void EnregistrerSous()
        {
            int sauvegarde = FonctionsNatives.creerXML(pathXML, pathXML.Capacity, prop);

            if (sauvegarde == 0)
            {
                System.Media.SoundPlayer player = new System.Media.SoundPlayer(@"media/SFX/no.wav");
                player.Play();
                MessageBox.Show("Il doit avoir au moins un trou, un générateur de bille et un ressort dans la zone de jeu!", "ERREUR DE SAUVEGARDE",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            else if (sauvegarde == 2)
            {
                SaveFileDialog enregistrer_fichier = new SaveFileDialog();
                enregistrer_fichier.Filter = "Fichier XML(*.xml)| *.xml| All files(*.*)|*.*";
                enregistrer_fichier.ShowDialog();
                pathXML = new StringBuilder(enregistrer_fichier.FileName);
                for (int i = 0; i < 6; i++)
                    prop[i] = propZJ[i];

                int a = FonctionsNatives.creerXML(pathXML, pathXML.Capacity, prop);
                
            }

            else
            {
                MessageBox.Show("Vous ne pouvez pas sauvegarder la zone de jeu par défaut. Rajoutez des objets!", "ERREUR DE SAUVEGARDE",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        } 

        private void helpToolStripButton_Click(object sender, EventArgs e)
        {
            Aide_MenuItem_Click(this, e);
        }

        private void Selectionner_BO_Click(object sender, EventArgs e)
        {
            if (Creation_Panel.Visible)
                Creation_Panel.Hide();
            else
                Creation_Panel.Show();
        }

        private void panel1_Click(object sender, EventArgs e)
        {
            Console.Write(this.PointToClient(MousePosition));
        }

        private void Selection_MenuItem_Click(object sender, EventArgs e)
        {

            bouton_Selection_Click(this, e);
        }

        private void Selection_BO_Click(object sender, EventArgs e)
        {
            Selection_MenuItem_Click(this, e);
        }

        private void Rotation_MenuItem_Click(object sender, EventArgs e)
        {
            bouton_Rotation_Click(this, e);
        }

        private void Rotation_BO_Click(object sender, EventArgs e)
        {
            Rotation_MenuItem_Click(this, e);
        }

        private void bouton_Selection_Click(object sender, EventArgs e)
        {
            etat = new EtatSelection(this);

            Console.WriteLine("Outil Selection.");
        }

        private void bouton_Creation_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Creation.");
            if (Creation_Panel.Visible)
                Creation_Panel.Visible = false;
            else
                Creation_Panel.Visible = true;

        }

        private void panel_GL_MouseClick(object sender, MouseEventArgs e)
        {
            Console.Write(panel_GL.PointToClient(MousePosition));
          //  Xbox.Text = panel_GL.PointToClient(MousePosition).X.ToString();
          //  Ybox.Text = (panel_GL.PointToClient(MousePosition).Y).ToString();

            panel_GL.Focus();
        }

        private void butourCirc_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("ButoirCirculaire");
            myObjectName = new StringBuilder("butoircirculaire");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        private void Proprietes_MenuItem_Click(object sender, EventArgs e)
        {
            Proprietes proprietes = new Proprietes(this.propZJ);
            //proprietes.Parent = this;
            proprietes.StartPosition = FormStartPosition.CenterScreen;
            proprietes.ShowDialog();
            propZJ = proprietes.getProps();
            proprietes.Close();
            
        }

        private void butoirG_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Butoir Gauche.");
            myObjectName = new StringBuilder("butoir");
            angleX = 0;
            angleY = 0;
            angleZ = 180;

        }

        private void OK_prop_bouton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.deplacerSelection(
                FonctionsNatives.getPositionX(),
                FonctionsNatives.getPositionY(),
                Convert.ToInt32(Xbox.Text), 
                Convert.ToInt32(Ybox.Text));
            
           
            
        }

        public void Afficher_Objet(bool twin)
        {
            Console.WriteLine(myObjectName);
            FonctionsNatives.creerObjet(myObjectName, myObjectName.Capacity, twin);
        }

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

        private void Fenetre_Redimension(object sender, EventArgs e)
        {
            Console.Write("Width to send : " + panel_GL.Width.ToString() + "\n" + "Height to send : " + panel_GL.Height.ToString() + "\n");
            FonctionsNatives.redimensionnerFenetre(panel_GL.Width == 0 ? 1 : panel_GL.Width, panel_GL.Height == 0 ? 1 : panel_GL.Height);
        }
        private void Annuler_prop_boutn_Click(object sender, EventArgs e)
        {
            FonctionsNatives.removeObject();
        }

        private void Exemple_Load(object sender, EventArgs e)
        {

        }

        private void Ressort_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Ressort");
            myObjectName = new StringBuilder("ressort");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        private void Generateur_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Generateur");
            myObjectName = new StringBuilder("generateurbille");
            angleX = 0;
            angleY = 0;// 90;
            angleZ = 0;//180;
        }

        private void Trou_bouton_Click(object sender, EventArgs e)
        {
            
            etat = new EtatCreation(this);
            Console.WriteLine("Trou");
            myObjectName = new StringBuilder("trou");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        private void bouton_Deplacement_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Deplacement.");
            // TO DO
            etat = null;
            etat = new EtatDeplacement(this);
        }

        private void Deplacement_MenuItem_Click(object sender, EventArgs e)
        {
            bouton_Deplacement_Click(this, e);
        }

        private void MenuP_MenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void bouton_Rotation_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Rotation.");
            // TO DO
            etat = null;
            etat = new EtatRotation(this);
        }

        private void bouton_Scaling_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Mise a echelle.");
            // TO DO
            etat = null;
            etat = new EtatScale(this);
        }

        private void MiseE_MenuItem_Click(object sender, EventArgs e)
        {
            bouton_Scaling_Click(this, e);
        }

        private void Zoom_MenuItem_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Zoom.");
            
            etat = null;
            etat = new EtatZoom(this);
        }

        private void bouton_Duplication_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Duplication.");
            // TO DO
            etat = null;
            etat = new EtatDuplication(this);
        }

        private void Duplication_MenuItem_Click(object sender, EventArgs e)
        {
            bouton_Duplication_Click(this, e);
        }

        private void Creation_MenuItem_Click(object sender, EventArgs e)
        {
            bouton_Creation_Click(this, e);
        }

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

        private void PGJ1_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Palette gauche J1.");
            myObjectName = new StringBuilder("palette");
            angleX = 180;
            angleY = 0;
            angleZ = 180;
        }

        private void PG_J1_MenuItem_Click(object sender, EventArgs e)
        {
            PGJ1_bouton_Click(this, e);
        }

        private void PDJ1_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Palette droite J1.");
            myObjectName = new StringBuilder("palette");
            angleX = 180;
            angleY = 0;
            angleZ = 0;
        }

        private void PD_J1_MenuItem_Click(object sender, EventArgs e)
        {
            PDJ1_bouton_Click(this, e);
        }

        private void PGJ2_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Palette gauche J2.");
            myObjectName = new StringBuilder("palette");
            angleX = 180;
            angleY = 0;
            angleZ = 180;
        }

        private void PG_J2_MenuItem_Click(object sender, EventArgs e)
        {
            PGJ2_bouton_Click(this, e);
        }

        private void PDJ2_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Palette droite J2.");
            myObjectName = new StringBuilder("palette");
            angleX = 180;
            angleY = 0;
            angleZ = 0;
        }

        private void PD_J2_MenuItem_Click(object sender, EventArgs e)
        {
            PDJ2_bouton_Click(this, e);
        }

        private void BTG_MenuItem_Click(object sender, EventArgs e)
        {
            butoirG_bouton_Click(this, e);
        }

        private void butoirD_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Butoir Droit.");
            myObjectName = new StringBuilder("butoir");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        private void BTD_MenuItem_Click(object sender, EventArgs e)
        {
            butoirD_bouton_Click(this, e);
        }

        private void Cible_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Cible.");
           myObjectName = new StringBuilder("cible");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        private void Cible_MenuItem_Click(object sender, EventArgs e)
        {
            Cible_bouton_Click(this, e);
        }

        private void Portails_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Portail");
            myObjectName = new StringBuilder("portail");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        private void Portails_MenuItem_Click(object sender, EventArgs e)
        {
            Portails_bouton_Click(this, e);
        }

        private void Mur_bouton_Click(object sender, EventArgs e)
        {
            etat = new EtatCreation(this);
            Console.WriteLine("Mur");
            myObjectName = new StringBuilder("mur");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
        }

        private void Mur_MenuItem_Click(object sender, EventArgs e)
        {
            Mur_bouton_Click(this, e);
        }

        private void Ressort_MenuItem_Click(object sender, EventArgs e)
        {
            Ressort_bouton_Click(this, e);
        }

        private void GB_MenuItem_Click(object sender, EventArgs e)
        {
            Generateur_bouton_Click(this, e);
        }

        private void Trou_MenuItem_Click(object sender, EventArgs e)
        {
            Trou_bouton_Click(this, e);
        }


        private void Nouveau_MenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.purgeAll();
            propZJ = new List<int> { 10, 10, 10, 10, 10, 1 };
        }

        private void panel_GL_MouseDown(object sender, MouseEventArgs e)
        {
            origin = panel_GL.PointToClient(MousePosition);
            //if( !(etat is EtatCreation))
            //    panel_GL.MouseMove += new MouseEventHandler(panel_MouseMove);   
            
            
                    
            
            previousP.X = e.X;
            previousP.Y = e.Y;
            currentP.X = e.X;
            currentP.Y = e.Y;
            if (e.Button == MouseButtons.Left &&
            (etat is EtatSelection || etat is EtatDeplacement || etat is EtatRotation
                    || etat is EtatScale)
            )
                {
                    panel_GL.MouseMove += new MouseEventHandler(panel_MouseMove);
                }
                
            
            if (e.Button == MouseButtons.Right)
            {
                panel_GL.MouseMove += new MouseEventHandler(panel_MouseMove);


            }

        }
        private void panel_MouseMove(object sender, MouseEventArgs e)
        {
            currentP = panel_GL.PointToClient(MousePosition);
            if (etat is EtatDeplacement && nbSelection == 1) 
            {
                Xbox.Text = FonctionsNatives.getPositionX().ToString();
                Ybox.Text = FonctionsNatives.getPositionY().ToString();
                
            }
            if (etat is EtatRotation && nbSelection == 1)
            {
                Anglebox.Text = FonctionsNatives.getAngle().ToString();
            }
            if ( etat is EtatScale && nbSelection == 1)
            {
                FMEbox.Text = FonctionsNatives.getScale().ToString();
            }
            if (!(clickValide(origin, currentP)) && (etat is EtatSelection) && !(etat is EtatSelectionMultiple) && e.Button == MouseButtons.Left)
            {
                etat = new EtatSelectionMultiple(this);
            }

            if (!(etat is EtatSelectionMultiple))
                etat.traiterSouris(e);
        }

        private void panel_GL_MouseUp(object sender, MouseEventArgs e)
        {
            panel_GL.MouseMove -= panel_MouseMove;
                         
            if (e.Button == MouseButtons.Left)
            {
                Point destination = panel_GL.PointToClient(MousePosition);
                if (etat is EtatZoom)
                {
                    FonctionsNatives.zoomElastique(origin.X, origin.Y, destination.X, destination.Y);
                }
                else if (etat is EtatSelectionMultiple)
                {
                    etat.traiterSouris(e);
                    etat = new EtatSelection(this);
                }
                else if(clickValide(origin,destination))
                {                    
                    etat.traiterSouris(e);
                }
            }
        }

        private void panel_GL_MouseWheel(object sender, MouseEventArgs e)
        {
            etat.traiterRoulette(e);
            
        }


        private void label1_Click(object sender, EventArgs e)
        {
            label1.Hide();
            
        }

        /* Fonctionnalités des états */

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

        public void deplacementVueSouris(MouseEventArgs e)
        {
            double deltaX = (-(currentP.X - previousP.X)) * 100.0 / panelWidth;
            double deltaY = ((currentP.Y - previousP.Y)) * 100.0 / panelHeight;
            FonctionsNatives.translater(deltaX, deltaY);
            
            previousP.X = currentP.X;
            previousP.Y = currentP.Y;
            currentP.X = e.X;
            currentP.Y = e.Y;
        }

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
            if (nbSelection == 0)
            {
                outilsEnable(false);
                proprietesEnable(false);
                if (isSelected == 0)
                {
                    System.Media.SoundPlayer player = new System.Media.SoundPlayer(@"media/SFX/no.wav");
                    player.Play();
                }
            }
            else
            {
                outilsEnable(true);
                proprietesEnable(true);
                Xbox.Text = FonctionsNatives.getPositionX().ToString();
                Ybox.Text = FonctionsNatives.getPositionY().ToString();
                Anglebox.Text = FonctionsNatives.getAngle().ToString();
                FMEbox.Text = FonctionsNatives.getScale().ToString();
            }
        }

        public void rectangleElastique()
        {
            FonctionsNatives.rectangleElastique(origin.X, origin.Y, currentP.X, currentP.Y);
        }

        public void selectionMultiple()
        {
            nbSelection = FonctionsNatives.selectionMultiple();
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
                    Xbox.Text = FonctionsNatives.getPositionX().ToString();
                    Ybox.Text = FonctionsNatives.getPositionY().ToString();
                    Anglebox.Text = FonctionsNatives.getAngle().ToString();
                    FMEbox.Text = FonctionsNatives.getScale().ToString();
                }
                outilsEnable(true);
            }

        }

        public void dupliquerSelection()
        {
            currentP = panel_GL.PointToClient(MousePosition);
            FonctionsNatives.dupliquerSelection(currentP.X, currentP.Y);
        }

        public void creationObjet(MouseEventArgs e, bool twin = false)
        {

            if (FonctionsNatives.verifierCliqueDansTable(origin.X, origin.Y))
            {
                Afficher_Objet(twin);
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
                    Console.WriteLine("Click dans pas la table");
            }
        }

        private void Enregistrer_MenuItem_Click(object sender, EventArgs e)
        {
            if (pathXML.ToString() == "")
                EnregistrerSous();
            else
                FonctionsNatives.creerXML(pathXML, pathXML.Capacity, prop);
        }

        public void proprietesEnable(bool active)
        {
            Xbox.Enabled = active;
            Ybox.Enabled = active;
            Anglebox.Enabled = active;
            FMEbox.Enabled = active;
            OK_prop_bouton.Enabled = active;
            Annuler_prop_boutn.Enabled = active;
        }
        public void outilsEnable(bool active)
        {
            bouton_Deplacement.Enabled = active;
            bouton_Rotation.Enabled = active;
            bouton_Scaling.Enabled = active;
            bouton_Duplication.Enabled = active;
        }
        private bool clickValide(Point origin, Point destination)
        {
            return ((Math.Abs(destination.X - origin.X) < 3)
                     &&
                    (Math.Abs(destination.Y - origin.Y) < 3));
                    
        }


        public void tournerSelectionSouris(MouseEventArgs e)
        {
            FonctionsNatives.tournerSelectionSouris(previousP.X, previousP.Y, currentP.X, currentP.Y);
            previousP = currentP;
            currentP = panel_GL.PointToClient(MousePosition);
        }

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

        public void deselection()
        {
            FonctionsNatives.deselectAll();
            proprietesEnable(false);
            outilsEnable(false);
        }


    }
    // Full Screen

    class FullScreen
    {
        public void EnterFullScreenMode(Form targetForm)
        {

            targetForm.WindowState = FormWindowState.Normal;
            targetForm.FormBorderStyle = FormBorderStyle.None;
            targetForm.WindowState = FormWindowState.Maximized;
        }

        public void LeaveFullScreenMode(Form targetForm)
        {
            targetForm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable;
            targetForm.WindowState = FormWindowState.Normal;
        }

        public bool IsFullScreen(Form targetForm)
        {
            return (targetForm.WindowState == FormWindowState.Maximized);
        }
    }



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
        public static extern void creerObjet(StringBuilder value, int length, bool isTwin = false);

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
        public static extern void zoomElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void agrandirSelection(int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void rectangleElastique(int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int selectionMultiple();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool verifierCliqueDansTable(int x, int y);
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deselectAll();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getPositionX();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getPositionY();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getAngle();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getScale();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void dupliquerSelection(int i, int j);
    }
}
