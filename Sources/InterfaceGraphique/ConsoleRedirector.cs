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
    public class CustomConsoleHandler
    {
        private CustomConsole cConsole = null;
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
        public void stopForm()
        {
            if (cConsole == null)
                return;
            cConsole.Dispose();
            cConsole.Close();
        }
        public void Show()
        {
            if (cConsole == null)
                return;
            if (FonctionsNatives.obtenirAffichageGlobal() == 1)
                cConsole.Show();
        }
        public void Hide()
        {
            if (cConsole == null)
                return;
            cConsole.Hide();
        }
        public void AlwaysShow()
        {
            if (cConsole == null)
                return;
            cConsole.Show();
            cConsole.AlwaysShow();
        }
        public void UpdateConsoleTexte(string text)
        {
            if (cConsole == null)
                return;
            cConsole.UpdateConsoleTexte(text);
        }
        public void Update()
        {
            if (cConsole == null)
                return;
            Hide();
            if (cConsole.getAlwaysVisible())
                cConsole.Show();
        }
        public bool isVisible()
        {
            if (cConsole == null)
                return false;
            return cConsole.isVisible();
        }
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