namespace InterfaceGraphique
{
    partial class ZoneInfo
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
            this.components = new System.ComponentModel.Container();
            this.label_Nom = new System.Windows.Forms.Label();
            this.label_Rank = new System.Windows.Forms.Label();
            this.label_Difficulte = new System.Windows.Forms.Label();
            this.label_Zone = new System.Windows.Forms.Label();
            this.screenShot = new System.Windows.Forms.PictureBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.screenShot)).BeginInit();
            this.SuspendLayout();
            // 
            // label_Nom
            // 
            this.label_Nom.AutoSize = true;
            this.label_Nom.Location = new System.Drawing.Point(13, 32);
            this.label_Nom.Name = "label_Nom";
            this.label_Nom.Size = new System.Drawing.Size(86, 13);
            this.label_Nom.TabIndex = 0;
            this.label_Nom.Text = "Prochaine Zone:";
            // 
            // label_Rank
            // 
            this.label_Rank.AutoSize = true;
            this.label_Rank.Location = new System.Drawing.Point(13, 62);
            this.label_Rank.Name = "label_Rank";
            this.label_Rank.Size = new System.Drawing.Size(48, 13);
            this.label_Rank.TabIndex = 1;
            this.label_Rank.Text = "Difficulté";
            // 
            // label_Difficulte
            // 
            this.label_Difficulte.AutoSize = true;
            this.label_Difficulte.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_Difficulte.Location = new System.Drawing.Point(157, 62);
            this.label_Difficulte.Name = "label_Difficulte";
            this.label_Difficulte.Size = new System.Drawing.Size(0, 20);
            this.label_Difficulte.TabIndex = 2;
            this.label_Difficulte.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label_Zone
            // 
            this.label_Zone.AutoSize = true;
            this.label_Zone.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_Zone.Location = new System.Drawing.Point(157, 32);
            this.label_Zone.Name = "label_Zone";
            this.label_Zone.Size = new System.Drawing.Size(0, 20);
            this.label_Zone.TabIndex = 3;
            this.label_Zone.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // screenShot
            // 
            this.screenShot.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.screenShot.Location = new System.Drawing.Point(16, 113);
            this.screenShot.Name = "screenShot";
            this.screenShot.Size = new System.Drawing.Size(256, 197);
            this.screenShot.TabIndex = 4;
            this.screenShot.TabStop = false;
            // 
            // ZoneInfo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 322);
            this.Controls.Add(this.screenShot);
            this.Controls.Add(this.label_Zone);
            this.Controls.Add(this.label_Difficulte);
            this.Controls.Add(this.label_Rank);
            this.Controls.Add(this.label_Nom);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "ZoneInfo";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ZoneInfo";
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.ZoneInfo_KeyPress);
            ((System.ComponentModel.ISupportInitialize)(this.screenShot)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label_Nom;
        private System.Windows.Forms.Label label_Rank;
        private System.Windows.Forms.Label label_Difficulte;
        private System.Windows.Forms.Label label_Zone;
        private System.Windows.Forms.PictureBox screenShot;
        private System.Windows.Forms.Timer timer1;
    }
}