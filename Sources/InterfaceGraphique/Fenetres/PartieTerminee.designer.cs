namespace InterfaceGraphique
{
    partial class PartieTerminee
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
            this.boutonRecommencer = new System.Windows.Forms.Button();
            this.boutonMenuP = new System.Windows.Forms.Button();
            this.labelTermine = new System.Windows.Forms.Label();
            this.imageTermine = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.imageTermine)).BeginInit();
            this.SuspendLayout();
            // 
            // boutonRecommencer
            // 
            this.boutonRecommencer.Location = new System.Drawing.Point(289, 378);
            this.boutonRecommencer.Name = "boutonRecommencer";
            this.boutonRecommencer.Size = new System.Drawing.Size(92, 36);
            this.boutonRecommencer.TabIndex = 0;
            this.boutonRecommencer.Text = "Recommencer";
            this.boutonRecommencer.UseVisualStyleBackColor = true;
            this.boutonRecommencer.Click += new System.EventHandler(this.boutonRecommencer_Click);
            // 
            // boutonMenuP
            // 
            this.boutonMenuP.Location = new System.Drawing.Point(399, 378);
            this.boutonMenuP.Name = "boutonMenuP";
            this.boutonMenuP.Size = new System.Drawing.Size(92, 36);
            this.boutonMenuP.TabIndex = 1;
            this.boutonMenuP.Text = "Retourner au menu principal";
            this.boutonMenuP.UseVisualStyleBackColor = true;
            this.boutonMenuP.Click += new System.EventHandler(this.boutonMenuP_Click);
            // 
            // labelTermine
            // 
            this.labelTermine.Location = new System.Drawing.Point(9, 9);
            this.labelTermine.Name = "labelTermine";
            this.labelTermine.Size = new System.Drawing.Size(482, 13);
            this.labelTermine.TabIndex = 2;
            this.labelTermine.Text = "Félicitations, vous avez remporté la partie!";
            this.labelTermine.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // imageTermine
            // 
            this.imageTermine.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.imageTermine.Location = new System.Drawing.Point(12, 36);
            this.imageTermine.Name = "imageTermine";
            this.imageTermine.Size = new System.Drawing.Size(479, 336);
            this.imageTermine.TabIndex = 3;
            this.imageTermine.TabStop = false;
            // 
            // PartieTerminee
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(503, 426);
            this.Controls.Add(this.imageTermine);
            this.Controls.Add(this.labelTermine);
            this.Controls.Add(this.boutonMenuP);
            this.Controls.Add(this.boutonRecommencer);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = global::InterfaceGraphique.Properties.Resources.Pinball;
            this.MaximizeBox = false;
            this.Name = "PartieTerminee";
            this.Text = "Fin de Partie";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.PartieTerminee_FormClosing);
            this.Shown += new System.EventHandler(this.PartieTerminee_Shown);
            ((System.ComponentModel.ISupportInitialize)(this.imageTermine)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button boutonRecommencer;
        private System.Windows.Forms.Button boutonMenuP;
        private System.Windows.Forms.Label labelTermine;
        private System.Windows.Forms.PictureBox imageTermine;
    }
}