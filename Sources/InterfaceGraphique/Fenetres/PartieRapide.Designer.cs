namespace InterfaceGraphique
{
    partial class PartieRapide
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
            this.ZonesDisponibles = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.screenShot = new System.Windows.Forms.PictureBox();
            this.bouton_OK = new System.Windows.Forms.Button();
            this.label_ZJDisp = new System.Windows.Forms.Label();
            this.GB_Player = new System.Windows.Forms.GroupBox();
            this.RB_AI = new System.Windows.Forms.RadioButton();
            this.RB_Multi = new System.Windows.Forms.RadioButton();
            this.RB_Solo = new System.Windows.Forms.RadioButton();
            this.bouton_Cancel = new System.Windows.Forms.Button();
            this.textBoxName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.screenShot)).BeginInit();
            this.GB_Player.SuspendLayout();
            this.SuspendLayout();
            // 
            // ZonesDisponibles
            // 
            this.ZonesDisponibles.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2});
            this.ZonesDisponibles.FullRowSelect = true;
            this.ZonesDisponibles.Location = new System.Drawing.Point(32, 143);
            this.ZonesDisponibles.MultiSelect = false;
            this.ZonesDisponibles.Name = "ZonesDisponibles";
            this.ZonesDisponibles.Size = new System.Drawing.Size(196, 340);
            this.ZonesDisponibles.TabIndex = 16;
            this.ZonesDisponibles.UseCompatibleStateImageBehavior = false;
            this.ZonesDisponibles.View = System.Windows.Forms.View.Details;
            this.ZonesDisponibles.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.ZonesDisponibles_ColumnClick);
            this.ZonesDisponibles.ColumnWidthChanging += new System.Windows.Forms.ColumnWidthChangingEventHandler(this.ZonesDisponibles_ColumnWidthChanging);
            this.ZonesDisponibles.SelectedIndexChanged += new System.EventHandler(this.ZonesDisponibles_SelectedIndexChanged);
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Zone de jeu";
            this.columnHeader1.Width = 92;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Difficulté";
            this.columnHeader2.Width = 100;
            // 
            // screenShot
            // 
            this.screenShot.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.screenShot.Location = new System.Drawing.Point(260, 143);
            this.screenShot.Name = "screenShot";
            this.screenShot.Size = new System.Drawing.Size(340, 340);
            this.screenShot.TabIndex = 15;
            this.screenShot.TabStop = false;
            // 
            // bouton_OK
            // 
            this.bouton_OK.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.bouton_OK.Enabled = false;
            this.bouton_OK.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bouton_OK.Location = new System.Drawing.Point(260, 489);
            this.bouton_OK.Name = "bouton_OK";
            this.bouton_OK.Size = new System.Drawing.Size(165, 40);
            this.bouton_OK.TabIndex = 14;
            this.bouton_OK.Text = "Lancer la partie";
            this.bouton_OK.UseVisualStyleBackColor = true;
            this.bouton_OK.Click += new System.EventHandler(this.bouton_OK_Click);
            // 
            // label_ZJDisp
            // 
            this.label_ZJDisp.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_ZJDisp.Location = new System.Drawing.Point(32, 117);
            this.label_ZJDisp.Name = "label_ZJDisp";
            this.label_ZJDisp.Size = new System.Drawing.Size(196, 23);
            this.label_ZJDisp.TabIndex = 13;
            this.label_ZJDisp.Text = "Zones de jeu disponibles";
            this.label_ZJDisp.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // GB_Player
            // 
            this.GB_Player.Controls.Add(this.RB_AI);
            this.GB_Player.Controls.Add(this.RB_Multi);
            this.GB_Player.Controls.Add(this.RB_Solo);
            this.GB_Player.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.GB_Player.Location = new System.Drawing.Point(32, 21);
            this.GB_Player.Name = "GB_Player";
            this.GB_Player.Size = new System.Drawing.Size(588, 79);
            this.GB_Player.TabIndex = 12;
            this.GB_Player.TabStop = false;
            this.GB_Player.Text = "Nombe de Joueurs";
            // 
            // RB_AI
            // 
            this.RB_AI.AutoSize = true;
            this.RB_AI.Location = new System.Drawing.Point(378, 29);
            this.RB_AI.Name = "RB_AI";
            this.RB_AI.Size = new System.Drawing.Size(165, 22);
            this.RB_AI.TabIndex = 2;
            this.RB_AI.Text = "Avec un joueur virtuel";
            this.RB_AI.UseVisualStyleBackColor = true;
            // 
            // RB_Multi
            // 
            this.RB_Multi.AutoSize = true;
            this.RB_Multi.Location = new System.Drawing.Point(182, 29);
            this.RB_Multi.Name = "RB_Multi";
            this.RB_Multi.Size = new System.Drawing.Size(151, 22);
            this.RB_Multi.TabIndex = 1;
            this.RB_Multi.Text = "Avec un joueur réel";
            this.RB_Multi.UseVisualStyleBackColor = true;
            // 
            // RB_Solo
            // 
            this.RB_Solo.AutoSize = true;
            this.RB_Solo.Checked = true;
            this.RB_Solo.Location = new System.Drawing.Point(17, 29);
            this.RB_Solo.Name = "RB_Solo";
            this.RB_Solo.Size = new System.Drawing.Size(87, 22);
            this.RB_Solo.TabIndex = 0;
            this.RB_Solo.TabStop = true;
            this.RB_Solo.Text = "Tout seul";
            this.RB_Solo.UseVisualStyleBackColor = true;
            // 
            // bouton_Cancel
            // 
            this.bouton_Cancel.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.bouton_Cancel.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bouton_Cancel.Location = new System.Drawing.Point(435, 489);
            this.bouton_Cancel.Name = "bouton_Cancel";
            this.bouton_Cancel.Size = new System.Drawing.Size(165, 40);
            this.bouton_Cancel.TabIndex = 17;
            this.bouton_Cancel.Text = "Annuler";
            this.bouton_Cancel.UseVisualStyleBackColor = true;
            this.bouton_Cancel.Click += new System.EventHandler(this.bouton_Cancel_Click);
            // 
            // textBoxName
            // 
            this.textBoxName.Location = new System.Drawing.Point(32, 506);
            this.textBoxName.Name = "textBoxName";
            this.textBoxName.Size = new System.Drawing.Size(196, 20);
            this.textBoxName.TabIndex = 18;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(29, 486);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(103, 13);
            this.label1.TabIndex = 19;
            this.label1.Text = "Entrez votre nom ici:";
            // 
            // PartieRapide
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(650, 538);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxName);
            this.Controls.Add(this.bouton_Cancel);
            this.Controls.Add(this.ZonesDisponibles);
            this.Controls.Add(this.screenShot);
            this.Controls.Add(this.bouton_OK);
            this.Controls.Add(this.label_ZJDisp);
            this.Controls.Add(this.GB_Player);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = global::InterfaceGraphique.Properties.Resources.Pinball;
            this.KeyPreview = true;
            this.MaximizeBox = false;
            this.Name = "PartieRapide";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "PartieRapide";
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.PartieRapide_KeyPress);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.PartieRapide_KeyUp);
            ((System.ComponentModel.ISupportInitialize)(this.screenShot)).EndInit();
            this.GB_Player.ResumeLayout(false);
            this.GB_Player.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ListView ZonesDisponibles;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.PictureBox screenShot;
        private System.Windows.Forms.Button bouton_OK;
        private System.Windows.Forms.Label label_ZJDisp;
        private System.Windows.Forms.GroupBox GB_Player;
        private System.Windows.Forms.RadioButton RB_AI;
        private System.Windows.Forms.RadioButton RB_Multi;
        private System.Windows.Forms.RadioButton RB_Solo;
        private System.Windows.Forms.Button bouton_Cancel;
        private System.Windows.Forms.TextBox textBoxName;
        private System.Windows.Forms.Label label1;

    }
}