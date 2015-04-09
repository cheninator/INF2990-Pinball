//////////////////////////////////////////////////////////////////////////////
/// @file Aide.cs
/// @author Ballers
/// @date 2015-01-27
/// @version 1.0 
///
/// @ingroup InterfaceGraphique
//////////////////////////////////////////////////////////////////////////////

using System.IO;
namespace InterfaceGraphique
{
    partial class Aide
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Aide));
            System.Windows.Forms.ListViewItem listViewItem123 = new System.Windows.Forms.ListViewItem("          Nouveau");
            System.Windows.Forms.ListViewItem listViewItem124 = new System.Windows.Forms.ListViewItem("          Ouvrir");
            System.Windows.Forms.ListViewItem listViewItem125 = new System.Windows.Forms.ListViewItem("          Enregistrer");
            System.Windows.Forms.ListViewItem listViewItem126 = new System.Windows.Forms.ListViewItem("          Enregistrer Sous");
            System.Windows.Forms.ListViewItem listViewItem127 = new System.Windows.Forms.ListViewItem("          Propriétés");
            System.Windows.Forms.ListViewItem listViewItem128 = new System.Windows.Forms.ListViewItem("          Mode Test");
            System.Windows.Forms.ListViewItem listViewItem129 = new System.Windows.Forms.ListViewItem("          Menu Principal");
            System.Windows.Forms.ListViewItem listViewItem130 = new System.Windows.Forms.ListViewItem("          Vue Orthographique");
            System.Windows.Forms.ListViewItem listViewItem131 = new System.Windows.Forms.ListViewItem("          Vue Orbite");
            System.Windows.Forms.ListViewItem listViewItem132 = new System.Windows.Forms.ListViewItem("             Selection");
            System.Windows.Forms.ListViewItem listViewItem133 = new System.Windows.Forms.ListViewItem("             Séléction Multiple");
            System.Windows.Forms.ListViewItem listViewItem134 = new System.Windows.Forms.ListViewItem("             Déplacement");
            System.Windows.Forms.ListViewItem listViewItem135 = new System.Windows.Forms.ListViewItem("             Rotation");
            System.Windows.Forms.ListViewItem listViewItem136 = new System.Windows.Forms.ListViewItem("             Duplication");
            System.Windows.Forms.ListViewItem listViewItem137 = new System.Windows.Forms.ListViewItem("             Mise à échelle");
            System.Windows.Forms.ListViewItem listViewItem138 = new System.Windows.Forms.ListViewItem("             Suppression");
            System.Windows.Forms.ListViewItem listViewItem139 = new System.Windows.Forms.ListViewItem("             Création");
            System.Windows.Forms.ListViewItem listViewItem140 = new System.Windows.Forms.ListViewItem("             Zoom Élastique");
            System.Windows.Forms.ListViewItem listViewItem113 = new System.Windows.Forms.ListViewItem("                Palette");
            System.Windows.Forms.ListViewItem listViewItem114 = new System.Windows.Forms.ListViewItem("                Butoir Triangulaire");
            System.Windows.Forms.ListViewItem listViewItem115 = new System.Windows.Forms.ListViewItem("                Butoir Circulaire");
            System.Windows.Forms.ListViewItem listViewItem116 = new System.Windows.Forms.ListViewItem("                Cible");
            System.Windows.Forms.ListViewItem listViewItem117 = new System.Windows.Forms.ListViewItem("                Portail");
            System.Windows.Forms.ListViewItem listViewItem118 = new System.Windows.Forms.ListViewItem("                Mur");
            System.Windows.Forms.ListViewItem listViewItem119 = new System.Windows.Forms.ListViewItem("                Porte");
            System.Windows.Forms.ListViewItem listViewItem120 = new System.Windows.Forms.ListViewItem("                Ressort");
            System.Windows.Forms.ListViewItem listViewItem121 = new System.Windows.Forms.ListViewItem("                Générateur de Billes");
            System.Windows.Forms.ListViewItem listViewItem122 = new System.Windows.Forms.ListViewItem("                Trou");
            System.Windows.Forms.ListViewGroup listViewGroup17 = new System.Windows.Forms.ListViewGroup("Outils", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup18 = new System.Windows.Forms.ListViewGroup("Divers", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup19 = new System.Windows.Forms.ListViewGroup("Mode Test", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup20 = new System.Windows.Forms.ListViewGroup("Fichiers", System.Windows.Forms.HorizontalAlignment.Left);
            this.panel1 = new System.Windows.Forms.Panel();
            this.panelBottom = new System.Windows.Forms.Panel();
            this.checkBoxHelp = new System.Windows.Forms.CheckBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.labelAccueil = new System.Windows.Forms.Label();
            this.pictureBoxAccueil = new System.Windows.Forms.PictureBox();
            this.tabPage6 = new System.Windows.Forms.TabPage();
            this.pictureBoxBase = new System.Windows.Forms.PictureBox();
            this.labelBase = new System.Windows.Forms.Label();
            this.listViewBase = new System.Windows.Forms.ListView();
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.tabPage5 = new System.Windows.Forms.TabPage();
            this.labelDescOutil = new System.Windows.Forms.Label();
            this.pictureBoxOutils = new System.Windows.Forms.PictureBox();
            this.listView1 = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.listView2 = new System.Windows.Forms.ListView();
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.pictureBoxObjets = new System.Windows.Forms.PictureBox();
            this.labelDescObj = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.listViewShortcut = new System.Windows.Forms.ListView();
            this.Commande = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Touche = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.label2 = new System.Windows.Forms.Label();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.panel1.SuspendLayout();
            this.panelBottom.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxAccueil)).BeginInit();
            this.tabPage6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxBase)).BeginInit();
            this.tabPage5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxOutils)).BeginInit();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxObjets)).BeginInit();
            this.tabPage2.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.AutoSize = true;
            this.panel1.Controls.Add(this.panelBottom);
            this.panel1.Controls.Add(this.tabControl1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(602, 399);
            this.panel1.TabIndex = 0;
            // 
            // panelBottom
            // 
            this.panelBottom.Controls.Add(this.checkBoxHelp);
            this.panelBottom.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panelBottom.Location = new System.Drawing.Point(0, 399);
            this.panelBottom.Name = "panelBottom";
            this.panelBottom.Size = new System.Drawing.Size(602, 0);
            this.panelBottom.TabIndex = 1;
            // 
            // checkBoxHelp
            // 
            this.checkBoxHelp.AutoSize = true;
            this.checkBoxHelp.Location = new System.Drawing.Point(421, 6);
            this.checkBoxHelp.Name = "checkBoxHelp";
            this.checkBoxHelp.Size = new System.Drawing.Size(170, 17);
            this.checkBoxHelp.TabIndex = 1;
            this.checkBoxHelp.Text = "Ne pas montrer l\'aide au début";
            this.checkBoxHelp.UseVisualStyleBackColor = true;
            this.checkBoxHelp.CheckedChanged += new System.EventHandler(this.checkBoxHelp_CheckedChanged);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage6);
            this.tabControl1.Controls.Add(this.tabPage5);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(602, 399);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.labelAccueil);
            this.tabPage1.Controls.Add(this.pictureBoxAccueil);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(594, 373);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "  ACCUEIL";
            this.tabPage1.ToolTipText = "Aide";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // labelAccueil
            // 
            this.labelAccueil.Location = new System.Drawing.Point(8, 6);
            this.labelAccueil.Name = "labelAccueil";
            this.labelAccueil.Size = new System.Drawing.Size(278, 356);
            this.labelAccueil.TabIndex = 1;
            this.labelAccueil.Text = resources.GetString("labelAccueil.Text");
            // 
            // pictureBoxAccueil
            // 
            this.pictureBoxAccueil.BackgroundImage = global::InterfaceGraphique.Properties.Resources.tablePhoto;
            this.pictureBoxAccueil.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.pictureBoxAccueil.Location = new System.Drawing.Point(303, 6);
            this.pictureBoxAccueil.Name = "pictureBoxAccueil";
            this.pictureBoxAccueil.Size = new System.Drawing.Size(283, 356);
            this.pictureBoxAccueil.TabIndex = 0;
            this.pictureBoxAccueil.TabStop = false;
            // 
            // tabPage6
            // 
            this.tabPage6.Controls.Add(this.pictureBoxBase);
            this.tabPage6.Controls.Add(this.labelBase);
            this.tabPage6.Controls.Add(this.listViewBase);
            this.tabPage6.Location = new System.Drawing.Point(4, 22);
            this.tabPage6.Name = "tabPage6";
            this.tabPage6.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage6.Size = new System.Drawing.Size(594, 373);
            this.tabPage6.TabIndex = 5;
            this.tabPage6.Text = "ÉLÉMENTS DE BASE";
            this.tabPage6.UseVisualStyleBackColor = true;
            // 
            // pictureBoxBase
            // 
            this.pictureBoxBase.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBoxBase.Location = new System.Drawing.Point(239, 17);
            this.pictureBoxBase.Name = "pictureBoxBase";
            this.pictureBoxBase.Size = new System.Drawing.Size(340, 340);
            this.pictureBoxBase.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBoxBase.TabIndex = 3;
            this.pictureBoxBase.TabStop = false;
            // 
            // labelBase
            // 
            this.labelBase.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.labelBase.Location = new System.Drawing.Point(9, 213);
            this.labelBase.Name = "labelBase";
            this.labelBase.Size = new System.Drawing.Size(206, 144);
            this.labelBase.TabIndex = 2;
            // 
            // listViewBase
            // 
            this.listViewBase.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader3});
            this.listViewBase.FullRowSelect = true;
            this.listViewBase.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            listViewItem123,
            listViewItem124,
            listViewItem125,
            listViewItem126,
            listViewItem127,
            listViewItem128,
            listViewItem129,
            listViewItem130,
            listViewItem131});
            this.listViewBase.Location = new System.Drawing.Point(9, 21);
            this.listViewBase.Name = "listViewBase";
            this.listViewBase.Size = new System.Drawing.Size(206, 189);
            this.listViewBase.TabIndex = 1;
            this.listViewBase.UseCompatibleStateImageBehavior = false;
            this.listViewBase.View = System.Windows.Forms.View.Details;
            this.listViewBase.SelectedIndexChanged += new System.EventHandler(this.listViewBase_SelectedIndexChanged);
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "                  Éléments de base";
            this.columnHeader3.Width = 202;
            // 
            // tabPage5
            // 
            this.tabPage5.Controls.Add(this.labelDescOutil);
            this.tabPage5.Controls.Add(this.pictureBoxOutils);
            this.tabPage5.Controls.Add(this.listView1);
            this.tabPage5.Location = new System.Drawing.Point(4, 22);
            this.tabPage5.Name = "tabPage5";
            this.tabPage5.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage5.Size = new System.Drawing.Size(594, 373);
            this.tabPage5.TabIndex = 4;
            this.tabPage5.Text = "    OUTILS     ";
            this.tabPage5.UseVisualStyleBackColor = true;
            // 
            // labelDescOutil
            // 
            this.labelDescOutil.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.labelDescOutil.Location = new System.Drawing.Point(9, 209);
            this.labelDescOutil.Name = "labelDescOutil";
            this.labelDescOutil.Size = new System.Drawing.Size(207, 148);
            this.labelDescOutil.TabIndex = 2;
            // 
            // pictureBoxOutils
            // 
            this.pictureBoxOutils.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBoxOutils.Location = new System.Drawing.Point(241, 17);
            this.pictureBoxOutils.Name = "pictureBoxOutils";
            this.pictureBoxOutils.Size = new System.Drawing.Size(340, 340);
            this.pictureBoxOutils.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBoxOutils.TabIndex = 1;
            this.pictureBoxOutils.TabStop = false;
            // 
            // listView1
            // 
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1});
            this.listView1.FullRowSelect = true;
            listViewItem132.ToolTipText = "Outil de séléction";
            listViewItem133.ToolTipText = "Outil Séléction Multiple";
            listViewItem134.ToolTipText = "Outil Déplacement";
            listViewItem135.ToolTipText = "Outil Rotation";
            listViewItem136.ToolTipText = "Outil Duplication";
            listViewItem137.ToolTipText = "Outil Mise à échelle";
            listViewItem138.ToolTipText = "Outil Suppression";
            listViewItem139.ToolTipText = "Outil Création";
            listViewItem140.ToolTipText = "Outil Zoom";
            this.listView1.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            listViewItem132,
            listViewItem133,
            listViewItem134,
            listViewItem135,
            listViewItem136,
            listViewItem137,
            listViewItem138,
            listViewItem139,
            listViewItem140});
            this.listView1.Location = new System.Drawing.Point(9, 17);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(206, 189);
            this.listView1.TabIndex = 0;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.ColumnWidthChanging += new System.Windows.Forms.ColumnWidthChangingEventHandler(this.listView1_ColumnWidthChanging);
            this.listView1.SelectedIndexChanged += new System.EventHandler(this.listView1_SelectedIndexChanged);
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "                         Outils";
            this.columnHeader1.Width = 202;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.listView2);
            this.tabPage3.Controls.Add(this.pictureBoxObjets);
            this.tabPage3.Controls.Add(this.labelDescObj);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(594, 373);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "     OBJETS     ";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // listView2
            // 
            this.listView2.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader2});
            this.listView2.FullRowSelect = true;
            this.listView2.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            listViewItem113,
            listViewItem114,
            listViewItem115,
            listViewItem116,
            listViewItem117,
            listViewItem118,
            listViewItem119,
            listViewItem120,
            listViewItem121,
            listViewItem122});
            this.listView2.Location = new System.Drawing.Point(8, 17);
            this.listView2.Name = "listView2";
            this.listView2.Size = new System.Drawing.Size(208, 198);
            this.listView2.TabIndex = 2;
            this.listView2.UseCompatibleStateImageBehavior = false;
            this.listView2.View = System.Windows.Forms.View.Details;
            this.listView2.ColumnWidthChanging += new System.Windows.Forms.ColumnWidthChangingEventHandler(this.listView2_ColumnWidthChanging);
            this.listView2.SelectedIndexChanged += new System.EventHandler(this.listView2_SelectedIndexChanged);
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "                         Objets";
            this.columnHeader2.Width = 203;
            // 
            // pictureBoxObjets
            // 
            this.pictureBoxObjets.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBoxObjets.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBoxObjets.Location = new System.Drawing.Point(247, 17);
            this.pictureBoxObjets.Name = "pictureBoxObjets";
            this.pictureBoxObjets.Size = new System.Drawing.Size(340, 340);
            this.pictureBoxObjets.TabIndex = 1;
            this.pictureBoxObjets.TabStop = false;
            // 
            // labelDescObj
            // 
            this.labelDescObj.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.labelDescObj.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelDescObj.Location = new System.Drawing.Point(9, 218);
            this.labelDescObj.Name = "labelDescObj";
            this.labelDescObj.Size = new System.Drawing.Size(207, 139);
            this.labelDescObj.TabIndex = 0;
            this.labelDescObj.Text = "\r\n";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.listViewShortcut);
            this.tabPage2.Controls.Add(this.label2);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(594, 373);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "  RACCOURCIS  ";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // listViewShortcut
            // 
            this.listViewShortcut.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.Commande,
            this.Touche});
            this.listViewShortcut.FullRowSelect = true;
            listViewGroup17.Header = "Outils";
            listViewGroup17.Name = "listViewGroup1";
            listViewGroup18.Header = "Divers";
            listViewGroup18.Name = "listViewGroup2";
            listViewGroup19.Header = "Mode Test";
            listViewGroup19.Name = "listViewGroup3";
            listViewGroup20.Header = "Fichiers";
            listViewGroup20.Name = "listViewGroup4";
            this.listViewShortcut.Groups.AddRange(new System.Windows.Forms.ListViewGroup[] {
            listViewGroup17,
            listViewGroup18,
            listViewGroup19,
            listViewGroup20});
            this.listViewShortcut.Location = new System.Drawing.Point(10, 18);
            this.listViewShortcut.Name = "listViewShortcut";
            this.listViewShortcut.Size = new System.Drawing.Size(578, 344);
            this.listViewShortcut.TabIndex = 1;
            this.listViewShortcut.UseCompatibleStateImageBehavior = false;
            this.listViewShortcut.View = System.Windows.Forms.View.Details;
            this.listViewShortcut.ColumnWidthChanging += new System.Windows.Forms.ColumnWidthChangingEventHandler(this.listViewShortcut_ColumnWidthChanging);
            // 
            // Commande
            // 
            this.Commande.Text = "Commande";
            this.Commande.Width = 312;
            // 
            // Touche
            // 
            this.Touche.Text = "Touche";
            this.Touche.Width = 244;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label2.Location = new System.Drawing.Point(3, 3);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(0, 13);
            this.label2.TabIndex = 0;
            // 
            // tabPage4
            // 
            this.tabPage4.BackgroundImage = global::InterfaceGraphique.Properties.Resources.SaintTrinity;
            this.tabPage4.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(594, 373);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "REMERCIMENTS";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // Aide
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(602, 399);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Aide";
            this.Text = "Aide";
            this.panel1.ResumeLayout(false);
            this.panelBottom.ResumeLayout(false);
            this.panelBottom.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxAccueil)).EndInit();
            this.tabPage6.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxBase)).EndInit();
            this.tabPage5.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxOutils)).EndInit();
            this.tabPage3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxObjets)).EndInit();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label labelDescObj;
        private System.Windows.Forms.PictureBox pictureBoxObjets;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.TabPage tabPage5;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.Label labelDescOutil;
        private System.Windows.Forms.PictureBox pictureBoxOutils;
        private System.Windows.Forms.ListView listView2;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ListView listViewShortcut;
        private System.Windows.Forms.ColumnHeader Commande;
        private System.Windows.Forms.ColumnHeader Touche;
        private System.Windows.Forms.PictureBox pictureBoxAccueil;
        private System.Windows.Forms.Label labelAccueil;
        private System.Windows.Forms.TabPage tabPage6;
        private System.Windows.Forms.ListView listViewBase;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.PictureBox pictureBoxBase;
        private System.Windows.Forms.Label labelBase;
        private System.Windows.Forms.Panel panelBottom;
        private System.Windows.Forms.CheckBox checkBoxHelp;




    }
}