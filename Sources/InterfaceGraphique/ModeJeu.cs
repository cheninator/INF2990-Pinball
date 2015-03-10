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
        private Timer timer;
        private double currentZoom = -1; ///< Zoom courant
        private Touches touches; ///< Les touches pour le jeu
        private ZoneInfo zInfo;
        private int currentZone = 0;
        private int nbZones;
        List<string> myMaps;
        StringBuilder map;
        StringBuilder nextMap;
        StringBuilder tempMap;
        bool peutAnimer;
        bool boolTemp = true;
        private bool activateAmbianteLight = false; ///< Etat de la lumiere ambiante
        private bool activateDirectLight = false; ///< Etat de la lumiere directe
        private bool activateSpotLight = false; ///< Etat de la lumiere spot
        private EtatJeuAbstrait etat; ///< Machine à états
                                      ///
        protected int debugInt;
        public int getDebugInt() { return debugInt; }
        public void setDebugInt(int val) { debugInt = val; }
        public double getCurrentZoom() { return currentZoom; }

        public void setCurrentZoom(double val) { currentZoom = val; }

        public partial class EtatJeuAbstrait
        {
            
            public EtatJeuAbstrait()
            {

            }
            public EtatJeuAbstrait(ModeJeu parent)
            {
                Console.WriteLine("Etat :" + '\t' + "Abstrait");
                this.parent_ = parent;
            }
        };

        public int pointsPartie = 0;
        public int pointsTotale = 0;
        public int billeDisponible = 0;
        private int nombreDeBillesGagnes = 0;
        private int pointsGagnerBille = 0;
        private int pointsGagnerPartie = 0;
        private int billesDisponibles = 0;
        
        public ModeJeu(List<string> maps, int playerType)
        {
            {
                this.WindowState = FormWindowState.Normal;
                this.FormBorderStyle = FormBorderStyle.None;
                this.WindowState = FormWindowState.Maximized;
            }
            timer = new Timer();
            timer.Enabled = true;

            timer.Interval = 3000;
            timer.Tick += new System.EventHandler(this.timer_Tick);
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
            tempMap = new StringBuilder(myMaps[0]);
            Console.WriteLine(nbZones);
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            resetConfig();
            //Console.WriteLine(pointsGagnerPartie);
            //Console.WriteLine(pointsPartie);
            FonctionsNatives.construireListesPalettes();
            currentZone++;
            Program.tempBool = true;
            panel_GL.Focus();

            debugInt = 773;
            Console.WriteLine("taskjhdkjashdjsa");
            etat = new EtatJeuAbstrait(this);
            etat = new EtatJeuDebutDePartie(this);
            etat = new EtatJeuJouer(this);
            etat = new EtatJeuPause(this);
            timer.Start();
          
        }


        private void resetConfig()
        {
            billeDisponible = 0;
            nombreDeBillesGagnes = 0;
            pointsPartie = 0;
            pointsTotale = 0;
            pointsGagnerPartie = FonctionsNatives.obtenirPointsGagnerPartie();
            pointsGagnerBille = FonctionsNatives.obtenirPointsGagnerBille();
            this.PointPartie.Text = pointsPartie.ToString();
            this.nbBilles.Text = "0";
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


        private void timer_Tick(object sender, EventArgs e)
        {
          StringBuilder bille = new StringBuilder("bille");
          FonctionsNatives.creerObjet(bille, bille.Capacity);
          timer.Stop();
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
                        pointsPartie = FonctionsNatives.obtenirNombreDePointsDePartie();

                    }
                   FonctionsNatives.dessinerOpenGL();
                   

                   if (pointsPartie >= nombreDeBillesGagnes * pointsGagnerBille + pointsGagnerBille)
                   {
                       nombreDeBillesGagnes++;
                       billesDisponibles++;
                   }

                   this.PointPartie.Text = pointsPartie.ToString();
                   this.nbBilles.Text = nombreDeBillesGagnes.ToString();
                    
                    if (pointsPartie >= pointsGagnerPartie && boolTemp)
                    {
                        if (currentZone >= nbZones)
                        {
                            peutAnimer = false;
                            boolTemp = false;
                            //FonctionsNatives.supprimerBille();
                            Console.WriteLine(pointsPartie);
                            pointsPartie = 0;
                           // gameOver = new PartieTerminee(true);
                           // gameOver.ShowDialog(this);
                            RecommencerTout();
                          
                            
                        }
                    }

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
            etat.KeyDown(sender, e);
        }


        private void PartieRapide_KeyUp(object sender, KeyEventArgs e)
        {
            etat.KeyUp(sender, e);
        }

        

        private void PartieRapide_redimensionner(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(panel_GL.Width == 0 ? 1 : panel_GL.Width, panel_GL.Height == 0 ? 1 : panel_GL.Height);
        }

        private void PartieRapide_KeyPress(object sender, KeyPressEventArgs e)
        {
            etat.KeyPress(sender, e);
        }

        private void panel_GL_MouseWheel(object sender, MouseEventArgs e)
        {
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
          /*  if (gameOver.Visible)
            {
                gameOver.Close();
                gameOver.Dispose();
            }
           */
            pointsPartie = 0;
            boolTemp = true;
            currentZone = 0;
           map = new StringBuilder(myMaps[0]);
           nextMap = new StringBuilder(map.ToString());
           nextMap.Remove(nextMap.Length - 4, 4);
            Console.WriteLine(map);
            
            zInfo = new ZoneInfo(Path.GetFileName(nextMap.ToString()), FonctionsNatives.obtenirDifficulte(map, map.Capacity).ToString());
            zInfo.ShowDialog();
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            /* 
         FonctionsNatives.ouvrirXML(tempMap, tempMap.Capacity);
           */
            FonctionsNatives.resetNombreDePointsDePartie();
         resetConfig();

         currentZone = 1;
         FonctionsNatives.construireListesPalettes();
         peutAnimer = true;
         timer.Start();
        

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
            timer.Stop();
            this.Close();
        }
        
        private void mPrincipal_menu_Click(object sender, EventArgs e)
        {
            timer.Stop();
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
