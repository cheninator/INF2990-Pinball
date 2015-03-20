//////////////////////////////////////////////////////////////////////////////
/// @file PartieRapide.cs
/// @author Ballers
/// @date 2015-03-03
/// @version 1.0 
///
/// @ingroup Fenetres
//////////////////////////////////////////////////////////////////////////////

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
    ///////////////////////////////////////////////////////////////////////////
    /// @class PartieRapide
    /// @brief Classe d'interface du mode Partie Rapide.
    ///
    /// @author Ballers
    /// @date 2015-03-03
    /// 
    /// @ingroup Fenetres
    ///////////////////////////////////////////////////////////////////////////
    public partial class PartieRapide : Form
    {
        string[] filePaths; ///< Path des fichiers de zones
        string fileNames;
        List<string> zonesCampagne; ///< Liste des zones de la campagne.
        int sortColumn = -1; ///< Pour le tri des colonnes.
        int diff;
        int typeJoueur;
        StringBuilder pathMap;
        //StringBuilder mapList;
        public ModeJeu modeJeu;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public PartieRapide()
        /// @brief Constructeur de la fenetre de Partie Rapide..
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Cancel_Click(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on clique sur le bouton Annuler.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ZonesDisponibles_SelectedIndexChanged(object sender, EventArgs e)
        /// @brief Affichage de l'image lorsqu'on clique sur un zone disponible dans la liste.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ZonesDisponibles_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (ZonesDisponibles.SelectedIndices.Count <= 0) return;
            int index = ZonesDisponibles.SelectedIndices[0];
            if (index >= 0)
            {
                fileNames = ZonesDisponibles.Items[index].Text;
                screenShot.SizeMode = PictureBoxSizeMode.StretchImage;
                if (File.Exists(Application.StartupPath + @"\zones\" + fileNames + ".jpg"))
                {
                    screenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\" + fileNames + ".jpg");
                }
                else
                {
                    screenShot.Image = Properties.Resources.SaintTrinity;
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ZonesDisponibles_ColumnClick(object sender, EventArgs e)
        /// @brief Appel des fonctions de tri lorsquon clique sur un colonne 
        ///        de la ListBox.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ZonesDisponibles_ColumnWidthChanging(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on change la taille des colonnes dans les
        ///        zones disponibles.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ZonesDisponibles_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            e.Cancel = true;
            e.NewWidth = ZonesDisponibles.Columns[e.ColumnIndex].Width;
           
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_OK_Click(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on clique sur le bouton OK.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_OK_Click(object sender, EventArgs e)
        {
            if (ZonesDisponibles.SelectedItems.Count != 0)
            {
                zonesCampagne.Insert(0, Application.StartupPath + @"\zones\" + ZonesDisponibles.SelectedItems[0].Text + ".xml");
                if (RB_Solo.Checked)
                {
                    typeJoueur = 1;
                }
                else if (RB_Multi.Checked)
                {
                    typeJoueur = 2;
                }
                else if (RB_AI.Checked)
                {
                    typeJoueur = 3;
                }
                this.Hide();
                ((MainMenu)this.Owner).LancerModeJeu(zonesCampagne, typeJoueur);
               
            }
            else
            {
                MessageBox.Show("Selectionnez une zone pour commencer la partie", "ERREUR DE LANCEMENT",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_KeyPress(Object o, KeyPressEventArgs e)
        /// @brief Gestion des touches lorsqu'une touche est enfoncee.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_KeyPress(object sender, KeyPressEventArgs e)
        {
            if( e.KeyChar ==13)
                bouton_OK.PerformClick();
            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_KeyUp(Object o, KeyPressEventArgs e)
        /// @brief Permet de fermer la form lorsqu'on fait CTRL + Q.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Q && ModifierKeys == Keys.Control)
            {
                this.Close();
            }
        }
    }
}
