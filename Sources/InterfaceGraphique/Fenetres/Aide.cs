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
                                                  "La séléction simple fait apparaitre le menu des Propriétés Spatiales à gauche qui permet de modifier les propriétés de l'objet sélectionné."+
                                                  "\nPour désélectionner, il suffit de simplement cliquer sur un espace vide de la table"+
                                                  " Si le bouton CTRL est appuyé pendant la séléction, l'état de sélection de l'objet est inversé.";
                            pictureBoxOutils.Image = Properties.Resources.SelectionSimple;
                            break;
                        }
                    case 1:
                        {
                            labelDescOutil.Text = "La Sélection Multiple se fait à l'aide d'un réctangle élastique."+
                                                  " Pour créer le réctangle élastique, il suffit d'enfoncer le bouton gauche de la souris et deplacer la souris"+
                                                  " Tout objet sous le rectangle élastique sera sélectionné. Si le bouton CTRL est appuyé pendant la séléction, l'état de sélection est inversé.";
                            pictureBoxOutils.Image = Properties.Resources.SelectionSimple;
                            break;
                        }
                    case 2:
                        {
                            labelDescOutil.Text = "Le déplacement d'un ou plusieurs objets sélectionnés se fait en appuyant sur le bouton gauche de la souris et, tout en gardant le bouton enfoncé, se déplaçant. Les objets sélectionnés suiveront la souris.";
                            pictureBoxOutils.Image = Properties.Resources.Deplacement;

                            break;
                        }
                    case 3:
                        {
                            labelDescOutil.Text = "La rotation d'un ou plusieurs objets sélectionnés se fait en choisissant l'outil Rotation"+
                                                  "à l'aide du bouton Rotation ou le raccourci R et en déplaçant la souris en gardant le bouton gauche enfoncé."+
                                                  "Un déplacement vers le haut fait tourner les objets dans le sens horaire."+
                                                  " Un déplacement vers le bas fait tourner les objets dans le sens anti-horaire.";
                            pictureBoxOutils.Image = Properties.Resources.RotationSimple;
                            break;
                        }
                    case 4:
                        {
                            labelDescOutil.Text = "La rotation d'un ou plusieurs objets sélectionnés se fait en choisissant l'outil Duplication" +
                                                  "à l'aide du bouton Duplication ou le raccourci C." +
                                                  " les objets dupliqués sont créés et suivent la souris. Un déplacement de la souris fait bouger les objets copies. " +
                                                  " Le clic du bouton gauche de la souris confirme la duplication et place définitivement les objets." +
                                                  " Le bouton Échapper annule la duplication et enlève les objets dupliqués.";
                            pictureBoxOutils.Image = Properties.Resources.Duplication;
                            break;
                        }
                    case 5:
                        {
                            labelDescOutil.Text = "La mise à échelle d'un ou plusieurs objets sélectionnés se fait en choisissant l'outil Mise à Échelle" +
                                                  "à l'aide du bouton Mise à Échelle ou le raccourci E et en déplaçant la souris en gardant le bouton gauche enfoncé." +
                                                  "Un déplacement vers le haut fait agrandir les objets." +
                                                  " Un déplacement vers le bas fait retrécir les objets.";
                            pictureBoxOutils.Image = Properties.Resources.Scale;
                            break;
                        }

                    case 6:
                        {
                            labelDescOutil.Text = "La suppression d'un ou plusieurs objets sélectionnés se fait à l'aide du bouton Suppression ou le raccourci Suppr."+
                                                  "La suppression fait disparaitre les objets sélectionnés de la zone de jeu";
                            pictureBoxOutils.Image = Properties.Resources.Scale;
                            break;
                        }
                    case 7:
                        {
                            labelDescOutil.Text = "La création se fait un objet à la fois."+
                                                  "Pour créer un objet, il suffit de choisir l'objet voulu dans le paneau de création à droite."+
                                                  "Un clic dans la table féra apparaitre l'objet sur la zone de jeu."+
                                                  "Un objet ne peut pas être crée en dehor de la table."+
                                                  "Pour plus d'information, voir l'onglet Objets sur les différents objets.";
                            pictureBoxOutils.Image = Properties.Resources.Scale;
                            break;
                        }
                    case 8:
                        {
                            labelDescOutil.Text = "L'effet de loupe se fait à l'aide du bouton Zoom ou le raccourci Z et un rectangle élastique"+
                                                  " Pour créer le réctangle élastique, il suffit d'enfoncer le bouton gauche de la souris et deplacer la souris" +
                                                  " La surface sous le rectangle élastique sera agrandie pour remplir l'écran. Si le bouton ALT est appuyé pendant la création du réctangle, il y aura un effet  de loupe négatif.";
                            pictureBoxOutils.Image = Properties.Resources.Scale;
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
                            labelDescObj.Text = "Il y a des palettes gauches et droite pour chaque joueur." +
                                " Les palettes pivottent avec un angle maximal de 60 degrées" +
                                " Les palettes du joueur 2 sont contrôlées par le joueur 1 en mode Solo et par l'ordinateur en mode IA. ";
                            break;
                        }
                    case 1:
                        {
                            labelDescObj.Text = "Lorsqu'une bille frappe le butoir, les points appropriées sont accordés au joeur et le butoir s'illuminera." +
                                               " Si l'option de force de rebond supplémentaire est activée, la vitesse de la balle augmentera après la collision.";
                            break;

                        }
                    case 2:
                        {
                            labelDescObj.Text = "Ce butoir a une forme circulaire. Lorsqu'une bille frappe le butoir, les points appropriées sont accordés au joeur et le butoir s'illuminera." +
                                                " Si l'option de force de rebond supplémentaire est activée, la vitesse de la balle augmentera après la collision.";
                            break;

                        }
                    case 3:
                        {
                            labelDescObj.Text = "La cible est un obstancle rectangulaire qui, lorsque frappé par la bille, disparait et donne des points au joueur." +
                                                " La collision retire la cible de la zone de jeu de façon permanente jusqu'une réinitialisation de la zone.";
                            break;

                        }
                    case 4:
                        {
                            labelDescObj.Text = "Les portails sont des objets toujours liés en pairs. La création des portails se fait un à la suite de l'autre " +
                                               " Lorsque la bille entre dans un des portail, elle sort par l'autre." +
                                               " Les portails sont entourés par un champ d'attraction dont la force est inversement proportionnelle à la distance avec la bille.";
                            break;

                        }
                    case 5:
                        {
                            labelDescObj.Text = "Les murs sont des obstacles rectangulaires dont la longueur est determinée durant la création." +
                                                "La création du mur se fait avec 2 étapes. Un premier clique indque le début du mur et celui-ci suit le pointeur de la souris. Le deuxième clic détermine la fin du mur.";
                            break;

                        }
                    case 6:
                        {
                            labelDescObj.Text = "La porte permet de laisser passer la balle d'un seule côté seulement. Si la balle frappe le côté opposée, elle rebondit comme sur un mur.";
                            break;

                        }
                    case 7:
                        {
                            labelDescObj.Text = "Le ressort permet de propulser la balle pour lui donner une vitesse initiale."+
                                                " La force donnée à la balle est proportionnelle à la compression du ressort. Il peut avoir plusieurs ressorts sur une zone et ils sont tous contrôlés par le même bouton.";
                            break;

                        }
                    case 8:
                        {
                            labelDescObj.Text = "Le générateur de bille est la source des billes qui arrivent sur la table." +
                                                " Une bille est toujours générée par un générateur aléatoire si plusieurs sont présents et sa taille est proportionelle à celle du générateur." +
                                                " Le générateur disparait après avoir généré la balle et ne cause pas de collisions pendant le jeu.";
                            break;

                        }
                    case 9:
                        {
                            labelDescObj.Text = "Le trou est un objet circulaire qui fait disparaitre une balle si celle-ci passe au-dessus d'un trou.";
                            break;

                        }
                }
            }
        }
    }
}
