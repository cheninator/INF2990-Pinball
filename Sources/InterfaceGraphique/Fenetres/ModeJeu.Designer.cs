namespace InterfaceGraphique
{
    partial class ModeJeu
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
            this.panel_GL = new System.Windows.Forms.Panel();
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.fichier_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mPrincipal_menu = new System.Windows.Forms.ToolStripMenuItem();
            this.Camera_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Ortho_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Orbitale_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.InfoPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.label_Titre = new System.Windows.Forms.Label();
            this.label_Nom = new System.Windows.Forms.Label();
            this.label_Points = new System.Windows.Forms.Label();
            this.label_nbPoints = new System.Windows.Forms.Label();
            this.label_Billes = new System.Windows.Forms.Label();
            this.label_nbBilles = new System.Windows.Forms.Label();
            this.label_Gagnes = new System.Windows.Forms.Label();
            this.label_nbGagnes = new System.Windows.Forms.Label();
            this.label_Titre2 = new System.Windows.Forms.Label();
            this.label_Win = new System.Windows.Forms.Label();
            this.label_nbWin = new System.Windows.Forms.Label();
            this.label_PointsBille = new System.Windows.Forms.Label();
            this.label_nbPointsBille = new System.Windows.Forms.Label();
            this.label_PointsCible = new System.Windows.Forms.Label();
            this.label_nbPointsCible = new System.Windows.Forms.Label();
            this.label_PointsButC = new System.Windows.Forms.Label();
            this.label_nbPointsButC = new System.Windows.Forms.Label();
            this.label_PointsButT = new System.Windows.Forms.Label();
            this.label_nbPointsButT = new System.Windows.Forms.Label();
            this.panel_GL.SuspendLayout();
            this.menuStrip.SuspendLayout();
            this.InfoPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel_GL
            // 
            this.panel_GL.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel_GL.BackColor = System.Drawing.Color.Transparent;
            this.panel_GL.Controls.Add(this.menuStrip);
            this.panel_GL.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel_GL.Location = new System.Drawing.Point(0, 0);
            this.panel_GL.Name = "panel_GL";
            this.panel_GL.Size = new System.Drawing.Size(633, 453);
            this.panel_GL.TabIndex = 4;
            this.panel_GL.MouseClick += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseClick);
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichier_MenuItem,
            this.Camera_MenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(633, 24);
            this.menuStrip.TabIndex = 0;
            this.menuStrip.Text = "menuStrip1";
            this.menuStrip.Visible = false;
            // 
            // fichier_MenuItem
            // 
            this.fichier_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mPrincipal_menu});
            this.fichier_MenuItem.Name = "fichier_MenuItem";
            this.fichier_MenuItem.Size = new System.Drawing.Size(54, 20);
            this.fichier_MenuItem.Text = "Fichier";
            // 
            // mPrincipal_menu
            // 
            this.mPrincipal_menu.Name = "mPrincipal_menu";
            this.mPrincipal_menu.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Q)));
            this.mPrincipal_menu.Size = new System.Drawing.Size(197, 22);
            this.mPrincipal_menu.Text = "Menu Principal";
            this.mPrincipal_menu.Click += new System.EventHandler(this.mPrincipal_menu_Click);
            // 
            // Camera_MenuItem
            // 
            this.Camera_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Ortho_MenuItem,
            this.Orbitale_MenuItem});
            this.Camera_MenuItem.Name = "Camera_MenuItem";
            this.Camera_MenuItem.Size = new System.Drawing.Size(60, 20);
            this.Camera_MenuItem.Text = "Camera";
            // 
            // Ortho_MenuItem
            // 
            this.Ortho_MenuItem.Name = "Ortho_MenuItem";
            this.Ortho_MenuItem.Size = new System.Drawing.Size(182, 22);
            this.Ortho_MenuItem.Text = "Vue Orthographique";
            // 
            // Orbitale_MenuItem
            // 
            this.Orbitale_MenuItem.Name = "Orbitale_MenuItem";
            this.Orbitale_MenuItem.Size = new System.Drawing.Size(182, 22);
            this.Orbitale_MenuItem.Text = "Vue Orbitale";
            // 
            // InfoPanel
            // 
            this.InfoPanel.BackColor = System.Drawing.Color.Transparent;
            this.InfoPanel.Controls.Add(this.label_Titre);
            this.InfoPanel.Controls.Add(this.label_Nom);
            this.InfoPanel.Controls.Add(this.label_Points);
            this.InfoPanel.Controls.Add(this.label_nbPoints);
            this.InfoPanel.Controls.Add(this.label_Billes);
            this.InfoPanel.Controls.Add(this.label_nbBilles);
            this.InfoPanel.Controls.Add(this.label_Gagnes);
            this.InfoPanel.Controls.Add(this.label_nbGagnes);
            this.InfoPanel.Controls.Add(this.label_Titre2);
            this.InfoPanel.Controls.Add(this.label_Win);
            this.InfoPanel.Controls.Add(this.label_nbWin);
            this.InfoPanel.Controls.Add(this.label_PointsBille);
            this.InfoPanel.Controls.Add(this.label_nbPointsBille);
            this.InfoPanel.Controls.Add(this.label_PointsCible);
            this.InfoPanel.Controls.Add(this.label_nbPointsCible);
            this.InfoPanel.Controls.Add(this.label_PointsButC);
            this.InfoPanel.Controls.Add(this.label_nbPointsButC);
            this.InfoPanel.Controls.Add(this.label_PointsButT);
            this.InfoPanel.Controls.Add(this.label_nbPointsButT);
            this.InfoPanel.Dock = System.Windows.Forms.DockStyle.Right;
            this.InfoPanel.Location = new System.Drawing.Point(443, 0);
            this.InfoPanel.Name = "InfoPanel";
            this.InfoPanel.Size = new System.Drawing.Size(190, 453);
            this.InfoPanel.TabIndex = 5;
            // 
            // label_Titre
            // 
            this.label_Titre.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label_Titre.Location = new System.Drawing.Point(3, 0);
            this.label_Titre.Name = "label_Titre";
            this.label_Titre.Size = new System.Drawing.Size(187, 23);
            this.label_Titre.TabIndex = 0;
            this.label_Titre.Text = "Informations sur la partie courrante";
            this.label_Titre.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_Nom
            // 
            this.label_Nom.Location = new System.Drawing.Point(3, 23);
            this.label_Nom.Name = "label_Nom";
            this.label_Nom.Size = new System.Drawing.Size(187, 23);
            this.label_Nom.TabIndex = 18;
            this.label_Nom.Text = "Nom de la zone:";
            this.label_Nom.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_Points
            // 
            this.label_Points.Location = new System.Drawing.Point(3, 46);
            this.label_Points.Name = "label_Points";
            this.label_Points.Size = new System.Drawing.Size(82, 42);
            this.label_Points.TabIndex = 1;
            this.label_Points.Text = "Points:";
            this.label_Points.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_nbPoints
            // 
            this.label_nbPoints.Location = new System.Drawing.Point(91, 46);
            this.label_nbPoints.Name = "label_nbPoints";
            this.label_nbPoints.Size = new System.Drawing.Size(82, 42);
            this.label_nbPoints.TabIndex = 2;
            this.label_nbPoints.Text = "0";
            this.label_nbPoints.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_Billes
            // 
            this.label_Billes.Location = new System.Drawing.Point(3, 88);
            this.label_Billes.Name = "label_Billes";
            this.label_Billes.Size = new System.Drawing.Size(82, 42);
            this.label_Billes.TabIndex = 3;
            this.label_Billes.Text = "Billes disponibles:";
            this.label_Billes.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_nbBilles
            // 
            this.label_nbBilles.Location = new System.Drawing.Point(91, 88);
            this.label_nbBilles.Name = "label_nbBilles";
            this.label_nbBilles.Size = new System.Drawing.Size(82, 42);
            this.label_nbBilles.TabIndex = 4;
            this.label_nbBilles.Text = "0";
            this.label_nbBilles.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_Gagnes
            // 
            this.label_Gagnes.Location = new System.Drawing.Point(3, 130);
            this.label_Gagnes.Name = "label_Gagnes";
            this.label_Gagnes.Size = new System.Drawing.Size(82, 42);
            this.label_Gagnes.TabIndex = 5;
            this.label_Gagnes.Text = "Billes gagnés:";
            this.label_Gagnes.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_nbGagnes
            // 
            this.label_nbGagnes.Location = new System.Drawing.Point(91, 130);
            this.label_nbGagnes.Name = "label_nbGagnes";
            this.label_nbGagnes.Size = new System.Drawing.Size(82, 42);
            this.label_nbGagnes.TabIndex = 6;
            this.label_nbGagnes.Text = "0";
            this.label_nbGagnes.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_Titre2
            // 
            this.label_Titre2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label_Titre2.Location = new System.Drawing.Point(3, 172);
            this.label_Titre2.Name = "label_Titre2";
            this.label_Titre2.Size = new System.Drawing.Size(187, 23);
            this.label_Titre2.TabIndex = 7;
            this.label_Titre2.Text = "Informations sur la zone";
            this.label_Titre2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_Win
            // 
            this.label_Win.Location = new System.Drawing.Point(3, 195);
            this.label_Win.Name = "label_Win";
            this.label_Win.Size = new System.Drawing.Size(82, 42);
            this.label_Win.TabIndex = 8;
            this.label_Win.Text = "Points pour gagner";
            this.label_Win.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_nbWin
            // 
            this.label_nbWin.Location = new System.Drawing.Point(91, 195);
            this.label_nbWin.Name = "label_nbWin";
            this.label_nbWin.Size = new System.Drawing.Size(82, 42);
            this.label_nbWin.TabIndex = 9;
            this.label_nbWin.Text = "0";
            this.label_nbWin.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_PointsBille
            // 
            this.label_PointsBille.Location = new System.Drawing.Point(3, 237);
            this.label_PointsBille.Name = "label_PointsBille";
            this.label_PointsBille.Size = new System.Drawing.Size(82, 42);
            this.label_PointsBille.TabIndex = 10;
            this.label_PointsBille.Text = "Points pour nouvelle bille:";
            this.label_PointsBille.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_nbPointsBille
            // 
            this.label_nbPointsBille.Location = new System.Drawing.Point(91, 237);
            this.label_nbPointsBille.Name = "label_nbPointsBille";
            this.label_nbPointsBille.Size = new System.Drawing.Size(82, 42);
            this.label_nbPointsBille.TabIndex = 11;
            this.label_nbPointsBille.Text = "0";
            this.label_nbPointsBille.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_PointsCible
            // 
            this.label_PointsCible.Location = new System.Drawing.Point(3, 279);
            this.label_PointsCible.Name = "label_PointsCible";
            this.label_PointsCible.Size = new System.Drawing.Size(82, 42);
            this.label_PointsCible.TabIndex = 12;
            this.label_PointsCible.Text = "Collision avec cible:";
            this.label_PointsCible.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_nbPointsCible
            // 
            this.label_nbPointsCible.Location = new System.Drawing.Point(91, 279);
            this.label_nbPointsCible.Name = "label_nbPointsCible";
            this.label_nbPointsCible.Size = new System.Drawing.Size(82, 42);
            this.label_nbPointsCible.TabIndex = 13;
            this.label_nbPointsCible.Text = "0";
            this.label_nbPointsCible.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_PointsButC
            // 
            this.label_PointsButC.Location = new System.Drawing.Point(3, 321);
            this.label_PointsButC.Name = "label_PointsButC";
            this.label_PointsButC.Size = new System.Drawing.Size(82, 42);
            this.label_PointsButC.TabIndex = 14;
            this.label_PointsButC.Text = "Collision avec butoir circulaire:";
            this.label_PointsButC.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_nbPointsButC
            // 
            this.label_nbPointsButC.Location = new System.Drawing.Point(91, 321);
            this.label_nbPointsButC.Name = "label_nbPointsButC";
            this.label_nbPointsButC.Size = new System.Drawing.Size(82, 42);
            this.label_nbPointsButC.TabIndex = 15;
            this.label_nbPointsButC.Text = "0";
            this.label_nbPointsButC.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_PointsButT
            // 
            this.label_PointsButT.Location = new System.Drawing.Point(3, 363);
            this.label_PointsButT.Name = "label_PointsButT";
            this.label_PointsButT.Size = new System.Drawing.Size(82, 42);
            this.label_PointsButT.TabIndex = 16;
            this.label_PointsButT.Text = "Collision avec butoir triangulaire:";
            this.label_PointsButT.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_nbPointsButT
            // 
            this.label_nbPointsButT.Location = new System.Drawing.Point(91, 363);
            this.label_nbPointsButT.Name = "label_nbPointsButT";
            this.label_nbPointsButT.Size = new System.Drawing.Size(82, 42);
            this.label_nbPointsButT.TabIndex = 17;
            this.label_nbPointsButT.Text = "0";
            this.label_nbPointsButT.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ModeJeu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(633, 453);
            this.Controls.Add(this.InfoPanel);
            this.Controls.Add(this.panel_GL);
            this.Icon = global::InterfaceGraphique.Properties.Resources.Pinball;
            this.MainMenuStrip = this.menuStrip;
            this.Name = "ModeJeu";
            this.Text = "ModeJeu";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.PartieRapide_FormClosing);
            this.Load += new System.EventHandler(this.PartieRapide_Load);
            this.Shown += new System.EventHandler(this.ModeJeu_Shown);
            this.SizeChanged += new System.EventHandler(this.PartieRapide_redimensionner);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.PartieRapide_KeyDown);
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.PartieRapide_KeyPress);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.PartieRapide_KeyUp);
            this.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseWheel);
            this.panel_GL.ResumeLayout(false);
            this.panel_GL.PerformLayout();
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.InfoPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel_GL;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem fichier_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Camera_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Ortho_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Orbitale_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem mPrincipal_menu;
        private System.Windows.Forms.FlowLayoutPanel InfoPanel;
        private System.Windows.Forms.Label label_Titre;
        private System.Windows.Forms.Label label_Points;
        private System.Windows.Forms.Label label_nbPoints;
        private System.Windows.Forms.Label label_Billes;
        private System.Windows.Forms.Label label_nbBilles;
        private System.Windows.Forms.Label label_Gagnes;
        private System.Windows.Forms.Label label_nbGagnes;
        private System.Windows.Forms.Label label_Titre2;
        private System.Windows.Forms.Label label_Win;
        private System.Windows.Forms.Label label_nbWin;
        private System.Windows.Forms.Label label_PointsBille;
        private System.Windows.Forms.Label label_nbPointsBille;
        private System.Windows.Forms.Label label_PointsCible;
        private System.Windows.Forms.Label label_nbPointsCible;
        private System.Windows.Forms.Label label_PointsButC;
        private System.Windows.Forms.Label label_nbPointsButC;
        private System.Windows.Forms.Label label_PointsButT;
        private System.Windows.Forms.Label label_nbPointsButT;
        private System.Windows.Forms.Label label_Nom;
    }
}