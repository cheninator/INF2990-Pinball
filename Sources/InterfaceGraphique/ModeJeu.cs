using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class ModeJeu : Form
    {
        private double currentZoom = -1; ///< Zoom courant
        private Touches touches;
        private ZoneInfo zInfo;
        private int currentZone = 0;
        private int nbZones;
        List<string> myMaps;
        StringBuilder map;
        StringBuilder nextMap;
        public ModeJeu(List<string> maps)
        {
            if(false)
            {
                this.WindowState = FormWindowState.Normal;
                this.FormBorderStyle = FormBorderStyle.None;
                this.WindowState = FormWindowState.Maximized;
            }

            this.WindowState = FormWindowState.Normal;
            this.FormBorderStyle = FormBorderStyle.None;
            this.WindowState = FormWindowState.Maximized;
           
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
            myMaps = new List<string>(maps);
            nbZones = maps.Count;
            map = new StringBuilder(myMaps[0]);
            Console.WriteLine(nbZones);
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            currentZone++;
            Program.tempBool = true;
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
                Program.tempBool = false;
            }
        }

        private void PartieRapide_Load(object sender, EventArgs e)
        {

        }

        private void PartieRapide_KeyDown(object sender, KeyEventArgs e)
        {
           
            // À enlever : permet de vérifier la fenêtre OpenGL
           if (e.KeyCode == Keys.Left)
                FonctionsNatives.translater(-10, 0);
            else if (e.KeyCode == Keys.Right)
                FonctionsNatives.translater(10, 0);
            else if (e.KeyCode == Keys.Up)
                FonctionsNatives.translater(0, 10);
            else if (e.KeyCode == Keys.Down)
                FonctionsNatives.translater(0, -10);

            if (e.KeyValue == touches.PGJ1) // Remplacer "R" par la touche obtenue des configurations
            {
                FonctionsNatives.activerPalettesGJ1();
              //  Console.WriteLine("Touche R enfoncée");// Activer les palettes gauches du joueur 1
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

        

        private void PartieRapide_redimensionner(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(panel_GL.Width == 0 ? 1 : panel_GL.Width, panel_GL.Height == 0 ? 1 : panel_GL.Height);
        }

        private void PartieRapide_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)27)
            {
                if (menuStrip.Visible)
                {
                    menuStrip.Visible = false;
                    FonctionsNatives.modePause(false);
                  //  Console.WriteLine("HIDE");
                }
                else
                {
                    menuStrip.Visible = true;
                    FonctionsNatives.modePause(true);
                 //   Console.WriteLine("SHOW");
                }
            }
            else
                if (e.KeyChar == 'n')
                {
                    Console.WriteLine(currentZone);
                    if (currentZone >= nbZones)
                        MessageBox.Show("VICTOIRE!!!!", "FIN DE LA CAMPAGNE",
                   MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    else
                    {
                        map = new StringBuilder(myMaps[currentZone]);
                        nextMap = new StringBuilder(map.ToString());
                        nextMap.Remove(nextMap.Length - 4, 4);
                        Console.WriteLine(Path.GetFileName(nextMap.ToString()));
                        zInfo = new ZoneInfo(Path.GetFileName(nextMap.ToString()), FonctionsNatives.obtenirDifficulte(map, map.Capacity).ToString());
                        //this.Hide();
                        zInfo.ShowDialog();
                        //this.Show();
                    
                        FonctionsNatives.ouvrirXML(map, map.Capacity);
                        currentZone++;
                    }
                    
                }
                else if (e.KeyChar == (char)8)
                {
                    // RELOAD DE LA MAP
                    FonctionsNatives.ouvrirXML(map, map.Capacity);
                }

        }

        private void mPrincipal_menu_Click(object sender, EventArgs e)
        {
            this.Close();
        }

    }

    public partial class FonctionsNatives
    {
       
    }
}
