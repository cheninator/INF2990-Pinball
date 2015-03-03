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
            this.menu_ReturnItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Camera_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Ortho_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Orbitale_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.panel_GL.SuspendLayout();
            this.menuStrip.SuspendLayout();
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
            this.panel_GL.Size = new System.Drawing.Size(284, 261);
            this.panel_GL.TabIndex = 4;
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menu_ReturnItem,
            this.Camera_MenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(284, 24);
            this.menuStrip.TabIndex = 0;
            this.menuStrip.Text = "menuStrip1";
            this.menuStrip.Visible = false;
            // 
            // menu_ReturnItem
            // 
            this.menu_ReturnItem.Name = "menu_ReturnItem";
            this.menu_ReturnItem.Size = new System.Drawing.Size(99, 20);
            this.menu_ReturnItem.Text = "Menu Principal";
            this.menu_ReturnItem.Click += new System.EventHandler(this.menu_ReturnItem_Click);
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
            // PartieRapide
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.panel_GL);
            this.Icon = global::InterfaceGraphique.Properties.Resources.Pinball;
            this.MainMenuStrip = this.menuStrip;
            this.Name = "PartieRapide";
            this.Text = "PartieRapide";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.PartieRapide_FormClosing);
            this.Load += new System.EventHandler(this.PartieRapide_Load);
            this.SizeChanged += new System.EventHandler(this.PartieRapide_redimensionner);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.PartieRapide_KeyDown);
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.PartieRapide_KeyPress);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.PartieRapide_KeyUp);
            this.panel_GL.ResumeLayout(false);
            this.panel_GL.PerformLayout();
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel_GL;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem menu_ReturnItem;
        private System.Windows.Forms.ToolStripMenuItem Camera_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Ortho_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Orbitale_MenuItem;
    }
}