using System;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Collections.Generic;


namespace InterfaceGraphique
{
    public partial class Campagne : Form
    {
        string[] filePaths;
        string[] configurations;
        List<string> zonesCampagne;
        string fileNames;
        int sortColumn = -1;
        int diff;
        StringBuilder pathMap;
        StringBuilder mapList;
        private MainMenu parent;
        public ModeJeu modeJeu;

        public Campagne()
        {
            InitializeComponent();
            sortColumnAscend(1);
            mapList = new StringBuilder();
            zonesCampagne = new List<string>();
            filePaths = Directory.GetFiles(Application.StartupPath + @"\zones", "*.xml");
            
            foreach(string s in filePaths)
            {
                pathMap = new StringBuilder(s);
                diff = FonctionsNatives.obtenirDifficulte(pathMap, pathMap.Capacity);
               // fileNames = Path.GetFileName(s);
                fileNames = Path.GetFileNameWithoutExtension(s);
                //fileNames = fileNames.Remove(fileNames.Length - 4);
                var item1 = new ListViewItem(new[] { fileNames, diff.ToString() });
                ZonesDisponibles.Items.Add(item1);
 
            }
            pathMap = new StringBuilder("");
            InitialiserConfigurations();


        }

        private void InitialiserConfigurations()
        {
            string tempConfig= FonctionsNatives.obtenirDerniereCampagne();
            configurations = tempConfig.Split(new char[] {' '},StringSplitOptions.RemoveEmptyEntries);
            if (configurations[0] == "UN")
            {
                RB_Solo.Checked = true;
            }
            else if (configurations[0] == "DEUX")
            {
                RB_Multi.Checked = true;
            }
            else if (configurations[0] == "AI")
            {
                RB_AI.Checked = true;
            }
            for (int i = 1; i < configurations.Length; i++ )
            {
                if (File.Exists(Application.StartupPath + @"\zones\" + configurations[i] + ".xml"))
                {
                    pathMap = new StringBuilder(Application.StartupPath + @"\zones\" + configurations[i] + ".xml");
                    int diff = FonctionsNatives.obtenirDifficulte(pathMap, pathMap.Capacity);
                    var item1 = new ListViewItem(new[] { configurations[i], diff.ToString() });
                    ZonesChoisis.Items.Add(item1);
                }
                else
                {
                    pathMap = new StringBuilder(Application.StartupPath + @"\zones\default.xml");
                    int diff = FonctionsNatives.obtenirDifficulte(pathMap, pathMap.Capacity);
                    var item1 = new ListViewItem(new[] { "default", diff.ToString() });
                    ZonesChoisis.Items.Add(item1);
                }
            }
        }

        private void listBox_SelectedValueChanged(object sender, EventArgs e)
        {
            screenShot.SizeMode = PictureBoxSizeMode.StretchImage;
            screenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\" + ZonesDisponibles.SelectedItems.ToString()+".jpg");
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

     

        private void bouton_ADD_Click(object sender, EventArgs e)
        {
            //Console.WriteLine(ZonesDisponibles.SelectedItems);
            pathMap = new StringBuilder(Application.StartupPath + @"\zones\" + fileNames + ".xml");
            int diff = FonctionsNatives.obtenirDifficulte(pathMap, pathMap.Capacity);
            var item1 = new ListViewItem(new[] { fileNames, diff.ToString() });

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
            this.Close();
        }

        private void bouton_OK_Click(object sender, EventArgs e)
        {
            if (ZonesChoisis.Items.Count < 2)
                MessageBox.Show("Vous ne pouvez pas lancer une campagne avec moins de 2 zones!", "ERREUR DE LANCEMENT",
                       MessageBoxButtons.OK, MessageBoxIcon.Error);
            else
            {
                if (RB_Solo.Checked)
                    mapList = new StringBuilder("UN ");
                else
                    if (RB_Multi.Checked)
                        mapList = new StringBuilder("DEUX ");
                    else
                        if (RB_AI.Checked)
                            mapList = new StringBuilder("AI ");
                int i = 0;
             foreach (ListViewItem eachItem in ZonesChoisis.Items)
             {
                 mapList.Append(eachItem.Text+" ");
                 zonesCampagne.Insert(i, Application.StartupPath + @"\zones\" + eachItem.Text + ".xml");
                 i++;                
                        
             }
             mapList.Length--;
             // TO DO : PASSER mapList 

             FonctionsNatives.creerFichierCampagne(mapList, mapList.Capacity);
             Console.WriteLine("LANCEMENT DE CAMPAGNE");
           

             ZoneInfo zi = new ZoneInfo(ZonesChoisis.Items[0].Text, ZonesChoisis.Items[0].SubItems[1].Text);
             this.Hide();
             zi.ShowDialog();
             //this.Show();
            // modeJeu = new ModeJeu(zonesCampagne);
            // modeJeu.ShowDialog();
             ((MainMenu)this.Owner).LancerModeJeu(zonesCampagne);
           //  this.Show();
           //  this.Close();
              
             
            }
        }

        private void ZonesDisponibles_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (ZonesDisponibles.SelectedIndices.Count <= 0) return;
            int index = ZonesDisponibles.SelectedIndices[0];
            if (index >= 0)
            {
                fileNames = ZonesDisponibles.Items[index].Text;
                screenShot.SizeMode = PictureBoxSizeMode.StretchImage;
                screenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\" + fileNames + ".jpg");

            }
            
        }

        private void ZonesDisponibles_ColumnClick(object sender, ColumnClickEventArgs e)
        {
           
               if (e.Column != sortColumn)
               {
                   sortColumn = e.Column;
                   ZonesDisponibles.Sorting = SortOrder.Ascending;
               }
               else
               {
                   if (ZonesDisponibles.Sorting == SortOrder.Ascending)
                       ZonesDisponibles.Sorting = SortOrder.Descending;
                   else
                       ZonesDisponibles.Sorting = SortOrder.Ascending;
               }
                
               //ZonesDisponibles.Sorting = SortOrder.Descending;
               ZonesDisponibles.Sort();
               this.ZonesDisponibles.ListViewItemSorter = new ListViewItemComparer(e.Column,
                                                         ZonesDisponibles.Sorting);
              
        }

        private void ZonesChoisis_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            e.Cancel = true;
            e.NewWidth = ZonesChoisis.Columns[e.ColumnIndex].Width;
        }

        private void ZonesDisponibles_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            e.Cancel = true;
            e.NewWidth = ZonesDisponibles.Columns[e.ColumnIndex].Width;
        }


    }

    class ListViewItemComparer : IComparer
    {
        private int col;
        private int temp;        
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
       
            if(Int32.TryParse( (((ListViewItem)x).SubItems[col].Text), out temp ))
            {
                returnVal = Convert.ToInt32(((ListViewItem)x).SubItems[col].Text).CompareTo(Convert.ToInt32(((ListViewItem)y).SubItems[col].Text));
            }
            else
            {
                returnVal = String.Compare(((ListViewItem)x).SubItems[col].Text,
                                         ((ListViewItem)y).SubItems[col].Text);
            }
            if (order == SortOrder.Descending)
            returnVal *= -1;
            return returnVal;
           
           
        }
    }
}
