using System;
using System.Drawing;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class CustomConsole : Form
    {
        Point location;
        private string pauseString;
        private bool forcePause = false;
        public CustomConsole()
        {
            InitializeComponent();
            pauseString = "";
            location = new Point(0, 0);
        }
        public void UpdateConsoleTexte()
        {
            pauseString += FonctionsNatives.obtenirConsole();
            if (pause_resume.Checked == false)
            {
                if (pauseString == "")
                    return;
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
            if (Always_Button.Checked)
            {
                MessageBox.Show("You are in 'Always show mode', please uncheck boxe to exit.", "CLOSING DENIED",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            this.Hide();
            FonctionsNatives.bloquerAffichageGlobal(0);
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
            scrollToEnd();
        }

        private void Close_External(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            if (Always_Button.Checked)
            {
                MessageBox.Show("You are in 'Always show mode', please uncheck boxe to exit.", "CLOSING DENIED",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            this.Hide();
            FonctionsNatives.bloquerAffichageGlobal(0);
        }

        private void pause_resume_CheckedChanged(object sender, EventArgs e)
        {
            if (forcePause)
            {
                forcePause = false;
                if (pause_resume.Checked == false)
                {
                    pause_resume.Text = "Pause";
                }
                else
                {
                    pause_resume.Text = "Resume";
                }
            }
            else
            {
                pauseString += FonctionsNatives.obtenirConsole();
                if (pause_resume.Checked == false)
                {
                    pause_resume.Text = "Pause";
                    richTextBox1.AppendText(pauseString);
                    pauseString = "";
                }
                else
                {
                    pause_resume.Text = "Resume";
                }
            }
        }

        private void CustomConsole_Shown(object sender, EventArgs e)
        {
            if (!Always_Button.Checked)
            {
                pause_resume.Checked = false;
                pause_resume.Text = "Pause";
            }
            else
            {
                if (pause_resume.Checked == false)
                {
                    pause_resume.Text = "Pause";
                }
                else
                {
                    pause_resume.Text = "Resume";
                }
            }
            this.Location = location;
        }

        private void scrollToEnd()
        {
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
                if (!Always_Button.Checked)
                {
                    pause_resume.Checked = false;
                    pause_resume.Text = "Pause";
                }
                else
                {
                    if (pause_resume.Checked == false)
                    {
                        pause_resume.Text = "Pause";
                    }
                    else
                    {
                        pause_resume.Text = "Resume";
                    }
                }
            }
            else if (Always_Button.Checked == true)
            {
                this.Visible = true;
                this.ActiveControl = null;
            }
        }
        public void AlwaysShow()
        {
            Always_Button.Checked = true;
        }
        public bool isLocked()
        {
            return Always_Button.Checked;
        }
        public bool isVisible()
        {
            return this.Visible;
        }
        public bool getPauseButton()
        {
            return pause_resume.Checked;
        }
        public void setPauseButton(bool check)
        {
            forcePause = true;
            pause_resume.Checked = check;
        }
        public bool getAlwaysVisible()
        {
            return Always_Button.Checked;
        }
        public void setAlwaysVisible(bool check)
        {
            Always_Button.Checked = check;
        }
        public String getCurrentText()
        {
            return richTextBox1.Text;
        }
        public void setCurrentText(string text)
        {
            richTextBox1.Text = text;
            scrollToEnd();
        }
        public String getPauseText()
        {
            return pauseString;
        }
        public void setPauseText(string text)
        {
            pauseString = text;
        }
        public Point getLocation()
        {
            return this.Location;
        }
        public void setLocation(Point newLocation)
        {
            location = newLocation;
        }
    }
}
