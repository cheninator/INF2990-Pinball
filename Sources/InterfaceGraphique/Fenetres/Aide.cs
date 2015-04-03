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
                            Console.WriteLine("SELECTION");
                            labelDescOutil.Text = "Description: Description de l'outil Selection TODO";
                            pictureBoxOutils.Image = Properties.Resources.SelectionSimple;
                            break;
                        }
                    case 1:
                        {
                            Console.WriteLine("DEPLACEMENT");
                            labelDescOutil.Text = "Description: Description de l'outil Deplacement TODO";
                            pictureBoxOutils.Image = Properties.Resources.Deplacement;

                            break;
                        }
                    case 2:
                        {
                            Console.WriteLine("ROTATION");
                            labelDescOutil.Text = "Description: Description de l'outil Rotation TODO";
                            pictureBoxOutils.Image = Properties.Resources.RotationSimple;
                            break;
                        }
                    case 3:
                        {
                            Console.WriteLine("DUPLICATION");
                            labelDescOutil.Text = "Description: Description de l'outil Duplication TODO";
                            pictureBoxOutils.Image = Properties.Resources.Duplication;
                            break;
                        }
                    case 4:
                        {
                            Console.WriteLine("MISE A ECHELLE");
                            labelDescOutil.Text = "Description: Description de l'outil Mise a Echelle TODO";
                            pictureBoxOutils.Image = Properties.Resources.Scale;
                            break;
                        }
                }

            }
        }
    }
}
