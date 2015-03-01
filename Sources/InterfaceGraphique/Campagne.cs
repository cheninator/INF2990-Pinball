using System;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Collections;


namespace InterfaceGraphique
{
    public partial class Campagne : Form
    {
        string[] filePaths;
        string fileNames;
        int sortColumn = -1;
        StringBuilder pathMap;
        StringBuilder mapList;
        public Campagne()
        {
            InitializeComponent();
            sortColumnDescend(1);
            mapList = new StringBuilder();
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
            screenShot.SizeMode = PictureBoxSizeMode.StretchImage;
            screenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\" + listBox.SelectedItem.ToString()+".jpg");
        }

        private void ZonesChoisis_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            /*
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
                
                ZonesChoisis.Sorting = SortOrder.Descending;
                ZonesChoisis.Sort();
                this.ZonesChoisis.ListViewItemSorter = new ListViewItemComparer(e.Column,
                                                          ZonesChoisis.Sorting);
                */
           
        }


        private void sortColumnDescend(int column)
        {
            ZonesChoisis.Sorting = SortOrder.Descending;
            ZonesChoisis.Sort();
            this.ZonesChoisis.ListViewItemSorter = new ListViewItemComparer(column,
                                                         ZonesChoisis.Sorting);
        }

        private void sortColumnAscend(int column)
        {
            ZonesChoisis.Sorting = SortOrder.Ascending;
            ZonesChoisis.Sort();
            this.ZonesChoisis.ListViewItemSorter = new ListViewItemComparer(column,
                                                         ZonesChoisis.Sorting);
        }

        private void InitialiseConfigs()
        {
            // TO DO : mapList = le fichier que yonni me passe
        }

        private void bouton_ADD_Click(object sender, EventArgs e)
        {
            Console.WriteLine(listBox.SelectedItem);
            pathMap = new StringBuilder(Application.StartupPath + @"\zones\" + listBox.SelectedItem.ToString() + ".xml");
            int diff = FonctionsNatives.obtenirDifficulte(pathMap, pathMap.Capacity);
            var item1 = new ListViewItem(new[] { listBox.SelectedItem.ToString(), diff.ToString() });

            ZonesChoisis.Items.Add(item1);
        }

        private void bouton_REMOVE_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem eachItem in ZonesChoisis.SelectedItems)
            {
                ZonesChoisis.Items.Remove(eachItem);
            }
        }

        private void bouton_REMOVEALL_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem eachItem in ZonesChoisis.Items)
            {
                ZonesChoisis.Items.Remove(eachItem);
            }
        }

        private void bouton_Annuler_Click(object sender, EventArgs e)
        {
            // Literallement rien de fait ici
            
            this.Close();
        }

        private void bouton_OK_Click(object sender, EventArgs e)
        {
            if (ZonesChoisis.Items.Count < 2)
                MessageBox.Show("Vous ne pouvez pas lancer une campagne avec moins de 2 zones!", "ERREUR DE LANCEMENT",
                       MessageBoxButtons.OK, MessageBoxIcon.Error);
            else
            {
                // TO DO
               
                if (RB_Solo.Checked)
                    mapList = new StringBuilder("UN ");
                else
                    if (RB_Multi.Checked)
                        mapList = new StringBuilder("DEUX ");
                    else
                        if (RB_AI.Checked)
                            mapList = new StringBuilder("AI ");
                
             foreach (ListViewItem eachItem in ZonesChoisis.Items)
                {
                    mapList.Append(eachItem.Text+" ");
                        
                }
             mapList.Length--;
             
             // TO DO : PASSER mapList 
             FonctionsNatives.creerFichierConfigCampagne(mapList);
             Console.WriteLine("LANCEMENT DE CA5MPAGNE");
            }
        }
    }

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
            int returnVal = -1;
            returnVal = String.Compare(((ListViewItem)x).SubItems[col].Text,
                                    ((ListViewItem)y).SubItems[col].Text);
            if (order == SortOrder.Descending)
                returnVal *= -1;
            return returnVal;
        }
    }
}
