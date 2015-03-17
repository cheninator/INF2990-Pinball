using System;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class CustomConsole : Form
    {
        public CustomConsole()
        {
            InitializeComponent();
        }
        public void UpdateConsoleTexte()
        {
            richTextBox1.Text += FonctionsNatives.obtenirConsole();
            richTextBox1.ScrollToCaret();
        }

        private void Clear_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
        }

        private void Close_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
            this.Hide();
        }

        private void DeleteHistory_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
            FonctionsNatives.viderHistoricConsole();
            richTextBox1.ScrollToCaret();
        }

        private void ShowHistory_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = FonctionsNatives.obtenirHistoriqueConsole();
            richTextBox1.ScrollToCaret();
        }

        private void Close_External(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }
    }
}
