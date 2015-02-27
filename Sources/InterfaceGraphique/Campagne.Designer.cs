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
            this.listBox = new System.Windows.Forms.ListBox();
            this.ZonesChoisis = new System.Windows.Forms.ListView();
            this.colonneZone = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.colonneDiff = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SuspendLayout();
            // 
            // listBox
            // 
            this.listBox.Font = new System.Drawing.Font("Old English Text MT", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.listBox.FormattingEnabled = true;
            this.listBox.ItemHeight = 26;
            this.listBox.Location = new System.Drawing.Point(28, 26);
            this.listBox.Name = "listBox";
            this.listBox.Size = new System.Drawing.Size(215, 368);
            this.listBox.TabIndex = 0;
            this.listBox.SelectedValueChanged += new System.EventHandler(this.listBox_SelectedValueChanged);
            // 
            // ZonesChoisis
            // 
            this.ZonesChoisis.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.colonneZone,
            this.colonneDiff});
            this.ZonesChoisis.Location = new System.Drawing.Point(304, 26);
            this.ZonesChoisis.Name = "ZonesChoisis";
            this.ZonesChoisis.Size = new System.Drawing.Size(253, 368);
            this.ZonesChoisis.TabIndex = 1;
            this.ZonesChoisis.UseCompatibleStateImageBehavior = false;
            this.ZonesChoisis.View = System.Windows.Forms.View.Details;
            this.ZonesChoisis.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.ZonesChoisis_ColumnClick);
            // 
            // colonneZone
            // 
            this.colonneZone.Text = "Zones de jeu";
            this.colonneZone.Width = 116;
            // 
            // colonneDiff
            // 
            this.colonneDiff.Text = "Difficultés";
            this.colonneDiff.Width = 125;
            // 
            // Campagne
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(674, 466);
            this.Controls.Add(this.ZonesChoisis);
            this.Controls.Add(this.listBox);
            this.Icon = global::InterfaceGraphique.Properties.Resources.Pinball;
            this.Name = "Campagne";
            this.Text = "Campagne";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox listBox;
        private System.Windows.Forms.ListView ZonesChoisis;
        private System.Windows.Forms.ColumnHeader colonneZone;
        private System.Windows.Forms.ColumnHeader colonneDiff;


    }
}