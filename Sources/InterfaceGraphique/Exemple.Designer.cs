namespace InterfaceGraphique
{
    partial class Exemple
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Exemple));
            this.panel1 = new System.Windows.Forms.Panel();
            this.Creation_Panel = new System.Windows.Forms.FlowLayoutPanel();
            this.Groupe_Palettes = new System.Windows.Forms.GroupBox();
            this.PDJ2_bouton = new System.Windows.Forms.Button();
            this.PGJ2_bouton = new System.Windows.Forms.Button();
            this.PDJ1_bouton = new System.Windows.Forms.Button();
            this.PGJ1_bouton = new System.Windows.Forms.Button();
            this.Group_Butoir = new System.Windows.Forms.GroupBox();
            this.butoirD_bouton = new System.Windows.Forms.Button();
            this.butoireG_bouton = new System.Windows.Forms.Button();
            this.barre_outils = new System.Windows.Forms.ToolStrip();
            this.toolStripSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.Selectionner_BO = new System.Windows.Forms.ToolStripButton();
            this.Deplacer_BO = new System.Windows.Forms.ToolStripButton();
            this.Selection_BO = new System.Windows.Forms.ToolStripButton();
            this.Rotation_BO = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.helpToolStripButton = new System.Windows.Forms.ToolStripButton();
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
            this.Zoom_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Vues_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Orthographique_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Orbite_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Information_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Aide_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.printPreviewDialog1 = new System.Windows.Forms.PrintPreviewDialog();
            this.button1 = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            this.Creation_Panel.SuspendLayout();
            this.Groupe_Palettes.SuspendLayout();
            this.Group_Butoir.SuspendLayout();
            this.barre_outils.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.Creation_Panel);
            this.panel1.Controls.Add(this.barre_outils);
            this.panel1.Controls.Add(this.menuStrip1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(623, 428);
            this.panel1.TabIndex = 0;
            this.panel1.Click += new System.EventHandler(this.panel1_Click);
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
            // 
            // Creation_Panel
            // 
            this.Creation_Panel.BackColor = System.Drawing.SystemColors.InactiveBorder;
            this.Creation_Panel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Creation_Panel.Controls.Add(this.Groupe_Palettes);
            this.Creation_Panel.Controls.Add(this.Group_Butoir);
            this.Creation_Panel.Dock = System.Windows.Forms.DockStyle.Right;
            this.Creation_Panel.Location = new System.Drawing.Point(398, 50);
            this.Creation_Panel.Name = "Creation_Panel";
            this.Creation_Panel.Size = new System.Drawing.Size(223, 376);
            this.Creation_Panel.TabIndex = 2;
            this.Creation_Panel.Visible = false;
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
            this.PDJ2_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.flipperR;
            this.PDJ2_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PDJ2_bouton.Location = new System.Drawing.Point(110, 70);
            this.PDJ2_bouton.Name = "PDJ2_bouton";
            this.PDJ2_bouton.Size = new System.Drawing.Size(100, 50);
            this.PDJ2_bouton.TabIndex = 3;
            this.PDJ2_bouton.Text = "J2";
            this.PDJ2_bouton.UseVisualStyleBackColor = true;
            // 
            // PGJ2_bouton
            // 
            this.PGJ2_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.flipperL;
            this.PGJ2_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PGJ2_bouton.Location = new System.Drawing.Point(6, 71);
            this.PGJ2_bouton.Name = "PGJ2_bouton";
            this.PGJ2_bouton.Size = new System.Drawing.Size(100, 49);
            this.PGJ2_bouton.TabIndex = 2;
            this.PGJ2_bouton.Text = "J2";
            this.PGJ2_bouton.UseVisualStyleBackColor = true;
            // 
            // PDJ1_bouton
            // 
            this.PDJ1_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.flipperR;
            this.PDJ1_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PDJ1_bouton.Location = new System.Drawing.Point(110, 19);
            this.PDJ1_bouton.Name = "PDJ1_bouton";
            this.PDJ1_bouton.Size = new System.Drawing.Size(100, 47);
            this.PDJ1_bouton.TabIndex = 1;
            this.PDJ1_bouton.Text = "J1";
            this.PDJ1_bouton.UseVisualStyleBackColor = true;
            // 
            // PGJ1_bouton
            // 
            this.PGJ1_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.flipperL;
            this.PGJ1_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PGJ1_bouton.Location = new System.Drawing.Point(6, 19);
            this.PGJ1_bouton.Name = "PGJ1_bouton";
            this.PGJ1_bouton.Size = new System.Drawing.Size(100, 47);
            this.PGJ1_bouton.TabIndex = 0;
            this.PGJ1_bouton.Text = "J1";
            this.PGJ1_bouton.UseVisualStyleBackColor = true;
            // 
            // Group_Butoir
            // 
            this.Group_Butoir.Controls.Add(this.button1);
            this.Group_Butoir.Controls.Add(this.butoirD_bouton);
            this.Group_Butoir.Controls.Add(this.butoireG_bouton);
            this.Group_Butoir.Location = new System.Drawing.Point(3, 135);
            this.Group_Butoir.Name = "Group_Butoir";
            this.Group_Butoir.Size = new System.Drawing.Size(216, 125);
            this.Group_Butoir.TabIndex = 6;
            this.Group_Butoir.TabStop = false;
            this.Group_Butoir.Text = "Butoirs";
            // 
            // butoirD_bouton
            // 
            this.butoirD_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.butoirD;
            this.butoirD_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.butoirD_bouton.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.butoirD_bouton.Location = new System.Drawing.Point(110, 16);
            this.butoirD_bouton.Name = "butoirD_bouton";
            this.butoirD_bouton.Size = new System.Drawing.Size(100, 54);
            this.butoirD_bouton.TabIndex = 1;
            this.butoirD_bouton.UseVisualStyleBackColor = true;
            // 
            // butoireG_bouton
            // 
            this.butoireG_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.butoirL;
            this.butoireG_bouton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.butoireG_bouton.Location = new System.Drawing.Point(4, 16);
            this.butoireG_bouton.Name = "butoireG_bouton";
            this.butoireG_bouton.Size = new System.Drawing.Size(101, 54);
            this.butoireG_bouton.TabIndex = 0;
            this.butoireG_bouton.UseVisualStyleBackColor = true;
            // 
            // barre_outils
            // 
            this.barre_outils.AutoSize = false;
            this.barre_outils.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripSeparator,
            this.toolStripSeparator2,
            this.Rotation_BO,
            this.Deplacer_BO,
            this.Selection_BO,
            this.Selectionner_BO,
            this.toolStripSeparator1,
            this.helpToolStripButton});
            this.barre_outils.Location = new System.Drawing.Point(0, 24);
            this.barre_outils.Name = "barre_outils";
            this.barre_outils.Size = new System.Drawing.Size(621, 26);
            this.barre_outils.TabIndex = 1;
            // 
            // toolStripSeparator
            // 
            this.toolStripSeparator.Name = "toolStripSeparator";
            this.toolStripSeparator.Size = new System.Drawing.Size(6, 26);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 26);
            // 
            // Selectionner_BO
            // 
            this.Selectionner_BO.CheckOnClick = true;
            this.Selectionner_BO.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Selectionner_BO.Image = ((System.Drawing.Image)(resources.GetObject("Selectionner_BO.Image")));
            this.Selectionner_BO.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Selectionner_BO.Name = "Selectionner_BO";
            this.Selectionner_BO.Size = new System.Drawing.Size(23, 23);
            this.Selectionner_BO.Text = "Création";
            this.Selectionner_BO.Click += new System.EventHandler(this.Selectionner_BO_Click);
            // 
            // Deplacer_BO
            // 
            this.Deplacer_BO.CheckOnClick = true;
            this.Deplacer_BO.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Deplacer_BO.Image = ((System.Drawing.Image)(resources.GetObject("Deplacer_BO.Image")));
            this.Deplacer_BO.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Deplacer_BO.Name = "Deplacer_BO";
            this.Deplacer_BO.Size = new System.Drawing.Size(23, 23);
            this.Deplacer_BO.Text = "Deplacement";
            // 
            // Selection_BO
            // 
            this.Selection_BO.CheckOnClick = true;
            this.Selection_BO.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Selection_BO.Image = ((System.Drawing.Image)(resources.GetObject("Selection_BO.Image")));
            this.Selection_BO.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Selection_BO.Name = "Selection_BO";
            this.Selection_BO.Size = new System.Drawing.Size(23, 23);
            this.Selection_BO.Text = "Selection";
            this.Selection_BO.Click += new System.EventHandler(this.Selection_BO_Click);
            // 
            // Rotation_BO
            // 
            this.Rotation_BO.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Rotation_BO.Image = ((System.Drawing.Image)(resources.GetObject("Rotation_BO.Image")));
            this.Rotation_BO.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Rotation_BO.Name = "Rotation_BO";
            this.Rotation_BO.Size = new System.Drawing.Size(23, 23);
            this.Rotation_BO.Text = "Rotation";
            this.Rotation_BO.Click += new System.EventHandler(this.Rotation_BO_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 26);
            // 
            // helpToolStripButton
            // 
            this.helpToolStripButton.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.helpToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.helpToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("helpToolStripButton.Image")));
            this.helpToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.helpToolStripButton.Name = "helpToolStripButton";
            this.helpToolStripButton.Size = new System.Drawing.Size(23, 23);
            this.helpToolStripButton.Text = "&Aide";
            this.helpToolStripButton.Click += new System.EventHandler(this.helpToolStripButton_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.Edition_MenuItem,
            this.Outils_MenuItem,
            this.Vues_MenuItem,
            this.Information_MenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(621, 24);
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
            this.Nouveau_MenuItem.Size = new System.Drawing.Size(198, 22);
            this.Nouveau_MenuItem.Text = "Nouveau";
            this.Nouveau_MenuItem.Click += new System.EventHandler(this.nouveauToolStripMenuItem_Click);
            // 
            // Ouvrir_MenuItem
            // 
            this.Ouvrir_MenuItem.Name = "Ouvrir_MenuItem";
            this.Ouvrir_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.Ouvrir_MenuItem.Size = new System.Drawing.Size(198, 22);
            this.Ouvrir_MenuItem.Text = "Ouvrir";
            this.Ouvrir_MenuItem.Click += new System.EventHandler(this.Ouvrir_MenuItem_Click);
            // 
            // Enregistrer_MenuItem
            // 
            this.Enregistrer_MenuItem.Name = "Enregistrer_MenuItem";
            this.Enregistrer_MenuItem.Size = new System.Drawing.Size(198, 22);
            this.Enregistrer_MenuItem.Text = "Enregistrer";
            // 
            // EnregistrerS_MenuItem
            // 
            this.EnregistrerS_MenuItem.Name = "EnregistrerS_MenuItem";
            this.EnregistrerS_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.EnregistrerS_MenuItem.Size = new System.Drawing.Size(198, 22);
            this.EnregistrerS_MenuItem.Text = "Enregistrer Sous";
            this.EnregistrerS_MenuItem.Click += new System.EventHandler(this.EnregistrerS_MenuItem_Click);
            // 
            // Proprietes_MenuItem
            // 
            this.Proprietes_MenuItem.Name = "Proprietes_MenuItem";
            this.Proprietes_MenuItem.Size = new System.Drawing.Size(198, 22);
            this.Proprietes_MenuItem.Text = "Proprietes";
            // 
            // ModeTest_MenuItem
            // 
            this.ModeTest_MenuItem.Name = "ModeTest_MenuItem";
            this.ModeTest_MenuItem.Size = new System.Drawing.Size(198, 22);
            this.ModeTest_MenuItem.Text = "Mode Test";
            // 
            // MenuP_MenuItem
            // 
            this.MenuP_MenuItem.Name = "MenuP_MenuItem";
            this.MenuP_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Q)));
            this.MenuP_MenuItem.Size = new System.Drawing.Size(198, 22);
            this.MenuP_MenuItem.Text = "Menu Principal";
            this.MenuP_MenuItem.Click += new System.EventHandler(this.quitterToolStripMenuItem_Click);
            // 
            // Edition_MenuItem
            // 
            this.Edition_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Supprimer_MenuItem});
            this.Edition_MenuItem.Name = "Edition_MenuItem";
            this.Edition_MenuItem.Size = new System.Drawing.Size(56, 20);
            this.Edition_MenuItem.Text = "Édition";
            // 
            // Supprimer_MenuItem
            // 
            this.Supprimer_MenuItem.Name = "Supprimer_MenuItem";
            this.Supprimer_MenuItem.ShortcutKeys = System.Windows.Forms.Keys.Delete;
            this.Supprimer_MenuItem.Size = new System.Drawing.Size(153, 22);
            this.Supprimer_MenuItem.Text = "Supprimer";
            // 
            // Outils_MenuItem
            // 
            this.Outils_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Selection_MenuItem,
            this.Deplacement_MenuItem,
            this.Rotation_MenuItem,
            this.MiseE_MenuItem,
            this.Duplication_MenuItem,
            this.Creation_MenuItem,
            this.Zoom_MenuItem});
            this.Outils_MenuItem.Name = "Outils_MenuItem";
            this.Outils_MenuItem.Size = new System.Drawing.Size(50, 20);
            this.Outils_MenuItem.Text = "Outils";
            // 
            // Selection_MenuItem
            // 
            this.Selection_MenuItem.Name = "Selection_MenuItem";
            this.Selection_MenuItem.Size = new System.Drawing.Size(186, 22);
            this.Selection_MenuItem.Text = "Sélection";
            this.Selection_MenuItem.Click += new System.EventHandler(this.Selection_MenuItem_Click);
            // 
            // Deplacement_MenuItem
            // 
            this.Deplacement_MenuItem.Name = "Deplacement_MenuItem";
            this.Deplacement_MenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.D)));
            this.Deplacement_MenuItem.Size = new System.Drawing.Size(186, 22);
            this.Deplacement_MenuItem.Text = "Déplacement";
            // 
            // Rotation_MenuItem
            // 
            this.Rotation_MenuItem.Name = "Rotation_MenuItem";
            this.Rotation_MenuItem.Size = new System.Drawing.Size(186, 22);
            this.Rotation_MenuItem.Text = "Rotation";
            this.Rotation_MenuItem.Click += new System.EventHandler(this.Rotation_MenuItem_Click);
            // 
            // MiseE_MenuItem
            // 
            this.MiseE_MenuItem.Name = "MiseE_MenuItem";
            this.MiseE_MenuItem.Size = new System.Drawing.Size(186, 22);
            this.MiseE_MenuItem.Text = "Mise à échelle";
            // 
            // Duplication_MenuItem
            // 
            this.Duplication_MenuItem.Name = "Duplication_MenuItem";
            this.Duplication_MenuItem.Size = new System.Drawing.Size(186, 22);
            this.Duplication_MenuItem.Text = "Duplication";
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
            this.Creation_MenuItem.Size = new System.Drawing.Size(186, 22);
            this.Creation_MenuItem.Text = "Création d\'objets";
            // 
            // PG_J1_MenuItem
            // 
            this.PG_J1_MenuItem.Name = "PG_J1_MenuItem";
            this.PG_J1_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.PG_J1_MenuItem.Text = "Palette gauche J1";
            // 
            // PD_J1_MenuItem
            // 
            this.PD_J1_MenuItem.Name = "PD_J1_MenuItem";
            this.PD_J1_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.PD_J1_MenuItem.Text = "Palette droite J1";
            // 
            // PG_J2_MenuItem
            // 
            this.PG_J2_MenuItem.Name = "PG_J2_MenuItem";
            this.PG_J2_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.PG_J2_MenuItem.Text = "Palette gauche J2";
            // 
            // PD_J2_MenuItem
            // 
            this.PD_J2_MenuItem.Name = "PD_J2_MenuItem";
            this.PD_J2_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.PD_J2_MenuItem.Text = "Palette droite J2";
            // 
            // BTG_MenuItem
            // 
            this.BTG_MenuItem.Name = "BTG_MenuItem";
            this.BTG_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.BTG_MenuItem.Text = "Butoir triangulaire gauche";
            // 
            // BTD_MenuItem
            // 
            this.BTD_MenuItem.Name = "BTD_MenuItem";
            this.BTD_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.BTD_MenuItem.Text = "Butoire triangulaire droit";
            // 
            // BC_MenuItem
            // 
            this.BC_MenuItem.Name = "BC_MenuItem";
            this.BC_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.BC_MenuItem.Text = "Butoir circulaire";
            // 
            // Cible_MenuItem
            // 
            this.Cible_MenuItem.Name = "Cible_MenuItem";
            this.Cible_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Cible_MenuItem.Text = "Cible";
            // 
            // Portails_MenuItem
            // 
            this.Portails_MenuItem.Name = "Portails_MenuItem";
            this.Portails_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Portails_MenuItem.Text = "Portails";
            // 
            // Mur_MenuItem
            // 
            this.Mur_MenuItem.Name = "Mur_MenuItem";
            this.Mur_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Mur_MenuItem.Text = "Mur";
            // 
            // Ressort_MenuItem
            // 
            this.Ressort_MenuItem.Name = "Ressort_MenuItem";
            this.Ressort_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Ressort_MenuItem.Text = "Ressort";
            // 
            // GB_MenuItem
            // 
            this.GB_MenuItem.Name = "GB_MenuItem";
            this.GB_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.GB_MenuItem.Text = "Générateur de billes";
            // 
            // Trou_MenuItem
            // 
            this.Trou_MenuItem.Name = "Trou_MenuItem";
            this.Trou_MenuItem.Size = new System.Drawing.Size(211, 22);
            this.Trou_MenuItem.Text = "Trou";
            // 
            // Zoom_MenuItem
            // 
            this.Zoom_MenuItem.Name = "Zoom_MenuItem";
            this.Zoom_MenuItem.Size = new System.Drawing.Size(186, 22);
            this.Zoom_MenuItem.Text = "Zoom";
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
            this.Orthographique_MenuItem.Size = new System.Drawing.Size(159, 22);
            this.Orthographique_MenuItem.Text = "Orthographique";
            // 
            // Orbite_MenuItem
            // 
            this.Orbite_MenuItem.Name = "Orbite_MenuItem";
            this.Orbite_MenuItem.Size = new System.Drawing.Size(159, 22);
            this.Orbite_MenuItem.Text = "Orbite";
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
            // button1
            // 
            this.button1.BackgroundImage = global::InterfaceGraphique.Properties.Resources.but;
            this.button1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.button1.Location = new System.Drawing.Point(62, 76);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(98, 48);
            this.button1.TabIndex = 2;
            this.button1.UseVisualStyleBackColor = true;
            // 
            // Exemple
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(623, 428);
            this.Controls.Add(this.panel1);
            this.MainMenuStrip = this.menuStrip1;
            this.MinimumSize = new System.Drawing.Size(400, 400);
            this.Name = "Exemple";
            this.Text = "Mode Edition";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Exemple_FormClosing);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.Creation_Panel.ResumeLayout(false);
            this.Groupe_Palettes.ResumeLayout(false);
            this.Group_Butoir.ResumeLayout(false);
            this.barre_outils.ResumeLayout(false);
            this.barre_outils.PerformLayout();
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
        private System.Windows.Forms.ToolStrip barre_outils;
        private System.Windows.Forms.ToolStripButton Selectionner_BO;
        private System.Windows.Forms.ToolStripButton Deplacer_BO;
        private System.Windows.Forms.ToolStripButton Selection_BO;
        private System.Windows.Forms.ToolStripButton Rotation_BO;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton helpToolStripButton;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.FlowLayoutPanel Creation_Panel;
        private System.Windows.Forms.GroupBox Groupe_Palettes;
        private System.Windows.Forms.PrintPreviewDialog printPreviewDialog1;
        private System.Windows.Forms.Button PDJ1_bouton;
        private System.Windows.Forms.Button PGJ1_bouton;
        private System.Windows.Forms.Button PDJ2_bouton;
        private System.Windows.Forms.Button PGJ2_bouton;
        private System.Windows.Forms.GroupBox Group_Butoir;
        private System.Windows.Forms.Button butoirD_bouton;
        private System.Windows.Forms.Button butoireG_bouton;
        private System.Windows.Forms.Button button1;
    }
}

