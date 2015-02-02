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



// test
namespace InterfaceGraphique
{
    public partial class Exemple : Form
    {
        FullScreen fs = new FullScreen();
        StringBuilder myObjectName = new StringBuilder("vide");
        Point origin;
        Point previousP, currentP;
        private char state = 's';
        private float angleX = 0F;
        private float angleY = 0F;
        private float angleZ = 0F;
        private float scale = 1F;
        private char color = 'x';
        public Exemple()
        {
            this.KeyPress += new KeyPressEventHandler(ToucheEnfonce);
            // Pour le deplacement de la vue
            // besoin de nouveau event parce que C#....
            this.KeyDown += new KeyEventHandler(ToucheDown);
            this.Icon = Properties.Resources.Pinball;
            InitializeComponent();
            Program.peutAfficher = true;
            panel_GL.Focus();
            InitialiserAnimation();
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
                });
            }
            catch (Exception)
            {
            }
        }
        private void ToucheDown(Object o, KeyEventArgs e)
        {
            if (panel_GL.Focused)
            {
                if (e.KeyData == Keys.Subtract)
                    FonctionsNatives.zoomOut();

                if (e.KeyData == Keys.Add)
                    FonctionsNatives.zoomIn();

                if (e.KeyData == Keys.Left)
                    FonctionsNatives.translater(-10, 0);

                if (e.KeyData == Keys.Right)
                    FonctionsNatives.translater(10, 0);

                if (e.KeyData == Keys.Up)
                    FonctionsNatives.translater(0, 10);

                if (e.KeyData == Keys.Down)
                    FonctionsNatives.translater(0, -10);
            }
        }
        private void ToucheEnfonce(Object o, KeyPressEventArgs e)
        {

            System.Console.WriteLine(e.KeyChar);
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
                state = 'd';
            }
            if (e.KeyChar == 'e')
            {
                state = 'e';
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
            ouvrir_fichier.ShowDialog();
        }

        private void EnregistrerS_MenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog enregistrer_fichier = new SaveFileDialog();
            enregistrer_fichier.Filter = "Fichier XML(*.xml)| *.xml| All files(*.*)|*.*";
            enregistrer_fichier.ShowDialog();
            StringBuilder pathXML = new StringBuilder(enregistrer_fichier.FileName);
            FonctionsNatives.creerXML(pathXML, pathXML.Capacity);

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
            // TO DO
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
            Xbox.Text = panel_GL.PointToClient(MousePosition).X.ToString();
            Ybox.Text = (panel_GL.PointToClient(MousePosition).Y).ToString();

            panel_GL.Focus();
        }

        private void butourCirc_bouton_Click(object sender, EventArgs e)
        {
            Console.WriteLine("ButoirCirculaire");
            myObjectName = new StringBuilder("butoircirculaire");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            color = 'x';
        }

        private void Proprietes_MenuItem_Click(object sender, EventArgs e)
        {
            Proprietes proprietes = new Proprietes();
            proprietes.StartPosition = FormStartPosition.CenterScreen;
            proprietes.Show();
        }

        private void butoirG_bouton_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Butoir Gauche.");
            myObjectName = new StringBuilder("butoir");
            angleX = 0;
            angleY = 0;
            angleZ = 180;
            color = 'x';

        }

        private void OK_prop_bouton_Click(object sender, EventArgs e)
        {
            Positionner_Objet();
            Scale_Objet();
            Rotate_Object();
        }

        public void Afficher_Objet()
        {
            Console.WriteLine(myObjectName);
            FonctionsNatives.creerObjet(myObjectName, myObjectName.Capacity);
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
            //myObjectName = new StringBuilder("vide");
            //FonctionsNatives.resetObject();
            FonctionsNatives.removeObject();
        }

        private void Exemple_Load(object sender, EventArgs e)
        {

        }

        private void Ressort_bouton_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Ressort");
            myObjectName = new StringBuilder("ressort");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            color = 'x';
        }

        private void Generateur_bouton_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Generateur");
            myObjectName = new StringBuilder("generateurbille");
            angleX = 0;
            angleY = 0;// 90;
            angleZ = 0;//180;
            color = 'x';
        }

        private void Trou_bouton_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Trou");
            myObjectName = new StringBuilder("trou");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            color = 'x';
        }

        private void bouton_Deplacement_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Deplacement.");
            // TO DO
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
        }

        private void bouton_Scaling_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Mise a echelle.");
            // TO DO
        }

        private void MiseE_MenuItem_Click(object sender, EventArgs e)
        {
            bouton_Scaling_Click(this, e);
        }

        private void Zoom_MenuItem_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Zoom.");
            // TO DO

            if (zoom_Bar.Enabled)
                zoom_Bar.Enabled = false;
            else
                zoom_Bar.Enabled = true;
        }

        private void bouton_Duplication_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Duplication.");
            // TO DO
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
            Console.WriteLine("Palette gauche J1.");
            myObjectName = new StringBuilder("palette");
            angleX = 180;
            angleY = 0;
            angleZ = 0;
            color = 'r';
            // Afficher_Objet();
            // DO STUFF
        }

        private void PG_J1_MenuItem_Click(object sender, EventArgs e)
        {
            PGJ1_bouton_Click(this, e);
        }

        private void PDJ1_bouton_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Palette droite J1.");
            myObjectName = new StringBuilder("palette");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            color = 'r';
        }

        private void PD_J1_MenuItem_Click(object sender, EventArgs e)
        {
            PDJ1_bouton_Click(this, e);
        }

        private void PGJ2_bouton_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Palette gauche J2.");
            myObjectName = new StringBuilder("palette");
            angleX = 180;
            angleY = 0;
            angleZ = 0;
            color = 'b';
        }

        private void PG_J2_MenuItem_Click(object sender, EventArgs e)
        {
            PGJ2_bouton_Click(this, e);
        }

        private void PDJ2_bouton_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Palette droite J2.");
            myObjectName = new StringBuilder("palette");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            color = 'b';
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
            Console.WriteLine("Butoir Droit.");
            myObjectName = new StringBuilder("butoir");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            color = 'x';
        }

        private void BTD_MenuItem_Click(object sender, EventArgs e)
        {
            butoirD_bouton_Click(this, e);
        }

        private void Cible_bouton_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Cible.");
           myObjectName = new StringBuilder("cible");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            color = 'x';
        }

        private void Cible_MenuItem_Click(object sender, EventArgs e)
        {
            Cible_bouton_Click(this, e);
        }

        private void Portails_bouton_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Portail");
            myObjectName = new StringBuilder("portail");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            color = 'x';
        }

        private void Portails_MenuItem_Click(object sender, EventArgs e)
        {
            Portails_bouton_Click(this, e);
        }

        private void Mur_bouton_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Mur");
            myObjectName = new StringBuilder("mur");
            angleX = 0;
            angleY = 0;
            angleZ = 0;
            color = 'x';
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
        }

        private void panel_GL_MouseDown(object sender, MouseEventArgs e)
        {

            origin = panel_GL.PointToClient(MousePosition);
            if (e.Button == MouseButtons.Left)
            {
                
                
            }
            if (e.Button == MouseButtons.Right)
            {
                panel_GL.MouseMove += new MouseEventHandler(panel_MouseMove);
                previousP.X = e.X;
                previousP.Y = e.Y;
                currentP.X = e.X;
                currentP.Y = e.Y;


            }

        }
        private void panel_MouseMove(object sender, MouseEventArgs e)
        {
            
          
            if (state == 'd')
            {
                int deltaX = (currentP.X - previousP.X) ;
                int deltaY = -(currentP.Y - previousP.Y) ;
                FonctionsNatives.translateObjet(deltaX, deltaY);

                previousP.X = currentP.X;
                previousP.Y = currentP.Y;
                currentP.X = e.X;
                currentP.Y = e.Y;
            }


            if (state == 'e')
            {
                int deltaY = -(currentP.Y - previousP.Y);
                FonctionsNatives.addScaleObjet(deltaY);
                previousP.Y = currentP.Y;
                currentP.Y = e.Y;
                
          }
          //  scale = 1;
        }

        private void panel_GL_MouseUp(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Right)
                panel_GL.MouseMove -= panel_MouseMove;
            if (e.Button == MouseButtons.Left)
            {
                Point destination = panel_GL.PointToClient(MousePosition);
                if ((Math.Abs(destination.X - origin.X) < 3)
                     &&
                     (Math.Abs(destination.Y - origin.Y) < 3)
                    )
                {
                    Afficher_Objet();
                    FonctionsNatives.positionObjet(panel_GL.PointToClient(MousePosition).X, panel_GL.PointToClient(MousePosition).Y);
                    FonctionsNatives.rotate(angleX, 'x');
                    FonctionsNatives.rotate(angleY, 'y');
                    FonctionsNatives.rotate(angleZ, 'z');
                    FonctionsNatives.scaleObjet(scale);
                    previousP.X = panel_GL.PointToClient(MousePosition).X;
                    previousP.Y = panel_GL.PointToClient(MousePosition).Y;
                    Console.WriteLine("Good Spawn");
                    FonctionsNatives.trouverObjetSousPointClique(panel_GL.PointToClient(MousePosition).X, panel_GL.PointToClient(MousePosition).Y);
                }
            }
        }

        private float deltaY(float originY, float destY)
        {
            return (destY - originY) / 10;
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
        public static extern void creerObjet(StringBuilder value, int length);

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
        public static extern void creerXML(StringBuilder path, int taille);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void trouverObjetSousPointClique(int i, int j);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomIn();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomOut();
    }
}
