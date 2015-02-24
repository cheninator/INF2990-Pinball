namespace InterfaceGraphique
{
    partial class Configuration
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
            this.tabProprietes = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.label_Rebind = new System.Windows.Forms.Label();
            this.Ressort_bouton = new System.Windows.Forms.Button();
            this.PDJ2_bouton = new System.Windows.Forms.Button();
            this.PGJ2_bouton = new System.Windows.Forms.Button();
            this.PDJ1_bouton = new System.Windows.Forms.Button();
            this.PGJ1_bouton = new System.Windows.Forms.Button();
            this.Default_bouton = new System.Windows.Forms.Button();
            this.label_Ressort = new System.Windows.Forms.Label();
            this.label_PDJ2 = new System.Windows.Forms.Label();
            this.label_PGJ2 = new System.Windows.Forms.Label();
            this.label_PDJ1 = new System.Windows.Forms.Label();
            this.Label_PGJ1 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.comboBoxBilles = new System.Windows.Forms.ComboBox();
            this.labelDoublesBilles = new System.Windows.Forms.Label();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.OK_bouton = new System.Windows.Forms.Button();
            this.Annuler_bouton = new System.Windows.Forms.Button();
            this.MDB_OK = new System.Windows.Forms.RadioButton();
            this.MDB_Cancel = new System.Windows.Forms.RadioButton();
            this.GBox_ModeBilles = new System.Windows.Forms.GroupBox();
            this.GBOX_acceleration = new System.Windows.Forms.GroupBox();
            this.FRS_Cancel = new System.Windows.Forms.RadioButton();
            this.FRS_OK = new System.Windows.Forms.RadioButton();
            this.tabProprietes.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.GBox_ModeBilles.SuspendLayout();
            this.GBOX_acceleration.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabProprietes
            // 
            this.tabProprietes.Controls.Add(this.tabPage1);
            this.tabProprietes.Controls.Add(this.tabPage2);
            this.tabProprietes.Controls.Add(this.tabPage3);
            this.tabProprietes.Location = new System.Drawing.Point(13, 13);
            this.tabProprietes.Name = "tabProprietes";
            this.tabProprietes.SelectedIndex = 0;
            this.tabProprietes.Size = new System.Drawing.Size(310, 432);
            this.tabProprietes.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.label_Rebind);
            this.tabPage1.Controls.Add(this.Ressort_bouton);
            this.tabPage1.Controls.Add(this.PDJ2_bouton);
            this.tabPage1.Controls.Add(this.PGJ2_bouton);
            this.tabPage1.Controls.Add(this.PDJ1_bouton);
            this.tabPage1.Controls.Add(this.PGJ1_bouton);
            this.tabPage1.Controls.Add(this.Default_bouton);
            this.tabPage1.Controls.Add(this.label_Ressort);
            this.tabPage1.Controls.Add(this.label_PDJ2);
            this.tabPage1.Controls.Add(this.label_PGJ2);
            this.tabPage1.Controls.Add(this.label_PDJ1);
            this.tabPage1.Controls.Add(this.Label_PGJ1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(302, 406);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Touches";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // label_Rebind
            // 
            this.label_Rebind.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_Rebind.ForeColor = System.Drawing.Color.DarkRed;
            this.label_Rebind.Location = new System.Drawing.Point(6, 373);
            this.label_Rebind.Name = "label_Rebind";
            this.label_Rebind.Size = new System.Drawing.Size(282, 30);
            this.label_Rebind.TabIndex = 16;
            this.label_Rebind.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Ressort_bouton
            // 
            this.Ressort_bouton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.Ressort_bouton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Ressort_bouton.Location = new System.Drawing.Point(170, 280);
            this.Ressort_bouton.Name = "Ressort_bouton";
            this.Ressort_bouton.Size = new System.Drawing.Size(118, 35);
            this.Ressort_bouton.TabIndex = 15;
            this.Ressort_bouton.Text = "Espace";
            this.Ressort_bouton.UseVisualStyleBackColor = true;
            this.Ressort_bouton.Click += new System.EventHandler(this.Ressort_bouton_Click);
            this.Ressort_bouton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Ressort_bouton_KeyDown);
            // 
            // PDJ2_bouton
            // 
            this.PDJ2_bouton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.PDJ2_bouton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PDJ2_bouton.Location = new System.Drawing.Point(170, 215);
            this.PDJ2_bouton.Name = "PDJ2_bouton";
            this.PDJ2_bouton.Size = new System.Drawing.Size(118, 35);
            this.PDJ2_bouton.TabIndex = 14;
            this.PDJ2_bouton.Text = "5";
            this.PDJ2_bouton.UseVisualStyleBackColor = true;
            this.PDJ2_bouton.Click += new System.EventHandler(this.PDJ2_bouton_Click);
            this.PDJ2_bouton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.PDJ2_bouton_KeyDown);
            // 
            // PGJ2_bouton
            // 
            this.PGJ2_bouton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.PGJ2_bouton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PGJ2_bouton.Location = new System.Drawing.Point(170, 150);
            this.PGJ2_bouton.Name = "PGJ2_bouton";
            this.PGJ2_bouton.Size = new System.Drawing.Size(118, 35);
            this.PGJ2_bouton.TabIndex = 13;
            this.PGJ2_bouton.Text = "4";
            this.PGJ2_bouton.UseVisualStyleBackColor = true;
            this.PGJ2_bouton.Click += new System.EventHandler(this.PGJ2_bouton_Click);
            this.PGJ2_bouton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.PGJ2_bouton_KeyDown);
            // 
            // PDJ1_bouton
            // 
            this.PDJ1_bouton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.PDJ1_bouton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PDJ1_bouton.Location = new System.Drawing.Point(170, 85);
            this.PDJ1_bouton.Name = "PDJ1_bouton";
            this.PDJ1_bouton.Size = new System.Drawing.Size(118, 35);
            this.PDJ1_bouton.TabIndex = 12;
            this.PDJ1_bouton.Text = "S";
            this.PDJ1_bouton.UseVisualStyleBackColor = true;
            this.PDJ1_bouton.Click += new System.EventHandler(this.PDJ1_bouton_Click);
            this.PDJ1_bouton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.PDJ1_bouton_KeyDown);
            // 
            // PGJ1_bouton
            // 
            this.PGJ1_bouton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.PGJ1_bouton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PGJ1_bouton.ForeColor = System.Drawing.SystemColors.ControlText;
            this.PGJ1_bouton.Location = new System.Drawing.Point(170, 20);
            this.PGJ1_bouton.Name = "PGJ1_bouton";
            this.PGJ1_bouton.Size = new System.Drawing.Size(118, 35);
            this.PGJ1_bouton.TabIndex = 11;
            this.PGJ1_bouton.Text = "A";
            this.PGJ1_bouton.UseVisualStyleBackColor = true;
            this.PGJ1_bouton.Click += new System.EventHandler(this.PGJ1_bouton_Click);
            this.PGJ1_bouton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.PGJ1_bouton_KeyDown);
            // 
            // Default_bouton
            // 
            this.Default_bouton.Location = new System.Drawing.Point(170, 325);
            this.Default_bouton.Name = "Default_bouton";
            this.Default_bouton.Size = new System.Drawing.Size(118, 35);
            this.Default_bouton.TabIndex = 10;
            this.Default_bouton.Text = "Remettre à defaut";
            this.Default_bouton.UseVisualStyleBackColor = true;
            this.Default_bouton.Click += new System.EventHandler(this.Default_bouton_Click);
            // 
            // label_Ressort
            // 
            this.label_Ressort.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.label_Ressort.Location = new System.Drawing.Point(22, 280);
            this.label_Ressort.Name = "label_Ressort";
            this.label_Ressort.Size = new System.Drawing.Size(118, 35);
            this.label_Ressort.TabIndex = 4;
            this.label_Ressort.Text = "Ressort";
            this.label_Ressort.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_PDJ2
            // 
            this.label_PDJ2.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.label_PDJ2.Location = new System.Drawing.Point(22, 215);
            this.label_PDJ2.Name = "label_PDJ2";
            this.label_PDJ2.Size = new System.Drawing.Size(118, 35);
            this.label_PDJ2.TabIndex = 3;
            this.label_PDJ2.Text = "Palette droite  du joueur 2";
            this.label_PDJ2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_PGJ2
            // 
            this.label_PGJ2.BackColor = System.Drawing.Color.Transparent;
            this.label_PGJ2.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.label_PGJ2.Location = new System.Drawing.Point(22, 150);
            this.label_PGJ2.Name = "label_PGJ2";
            this.label_PGJ2.Size = new System.Drawing.Size(118, 35);
            this.label_PGJ2.TabIndex = 2;
            this.label_PGJ2.Text = "Palette gauche du joueur 2";
            this.label_PGJ2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_PDJ1
            // 
            this.label_PDJ1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.label_PDJ1.Location = new System.Drawing.Point(22, 85);
            this.label_PDJ1.Name = "label_PDJ1";
            this.label_PDJ1.Size = new System.Drawing.Size(118, 35);
            this.label_PDJ1.TabIndex = 1;
            this.label_PDJ1.Text = "Palette droite  du joueur 1";
            this.label_PDJ1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Label_PGJ1
            // 
            this.Label_PGJ1.BackColor = System.Drawing.Color.Transparent;
            this.Label_PGJ1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.Label_PGJ1.Location = new System.Drawing.Point(22, 20);
            this.Label_PGJ1.Name = "Label_PGJ1";
            this.Label_PGJ1.Size = new System.Drawing.Size(118, 35);
            this.Label_PGJ1.TabIndex = 0;
            this.Label_PGJ1.Text = "Palette gauche du joueur 1";
            this.Label_PGJ1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.GBOX_acceleration);
            this.tabPage2.Controls.Add(this.GBox_ModeBilles);
            this.tabPage2.Controls.Add(this.comboBoxBilles);
            this.tabPage2.Controls.Add(this.labelDoublesBilles);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(302, 406);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Configuration de jeu";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // comboBoxBilles
            // 
            this.comboBoxBilles.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxBilles.FormattingEnabled = true;
            this.comboBoxBilles.Items.AddRange(new object[] {
            "3",
            "5",
            "7"});
            this.comboBoxBilles.Location = new System.Drawing.Point(215, 14);
            this.comboBoxBilles.Name = "comboBoxBilles";
            this.comboBoxBilles.Size = new System.Drawing.Size(81, 21);
            this.comboBoxBilles.TabIndex = 3;
            // 
            // labelDoublesBilles
            // 
            this.labelDoublesBilles.AutoSize = true;
            this.labelDoublesBilles.Location = new System.Drawing.Point(6, 22);
            this.labelDoublesBilles.Name = "labelDoublesBilles";
            this.labelDoublesBilles.Size = new System.Drawing.Size(143, 13);
            this.labelDoublesBilles.TabIndex = 0;
            this.labelDoublesBilles.Text = "Nombre de billes disponibles:";
            // 
            // tabPage3
            // 
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(302, 406);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Débogage";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // OK_bouton
            // 
            this.OK_bouton.Location = new System.Drawing.Point(17, 451);
            this.OK_bouton.Name = "OK_bouton";
            this.OK_bouton.Size = new System.Drawing.Size(140, 46);
            this.OK_bouton.TabIndex = 1;
            this.OK_bouton.Text = "Accepter";
            this.OK_bouton.UseVisualStyleBackColor = true;
            this.OK_bouton.Click += new System.EventHandler(this.OK_bouton_Click);
            // 
            // Annuler_bouton
            // 
            this.Annuler_bouton.Location = new System.Drawing.Point(179, 451);
            this.Annuler_bouton.Name = "Annuler_bouton";
            this.Annuler_bouton.Size = new System.Drawing.Size(140, 46);
            this.Annuler_bouton.TabIndex = 2;
            this.Annuler_bouton.Text = "Annuler";
            this.Annuler_bouton.UseVisualStyleBackColor = true;
            this.Annuler_bouton.Click += new System.EventHandler(this.Annuler_bouton_Click);
            // 
            // MDB_OK
            // 
            this.MDB_OK.AutoSize = true;
            this.MDB_OK.Location = new System.Drawing.Point(9, 32);
            this.MDB_OK.Name = "MDB_OK";
            this.MDB_OK.Size = new System.Drawing.Size(58, 17);
            this.MDB_OK.TabIndex = 4;
            this.MDB_OK.TabStop = true;
            this.MDB_OK.Text = "Activer";
            this.MDB_OK.UseVisualStyleBackColor = true;
            // 
            // MDB_Cancel
            // 
            this.MDB_Cancel.AutoSize = true;
            this.MDB_Cancel.Checked = true;
            this.MDB_Cancel.Location = new System.Drawing.Point(9, 55);
            this.MDB_Cancel.Name = "MDB_Cancel";
            this.MDB_Cancel.Size = new System.Drawing.Size(76, 17);
            this.MDB_Cancel.TabIndex = 5;
            this.MDB_Cancel.TabStop = true;
            this.MDB_Cancel.Text = "Desactiver";
            this.MDB_Cancel.UseVisualStyleBackColor = true;
            // 
            // GBox_ModeBilles
            // 
            this.GBox_ModeBilles.Controls.Add(this.MDB_Cancel);
            this.GBox_ModeBilles.Controls.Add(this.MDB_OK);
            this.GBox_ModeBilles.Location = new System.Drawing.Point(9, 53);
            this.GBox_ModeBilles.Name = "GBox_ModeBilles";
            this.GBox_ModeBilles.Size = new System.Drawing.Size(287, 92);
            this.GBox_ModeBilles.TabIndex = 6;
            this.GBox_ModeBilles.TabStop = false;
            this.GBox_ModeBilles.Text = "Mode Double Billes";
            // 
            // GBOX_acceleration
            // 
            this.GBOX_acceleration.Controls.Add(this.FRS_Cancel);
            this.GBOX_acceleration.Controls.Add(this.FRS_OK);
            this.GBOX_acceleration.Location = new System.Drawing.Point(9, 161);
            this.GBOX_acceleration.Name = "GBOX_acceleration";
            this.GBOX_acceleration.Size = new System.Drawing.Size(287, 98);
            this.GBOX_acceleration.TabIndex = 7;
            this.GBOX_acceleration.TabStop = false;
            this.GBOX_acceleration.Text = "Force de rebond supplémentaire";
            // 
            // FRS_Cancel
            // 
            this.FRS_Cancel.AutoSize = true;
            this.FRS_Cancel.Location = new System.Drawing.Point(9, 52);
            this.FRS_Cancel.Name = "FRS_Cancel";
            this.FRS_Cancel.Size = new System.Drawing.Size(76, 17);
            this.FRS_Cancel.TabIndex = 7;
            this.FRS_Cancel.TabStop = true;
            this.FRS_Cancel.Text = "Desactiver";
            this.FRS_Cancel.UseVisualStyleBackColor = true;
            // 
            // FRS_OK
            // 
            this.FRS_OK.AutoSize = true;
            this.FRS_OK.Checked = true;
            this.FRS_OK.Location = new System.Drawing.Point(9, 29);
            this.FRS_OK.Name = "FRS_OK";
            this.FRS_OK.Size = new System.Drawing.Size(58, 17);
            this.FRS_OK.TabIndex = 6;
            this.FRS_OK.TabStop = true;
            this.FRS_OK.Text = "Activer";
            this.FRS_OK.UseVisualStyleBackColor = true;
            // 
            // Configuration
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(335, 509);
            this.Controls.Add(this.Annuler_bouton);
            this.Controls.Add(this.OK_bouton);
            this.Controls.Add(this.tabProprietes);
            this.Icon = global::InterfaceGraphique.Properties.Resources.Pinball;
            this.Name = "Configuration";
            this.Text = "Configuration";
            this.tabProprietes.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.GBox_ModeBilles.ResumeLayout(false);
            this.GBox_ModeBilles.PerformLayout();
            this.GBOX_acceleration.ResumeLayout(false);
            this.GBOX_acceleration.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabProprietes;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Button OK_bouton;
        private System.Windows.Forms.Button Annuler_bouton;
        private System.Windows.Forms.Label label_Ressort;
        private System.Windows.Forms.Label label_PDJ2;
        private System.Windows.Forms.Label label_PGJ2;
        private System.Windows.Forms.Label label_PDJ1;
        private System.Windows.Forms.Label Label_PGJ1;
        private System.Windows.Forms.Button Default_bouton;
        private System.Windows.Forms.Button Ressort_bouton;
        private System.Windows.Forms.Button PDJ2_bouton;
        private System.Windows.Forms.Button PGJ2_bouton;
        private System.Windows.Forms.Button PDJ1_bouton;
        private System.Windows.Forms.Button PGJ1_bouton;
        private System.Windows.Forms.Label label_Rebind;
        private System.Windows.Forms.ComboBox comboBoxBilles;
        private System.Windows.Forms.Label labelDoublesBilles;
        private System.Windows.Forms.GroupBox GBOX_acceleration;
        private System.Windows.Forms.RadioButton FRS_Cancel;
        private System.Windows.Forms.RadioButton FRS_OK;
        private System.Windows.Forms.GroupBox GBox_ModeBilles;
        private System.Windows.Forms.RadioButton MDB_Cancel;
        private System.Windows.Forms.RadioButton MDB_OK;
    }
}