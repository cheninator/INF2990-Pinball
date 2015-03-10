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
            this.labelTimeLeft = new System.Windows.Forms.Label();
            this.labelTimer = new System.Windows.Forms.Label();
            this.labelWarning = new System.Windows.Forms.Label();
            this.tempRestant = new System.Windows.Forms.ProgressBar();
            this.labelPoints = new System.Windows.Forms.Label();
            this.label_Points = new System.Windows.Forms.Label();
            this.labelBille = new System.Windows.Forms.Label();
            this.label_Bille = new System.Windows.Forms.Label();
            this.labelWin = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.screenShot)).BeginInit();
            this.SuspendLayout();
            // 
            // label_Nom
            // 
            this.label_Nom.AutoSize = true;
            this.label_Nom.Location = new System.Drawing.Point(19, 78);
            this.label_Nom.Name = "label_Nom";
            this.label_Nom.Size = new System.Drawing.Size(86, 13);
            this.label_Nom.TabIndex = 0;
            this.label_Nom.Text = "Prochaine Zone:";
            // 
            // label_Rank
            // 
            this.label_Rank.AutoSize = true;
            this.label_Rank.Location = new System.Drawing.Point(19, 108);
            this.label_Rank.Name = "label_Rank";
            this.label_Rank.Size = new System.Drawing.Size(48, 13);
            this.label_Rank.TabIndex = 1;
            this.label_Rank.Text = "Difficulté";
            // 
            // label_Difficulte
            // 
            this.label_Difficulte.AutoSize = true;
            this.label_Difficulte.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_Difficulte.Location = new System.Drawing.Point(173, 108);
            this.label_Difficulte.Name = "label_Difficulte";
            this.label_Difficulte.Size = new System.Drawing.Size(14, 13);
            this.label_Difficulte.TabIndex = 2;
            this.label_Difficulte.Text = "0";
            this.label_Difficulte.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_Zone
            // 
            this.label_Zone.AutoSize = true;
            this.label_Zone.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_Zone.Location = new System.Drawing.Point(173, 78);
            this.label_Zone.Name = "label_Zone";
            this.label_Zone.Size = new System.Drawing.Size(14, 13);
            this.label_Zone.TabIndex = 3;
            this.label_Zone.Text = "0";
            this.label_Zone.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // screenShot
            // 
            this.screenShot.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.screenShot.Location = new System.Drawing.Point(16, 199);
            this.screenShot.Name = "screenShot";
            this.screenShot.Size = new System.Drawing.Size(275, 236);
            this.screenShot.TabIndex = 4;
            this.screenShot.TabStop = false;
            // 
            // labelTimeLeft
            // 
            this.labelTimeLeft.AutoSize = true;
            this.labelTimeLeft.BackColor = System.Drawing.Color.Transparent;
            this.labelTimeLeft.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelTimeLeft.Location = new System.Drawing.Point(247, 443);
            this.labelTimeLeft.Name = "labelTimeLeft";
            this.labelTimeLeft.Size = new System.Drawing.Size(19, 20);
            this.labelTimeLeft.TabIndex = 6;
            this.labelTimeLeft.Text = "5";
            this.labelTimeLeft.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // labelTimer
            // 
            this.labelTimer.AutoSize = true;
            this.labelTimer.Location = new System.Drawing.Point(18, 445);
            this.labelTimer.Name = "labelTimer";
            this.labelTimer.Size = new System.Drawing.Size(157, 13);
            this.labelTimer.TabIndex = 5;
            this.labelTimer.Text = "Temps avant début de la partie:";
            // 
            // labelWarning
            // 
            this.labelWarning.AutoSize = true;
            this.labelWarning.Location = new System.Drawing.Point(19, 492);
            this.labelWarning.Name = "labelWarning";
            this.labelWarning.Size = new System.Drawing.Size(253, 13);
            this.labelWarning.TabIndex = 7;
            this.labelWarning.Text = "(Appuyez sur Espace pour commencer tout de suite)";
            // 
            // tempRestant
            // 
            this.tempRestant.Location = new System.Drawing.Point(16, 466);
            this.tempRestant.Maximum = 200;
            this.tempRestant.Name = "tempRestant";
            this.tempRestant.Size = new System.Drawing.Size(275, 23);
            this.tempRestant.TabIndex = 8;
            this.tempRestant.Value = 200;
            // 
            // labelPoints
            // 
            this.labelPoints.AutoSize = true;
            this.labelPoints.Location = new System.Drawing.Point(18, 138);
            this.labelPoints.Name = "labelPoints";
            this.labelPoints.Size = new System.Drawing.Size(99, 13);
            this.labelPoints.TabIndex = 9;
            this.labelPoints.Text = "Points pour gagner:";
            // 
            // label_Points
            // 
            this.label_Points.AutoSize = true;
            this.label_Points.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_Points.Location = new System.Drawing.Point(173, 138);
            this.label_Points.Name = "label_Points";
            this.label_Points.Size = new System.Drawing.Size(14, 13);
            this.label_Points.TabIndex = 10;
            this.label_Points.Text = "0";
            // 
            // labelBille
            // 
            this.labelBille.AutoSize = true;
            this.labelBille.Location = new System.Drawing.Point(19, 171);
            this.labelBille.Name = "labelBille";
            this.labelBille.Size = new System.Drawing.Size(148, 13);
            this.labelBille.TabIndex = 11;
            this.labelBille.Text = "Points pour une nouvelle bille:";
            // 
            // label_Bille
            // 
            this.label_Bille.AutoSize = true;
            this.label_Bille.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_Bille.Location = new System.Drawing.Point(173, 171);
            this.label_Bille.Name = "label_Bille";
            this.label_Bille.Size = new System.Drawing.Size(14, 13);
            this.label_Bille.TabIndex = 12;
            this.label_Bille.Text = "0";
            // 
            // labelWin
            // 
            this.labelWin.Font = new System.Drawing.Font("Monotype Corsiva", 21.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelWin.Location = new System.Drawing.Point(16, 13);
            this.labelWin.Name = "labelWin";
            this.labelWin.Size = new System.Drawing.Size(275, 53);
            this.labelWin.TabIndex = 13;
            this.labelWin.Text = "Vous avez gagné!!!";
            this.labelWin.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ZoneInfo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(303, 514);
            this.Controls.Add(this.labelTimeLeft);
            this.Controls.Add(this.labelWin);
            this.Controls.Add(this.label_Bille);
            this.Controls.Add(this.labelBille);
            this.Controls.Add(this.label_Points);
            this.Controls.Add(this.labelPoints);
            this.Controls.Add(this.tempRestant);
            this.Controls.Add(this.labelWarning);
            this.Controls.Add(this.labelTimer);
            this.Controls.Add(this.screenShot);
            this.Controls.Add(this.label_Zone);
            this.Controls.Add(this.label_Difficulte);
            this.Controls.Add(this.label_Rank);
            this.Controls.Add(this.label_Nom);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "ZoneInfo";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Information";
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
        private System.Windows.Forms.Label labelTimeLeft;
        private System.Windows.Forms.Label labelTimer;
        private System.Windows.Forms.Label labelWarning;
        private System.Windows.Forms.ProgressBar tempRestant;
        private System.Windows.Forms.Label labelPoints;
        private System.Windows.Forms.Label label_Points;
        private System.Windows.Forms.Label labelBille;
        private System.Windows.Forms.Label label_Bille;
        private System.Windows.Forms.Label labelWin;
    }
}