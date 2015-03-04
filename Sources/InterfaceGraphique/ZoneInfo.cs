﻿using System;
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
    public partial class ZoneInfo : Form
    {
        int time;
        public ZoneInfo(string nomZone, string difficulte)
        {
            InitializeComponent();
            this.Icon = Properties.Resources.Pinball;
            this.WindowState = FormWindowState.Normal;
            this.FormBorderStyle = FormBorderStyle.None;
            //targetForm.WindowState = FormWindowState.Maximized;
            time = 5;
            timer1.Enabled = true;
           
            timer1.Interval = 25;
            timer1.Tick += new EventHandler(DecrementProgressBar);
            timer1.Tick += new System.EventHandler(this.timer1_Tick);
            label_Zone.Text = nomZone;
            label_Difficulte.Text = difficulte;
            screenShot.SizeMode = PictureBoxSizeMode.StretchImage;
            screenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\" + nomZone+ ".jpg");
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
         //   time--;
         //   labelTimeLeft.Text = time.ToString();
          //  if (time == 0)
         //       this.Close();
        }

        private void ZoneInfo_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == ' ')
            {
                this.Close();
            }
        }

        private void DecrementProgressBar(object sender, EventArgs e)
        {
            tempRestant.Value--;
            if (tempRestant.Value % 40 == 0)
            {
                time--;
               
                labelTimeLeft.Text = time.ToString();
            }
            if (tempRestant.Value == tempRestant.Minimum)
            {
                timer1.Stop();
                this.Close();
            }
        }
    }
}
