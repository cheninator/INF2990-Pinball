using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class PartieTerminee : Form
    {
        System.Media.SoundPlayer player;

        public PartieTerminee(bool victoire)
        {
            InitializeComponent();
            StartPosition = FormStartPosition.CenterScreen;

            if (victoire == false)
            {
                player = new System.Media.SoundPlayer(Properties.Resources.Trombone);
                labelTermine.Text = "Désolé! Vous avez perdu la partie...";
                imageTermine.SizeMode = PictureBoxSizeMode.StretchImage;
                imageTermine.Image = Properties.Resources.Lose;
            }
            else
            {
                player = new System.Media.SoundPlayer(Properties.Resources.Fireworks);
                imageTermine.SizeMode = PictureBoxSizeMode.StretchImage;
                imageTermine.Image = Properties.Resources.Win;
            }

        }

        private void PartieTerminee_Shown(object sender, EventArgs e)
        {
            player.Play();
        }

        private void boutonMenuP_Click(object sender, EventArgs e)
        {
            this.Close();
            ((ModeJeu)this.Owner).Close();
        }

        private void boutonRecommencer_Click(object sender, EventArgs e)
        {
            ((ModeJeu)this.Owner).RecommencerTout();
        }

        private void PartieTerminee_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Close();
            ((ModeJeu)this.Owner).Close();
            player.Stop();
        }
    }
}
