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
        private int typeJoueur;
        private bool fullScreen = false;
        List<string> myMaps;
        StringBuilder map;
        StringBuilder nextMap;

        private bool activateAmbianteLight = false; ///< Etat de la lumiere ambiante
        private bool activateDirectLight = false; ///< Etat de la lumiere directe
        private bool activateSpotLight = false; ///< Etat de la lumiere spot

        public ModeJeu(List<string> maps, int playerType)
        {
           
         /*   if(fullScreen)
            {
                this.WindowState = FormWindowState.Normal;
                this.FormBorderStyle = FormBorderStyle.None;
                this.WindowState = FormWindowState.Maximized;
            }
         */
            EtablirTouches(playerType);
            this.KeyDown += new KeyEventHandler(PartieRapide_KeyDown);
            this.KeyUp += new KeyEventHandler(PartieRapide_KeyUp);
           
            InitializeComponent();
            Program.peutAfficher = true;              
            InitialiserAnimation();

            FonctionsNatives.resetZoom();
            currentZoom = -1;

           
            myMaps = new List<string>(maps);
            nbZones = maps.Count;
            map = new StringBuilder(myMaps[0]);
            Console.WriteLine(nbZones);
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            FonctionsNatives.construireListesPalettes();
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
                   FPSCounter.Text = FonctionsNatives.obtenirAffichagesParSeconde().ToString();

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

        private void EtablirTouches(int playerType)
        {
            if (playerType == 1)
            {
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                 FonctionsNatives.obtenirTouchePGJ1(),
                                 FonctionsNatives.obtenirTouchePDJ1(),
                                 FonctionsNatives.obtenirTouchePDJ1(),
                                 FonctionsNatives.obtenirToucheRessort());
            }
            else if (playerType == 2)
            {
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                FonctionsNatives.obtenirTouchePGJ2(),
                                FonctionsNatives.obtenirTouchePDJ1(),
                                FonctionsNatives.obtenirTouchePDJ2(),
                                FonctionsNatives.obtenirToucheRessort());
            }
            else if (playerType == 3)
            {
                // Le 1337 est la pour rendre l'acces aux touches de joueur 2 invalide
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                1337,
                                FonctionsNatives.obtenirTouchePDJ1(),
                                1337,
                                FonctionsNatives.obtenirToucheRessort());
            }



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

           if (e.KeyValue == touches.PGJ1)
           {
               FonctionsNatives.activerPalettesGJ1();
           }

           else if (e.KeyValue == touches.PGJ2)
           {
               // TODO: palette gauche joueur 2
           }
           else if (e.KeyValue == touches.PDJ1)
           {

           }
           else if (e.KeyValue == touches.PDJ2)
           {

           }
           else if (e.KeyValue == touches.Ressort)
           {

           }
        }


        private void PartieRapide_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyValue == touches.PGJ1)
            {
                FonctionsNatives.desactiverPalettesGJ1();
               // Console.WriteLine("Touche R relachée");
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
                 
                }
                else
                {
                    menuStrip.Visible = true;
                    FonctionsNatives.modePause(true);
               
                }
            }
            else if (e.KeyChar == 'j')
            {
                //Console.WriteLine("LUMIERE AMBIANTE");
                activateAmbianteLight = !activateAmbianteLight;
                FonctionsNatives.spotLight(0, activateAmbianteLight);
            }
            else if (e.KeyChar == 'k')
            {
                //Console.WriteLine("LUMIERE DIRECTE");
                activateDirectLight = !activateDirectLight;
                FonctionsNatives.spotLight(1, activateDirectLight);
            }
            else if (e.KeyChar == 'l')
            {
                //Console.WriteLine("LUMIERE SPOTS");
                activateSpotLight = !activateSpotLight;
                FonctionsNatives.spotLight(2, activateSpotLight);
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
                        FonctionsNatives.construireListesPalettes();
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
