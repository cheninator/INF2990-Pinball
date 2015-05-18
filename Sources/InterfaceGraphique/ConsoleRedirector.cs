using System;
using System.Drawing;
using System.Threading;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using System.IO;
using System.IO.Pipes;
using System.ComponentModel;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class CustomConsoleHandler
    /// @brief Controle de la console Custom.
    /// @author The Ballers
    /// @date 2015-02-29
    /// 
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    public class CustomConsoleHandler
    {
        private CustomConsole cConsole = null;

        //////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void CustomConsoleHandler(bool active)
        /// @brief Constructeur
        /// 
        /// @param[in] active : Indique si la console est active.
        /// 
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
        public CustomConsoleHandler(bool activate)
        {
            if (activate == false)
                return;
            cConsole = new CustomConsole();
            IntPtr hConsole = GetConsoleWindow();
            if (IntPtr.Zero != hConsole)
            {
                ShowWindow(hConsole, 0);
            }
            FonctionsNatives.activerCustomConsole();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public stopForm()
        /// @brief Ferme la Console.
        /// 
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        public void stopForm()
        {
            if (cConsole == null)
                return;
            cConsole.Dispose();
            cConsole.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Show()
        /// @brief Affiche la Console.
        /// 
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Show()
        {
            if (cConsole == null)
                return;
            if (FonctionsNatives.obtenirAffichageGlobal() == 1)
                cConsole.Show();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Hide()
        /// @brief Cache la Console.
        /// 
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Hide()
        {
            if (cConsole == null)
                return;
            cConsole.Hide();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public AlwaysShow()
        /// @brief Affiche toujours la Console.
        /// 
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        public void AlwaysShow()
        {
            if (cConsole == null)
                return;
            cConsole.Show();
            cConsole.AlwaysShow();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public UpdateConsoleTexte(string text)
        /// @brief Affiche du texte dans la console.
        /// @param[in] text : le texte a afficher.
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        public void UpdateConsoleTexte(string text)
        {
            if (cConsole == null)
                return;
            cConsole.UpdateConsoleTexte(text);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Update()
        /// @brief Mettre a Jour la Console.
        /// 
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Update()
        {
            if (cConsole == null)
                return;
            Hide();
            if (cConsole.getAlwaysVisible())
                cConsole.Show();
        }

        //////////////////////////////////////////////////////////////////////
        //
        // @fn public isVibile()
        // @brief Mettre a Jour la Console.
        // 
        // @return Aucune
        //
        ///////////////////////////////////////////////////////////////////////
        public bool isVisible()
        {
            if (cConsole == null)
                return false;
            return cConsole.isVisible();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public reStart()
        /// @brief Redemarre la Console.
        /// 
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        public void reStart()
        {
            if (cConsole == null)
                return;
            bool boutonPause = cConsole.getPauseButton();
            bool alwaysVisible = cConsole.getAlwaysVisible();
            string currentText = cConsole.getCurrentText();
            string pauseText = cConsole.getPauseText();
            string currentHistory = cConsole.getHistory();
            Point location = cConsole.getLocation();
            stopForm();
            cConsole = new CustomConsole();
            cConsole.setPauseButton(boutonPause);
            cConsole.setAlwaysVisible(alwaysVisible);
            cConsole.setCurrentText(currentText);
            cConsole.setPauseText(pauseText);
            cConsole.setHistory(currentHistory);
            cConsole.setLocation(location);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public WriteLine(string text)
        /// @brief Affiche du texte dans la console.
        /// @param[in] text : le texte a afficher.
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        public void WriteLine( string text)
        {
            if (this == null)
                Console.WriteLine(text);
            else
            {
                text += "\n";
                UpdateConsoleTexte(text);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Write(string text)
        /// @brief Affiche du texte dans la console.
        /// @param[in] text : le texte a afficher.
        /// @return Aucune
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Write(string text)
        {
            if (this == null)
                Console.Write(text);
            else
            {
                UpdateConsoleTexte(text);
            }
        }

        [DllImport("user32.dll")]
        public static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
        [DllImport("kernel32")]
        public static extern IntPtr GetConsoleWindow();
    }
}