using System;

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
            this.pause_resume = new System.Windows.Forms.CheckBox();
            this.Always_Button = new System.Windows.Forms.CheckBox();
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
            this.richTextBox1.HideSelection = false;
            this.richTextBox1.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.richTextBox1.Location = new System.Drawing.Point(12, 12);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.ShortcutsEnabled = false;
            this.richTextBox1.Size = new System.Drawing.Size(687, 393);
            this.richTextBox1.TabIndex = 6;
            this.richTextBox1.Text = "";
            this.richTextBox1.TextChanged += new System.EventHandler(this.richTextBox1_TextChanged);
            // 
            // pause_resume
            // 
            this.pause_resume.Appearance = System.Windows.Forms.Appearance.Button;
            this.pause_resume.AutoSize = true;
            this.pause_resume.Location = new System.Drawing.Point(253, 412);
            this.pause_resume.Name = "pause_resume";
            this.pause_resume.Size = new System.Drawing.Size(91, 23);
            this.pause_resume.TabIndex = 8;
            this.pause_resume.Text = "Pause/Resume";
            this.pause_resume.UseVisualStyleBackColor = true;
            this.pause_resume.CheckedChanged += new System.EventHandler(this.pause_resume_CheckedChanged);
            // 
            // Always_Button
            // 
            this.Always_Button.AutoSize = true;
            this.Always_Button.Location = new System.Drawing.Point(379, 416);
            this.Always_Button.Name = "Always_Button";
            this.Always_Button.Size = new System.Drawing.Size(89, 17);
            this.Always_Button.TabIndex = 9;
            this.Always_Button.Text = "Show Always";
            this.Always_Button.UseVisualStyleBackColor = true;
            // 
            // CustomConsole
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(711, 446);
            this.Controls.Add(this.Always_Button);
            this.Controls.Add(this.pause_resume);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.CloseConsole);
            this.Controls.Add(this.ClearConsole);
            this.Controls.Add(this.DeleteHistory);
            this.Controls.Add(this.ShowHistory);
            this.Name = "CustomConsole";
            this.Text = "CustomConsole";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Close_External);
            this.Shown += new System.EventHandler(this.CustomConsole_Shown);
            this.VisibleChanged += new System.EventHandler(this.CustomConsole_VisibleChanged);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button ShowHistory;
        private System.Windows.Forms.Button DeleteHistory;
        private System.Windows.Forms.Button ClearConsole;
        private System.Windows.Forms.Button CloseConsole;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.CheckBox pause_resume;
        private System.Windows.Forms.CheckBox Always_Button;
    }
}