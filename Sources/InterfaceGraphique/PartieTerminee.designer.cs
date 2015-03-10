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
            this.labelBravo = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // boutonRecommencer
            // 
            this.boutonRecommencer.Location = new System.Drawing.Point(12, 37);
            this.boutonRecommencer.Name = "boutonRecommencer";
            this.boutonRecommencer.Size = new System.Drawing.Size(92, 36);
            this.boutonRecommencer.TabIndex = 0;
            this.boutonRecommencer.Text = "Recommencer la partie";
            this.boutonRecommencer.UseVisualStyleBackColor = true;
            this.boutonRecommencer.Click += new System.EventHandler(this.boutonRecommencer_Click);
            // 
            // boutonMenuP
            // 
            this.boutonMenuP.Location = new System.Drawing.Point(121, 37);
            this.boutonMenuP.Name = "boutonMenuP";
            this.boutonMenuP.Size = new System.Drawing.Size(92, 36);
            this.boutonMenuP.TabIndex = 1;
            this.boutonMenuP.Text = "Retourner au menu principal";
            this.boutonMenuP.UseVisualStyleBackColor = true;
            this.boutonMenuP.Click += new System.EventHandler(this.boutonMenuP_Click);
            // 
            // labelBravo
            // 
            this.labelBravo.AutoSize = true;
            this.labelBravo.Location = new System.Drawing.Point(9, 9);
            this.labelBravo.Name = "labelBravo";
            this.labelBravo.Size = new System.Drawing.Size(204, 13);
            this.labelBravo.TabIndex = 2;
            this.labelBravo.Text = "Félicitations, vous avez remporté la partie!";
            // 
            // PartieTerminee
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(226, 84);
            this.Controls.Add(this.labelBravo);
            this.Controls.Add(this.boutonMenuP);
            this.Controls.Add(this.boutonRecommencer);
            this.MaximizeBox = false;
            this.Name = "PartieTerminee";
            this.Text = "PartieTerminee";
            this.Shown += new System.EventHandler(this.PartieTerminee_Shown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button boutonRecommencer;
        private System.Windows.Forms.Button boutonMenuP;
        private System.Windows.Forms.Label labelBravo;
    }
}