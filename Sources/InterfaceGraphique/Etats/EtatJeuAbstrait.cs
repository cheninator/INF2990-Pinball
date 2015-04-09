//////////////////////////////////////////////////////////////////////////////
/// @file EtatJeuAbstrait.cs
/// @author Ballers
/// @date 2015-03-06
/// @version 1.0 
///
/// @ingroup Etats
//////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class ModeJeu : Form
    {
        ///////////////////////////////////////////////////////////////////////////
        /// @class EtatJeuAbstrait
        /// @brief EtatJeuAbstrait du patron State.
        ///
        /// @author The Ballers
        /// @date 2015-03-06
        /// 
        /// @ingroup Etats
        ///////////////////////////////////////////////////////////////////////////
        public partial class EtatJeuAbstrait
        {
            protected ModeJeu parent_;

            ////////////////////////////////////////////////////////////////////////
            ///
            /// @fn public virtual bool traiterRoulette(object sender, KeyEventArgs e)
            /// @brief Traiter le changement d'etat suite a une action de la roulette de souris.
            /// 
            /// @param[in] sender : Objet duquel provient un evenement.
            /// @param[in] e : evenement qui lance la fonction.
            /// 
            /// @return True ou false selon la reussite des operations.
            ///
            ////////////////////////////////////////////////////////////////////////
            public virtual bool traiterRoulette(object sender, MouseEventArgs e)
            {
                if (e.Delta > 0)
                    FonctionsNatives.zoomIn();
                else if (e.Delta < 0)
                    FonctionsNatives.zoomOut();
                parent_.setCurrentZoom(FonctionsNatives.obtenirZoomCourant());
                return false;
            }

            ////////////////////////////////////////////////////////////////////////
            ///
            /// @fn public virtual bool traiterKeyDown(object sender, KeyEventArgs e)
            /// @brief Traiter le changement d'etat suite a une action du clavier.
            /// 
            /// @param[in] sender : Objet duquel provient un evenement.
            /// @param[in] e : evenement qui lance la fonction.
            /// 
            /// @return True ou false selon la reussite des operations.
            ///
            ////////////////////////////////////////////////////////////////////////
            public virtual bool traiterKeyDown(object sender, KeyEventArgs e)
            {
                
                if (e.KeyCode == Keys.Left)
                    FonctionsNatives.translater(-10, 0);
                else if (e.KeyCode == Keys.Right)
                    FonctionsNatives.translater(10, 0);
                else if (e.KeyCode == Keys.Up)
                    FonctionsNatives.translater(0, 10);
                else if (e.KeyCode == Keys.Down)
                    FonctionsNatives.translater(0, -10);

                if ((e.KeyData == Keys.Subtract ||
                       e.KeyCode == Keys.OemMinus))
                {
                    FonctionsNatives.zoomOut();
                    parent_.currentZoom = FonctionsNatives.obtenirZoomCourant();
                }
                if ((e.KeyData == Keys.Add ||
                    e.KeyCode == Keys.Oemplus && e.Modifiers == Keys.Shift))
                {
                    FonctionsNatives.zoomIn();
                    parent_.currentZoom = FonctionsNatives.obtenirZoomCourant();
                }
                return false;
            }

            ////////////////////////////////////////////////////////////////////////
            ///
            /// @fn public virtual bool traiterKeyPress(KeyEventArgs e)
            /// @brief Traiter le changement d'etat suite a une action du clavier.
            /// 
            /// @param[in] sender : Objet duquel provient un evenement.
            /// @param[in] e : evenement qui lance la fonction.
            /// 
            /// @return True ou false selon la reussite des operations.
            ///
            ////////////////////////////////////////////////////////////////////////
            public virtual bool traiterKeyPress(object sender, KeyPressEventArgs e)
            {
                return false;
            }

            ////////////////////////////////////////////////////////////////////////
            ///
            /// @fn public virtual bool traiterKeyUp(KeyEventArgs e)
            /// @brief Traiter le changement d'etat suite a une action du clavier.
            /// 
            /// @param[in] sender : Objet duquel provient un evenement.
            /// @param[in] e : evenement qui lance la fonction.
            /// 
            /// @return True ou false selon la reussite des operations.
            ///
            ////////////////////////////////////////////////////////////////////////
            public virtual bool traiterKeyUp(object sender, KeyEventArgs e)
            {
                return false;
            }

            ////////////////////////////////////////////////////////////////////////
            ///
            /// @fn public void toggleDebugOutput()
            /// @brief Bloque ou debloque l'affichage global.
            /// @return Aucune.
            ///
            ////////////////////////////////////////////////////////////////////////
            public void toggleDebugOutput()
            {
                if (FonctionsNatives.obtenirAffichageGlobal() == 0)
                {
                    FonctionsNatives.WriteLine("Affichage bloque. On debloque");
                    FonctionsNatives.bloquerAffichageGlobal(1);
                    Program.myCustomConsole.Show();
                    if (Program.mMenu.modeJeuMain != null)
                    {
                        Program.myCustomConsole.Show();
                        Program.mMenu.modeJeuMain.Focus();
                    }
                }
                else
                {
                    FonctionsNatives.WriteLine("Affichage permis. On bloque");
                    FonctionsNatives.bloquerAffichageGlobal(0);
                    Program.myCustomConsole.Hide();
                }
            }

            public virtual bool traiterMouseDown(object sender, MouseEventArgs e)
            {
                return false;
            }

            public virtual bool traiterMouseUp(object sender, MouseEventArgs e)
            {
                return false;
            }

            public virtual bool traiterMouseMove(object sender, MouseEventArgs e)
            {
                return false;
            }

            ////////////////////////////////////////////////////////////////////////
            ///
            /// @fn public void resetConfig()
            /// @brief Reset les config du parent appelant.
            /// @return Aucune.
            ///
            ////////////////////////////////////////////////////////////////////////
            public void resetConfig()
            {
                parent_.resetConfig();
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatJeuPause
    /// @brief EtatJeuPause du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-03-06
    /// 
    /// @ingroup Etats
    ///////////////////////////////////////////////////////////////////////////
    class EtatJeuPause : InterfaceGraphique.ModeJeu.EtatJeuAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatJeuPause(ModeJeu modeJeu)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] modeJeu : Mode de jeu associe a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatJeuPause(ModeJeu modeJeu)
            : base(modeJeu)
        {

            parent_.setVisibilityMenuStrip(true);
            FonctionsNatives.modePause(true);
            parent_.setPeutAnimer(false);
           

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterKeyPress(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterKeyPress(object sender, KeyPressEventArgs e)
        {
            bool treated = false;
            if (e.KeyChar == (char)27)
            {
                parent_.resumeGame();
                treated = true;
            }
            if (Char.ToLower(e.KeyChar) == 'b')
            {
                toggleDebugOutput();
                treated = true;
            }
            return treated;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatJeuJouer
    /// @brief EtatJeuJouer du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-03-06
    /// 
    /// @ingroup Etats
    ///////////////////////////////////////////////////////////////////////////
    class EtatJeuJouer : InterfaceGraphique.ModeJeu.EtatJeuAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatJeuJouer(ModeJeu modeJeu)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] modeJeu : Mode de jeu associe a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatJeuJouer(ModeJeu modeJeu)
            : base(modeJeu)
        {
            parent_.setVisibilityMenuStrip(false);
            FonctionsNatives.modePause(false);
            parent_.setPeutAnimer(true);
           

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterKeyDown(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterKeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyValue == parent_.getTouches().PGJ1)
            {
                FonctionsNatives.activerPalettesGJ1();
            }

             if (e.KeyValue == parent_.getTouches().PGJ2)
            {
                FonctionsNatives.activerPalettesGJ2();
            }
             if (e.KeyValue == parent_.getTouches().PDJ1)
            {
                FonctionsNatives.activerPalettesDJ1();
            }
             if (e.KeyValue == parent_.getTouches().PDJ2)
            {
                FonctionsNatives.activerPalettesDJ2();
            }
            else if (e.KeyValue == parent_.getTouches().Ressort)
            {
                FonctionsNatives.compresserRessort();
            }
            if (e.KeyCode == Keys.Left)
                FonctionsNatives.translater(-10, 0);
            else if (e.KeyCode == Keys.Right)
                FonctionsNatives.translater(10, 0);
            else if (e.KeyCode == Keys.Up)
                FonctionsNatives.translater(0, 10);
            else if (e.KeyCode == Keys.Down)
                FonctionsNatives.translater(0, -10);




            if ((e.KeyData == Keys.Subtract ||
                   e.KeyCode == Keys.OemMinus))
            {
                FonctionsNatives.zoomOut();
                parent_.setCurrentZoom(FonctionsNatives.obtenirZoomCourant());
            }
            else if ((e.KeyData == Keys.Add ||
                e.KeyCode == Keys.Oemplus && e.Modifiers == Keys.Shift))
            {
                FonctionsNatives.zoomIn();
                parent_.setCurrentZoom(FonctionsNatives.obtenirZoomCourant());
            }


            if (e.KeyData == Keys.D1)
            {
                FonctionsNatives.utiliserCameraOrbite(false);
            }
            else if (e.KeyData == Keys.D2)
            {
                FonctionsNatives.utiliserCameraOrbite(true);
            }

            return true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterKeyUp(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterKeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyValue == parent_.getTouches().PGJ1)
            {
                FonctionsNatives.desactiverPalettesGJ1();
            }
            if (e.KeyValue == parent_.getTouches().PDJ1)
            {
                FonctionsNatives.desactiverPalettesDJ1();
            }
             if (e.KeyValue == parent_.getTouches().PGJ2)
            {
                FonctionsNatives.desactiverPalettesGJ2();
            }
             if (e.KeyValue == parent_.getTouches().PDJ2)
            {
                FonctionsNatives.desactiverPalettesDJ2();
            }
             if (e.KeyValue == parent_.getTouches().Ressort)
            {
                FonctionsNatives.relacherRessort();
            }


            return true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterKeyPress(KeyEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action du clavier.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterKeyPress(object sender, KeyPressEventArgs e)
        {
            if (Char.ToLower(e.KeyChar) == 'b')

            {
                toggleDebugOutput();
            }

            else if (Char.ToLower(e.KeyChar) == 'j')
            {
                //Console.WriteLine("LUMIERE AMBIANTE");
                parent_.toggleAmbiantLight();
                FonctionsNatives.spotLight(0, parent_.getAmbiantLight());
            }
            else if (Char.ToLower(e.KeyChar) == 'k')
            {
                //Console.WriteLine("LUMIERE DIRECTE");
                parent_.toggleDirectLight();
                FonctionsNatives.spotLight(1, parent_.getDirectLight());
            }
            else if (Char.ToLower(e.KeyChar) == 'l')
            {
                //Console.WriteLine("LUMIERE SPOTS");
                parent_.toggleSpotLight();
                FonctionsNatives.spotLight(2, parent_.getSpotLight());
            }

            else if (Char.ToLower(e.KeyChar) == 'h' && Program.playerName.ToUpper() =="ADMIN")
            {
                parent_.AfficherInformations();
            }
           
            else if (e.KeyChar == (char)8)
                {
                    // RELOAD DE LA MAP
                    parent_.RecommencerPartie();
                    if (Program.mMenu.modeJeuMain != null) 
                    {
                        Program.myCustomConsole.Show();
                        Program.mMenu.modeJeuMain.Focus();
                    } 
                }
            else if (e.KeyChar == (char)27)
            {
                //Console.WriteLine("¨METTRE EN PAUSE");
                parent_.pauseGame();
            }
            return true;
        }


        public override bool traiterMouseDown(object sender, MouseEventArgs e)
        {
            parent_.previousP = new Point(e.X, e.Y);
            parent_.currentP = new Point(e.X, e.Y);
            
            return true;
        }


        public override bool traiterMouseUp(object sender, MouseEventArgs e)
        {
            return base.traiterMouseUp(sender, e);
        }

        public override bool traiterMouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            { 
                double deltaX = (-(parent_.currentP.X - parent_.previousP.X)) * 100.0 / parent_.panelWidth;
                double deltaY = ( (parent_.currentP.Y - parent_.previousP.Y)) * 100.0 / parent_.panelHeight;
                FonctionsNatives.translater(deltaX, deltaY);
                
                parent_.previousP = new Point(parent_.currentP.X, parent_.currentP.Y);
                parent_.currentP  = new Point(e.X, e.Y);
            }

            return true;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatJeuDebutDePartie
    /// @brief EtatJeuDebutDePartie du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-03-06
    /// 
    /// @ingroup Etats
    ///////////////////////////////////////////////////////////////////////////
    class EtatJeuDebutDePartie : InterfaceGraphique.ModeJeu.EtatJeuAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatJeuDebutDePartie(ModeJeu modeJeu)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] modeJeu : Mode de jeu associe a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatJeuDebutDePartie(ModeJeu modeJeu) : base(modeJeu)
        {
            resetConfig();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool traiterRoulette(object sender, MouseEventArgs e)
        /// @brief Traiter le changement d'etat suite a une action de la roulette de souris.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return True ou false selon la reussite des operations.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool traiterRoulette(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
                FonctionsNatives.zoomIn();
            else if (e.Delta < 0)
                FonctionsNatives.zoomOut();
            parent_.setCurrentZoom(FonctionsNatives.obtenirZoomCourant());
            return false;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatJeuFinDePartie
    /// @brief EtatJeuFinDePartie du patron State.
    ///
    /// @author The Ballers
    /// @date 2015-03-06
    /// 
    /// @ingroup Etats
    ///////////////////////////////////////////////////////////////////////////
    class EtatJeuFinDePartie : InterfaceGraphique.ModeJeu.EtatJeuAbstrait
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public EtatJeuFinDePartie(ModeJeu modeJeu)
        /// @brief Constructeur par parametre de l'etat.
        /// 
        /// param[in] modeJeu : Mode de jeu associe a l'etat.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public EtatJeuFinDePartie(ModeJeu modeJeu) : base(modeJeu)
        {
            
        }
    }

}
