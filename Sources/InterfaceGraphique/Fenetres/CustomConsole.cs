using System;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class CustomConsole : Form
    {
        private string pauseString;

        public CustomConsole()
        {
            InitializeComponent();
            pauseString = "";
        }
        public void UpdateConsoleTexte()
        {
            pauseString += FonctionsNatives.obtenirConsole();
            if (pause_resume.Checked == false)
            {
                richTextBox1.AppendText(pauseString);
                pauseString = "";
                richTextBox1.Select(richTextBox1.Text.Length, 0);
            }
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
        }

        private void Close_External(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }

        private void pause_resume_CheckedChanged(object sender, EventArgs e)
        {
            pauseString += FonctionsNatives.obtenirConsole();
            if (pause_resume.Checked == false)
            {
                pause_resume.Text = "Pause";
                richTextBox1.AppendText(pauseString);
            }
            else
            {
                pause_resume.Text = "Resume";
            }
        }

        private void CustomConsole_Shown(object sender, EventArgs e)
        {
            pause_resume.Checked = false;
            pause_resume.Text = "Pause";
        }

        private void scrollToEnd()
        {
            pauseString = "";
            richTextBox1.AppendText("");
            richTextBox1.SelectionStart = richTextBox1.TextLength;
            richTextBox1.ScrollToCaret();
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            scrollToEnd();
        }

        private void CustomConsole_VisibleChanged(object sender, EventArgs e)
        {
            
            if (this.Visible == true)
            {
                pause_resume.Checked = false;
                pause_resume.Text = "Pause";
            }
            else if (Always_Button.Checked == true)
            {
                this.Visible = true;
                this.ActiveControl = null;
            }
        }
    }
}
