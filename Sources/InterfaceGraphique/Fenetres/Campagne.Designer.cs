namespace InterfaceGraphique
{
    partial class Campagne
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
            this.ZonesChoisis = new System.Windows.Forms.ListView();
            this.colonneZone = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.colonneDiff = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.GB_Player = new System.Windows.Forms.GroupBox();
            this.RB_AI = new System.Windows.Forms.RadioButton();
            this.RB_Multi = new System.Windows.Forms.RadioButton();
            this.RB_Solo = new System.Windows.Forms.RadioButton();
            this.label_ZJDisp = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.bouton_ADD = new System.Windows.Forms.Button();
            this.bouton_REMOVE = new System.Windows.Forms.Button();
            this.bouton_REMOVEALL = new System.Windows.Forms.Button();
            this.bouton_Annuler = new System.Windows.Forms.Button();
            this.bouton_OK = new System.Windows.Forms.Button();
            this.screenShot = new System.Windows.Forms.PictureBox();
            this.ZonesDisponibles = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxName = new System.Windows.Forms.TextBox();
            this.GB_Player.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.screenShot)).BeginInit();
            this.SuspendLayout();
            // 
            // ZonesChoisis
            // 
            this.ZonesChoisis.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.colonneZone,
            this.colonneDiff});
            this.ZonesChoisis.FullRowSelect = true;
            this.ZonesChoisis.Location = new System.Drawing.Point(432, 150);
            this.ZonesChoisis.Name = "ZonesChoisis";
            this.ZonesChoisis.Size = new System.Drawing.Size(196, 274);
            this.ZonesChoisis.TabIndex = 1;
            this.ZonesChoisis.UseCompatibleStateImageBehavior = false;
            this.ZonesChoisis.View = System.Windows.Forms.View.Details;
            this.ZonesChoisis.ColumnWidthChanging += new System.Windows.Forms.ColumnWidthChangingEventHandler(this.ZonesChoisis_ColumnWidthChanging);
            this.ZonesChoisis.SelectedIndexChanged += new System.EventHandler(this.ZonesChoisis_SelectedIndexChanged);
            // 
            // colonneZone
            // 
            this.colonneZone.Text = "Zone de jeu";
            this.colonneZone.Width = 89;
            // 
            // colonneDiff
            // 
            this.colonneDiff.Text = "Difficulté";
            this.colonneDiff.Width = 89;
            // 
            // GB_Player
            // 
            this.GB_Player.Controls.Add(this.RB_AI);
            this.GB_Player.Controls.Add(this.RB_Multi);
            this.GB_Player.Controls.Add(this.RB_Solo);
            this.GB_Player.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.GB_Player.Location = new System.Drawing.Point(40, 12);
            this.GB_Player.Name = "GB_Player";
            this.GB_Player.Size = new System.Drawing.Size(588, 79);
            this.GB_Player.TabIndex = 2;
            this.GB_Player.TabStop = false;
            this.GB_Player.Text = "Nombre de joueurs";
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
            this.RB_Solo.Size = new System.Drawing.Size(57, 22);
            this.RB_Solo.TabIndex = 0;
            this.RB_Solo.TabStop = true;
            this.RB_Solo.Text = "Solo";
            this.RB_Solo.UseVisualStyleBackColor = true;
            // 
            // label_ZJDisp
            // 
            this.label_ZJDisp.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_ZJDisp.Location = new System.Drawing.Point(40, 114);
            this.label_ZJDisp.Name = "label_ZJDisp";
            this.label_ZJDisp.Size = new System.Drawing.Size(152, 23);
            this.label_ZJDisp.TabIndex = 3;
            this.label_ZJDisp.Text = "Zones de jeu disponibles";
            this.label_ZJDisp.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(445, 114);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(183, 23);
            this.label1.TabIndex = 4;
            this.label1.Text = "Zones de jeu choisies";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // bouton_ADD
            // 
            this.bouton_ADD.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.bouton_ADD.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bouton_ADD.Location = new System.Drawing.Point(24, 430);
            this.bouton_ADD.Name = "bouton_ADD";
            this.bouton_ADD.Size = new System.Drawing.Size(192, 39);
            this.bouton_ADD.TabIndex = 5;
            this.bouton_ADD.Text = "Ajouter a la liste";
            this.bouton_ADD.UseVisualStyleBackColor = true;
            this.bouton_ADD.Click += new System.EventHandler(this.bouton_ADD_Click);
            // 
            // bouton_REMOVE
            // 
            this.bouton_REMOVE.Location = new System.Drawing.Point(432, 430);
            this.bouton_REMOVE.Name = "bouton_REMOVE";
            this.bouton_REMOVE.Size = new System.Drawing.Size(91, 39);
            this.bouton_REMOVE.TabIndex = 6;
            this.bouton_REMOVE.Text = "Enlever de la liste";
            this.bouton_REMOVE.UseVisualStyleBackColor = true;
            this.bouton_REMOVE.Click += new System.EventHandler(this.bouton_REMOVE_Click);
            // 
            // bouton_REMOVEALL
            // 
            this.bouton_REMOVEALL.Location = new System.Drawing.Point(537, 430);
            this.bouton_REMOVEALL.Name = "bouton_REMOVEALL";
            this.bouton_REMOVEALL.Size = new System.Drawing.Size(91, 39);
            this.bouton_REMOVEALL.TabIndex = 7;
            this.bouton_REMOVEALL.Text = "Vider la liste";
            this.bouton_REMOVEALL.UseVisualStyleBackColor = true;
            this.bouton_REMOVEALL.Click += new System.EventHandler(this.bouton_REMOVEALL_Click);
            // 
            // bouton_Annuler
            // 
            this.bouton_Annuler.BackColor = System.Drawing.SystemColors.Control;
            this.bouton_Annuler.Location = new System.Drawing.Point(526, 513);
            this.bouton_Annuler.Name = "bouton_Annuler";
            this.bouton_Annuler.Size = new System.Drawing.Size(102, 47);
            this.bouton_Annuler.TabIndex = 8;
            this.bouton_Annuler.Text = "Annuler";
            this.bouton_Annuler.UseVisualStyleBackColor = false;
            this.bouton_Annuler.Click += new System.EventHandler(this.bouton_Annuler_Click);
            // 
            // bouton_OK
            // 
            this.bouton_OK.BackColor = System.Drawing.SystemColors.Control;
            this.bouton_OK.Location = new System.Drawing.Point(418, 513);
            this.bouton_OK.Name = "bouton_OK";
            this.bouton_OK.Size = new System.Drawing.Size(102, 47);
            this.bouton_OK.TabIndex = 9;
            this.bouton_OK.Text = "Lancer la campagne";
            this.bouton_OK.UseVisualStyleBackColor = false;
            this.bouton_OK.Click += new System.EventHandler(this.bouton_OK_Click);
            // 
            // screenShot
            // 
            this.screenShot.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.screenShot.Location = new System.Drawing.Point(222, 187);
            this.screenShot.Name = "screenShot";
            this.screenShot.Size = new System.Drawing.Size(204, 209);
            this.screenShot.TabIndex = 10;
            this.screenShot.TabStop = false;
            // 
            // ZonesDisponibles
            // 
            this.ZonesDisponibles.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2});
            this.ZonesDisponibles.FullRowSelect = true;
            this.ZonesDisponibles.Location = new System.Drawing.Point(24, 150);
            this.ZonesDisponibles.MultiSelect = false;
            this.ZonesDisponibles.Name = "ZonesDisponibles";
            this.ZonesDisponibles.Size = new System.Drawing.Size(192, 274);
            this.ZonesDisponibles.TabIndex = 11;
            this.ZonesDisponibles.UseCompatibleStateImageBehavior = false;
            this.ZonesDisponibles.View = System.Windows.Forms.View.Details;
            this.ZonesDisponibles.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.ZonesDisponibles_ColumnClick);
            this.ZonesDisponibles.ColumnWidthChanging += new System.Windows.Forms.ColumnWidthChangingEventHandler(this.ZonesDisponibles_ColumnWidthChanging);
            this.ZonesDisponibles.SelectedIndexChanged += new System.EventHandler(this.ZonesDisponibles_SelectedIndexChanged);
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Zone de jeu";
            this.columnHeader1.Width = 89;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Difficulté";
            this.columnHeader2.Width = 98;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(21, 513);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(103, 13);
            this.label2.TabIndex = 21;
            this.label2.Text = "Entrez votre nom ici:";
            // 
            // textBoxName
            // 
            this.textBoxName.Location = new System.Drawing.Point(24, 533);
            this.textBoxName.Name = "textBoxName";
            this.textBoxName.Size = new System.Drawing.Size(192, 20);
            this.textBoxName.TabIndex = 20;
            // 
            // Campagne
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(650, 572);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBoxName);
            this.Controls.Add(this.ZonesDisponibles);
            this.Controls.Add(this.screenShot);
            this.Controls.Add(this.bouton_OK);
            this.Controls.Add(this.bouton_Annuler);
            this.Controls.Add(this.bouton_REMOVEALL);
            this.Controls.Add(this.bouton_REMOVE);
            this.Controls.Add(this.bouton_ADD);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label_ZJDisp);
            this.Controls.Add(this.GB_Player);
            this.Controls.Add(this.ZonesChoisis);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = global::InterfaceGraphique.Properties.Resources.Pinball;
            this.KeyPreview = true;
            this.MaximizeBox = false;
            this.Name = "Campagne";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Campagne";
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.Campagne_KeyPress);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Campagne_KeyUp);
            this.GB_Player.ResumeLayout(false);
            this.GB_Player.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.screenShot)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView ZonesChoisis;
        private System.Windows.Forms.ColumnHeader colonneZone;
        private System.Windows.Forms.ColumnHeader colonneDiff;
        private System.Windows.Forms.GroupBox GB_Player;
        private System.Windows.Forms.RadioButton RB_AI;
        private System.Windows.Forms.RadioButton RB_Multi;
        private System.Windows.Forms.RadioButton RB_Solo;
        private System.Windows.Forms.Label label_ZJDisp;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button bouton_ADD;
        private System.Windows.Forms.Button bouton_REMOVE;
        private System.Windows.Forms.Button bouton_REMOVEALL;
        private System.Windows.Forms.Button bouton_Annuler;
        private System.Windows.Forms.Button bouton_OK;
        private System.Windows.Forms.PictureBox screenShot;
        private System.Windows.Forms.ListView ZonesDisponibles;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxName;


    }
}