//////////////////////////////////////////////////////////////////////////////
/// @file Program.cs
/// @author Inconnu
/// @date Inconnue
/// @version 1.0 
///
/// @ingroup InterfaceGraphique
//////////////////////////////////////////////////////////////////////////////

/**
*	@defgroup InterfaceGraphique InterfaceGraphique
*	@ingroup INF2990
*  Ce module contient le GUI de l'application.
*/

using System;
using System.Threading;
using System.Diagnostics;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Text;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Program
    /// @brief Classe qui gere le demarrage de l'application.
    ///
    /// @author Inconnu
    /// @date Inconnue
    /// 
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    static class Program
    {
        private const int NB_IMAGES_PAR_SECONDE = 60; ///< Frame rate de l'application
        public static CustomConsoleHandler myCustomConsole;
        public static Object unLock = new Object();
        public static bool peutAfficher = false;
        public static bool tempBool = false;
        //private static Exemple exemple;
        // private static mm menu;
        private static MainMenu mMenu; ///< Main Menu de l'application
        private static TimeSpan dernierTemps; ///< Dernier temps enregistre
        private static TimeSpan tempsAccumule; ///< Temps total accumule
        private static Stopwatch chrono = Stopwatch.StartNew(); ///< Chronometre
        private static TimeSpan tempsEcouleVoulu = TimeSpan.FromTicks(TimeSpan.TicksPerSecond / (NB_IMAGES_PAR_SECONDE * 10)); ///< Temps avant le rafraichissement
        public static int compteurFrames = 0;


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn static void Main(string[] args)
        /// @brief Le point d'entree de l'application.
        /// 
        /// @param[in] args : argument passe a la compilation (permet de demarrer les tests)
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        [STAThread]
        static void Main(string[] args)
        {
            if (args.Length != 0)
                if (args[0] == "testsC++")
                {
                    if (FonctionsNatives.executerTests())
                    {
                        System.Console.WriteLine("Echec d'un ou plusieurs tests.");
                        string s1 = System.Console.ReadLine();
                    }
                    else
                    { 
                        System.Console.WriteLine("Tests reussis.");
                        string s1 = System.Console.ReadLine();
                    }

                   return;
                }
            
            chrono.Start();
            Application.Idle += ExecuterQuandInactif;
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            myCustomConsole = new CustomConsoleHandler();

            mMenu = new MainMenu();

            Application.Run(mMenu);

        

            
        }

       ////////////////////////////////////////////////////////////////////////
       ///
       /// @fn static void ExecuterQuandInactif(object sender, EventArgs e)
       /// @brief Operations executer lorsque l'application est inactive.
       /// 
       /// @param[in] sender : Objet duquel provient un evenement
       /// @param[in] e : evenement qui lance la fonction.
       /// 
       /// @return Aucune.
       ///
       ////////////////////////////////////////////////////////////////////////
       static void ExecuterQuandInactif(object sender, EventArgs e)
        {
            FonctionsNatives.Message message;

            while (!FonctionsNatives.PeekMessage(out message, IntPtr.Zero, 0, 0, 0))
            {
                TimeSpan currentTime = chrono.Elapsed;
                TimeSpan elapsedTime = currentTime - dernierTemps;
                dernierTemps = currentTime;

                tempsAccumule += elapsedTime;

                if (tempsAccumule >= tempsEcouleVoulu)
                {
                    lock (unLock)
                    {
                        if (mMenu.modeEdit != null && peutAfficher)
                        {
                            mMenu.modeEdit.MettreAJour((double)tempsAccumule.Ticks / TimeSpan.TicksPerSecond);
                        }
                        else if (mMenu.modeJeuMain != null && peutAfficher)
                        {
                            mMenu.modeJeuMain.MettreAJour((double)tempsAccumule.Ticks / TimeSpan.TicksPerSecond);
                        }
                        // To remove from here
                        if (compteurFrames == 0)
                        {
                            myCustomConsole.UpdateConsoleTexte();
                        }
                        compteurFrames++;
                        if (compteurFrames >= 10)
                            compteurFrames = 0;
                    }
                    tempsAccumule = TimeSpan.Zero;
                }
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class FullScreen
    /// @brief Gestion du mode Plein ecran.
    ///
    /// @author The Ballers
    /// @date 2015-01-13
    /// 
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    class FullScreen
    {
        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void EnterFullScreenMode(Form targetForm)
        /// @brief Entre en mode Plein ecran.
        /// 
        /// @param[in] targetForm : La form qui passe en mode Plein ecran.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void EnterFullScreenMode(Form targetForm)
        {

            targetForm.WindowState = FormWindowState.Normal;
            //targetForm.FormBorderStyle = FormBorderStyle.None;
            targetForm.WindowState = FormWindowState.Maximized;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void LeaveFullScreenMode(Form targetForm)
        /// @brief Quitte le mode Plein ecran.
        /// 
        /// @param[in] targetForm : La form qui quitte le mode Plein ecran.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public void LeaveFullScreenMode(Form targetForm)
        {
            targetForm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable;
            targetForm.WindowState = FormWindowState.Normal;
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public bool IsFullScreen(Form targetForm)
        /// @brief Indique si une form est en mode Plein ecran.
        /// 
        /// @param[in] targetForm : La form qui quitte le mode Plein ecran.
        /// 
        /// @return True si la form est en Plein ecran, false sinon.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public bool IsFullScreen(Form targetForm)
        {
            return (targetForm.WindowState == FormWindowState.Maximized);
        }
    }


    ///////////////////////////////////////////////////////////////////////////
    /// @class Touches
    /// @brief Classe qui contient les touches pour les palettes
    ///
    /// @author Inconnu
    /// @date Inconnue
    /// 
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////

    public class Touches
    {
        public int PGJ1;
        public int PGJ2;
        public int PDJ1;
        public int PDJ2;
        public int Ressort;
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Touches(int pgj1, int pgj2, int pdj1, int pdj2, int ressort)
        /// @brief Constructeur de la fenetre.
        /// @param[in] pgj1 : palette gauche joueur 1
        /// @param[in] pgj2 : palette gauche joueur 2
        /// @param[in] pdj1 : palette droite joueur 1
        /// @param[in] pdj2 : palette droite joueur 2
        /// @param[in] ressort : ressort
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public Touches(int pgj1, int pgj2, int pdj1, int pdj2, int ressort)
        {
            PGJ1 = pgj1;
            PGJ2 = pgj2;
            PDJ1 = pdj1;
            PDJ2 = pdj2;
            Ressort = ressort;
        }
    }

    public class CustomConsoleHandler
    {
        private CustomConsole cConsole;
        public CustomConsoleHandler()
        {
            cConsole = new CustomConsole();
        }
        public void stopForm()
        {
            cConsole.Dispose();
            cConsole.Close();
        }
        public void Show()
        {
            if (FonctionsNatives.obtenirAffichageGlobal() == 1)
                cConsole.Show();
        }
        public void Hide()
        {
            cConsole.Hide();
        }
        public void AlwaysShow()
        {
            cConsole.Show();
            cConsole.AlwaysShow();
        }
        public void UpdateConsoleTexte()
        {
            if (cConsole.Visible)
                cConsole.UpdateConsoleTexte();
        }
        public void Update()
        {
            ForceHide();
            if (cConsole.Visible || (FonctionsNatives.obtenirAffichageGlobal() == 1) )
                Show();
        }
        public void ForceHide()
        {
            cConsole.ForceHide();
        }
        public bool isVisible()
        {
            return cConsole.isVisible();
        }
        public void reStart()
        {
            bool boutonPause = cConsole.getPauseButton();
            bool alwaysVisible = cConsole.getAlwaysVisible();
            string currentText = cConsole.getCurrentText();
            string pauseText = cConsole.getPauseText();
            stopForm();
            cConsole = new CustomConsole();
            cConsole.setPauseButton(boutonPause);
            cConsole.setAlwaysVisible(alwaysVisible);
            cConsole.setCurrentText(currentText);
            cConsole.setPauseText(pauseText);
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class FonctionsNatives
    /// @brief Classe qui importe les fontions natives C++.
    ///
    /// @author Inconnu
    /// @date Inconnue
    /// 
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    static partial class FonctionsNatives
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct Message
        {
            public IntPtr hWnd;
            public uint Msg;
            public IntPtr wParam;
            public IntPtr lParam;
            public uint Time;
            public System.Drawing.Point Point;
        }

        [DllImport("User32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool PeekMessage(out Message message, IntPtr hWnd, uint filterMin, uint filterMax, uint flags);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool executerTests();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserOpenGL(IntPtr handle);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void libererOpenGL();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void dessinerOpenGL();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animer(double temps);

        [DllImport(@"Noyau.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.BStr)]
        public static extern string obtenirDerniereCampagne();

        [DllImport(@"Noyau.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.BStr)]
        public static extern string obtenirConsole();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterTexteConsole(StringBuilder text, int length);

        [DllImport(@"Noyau.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.BStr)]
        public static extern string obtenirHistoriqueConsole();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void viderHistoricConsole();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void redimensionnerFenetre(int largeur, int hauteur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void creerObjet(StringBuilder value, int length, bool isTwin = false, bool colorShift = false);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool creerObjetAvecTests(StringBuilder value, int length, bool isTwin, bool colorShift, int posX, int posY, int posZ, float angleX, float angleY, float angleZ);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void positionObjet(int x, int y, int z = 0);

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
        public static extern int takeScreenShot(StringBuilder path, int taille, bool square = false, int maxSize = 0);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int selectionnerObjetSousPointClique(int i, int j, int hauteur, int largeur, bool ctrlDown = false);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomIn();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomOut();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void orbite(double phi, double theta);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerSelection(int x1, int y1, int x2, int y2, bool duplication);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void tournerSelectionSouris(int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomInElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomOutElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void agrandirSelection(int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void rectangleElastique(int i, int j);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int selectionMultiple(bool c);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool verifierCliqueDansTable(int x, int y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deselectAll();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getPositionX();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getPositionY();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getAngle();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getScale();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void dupliquerSelection(int i, int j);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void playSound(StringBuilder value, int length, bool stop = false);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void obligerTransparence(bool transparence);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserRectangleElastique(int i, int j);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void terminerRectangleElastique();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void creerMur(int originX, int originY, int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool setProprietesNoeud(int x, int y, int angle, double scale);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirZoomCourant();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirCentreMasseX();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirCentreMasseY();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirTouchePGJ1();
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirTouchePGJ2();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirTouchePDJ1();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirTouchePDJ2();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirToucheRessort();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool resetZoom();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool duplicationEstHorsTable();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void creerFichierConfig(int[] config);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr chargerFichierConfiguration();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr obtenirProprietes(StringBuilder path, int length);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirDifficulte(StringBuilder path, int length);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void creerFichierCampagne(StringBuilder listMaps, int length);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void construireListesPalettes();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mettreAJourListeBillesEtNoeuds();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void activerPalettesGJ1();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void desactiverPalettesGJ1();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void activerPalettesDJ1();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void desactiverPalettesDJ1();
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern  void activerPalettesGJ2();
	    
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern  void desactiverPalettesGJ2();
	    
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern  void activerPalettesDJ2();
	    
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern  void desactiverPalettesDJ2();



        [DllImport(@"Noyau.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.BStr)]
        public static extern string obtenirDerniereCampagne();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void supprimerBille();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void modePause(bool pause);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool spotLight(int lum, bool state);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirAffichagesParSeconde();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirAffichageGlobal();
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void bloquerAffichageGlobal(int active);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserSingleton();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void detruireSingleton();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirPointsGagnerBille();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirPointsGagnerPartie();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreDePointsDePartie();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void resetNombreDePointsDePartie();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreBillesCourante();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirModeDoubleBille();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreDeBilles();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void resetNombreBillesCourantes();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void compresserRessort();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void relacherRessort();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animerJeu(bool animer);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void rechargerArbre(bool recharger);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void activerAI(bool actif);
    }
}
