using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Media;
using System.Windows.Forms;
using System.Diagnostics;


namespace InterfaceGraphique
{

    public partial class MainMenu : Form
    {
       System.Media.SoundPlayer player = new System.Media.SoundPlayer(Properties.Resources.button_29);
       public Exemple modeEdit;  
 
        public MainMenu()
        {
            this.KeyPress += new KeyPressEventHandler(Form1_KeyPress);
            InitializeComponent();
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.Image = Properties.Resources.pinball1;
            this.KeyPreview = true;
            StartPosition = FormStartPosition.CenterScreen;
         
           
            
            
        }

       private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {
           
        }

       private void bouton_quit_Click(object sender, EventArgs e)
        {
          this.Dispose();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            

        }

        private void bouton_edit_Click(object sender, EventArgs e)
        {
            this.Hide();
            modeEdit = new Exemple();
            modeEdit.ShowDialog();
            this.Show();
            
           }

        private void bouton_edit_MouseEnter(object sender, EventArgs e)
        {
            bouton_edit.ForeColor = Color.Green;
            bouton_edit.FlatAppearance.BorderColor = Color.Black;
            bouton_edit.FlatAppearance.BorderSize = 1;
            player.Play();
        }

        private void bouton_edit_MouseLeave(object sender, EventArgs e)
        {
            bouton_edit.ForeColor = Color.Black;
            bouton_edit.FlatAppearance.BorderSize = 0;
        }

        private void bouton_quit_MouseEnter(object sender, EventArgs e)
        {
            bouton_quit.FlatAppearance.BorderSize = 1;
            bouton_quit.ForeColor = Color.Red;
            bouton_quit.FlatAppearance.BorderColor = Color.Black;
            player.Play();
            
        }

        private void bouton_quit_MouseLeave(object sender, EventArgs e)
        {
            bouton_quit.FlatAppearance.BorderSize = 0;
            bouton_quit.ForeColor = Color.Black;
        }
        
       

    
 
    }
                                       
}
