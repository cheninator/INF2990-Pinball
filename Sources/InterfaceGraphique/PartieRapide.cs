using System;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class PartieRapide : Form
    {
        private double currentZoom = -1; ///< Zoom courant
        private Touches touches;
        public PartieRapide()
        {
            this.KeyDown += new KeyEventHandler(PartieRapide_KeyDown);
            this.KeyUp += new KeyEventHandler(PartieRapide_KeyUp);

            InitializeComponent();
            Program.peutAfficher = true;              
            InitialiserAnimation();

            FonctionsNatives.resetZoom();
            currentZoom = -1;

            touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                  FonctionsNatives.obtenirTouchePGJ2(),
                                  FonctionsNatives.obtenirTouchePDJ1(),
                                  FonctionsNatives.obtenirTouchePDJ2(),
                                  FonctionsNatives.obtenirToucheRessort());
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

        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    FonctionsNatives.animer(tempsInterAffichage);
                    FonctionsNatives.dessinerOpenGL();
                    if (currentZoom <= 0)
                    {
                        FonctionsNatives.resetZoom();
                        currentZoom = FonctionsNatives.obtenirZoomCourant();
                    }
                });
            }
            catch (Exception)
            {
            }
            
        }
        

        private void PartieRapide_FormClosing(object sender, FormClosingEventArgs e)
        {
            lock (Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;
            }
        }

        private void PartieRapide_Load(object sender, EventArgs e)
        {

        }

        private void PartieRapide_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
            {
                if (menuStrip.Visible)
                {
                    menuStrip.Visible = false;
                }
                else
                    menuStrip.Visible = true;
            }

            // À enlever : permet de vérifier la fenêtre OpenGL
            else if (e.KeyCode == Keys.Left)
                FonctionsNatives.translater(-50, 0);
            else if (e.KeyCode == Keys.Right)
                FonctionsNatives.translater(50, 0);
            else if (e.KeyCode == Keys.Up)
                FonctionsNatives.translater(0, 50);
            else if (e.KeyCode == Keys.Down)
                FonctionsNatives.translater(0, -50);

            if (e.KeyValue == touches.PGJ1) // Remplacer "R" par la touche obtenue des configurations
            {
                FonctionsNatives.activerPalettesGJ1();
                Console.WriteLine("Touche R enfoncée");// Activer les palettes gauches du joueur 1
            }
        }


        private void PartieRapide_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyValue == touches.PGJ1)
            {
                FonctionsNatives.desactiverPalettesGJ1();
                Console.WriteLine("Touche R relachée");
            }
        }

        private void menu_ReturnItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

    }

    public partial class FonctionsNatives
    {
       
    }
}
