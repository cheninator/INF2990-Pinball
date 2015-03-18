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
            richTextBox1.AppendText(FonctionsNatives.obtenirConsole());
            richTextBox1.Select(richTextBox1.Text.Length, 0);
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
        }

        private void ShowHistory_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
            richTextBox1.AppendText(FonctionsNatives.obtenirHistoriqueConsole());
            richTextBox1.Select(richTextBox1.Text.Length, 0);
        }

        private void Close_External(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }
    }
}
