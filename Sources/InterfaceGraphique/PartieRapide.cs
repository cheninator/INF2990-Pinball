using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class PartieRapide : Form
    {
        string[] filePaths;
        string fileNames;
        List<string> zonesCampagne;
        int sortColumn = -1;
        int diff;
        StringBuilder pathMap;
        //StringBuilder mapList;
        public ModeJeu modeJeu;
        public PartieRapide()
        {
            InitializeComponent();
          //  mapList = new StringBuilder();
            filePaths = Directory.GetFiles(Application.StartupPath + @"\zones", "*.xml");
            zonesCampagne = new List<string>();

            foreach (string s in filePaths)
            {
                pathMap = new StringBuilder(s);
                diff = FonctionsNatives.obtenirDifficulte(pathMap, pathMap.Capacity);
                // fileNames = Path.GetFileName(s);
                fileNames = Path.GetFileNameWithoutExtension(s);
                //fileNames = fileNames.Remove(fileNames.Length - 4);
                var item1 = new ListViewItem(new[] { fileNames, diff.ToString() });
                ZonesDisponibles.Items.Add(item1);

            }
        }

        private void bouton_Cancel_Click(object sender, EventArgs e)
        {
            this.Close();
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

            ZonesDisponibles.Sort();
            this.ZonesDisponibles.ListViewItemSorter = new ListViewItemComparer(e.Column,
                                                      ZonesDisponibles.Sorting);
              
        }

        private void ZonesDisponibles_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            e.Cancel = true;
            e.NewWidth = ZonesDisponibles.Columns[e.ColumnIndex].Width;
        }

        private void bouton_OK_Click(object sender, EventArgs e)
        {
            zonesCampagne.Insert(0, Application.StartupPath + @"\zones\" + ZonesDisponibles.SelectedItems[0].Text + ".xml");
            //Console.WriteLine(Application.StartupPath + @"\zones\" + ZonesDisponibles.SelectedItems[0].Text + ".xml");
            this.Hide();
            modeJeu = new ModeJeu(zonesCampagne);
            modeJeu.ShowDialog();
            this.Close();
        }
    }
}
