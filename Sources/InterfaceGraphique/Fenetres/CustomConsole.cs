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
        }

        private void Clear_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
        }

        private void Close_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
            this.Close();
        }

        private void DeleteHistory_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
            FonctionsNatives.viderHistoricConsole();
        }

        private void ShowHistory_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = FonctionsNatives.obtenirHistoriqueConsole();
        }

        private void Close_External(object sender, FormClosingEventArgs e)
        {
            richTextBox1.Text = "";
        }
    }
}
