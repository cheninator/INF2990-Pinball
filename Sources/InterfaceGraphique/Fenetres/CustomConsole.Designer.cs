namespace InterfaceGraphique
{
    partial class CustomConsole
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
            this.ShowHistory = new System.Windows.Forms.Button();
            this.DeleteHistory = new System.Windows.Forms.Button();
            this.ClearConsole = new System.Windows.Forms.Button();
            this.CloseConsole = new System.Windows.Forms.Button();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // ShowHistory
            // 
            this.ShowHistory.Location = new System.Drawing.Point(12, 411);
            this.ShowHistory.Name = "ShowHistory";
            this.ShowHistory.Size = new System.Drawing.Size(103, 23);
            this.ShowHistory.TabIndex = 1;
            this.ShowHistory.Text = "Show History";
            this.ShowHistory.UseVisualStyleBackColor = true;
            this.ShowHistory.Click += new System.EventHandler(this.ShowHistory_Click);
            // 
            // DeleteHistory
            // 
            this.DeleteHistory.Location = new System.Drawing.Point(121, 412);
            this.DeleteHistory.Name = "DeleteHistory";
            this.DeleteHistory.Size = new System.Drawing.Size(91, 23);
            this.DeleteHistory.TabIndex = 2;
            this.DeleteHistory.Text = "Delete History";
            this.DeleteHistory.UseVisualStyleBackColor = true;
            this.DeleteHistory.Click += new System.EventHandler(this.DeleteHistory_Click);
            // 
            // ClearConsole
            // 
            this.ClearConsole.Location = new System.Drawing.Point(543, 412);
            this.ClearConsole.Name = "ClearConsole";
            this.ClearConsole.Size = new System.Drawing.Size(75, 23);
            this.ClearConsole.TabIndex = 3;
            this.ClearConsole.Text = "Clear";
            this.ClearConsole.UseVisualStyleBackColor = true;
            this.ClearConsole.Click += new System.EventHandler(this.Clear_Click);
            // 
            // CloseConsole
            // 
            this.CloseConsole.Location = new System.Drawing.Point(624, 412);
            this.CloseConsole.Name = "CloseConsole";
            this.CloseConsole.Size = new System.Drawing.Size(75, 23);
            this.CloseConsole.TabIndex = 5;
            this.CloseConsole.Text = "Close";
            this.CloseConsole.UseVisualStyleBackColor = true;
            this.CloseConsole.Click += new System.EventHandler(this.Close_Click);
            // 
            // richTextBox1
            // 
            this.richTextBox1.BackColor = System.Drawing.Color.Black;
            this.richTextBox1.ForeColor = System.Drawing.Color.Lime;
            this.richTextBox1.Location = new System.Drawing.Point(12, 12);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(687, 393);
            this.richTextBox1.TabIndex = 6;
            this.richTextBox1.Text = "";
            // 
            // CustomConsole
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(711, 446);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.CloseConsole);
            this.Controls.Add(this.ClearConsole);
            this.Controls.Add(this.DeleteHistory);
            this.Controls.Add(this.ShowHistory);
            this.Name = "CustomConsole";
            this.Text = "CustomConsole";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Close_External);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button ShowHistory;
        private System.Windows.Forms.Button DeleteHistory;
        private System.Windows.Forms.Button ClearConsole;
        private System.Windows.Forms.Button CloseConsole;
        private System.Windows.Forms.RichTextBox richTextBox1;
    }
}