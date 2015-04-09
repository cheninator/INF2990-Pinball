//////////////////////////////////////////////////////////////////////////////
/// @file Aide.cs
/// @author Ballers
/// @date 2015-01-27
/// @version 1.0 
///
/// @ingroup Fenetres
//////////////////////////////////////////////////////////////////////////////

/**
*	@defgroup Fenetres Fenetres
*	@ingroup InterfaceGraphique
*   Ce module contient les différentes fenêtres de l'application.
*/

using System;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Aide
    /// @brief Fenetre d'aide de l'editeur.
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    public partial class Aide : Form
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Aide()
        /// @brief Constructeur de la fenetre.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public Aide()
        {
            InitializeComponent();
            if (!Program.helpMenu)
            {
                checkBoxHelp.Checked = true;
            }
            else
            {
                checkBoxHelp.Checked = false;
            }
            InitializeShortcuts();
        }

        private void InitializeShortcuts()
        {
            string shortcutTemp;
            var item1 = new ListViewItem(new[] { "Sélection", " S " });
            listViewShortcut.Items.Insert(0, item1);
            listViewShortcut.Items[0].Group = listViewShortcut.Groups[0];

            item1 = new ListViewItem(new[] { "Rotation", " R " });
            listViewShortcut.Items.Insert(1, item1);
            listViewShortcut.Items[1].Group = listViewShortcut.Groups[0];

            item1 = new ListViewItem(new[] { "Mise à Échelle", " E " });
            listViewShortcut.Items.Insert(2, item1);
            listViewShortcut.Items[2].Group = listViewShortcut.Groups[0];

            item1 = new ListViewItem(new[] { "Duplication", " C " });
            listViewShortcut.Items.Insert(3, item1);
            listViewShortcut.Items[3].Group = listViewShortcut.Groups[0];

            item1 = new ListViewItem(new[] { "Suppression", " Suppr. " });
            listViewShortcut.Items.Insert(4, item1);
            listViewShortcut.Items[4].Group = listViewShortcut.Groups[0];

            item1 = new ListViewItem(new[] { "Zoom Élastique", " Z " });
            listViewShortcut.Items.Insert(5, item1);
            listViewShortcut.Items[5].Group = listViewShortcut.Groups[0];

            item1 = new ListViewItem(new[] { "Paneau Création", " P " });
            listViewShortcut.Items.Insert(6, item1);
            listViewShortcut.Items[6].Group = listViewShortcut.Groups[0];

            item1 = new ListViewItem(new[] { "Vue Orthographique", " 1 " });
            listViewShortcut.Items.Insert(7, item1);
            listViewShortcut.Items[7].Group = listViewShortcut.Groups[1];

            item1 = new ListViewItem(new[] { "Vue Orbile", " 2 " });
            listViewShortcut.Items.Insert(8, item1);
            listViewShortcut.Items[8].Group = listViewShortcut.Groups[1];

            item1 = new ListViewItem(new[] { "Déplacement Clavier", " Flèches " });
            listViewShortcut.Items.Insert(9, item1);
            listViewShortcut.Items[9].Group = listViewShortcut.Groups[1];

            item1 = new ListViewItem(new[] { "Déplacement Souris", " Bouton Droit " });
            listViewShortcut.Items.Insert(10, item1);
            listViewShortcut.Items[10].Group = listViewShortcut.Groups[1];

            item1 = new ListViewItem(new[] { "Zoom Clavier", " + / -" });
            listViewShortcut.Items.Insert(11, item1);
            listViewShortcut.Items[11].Group = listViewShortcut.Groups[1];

            item1 = new ListViewItem(new[] { "Zoom Souris", " Roulette " });
            listViewShortcut.Items.Insert(12, item1);
            listViewShortcut.Items[12].Group = listViewShortcut.Groups[1];

            item1 = new ListViewItem(new[] { "Mode Test", " T " });
            listViewShortcut.Items.Insert(13, item1);
            listViewShortcut.Items[13].Group = listViewShortcut.Groups[2];

            item1 = new ListViewItem(new[] { "Pause", " Échapp. " });
            listViewShortcut.Items.Insert(14, item1);
            listViewShortcut.Items[14].Group = listViewShortcut.Groups[2];

            item1 = new ListViewItem(new[] { "Recommencer", " Retour Arrière " });
            listViewShortcut.Items.Insert(15, item1);
            listViewShortcut.Items[15].Group = listViewShortcut.Groups[2];

            item1 = new ListViewItem(new[] { "Affichage de débogage ", " B " });
            listViewShortcut.Items.Insert(16, item1);
            listViewShortcut.Items[16].Group = listViewShortcut.Groups[2];


            shortcutTemp = char.ConvertFromUtf32(FonctionsNatives.obtenirTouchePGJ1()).ToString();
            if (shortcutTemp == " ")
            {
                shortcutTemp = "Espace";
            }
            item1 = new ListViewItem(new[] { "Palettes Gauches", " " + shortcutTemp });
            listViewShortcut.Items.Insert(17, item1);
            listViewShortcut.Items[17].Group = listViewShortcut.Groups[2];

            shortcutTemp = char.ConvertFromUtf32(FonctionsNatives.obtenirTouchePDJ1()).ToString();
            if (shortcutTemp == " ")
            {
                shortcutTemp = "Espace";
            }
            item1 = new ListViewItem(new[] { "Palettes Droites", " " + shortcutTemp });
            listViewShortcut.Items.Insert(18, item1);
            listViewShortcut.Items[18].Group = listViewShortcut.Groups[2];

            shortcutTemp = char.ConvertFromUtf32(FonctionsNatives.obtenirToucheRessort()).ToString();
            if (shortcutTemp == " ")
            {
                shortcutTemp = "Espace";
            }
            item1 = new ListViewItem(new[] { "Ressorts ", " " + shortcutTemp });
            listViewShortcut.Items.Insert(19, item1);
            listViewShortcut.Items[19].Group = listViewShortcut.Groups[2];     

            item1 = new ListViewItem(new[] { "Nouvelle Zone ", " CTRL + N "  });
            listViewShortcut.Items.Insert(20, item1);
            listViewShortcut.Items[20].Group = listViewShortcut.Groups[3];

            item1 = new ListViewItem(new[] { "Ouvrir une Zone ", " CTRL + O " });
            listViewShortcut.Items.Insert(21, item1);
            listViewShortcut.Items[21].Group = listViewShortcut.Groups[3];

            item1 = new ListViewItem(new[] { "Enregistrer ", " CTRL + S " });
            listViewShortcut.Items.Insert(22, item1);
            listViewShortcut.Items[22].Group = listViewShortcut.Groups[3];

            item1 = new ListViewItem(new[] { "Enregistrer Sous ", " CTRL + SHIFT + S " });
            listViewShortcut.Items.Insert(23, item1);
            listViewShortcut.Items[23].Group = listViewShortcut.Groups[3];

            item1 = new ListViewItem(new[] { "Menu Principal ", " CTRL + Q " });
            listViewShortcut.Items.Insert(24, item1);
            listViewShortcut.Items[24].Group = listViewShortcut.Groups[3];

            item1 = new ListViewItem(new[] { "Aide ", " F1 " });
            listViewShortcut.Items.Insert(25, item1);
            listViewShortcut.Items[25].Group = listViewShortcut.Groups[3];

            item1 = new ListViewItem(new[] { "Lumière Ambiante ", " J " });
            listViewShortcut.Items.Insert(26, item1);
            listViewShortcut.Items[26].Group = listViewShortcut.Groups[2];

            item1 = new ListViewItem(new[] { "Lumière Directionnelle ", " K " });
            listViewShortcut.Items.Insert(27, item1);
            listViewShortcut.Items[27].Group = listViewShortcut.Groups[2];

            item1 = new ListViewItem(new[] { "Lumière Spot ", " L " });
            listViewShortcut.Items.Insert(28, item1);
            listViewShortcut.Items[28].Group = listViewShortcut.Groups[2];

            item1 = new ListViewItem(new[] { "Déplacement", " D / Bouton Milieu " });
            listViewShortcut.Items.Insert(2, item1);
            listViewShortcut.Items[2].Group = listViewShortcut.Groups[0];

            item1 = new ListViewItem(new[] { "Annuler", " CTRL + Z " });
            listViewShortcut.Items.Insert(7, item1);
            listViewShortcut.Items[7].Group = listViewShortcut.Groups[0];

            item1 = new ListViewItem(new[] { "Rétablir", " CTRL + Y " });
            listViewShortcut.Items.Insert(8, item1);
            listViewShortcut.Items[8].Group = listViewShortcut.Groups[0];

        }

        private void listView1_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            if (listView1.SelectedIndices.Count <= 0) return;
            int index = listView1.SelectedIndices[0];
            if (index >= 0)
            {
                switch (index)
                {
                    case 0:
                        {
                            labelDescOutil.Text = "La Sélection Simple se fait avec un seul clic sur un objet."+
                                                  " La Séléction Simple fait apparaître le menu des Propriétés Spatiales à gauche qui permet de modifier les propriétés de l'objet sélectionné."+
                                                  "\nPour désélectionner, il suffit de simplement cliquer sur un espace vide de la table"+
                                                  " Si le bouton CTRL est appuyé pendant la séléction, l'état de sélection de l'objet est inversé.";
                            pictureBoxOutils.Image = Properties.Resources.SelectionSimple;
                            break;
                        }
                    case 1:
                        {
                            labelDescOutil.Text = "La Sélection Multiple se fait à l'aide d'un réctangle élastique."+
                                                  " Pour créer le réctangle élastique, il suffit d'enfoncer le bouton gauche de la souris et déplacer la souris"+
                                                  " Tout objet sous le rectangle élastique sera sélectionné. Si le bouton CTRL est appuyé pendant la séléction, l'état de sélection est inversé.";
                            pictureBoxOutils.Image = Properties.Resources.SelectionMultiple;
                            break;
                        }
                    case 2:
                        {
                            labelDescOutil.Text = "Le déplacement des objets sélectionnés se fait en appuyant sur le bouton de milieu de la souris et, tout en gardant le bouton enfoncé, se déplaçant. Les objets sélectionnés suiveront la souris."+
                                                  " Si vous n'avez pas de bouton milieu( laptop par exemple ), vous pouvez utiliser l'outil Déplacement et utiliser le bouton gauche de la souris.";
                            pictureBoxOutils.Image = Properties.Resources.Deplacement;

                            break;
                        }
                    case 3:
                        {
                            labelDescOutil.Text = "La rotation des objets sélectionnés se fait en choisissant l'outil Rotation"+
                                                  " à l'aide du bouton Rotation ou le raccourci R puis en déplaçant la souris en gardant le bouton gauche enfoncé."+
                                                  " Un déplacement vers le haut fait tourner les objets dans le sens horaire."+
                                                  " Un déplacement vers le bas fait tourner les objets dans le sens anti-horaire.";
                            pictureBoxOutils.Image = Properties.Resources.RotationSimple;
                            break;
                        }
                    case 4:
                        {
                            labelDescOutil.Text = "La duplication des objets sélectionnés se fait en choisissant l'outil Duplication" +
                                                  " à l'aide du bouton Duplication ou le raccourci C." +
                                                  " Les objets dupliqués sont créés et suivent la souris. Un déplacement de la souris fait bouger les objets copiés. " +
                                                  " Le clic du bouton gauche de la souris confirme la duplication et place définitivement les objets." +
                                                  " Le bouton Échapper annule la duplication et enlève les objets dupliqués.";
                            pictureBoxOutils.Image = Properties.Resources.Duplication;
                            break;
                        }
                    case 5:
                        {
                            labelDescOutil.Text = "La mise à échelle des objets sélectionnés se fait en choisissant l'outil Mise à Échelle" +
                                                  " à l'aide du bouton Mise à Échelle ou le raccourci E et en déplaçant la souris en gardant le bouton gauche enfoncé." +
                                                  " Un déplacement vers le haut fait agrandir les objets." +
                                                  " Un déplacement vers le bas fait retrécir les objets.";
                            pictureBoxOutils.Image = Properties.Resources.Scale;
                            break;
                        }

                    case 6:
                        {
                            labelDescOutil.Text = "La suppression des objets sélectionnés se fait à l'aide du bouton Suppression ou le raccourci Suppr."+
                                                  "La suppression fait disparaitre les objets sélectionnés de la zone de jeu";
                            pictureBoxOutils.Image = Properties.Resources.Suppression;
                            break;
                        }
                    case 7:
                        {
                            labelDescOutil.Text = "La création se fait un objet à la fois."+
                                                  "Pour créer un objet, il suffit de choisir l'objet voulu dans le paneau de création à droite."+
                                                  "Un clic dans la table fera apparaitre l'objet sur la zone de jeu."+
                                                  "Un objet ne peut pas être créé en dehors de la table."+
                                                  "Pour plus d'information, voir l'onglet Objets sur les différents objets.";
                            pictureBoxOutils.Image = Properties.Resources.Creation;
                            break;
                        }
                    case 8:
                        {
                            labelDescOutil.Text = "L'effet de loupe se fait à l'aide du bouton Zoom ou le raccourci Z et un rectangle élastique"+
                                                  " Pour créer le réctangle élastique, il suffit d'enfoncer le bouton gauche de la souris et déplacer la souris" +
                                                  " La surface sous le rectangle élastique sera agrandie pour remplir l'écran. Si le bouton ALT est appuyé pendant la création du réctangle, il y aura un effet  de loupe inverse.";
                            pictureBoxOutils.Image = Properties.Resources.ZoomElastique;
                            break;
                        }
                }

            }
        }

        private void listView2_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            e.Cancel = true;
            e.NewWidth = listView2.Columns[e.ColumnIndex].Width;
        }

        private void listView1_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            e.Cancel = true;
            e.NewWidth = listView1.Columns[e.ColumnIndex].Width;
        }

        private void listView2_SelectedIndexChanged(object sender, EventArgs e)
        {
             if (listView2.SelectedIndices.Count <= 0) return;
            int index = listView2.SelectedIndices[0];
            if (index >= 0)
            {
                switch (index)
                {
                    case 0:
                        {
                            labelDescObj.Text = "Il y a des palettes gauches et droites pour chaque joueur." +
                                " Les palettes pivotent avec un angle maximal de 60 degrées" +
                                " Les palettes du joueur 2 sont contrôlées par le joueur 1 en mode Solo ou par l'ordinateur en mode Intelligence Artificielle. ";
                            pictureBoxObjets.Image = Properties.Resources.Palettes;
                            break;
                        }
                    case 1:
                        {
                            labelDescObj.Text = "Lorsqu'une bille frappe le butoir, les points appropriés sont accordés au joueur et le butoir s'illuminera." +
                                               " Si l'option de force de rebond supplémentaire est activée, la vitesse de la bille augmentera après la collision.";
                            pictureBoxObjets.Image = Properties.Resources.ButoirTriangulaire;
                            break;

                        }
                    case 2:
                        {
                            labelDescObj.Text = "Ce butoir a une forme circulaire. Lorsqu'une bille frappe le butoir, les points appropriés sont accordés au joueur et le butoir s'illuminera." +
                                                " Si l'option de force de rebond supplémentaire est activée, la vitesse de la bille augmentera après la collision.";
                            pictureBoxObjets.Image = Properties.Resources.ButoirCirculaire;
                            break;

                        }
                    case 3:
                        {
                            labelDescObj.Text = "La cible est un obstacle rectangulaire qui, lorsque frappé par la bille, disparait et donne des points au joueur." +
                                                " La collision retire la cible de la zone de jeu de façon permanente.";
                            pictureBoxObjets.Image = Properties.Resources.Cible2;
                            break;

                        }
                    case 4:
                        {
                            labelDescObj.Text = "Les portails sont des objets toujours liés en pairs. La création des portails se fait une à la suite de l'autre " +
                                               " Lorsque la bille entre dans un des portail, elle sort par l'autre." +
                                               " Les portails sont entourés d'un champ d'attraction dont la force est inversement proportionnelle à la distance avec la bille.";
                            pictureBoxObjets.Image = Properties.Resources.Portals;
                            
                            break;

                        }
                    case 5:
                        {
                            labelDescObj.Text = "Les murs sont des obstacles rectangulaires dont la longueur est determinée durant la création." +
                                                "La création du mur se fait en 2 étapes. Un premier clic indique le début du mur et celui-ci suit la souris. Le deuxième clic détermine la fin du mur.";
                            pictureBoxObjets.Image = Properties.Resources.Mur1;
                           
                            break;

                        }
                    case 6:
                        {
                            labelDescObj.Text = "La porte permet de laisser passer la bille d'un seul côté seulement. Si la bille frappe le côté opposé, elle rebondit comme sur un mur.";
                            pictureBoxObjets.Image = Properties.Resources.Porte;
                            
                            break;

                        }
                    case 7:
                        {
                            labelDescObj.Text = "Le ressort permet de propulser la bille pour lui donner une vitesse initiale."+
                                                " La force donnée à la bille est proportionnelle à la compression du ressort. Il peut y avoir plusieurs ressorts sur une zone et ils sont tous contrôlés par le même bouton.";
                            pictureBoxObjets.Image = Properties.Resources.Ressort1;
                            
                            break;

                        }
                    case 8:
                        {
                            labelDescObj.Text = "Le générateur de Billes est la source des billes qui arrivent sur la table." +
                                                " Une bille est toujours générée par un générateur aléatoire si plusieurs générateurs sont présents et sa taille est proportionelle à celle du générateur." +
                                                " Le générateur disparait après avoir généré la bille et ne cause pas de collisions pendant le jeu.";
                            pictureBoxObjets.Image = Properties.Resources.Generateur1;
                           
                            break;

                        }
                    case 9:
                        {
                            labelDescObj.Text = "Le trou est un objet circulaire qui fait disparaitre une bille si celle-ci passe au-dessus d'un trou.";
                            pictureBoxObjets.Image = Properties.Resources.Trou1;
                            
                            break;


                        }
                }
            }
        }

        private void listViewShortcut_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            e.Cancel = true;
            e.NewWidth = listViewShortcut.Columns[e.ColumnIndex].Width;
        }

        private void listViewBase_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listViewBase.SelectedIndices.Count <= 0) return;
            int index = listViewBase.SelectedIndices[0];
            if (index >= 0)
            {
                switch (index)
                {
                    case 0:
                        {
                            labelBase.Text = "L'option Nouveau permet de remplacer la zone de jeu en modification par la zone de jeu par défaut."+
                                             "\nATTENTION: toute modification à la zone de jeu sera perdue si vous choisissez cette option.";
                            pictureBoxBase.Image = Properties.Resources.NewMap;
                            break;

                        }
                    case 1:
                        {
                            labelBase.Text = "L'option Ouvrir permet d'ouvrir une zone de jeu existante."+
                                             "La zone choisie remplacera la zone en cours de modification."+
                                             "\nATTENTION: toute modification à la zone de jeu sera perdue si vous ouvrez une nouvelle.";
                            pictureBoxBase.Image = Properties.Resources.Ouvrir;
                            break;
                        }
                    case 2:
                        {
                            labelBase.Text = "L'option Enregistrer permet d'enregistrer la zone de jeu en cours de modification." +
                                             " Si la zone n'a jamais été enregistrée auparavant, vous serez amené à l'enregistrer avec un nom de votre choix." +
                                             " Sinon, vos modifications seront enregistrées par-dessus le fichier déjà existant."+
                                             " Lorsque vous sauvegardez votre zone, une image sera automatiquement générée."; 
                            pictureBoxBase.Image = Properties.Resources.SaveAs;
                            break;
                        }
                    case 3:
                        {
                            labelBase.Text = "L'option Enregistrer Sous permet d'enregistrer la zone de jeu en cours de modification." +
                                             " Vous serez amené à l'enregistrer avec un nom de votre choix dans le répertoire Zones."+
                                             " Lorsque vous sauvegardez votre zone, une image sera automatiquement générée.";
                            pictureBoxBase.Image = Properties.Resources.SaveAs;
                            break;
                        }
                    case 4:
                        {
                            labelBase.Text = "L'option Propriétés permet de modifier les propriétés de la zone de jeu." +
                                             " Dans ce menu, vous pouvez spécifier le nombre de points accordé au joueur lors d'un collision,"+
                                             " le nombre de points pour gagner la zone de jeu"+
                                             " et le nombre de points pour une bille gratuite. Ces valeurs peuvent être de 0 à 10 000." +
                                             " Finalement, vous pouvez donner une côte de difficulté à votre zone qui va de 1 à 10.";
                            pictureBoxBase.Image = Properties.Resources.Proprietes;
                            break;
                        }

                    case 5:
                        {
                            labelBase.Text = "Le mode Test permet d'essayer la zone de jeu en cours de modification." +
                                             " Vous pouvez passer du mode Éditeur au mode Test à tout moment avec la touche T." +
                                             " Le mode Test se joue comme une partie normale avec 1 seul joueur et une infinité de billes";
                            pictureBoxBase.Image = Properties.Resources.Tester;
                            break;
                        }
                    case 6:
                        {
                            labelBase.Text = "L'option Menu Principal quitte le mode Éditeur et retourne au menu principal." +
                                             " Un message sera présent lorsque vous quittez pour vous assurer que vous voulez bien quitter le mdoe Éditeur." +
                                             "\nATTENTION: Si vous quittez, toute modification sur la zone de jeu non sauvegardée sera perdue.";
                            pictureBoxBase.Image = Properties.Resources.Quit;
                            break;
                        }
                    case 7:
                        {
                            labelBase.Text = "La Vue Orthographique est une vue dans laquelle la caméra est toujours perpendiculaire à la zone de jeu." +
                                            " Vous pouvez vous déplacer à l'aide des flèches ainsi qu'avec le bouton droit de la souris appuyé.";
                            pictureBoxBase.Image = Properties.Resources.NewMap;
                            break;
                        }
                    case 8:
                        {
                            labelBase.Text = "La Vue Orbite est une vue dans laquelle la caméra peut être contrôlée par l'utilisateur." +
                                            " Vous pouvez vous déplacer à l'aide des flèches ainsi qu'avec le bouton droit de la souris appuyé." +
                                            " Un déplacement gauche/droite permet de tourner la caméra. Un déplacement haut/bas permet de changer l'angle de la caméra.";
                            pictureBoxBase.Image = Properties.Resources.VueOrbite;
                            break;
                        }


                }
            }
        }

        private void checkBoxHelp_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxHelp.Checked)
            {
                Program.helpMenu = false;
            }
            else
            {
                Program.helpMenu = true;
            }
        }
    }
}
