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
        public Exemple()
        {
            this.KeyPress += new KeyPressEventHandler(ToucheEnfonce);
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

        private void ToucheEnfonce(Object o, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.Space)
            {
             //   System.Console.WriteLine("Barre d'espacement appuyée.");
                              
            }
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
                Selection_MenuItem_Click(this,e);
            }
          
        }

        private void nouveauToolStripMenuItem_Click(object sender, EventArgs e)
        {
          //  System.Console.WriteLine("Nouveau");            
        }
        
        private void quitterToolStripMenuItem_Click(object sender, EventArgs e)
        {
          //  System.Console.WriteLine("Quitter");
            this.Close();
            
        }

        private void Exemple_FormClosing(object sender, FormClosingEventArgs e)
        {
            lock(Program.unLock)
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
        delegate(object o, DoWorkEventArgs args)
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
            ouvrir_fichier.Filter = "Fichiers XML (*.xml)| *.xml | All Files(*.*)|(*.*)";
            ouvrir_fichier.ShowDialog();
        }

        private void EnregistrerS_MenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog enregistrer_fichier = new SaveFileDialog();
            enregistrer_fichier.Filter = "Fichiers XML (*.xml)| *.xml | All Files(*.*)|(*.*)";
            enregistrer_fichier.ShowDialog();
            
        }

     
        private void helpToolStripButton_Click(object sender, EventArgs e)
        {
            Aide_MenuItem_Click(this,e);
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
            Console.WriteLine("Outil Selection.");
        }

        private void Selection_BO_Click(object sender, EventArgs e)
        {
            Selection_MenuItem_Click(this, e);
        }

        private void Rotation_MenuItem_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Outil Rotation");
        }

        private void Rotation_BO_Click(object sender, EventArgs e)
        {
            Rotation_MenuItem_Click(this, e);
        }
                
        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void bouton_Selection_Click(object sender, EventArgs e)
        {

        }

        private void bouton_Creation_Click(object sender, EventArgs e)
        {

            if (Creation_Panel.Visible)
                Creation_Panel.Visible = false;
            else
                Creation_Panel.Visible = true;
        }

        private void panel_GL_MouseClick(object sender, MouseEventArgs e)
        {
            Console.Write(panel_GL.PointToClient(MousePosition));

            Xbox.Text = panel_GL.PointToClient(MousePosition).X.ToString();
            Ybox.Text = panel_GL.PointToClient(MousePosition).Y.ToString();
            
            // Les deux prochaines lignes sont temporaires : elles affichent la taille de l'écran
            Anglebox.Text = panel_GL.Width.ToString();
            FMEbox.Text = panel_GL.Height.ToString();

        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            myObjectName = new StringBuilder("generateurbille");
        }

        private void Proprietes_MenuItem_Click(object sender, EventArgs e)
        {
            Proprietes proprietes = new Proprietes();
            proprietes.StartPosition = FormStartPosition.CenterScreen;
            proprietes.Show();
        }

        // Afin de ne pas tout le temps redimensionner l'écran dans le rendu, 
        // (pour les tests), je fais ce traitement ici. Il faut éventuellement
        // replacer le call dans un event qui sera appelé à chaque redimensionnement
        // (en ce moment, chaque red. c# est lié à ce bouton).
        private void butoirG_bouton_Click(object sender, EventArgs e)
        {
            Console.Write("Width to send : " + panel_GL.Width.ToString() + "\n" + "Height to send : " + panel_GL.Height.ToString() + "\n");
            FonctionsNatives.redimensionnerFenetre(panel_GL.Width, panel_GL.Height);
        }

        private void OK_prop_bouton_Click(object sender, EventArgs e)
        {
            int positionX = Convert.ToInt32(Xbox.Text == "" ? null : Xbox.Text);
            int positionY = Convert.ToInt32(Ybox.Text == "" ? null : Ybox.Text);

            Console.WriteLine(FonctionsNatives.creerObjet(myObjectName, myObjectName.Capacity, positionX, positionY));
        }

        private void Annuler_prop_boutn_Click(object sender, EventArgs e)
        {
            myObjectName = new StringBuilder("vide");
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
        public static extern bool creerObjet(StringBuilder value, int length, int x = 0, int y = 0, double rotation = 0.0); 
    
    }
}
