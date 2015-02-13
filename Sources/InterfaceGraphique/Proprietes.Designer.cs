//////////////////////////////////////////////////////////////////////////////
/// @file Proprietes.Designer.cs
/// @author Ballers
/// @date 2015-01-27
/// @version 1.0 
///
/// @ingroup InterfaceGraphique
//////////////////////////////////////////////////////////////////////////////

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
            this.ptsVictoire_Label = new System.Windows.Forms.Label();
            this.ptsFreeBall_Label = new System.Windows.Forms.Label();
            this.difficulte_Label = new System.Windows.Forms.Label();
            this.ptsVictoire_Box = new System.Windows.Forms.TextBox();
            this.ptsFreeBall_Box = new System.Windows.Forms.TextBox();
            this.difficulte_ComboBox = new System.Windows.Forms.ComboBox();
            this.propConfirm_Bouton = new System.Windows.Forms.Button();
            this.propAnnuler_Bouton = new System.Windows.Forms.Button();
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
            this.groupe_Collisions.Size = new System.Drawing.Size(225, 101);
            this.groupe_Collisions.TabIndex = 0;
            this.groupe_Collisions.TabStop = false;
            this.groupe_Collisions.Text = "Points par collision";
            // 
            // ptsCible_Box
            // 
            this.ptsCible_Box.Location = new System.Drawing.Point(143, 71);
            this.ptsCible_Box.Name = "ptsCible_Box";
            this.ptsCible_Box.Size = new System.Drawing.Size(61, 20);
            this.ptsCible_Box.TabIndex = 5;
            // 
            // ptsButTri_Box
            // 
            this.ptsButTri_Box.Location = new System.Drawing.Point(143, 49);
            this.ptsButTri_Box.Name = "ptsButTri_Box";
            this.ptsButTri_Box.Size = new System.Drawing.Size(61, 20);
            this.ptsButTri_Box.TabIndex = 4;
            // 
            // ptsButCirc_Box
            // 
            this.ptsButCirc_Box.Location = new System.Drawing.Point(143, 27);
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
            // ptsVictoire_Label
            // 
            this.ptsVictoire_Label.AutoSize = true;
            this.ptsVictoire_Label.Location = new System.Drawing.Point(12, 129);
            this.ptsVictoire_Label.Name = "ptsVictoire_Label";
            this.ptsVictoire_Label.Size = new System.Drawing.Size(99, 13);
            this.ptsVictoire_Label.TabIndex = 1;
            this.ptsVictoire_Label.Text = "Points pour gagner:";
            // 
            // ptsFreeBall_Label
            // 
            this.ptsFreeBall_Label.AutoSize = true;
            this.ptsFreeBall_Label.Location = new System.Drawing.Point(12, 159);
            this.ptsFreeBall_Label.Name = "ptsFreeBall_Label";
            this.ptsFreeBall_Label.Size = new System.Drawing.Size(122, 13);
            this.ptsFreeBall_Label.TabIndex = 2;
            this.ptsFreeBall_Label.Text = "Points pour bille gratuite:";
            // 
            // difficulte_Label
            // 
            this.difficulte_Label.AutoSize = true;
            this.difficulte_Label.Location = new System.Drawing.Point(12, 202);
            this.difficulte_Label.Name = "difficulte_Label";
            this.difficulte_Label.Size = new System.Drawing.Size(51, 13);
            this.difficulte_Label.TabIndex = 3;
            this.difficulte_Label.Text = "Difficulté:";
            // 
            // ptsVictoire_Box
            // 
            this.ptsVictoire_Box.Location = new System.Drawing.Point(137, 126);
            this.ptsVictoire_Box.Name = "ptsVictoire_Box";
            this.ptsVictoire_Box.Size = new System.Drawing.Size(73, 20);
            this.ptsVictoire_Box.TabIndex = 4;
            // 
            // ptsFreeBall_Box
            // 
            this.ptsFreeBall_Box.Location = new System.Drawing.Point(137, 156);
            this.ptsFreeBall_Box.Name = "ptsFreeBall_Box";
            this.ptsFreeBall_Box.Size = new System.Drawing.Size(73, 20);
            this.ptsFreeBall_Box.TabIndex = 5;
            // 
            // difficulte_ComboBox
            // 
            this.difficulte_ComboBox.FormattingEnabled = true;
            this.difficulte_ComboBox.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10"});
            this.difficulte_ComboBox.Location = new System.Drawing.Point(69, 199);
            this.difficulte_ComboBox.MaxDropDownItems = 10;
            this.difficulte_ComboBox.Name = "difficulte_ComboBox";
            this.difficulte_ComboBox.Size = new System.Drawing.Size(56, 21);
            this.difficulte_ComboBox.TabIndex = 6;
            // 
            // propConfirm_Bouton
            // 
            this.propConfirm_Bouton.Location = new System.Drawing.Point(54, 247);
            this.propConfirm_Bouton.Name = "propConfirm_Bouton";
            this.propConfirm_Bouton.Size = new System.Drawing.Size(75, 23);
            this.propConfirm_Bouton.TabIndex = 7;
            this.propConfirm_Bouton.Text = "Confirmer";
            this.propConfirm_Bouton.UseVisualStyleBackColor = true;
            this.propConfirm_Bouton.Click += new System.EventHandler(this.propConfirm_Bouton_Click);
            // 
            // propAnnuler_Bouton
            // 
            this.propAnnuler_Bouton.Location = new System.Drawing.Point(135, 247);
            this.propAnnuler_Bouton.Name = "propAnnuler_Bouton";
            this.propAnnuler_Bouton.Size = new System.Drawing.Size(75, 23);
            this.propAnnuler_Bouton.TabIndex = 8;
            this.propAnnuler_Bouton.Text = "Annuler";
            this.propAnnuler_Bouton.UseVisualStyleBackColor = true;
            this.propAnnuler_Bouton.Click += new System.EventHandler(this.propAnnuler_Bouton_Click);
            // 
            // Proprietes
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(238, 276);
            this.Controls.Add(this.propAnnuler_Bouton);
            this.Controls.Add(this.propConfirm_Bouton);
            this.Controls.Add(this.difficulte_ComboBox);
            this.Controls.Add(this.ptsFreeBall_Box);
            this.Controls.Add(this.ptsVictoire_Box);
            this.Controls.Add(this.difficulte_Label);
            this.Controls.Add(this.ptsFreeBall_Label);
            this.Controls.Add(this.ptsVictoire_Label);
            this.Controls.Add(this.groupe_Collisions);
            this.Icon = global::InterfaceGraphique.Properties.Resources.Pinball;
            this.Name = "Proprietes";
            this.Text = "Propriétés";
            this.groupe_Collisions.ResumeLayout(false);
            this.groupe_Collisions.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupe_Collisions;
        private System.Windows.Forms.Label pts_Cible;
        private System.Windows.Forms.Label pts_ButoirTriangulaire;
        private System.Windows.Forms.Label pts_ButoirCirculaire;
        private System.Windows.Forms.TextBox ptsCible_Box;
        private System.Windows.Forms.TextBox ptsButTri_Box;
        private System.Windows.Forms.TextBox ptsButCirc_Box;
        private System.Windows.Forms.Label ptsVictoire_Label;
        private System.Windows.Forms.Label ptsFreeBall_Label;
        private System.Windows.Forms.Label difficulte_Label;
        private System.Windows.Forms.TextBox ptsVictoire_Box;
        private System.Windows.Forms.TextBox ptsFreeBall_Box;
        private System.Windows.Forms.ComboBox difficulte_ComboBox;
        private System.Windows.Forms.Button propConfirm_Bouton;
        private System.Windows.Forms.Button propAnnuler_Bouton;
    }
}