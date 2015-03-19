//////////////////////////////////////////////////////////////////////////////
/// @file Campagne.cs
/// @author Ballers
/// @date 2015-03-03
/// @version 1.0 
///
/// @ingroup Fenetres
//////////////////////////////////////////////////////////////////////////////

using System;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Collections.Generic;


namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Campagne
    /// @brief Classe qui gere la logique d'interface et l'affichage du mode 
    ///        campagne.
    ///
    /// @author Ballers
    /// @date 2015-03-03
    /// 
    /// @ingroup Fenetres
    ///////////////////////////////////////////////////////////////////////////
    public partial class Campagne : Form
    {
        string[] filePaths; ///< Path des fichiers de zones.
        string[] configurations; ///< Configurations de jeu.
        List<string> zonesCampagne;
        string fileNames;
        int sortColumn = -1; ///< Pour le tri des colonnes.
        int diff;
        int typeJoueur; ///< Solo, multijoueur, joueur virtuel.
        StringBuilder pathMap;
        StringBuilder mapList;
        public ModeJeu modeJeu;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Campagne()
        /// @brief Constructeur de la fenetre de demarrage.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public InitialiserConfigurations()
        /// @brief Initialisation des configurations par defaut de la partie.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void listBox_SelectedValueChanged(object sender, EventArgs e)
        /// @brief Affichage de l'image lorsqu'on clique sur un zone dans la liste.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void listBox_SelectedValueChanged(object sender, EventArgs e)
        {
            screenShot.SizeMode = PictureBoxSizeMode.StretchImage;
            if (File.Exists(Application.StartupPath + @"\zones\" + ZonesDisponibles.SelectedItems.ToString() + ".jpg"))
            {
                screenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\" + ZonesDisponibles.SelectedItems.ToString() + ".jpg");
            }
            else
                screenShot.Image = Properties.Resources.SaintTrinity;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void sortColumnDescend(int column)
        /// @brief Tri descendant des zones de jeu choisies.
        /// @param[in] column: numero de la colonne a trier.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void sortColumnDescend(int column)
        {
            ZonesChoisis.Sorting = SortOrder.Descending;
            ZonesChoisis.Sort();
            this.ZonesChoisis.ListViewItemSorter = new ListViewItemComparer(column,
                                                         ZonesChoisis.Sorting);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void sortColumnAscend(int column)
        /// @brief Tri ascendant des zones de jeu choisies. 
        /// @param[in] column: numero de la colonne a trier.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void sortColumnAscend(int column)
        {
            ZonesChoisis.Sorting = SortOrder.Ascending;
            ZonesChoisis.Sort();
            this.ZonesChoisis.ListViewItemSorter = new ListViewItemComparer(column,
                                                         ZonesChoisis.Sorting);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_ADD_Click(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on clique sur le bouton Ajouter.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_ADD_Click(object sender, EventArgs e)
        {
            pathMap = new StringBuilder(Application.StartupPath + @"\zones\" + fileNames + ".xml");
            int diff = FonctionsNatives.obtenirDifficulte(pathMap, pathMap.Capacity);
            var item1 = new ListViewItem(new[] { fileNames, diff.ToString() });

            ZonesChoisis.Items.Add(item1);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_REMOVE_Click(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on clique sur le bouton Enlever.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_REMOVE_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem eachItem in ZonesChoisis.SelectedItems)
            {
                ZonesChoisis.Items.Remove(eachItem);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_REMOVEALL_Click(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on clique sur le bouton Vider.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_REMOVEALL_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem eachItem in ZonesChoisis.Items)
            {
                ZonesChoisis.Items.Remove(eachItem);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Annuler_Click(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on clique sur le bouton Annuler.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Annuler_Click(object sender, EventArgs e)
        {
            this.Close();
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
            if (ZonesChoisis.Items.Count < 2)
                MessageBox.Show("Vous ne pouvez pas lancer une campagne avec moins de 2 zones!", "ERREUR DE LANCEMENT",
                       MessageBoxButtons.OK, MessageBoxIcon.Error);
            else
            {
                if (RB_Solo.Checked)
                {
                    mapList = new StringBuilder("UN ");
                    typeJoueur = 1;
                }
                else
                    if (RB_Multi.Checked)
                    {
                        mapList = new StringBuilder("DEUX ");
                        typeJoueur = 2;
                    }
                    else
                        if (RB_AI.Checked)
                        {
                            mapList = new StringBuilder("AI ");
                            typeJoueur = 3;
                        }
                int i = 0;
             foreach (ListViewItem eachItem in ZonesChoisis.Items)
             {
                 mapList.Append(eachItem.Text+" ");
                 zonesCampagne.Insert(i, Application.StartupPath + @"\zones\" + eachItem.Text + ".xml");
                 i++;                
                        
             }
             mapList.Length--;
             FonctionsNatives.creerFichierCampagne(mapList, mapList.Capacity);

             ZoneInfo zi = new ZoneInfo(ZonesChoisis.Items[0].Text, ZonesChoisis.Items[0].SubItems[1].Text,false);
             this.Hide();
             zi.ShowDialog();
             ((MainMenu)this.Owner).LancerModeJeu(zonesCampagne,typeJoueur);

                //this.Show();
                // modeJeu = new ModeJeu(zonesCampagne);
                // modeJeu.ShowDialog();
                //  this.Show();
                //  this.Close();
              
             
            }
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
                    screenShot.Image = Properties.Resources.SaintTrinity;

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
                
               //ZonesDisponibles.Sorting = SortOrder.Descending;
               ZonesDisponibles.Sort();
               this.ZonesDisponibles.ListViewItemSorter = new ListViewItemComparer(e.Column,
                                                         ZonesDisponibles.Sorting);
              
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ZonesChoisis_ColumnWidthChanging(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on change la taille des colonnes dans les
        ///        zones choisies.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ZonesChoisis_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            e.Cancel = true;
            e.NewWidth = ZonesChoisis.Columns[e.ColumnIndex].Width;
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
        /// @fn private void ZonesDisponibles_SelectedIndexChanged(object sender, EventArgs e)
        /// @brief Affichage de l'image lorsqu'on clique sur un zone choisie dans la liste.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ZonesChoisis_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (ZonesChoisis.SelectedIndices.Count <= 0) return;
            int index = ZonesChoisis.SelectedIndices[0];
            if (index >= 0)
            {
                fileNames = ZonesChoisis.Items[index].Text;
                screenShot.SizeMode = PictureBoxSizeMode.StretchImage;
                if (File.Exists(Application.StartupPath + @"\zones\" + fileNames + ".jpg"))
                {
                    screenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\" + fileNames + ".jpg");
                }
                else
                    screenShot.Image = Properties.Resources.SaintTrinity;

            }
        }


    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class Campagne
    /// @brief Classe pour la comparaison de valeurs dans un ListView.
    ///
    /// @author Ballers
    /// @date 2015-2-27
    /// 
    /// @ingroup Fenetres
    ///////////////////////////////////////////////////////////////////////////
    class ListViewItemComparer : IComparer
    {
        private int col; ///< Numero de la colonne.
        private int temp; ///<        
        private SortOrder order;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ListViewItemComparer()
        /// @brief Constructeur par defaut.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public ListViewItemComparer()
        {
            col = 0;
            order = SortOrder.Ascending;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ListViewItemComparer(int column, SortOrder order)
        /// @brief Constructeur par parametre.
        /// @param[in] column : Numero de colonne.
        /// @param[in] order : Methode de tri.
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public ListViewItemComparer(int column, SortOrder order)
        {
            col = column;
            this.order = order;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public int Compare(object x, object y)
        /// @brief TODO: (Niko) Expliquer ca.
        /// @param[in] x : Premier objet.
        /// @param[in] y : Deuxieme objet.
        /// @return Valeur de comparaison obtenue.
        ///
        ////////////////////////////////////////////////////////////////////////
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
