using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace InterfaceGraphique
{
    public partial class Campagne : Form
    {
        string[] filePaths;
        string fileNames;
        public Campagne()
        {
            InitializeComponent();
            filePaths = Directory.GetFiles(Application.StartupPath + @"\zones", "*.xml");
            int i = 0;
            foreach(string s in filePaths)
            {
                fileNames = Path.GetFileName(s);
                fileNames = fileNames.Remove(fileNames.Length - 4);
                listBox.Items.Add(fileNames);
               
            }
           // foreach (string s in fileNames) Console.WriteLine(s);
        }

        private void listBox_SelectedValueChanged(object sender, EventArgs e)
        {
            Console.WriteLine(listBox.SelectedItem);
           
        }
    }
}
