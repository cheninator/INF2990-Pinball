using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class ModeJeu : Form
    {
        public PartieTerminee gameOver;
        private double currentZoom = -1; ///< Zoom courant
        private Touches touches; /// les Touches pour le jeux
        private ZoneInfo zInfo;
        private int currentZone = 0;
        private int nbZones;
        List<string> myMaps;
        StringBuilder map;
        StringBuilder nextMap;
        bool peutAnimer;
        private bool activateAmbianteLight = false; ///< Etat de la lumiere ambiante
        private bool activateDirectLight = false; ///< Etat de la lumiere directe
        private bool activateSpotLight = false; ///< Etat de la lumiere spot
        private EtatJeuAbstrait etat; ///< Machine à états
        public int pointsPartie = FonctionsNatives.obtenirNombreDePointsDePartie();
        public int pointsTotale = FonctionsNatives.obtenirNombreDePointsTotals();
        public int billeDisponible;
        private int nombreDeBillesGagner;
        private int nobtenirNombreDePointsPourUneBilleSupplementaire;
        
        private void resetConfig() 
        {
            billeDisponible = 0;
            nombreDeBillesGagner = 0;
            nobtenirNombreDePointsPourUneBilleSupplementaire = FonctionsNatives.obtenirNombreDePointsPourUneBilleSupplementaire();
        }

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
            peutAnimer = true;
            Program.peutAfficher = true;              
            InitialiserAnimation();
            FonctionsNatives.resetZoom();
            currentZoom = -1;
            myMaps = new List<string>(maps);
            nbZones = maps.Count;
            if( nbZones == 1)
                this.Text = "Partie Rapide";
            if (nbZones > 1)
                this.Text = "Campagne";
            map = new StringBuilder(myMaps[0]);
            Console.WriteLine(nbZones);
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            resetConfig();
            FonctionsNatives.construireListesPalettes();
            currentZone++;
            Program.tempBool = true;
            panel_GL.Focus();
            StringBuilder bille = new StringBuilder("bille");
            FonctionsNatives.creerObjet(bille, bille.Capacity);
            gameOver = new PartieTerminee();
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
                    if (peutAnimer)
                    {
                        FonctionsNatives.animer(tempsInterAffichage);
                    }
                   FonctionsNatives.dessinerOpenGL();
                   FPSCounter.Text = FonctionsNatives.obtenirAffichagesParSeconde().ToString();
                   pointsPartie = FonctionsNatives.obtenirNombreDePointsDePartie();
                   pointsTotale = FonctionsNatives.obtenirNombreDePointsTotals();

                   if (pointsPartie > nombreDeBillesGagner * nobtenirNombreDePointsPourUneBilleSupplementaire + nobtenirNombreDePointsPourUneBilleSupplementaire)
                       nombreDeBillesGagner++;

                   this.PointsTotal.Text = pointsTotale.ToString();
                   this.PointPartie.Text = pointsPartie.ToString();
                   this.nbBilles.Text = nombreDeBillesGagner.ToString();

                    if (pointsTotale < pointsPartie)
                    {
                        if (gameOver.Visible == false)
                            gameOver.ShowDialog(this);
                        peutAnimer = false;
                    }
                    /*
                    if (nombreDeBillesGagner <= 0 && pointsTotale >= pointsPartie)
                    {
                        // TODO: En cas de défaut (arranger les fonctions natives pour reset le bon nb de billes sinon
                      * //       c'est toujours 0.
                    }
                    */

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
                    peutAnimer = true;
                 
                }
                else
                {
                    menuStrip.Visible = true;
                    FonctionsNatives.modePause(true);
                    peutAnimer = false;
               
                }
            }
            else if (e.KeyChar == 'b')
            {
                if (FonctionsNatives.obtenirAffichageGlobal() == 0)
                {
                    Console.WriteLine("Affichage bloque. On debloque");
                    FonctionsNatives.bloquerAffichageGlobal(1);
                }
                else
                {
                    Console.WriteLine("Affichage permis. On bloque");
                    FonctionsNatives.bloquerAffichageGlobal(0);
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
                        if(MessageBox.Show("VICTOIRE!!!!VOULEZ VOUR RECOMMENCER?", "FIN DE LA CAMPAGNE",
                   MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation) == DialogResult.Yes)
                        {
                            RecommencerTout();
                        }
                        else
                        {
                            Quitter();
                        }
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
                        resetConfig();
                        FonctionsNatives.construireListesPalettes();
                        currentZone++;
                    }
                    
                }
                else if (e.KeyChar == (char)8)
                {
                    // RELOAD DE LA MAP
                    FonctionsNatives.ouvrirXML(map, map.Capacity);
                    resetConfig();
                }

        }

        private void panel_GL_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
                FonctionsNatives.zoomIn();
            else if (e.Delta < 0)
                FonctionsNatives.zoomOut();
            currentZoom = FonctionsNatives.obtenirZoomCourant();
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void RecommencerTout()
        /// @brief Reinitialise la campagne ou la partie rapide lorsqu'on termine
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void RecommencerTout()
        {
            pointsTotale = 0;
            peutAnimer = true;
            currentZone = 0;
            map = new StringBuilder(myMaps[currentZone]);
            nextMap = new StringBuilder(map.ToString());
            nextMap.Remove(nextMap.Length - 4, 4);
            Console.WriteLine(Path.GetFileName(nextMap.ToString()));
            zInfo = new ZoneInfo(Path.GetFileName(nextMap.ToString()), FonctionsNatives.obtenirDifficulte(map, map.Capacity).ToString());
            zInfo.ShowDialog();
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            resetConfig();
            FonctionsNatives.construireListesPalettes();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Quitter()
        /// @brief Quitte le mode Jeu
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Quitter()
        {
            this.Close();
        }
        
        private void mPrincipal_menu_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void panel_GL_MouseClick(object sender, MouseEventArgs e)
        {
          //  panel_GL.Focus();
        }

    }

    public partial class FonctionsNatives
    {
       
    }
}
