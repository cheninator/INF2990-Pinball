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
*  Ce module contient le GUI de l'application et la logique de l'interface.
*/

using System;
using System.Diagnostics;
using System.Windows.Forms;

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
        public static String playerName;
        public static MainMenu mMenu; ///< Main Menu de l'application
        private static TimeSpan dernierTemps; ///< Dernier temps enregistre
        private static TimeSpan tempsAccumule; ///< Temps total accumule
        private static Stopwatch chrono = Stopwatch.StartNew(); ///< Chronometre
        private static TimeSpan tempsEcouleVoulu = TimeSpan.FromTicks(TimeSpan.TicksPerSecond / (NB_IMAGES_PAR_SECONDE * 10)); ///< Temps avant le rafraichissement
        public static int compteurFrames = 0;
        public static bool customConsoleActive = false;
        private static bool noWarnings = false;

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
            {
                if (args[0] == "testsC++")
                {
                    if (FonctionsNatives.executerTests())
                    {
                        Console.WriteLine("Echec d'un ou plusieurs tests.");
                        string s1 = System.Console.ReadLine();
                    }
                    else
                    {
                        Console.WriteLine("Tests reussis.");
                        string s1 = System.Console.ReadLine();
                    }
                    return;
                }
                else if (args[0] == "nowarnings")
                    noWarnings = true;
            }
            if (!noWarnings)
            {
                DialogResult dialogResult = MessageBox.Show("Voulez vous utiliser la console Windows native, ou la console " +
                "sur mesure avec interface graphique? YES pour la console native, NO pour la console GUI.", "Utilisation de la console ?", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (dialogResult == DialogResult.No)
                {
                    DialogResult dialogResult2 = MessageBox.Show("Cette console est encore experimentale. Avertissement: " +
                    "pour la correction des SRS, ne pas utiliser ce mode. Voulez vous toujours utilisez cette console ?", "Etes vous sur ?", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
                    if (dialogResult2 == DialogResult.Yes)
                    {
                        customConsoleActive = true;
                    }
                    else if (dialogResult2 == DialogResult.No)
                    {
                        customConsoleActive = false;
                    }
                }
                else if (dialogResult == DialogResult.Yes)
                {
                    customConsoleActive = false;
                }
            }

            chrono.Start();
            Application.Idle += ExecuterQuandInactif;
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            myCustomConsole = new CustomConsoleHandler(customConsoleActive);
            if (!noWarnings)
            {
                string warningMessage = "\nNous ne sommes pas responsables des bogues et problemes qui pourraient survenir dans cette situation.\n";

                string machineName = System.Environment.MachineName;
                string warningMessageM = "Vous ne semblez pas etre sur une des machines du L-4810 ou du L-4818" + warningMessage;
                if (!(machineName.Contains("L-4810") || machineName.Contains("L-4818")))
                    MessageBox.Show(warningMessageM, "AVERTISSEMENT", MessageBoxButtons.OK, MessageBoxIcon.Warning);

                string windowsName = System.Environment.MachineName;
                string warningMessageW = "Vous ne semblez pas etre sur une version de Windows 7 ou plus recent.\n" + warningMessageM;
                if (!(System.Environment.OSVersion.Version.Major >= 6 &&
                    System.Environment.OSVersion.Version.Minor >= 1))
                    MessageBox.Show(warningMessageW, "AVERTISSEMENT", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }

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
                        compteurFrames++;
                        if (compteurFrames >= 10)
                        {
                            compteurFrames = 0;
                            if (customConsoleActive)
                                myCustomConsole.UpdateConsoleTexte(FonctionsNatives.obtenirCout());
                        }
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
}