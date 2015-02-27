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
using System.Collections;


namespace InterfaceGraphique
{
    class ListViewItemComparer : IComparer
    {
        private int col;
        private SortOrder order;
        public ListViewItemComparer()
        {
            col = 0;
            order = SortOrder.Ascending;
        }
        public ListViewItemComparer(int column, SortOrder order)
        {
            col = column;
            this.order = order;
        }
        public int Compare(object x, object y) 
    {
        int returnVal= -1;
        returnVal = String.Compare(((ListViewItem)x).SubItems[col].Text,
                                ((ListViewItem)y).SubItems[col].Text);
        if (order == SortOrder.Descending)
            returnVal *= -1;
        return returnVal;
    }
    }
    public partial class Campagne : Form
    {
        string[] filePaths;
        string fileNames;
        int sortColumn = -1;
        public Campagne()
        {
            InitializeComponent();
            filePaths = Directory.GetFiles(Application.StartupPath + @"\zones", "*.xml");
            
            foreach(string s in filePaths)
            {
                fileNames = Path.GetFileName(s);
                fileNames = fileNames.Remove(fileNames.Length - 4);
                listBox.Items.Add(fileNames);
               
            }
        }

        private void listBox_SelectedValueChanged(object sender, EventArgs e)
        {
            Console.WriteLine(listBox.SelectedItem);
            Random rnd = new Random();
            int diff = rnd.Next(1, 10);
            var item1 = new ListViewItem(new[] {listBox.SelectedItem.ToString(), diff.ToString()});

            ZonesChoisis.Items.Add(item1);
           
        }

        private void ZonesChoisis_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            if (e.Column != sortColumn)
            {
                sortColumn = e.Column;
                ZonesChoisis.Sorting = SortOrder.Ascending;
            }
            else
            {
                if (ZonesChoisis.Sorting == SortOrder.Ascending)
                    ZonesChoisis.Sorting = SortOrder.Descending;
                else
                    ZonesChoisis.Sorting = SortOrder.Ascending;
            }
            ZonesChoisis.Sort();
            this.ZonesChoisis.ListViewItemSorter = new ListViewItemComparer(e.Column,
                                                      ZonesChoisis.Sorting);
        }
    }
}
