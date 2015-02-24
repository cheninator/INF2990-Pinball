//////////////////////////////////////////////////////////////////////////////
/// @file Exemple.Designer.cs
/// @author Ballers
/// @date 2015-01-13
/// @version 1.0 
///
/// @ingroup InterfaceGraphique
//////////////////////////////////////////////////////////////////////////////

namespace InterfaceGraphique
{
    partial class Exemple
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Exemple));
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel_GL = new System.Windows.Forms.Panel();
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
            this.Group_Elements = new System.Windows.Forms.GroupBox();
            this.Mur_bouton = new System.Windows.Forms.Button();
            this.Portails_bouton = new System.Windows.Forms.Button();
            this.Cible_bouton = new System.Windows.Forms.Button();
            this.Group_Element2 = new System.Windows.Forms.GroupBox();
            this.Trou_bouton = new System.Windows.Forms.Button();
            this.Generateur_bouton = new System.Windows.Forms.Button();
            this.Ressort_bouton = new System.Windows.Forms.Button();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.Groupe_Outils = new System.Windows.Forms.GroupBox();
            this.curZoomVal = new System.Windows.Forms.TextBox();
            this.DecreaseZoomButton = new System.Windows.Forms.Button();
            this.IncreaseZoomButton = new System.Windows.Forms.Button();
            this.label_Zoom = new System.Windows.Forms.Label();
            this.bouton_Creation = new System.Windows.Forms.Button();
            this.bouton_Duplication = new System.Windows.Forms.Button();
            this.bouton_Scaling = new System.Windows.Forms.Button();
            this.bouton_Rotation = new System.Windows.Forms.Button();
            this.bouton_Deplacement = new System.Windows.Forms.Button();
            this.bouton_Selection = new System.Windows.Forms.Button();
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
            this.Vues_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Orthographique_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Orbite_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Information_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Aide_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Mute_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.printPreviewDialog1 = new System.Windows.Forms.PrintPreviewDialog();
            this.Bille_bouton = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            this.Creation_Panel.SuspendLayout();
            this.Groupe_Palettes.SuspendLayout();
            this.Group_Butoir.SuspendLayout();
            this.Group_Elements.SuspendLayout();
            this.Group_Element2.SuspendLayout();
            this.flowLayoutPanel1.SuspendLayout();
            this.Groupe_Outils.SuspendLayout();
            this.OutilGraphique.SuspendLayout();
            this.Groupe_Proprietes.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.panel_GL);
            this.panel1.Controls.Add(this.Creation_Panel);
            this.panel1.Controls.Add(this.flowLayoutPanel1);
            this.panel1.Controls.Add(this.menuStrip1);
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
            this.panel_GL.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel_GL.Location = new System.Drawing.Point(163, 24);
            this.panel_GL.Name = "panel_GL";
            this.panel_GL.Size = new System.Drawing.Size(566, 705);
            this.panel_GL.TabIndex = 4;
            this.panel_GL.MouseClick += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseClick);
            this.panel_GL.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseDown);
            this.panel_GL.MouseLeave += new System.EventHandler(this.panel_GL_MouseLeave);
            this.panel_GL.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseUp);
            this.panel_GL.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseWheel);
            // 
            // Creation_Panel
            // 
            this.Creation_Panel.BackColor = System.Drawing.SystemColors.InactiveBorder;
            this.Creation_Panel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Creation_Panel.Controls.Add(this.Groupe_Palettes);
            this.Creation_Panel.Controls.Add(this.Group_Butoir);
            this.Creation_Panel.Controls.Add(this.Group_Elements);
            this.Creation_Panel.Controls.Add(this.Group_Element2);
            this.Creation_Panel.Controls.Add(this.Bille_bouton);
            this.Creation_Panel.Dock = System.Windows.Forms.DockStyle.Right;
            this.Creation_Panel.Location = new System.Drawing.Point(729, 24);
            this.Creation_Panel.Name = "Creation_Panel";
            this.Creation_Panel.Size = new System.Drawing.Size(225, 705);
            this.Creation_Panel.TabIndex = 2;
            this.Creation_Panel.Visible = false;
            this.Creation_Panel.MouseEnter += new System.EventHandler(this.Creation_Panel_MouseEnter);
            // 
            // Groupe_Palettes
            // 
            this.Groupe_Palettes.Controls.Add(this.PDJ2_bouton);
            this.Groupe_Palettes.Controls.Add(this.PGJ2_bouton);
            this.Groupe_Palettes.Controls.Add(this.PDJ1_bouton);
            this.Groupe_Palettes.Controls.Add(this.PGJ1_bouton);
            this.Groupe_Palettes.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.Groupe_Palettes.Location = new System.Drawing.Point(3, 3);
            this.Groupe_Palettes.Name = "Groupe_Palettes";
            this.Groupe_Palettes.Size = new System.Drawing.Size(216, 126);
            this.Groupe_Palettes.TabIndex = 5;
            this.Groupe_Palettes.TabStop = false;
            this.Groupe_Palettes.Text = "Palettes";
            // 
            // PDJ2_bouton
            // 
            this.PDJ2_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.PDJ2;
            this.PDJ2_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PDJ2_bouton.Location = new System.Drawing.Point(110, 70);
            this.PDJ2_bouton.Name = "PDJ2_bouton";
            this.PDJ2_bouton.Size = new System.Drawing.Size(100, 50);
            this.PDJ2_bouton.TabIndex = 3;
            this.PDJ2_bouton.Text = "J2";
            this.PDJ2_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.PDJ2_bouton.UseVisualStyleBackColor = true;
            this.PDJ2_bouton.Click += new System.EventHandler(this.PDJ2_bouton_Click);
            // 
            // PGJ2_bouton
            // 
            this.PGJ2_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.PGJ2;
            this.PGJ2_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PGJ2_bouton.Location = new System.Drawing.Point(6, 71);
            this.PGJ2_bouton.Name = "PGJ2_bouton";
            this.PGJ2_bouton.Size = new System.Drawing.Size(100, 49);
            this.PGJ2_bouton.TabIndex = 2;
            this.PGJ2_bouton.Text = "J2";
            this.PGJ2_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.PGJ2_bouton.UseVisualStyleBackColor = true;
            this.PGJ2_bouton.Click += new System.EventHandler(this.PGJ2_bouton_Click);
            // 
            // PDJ1_bouton
            // 
            this.PDJ1_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.PDJ1;
            this.PDJ1_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PDJ1_bouton.Location = new System.Drawing.Point(110, 19);
            this.PDJ1_bouton.Name = "PDJ1_bouton";
            this.PDJ1_bouton.Size = new System.Drawing.Size(100, 47);
            this.PDJ1_bouton.TabIndex = 1;
            this.PDJ1_bouton.Text = "J1";
            this.PDJ1_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.PDJ1_bouton.UseVisualStyleBackColor = true;
            this.PDJ1_bouton.Click += new System.EventHandler(this.PDJ1_bouton_Click);
            // 
            // PGJ1_bouton
            // 
            this.PGJ1_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.PGJ1;
            this.PGJ1_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PGJ1_bouton.Location = new System.Drawing.Point(6, 19);
            this.PGJ1_bouton.Name = "PGJ1_bouton";
            this.PGJ1_bouton.Size = new System.Drawing.Size(100, 47);
            this.PGJ1_bouton.TabIndex = 0;
            this.PGJ1_bouton.Text = "J1";
            this.PGJ1_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.PGJ1_bouton.UseVisualStyleBackColor = true;
            this.PGJ1_bouton.Click += new System.EventHandler(this.PGJ1_bouton_Click);
            // 
            // Group_Butoir
            // 
            this.Group_Butoir.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Group_Butoir.Controls.Add(this.butoirCirc_bouton);
            this.Group_Butoir.Controls.Add(this.butoirD_bouton);
            this.Group_Butoir.Controls.Add(this.butoirG_bouton);
            this.Group_Butoir.Location = new System.Drawing.Point(3, 135);
            this.Group_Butoir.Name = "Group_Butoir";
            this.Group_Butoir.Size = new System.Drawing.Size(216, 133);
            this.Group_Butoir.TabIndex = 6;
            this.Group_Butoir.TabStop = false;
            this.Group_Butoir.Text = "Butoirs";
            // 
            // butoirCirc_bouton
            // 
            this.butoirCirc_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.CibleCirc;
            this.butoirCirc_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.butoirCirc_bouton.Location = new System.Drawing.Point(62, 76);
            this.butoirCirc_bouton.Name = "butoirCirc_bouton";
            this.butoirCirc_bouton.Size = new System.Drawing.Size(98, 48);
            this.butoirCirc_bouton.TabIndex = 2;
            this.butoirCirc_bouton.Text = "Circulaire";
            this.butoirCirc_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.butoirCirc_bouton.UseVisualStyleBackColor = true;
            this.butoirCirc_bouton.Click += new System.EventHandler(this.butourCirc_bouton_Click);
            // 
            // butoirD_bouton
            // 
            this.butoirD_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.ButoirTriangD;
            this.butoirD_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.butoirD_bouton.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.butoirD_bouton.Location = new System.Drawing.Point(110, 16);
            this.butoirD_bouton.Name = "butoirD_bouton";
            this.butoirD_bouton.Size = new System.Drawing.Size(100, 54);
            this.butoirD_bouton.TabIndex = 1;
            this.butoirD_bouton.Text = "Droit";
            this.butoirD_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.butoirD_bouton.UseVisualStyleBackColor = true;
            this.butoirD_bouton.Click += new System.EventHandler(this.butoirD_bouton_Click);
            // 
            // butoirG_bouton
            // 
            this.butoirG_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.ButoirTriangG;
            this.butoirG_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.butoirG_bouton.Location = new System.Drawing.Point(4, 16);
            this.butoirG_bouton.Name = "butoirG_bouton";
            this.butoirG_bouton.Size = new System.Drawing.Size(101, 54);
            this.butoirG_bouton.TabIndex = 0;
            this.butoirG_bouton.Text = "Gauche";
            this.butoirG_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.butoirG_bouton.UseVisualStyleBackColor = true;
            this.butoirG_bouton.Click += new System.EventHandler(this.butoirG_bouton_Click);
            // 
            // Group_Elements
            // 
            this.Group_Elements.Controls.Add(this.Mur_bouton);
            this.Group_Elements.Controls.Add(this.Portails_bouton);
            this.Group_Elements.Controls.Add(this.Cible_bouton);
            this.Group_Elements.Location = new System.Drawing.Point(3, 274);
            this.Group_Elements.Name = "Group_Elements";
            this.Group_Elements.Size = new System.Drawing.Size(216, 133);
            this.Group_Elements.TabIndex = 7;
            this.Group_Elements.TabStop = false;
            this.Group_Elements.Text = "Éléments";
            // 
            // Mur_bouton
            // 
            this.Mur_bouton.BackColor = System.Drawing.Color.White;
            this.Mur_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.mur;
            this.Mur_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Mur_bouton.Location = new System.Drawing.Point(62, 78);
            this.Mur_bouton.Name = "Mur_bouton";
            this.Mur_bouton.Size = new System.Drawing.Size(98, 48);
            this.Mur_bouton.TabIndex = 2;
            this.Mur_bouton.Text = "Mur";
            this.Mur_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.Mur_bouton.UseVisualStyleBackColor = false;
            this.Mur_bouton.Click += new System.EventHandler(this.Mur_bouton_Click);
            // 
            // Portails_bouton
            // 
            this.Portails_bouton.BackColor = System.Drawing.Color.White;
            this.Portails_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.portail;
            this.Portails_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.Portails_bouton.Location = new System.Drawing.Point(110, 18);
            this.Portails_bouton.Name = "Portails_bouton";
            this.Portails_bouton.Size = new System.Drawing.Size(100, 54);
            this.Portails_bouton.TabIndex = 1;
            this.Portails_bouton.Text = "Portail";
            this.Portails_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.Portails_bouton.UseVisualStyleBackColor = false;
            this.Portails_bouton.Click += new System.EventHandler(this.Portails_bouton_Click);
            // 
            // Cible_bouton
            // 
            this.Cible_bouton.BackColor = System.Drawing.Color.White;
            this.Cible_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.cible;
            this.Cible_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.Cible_bouton.Location = new System.Drawing.Point(6, 18);
            this.Cible_bouton.Name = "Cible_bouton";
            this.Cible_bouton.Size = new System.Drawing.Size(100, 54);
            this.Cible_bouton.TabIndex = 0;
            this.Cible_bouton.Text = "Cible";
            this.Cible_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.Cible_bouton.UseVisualStyleBackColor = false;
            this.Cible_bouton.Click += new System.EventHandler(this.Cible_bouton_Click);
            // 
            // Group_Element2
            // 
            this.Group_Element2.Controls.Add(this.Trou_bouton);
            this.Group_Element2.Controls.Add(this.Generateur_bouton);
            this.Group_Element2.Controls.Add(this.Ressort_bouton);
            this.Group_Element2.Location = new System.Drawing.Point(3, 413);
            this.Group_Element2.Name = "Group_Element2";
            this.Group_Element2.Size = new System.Drawing.Size(216, 133);
            this.Group_Element2.TabIndex = 8;
            this.Group_Element2.TabStop = false;
            this.Group_Element2.Text = "Éléments de base";
            // 
            // Trou_bouton
            // 
            this.Trou_bouton.BackColor = System.Drawing.Color.White;
            this.Trou_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.Trou;
            this.Trou_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Trou_bouton.Location = new System.Drawing.Point(61, 79);
            this.Trou_bouton.Name = "Trou_bouton";
            this.Trou_bouton.Size = new System.Drawing.Size(98, 48);
            this.Trou_bouton.TabIndex = 5;
            this.Trou_bouton.Tag = "Hole";
            this.Trou_bouton.Text = "Trou";
            this.Trou_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.Trou_bouton.UseVisualStyleBackColor = false;
            this.Trou_bouton.Click += new System.EventHandler(this.Trou_bouton_Click);
            // 
            // Generateur_bouton
            // 
            this.Generateur_bouton.BackColor = System.Drawing.Color.White;
            this.Generateur_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.Generateur;
            this.Generateur_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.Generateur_bouton.Location = new System.Drawing.Point(109, 19);
            this.Generateur_bouton.Name = "Generateur_bouton";
            this.Generateur_bouton.Size = new System.Drawing.Size(100, 54);
            this.Generateur_bouton.TabIndex = 4;
            this.Generateur_bouton.Text = "Generateur de billes";
            this.Generateur_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.Generateur_bouton.TextImageRelation = System.Windows.Forms.TextImageRelation.TextAboveImage;
            this.Generateur_bouton.UseVisualStyleBackColor = false;
            this.Generateur_bouton.Click += new System.EventHandler(this.Generateur_bouton_Click);
            // 
            // Ressort_bouton
            // 
            this.Ressort_bouton.BackColor = System.Drawing.Color.White;
            this.Ressort_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.ressort;
            this.Ressort_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.Ressort_bouton.Location = new System.Drawing.Point(5, 19);
            this.Ressort_bouton.Name = "Ressort_bouton";
            this.Ressort_bouton.Size = new System.Drawing.Size(100, 54);
            this.Ressort_bouton.TabIndex = 3;
            this.Ressort_bouton.Text = "Ressort";
            this.Ressort_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
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
            this.flowLayoutPanel1.Location = new System.Drawing.Point(0, 24);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(163, 705);
            this.flowLayoutPanel1.TabIndex = 3;
            this.flowLayoutPanel1.SizeChanged += new System.EventHandler(this.flowLayoutPanel1_SizeChanged);
            // 
            // Groupe_Outils
            // 
            this.Groupe_Outils.Controls.Add(this.curZoomVal);
            this.Groupe_Outils.Controls.Add(this.DecreaseZoomButton);
            this.Groupe_Outils.Controls.Add(this.IncreaseZoomButton);
            this.Groupe_Outils.Controls.Add(this.label_Zoom);
            this.Groupe_Outils.Controls.Add(this.bouton_Creation);
            this.Groupe_Outils.Controls.Add(this.bouton_Duplication);
            this.Groupe_Outils.Controls.Add(this.bouton_Scaling);
            this.Groupe_Outils.Controls.Add(this.bouton_Rotation);
            this.Groupe_Outils.Controls.Add(this.bouton_Deplacement);
            this.Groupe_Outils.Controls.Add(this.bouton_Selection);
            this.Groupe_Outils.Location = new System.Drawing.Point(3, 3);
            this.Groupe_Outils.Name = "Groupe_Outils";
            this.Groupe_Outils.Size = new System.Drawing.Size(153, 265);
            this.Groupe_Outils.TabIndex = 0;
            this.Groupe_Outils.TabStop = false;
            this.Groupe_Outils.Text = "Outils";
            // 
            // curZoomVal
            // 
            this.curZoomVal.Location = new System.Drawing.Point(46, 237);
            this.curZoomVal.Name = "curZoomVal";
            this.curZoomVal.ReadOnly = true;
            this.curZoomVal.Size = new System.Drawing.Size(64, 20);
            this.curZoomVal.TabIndex = 9;
            this.curZoomVal.TabStop = false;
            this.curZoomVal.Text = "000";
            this.curZoomVal.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // DecreaseZoomButton
            // 
            this.DecreaseZoomButton.Enabled = false;
            this.DecreaseZoomButton.Location = new System.Drawing.Point(6, 233);
            this.DecreaseZoomButton.Name = "DecreaseZoomButton";
            this.DecreaseZoomButton.Size = new System.Drawing.Size(31, 23);
            this.DecreaseZoomButton.TabIndex = 8;
            this.DecreaseZoomButton.Text = "-";
            this.DecreaseZoomButton.UseVisualStyleBackColor = true;
            this.DecreaseZoomButton.Click += new System.EventHandler(this.DecreaseZoomButton_Click);
            // 
            // IncreaseZoomButton
            // 
            this.IncreaseZoomButton.Enabled = false;
            this.IncreaseZoomButton.Location = new System.Drawing.Point(120, 234);
            this.IncreaseZoomButton.Name = "IncreaseZoomButton";
            this.IncreaseZoomButton.Size = new System.Drawing.Size(31, 23);
            this.IncreaseZoomButton.TabIndex = 7;
            this.IncreaseZoomButton.Text = "+";
            this.IncreaseZoomButton.UseVisualStyleBackColor = true;
            this.IncreaseZoomButton.Click += new System.EventHandler(this.IncreaseZoomButton_Click);
            // 
            // label_Zoom
            // 
            this.label_Zoom.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_Zoom.Location = new System.Drawing.Point(13, 209);
            this.label_Zoom.Name = "label_Zoom";
            this.label_Zoom.Size = new System.Drawing.Size(130, 14);
            this.label_Zoom.TabIndex = 6;
            this.label_Zoom.Text = "(-)        Zoom        (+)";
            this.label_Zoom.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.label_Zoom.Click += new System.EventHandler(this.label_Zoom_Click);
            this.label_Zoom.MouseEnter += new System.EventHandler(this.label_Zoom_MouseEnter);
            this.label_Zoom.MouseLeave += new System.EventHandler(this.label_Zoom_MouseLeave);
            // 
            // bouton_Creation
            // 
            this.bouton_Creation.Location = new System.Drawing.Point(13, 176);
            this.bouton_Creation.Name = "bouton_Creation";
            this.bouton_Creation.Size = new System.Drawing.Size(130, 24);
            this.bouton_Creation.TabIndex = 5;
            this.bouton_Creation.Text = "Paneau Création";
            this.bouton_Creation.UseVisualStyleBackColor = true;
            this.bouton_Creation.Click += new System.EventHandler(this.bouton_Creation_Click);
            // 
            // bouton_Duplication
            // 
            this.bouton_Duplication.Enabled = false;
            this.bouton_Duplication.Location = new System.Drawing.Point(13, 146);
            this.bouton_Duplication.Name = "bouton_Duplication";
            this.bouton_Duplication.Size = new System.Drawing.Size(130, 24);
            this.bouton_Duplication.TabIndex = 4;
            this.bouton_Duplication.Text = "Duplication";
            this.bouton_Duplication.UseVisualStyleBackColor = true;
            this.bouton_Duplication.Click += new System.EventHandler(this.bouton_Duplication_Click);
            // 
            // bouton_Scaling
            // 
            this.bouton_Scaling.Enabled = false;
            this.bouton_Scaling.Location = new System.Drawing.Point(13, 116);
            this.bouton_Scaling.Name = "bouton_Scaling";
            this.bouton_Scaling.Size = new System.Drawing.Size(130, 24);
            this.bouton_Scaling.TabIndex = 3;
            this.bouton_Scaling.Text = "Mise à échelle";
            this.bouton_Scaling.UseVisualStyleBackColor = true;
            this.bouton_Scaling.Click += new System.EventHandler(this.bouton_Scaling_Click);
            // 
            // bouton_Rotation
            // 
            this.bouton_Rotation.Enabled = false;
            this.bouton_Rotation.Location = new System.Drawing.Point(13, 86);
            this.bouton_Rotation.Name = "bouton_Rotation";
            this.bouton_Rotation.Size = new System.Drawing.Size(130, 24);
            this.bouton_Rotation.TabIndex = 2;
            this.bouton_Rotation.Text = "Rotation";
            this.bouton_Rotation.UseVisualStyleBackColor = true;
            this.bouton_Rotation.Click += new System.EventHandler(this.bouton_Rotation_Click);
            // 
            // bouton_Deplacement
            // 
            this.bouton_Deplacement.Enabled = false;
            this.bouton_Deplacement.Location = new System.Drawing.Point(13, 55);
            this.bouton_Deplacement.Name = "bouton_Deplacement";
            this.bouton_Deplacement.Size = new System.Drawing.Size(130, 24);
            this.bouton_Deplacement.TabIndex = 1;
            this.bouton_Deplacement.Text = "Déplacement";
            this.bouton_Deplacement.UseVisualStyleBackColor = true;
            this.bouton_Deplacement.Click += new System.EventHandler(this.bouton_Deplacement_Click);
            // 
            // bouton_Selection
            // 
            this.bouton_Selection.Location = new System.Drawing.Point(13, 25);
            this.bouton_Selection.Name = "bouton_Selection";
            this.bouton_Selection.Size = new System.Drawing.Size(130, 24);
            this.bouton_Selection.TabIndex = 0;
            this.bouton_Selection.Text = "Sélection";
            this.bouton_Selection.UseVisualStyleBackColor = true;
            this.bouton_Selection.Click += new System.EventHandler(this.bouton_Selection_Click);
            // 
            // OutilGraphique
            // 
            this.OutilGraphique.Controls.Add(this.labelOCourant);
            this.OutilGraphique.Location = new System.Drawing.Point(3, 274);
            this.OutilGraphique.Name = "OutilGraphique";
            this.OutilGraphique.Size = new System.Drawing.Size(153, 49);
            this.OutilGraphique.TabIndex = 10;
            this.OutilGraphique.TabStop = false;
            this.OutilGraphique.Text = "Outil Courant";
            // 
            // labelOCourant
            // 
            this.labelOCourant.ForeColor = System.Drawing.SystemColors.InfoText;
            this.labelOCourant.Location = new System.Drawing.Point(8, 16);
            this.labelOCourant.Name = "labelOCourant";
            this.labelOCourant.Size = new System.Drawing.Size(135, 30);
            this.labelOCourant.TabIndex = 0;
            this.labelOCourant.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Groupe_Proprietes
            // 
            this.Groupe_Proprietes.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
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
            this.Groupe_Proprietes.Location = new System.Drawing.Point(3, 329);
            this.Groupe_Proprietes.Name = "Groupe_Proprietes";
            this.Groupe_Proprietes.Size = new System.Drawing.Size(153, 168);
            this.Groupe_Proprietes.TabIndex = 1;
            this.Groupe_Proprietes.TabStop = false;
            this.Groupe_Proprietes.Text = "Propriétés spaciales";
            // 
            // Annuler_prop_boutn
            // 
            this.Annuler_prop_boutn.Enabled = false;
            this.Annuler_prop_boutn.Location = new System.Drawing.Point(84, 137);
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
            this.OK_prop_bouton.Location = new System.Drawing.Point(8, 137);
            this.OK_prop_bouton.Name = "OK_prop_bouton";
            this.OK_prop_bouton.Size = new System.Drawing.Size(65, 23);
            this.OK_prop_bouton.TabIndex = 8;
            this.OK_prop_bouton.TabStop = false;
            this.OK_prop_bouton.Text = "Accepter";
            this.OK_prop_bouton.UseVisualStyleBackColor = true;
            this.OK_prop_bouton.Click += new System.EventHandler(this.OK_prop_bouton_Click);
            // 
            // Anglebox
            // 
            this.Anglebox.Enabled = false;
            this.Anglebox.Location = new System.Drawing.Point(93, 73);
            this.Anglebox.Name = "Anglebox";
            this.Anglebox.Size = new System.Drawing.Size(51, 20);
            this.Anglebox.TabIndex = 5;
            this.Anglebox.TabStop = false;
            // 
            // Angle_label
            // 
            this.Angle_label.Enabled = false;
            this.Angle_label.Location = new System.Drawing.Point(14, 73);
            this.Angle_label.Name = "Angle_label";
            this.Angle_label.Size = new System.Drawing.Size(50, 20);
            this.Angle_label.TabIndex = 6;
            this.Angle_label.Text = "Angle:";
            this.Angle_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // FMEbox
            // 
            this.FMEbox.Enabled = false;
            this.FMEbox.Location = new System.Drawing.Point(92, 101);
            this.FMEbox.Name = "FMEbox";
            this.FMEbox.Size = new System.Drawing.Size(51, 20);
            this.FMEbox.TabIndex = 7;
            this.FMEbox.TabStop = false;
            // 
            // FME_label
            // 
            this.FME_label.Enabled = false;
            this.FME_label.Location = new System.Drawing.Point(17, 102);
            this.FME_label.Name = "FME_label";
            this.FME_label.Size = new System.Drawing.Size(67, 19);
            this.FME_label.TabIndex = 4;
            this.FME_label.Text = "Scale:";
            this.FME_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Ybox
            // 
            this.Ybox.Enabled = false;
            this.Ybox.Location = new System.Drawing.Point(93, 47);
            this.Ybox.Name = "Ybox";
            this.Ybox.Size = new System.Drawing.Size(51, 20);
            this.Ybox.TabIndex = 3;
            this.Ybox.TabStop = false;
            // 
            // Y_label
            // 
            this.Y_label.Enabled = false;
            this.Y_label.Location = new System.Drawing.Point(14, 46);
            this.Y_label.Name = "Y_label";
            this.Y_label.Size = new System.Drawing.Size(73, 20);
            this.Y_label.TabIndex = 2;
            this.Y_label.Text = "Position en Y:";
            this.Y_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Xbox
            // 
            this.Xbox.Enabled = false;
            this.Xbox.Location = new System.Drawing.Point(93, 21);
            this.Xbox.Name = "Xbox";
            this.Xbox.Size = new System.Drawing.Size(51, 20);
            this.Xbox.TabIndex = 1;
            this.Xbox.TabStop = false;
            // 
            // X_label
            // 
            this.X_label.Enabled = false;
            this.X_label.Location = new System.Drawing.Point(14, 21);
            this.X_label.Name = "X_label";
            this.X_label.Size = new System.Drawing.Size(73, 20);
            this.X_label.TabIndex = 0;
            this.X_label.Text = "Position en X:";
            this.X_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // richTextBox1
            // 
            this.richTextBox1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.richTextBox1.Location = new System.Drawing.Point(3, 503);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.Size = new System.Drawing.Size(151, 109);
            this.richTextBox1.TabIndex = 11;
            this.richTextBox1.TabStop = false;
            this.richTextBox1.Text = resources.GetString("richTextBox1.Text");
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.Edition_MenuItem,
            this.Outils_MenuItem,
            this.Vues_MenuItem,
            this.Information_MenuItem,
            this.Mute_MenuItem});
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
            this.Nouveau_MenuItem.Name = "Nouveau_MenuItem";
            this.Nouveau_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.Nouveau_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.Nouveau_MenuItem.Text = "Nouveau";
            this.Nouveau_MenuItem.Click += new System.EventHandler(this.Nouveau_MenuItem_Click);
            // 
            // Ouvrir_MenuItem
            // 
            this.Ouvrir_MenuItem.Name = "Ouvrir_MenuItem";
            this.Ouvrir_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.Ouvrir_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.Ouvrir_MenuItem.Text = "Ouvrir";
            this.Ouvrir_MenuItem.Click += new System.EventHandler(this.Ouvrir_MenuItem_Click);
            // 
            // Enregistrer_MenuItem
            // 
            this.Enregistrer_MenuItem.Name = "Enregistrer_MenuItem";
            this.Enregistrer_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.Enregistrer_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.Enregistrer_MenuItem.Text = "Enregistrer";
            this.Enregistrer_MenuItem.Click += new System.EventHandler(this.Enregistrer_MenuItem_Click);
            // 
            // EnregistrerS_MenuItem
            // 
            this.EnregistrerS_MenuItem.Name = "EnregistrerS_MenuItem";
            this.EnregistrerS_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.S)));
            this.EnregistrerS_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.EnregistrerS_MenuItem.Text = "Enregistrer Sous";
            this.EnregistrerS_MenuItem.Click += new System.EventHandler(this.EnregistrerS_MenuItem_Click);
            // 
            // Proprietes_MenuItem
            // 
            this.Proprietes_MenuItem.Name = "Proprietes_MenuItem";
            this.Proprietes_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.Proprietes_MenuItem.Text = "Propriétés";
            this.Proprietes_MenuItem.Click += new System.EventHandler(this.Proprietes_MenuItem_Click);
            // 
            // ModeTest_MenuItem
            // 
            this.ModeTest_MenuItem.Name = "ModeTest_MenuItem";
            this.ModeTest_MenuItem.ShortcutKeyDisplayString = "t";
            this.ModeTest_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.ModeTest_MenuItem.Text = "Mode Test";
            this.ModeTest_MenuItem.Click += new System.EventHandler(this.ModeTest_MenuItem_Click);
            // 
            // MenuP_MenuItem
            // 
            this.MenuP_MenuItem.Name = "MenuP_MenuItem";
            this.MenuP_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Q)));
            this.MenuP_MenuItem.Size = new System.Drawing.Size(230, 22);
            this.MenuP_MenuItem.Text = "Menu Principal";
            this.MenuP_MenuItem.Click += new System.EventHandler(this.MenuP_MenuItem_Click);
            // 
            // Edition_MenuItem
            // 
            this.Edition_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Supprimer_MenuItem});
            this.Edition_MenuItem.Name = "Edition_MenuItem";
            this.Edition_MenuItem.ShortcutKeyDisplayString = "Delete";
            this.Edition_MenuItem.Size = new System.Drawing.Size(56, 20);
            this.Edition_MenuItem.Text = "Édition";
            // 
            // Supprimer_MenuItem
            // 
            this.Supprimer_MenuItem.Enabled = false;
            this.Supprimer_MenuItem.Name = "Supprimer_MenuItem";
            this.Supprimer_MenuItem.ShortcutKeys = System.Windows.Forms.Keys.Delete;
            this.Supprimer_MenuItem.Size = new System.Drawing.Size(153, 22);
            this.Supprimer_MenuItem.Text = "Supprimer";
            this.Supprimer_MenuItem.Click += new System.EventHandler(this.Supprimer_MenuItem_Click);
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
            this.Selection_MenuItem.Name = "Selection_MenuItem";
            this.Selection_MenuItem.ShortcutKeyDisplayString = "s";
            this.Selection_MenuItem.Size = new System.Drawing.Size(164, 22);
            this.Selection_MenuItem.Text = "Sélection";
            this.Selection_MenuItem.Click += new System.EventHandler(this.Selection_MenuItem_Click);
            // 
            // Deplacement_MenuItem
            // 
            this.Deplacement_MenuItem.Enabled = false;
            this.Deplacement_MenuItem.Name = "Deplacement_MenuItem";
            this.Deplacement_MenuItem.ShortcutKeyDisplayString = "d";
            this.Deplacement_MenuItem.Size = new System.Drawing.Size(164, 22);
            this.Deplacement_MenuItem.Text = "Déplacement";
            this.Deplacement_MenuItem.Click += new System.EventHandler(this.Deplacement_MenuItem_Click);
            // 
            // Rotation_MenuItem
            // 
            this.Rotation_MenuItem.Enabled = false;
            this.Rotation_MenuItem.Name = "Rotation_MenuItem";
            this.Rotation_MenuItem.ShortcutKeyDisplayString = "r";
            this.Rotation_MenuItem.Size = new System.Drawing.Size(164, 22);
            this.Rotation_MenuItem.Text = "Rotation";
            this.Rotation_MenuItem.Click += new System.EventHandler(this.Rotation_MenuItem_Click);
            // 
            // MiseE_MenuItem
            // 
            this.MiseE_MenuItem.Enabled = false;
            this.MiseE_MenuItem.Name = "MiseE_MenuItem";
            this.MiseE_MenuItem.ShortcutKeyDisplayString = "e";
            this.MiseE_MenuItem.Size = new System.Drawing.Size(164, 22);
            this.MiseE_MenuItem.Text = "Mise à échelle";
            this.MiseE_MenuItem.Click += new System.EventHandler(this.MiseE_MenuItem_Click);
            // 
            // Duplication_MenuItem
            // 
            this.Duplication_MenuItem.Enabled = false;
            this.Duplication_MenuItem.Name = "Duplication_MenuItem";
            this.Duplication_MenuItem.ShortcutKeyDisplayString = "c";
            this.Duplication_MenuItem.Size = new System.Drawing.Size(164, 22);
            this.Duplication_MenuItem.Text = "Duplication";
            this.Duplication_MenuItem.Click += new System.EventHandler(this.Duplication_MenuItem_Click);
            // 
            // Zoom_MenuItem
            // 
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
            this.Trou_MenuItem});
            this.Creation_MenuItem.Name = "Creation_MenuItem";
            this.Creation_MenuItem.Size = new System.Drawing.Size(164, 22);
            this.Creation_MenuItem.Text = "Création d\'objets";
            this.Creation_MenuItem.Click += new System.EventHandler(this.Creation_MenuItem_Click);
            // 
            // PG_J1_MenuItem
            // 
            this.PG_J1_MenuItem.Name = "PG_J1_MenuItem";
            this.PG_J1_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.PG_J1_MenuItem.Text = "Palette gauche J1";
            this.PG_J1_MenuItem.Click += new System.EventHandler(this.PG_J1_MenuItem_Click);
            // 
            // PD_J1_MenuItem
            // 
            this.PD_J1_MenuItem.Name = "PD_J1_MenuItem";
            this.PD_J1_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.PD_J1_MenuItem.Text = "Palette droite J1";
            this.PD_J1_MenuItem.Click += new System.EventHandler(this.PD_J1_MenuItem_Click);
            // 
            // PG_J2_MenuItem
            // 
            this.PG_J2_MenuItem.Name = "PG_J2_MenuItem";
            this.PG_J2_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.PG_J2_MenuItem.Text = "Palette gauche J2";
            this.PG_J2_MenuItem.Click += new System.EventHandler(this.PG_J2_MenuItem_Click);
            // 
            // PD_J2_MenuItem
            // 
            this.PD_J2_MenuItem.Name = "PD_J2_MenuItem";
            this.PD_J2_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.PD_J2_MenuItem.Text = "Palette droite J2";
            this.PD_J2_MenuItem.Click += new System.EventHandler(this.PD_J2_MenuItem_Click);
            // 
            // BTG_MenuItem
            // 
            this.BTG_MenuItem.Name = "BTG_MenuItem";
            this.BTG_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.BTG_MenuItem.Text = "Butoir triangulaire gauche";
            this.BTG_MenuItem.Click += new System.EventHandler(this.BTG_MenuItem_Click);
            // 
            // BTD_MenuItem
            // 
            this.BTD_MenuItem.Name = "BTD_MenuItem";
            this.BTD_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.BTD_MenuItem.Text = "Butoire triangulaire droit";
            this.BTD_MenuItem.Click += new System.EventHandler(this.BTD_MenuItem_Click);
            // 
            // BC_MenuItem
            // 
            this.BC_MenuItem.Name = "BC_MenuItem";
            this.BC_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.BC_MenuItem.Text = "Butoir circulaire";
            this.BC_MenuItem.Click += new System.EventHandler(this.BC_MenuItem_Click);
            // 
            // Cible_MenuItem
            // 
            this.Cible_MenuItem.Name = "Cible_MenuItem";
            this.Cible_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Cible_MenuItem.Text = "Cible";
            this.Cible_MenuItem.Click += new System.EventHandler(this.Cible_MenuItem_Click);
            // 
            // Portails_MenuItem
            // 
            this.Portails_MenuItem.Name = "Portails_MenuItem";
            this.Portails_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Portails_MenuItem.Text = "Portails";
            this.Portails_MenuItem.Click += new System.EventHandler(this.Portails_MenuItem_Click);
            // 
            // Mur_MenuItem
            // 
            this.Mur_MenuItem.Name = "Mur_MenuItem";
            this.Mur_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Mur_MenuItem.Text = "Mur";
            this.Mur_MenuItem.Click += new System.EventHandler(this.Mur_MenuItem_Click);
            // 
            // Ressort_MenuItem
            // 
            this.Ressort_MenuItem.Name = "Ressort_MenuItem";
            this.Ressort_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Ressort_MenuItem.Text = "Ressort";
            this.Ressort_MenuItem.Click += new System.EventHandler(this.Ressort_MenuItem_Click);
            // 
            // GB_MenuItem
            // 
            this.GB_MenuItem.Name = "GB_MenuItem";
            this.GB_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.GB_MenuItem.Text = "Générateur de billes";
            this.GB_MenuItem.Click += new System.EventHandler(this.GB_MenuItem_Click);
            // 
            // Trou_MenuItem
            // 
            this.Trou_MenuItem.Name = "Trou_MenuItem";
            this.Trou_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Trou_MenuItem.Text = "Trou";
            this.Trou_MenuItem.Click += new System.EventHandler(this.Trou_MenuItem_Click);
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
            this.Information_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Aide_MenuItem});
            this.Information_MenuItem.Name = "Information_MenuItem";
            this.Information_MenuItem.Size = new System.Drawing.Size(87, 20);
            this.Information_MenuItem.Text = "Informations";
            // 
            // Aide_MenuItem
            // 
            this.Aide_MenuItem.Name = "Aide_MenuItem";
            this.Aide_MenuItem.Size = new System.Drawing.Size(98, 22);
            this.Aide_MenuItem.Text = "Aide";
            this.Aide_MenuItem.Click += new System.EventHandler(this.Aide_MenuItem_Click);
            // 
            // Mute_MenuItem
            // 
            this.Mute_MenuItem.Name = "Mute_MenuItem";
            this.Mute_MenuItem.Size = new System.Drawing.Size(47, 20);
            this.Mute_MenuItem.Text = "Mute";
            this.Mute_MenuItem.Click += new System.EventHandler(this.Mute_MenuItem_Click);
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
            // Bille_bouton
            // 
            this.Bille_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.ball;
            this.Bille_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Bille_bouton.Location = new System.Drawing.Point(3, 552);
            this.Bille_bouton.Name = "Bille_bouton";
            this.Bille_bouton.Size = new System.Drawing.Size(218, 69);
            this.Bille_bouton.TabIndex = 9;
            this.Bille_bouton.Text = "bille";
            this.Bille_bouton.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.Bille_bouton.UseVisualStyleBackColor = true;
            this.Bille_bouton.Click += new System.EventHandler(this.Bille_bouton_Click);
            // 
            // Exemple
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(956, 731);
            this.Controls.Add(this.panel1);
            this.KeyPreview = true;
            this.MainMenuStrip = this.menuStrip1;
            this.MinimumSize = new System.Drawing.Size(972, 678);
            this.Name = "Exemple";
            this.Text = "Mode Edition";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Exemple_FormClosing);
            this.Load += new System.EventHandler(this.Exemple_Load);
            this.SizeChanged += new System.EventHandler(this.Fenetre_Redimension);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.Creation_Panel.ResumeLayout(false);
            this.Groupe_Palettes.ResumeLayout(false);
            this.Group_Butoir.ResumeLayout(false);
            this.Group_Elements.ResumeLayout(false);
            this.Group_Element2.ResumeLayout(false);
            this.flowLayoutPanel1.ResumeLayout(false);
            this.Groupe_Outils.ResumeLayout(false);
            this.Groupe_Outils.PerformLayout();
            this.OutilGraphique.ResumeLayout(false);
            this.Groupe_Proprietes.ResumeLayout(false);
            this.Groupe_Proprietes.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
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
        private System.Windows.Forms.ToolStripMenuItem Edition_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Ouvrir_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Proprietes_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem ModeTest_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Supprimer_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Information_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Aide_MenuItem;
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
        private System.Windows.Forms.Label label_Zoom;
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
        private System.Windows.Forms.Button IncreaseZoomButton;
        private System.Windows.Forms.Button DecreaseZoomButton;
        private System.Windows.Forms.TextBox curZoomVal;
        private System.Windows.Forms.ToolStripMenuItem Mute_MenuItem;
        private System.Windows.Forms.GroupBox OutilGraphique;
        private System.Windows.Forms.Label labelOCourant;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Button Bille_bouton;
    }
}

