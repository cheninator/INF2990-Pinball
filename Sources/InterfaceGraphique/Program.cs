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
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.ComponentModel;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Program
    /// @brief Classe qui gère le démarrage de l'application.
    ///
    /// @author Inconnu
    /// @date Inconnue
    /// 
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    static class Program
    {
        private const int NB_IMAGES_PAR_SECONDE = 60; ///< Frame rate de l'application

        public static Object unLock = new Object();
        public static bool peutAfficher = true;

        //private static Exemple exemple;
        // private static mm menu;
        private static MainMenu mMenu; ///< Main Menu de l'application
        private static TimeSpan dernierTemps; ///< Dernier temps enregistré
        private static TimeSpan tempsAccumule; ///< Temps total accumulé
        private static Stopwatch chrono = Stopwatch.StartNew(); ///< Chronometre
        private static TimeSpan tempsEcouleVoulu = TimeSpan.FromTicks(TimeSpan.TicksPerSecond / NB_IMAGES_PAR_SECONDE); ///< Temps avant le rafraichissement

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn static void Main(string[] args)
        /// @brief Le point d'entrée de l'application.
        /// 
        /// @param[in] args : argument passé à la compilation (permet de ddémarrer les tests)
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
                        System.Console.WriteLine("Échec d'un ou plusieurs tests.");
                    else
                        System.Console.WriteLine("Tests réussis.");

                   return;
                }

            chrono.Start();
            Application.Idle += ExecuterQuandInactif;
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
          
            mMenu = new MainMenu();

            Application.Run(mMenu);

        

            
        }

       ////////////////////////////////////////////////////////////////////////
       ///
       /// @fn static void ExecuterQuandInactif(object sender, EventArgs e)
       /// @brief Opérations exécuter lorsque l'application est inactive.
       /// 
       /// @param[in] sender : Objet duquel provient un événement
       /// @param[in] e : Événement qui lance la fonction.
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
                        if ( mMenu.modeEdit != null && peutAfficher)
                            mMenu.modeEdit.MettreAJour((double)tempsAccumule.Ticks / TimeSpan.TicksPerSecond);

                    }
                    tempsAccumule = TimeSpan.Zero;
                }
            }
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
    }
}
