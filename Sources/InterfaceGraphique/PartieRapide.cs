using System;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class PartieRapide : Form
    {
        private double currentZoom = -1; ///< Zoom courant
        public PartieRapide()
        {
           
            InitializeComponent();
            Program.peutAfficher = true;              
            InitialiserAnimation();

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
