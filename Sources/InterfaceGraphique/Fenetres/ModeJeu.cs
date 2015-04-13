//////////////////////////////////////////////////////////////////////////////
/// @file ModeJeu.cs
/// @author Ballers
/// @date 2015-03-10
/// @version 1.0 
///
/// @ingroup Fenetres
//////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class ModeJeu
    /// @brief Classe d'interface du mode jeu.
    ///
    /// @author Ballers
    /// @date 2015-03-10
    /// 
    /// @ingroup Fenetres
    ///////////////////////////////////////////////////////////////////////////
    public partial class ModeJeu : Form
    {
        private bool firstStart = true;
        public PartieTerminee gameOver; ///< Form de fin de partie
        private double currentZoom = -1; ///< Zoom courant
        private Touches touches; ///< Les touches pour le jeu
        private ZoneInfo zInfo;  ///< Form dinfo de prochaine zone
        private int currentZone = 0; ///< la zone a laquelle on est rendue
        private int nbZones;    ///< nombre de Zones dans la campagne/Partie rapide
        private int nombreBillesInit = 0;   /// Nombre de Billes initiales ( 3/5/7)
        private int nombreBillesMax;    ///< nombre maximal de billes en jeu
        List<string> myMaps;    ///< liste des zones a jouer
        StringBuilder map;      ///< la zone en jeu
        StringBuilder nextMap;  ///< prochaine zone
        private FullScreen fullscreen = new FullScreen();
        static StringBuilder Points = new StringBuilder("Points : ");
        static StringBuilder Billes = new StringBuilder("Billes : ");
        bool peutAnimer;
        bool boolTemp = true;   ///< bool pour ne pas spam FinDePartie
        private bool activateAmbiantLight = false; ///< Etat de la lumiere ambiante
        private bool activateDirectLight = false; ///< Etat de la lumiere directe
        private bool activateSpotLight = false; ///< Etat de la lumiere spot
        private EtatJeuAbstrait etat; ///< Machine à états
        int[] proprietes = new int[5];  ///< les proprietes de la zone
        public int pointsPartie = 0;    ///< nombre de points
        public int pointsTotale = 0;    ///< no idea wtf is this

        private int nombreDeBillesGagnes = 0; ///< nombre de billes extras
        private int pointsGagnerBille = 0;  ///< Nombre de Points pour gagner une nouvelle bille
        private int pointsGagnerPartie = 0; ///< Nombre de Points pour gagner une zone
        private int billesDisponibles = 0;  ///< Billes dont le(s) joueur(s) disposent
        public int billesEnJeu = 0;         ///< Billes qui sont sur la zone
        private int nombreDeBillesUtilise = 0; ///< Nombre de Billes deja utilises
        private int billesPerdus = 0;       ///< Nombre de billes tombees dans le trou

        private static StringBuilder informations = new StringBuilder("Appuyez sur 'h' pour afficher plus d'information");
        private static StringBuilder fontArial = new StringBuilder(@"arial.tff");
        private static StringBuilder bgm = new StringBuilder("birdsofsorrow");
        private static StringBuilder winSound = new StringBuilder("campagneWin");
        private static StringBuilder newBallSFX = new StringBuilder("newBall");

        public int panelHeight { get; set; } ///< Hauteur de la fenetre
        public int panelWidth  { get; set; }///< Largeur de la fenetre
        public Point previousP { get; set;}
        public Point currentP  { get; set;}
        
        // Modificateurs
        public void setVisibilityMenuStrip(bool vis) { menuStrip.Visible = vis; }
        public void setCurrentZoom(double val) { currentZoom = val; }
        public void setPeutAnimer(bool activation) { peutAnimer = activation; }
        /*public void setPreviousP(Point prevP) { previousP = prevP; }
        public void setCurrentP(Point currP) { currentP = currP; }*/


        // Accesseurs
        public double getCurrentZoom() { return currentZoom; }
        public Touches getTouches() { return touches; }
        public bool getAmbiantLight() { return activateAmbiantLight; }
        public bool getDirectLight() { return activateDirectLight; }
        public bool getSpotLight() { return activateSpotLight; }
       /* public Point getPreviousP() { return previousP ; }
        public Point getCurrentP() { return currentP ; }*/

        
        // Toggle des lumières
        public void toggleAmbiantLight() { activateAmbiantLight = !activateAmbiantLight; }
        public void toggleDirectLight() { activateDirectLight = !activateDirectLight; }
        public void toggleSpotLight() { activateSpotLight = !activateSpotLight; }

        // Méthodes de changement d'état
        public void pauseGame() { etat = new EtatJeuPause(this); }
        public void resumeGame() { etat = new EtatJeuJouer(this); }

        ///////////////////////////////////////////////////////////////////////////
        /// @class EtatJeuAbstrait
        /// @brief Classe interne (ModeJeu) d'etat abstrait
        ///
        /// @author Ballers
        /// @date 2015-3-10
        ///
        /// @ingroup Fenetres
        ///////////////////////////////////////////////////////////////////////////
        public partial class EtatJeuAbstrait
        {
            public EtatJeuAbstrait() { }
            public EtatJeuAbstrait(ModeJeu parent)
            {
                this.parent_ = parent;
            }
        };

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ModeJeu(List<string> maps, int playerType)
        /// @brief Constructeur par parametre de la fenetre de mode jeu.
        ///
        /// @param[in] maps : Liste de zones a jouer.
        /// @param[in] playerType : Type de joueur (Solo, 2P, AI)
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public ModeJeu(List<string> maps, int playerType)
        {
            this.MouseWheel += new MouseEventHandler(panel_GL_MouseWheel);

            if (FonctionsNatives.obtenirModeDoubleBille() != 0)
            {
                nombreBillesMax = 2;
            }
            else
            {
                nombreBillesMax = 1;
            }

            // Permet d'etablir le type de joueur
            EtablirTouchesEtAI(playerType);

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
            map = new StringBuilder(myMaps[0]);
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            resetConfig();
            nombreBillesInit = FonctionsNatives.obtenirNombreDeBilles();
            FonctionsNatives.construireListesPalettes();
            FonctionsNatives.translater(-10, 0);

            currentZone++;
            Program.tempBool = true;
            panel_GL.Focus();
            string nomMap = Path.GetFileNameWithoutExtension(map.ToString());
            label_Nom.Text = "Nom: " + nomMap;
            if (nbZones == 1)
                this.Text = "Partie Rapide: " + nomMap;
            if (nbZones > 1)
                this.Text = "Campagne: " + nomMap;
            etat = new EtatJeuDebutDePartie(this);
            // Il faut changer le mode car le traitement de début est fini
            etat = new EtatJeuJouer(this);
            FonctionsNatives.animerJeu(true);

            StringBuilder billeSound = new StringBuilder("rolling");

            FonctionsNatives.bouclerSon(bgm, bgm.Length);
            FonctionsNatives.ajusterVolume(bgm, bgm.Length,90);
            FonctionsNatives.ajusterVolume(billeSound, billeSound.Length, 100);
            FonctionsNatives.jouerSon(bgm, bgm.Length);

            if (true)
            {
                StringBuilder myFont = new StringBuilder("Bloodthirsty.ttf");
                // On spécifie la font
                FonctionsNatives.creeTexte(Points, Points.Capacity, myFont, myFont.Capacity);
                FonctionsNatives.creeTexte(Billes, Billes.Capacity, myFont, myFont.Capacity);
                
                // On specifie la taille (en 1/72 de pouce)
                FonctionsNatives.resize(Points, Points.Capacity, 35);
                FonctionsNatives.resize(Billes, Billes.Capacity, 35);

                // On specifie une couleur RGB
                FonctionsNatives.changerCouleurV(Points, Points.Capacity, ColorList.COLOR_Green);
                FonctionsNatives.changerCouleurV(Billes, Billes.Capacity, ColorList.COLOR_White);

                // On specifie la position
                FonctionsNatives.repositionner(Points, Points.Capacity, 1, 1);
                FonctionsNatives.repositionner(Billes, Billes.Capacity, 1, 1);

                // On demande d'afficher !
                FonctionsNatives.afficherTextes();
            }

            panelHeight = panel_GL.Size.Height;
            panelWidth = panel_GL.Size.Width;


            if (Program.playerName.ToLower() == "admin")
            {

                FonctionsNatives.creeTexte(informations, informations.Capacity, fontArial, fontArial.Capacity);
                FonctionsNatives.resize(informations, informations.Capacity, 12);
                FonctionsNatives.changerCouleurV(informations, informations.Capacity, ColorList.COLOR_dark_red);
                FonctionsNatives.repositionner(informations, informations.Capacity, 0, 1);
            }

            fullscreen.EnterFullScreenMode(this);
             
         }



        public void FullScreenChange()
        {
            if (fullscreen.IsFullScreen(this))
            {
                fullscreen.LeaveFullScreenMode(this);
            }
            else
            {
                fullscreen.EnterFullScreenMode(this);
            }
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn protected void resetConfig()
        /// @brief Reset des points et aux configurations de partie.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        protected void resetConfig()
        {
            billesEnJeu = 0;
            FonctionsNatives.resetNombreBillesCourantes();
            nombreDeBillesGagnes = 0;
            nombreDeBillesUtilise = 0;
            pointsPartie = 0;
            pointsTotale = 0;
            pointsGagnerPartie = FonctionsNatives.obtenirPointsGagnerPartie();
            pointsGagnerBille = FonctionsNatives.obtenirPointsGagnerBille();
            nombreBillesInit = FonctionsNatives.obtenirNombreDeBilles();
            billesDisponibles = nombreBillesInit;
            label_nbGagnes.Text = nombreDeBillesGagnes.ToString();
            setProprietes();
            if (!firstStart)
                Program.myCustomConsole.Update();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void setProprietes()
        /// @brief Affichage des proprietes dans les labels correspondants.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void setProprietes()
        {
            IntPtr config = FonctionsNatives.obtenirProprietes(map, map.Capacity);
            Marshal.Copy(config, proprietes, 0, 5);
            label_nbPointsButC.Text = proprietes[0].ToString();
            label_nbPointsButT.Text = proprietes[1].ToString();
            label_nbPointsCible.Text = proprietes[2].ToString();
            label_nbWin.Text = proprietes[3].ToString();
            label_nbPointsBille.Text = proprietes[4].ToString();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn static public void InitialiserAnimation()
        /// @brief Initialise openGL et l'animation.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            this.StartPosition = FormStartPosition.WindowsDefaultBounds;
            FonctionsNatives.initialiserOpenGL(panel_GL.Handle);
            FonctionsNatives.populateUsines();
            FonctionsNatives.dessinerOpenGL();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void MettreAJour(double tempsInterAffichage)
        /// @brief Mise a jour du panneau OpenGL.
        /// @param[in] tempsInterAffichage : Objet duquel provient un evenement.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    FonctionsNatives.refreshText(panel_GL.Size.Width, panel_GL.Size.Height);
                    if (peutAnimer)
                    {
                        FonctionsNatives.animer(tempsInterAffichage);
                        if (Program.compteurFrames == 0)
                        {
                            pointsPartie = FonctionsNatives.obtenirNombreDePointsDePartie();
                            // TODO Exemple a delete
                            StringBuilder precedentText = Points;
                            Points = new StringBuilder("Points : " + pointsPartie.ToString());
                            FonctionsNatives.updateText(precedentText, precedentText.Capacity, Points, Points.Capacity);
                            // FIN DE L'EXEMPLE
                        }
                    }
                    if (Program.compteurFrames == 0)
                    {
                        FonctionsNatives.dessinerOpenGL();
                    }
                    billesEnJeu = FonctionsNatives.obtenirNombreBillesCourante();
                    billesPerdus = FonctionsNatives.obtenirNombreBillesPerdus();
                    billesDisponibles = nombreBillesInit + nombreDeBillesGagnes - billesPerdus - billesEnJeu;
                    if (billesEnJeu < nombreBillesMax && (billesDisponibles > 0))
                    {
                        // Wait a certain time
                        CreerBille();
                    }
                    if (billesDisponibles == 0 && boolTemp && billesEnJeu == 0)
                    {
                        if (nbZones == 1)
                            FinCampagne(false, pointsPartie);
                        else
                            FinCampagne(false, -5);
                    }
                    if (pointsPartie >= nombreDeBillesGagnes * pointsGagnerBille + pointsGagnerBille)
                    {
                        FonctionsNatives.jouerSon(newBallSFX, newBallSFX.Length);
                        nombreDeBillesGagnes++;
                        label_nbGagnes.Text = nombreDeBillesGagnes.ToString();
                    }

                    label_nbPoints.Text = pointsPartie.ToString();
                    if (billesDisponibles >= 0)
                    {
                        label_nbBilles.Text = billesDisponibles.ToString();
                        StringBuilder precedentText = Billes;
                        Billes = new StringBuilder("Billes : " + billesDisponibles.ToString());
                        FonctionsNatives.updateText(precedentText, precedentText.Capacity, Billes, Billes.Capacity);
                    }
                    if (pointsPartie >= pointsGagnerPartie && boolTemp && (nbZones > 1))
                    {
                        if (currentZone >= nbZones)
                        {
                            FinCampagne(true, -5);
                        }
                        else
                        {
                            ProchainePartie();
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_FormClosing(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on ferme la form PartieRapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_FormClosing(object sender, FormClosingEventArgs e)
        {
            FonctionsNatives.arreterToutSons();
            lock (Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;
                Program.tempBool = false;
            }
            Program.myCustomConsole.Hide();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void RecommencerPartie()
        /// @brief Recommence la partie.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void RecommencerPartie()
        {
            resetConfig();
            FonctionsNatives.purgeAll();
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            FonctionsNatives.resetNombreBillesCourantes();
            FonctionsNatives.construireListesPalettes();
            FonctionsNatives.mettreAJourListeBillesEtNoeuds();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void AfficherInformations()
        /// @brief Afficher les informations de la partie.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void AfficherInformations()
        {
            bool estVisible = InfoPanel.Visible;
            InfoPanel.Visible = !InfoPanel.Visible;

            if (!estVisible)
                FonctionsNatives.updateText(informations, informations.Capacity, new StringBuilder(""), 0);
            else
                FonctionsNatives.updateText(new StringBuilder(""), 0, informations, informations.Capacity);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ProchainePartie()
        /// @brief Chargement de la prochaine partie.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ProchainePartie()
        {
            FonctionsNatives.arreterToutSons();
            boolTemp = false;
            peutAnimer = false;
            map = new StringBuilder(myMaps[currentZone]);
            nextMap = new StringBuilder(map.ToString());
            nextMap.Remove(nextMap.Length - 4, 4);
            System.Threading.Thread.Sleep(500);
            zInfo = new ZoneInfo(Path.GetFileName(nextMap.ToString()), FonctionsNatives.obtenirDifficulte(map, map.Capacity).ToString(), true);
            Program.myCustomConsole.Hide();
            this.Hide();
            zInfo.ShowDialog();
            this.Show();
            Program.myCustomConsole.Show();
            if (Program.mMenu.modeJeuMain != null)
            {
                FonctionsNatives.arreterToutSons();
                Program.myCustomConsole.Show();
                Program.mMenu.modeJeuMain.Focus();
            }
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            FonctionsNatives.construireListesPalettes();
            FonctionsNatives.resetNombreDePointsDePartie();
            FonctionsNatives.resetNombreBillesCourantes();
            FonctionsNatives.mettreAJourListeBillesEtNoeuds();
            currentZone++;
            peutAnimer = true;
            boolTemp = true;
            FonctionsNatives.bouclerSon(bgm, bgm.Length);
            FonctionsNatives.ajusterVolume(bgm, bgm.Length, 90);
            FonctionsNatives.jouerSon(bgm, bgm.Length);
            /// La création de l'état s'occupe d'appeler resetConfig
            etat = new EtatJeuDebutDePartie(this);
            // Il faut changer le mode car le traitement de début est fini
            etat = new EtatJeuJouer(this);
            label_Nom.Text = "Nom: " + Path.GetFileNameWithoutExtension(map.ToString());
            if (nbZones == 1)
                this.Text = "Partie Rapide: " + Path.GetFileNameWithoutExtension(map.ToString());
            if (nbZones > 1)
                this.Text = "Campagne: " + Path.GetFileNameWithoutExtension(map.ToString());

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void CreerBille()
        /// @brief Creation d'une nouvelle bille.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void CreerBille()
        {
            StringBuilder bille = new StringBuilder("bille");
            FonctionsNatives.creerObjet(bille, bille.Capacity);
            nombreDeBillesUtilise++;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void FinCampagne(bool active, nbPoints)
        /// @brief Desactivation d'options en fin de campagne.
        /// @param[in] active : valeur d'activation.
        /// @param[in] nbPoints : nombre de points gagne.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void FinCampagne(bool active, int nbPoints)
        {
            if (active)
                FonctionsNatives.jouerSon(winSound, winSound.Length);

            FonctionsNatives.arreterToutSons();
            Program.myCustomConsole.Hide();
            peutAnimer = false;
            boolTemp = false;
            gameOver = new PartieTerminee(active, nbPoints);
            Program.myCustomConsole.Hide();
            gameOver.ShowDialog(this);
            if (Program.mMenu.modeJeuMain != null)
            {
                Program.myCustomConsole.Show();
                Program.mMenu.modeJeuMain.Focus();
            }
        }

        private void PartieRapide_Load(object sender, EventArgs e)
        {

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void EtablirTouchesEtAI(int playerType)
        /// @brief Etablit les touches de jeu et active ou non l'AI selon le mode choisi.
        /// @param[in] playerType : Type de joueur (Solo, 2P, AI).
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void EtablirTouchesEtAI(int playerType)
        {
            if (playerType == 1)
            {
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                 FonctionsNatives.obtenirTouchePGJ1(),
                                 FonctionsNatives.obtenirTouchePDJ1(),
                                 FonctionsNatives.obtenirTouchePDJ1(),
                                 FonctionsNatives.obtenirToucheRessort());
                FonctionsNatives.activerAI(false);
            }
            else if (playerType == 2)
            {
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                FonctionsNatives.obtenirTouchePGJ2(),
                                FonctionsNatives.obtenirTouchePDJ1(),
                                FonctionsNatives.obtenirTouchePDJ2(),
                                FonctionsNatives.obtenirToucheRessort());

                FonctionsNatives.activerAI(false);
            }
            else if (playerType == 3)
            {
                // Le 1337 est la pour rendre l'acces aux touches de joueur 2 invalide
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                1337,
                                FonctionsNatives.obtenirTouchePDJ1(),
                                1337,
                                FonctionsNatives.obtenirToucheRessort());

                FonctionsNatives.activerAI(true);
            }

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_KeyDown(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on appuie sur une touche en partie rapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_KeyDown(object sender, KeyEventArgs e)
        {
            etat.traiterKeyDown(sender, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_KeyUp(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on relache une touche en partie rapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_KeyUp(object sender, KeyEventArgs e)
        {
            etat.traiterKeyUp(sender, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_redimensionner(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on redimensionne la fenetre de partie rapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_redimensionner(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(panel_GL.Width == 0 ? 1 : panel_GL.Width, panel_GL.Height == 0 ? 1 : panel_GL.Height);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_KeyDown(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on appuie et relache une touche en partie rapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_KeyPress(object sender, KeyPressEventArgs e)
        {
            etat.traiterKeyPress(sender, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_MouseWheel(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on utilise la roulette de la souris sur le panel GL.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseWheel(object sender, MouseEventArgs e)
        {
            etat.traiterRoulette(sender, e);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void RecommencerTout()
        /// @brief Reinitialise la campagne ou la partie rapide lorsqu'on termine.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void RecommencerTout()
        {
            if (gameOver.Enabled)
            {
                gameOver.Hide();
            }

            pointsPartie = 0;
            currentZone = 0;
            map = new StringBuilder(myMaps[0]);
            nextMap = new StringBuilder(map.ToString());
            nextMap.Remove(nextMap.Length - 4, 4);
            Program.myCustomConsole.Hide();
            this.Hide();
            zInfo = new ZoneInfo(Path.GetFileName(nextMap.ToString()), FonctionsNatives.obtenirDifficulte(map, map.Capacity).ToString(), false);
            zInfo.ShowDialog();
            this.Show();
            if (Program.mMenu.modeJeuMain != null)
            {
                Program.myCustomConsole.Show();
                Program.mMenu.modeJeuMain.Focus();
            }
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            FonctionsNatives.resetNombreDePointsDePartie();
            FonctionsNatives.resetNombreBillesCourantes();
            FonctionsNatives.construireListesPalettes();
            currentZone = 1;
            peutAnimer = true;
            boolTemp = true;
            FonctionsNatives.jouerSon(bgm, bgm.Length);
            /// La création de l'état s'occupe d'appeler resetConfig
            etat = new EtatJeuDebutDePartie(this);
            // Il faut changer le mode car le traitement de début est fini
            etat = new EtatJeuJouer(this);

            // gameOver.Close();
            gameOver.Dispose();
            label_Nom.Text = "Nom: " + Path.GetFileNameWithoutExtension(map.ToString());



        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Quitter()
        /// @brief Quitte le mode Jeu.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Quitter()
        {
            FonctionsNatives.arreterToutSons();
            // resetConfig();
            Program.myCustomConsole.Hide();
            this.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void mPrincipal_menu_Click(object sender, EventArgs e)
        /// @brief Retour au menu principal lorsqu'on clique sur l'option dans le menu.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void mPrincipal_menu_Click(object sender, EventArgs e)
        {
            Program.myCustomConsole.Hide();
            this.Close();
        }

        private void panel_GL_MouseClick(object sender, MouseEventArgs e)
        {
            //  panel_GL.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ModeJeu_Shown(object sender, EventArgs e)
        /// @brief Affichage/Ajustement de la console custom si utilisee
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ModeJeu_Shown(object sender, EventArgs e)
        {
            var scrren = Screen.PrimaryScreen.Bounds.Height;
            this.Height = (scrren * 3) / 4;

            Program.myCustomConsole.reStart();
            Program.myCustomConsole.Update();
            Program.myCustomConsole.Show();
            if (Program.mMenu.modeJeuMain != null)
                Program.mMenu.modeJeuMain.Focus();
            firstStart = false;

        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ModeJeu_Deactivate(object sender, EventArgs e)
        /// @brief Desactiver les palettes lorsqu'on sort de la form
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ModeJeu_Deactivate(object sender, EventArgs e)
        {
            FonctionsNatives.desactiverPalettesDJ1();
            FonctionsNatives.desactiverPalettesDJ2();
            FonctionsNatives.desactiverPalettesGJ1();
            FonctionsNatives.desactiverPalettesGJ2();
        }

        private void ModeJeu_VisibleChanged(object sender, EventArgs e)
        {
            if (this.Visible == true)
            {
                FonctionsNatives.jouerSon(Program.couvercle, Program.couvercle.Length);
                Program.myCustomConsole.reStart();
                Program.myCustomConsole.Update();
                Program.myCustomConsole.Show();
                if (Program.mMenu.modeJeuMain != null)
                    Program.mMenu.modeJeuMain.Focus();
            }
            else
            {
                Program.myCustomConsole.Hide();
                FonctionsNatives.arreterToutSons();
            }
        }

        private void panel_GL_MouseDown(object sender, MouseEventArgs e)
        {
            etat.traiterMouseDown(sender, e);
        }

        private void panel_GL_MouseUp(object sender, MouseEventArgs e)
        {
            etat.traiterMouseUp(sender, e);
        }

        private void panel_GL_MouseMove(object sender, MouseEventArgs e)
        {
            etat.traiterMouseMove(sender, e);
        }

        private void panel_GL_SizeChanged(object sender, EventArgs e)
        {
            panelHeight = panel_GL.Size.Height;
            panelWidth = panel_GL.Size.Width;
        }

        private void Ortho_MenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.utiliserCameraOrbite(false);
        }

        private void Orbitale_MenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.utiliserCameraOrbite(true);
        }
    }
}