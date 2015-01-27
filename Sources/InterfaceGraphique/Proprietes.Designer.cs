namespace InterfaceGraphique
{
    partial class Proprietes
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
            this.groupe_Collisions = new System.Windows.Forms.GroupBox();
            this.ptsCible_Box = new System.Windows.Forms.TextBox();
            this.ptsButTri_Box = new System.Windows.Forms.TextBox();
            this.ptsButCirc_Box = new System.Windows.Forms.TextBox();
            this.pts_Cible = new System.Windows.Forms.Label();
            this.pts_ButoirTriangulaire = new System.Windows.Forms.Label();
            this.pts_ButoirCirculaire = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupe_Collisions.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupe_Collisions
            // 
            this.groupe_Collisions.Controls.Add(this.ptsCible_Box);
            this.groupe_Collisions.Controls.Add(this.ptsButTri_Box);
            this.groupe_Collisions.Controls.Add(this.ptsButCirc_Box);
            this.groupe_Collisions.Controls.Add(this.pts_Cible);
            this.groupe_Collisions.Controls.Add(this.pts_ButoirTriangulaire);
            this.groupe_Collisions.Controls.Add(this.pts_ButoirCirculaire);
            this.groupe_Collisions.Location = new System.Drawing.Point(6, 10);
            this.groupe_Collisions.Name = "groupe_Collisions";
            this.groupe_Collisions.Size = new System.Drawing.Size(212, 101);
            this.groupe_Collisions.TabIndex = 0;
            this.groupe_Collisions.TabStop = false;
            this.groupe_Collisions.Text = "Points par collision";
            // 
            // ptsCible_Box
            // 
            this.ptsCible_Box.Location = new System.Drawing.Point(109, 71);
            this.ptsCible_Box.Name = "ptsCible_Box";
            this.ptsCible_Box.Size = new System.Drawing.Size(61, 20);
            this.ptsCible_Box.TabIndex = 5;
            // 
            // ptsButTri_Box
            // 
            this.ptsButTri_Box.Location = new System.Drawing.Point(109, 49);
            this.ptsButTri_Box.Name = "ptsButTri_Box";
            this.ptsButTri_Box.Size = new System.Drawing.Size(61, 20);
            this.ptsButTri_Box.TabIndex = 4;
            // 
            // ptsButCirc_Box
            // 
            this.ptsButCirc_Box.Location = new System.Drawing.Point(109, 27);
            this.ptsButCirc_Box.Name = "ptsButCirc_Box";
            this.ptsButCirc_Box.Size = new System.Drawing.Size(61, 20);
            this.ptsButCirc_Box.TabIndex = 3;
            // 
            // pts_Cible
            // 
            this.pts_Cible.AutoSize = true;
            this.pts_Cible.Location = new System.Drawing.Point(12, 74);
            this.pts_Cible.Name = "pts_Cible";
            this.pts_Cible.Size = new System.Drawing.Size(33, 13);
            this.pts_Cible.TabIndex = 2;
            this.pts_Cible.Text = "Cible:";
            this.pts_Cible.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pts_ButoirTriangulaire
            // 
            this.pts_ButoirTriangulaire.AutoSize = true;
            this.pts_ButoirTriangulaire.Location = new System.Drawing.Point(12, 52);
            this.pts_ButoirTriangulaire.Name = "pts_ButoirTriangulaire";
            this.pts_ButoirTriangulaire.Size = new System.Drawing.Size(91, 13);
            this.pts_ButoirTriangulaire.TabIndex = 1;
            this.pts_ButoirTriangulaire.Text = "Butoir triangulaire:";
            this.pts_ButoirTriangulaire.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pts_ButoirCirculaire
            // 
            this.pts_ButoirCirculaire.AutoSize = true;
            this.pts_ButoirCirculaire.Location = new System.Drawing.Point(12, 30);
            this.pts_ButoirCirculaire.Name = "pts_ButoirCirculaire";
            this.pts_ButoirCirculaire.Size = new System.Drawing.Size(82, 13);
            this.pts_ButoirCirculaire.TabIndex = 0;
            this.pts_ButoirCirculaire.Text = "Butoir circulaire:";
            this.pts_ButoirCirculaire.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // groupBox1
            // 
            this.groupBox1.Location = new System.Drawing.Point(231, 17);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 100);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "groupBox1";
            // 
            // Proprietes
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(436, 299);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupe_Collisions);
            this.Name = "Proprietes";
            this.Text = "Proprietes";
            this.groupe_Collisions.ResumeLayout(false);
            this.groupe_Collisions.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupe_Collisions;
        private System.Windows.Forms.Label pts_Cible;
        private System.Windows.Forms.Label pts_ButoirTriangulaire;
        private System.Windows.Forms.Label pts_ButoirCirculaire;
        private System.Windows.Forms.TextBox ptsCible_Box;
        private System.Windows.Forms.TextBox ptsButTri_Box;
        private System.Windows.Forms.TextBox ptsButCirc_Box;
        private System.Windows.Forms.GroupBox groupBox1;
    }
}