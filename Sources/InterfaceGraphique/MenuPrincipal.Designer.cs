//////////////////////////////////////////////////////////////////////////////
/// @file MenuPrincipal.Designer.cs
/// @author Ballers
/// @date 2015-01-18
/// @version 1.0 
///
/// @ingroup InterfaceGraphique
//////////////////////////////////////////////////////////////////////////////

namespace InterfaceGraphique
{
    partial class MainMenu
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainMenu));
            this.bouton_config = new System.Windows.Forms.Button();
            this.bouton_edit = new System.Windows.Forms.Button();
            this.bouton_quit = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.bouton_pRapide = new System.Windows.Forms.Button();
            this.bouton_campagne = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // bouton_config
            // 
            this.bouton_config.Enabled = false;
            this.bouton_config.FlatAppearance.BorderSize = 0;
            this.bouton_config.FlatAppearance.MouseOverBackColor = System.Drawing.Color.ForestGreen;
            this.bouton_config.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bouton_config.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bouton_config.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.bouton_config.Location = new System.Drawing.Point(0, 318);
            this.bouton_config.Name = "bouton_config";
            this.bouton_config.Size = new System.Drawing.Size(384, 73);
            this.bouton_config.TabIndex = 0;
            this.bouton_config.Text = "Configuration";
            this.bouton_config.UseVisualStyleBackColor = true;
            // 
            // bouton_edit
            // 
            this.bouton_edit.FlatAppearance.BorderSize = 0;
            this.bouton_edit.FlatAppearance.MouseOverBackColor = System.Drawing.SystemColors.ButtonFace;
            this.bouton_edit.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bouton_edit.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bouton_edit.ImageAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.bouton_edit.Location = new System.Drawing.Point(0, 386);
            this.bouton_edit.Name = "bouton_edit";
            this.bouton_edit.Size = new System.Drawing.Size(384, 70);
            this.bouton_edit.TabIndex = 1;
            this.bouton_edit.Text = "Éditeur";
            this.bouton_edit.UseVisualStyleBackColor = true;
            this.bouton_edit.Click += new System.EventHandler(this.bouton_edit_Click);
            this.bouton_edit.MouseEnter += new System.EventHandler(this.bouton_edit_MouseEnter);
            this.bouton_edit.MouseLeave += new System.EventHandler(this.bouton_edit_MouseLeave);
            // 
            // bouton_quit
            // 
            this.bouton_quit.FlatAppearance.BorderSize = 0;
            this.bouton_quit.FlatAppearance.MouseOverBackColor = System.Drawing.SystemColors.ButtonFace;
            this.bouton_quit.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bouton_quit.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bouton_quit.Location = new System.Drawing.Point(0, 462);
            this.bouton_quit.Name = "bouton_quit";
            this.bouton_quit.Size = new System.Drawing.Size(384, 70);
            this.bouton_quit.TabIndex = 2;
            this.bouton_quit.Text = "Quitter";
            this.bouton_quit.UseVisualStyleBackColor = true;
            this.bouton_quit.Click += new System.EventHandler(this.bouton_quit_Click);
            this.bouton_quit.MouseEnter += new System.EventHandler(this.bouton_quit_MouseEnter);
            this.bouton_quit.MouseLeave += new System.EventHandler(this.bouton_quit_MouseLeave);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(384, 170);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox1.TabIndex = 3;
            this.pictureBox1.TabStop = false;
            // 
            // bouton_pRapide
            // 
            this.bouton_pRapide.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.bouton_pRapide.Enabled = false;
            this.bouton_pRapide.FlatAppearance.BorderSize = 0;
            this.bouton_pRapide.FlatAppearance.MouseOverBackColor = System.Drawing.Color.ForestGreen;
            this.bouton_pRapide.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bouton_pRapide.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bouton_pRapide.Location = new System.Drawing.Point(0, 247);
            this.bouton_pRapide.Name = "bouton_pRapide";
            this.bouton_pRapide.Size = new System.Drawing.Size(384, 73);
            this.bouton_pRapide.TabIndex = 4;
            this.bouton_pRapide.Text = "Partie Rapide";
            this.bouton_pRapide.UseVisualStyleBackColor = true;
            // 
            // bouton_campagne
            // 
            this.bouton_campagne.Enabled = false;
            this.bouton_campagne.FlatAppearance.BorderSize = 0;
            this.bouton_campagne.FlatAppearance.MouseOverBackColor = System.Drawing.Color.ForestGreen;
            this.bouton_campagne.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bouton_campagne.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bouton_campagne.Location = new System.Drawing.Point(0, 176);
            this.bouton_campagne.Name = "bouton_campagne";
            this.bouton_campagne.Size = new System.Drawing.Size(384, 73);
            this.bouton_campagne.TabIndex = 5;
            this.bouton_campagne.Text = "Campagne";
            this.bouton_campagne.UseVisualStyleBackColor = true;
            this.bouton_campagne.Click += new System.EventHandler(this.bouton_campagne_Click);
            // 
            // MainMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(384, 533);
            this.Controls.Add(this.bouton_campagne);
            this.Controls.Add(this.bouton_pRapide);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.bouton_quit);
            this.Controls.Add(this.bouton_edit);
            this.Controls.Add(this.bouton_config);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(400, 700);
            this.MinimumSize = new System.Drawing.Size(400, 300);
            this.Name = "MainMenu";
            this.Text = "PainBall";
            this.Shown += new System.EventHandler(this.MainMenu_Shown);
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.Form1_KeyPress);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button bouton_config;
        private System.Windows.Forms.Button bouton_edit;
        private System.Windows.Forms.Button bouton_quit;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button bouton_pRapide;
        private System.Windows.Forms.Button bouton_campagne;
    }
}

