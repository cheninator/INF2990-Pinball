//////////////////////////////////////////////////////////////////////////////
/// @file Editeur.Designer.cs
/// @author Ballers
/// @date 2015-01-13
/// @version 1.0 
///
/// @ingroup InterfaceGraphique
//////////////////////////////////////////////////////////////////////////////

namespace InterfaceGraphique
{
    partial class Editeur
    {
        /// <summary>
        /// Variable necessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisees.
        /// </summary>
        /// <param name="disposing">true si les ressources managees doivent etre supprimees ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code genere par le Concepteur Windows Form

        /// <summary>
        /// Methode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette methode avec l'editeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.ToolStripButton Enregistrer_ToolStrip;
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Editeur));
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel_GL = new System.Windows.Forms.Panel();
            this.bouton_Creation = new System.Windows.Forms.Button();
            this.Creation_Panel = new System.Windows.Forms.FlowLayoutPanel();
            this.Groupe_Palettes = new System.Windows.Forms.GroupBox();
            this.PDJ2_bouton = new System.Windows.Forms.Button();
            this.PGJ2_bouton = new System.Windows.Forms.Button();
            this.PDJ1_bouton = new System.Windows.Forms.Button();
            this.PGJ1_bouton = new System.Windows.Forms.Button();
            this.Group_Butoir = new System.Windows.Forms.GroupBox();
            this.butoirCirc_bouton = new System.Windows.Forms.Button();
            this.butoirD_bouton = new System.Windows.Forms.Button();
            this.butoirG_bouton = new System.Windows.Forms.Button();
            this.Cible_bouton = new System.Windows.Forms.Button();
            this.Group_Elements = new System.Windows.Forms.GroupBox();
            this.Gate = new System.Windows.Forms.Button();
            this.Mur_bouton = new System.Windows.Forms.Button();
            this.Portails_bouton = new System.Windows.Forms.Button();
            this.Group_Element2 = new System.Windows.Forms.GroupBox();
            this.Trou_bouton = new System.Windows.Forms.Button();
            this.Generateur_bouton = new System.Windows.Forms.Button();
            this.Ressort_bouton = new System.Windows.Forms.Button();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.Groupe_Outils = new System.Windows.Forms.GroupBox();
            this.bouton_Suppression = new System.Windows.Forms.Button();
            this.bouton_Selection = new System.Windows.Forms.Button();
            this.bouton_Deplacement = new System.Windows.Forms.Button();
            this.bouton_Duplication = new System.Windows.Forms.Button();
            this.bouton_Rotation = new System.Windows.Forms.Button();
            this.bouton_Scaling = new System.Windows.Forms.Button();
            this.OutilGraphique = new System.Windows.Forms.GroupBox();
            this.labelOCourant = new System.Windows.Forms.Label();
            this.Groupe_Proprietes = new System.Windows.Forms.GroupBox();
            this.Annuler_prop_boutn = new System.Windows.Forms.Button();
            this.OK_prop_bouton = new System.Windows.Forms.Button();
            this.Anglebox = new System.Windows.Forms.TextBox();
            this.Angle_label = new System.Windows.Forms.Label();
            this.FMEbox = new System.Windows.Forms.TextBox();
            this.FME_label = new System.Windows.Forms.Label();
            this.Ybox = new System.Windows.Forms.TextBox();
            this.Y_label = new System.Windows.Forms.Label();
            this.Xbox = new System.Windows.Forms.TextBox();
            this.X_label = new System.Windows.Forms.Label();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.MenuP_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.Nouveau_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.Ouvrir_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.EnregistrerSous_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.Annuler_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.Retablir_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.Proprietes_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.ModeTest_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.ZoomIn_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.ZoomOut_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.ZoomElastique_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Nouveau_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Ouvrir_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Enregistrer_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.EnregistrerS_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Proprietes_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ModeTest_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuP_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Edition_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Supprimer_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Annuler_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Retablir_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Outils_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Selection_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Deplacement_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Rotation_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MiseE_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Duplication_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Zoom_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Creation_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PG_J1_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PD_J1_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PG_J2_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PD_J2_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.BTG_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.BTD_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.BC_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Cible_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Portails_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Mur_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Ressort_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.GB_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Trou_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.gateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Vues_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Orthographique_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Orbite_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Information_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip3 = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.testRetourMenuPrincipal = new System.Windows.Forms.ToolStripMenuItem();
            this.testRetourModeEdition = new System.Windows.Forms.ToolStripMenuItem();
            this.caméraToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.orthographiqueToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orbiteToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.printPreviewDialog1 = new System.Windows.Forms.PrintPreviewDialog();
            this.toolTipPaneauCreation = new System.Windows.Forms.ToolTip(this.components);
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            Enregistrer_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.panel1.SuspendLayout();
            this.panel_GL.SuspendLayout();
            this.Creation_Panel.SuspendLayout();
            this.Groupe_Palettes.SuspendLayout();
            this.Group_Butoir.SuspendLayout();
            this.Group_Elements.SuspendLayout();
            this.Group_Element2.SuspendLayout();
            this.flowLayoutPanel1.SuspendLayout();
            this.Groupe_Outils.SuspendLayout();
            this.OutilGraphique.SuspendLayout();
            this.Groupe_Proprietes.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.menuStrip3.SuspendLayout();
            this.SuspendLayout();
            // 
            // Enregistrer_ToolStrip
            // 
            Enregistrer_ToolStrip.AutoSize = false;
            Enregistrer_ToolStrip.BackColor = System.Drawing.Color.Transparent;
            Enregistrer_ToolStrip.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            Enregistrer_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            Enregistrer_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.save1;
            Enregistrer_ToolStrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            Enregistrer_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            Enregistrer_ToolStrip.Name = "Enregistrer_ToolStrip";
            Enregistrer_ToolStrip.Size = new System.Drawing.Size(35, 30);
            Enregistrer_ToolStrip.Text = "Enregistrer";
            Enregistrer_ToolStrip.ToolTipText = "Enregistrer (CTRL + S)";
            Enregistrer_ToolStrip.Click += new System.EventHandler(this.Enregistrer_ToolStrip_Click);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.panel_GL);
            this.panel1.Controls.Add(this.Creation_Panel);
            this.panel1.Controls.Add(this.flowLayoutPanel1);
            this.panel1.Controls.Add(this.toolStrip1);
            this.panel1.Controls.Add(this.menuStrip1);
            this.panel1.Controls.Add(this.menuStrip3);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(956, 731);
            this.panel1.TabIndex = 0;
            this.panel1.Click += new System.EventHandler(this.panel1_Click);
            // 
            // panel_GL
            // 
            this.panel_GL.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel_GL.BackColor = System.Drawing.Color.Transparent;
            this.panel_GL.Controls.Add(this.bouton_Creation);
            this.panel_GL.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel_GL.Location = new System.Drawing.Point(189, 59);
            this.panel_GL.Name = "panel_GL";
            this.panel_GL.Size = new System.Drawing.Size(528, 670);
            this.panel_GL.TabIndex = 4;
            this.panel_GL.SizeChanged += new System.EventHandler(this.panel_GL_SizeChanged);
            this.panel_GL.MouseClick += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseClick);
            this.panel_GL.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseDown);
            this.panel_GL.MouseLeave += new System.EventHandler(this.panel_GL_MouseLeave);
            this.panel_GL.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseUp);
            this.panel_GL.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseWheel);
            // 
            // bouton_Creation
            // 
            this.bouton_Creation.Dock = System.Windows.Forms.DockStyle.Right;
            this.bouton_Creation.Font = new System.Drawing.Font("Stencil", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bouton_Creation.Location = new System.Drawing.Point(505, 0);
            this.bouton_Creation.Name = "bouton_Creation";
            this.bouton_Creation.Size = new System.Drawing.Size(23, 670);
            this.bouton_Creation.TabIndex = 5;
            this.bouton_Creation.Text = ">>>";
            this.bouton_Creation.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.toolTipPaneauCreation.SetToolTip(this.bouton_Creation, "Paneau Création");
            this.bouton_Creation.UseVisualStyleBackColor = true;
            this.bouton_Creation.Click += new System.EventHandler(this.bouton_Creation_Click);
            // 
            // Creation_Panel
            // 
            this.Creation_Panel.BackColor = System.Drawing.SystemColors.InactiveBorder;
            this.Creation_Panel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Creation_Panel.Controls.Add(this.Groupe_Palettes);
            this.Creation_Panel.Controls.Add(this.Group_Butoir);
            this.Creation_Panel.Controls.Add(this.Group_Elements);
            this.Creation_Panel.Controls.Add(this.Group_Element2);
            this.Creation_Panel.Dock = System.Windows.Forms.DockStyle.Right;
            this.Creation_Panel.Location = new System.Drawing.Point(717, 59);
            this.Creation_Panel.Name = "Creation_Panel";
            this.Creation_Panel.Size = new System.Drawing.Size(237, 670);
            this.Creation_Panel.TabIndex = 2;
            this.Creation_Panel.MouseEnter += new System.EventHandler(this.Creation_Panel_MouseEnter);
            // 
            // Groupe_Palettes
            // 
            this.Groupe_Palettes.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.Groupe_Palettes.Controls.Add(this.PDJ2_bouton);
            this.Groupe_Palettes.Controls.Add(this.PGJ2_bouton);
            this.Groupe_Palettes.Controls.Add(this.PDJ1_bouton);
            this.Groupe_Palettes.Controls.Add(this.PGJ1_bouton);
            this.Groupe_Palettes.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Groupe_Palettes.Location = new System.Drawing.Point(15, 10);
            this.Groupe_Palettes.Margin = new System.Windows.Forms.Padding(15, 10, 3, 5);
            this.Groupe_Palettes.Name = "Groupe_Palettes";
            this.Groupe_Palettes.Size = new System.Drawing.Size(205, 140);
            this.Groupe_Palettes.TabIndex = 5;
            this.Groupe_Palettes.TabStop = false;
            this.Groupe_Palettes.Text = "Palettes";
            // 
            // PDJ2_bouton
            // 
            this.PDJ2_bouton.BackColor = System.Drawing.Color.White;
            this.PDJ2_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.PDJ2;
            this.PDJ2_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PDJ2_bouton.Location = new System.Drawing.Point(107, 79);
            this.PDJ2_bouton.Name = "PDJ2_bouton";
            this.PDJ2_bouton.Size = new System.Drawing.Size(85, 50);
            this.PDJ2_bouton.TabIndex = 3;
            this.PDJ2_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.toolTip1.SetToolTip(this.PDJ2_bouton, "Joueur 2");
            this.PDJ2_bouton.UseVisualStyleBackColor = false;
            this.PDJ2_bouton.Click += new System.EventHandler(this.PDJ2_bouton_Click);
            // 
            // PGJ2_bouton
            // 
            this.PGJ2_bouton.BackColor = System.Drawing.Color.White;
            this.PGJ2_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.PGJ2;
            this.PGJ2_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PGJ2_bouton.Location = new System.Drawing.Point(16, 79);
            this.PGJ2_bouton.Name = "PGJ2_bouton";
            this.PGJ2_bouton.Size = new System.Drawing.Size(85, 50);
            this.PGJ2_bouton.TabIndex = 2;
            this.PGJ2_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.toolTip1.SetToolTip(this.PGJ2_bouton, "Joueur 2");
            this.PGJ2_bouton.UseVisualStyleBackColor = false;
            this.PGJ2_bouton.Click += new System.EventHandler(this.PGJ2_bouton_Click);
            // 
            // PDJ1_bouton
            // 
            this.PDJ1_bouton.BackColor = System.Drawing.Color.White;
            this.PDJ1_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.PDJ1;
            this.PDJ1_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PDJ1_bouton.Location = new System.Drawing.Point(106, 23);
            this.PDJ1_bouton.Name = "PDJ1_bouton";
            this.PDJ1_bouton.Size = new System.Drawing.Size(85, 50);
            this.PDJ1_bouton.TabIndex = 1;
            this.PDJ1_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.toolTip1.SetToolTip(this.PDJ1_bouton, "Joueur 1");
            this.PDJ1_bouton.UseVisualStyleBackColor = false;
            this.PDJ1_bouton.Click += new System.EventHandler(this.PDJ1_bouton_Click);
            // 
            // PGJ1_bouton
            // 
            this.PGJ1_bouton.BackColor = System.Drawing.Color.White;
            this.PGJ1_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.PGJ1;
            this.PGJ1_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PGJ1_bouton.Location = new System.Drawing.Point(16, 23);
            this.PGJ1_bouton.Name = "PGJ1_bouton";
            this.PGJ1_bouton.Size = new System.Drawing.Size(85, 50);
            this.PGJ1_bouton.TabIndex = 0;
            this.PGJ1_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.toolTip1.SetToolTip(this.PGJ1_bouton, "Joueur 1");
            this.PGJ1_bouton.UseVisualStyleBackColor = false;
            this.PGJ1_bouton.Click += new System.EventHandler(this.PGJ1_bouton_Click);
            // 
            // Group_Butoir
            // 
            this.Group_Butoir.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.Group_Butoir.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Group_Butoir.Controls.Add(this.butoirCirc_bouton);
            this.Group_Butoir.Controls.Add(this.butoirD_bouton);
            this.Group_Butoir.Controls.Add(this.butoirG_bouton);
            this.Group_Butoir.Controls.Add(this.Cible_bouton);
            this.Group_Butoir.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Group_Butoir.Location = new System.Drawing.Point(15, 162);
            this.Group_Butoir.Margin = new System.Windows.Forms.Padding(15, 7, 3, 5);
            this.Group_Butoir.Name = "Group_Butoir";
            this.Group_Butoir.Size = new System.Drawing.Size(205, 140);
            this.Group_Butoir.TabIndex = 6;
            this.Group_Butoir.TabStop = false;
            this.Group_Butoir.Text = "Butoirs et Cibles";
            this.Group_Butoir.Enter += new System.EventHandler(this.Group_Butoir_Enter);
            // 
            // butoirCirc_bouton
            // 
            this.butoirCirc_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.cible1;
            this.butoirCirc_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.butoirCirc_bouton.Location = new System.Drawing.Point(16, 81);
            this.butoirCirc_bouton.Name = "butoirCirc_bouton";
            this.butoirCirc_bouton.Size = new System.Drawing.Size(85, 50);
            this.butoirCirc_bouton.TabIndex = 2;
            this.butoirCirc_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.toolTip1.SetToolTip(this.butoirCirc_bouton, "Butoir circulaire");
            this.butoirCirc_bouton.UseVisualStyleBackColor = true;
            this.butoirCirc_bouton.Click += new System.EventHandler(this.butourCirc_bouton_Click);
            // 
            // butoirD_bouton
            // 
            this.butoirD_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.ButoirTriangD;
            this.butoirD_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.butoirD_bouton.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.butoirD_bouton.Location = new System.Drawing.Point(107, 25);
            this.butoirD_bouton.Name = "butoirD_bouton";
            this.butoirD_bouton.Size = new System.Drawing.Size(85, 50);
            this.butoirD_bouton.TabIndex = 1;
            this.butoirD_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.toolTip1.SetToolTip(this.butoirD_bouton, "Butoir droit");
            this.butoirD_bouton.UseVisualStyleBackColor = true;
            this.butoirD_bouton.Click += new System.EventHandler(this.butoirD_bouton_Click);
            // 
            // butoirG_bouton
            // 
            this.butoirG_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.ButoirTriangG;
            this.butoirG_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.butoirG_bouton.Location = new System.Drawing.Point(16, 25);
            this.butoirG_bouton.Name = "butoirG_bouton";
            this.butoirG_bouton.Size = new System.Drawing.Size(85, 50);
            this.butoirG_bouton.TabIndex = 0;
            this.butoirG_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.toolTip1.SetToolTip(this.butoirG_bouton, "Butoir gauche");
            this.butoirG_bouton.UseVisualStyleBackColor = true;
            this.butoirG_bouton.Click += new System.EventHandler(this.butoirG_bouton_Click);
            // 
            // Cible_bouton
            // 
            this.Cible_bouton.BackColor = System.Drawing.Color.White;
            this.Cible_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.cible;
            this.Cible_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.Cible_bouton.Location = new System.Drawing.Point(107, 81);
            this.Cible_bouton.Name = "Cible_bouton";
            this.Cible_bouton.Size = new System.Drawing.Size(85, 50);
            this.Cible_bouton.TabIndex = 0;
            this.Cible_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.toolTip1.SetToolTip(this.Cible_bouton, "Cible");
            this.Cible_bouton.UseVisualStyleBackColor = false;
            this.Cible_bouton.Click += new System.EventHandler(this.Cible_bouton_Click);
            // 
            // Group_Elements
            // 
            this.Group_Elements.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.Group_Elements.Controls.Add(this.Gate);
            this.Group_Elements.Controls.Add(this.Mur_bouton);
            this.Group_Elements.Controls.Add(this.Portails_bouton);
            this.Group_Elements.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Group_Elements.Location = new System.Drawing.Point(15, 314);
            this.Group_Elements.Margin = new System.Windows.Forms.Padding(15, 7, 3, 5);
            this.Group_Elements.Name = "Group_Elements";
            this.Group_Elements.Size = new System.Drawing.Size(205, 140);
            this.Group_Elements.TabIndex = 7;
            this.Group_Elements.TabStop = false;
            this.Group_Elements.Text = "Éléments";
            this.Group_Elements.Enter += new System.EventHandler(this.Group_Elements_Enter);
            // 
            // Gate
            // 
            this.Gate.BackColor = System.Drawing.Color.White;
            this.Gate.BackgroundImage = global::InterfaceGraphique.Properties.Resources.gate;
            this.Gate.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Gate.Location = new System.Drawing.Point(68, 80);
            this.Gate.Name = "Gate";
            this.Gate.Size = new System.Drawing.Size(85, 50);
            this.Gate.TabIndex = 7;
            this.Gate.Tag = "Gate";
            this.Gate.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.toolTip1.SetToolTip(this.Gate, "Porte");
            this.Gate.UseVisualStyleBackColor = false;
            this.Gate.Click += new System.EventHandler(this.Gate_Button_Click);
            // 
            // Mur_bouton
            // 
            this.Mur_bouton.BackColor = System.Drawing.Color.White;
            this.Mur_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.mur;
            this.Mur_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Mur_bouton.Location = new System.Drawing.Point(19, 24);
            this.Mur_bouton.Name = "Mur_bouton";
            this.Mur_bouton.Size = new System.Drawing.Size(85, 50);
            this.Mur_bouton.TabIndex = 2;
            this.Mur_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.toolTip1.SetToolTip(this.Mur_bouton, "Mur");
            this.Mur_bouton.UseVisualStyleBackColor = false;
            this.Mur_bouton.Click += new System.EventHandler(this.Mur_bouton_Click);
            // 
            // Portails_bouton
            // 
            this.Portails_bouton.BackColor = System.Drawing.Color.White;
            this.Portails_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.portail;
            this.Portails_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.Portails_bouton.Location = new System.Drawing.Point(110, 23);
            this.Portails_bouton.Name = "Portails_bouton";
            this.Portails_bouton.Size = new System.Drawing.Size(85, 50);
            this.Portails_bouton.TabIndex = 1;
            this.Portails_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.toolTip1.SetToolTip(this.Portails_bouton, "Portail");
            this.Portails_bouton.UseVisualStyleBackColor = false;
            this.Portails_bouton.Click += new System.EventHandler(this.Portails_bouton_Click);
            // 
            // Group_Element2
            // 
            this.Group_Element2.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.Group_Element2.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.Group_Element2.Controls.Add(this.Trou_bouton);
            this.Group_Element2.Controls.Add(this.Generateur_bouton);
            this.Group_Element2.Controls.Add(this.Ressort_bouton);
            this.Group_Element2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Group_Element2.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Group_Element2.Location = new System.Drawing.Point(15, 466);
            this.Group_Element2.Margin = new System.Windows.Forms.Padding(15, 7, 3, 7);
            this.Group_Element2.Name = "Group_Element2";
            this.Group_Element2.Size = new System.Drawing.Size(205, 140);
            this.Group_Element2.TabIndex = 8;
            this.Group_Element2.TabStop = false;
            this.Group_Element2.Text = "Éléments essentiels";
            // 
            // Trou_bouton
            // 
            this.Trou_bouton.BackColor = System.Drawing.Color.White;
            this.Trou_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.Trou;
            this.Trou_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Trou_bouton.Location = new System.Drawing.Point(68, 81);
            this.Trou_bouton.Name = "Trou_bouton";
            this.Trou_bouton.Size = new System.Drawing.Size(85, 50);
            this.Trou_bouton.TabIndex = 5;
            this.Trou_bouton.Tag = "Hole";
            this.Trou_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.toolTip1.SetToolTip(this.Trou_bouton, "Trou");
            this.Trou_bouton.UseVisualStyleBackColor = false;
            this.Trou_bouton.Click += new System.EventHandler(this.Trou_bouton_Click);
            // 
            // Generateur_bouton
            // 
            this.Generateur_bouton.BackColor = System.Drawing.Color.White;
            this.Generateur_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.Generateur;
            this.Generateur_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.Generateur_bouton.Location = new System.Drawing.Point(110, 25);
            this.Generateur_bouton.Name = "Generateur_bouton";
            this.Generateur_bouton.Size = new System.Drawing.Size(85, 50);
            this.Generateur_bouton.TabIndex = 4;
            this.Generateur_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.Generateur_bouton.TextImageRelation = System.Windows.Forms.TextImageRelation.TextAboveImage;
            this.toolTip1.SetToolTip(this.Generateur_bouton, "Générateur de bille");
            this.Generateur_bouton.UseVisualStyleBackColor = false;
            this.Generateur_bouton.Click += new System.EventHandler(this.Generateur_bouton_Click);
            // 
            // Ressort_bouton
            // 
            this.Ressort_bouton.BackColor = System.Drawing.Color.White;
            this.Ressort_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.ressort;
            this.Ressort_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.Ressort_bouton.Location = new System.Drawing.Point(19, 25);
            this.Ressort_bouton.Name = "Ressort_bouton";
            this.Ressort_bouton.Size = new System.Drawing.Size(85, 50);
            this.Ressort_bouton.TabIndex = 3;
            this.Ressort_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.toolTip1.SetToolTip(this.Ressort_bouton, "Ressort");
            this.Ressort_bouton.UseVisualStyleBackColor = false;
            this.Ressort_bouton.Click += new System.EventHandler(this.Ressort_bouton_Click);
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.BackColor = System.Drawing.SystemColors.InactiveBorder;
            this.flowLayoutPanel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.flowLayoutPanel1.Controls.Add(this.Groupe_Outils);
            this.flowLayoutPanel1.Controls.Add(this.OutilGraphique);
            this.flowLayoutPanel1.Controls.Add(this.Groupe_Proprietes);
            this.flowLayoutPanel1.Controls.Add(this.richTextBox1);
            this.flowLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Left;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(0, 59);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(189, 670);
            this.flowLayoutPanel1.TabIndex = 3;
            this.flowLayoutPanel1.SizeChanged += new System.EventHandler(this.flowLayoutPanel1_SizeChanged);
            // 
            // Groupe_Outils
            // 
            this.Groupe_Outils.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.Groupe_Outils.Controls.Add(this.bouton_Suppression);
            this.Groupe_Outils.Controls.Add(this.bouton_Selection);
            this.Groupe_Outils.Controls.Add(this.bouton_Deplacement);
            this.Groupe_Outils.Controls.Add(this.bouton_Duplication);
            this.Groupe_Outils.Controls.Add(this.bouton_Rotation);
            this.Groupe_Outils.Controls.Add(this.bouton_Scaling);
            this.Groupe_Outils.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Groupe_Outils.Location = new System.Drawing.Point(7, 10);
            this.Groupe_Outils.Margin = new System.Windows.Forms.Padding(7, 10, 3, 3);
            this.Groupe_Outils.Name = "Groupe_Outils";
            this.Groupe_Outils.Size = new System.Drawing.Size(169, 280);
            this.Groupe_Outils.TabIndex = 0;
            this.Groupe_Outils.TabStop = false;
            this.Groupe_Outils.Text = "Outils";
            // 
            // bouton_Suppression
            // 
            this.bouton_Suppression.Enabled = false;
            this.bouton_Suppression.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bouton_Suppression.Image = global::InterfaceGraphique.Properties.Resources.delete;
            this.bouton_Suppression.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bouton_Suppression.Location = new System.Drawing.Point(13, 233);
            this.bouton_Suppression.Name = "bouton_Suppression";
            this.bouton_Suppression.Size = new System.Drawing.Size(139, 32);
            this.bouton_Suppression.TabIndex = 5;
            this.bouton_Suppression.Text = "       Supprimer";
            this.bouton_Suppression.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.bouton_Suppression.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.toolTip1.SetToolTip(this.bouton_Suppression, "( Del )");
            this.bouton_Suppression.UseVisualStyleBackColor = true;
            this.bouton_Suppression.Click += new System.EventHandler(this.bouton_Suppression_Click);
            // 
            // bouton_Selection
            // 
            this.bouton_Selection.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bouton_Selection.Image = global::InterfaceGraphique.Properties.Resources.Selection;
            this.bouton_Selection.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bouton_Selection.Location = new System.Drawing.Point(13, 28);
            this.bouton_Selection.Name = "bouton_Selection";
            this.bouton_Selection.Size = new System.Drawing.Size(139, 32);
            this.bouton_Selection.TabIndex = 0;
            this.bouton_Selection.Text = "     Sélection";
            this.bouton_Selection.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.bouton_Selection.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.toolTip1.SetToolTip(this.bouton_Selection, "( S )");
            this.bouton_Selection.UseVisualStyleBackColor = true;
            this.bouton_Selection.Click += new System.EventHandler(this.bouton_Selection_Click);
            // 
            // bouton_Deplacement
            // 
            this.bouton_Deplacement.Enabled = false;
            this.bouton_Deplacement.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bouton_Deplacement.Image = global::InterfaceGraphique.Properties.Resources.move;
            this.bouton_Deplacement.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bouton_Deplacement.Location = new System.Drawing.Point(13, 69);
            this.bouton_Deplacement.Name = "bouton_Deplacement";
            this.bouton_Deplacement.Size = new System.Drawing.Size(139, 32);
            this.bouton_Deplacement.TabIndex = 1;
            this.bouton_Deplacement.Text = "     Déplacement";
            this.bouton_Deplacement.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.bouton_Deplacement.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.toolTip1.SetToolTip(this.bouton_Deplacement, "( D )");
            this.bouton_Deplacement.UseVisualStyleBackColor = true;
            this.bouton_Deplacement.Click += new System.EventHandler(this.bouton_Deplacement_Click);
            // 
            // bouton_Duplication
            // 
            this.bouton_Duplication.Enabled = false;
            this.bouton_Duplication.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bouton_Duplication.Image = global::InterfaceGraphique.Properties.Resources.duplicate;
            this.bouton_Duplication.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bouton_Duplication.Location = new System.Drawing.Point(13, 192);
            this.bouton_Duplication.Name = "bouton_Duplication";
            this.bouton_Duplication.Size = new System.Drawing.Size(139, 32);
            this.bouton_Duplication.TabIndex = 4;
            this.bouton_Duplication.Text = "     Duplication";
            this.bouton_Duplication.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.toolTip1.SetToolTip(this.bouton_Duplication, "( C )");
            this.bouton_Duplication.UseVisualStyleBackColor = true;
            this.bouton_Duplication.Click += new System.EventHandler(this.bouton_Duplication_Click);
            // 
            // bouton_Rotation
            // 
            this.bouton_Rotation.Enabled = false;
            this.bouton_Rotation.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bouton_Rotation.Image = global::InterfaceGraphique.Properties.Resources.rotation;
            this.bouton_Rotation.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bouton_Rotation.Location = new System.Drawing.Point(13, 110);
            this.bouton_Rotation.Name = "bouton_Rotation";
            this.bouton_Rotation.Size = new System.Drawing.Size(139, 32);
            this.bouton_Rotation.TabIndex = 2;
            this.bouton_Rotation.Text = "     Rotation";
            this.bouton_Rotation.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.bouton_Rotation.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.toolTip1.SetToolTip(this.bouton_Rotation, "( R )");
            this.bouton_Rotation.UseVisualStyleBackColor = true;
            this.bouton_Rotation.Click += new System.EventHandler(this.bouton_Rotation_Click);
            // 
            // bouton_Scaling
            // 
            this.bouton_Scaling.Enabled = false;
            this.bouton_Scaling.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bouton_Scaling.Image = global::InterfaceGraphique.Properties.Resources.scale1;
            this.bouton_Scaling.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bouton_Scaling.Location = new System.Drawing.Point(13, 151);
            this.bouton_Scaling.Name = "bouton_Scaling";
            this.bouton_Scaling.Size = new System.Drawing.Size(139, 32);
            this.bouton_Scaling.TabIndex = 3;
            this.bouton_Scaling.Text = "     Mise à échelle";
            this.bouton_Scaling.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.toolTip1.SetToolTip(this.bouton_Scaling, "( E )");
            this.bouton_Scaling.UseVisualStyleBackColor = true;
            this.bouton_Scaling.Click += new System.EventHandler(this.bouton_Scaling_Click);
            // 
            // OutilGraphique
            // 
            this.OutilGraphique.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.OutilGraphique.Controls.Add(this.labelOCourant);
            this.OutilGraphique.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.OutilGraphique.Location = new System.Drawing.Point(7, 308);
            this.OutilGraphique.Margin = new System.Windows.Forms.Padding(7, 15, 3, 3);
            this.OutilGraphique.Name = "OutilGraphique";
            this.OutilGraphique.Size = new System.Drawing.Size(169, 60);
            this.OutilGraphique.TabIndex = 10;
            this.OutilGraphique.TabStop = false;
            this.OutilGraphique.Text = "Outil Courant";
            // 
            // labelOCourant
            // 
            this.labelOCourant.ForeColor = System.Drawing.SystemColors.InfoText;
            this.labelOCourant.Location = new System.Drawing.Point(9, 23);
            this.labelOCourant.Name = "labelOCourant";
            this.labelOCourant.Size = new System.Drawing.Size(135, 30);
            this.labelOCourant.TabIndex = 0;
            this.labelOCourant.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Groupe_Proprietes
            // 
            this.Groupe_Proprietes.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.Groupe_Proprietes.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.Groupe_Proprietes.Controls.Add(this.Annuler_prop_boutn);
            this.Groupe_Proprietes.Controls.Add(this.OK_prop_bouton);
            this.Groupe_Proprietes.Controls.Add(this.Anglebox);
            this.Groupe_Proprietes.Controls.Add(this.Angle_label);
            this.Groupe_Proprietes.Controls.Add(this.FMEbox);
            this.Groupe_Proprietes.Controls.Add(this.FME_label);
            this.Groupe_Proprietes.Controls.Add(this.Ybox);
            this.Groupe_Proprietes.Controls.Add(this.Y_label);
            this.Groupe_Proprietes.Controls.Add(this.Xbox);
            this.Groupe_Proprietes.Controls.Add(this.X_label);
            this.Groupe_Proprietes.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Groupe_Proprietes.Location = new System.Drawing.Point(7, 386);
            this.Groupe_Proprietes.Margin = new System.Windows.Forms.Padding(7, 15, 3, 3);
            this.Groupe_Proprietes.Name = "Groupe_Proprietes";
            this.Groupe_Proprietes.Size = new System.Drawing.Size(169, 193);
            this.Groupe_Proprietes.TabIndex = 1;
            this.Groupe_Proprietes.TabStop = false;
            this.Groupe_Proprietes.Text = "Propriétés";
            this.Groupe_Proprietes.Enter += new System.EventHandler(this.Groupe_Proprietes_Enter);
            // 
            // Annuler_prop_boutn
            // 
            this.Annuler_prop_boutn.Enabled = false;
            this.Annuler_prop_boutn.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Annuler_prop_boutn.Location = new System.Drawing.Point(98, 161);
            this.Annuler_prop_boutn.Name = "Annuler_prop_boutn";
            this.Annuler_prop_boutn.Size = new System.Drawing.Size(65, 23);
            this.Annuler_prop_boutn.TabIndex = 9;
            this.Annuler_prop_boutn.TabStop = false;
            this.Annuler_prop_boutn.Text = "Annuler";
            this.Annuler_prop_boutn.UseVisualStyleBackColor = true;
            this.Annuler_prop_boutn.Click += new System.EventHandler(this.Annuler_prop_boutn_Click);
            // 
            // OK_prop_bouton
            // 
            this.OK_prop_bouton.Enabled = false;
            this.OK_prop_bouton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.OK_prop_bouton.Location = new System.Drawing.Point(27, 161);
            this.OK_prop_bouton.Name = "OK_prop_bouton";
            this.OK_prop_bouton.Size = new System.Drawing.Size(65, 23);
            this.OK_prop_bouton.TabIndex = 8;
            this.OK_prop_bouton.TabStop = false;
            this.OK_prop_bouton.Text = "OK";
            this.OK_prop_bouton.UseVisualStyleBackColor = true;
            this.OK_prop_bouton.Click += new System.EventHandler(this.OK_prop_bouton_Click);
            // 
            // Anglebox
            // 
            this.Anglebox.Enabled = false;
            this.Anglebox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Anglebox.Location = new System.Drawing.Point(112, 95);
            this.Anglebox.Name = "Anglebox";
            this.Anglebox.Size = new System.Drawing.Size(51, 21);
            this.Anglebox.TabIndex = 5;
            this.Anglebox.TabStop = false;
            this.Anglebox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Angle_label
            // 
            this.Angle_label.Enabled = false;
            this.Angle_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Angle_label.Location = new System.Drawing.Point(2, 96);
            this.Angle_label.Name = "Angle_label";
            this.Angle_label.Size = new System.Drawing.Size(57, 20);
            this.Angle_label.TabIndex = 6;
            this.Angle_label.Text = "Angle :";
            this.Angle_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // FMEbox
            // 
            this.FMEbox.Enabled = false;
            this.FMEbox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FMEbox.Location = new System.Drawing.Point(112, 122);
            this.FMEbox.Name = "FMEbox";
            this.FMEbox.Size = new System.Drawing.Size(51, 21);
            this.FMEbox.TabIndex = 7;
            this.FMEbox.TabStop = false;
            this.FMEbox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // FME_label
            // 
            this.FME_label.Enabled = false;
            this.FME_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FME_label.Location = new System.Drawing.Point(-3, 123);
            this.FME_label.Name = "FME_label";
            this.FME_label.Size = new System.Drawing.Size(67, 19);
            this.FME_label.TabIndex = 4;
            this.FME_label.Text = "Scale :";
            this.FME_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Ybox
            // 
            this.Ybox.Enabled = false;
            this.Ybox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Ybox.Location = new System.Drawing.Point(112, 57);
            this.Ybox.Name = "Ybox";
            this.Ybox.Size = new System.Drawing.Size(51, 21);
            this.Ybox.TabIndex = 3;
            this.Ybox.TabStop = false;
            this.Ybox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Y_label
            // 
            this.Y_label.Enabled = false;
            this.Y_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Y_label.Location = new System.Drawing.Point(-1, 32);
            this.Y_label.Name = "Y_label";
            this.Y_label.Size = new System.Drawing.Size(106, 20);
            this.Y_label.TabIndex = 2;
            this.Y_label.Text = "Position en Y :";
            this.Y_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Xbox
            // 
            this.Xbox.Enabled = false;
            this.Xbox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Xbox.Location = new System.Drawing.Point(112, 32);
            this.Xbox.Name = "Xbox";
            this.Xbox.Size = new System.Drawing.Size(51, 21);
            this.Xbox.TabIndex = 1;
            this.Xbox.TabStop = false;
            this.Xbox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // X_label
            // 
            this.X_label.Enabled = false;
            this.X_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.X_label.Location = new System.Drawing.Point(-2, 57);
            this.X_label.Name = "X_label";
            this.X_label.Size = new System.Drawing.Size(106, 20);
            this.X_label.TabIndex = 0;
            this.X_label.Text = "Position en X :";
            this.X_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // richTextBox1
            // 
            this.richTextBox1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.richTextBox1.Location = new System.Drawing.Point(3, 585);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.Size = new System.Drawing.Size(151, 10);
            this.richTextBox1.TabIndex = 11;
            this.richTextBox1.TabStop = false;
            this.richTextBox1.Text = resources.GetString("richTextBox1.Text");
            this.richTextBox1.Visible = false;
            // 
            // toolStrip1
            // 
            this.toolStrip1.AutoSize = false;
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(40, 40);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuP_ToolStrip,
            this.toolStripSeparator2,
            this.Nouveau_ToolStrip,
            this.Ouvrir_ToolStrip,
            Enregistrer_ToolStrip,
            this.EnregistrerSous_ToolStrip,
            this.toolStripSeparator1,
            this.Annuler_ToolStrip,
            this.Retablir_ToolStrip,
            this.Proprietes_ToolStrip,
            this.ModeTest_ToolStrip,
            this.toolStripSeparator3,
            this.ZoomIn_ToolStrip,
            this.ZoomOut_ToolStrip,
            this.ZoomElastique_ToolStrip});
            this.toolStrip1.Location = new System.Drawing.Point(0, 24);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(954, 35);
            this.toolStrip1.TabIndex = 6;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // MenuP_ToolStrip
            // 
            this.MenuP_ToolStrip.AutoSize = false;
            this.MenuP_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.MenuP_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.Return_home;
            this.MenuP_ToolStrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.MenuP_ToolStrip.Name = "MenuP_ToolStrip";
            this.MenuP_ToolStrip.Size = new System.Drawing.Size(35, 30);
            this.MenuP_ToolStrip.Text = "toolStripButton2";
            this.MenuP_ToolStrip.ToolTipText = "Retour au menu principal( CTRL + Q)";
            this.MenuP_ToolStrip.Click += new System.EventHandler(this.MenuP_ToolStrip_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Margin = new System.Windows.Forms.Padding(10, 0, 10, 0);
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 35);
            // 
            // Nouveau_ToolStrip
            // 
            this.Nouveau_ToolStrip.AutoSize = false;
            this.Nouveau_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Nouveau_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.NouveauFichier;
            this.Nouveau_ToolStrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Nouveau_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Nouveau_ToolStrip.Name = "Nouveau_ToolStrip";
            this.Nouveau_ToolStrip.Size = new System.Drawing.Size(35, 30);
            this.Nouveau_ToolStrip.Text = "Nouveau";
            this.Nouveau_ToolStrip.ToolTipText = "Nouveau (CTRL + N)";
            this.Nouveau_ToolStrip.Click += new System.EventHandler(this.Nouveau_Click);
            // 
            // Ouvrir_ToolStrip
            // 
            this.Ouvrir_ToolStrip.AutoSize = false;
            this.Ouvrir_ToolStrip.BackColor = System.Drawing.Color.Transparent;
            this.Ouvrir_ToolStrip.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Ouvrir_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Ouvrir_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.open1;
            this.Ouvrir_ToolStrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Ouvrir_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Ouvrir_ToolStrip.Name = "Ouvrir_ToolStrip";
            this.Ouvrir_ToolStrip.Size = new System.Drawing.Size(35, 30);
            this.Ouvrir_ToolStrip.Text = "Ouvrir";
            this.Ouvrir_ToolStrip.ToolTipText = "Ouvrir (CTRL + O)";
            this.Ouvrir_ToolStrip.Click += new System.EventHandler(this.Ouvrir_Click);
            // 
            // EnregistrerSous_ToolStrip
            // 
            this.EnregistrerSous_ToolStrip.AutoSize = false;
            this.EnregistrerSous_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.EnregistrerSous_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.enregistrersous;
            this.EnregistrerSous_ToolStrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.EnregistrerSous_ToolStrip.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.EnregistrerSous_ToolStrip.Name = "EnregistrerSous_ToolStrip";
            this.EnregistrerSous_ToolStrip.Size = new System.Drawing.Size(35, 30);
            this.EnregistrerSous_ToolStrip.Text = "toolStripButton4";
            this.EnregistrerSous_ToolStrip.ToolTipText = "Enregistrer sous (CTRL + SHIFT + S)";
            this.EnregistrerSous_ToolStrip.Click += new System.EventHandler(this.EnregistrerSous_ToolStrip_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Margin = new System.Windows.Forms.Padding(10, 0, 10, 0);
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 35);
            // 
            // Annuler_ToolStrip
            // 
            this.Annuler_ToolStrip.AutoSize = false;
            this.Annuler_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Annuler_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.undo;
            this.Annuler_ToolStrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Annuler_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Annuler_ToolStrip.Name = "Annuler_ToolStrip";
            this.Annuler_ToolStrip.Size = new System.Drawing.Size(35, 30);
            this.Annuler_ToolStrip.Text = "Annuler ( CTRL + Z )";
            this.Annuler_ToolStrip.Click += new System.EventHandler(this.Annuler_ToolStrip_Click);
            // 
            // Retablir_ToolStrip
            // 
            this.Retablir_ToolStrip.AutoSize = false;
            this.Retablir_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Retablir_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.redo;
            this.Retablir_ToolStrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Retablir_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Retablir_ToolStrip.Name = "Retablir_ToolStrip";
            this.Retablir_ToolStrip.Size = new System.Drawing.Size(35, 30);
            this.Retablir_ToolStrip.Text = "Rétablir ( CTRL + Y )";
            this.Retablir_ToolStrip.Click += new System.EventHandler(this.Retablir_ToolStrip_Click);
            // 
            // Proprietes_ToolStrip
            // 
            this.Proprietes_ToolStrip.AutoSize = false;
            this.Proprietes_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Proprietes_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.settings;
            this.Proprietes_ToolStrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Proprietes_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Proprietes_ToolStrip.Name = "Proprietes_ToolStrip";
            this.Proprietes_ToolStrip.Size = new System.Drawing.Size(35, 30);
            this.Proprietes_ToolStrip.Text = "Propriétés de zone de jeu";
            this.Proprietes_ToolStrip.Click += new System.EventHandler(this.Proprietes_ToolStrip_Click);
            // 
            // ModeTest_ToolStrip
            // 
            this.ModeTest_ToolStrip.AutoSize = false;
            this.ModeTest_ToolStrip.Font = new System.Drawing.Font("Segoe UI", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ModeTest_ToolStrip.Image = ((System.Drawing.Image)(resources.GetObject("ModeTest_ToolStrip.Image")));
            this.ModeTest_ToolStrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ModeTest_ToolStrip.Name = "ModeTest_ToolStrip";
            this.ModeTest_ToolStrip.Size = new System.Drawing.Size(80, 30);
            this.ModeTest_ToolStrip.Text = "Tester";
            this.ModeTest_ToolStrip.ToolTipText = "Mode Test (T)";
            this.ModeTest_ToolStrip.Click += new System.EventHandler(this.ModeTest_ToolStrip_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Margin = new System.Windows.Forms.Padding(10, 0, 10, 0);
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 35);
            // 
            // ZoomIn_ToolStrip
            // 
            this.ZoomIn_ToolStrip.AutoSize = false;
            this.ZoomIn_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.ZoomIn_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.zoomIN;
            this.ZoomIn_ToolStrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ZoomIn_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.ZoomIn_ToolStrip.Name = "ZoomIn_ToolStrip";
            this.ZoomIn_ToolStrip.Size = new System.Drawing.Size(35, 30);
            this.ZoomIn_ToolStrip.Text = "toolStripButton5";
            this.ZoomIn_ToolStrip.ToolTipText = "Zoom avant( + )";
            this.ZoomIn_ToolStrip.Click += new System.EventHandler(this.ZoomIn_ToolStrip_Click);
            // 
            // ZoomOut_ToolStrip
            // 
            this.ZoomOut_ToolStrip.AutoSize = false;
            this.ZoomOut_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.ZoomOut_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.ZoomOut;
            this.ZoomOut_ToolStrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ZoomOut_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.ZoomOut_ToolStrip.Name = "ZoomOut_ToolStrip";
            this.ZoomOut_ToolStrip.Size = new System.Drawing.Size(35, 30);
            this.ZoomOut_ToolStrip.Text = "toolStripButton6";
            this.ZoomOut_ToolStrip.ToolTipText = "Zoom arrière ( - )";
            this.ZoomOut_ToolStrip.Click += new System.EventHandler(this.ZoomOut_ToolStrip_Click);
            // 
            // ZoomElastique_ToolStrip
            // 
            this.ZoomElastique_ToolStrip.AutoSize = false;
            this.ZoomElastique_ToolStrip.BackColor = System.Drawing.Color.Transparent;
            this.ZoomElastique_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.ZoomElastique_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.zoomElastique2;
            this.ZoomElastique_ToolStrip.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ZoomElastique_ToolStrip.Margin = new System.Windows.Forms.Padding(0, 4, 0, 4);
            this.ZoomElastique_ToolStrip.Name = "ZoomElastique_ToolStrip";
            this.ZoomElastique_ToolStrip.Size = new System.Drawing.Size(35, 30);
            this.ZoomElastique_ToolStrip.Text = "toolStripButton7";
            this.ZoomElastique_ToolStrip.ToolTipText = "Zoom Elastique";
            this.ZoomElastique_ToolStrip.Click += new System.EventHandler(this.ZoomElastique_ToolStrip_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.AutoSize = false;
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.Edition_MenuItem,
            this.Outils_MenuItem,
            this.Vues_MenuItem,
            this.Information_MenuItem});
            this.menuStrip1.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(954, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fichierToolStripMenuItem
            // 
            this.fichierToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Nouveau_MenuItem,
            this.Ouvrir_MenuItem,
            this.Enregistrer_MenuItem,
            this.EnregistrerS_MenuItem,
            this.Proprietes_MenuItem,
            this.ModeTest_MenuItem,
            this.MenuP_MenuItem});
            this.fichierToolStripMenuItem.Name = "fichierToolStripMenuItem";
            this.fichierToolStripMenuItem.Size = new System.Drawing.Size(54, 20);
            this.fichierToolStripMenuItem.Text = "Fichier";
            // 
            // Nouveau_MenuItem
            // 
            this.Nouveau_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.NouveauFichier;
            this.Nouveau_MenuItem.Name = "Nouveau_MenuItem";
            this.Nouveau_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.Nouveau_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.Nouveau_MenuItem.Text = "Nouveau";
            this.Nouveau_MenuItem.Click += new System.EventHandler(this.Nouveau_MenuItem_Click);
            // 
            // Ouvrir_MenuItem
            // 
            this.Ouvrir_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.open;
            this.Ouvrir_MenuItem.Name = "Ouvrir_MenuItem";
            this.Ouvrir_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.Ouvrir_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.Ouvrir_MenuItem.Text = "Ouvrir";
            this.Ouvrir_MenuItem.Click += new System.EventHandler(this.Ouvrir_MenuItem_Click);
            // 
            // Enregistrer_MenuItem
            // 
            this.Enregistrer_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.save;
            this.Enregistrer_MenuItem.Name = "Enregistrer_MenuItem";
            this.Enregistrer_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.Enregistrer_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.Enregistrer_MenuItem.Text = "Enregistrer";
            this.Enregistrer_MenuItem.Click += new System.EventHandler(this.Enregistrer_MenuItem_Click);
            // 
            // EnregistrerS_MenuItem
            // 
            this.EnregistrerS_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.enregistrersous;
            this.EnregistrerS_MenuItem.Name = "EnregistrerS_MenuItem";
            this.EnregistrerS_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.S)));
            this.EnregistrerS_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.EnregistrerS_MenuItem.Text = "Enregistrer Sous";
            this.EnregistrerS_MenuItem.Click += new System.EventHandler(this.EnregistrerS_MenuItem_Click);
            // 
            // Proprietes_MenuItem
            // 
            this.Proprietes_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.settings;
            this.Proprietes_MenuItem.Name = "Proprietes_MenuItem";
            this.Proprietes_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.Proprietes_MenuItem.Text = "Propriétés";
            this.Proprietes_MenuItem.Click += new System.EventHandler(this.Proprietes_MenuItem_Click);
            // 
            // ModeTest_MenuItem
            // 
            this.ModeTest_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.Tester;
            this.ModeTest_MenuItem.Name = "ModeTest_MenuItem";
            this.ModeTest_MenuItem.ShortcutKeyDisplayString = "t";
            this.ModeTest_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.ModeTest_MenuItem.Text = "Mode Test";
            this.ModeTest_MenuItem.Click += new System.EventHandler(this.ModeTest_MenuItem_Click);
            // 
            // MenuP_MenuItem
            // 
            this.MenuP_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.Return_home;
            this.MenuP_MenuItem.Name = "MenuP_MenuItem";
            this.MenuP_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Q)));
            this.MenuP_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.MenuP_MenuItem.Text = "Menu Principal";
            this.MenuP_MenuItem.Click += new System.EventHandler(this.MenuP_MenuItem_Click);
            // 
            // Edition_MenuItem
            // 
            this.Edition_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Supprimer_MenuItem,
            this.Annuler_MenuItem,
            this.Retablir_MenuItem});
            this.Edition_MenuItem.Name = "Edition_MenuItem";
            this.Edition_MenuItem.Size = new System.Drawing.Size(56, 20);
            this.Edition_MenuItem.Text = "Édition";
            // 
            // Supprimer_MenuItem
            // 
            this.Supprimer_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.delete;
            this.Supprimer_MenuItem.Name = "Supprimer_MenuItem";
            this.Supprimer_MenuItem.ShortcutKeys = System.Windows.Forms.Keys.Delete;
            this.Supprimer_MenuItem.Size = new System.Drawing.Size(157, 22);
            this.Supprimer_MenuItem.Text = "Supprimer";
            this.Supprimer_MenuItem.Click += new System.EventHandler(this.Supprimer_MenuItem_Click_1);
            // 
            // Annuler_MenuItem
            // 
            this.Annuler_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.undo;
            this.Annuler_MenuItem.Name = "Annuler_MenuItem";
            this.Annuler_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z)));
            this.Annuler_MenuItem.Size = new System.Drawing.Size(157, 22);
            this.Annuler_MenuItem.Text = "Annuler";
            this.Annuler_MenuItem.Click += new System.EventHandler(this.Annuler_MenuItem_Click);
            // 
            // Retablir_MenuItem
            // 
            this.Retablir_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.redo;
            this.Retablir_MenuItem.Name = "Retablir_MenuItem";
            this.Retablir_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Y)));
            this.Retablir_MenuItem.Size = new System.Drawing.Size(157, 22);
            this.Retablir_MenuItem.Text = "Rétablir";
            this.Retablir_MenuItem.Click += new System.EventHandler(this.Retablir_MenuItem_Click);
            // 
            // Outils_MenuItem
            // 
            this.Outils_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Selection_MenuItem,
            this.Deplacement_MenuItem,
            this.Rotation_MenuItem,
            this.MiseE_MenuItem,
            this.Duplication_MenuItem,
            this.Zoom_MenuItem,
            this.Creation_MenuItem});
            this.Outils_MenuItem.Name = "Outils_MenuItem";
            this.Outils_MenuItem.Size = new System.Drawing.Size(50, 20);
            this.Outils_MenuItem.Text = "Outils";
            // 
            // Selection_MenuItem
            // 
            this.Selection_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.Selection;
            this.Selection_MenuItem.Name = "Selection_MenuItem";
            this.Selection_MenuItem.ShortcutKeyDisplayString = "s";
            this.Selection_MenuItem.Size = new System.Drawing.Size(164, 22);
            this.Selection_MenuItem.Text = "Sélection";
            this.Selection_MenuItem.Click += new System.EventHandler(this.Selection_MenuItem_Click);
            // 
            // Deplacement_MenuItem
            // 
            this.Deplacement_MenuItem.Enabled = false;
            this.Deplacement_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.move;
            this.Deplacement_MenuItem.Name = "Deplacement_MenuItem";
            this.Deplacement_MenuItem.ShortcutKeyDisplayString = "d";
            this.Deplacement_MenuItem.Size = new System.Drawing.Size(164, 22);
            this.Deplacement_MenuItem.Text = "Déplacement";
            this.Deplacement_MenuItem.Click += new System.EventHandler(this.Deplacement_MenuItem_Click);
            // 
            // Rotation_MenuItem
            // 
            this.Rotation_MenuItem.Enabled = false;
            this.Rotation_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.rotation;
            this.Rotation_MenuItem.Name = "Rotation_MenuItem";
            this.Rotation_MenuItem.ShortcutKeyDisplayString = "r";
            this.Rotation_MenuItem.Size = new System.Drawing.Size(164, 22);
            this.Rotation_MenuItem.Text = "Rotation";
            this.Rotation_MenuItem.Click += new System.EventHandler(this.Rotation_MenuItem_Click);
            // 
            // MiseE_MenuItem
            // 
            this.MiseE_MenuItem.Enabled = false;
            this.MiseE_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.scale1;
            this.MiseE_MenuItem.Name = "MiseE_MenuItem";
            this.MiseE_MenuItem.ShortcutKeyDisplayString = "e";
            this.MiseE_MenuItem.Size = new System.Drawing.Size(164, 22);
            this.MiseE_MenuItem.Text = "Mise à échelle";
            this.MiseE_MenuItem.Click += new System.EventHandler(this.MiseE_MenuItem_Click);
            // 
            // Duplication_MenuItem
            // 
            this.Duplication_MenuItem.Enabled = false;
            this.Duplication_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.duplicate;
            this.Duplication_MenuItem.Name = "Duplication_MenuItem";
            this.Duplication_MenuItem.ShortcutKeyDisplayString = "c";
            this.Duplication_MenuItem.Size = new System.Drawing.Size(164, 22);
            this.Duplication_MenuItem.Text = "Duplication";
            this.Duplication_MenuItem.Click += new System.EventHandler(this.Duplication_MenuItem_Click);
            // 
            // Zoom_MenuItem
            // 
            this.Zoom_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.zoomElastique2;
            this.Zoom_MenuItem.Name = "Zoom_MenuItem";
            this.Zoom_MenuItem.ShortcutKeyDisplayString = "z";
            this.Zoom_MenuItem.Size = new System.Drawing.Size(164, 22);
            this.Zoom_MenuItem.Text = "Zoom";
            this.Zoom_MenuItem.Click += new System.EventHandler(this.Zoom_MenuItem_Click);
            // 
            // Creation_MenuItem
            // 
            this.Creation_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.PG_J1_MenuItem,
            this.PD_J1_MenuItem,
            this.PG_J2_MenuItem,
            this.PD_J2_MenuItem,
            this.BTG_MenuItem,
            this.BTD_MenuItem,
            this.BC_MenuItem,
            this.Cible_MenuItem,
            this.Portails_MenuItem,
            this.Mur_MenuItem,
            this.Ressort_MenuItem,
            this.GB_MenuItem,
            this.Trou_MenuItem,
            this.gateToolStripMenuItem});
            this.Creation_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.add;
            this.Creation_MenuItem.Name = "Creation_MenuItem";
            this.Creation_MenuItem.Size = new System.Drawing.Size(164, 22);
            this.Creation_MenuItem.Text = "Création d\'objets";
            this.Creation_MenuItem.Click += new System.EventHandler(this.Creation_MenuItem_Click);
            // 
            // PG_J1_MenuItem
            // 
            this.PG_J1_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.PGJ1;
            this.PG_J1_MenuItem.Name = "PG_J1_MenuItem";
            this.PG_J1_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.PG_J1_MenuItem.Text = "Palette gauche J1";
            this.PG_J1_MenuItem.Click += new System.EventHandler(this.PG_J1_MenuItem_Click);
            // 
            // PD_J1_MenuItem
            // 
            this.PD_J1_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.PDJ1;
            this.PD_J1_MenuItem.Name = "PD_J1_MenuItem";
            this.PD_J1_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.PD_J1_MenuItem.Text = "Palette droite J1";
            this.PD_J1_MenuItem.Click += new System.EventHandler(this.PD_J1_MenuItem_Click);
            // 
            // PG_J2_MenuItem
            // 
            this.PG_J2_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.PGJ2;
            this.PG_J2_MenuItem.Name = "PG_J2_MenuItem";
            this.PG_J2_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.PG_J2_MenuItem.Text = "Palette gauche J2";
            this.PG_J2_MenuItem.Click += new System.EventHandler(this.PG_J2_MenuItem_Click);
            // 
            // PD_J2_MenuItem
            // 
            this.PD_J2_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.PDJ2;
            this.PD_J2_MenuItem.Name = "PD_J2_MenuItem";
            this.PD_J2_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.PD_J2_MenuItem.Text = "Palette droite J2";
            this.PD_J2_MenuItem.Click += new System.EventHandler(this.PD_J2_MenuItem_Click);
            // 
            // BTG_MenuItem
            // 
            this.BTG_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.ButoirTriangG;
            this.BTG_MenuItem.Name = "BTG_MenuItem";
            this.BTG_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.BTG_MenuItem.Text = "Butoir triangulaire gauche";
            this.BTG_MenuItem.Click += new System.EventHandler(this.BTG_MenuItem_Click);
            // 
            // BTD_MenuItem
            // 
            this.BTD_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.ButoirTriangD;
            this.BTD_MenuItem.Name = "BTD_MenuItem";
            this.BTD_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.BTD_MenuItem.Text = "Butoire triangulaire droit";
            this.BTD_MenuItem.Click += new System.EventHandler(this.BTD_MenuItem_Click);
            // 
            // BC_MenuItem
            // 
            this.BC_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.cible1;
            this.BC_MenuItem.Name = "BC_MenuItem";
            this.BC_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.BC_MenuItem.Text = "Butoir circulaire";
            this.BC_MenuItem.Click += new System.EventHandler(this.BC_MenuItem_Click);
            // 
            // Cible_MenuItem
            // 
            this.Cible_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.cible;
            this.Cible_MenuItem.Name = "Cible_MenuItem";
            this.Cible_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Cible_MenuItem.Text = "Cible";
            this.Cible_MenuItem.Click += new System.EventHandler(this.Cible_MenuItem_Click);
            // 
            // Portails_MenuItem
            // 
            this.Portails_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.portail;
            this.Portails_MenuItem.Name = "Portails_MenuItem";
            this.Portails_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Portails_MenuItem.Text = "Portails";
            this.Portails_MenuItem.Click += new System.EventHandler(this.Portails_MenuItem_Click);
            // 
            // Mur_MenuItem
            // 
            this.Mur_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.mur;
            this.Mur_MenuItem.Name = "Mur_MenuItem";
            this.Mur_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Mur_MenuItem.Text = "Mur";
            this.Mur_MenuItem.Click += new System.EventHandler(this.Mur_MenuItem_Click);
            // 
            // Ressort_MenuItem
            // 
            this.Ressort_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.ressort;
            this.Ressort_MenuItem.Name = "Ressort_MenuItem";
            this.Ressort_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Ressort_MenuItem.Text = "Ressort";
            this.Ressort_MenuItem.Click += new System.EventHandler(this.Ressort_MenuItem_Click);
            // 
            // GB_MenuItem
            // 
            this.GB_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.Generateur;
            this.GB_MenuItem.Name = "GB_MenuItem";
            this.GB_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.GB_MenuItem.Text = "Générateur de billes";
            this.GB_MenuItem.Click += new System.EventHandler(this.GB_MenuItem_Click);
            // 
            // Trou_MenuItem
            // 
            this.Trou_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.Trou;
            this.Trou_MenuItem.Name = "Trou_MenuItem";
            this.Trou_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Trou_MenuItem.Text = "Trou";
            this.Trou_MenuItem.Click += new System.EventHandler(this.Trou_MenuItem_Click);
            // 
            // gateToolStripMenuItem
            // 
            this.gateToolStripMenuItem.Image = global::InterfaceGraphique.Properties.Resources.gate;
            this.gateToolStripMenuItem.Name = "gateToolStripMenuItem";
            this.gateToolStripMenuItem.Size = new System.Drawing.Size(211, 22);
            this.gateToolStripMenuItem.Text = "Gate";
            this.gateToolStripMenuItem.Click += new System.EventHandler(this.Gate_Button_Click);
            // 
            // Vues_MenuItem
            // 
            this.Vues_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Orthographique_MenuItem,
            this.Orbite_MenuItem});
            this.Vues_MenuItem.Name = "Vues_MenuItem";
            this.Vues_MenuItem.Size = new System.Drawing.Size(44, 20);
            this.Vues_MenuItem.Text = "Vues";
            // 
            // Orthographique_MenuItem
            // 
            this.Orthographique_MenuItem.Name = "Orthographique_MenuItem";
            this.Orthographique_MenuItem.ShortcutKeyDisplayString = "1";
            this.Orthographique_MenuItem.Size = new System.Drawing.Size(172, 22);
            this.Orthographique_MenuItem.Text = "Orthographique";
            this.Orthographique_MenuItem.Click += new System.EventHandler(this.Orthographique_MenuItem_Click);
            // 
            // Orbite_MenuItem
            // 
            this.Orbite_MenuItem.Name = "Orbite_MenuItem";
            this.Orbite_MenuItem.ShortcutKeyDisplayString = "2";
            this.Orbite_MenuItem.Size = new System.Drawing.Size(172, 22);
            this.Orbite_MenuItem.Text = "Orbite";
            this.Orbite_MenuItem.Click += new System.EventHandler(this.Orbite_MenuItem_Click);
            // 
            // Information_MenuItem
            // 
            this.Information_MenuItem.CheckOnClick = true;
            this.Information_MenuItem.Name = "Information_MenuItem";
            this.Information_MenuItem.ShortcutKeys = System.Windows.Forms.Keys.F1;
            this.Information_MenuItem.Size = new System.Drawing.Size(87, 20);
            this.Information_MenuItem.Text = "Informations";
            this.Information_MenuItem.ToolTipText = "F1";
            this.Information_MenuItem.Click += new System.EventHandler(this.Information_MenuItem_Click);
            // 
            // menuStrip3
            // 
            this.menuStrip3.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem1,
            this.caméraToolStripMenuItem1});
            this.menuStrip3.Location = new System.Drawing.Point(0, 0);
            this.menuStrip3.Name = "menuStrip3";
            this.menuStrip3.Size = new System.Drawing.Size(954, 24);
            this.menuStrip3.TabIndex = 5;
            this.menuStrip3.Text = "menuStrip3";
            this.menuStrip3.Visible = false;
            // 
            // fichierToolStripMenuItem1
            // 
            this.fichierToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.testRetourMenuPrincipal,
            this.testRetourModeEdition});
            this.fichierToolStripMenuItem1.Name = "fichierToolStripMenuItem1";
            this.fichierToolStripMenuItem1.Size = new System.Drawing.Size(54, 20);
            this.fichierToolStripMenuItem1.Text = "Fichier";
            // 
            // testRetourMenuPrincipal
            // 
            this.testRetourMenuPrincipal.Name = "testRetourMenuPrincipal";
            this.testRetourMenuPrincipal.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Q)));
            this.testRetourMenuPrincipal.Size = new System.Drawing.Size(197, 22);
            this.testRetourMenuPrincipal.Text = "Menu principal";
            this.testRetourMenuPrincipal.Click += new System.EventHandler(this.testRetourMenuPrincipal_Click);
            // 
            // testRetourModeEdition
            // 
            this.testRetourModeEdition.Name = "testRetourModeEdition";
            this.testRetourModeEdition.ShortcutKeyDisplayString = "t";
            this.testRetourModeEdition.Size = new System.Drawing.Size(197, 22);
            this.testRetourModeEdition.Text = "Mode édition";
            this.testRetourModeEdition.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
            // 
            // caméraToolStripMenuItem1
            // 
            this.caméraToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.orthographiqueToolStripMenuItem,
            this.orbiteToolStripMenuItem1});
            this.caméraToolStripMenuItem1.Name = "caméraToolStripMenuItem1";
            this.caméraToolStripMenuItem1.Size = new System.Drawing.Size(44, 20);
            this.caméraToolStripMenuItem1.Text = "Vues";
            // 
            // orthographiqueToolStripMenuItem
            // 
            this.orthographiqueToolStripMenuItem.Name = "orthographiqueToolStripMenuItem";
            this.orthographiqueToolStripMenuItem.ShortcutKeyDisplayString = "1";
            this.orthographiqueToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.orthographiqueToolStripMenuItem.Text = "Orthographique";
            // 
            // orbiteToolStripMenuItem1
            // 
            this.orbiteToolStripMenuItem1.Name = "orbiteToolStripMenuItem1";
            this.orbiteToolStripMenuItem1.ShortcutKeyDisplayString = "2";
            this.orbiteToolStripMenuItem1.Size = new System.Drawing.Size(172, 22);
            this.orbiteToolStripMenuItem1.Text = "Orbite";
            // 
            // printPreviewDialog1
            // 
            this.printPreviewDialog1.AutoScrollMargin = new System.Drawing.Size(0, 0);
            this.printPreviewDialog1.AutoScrollMinSize = new System.Drawing.Size(0, 0);
            this.printPreviewDialog1.ClientSize = new System.Drawing.Size(400, 300);
            this.printPreviewDialog1.Enabled = true;
            this.printPreviewDialog1.Icon = ((System.Drawing.Icon)(resources.GetObject("printPreviewDialog1.Icon")));
            this.printPreviewDialog1.Name = "printPreviewDialog1";
            this.printPreviewDialog1.Visible = false;
            // 
            // Editeur
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(956, 731);
            this.Controls.Add(this.panel1);
            this.KeyPreview = true;
            this.MainMenuStrip = this.menuStrip1;
            this.MinimumSize = new System.Drawing.Size(972, 678);
            this.Name = "Editeur";
            this.Text = "Mode Edition";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Editeur_FormClosing);
            this.Load += new System.EventHandler(this.Editeur_Load);
            this.Shown += new System.EventHandler(this.Editeur_Shown);
            this.SizeChanged += new System.EventHandler(this.Fenetre_Redimension);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel_GL.ResumeLayout(false);
            this.Creation_Panel.ResumeLayout(false);
            this.Groupe_Palettes.ResumeLayout(false);
            this.Group_Butoir.ResumeLayout(false);
            this.Group_Elements.ResumeLayout(false);
            this.Group_Element2.ResumeLayout(false);
            this.flowLayoutPanel1.ResumeLayout(false);
            this.Groupe_Outils.ResumeLayout(false);
            this.OutilGraphique.ResumeLayout(false);
            this.Groupe_Proprietes.ResumeLayout(false);
            this.Groupe_Proprietes.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.menuStrip3.ResumeLayout(false);
            this.menuStrip3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Nouveau_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem MenuP_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Outils_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Enregistrer_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem EnregistrerS_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Vues_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Ouvrir_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Proprietes_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem ModeTest_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Information_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Orthographique_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Orbite_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Selection_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Deplacement_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Rotation_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem MiseE_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Duplication_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Creation_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Zoom_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem PG_J1_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem PD_J1_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem PG_J2_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem PD_J2_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem BTG_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem BTD_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem BC_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Cible_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Portails_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Mur_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Ressort_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem GB_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Trou_MenuItem;
        private System.Windows.Forms.FlowLayoutPanel Creation_Panel;
        private System.Windows.Forms.GroupBox Groupe_Palettes;
        private System.Windows.Forms.PrintPreviewDialog printPreviewDialog1;
        private System.Windows.Forms.Button PDJ1_bouton;
        private System.Windows.Forms.Button PGJ1_bouton;
        private System.Windows.Forms.Button PDJ2_bouton;
        private System.Windows.Forms.Button PGJ2_bouton;
        private System.Windows.Forms.GroupBox Group_Butoir;
        private System.Windows.Forms.Button butoirD_bouton;
        private System.Windows.Forms.Button butoirG_bouton;
        private System.Windows.Forms.Button butoirCirc_bouton;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.Panel panel_GL;
        private System.Windows.Forms.GroupBox Groupe_Outils;
        private System.Windows.Forms.GroupBox Groupe_Proprietes;
        private System.Windows.Forms.Button bouton_Selection;
        private System.Windows.Forms.Button bouton_Creation;
        private System.Windows.Forms.Button bouton_Duplication;
        private System.Windows.Forms.Button bouton_Scaling;
        private System.Windows.Forms.Button bouton_Rotation;
        private System.Windows.Forms.Button bouton_Deplacement;
        private System.Windows.Forms.TextBox Anglebox;
        private System.Windows.Forms.Label Angle_label;
        private System.Windows.Forms.TextBox FMEbox;
        private System.Windows.Forms.Label FME_label;
        private System.Windows.Forms.TextBox Ybox;
        private System.Windows.Forms.Label Y_label;
        private System.Windows.Forms.TextBox Xbox;
        private System.Windows.Forms.Label X_label;
        private System.Windows.Forms.Button Annuler_prop_boutn;
        private System.Windows.Forms.Button OK_prop_bouton;
        private System.Windows.Forms.GroupBox Group_Elements;
        private System.Windows.Forms.GroupBox Group_Element2;
        private System.Windows.Forms.Button Cible_bouton;
        private System.Windows.Forms.Button Mur_bouton;
        private System.Windows.Forms.Button Portails_bouton;
        private System.Windows.Forms.Button Trou_bouton;
        private System.Windows.Forms.Button Generateur_bouton;
        private System.Windows.Forms.Button Ressort_bouton;
        private System.Windows.Forms.GroupBox OutilGraphique;
        private System.Windows.Forms.Label labelOCourant;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.MenuStrip menuStrip3;
        private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem testRetourMenuPrincipal;
        private System.Windows.Forms.ToolStripMenuItem testRetourModeEdition;
        private System.Windows.Forms.ToolStripMenuItem caméraToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem orthographiqueToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem orbiteToolStripMenuItem1;
        private System.Windows.Forms.Button Gate;
        private System.Windows.Forms.ToolStripMenuItem gateToolStripMenuItem;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton Ouvrir_ToolStrip;
        private System.Windows.Forms.ToolStripButton Nouveau_ToolStrip;
        private System.Windows.Forms.ToolStripButton ModeTest_ToolStrip;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton MenuP_ToolStrip;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton Proprietes_ToolStrip;
        private System.Windows.Forms.ToolStripButton EnregistrerSous_ToolStrip;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripButton ZoomIn_ToolStrip;
        private System.Windows.Forms.ToolStripButton ZoomOut_ToolStrip;
        private System.Windows.Forms.ToolTip toolTipPaneauCreation;
        private System.Windows.Forms.Button bouton_Suppression;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.ToolStripButton ZoomElastique_ToolStrip;
        private System.Windows.Forms.ToolStripButton Annuler_ToolStrip;
        private System.Windows.Forms.ToolStripButton Retablir_ToolStrip;
        private System.Windows.Forms.ToolStripMenuItem Edition_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Supprimer_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Annuler_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Retablir_MenuItem;
    }
}

