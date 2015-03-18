using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class ModeJeu : Form
    { 
        public partial class EtatJeuAbstrait
        {
            protected ModeJeu parent_;
            
            public virtual bool traiterRoulette(object sender, MouseEventArgs e)
            {
                return false;
            }
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
            public virtual bool traiterKeyPress(object sender, KeyPressEventArgs e)
            {
                return false;
            }
            public virtual bool traiterKeyUp(object sender, KeyEventArgs e)
            {
                return false;
            }

            public void toggleDebugOutput()
            {
                if (FonctionsNatives.obtenirAffichageGlobal() == 0)
                {
                    FonctionsNatives.bloquerAffichageGlobal(1);
                    EtatAbstrait.cConsole.Show();
                }
                else
                {
                    FonctionsNatives.bloquerAffichageGlobal(0);
                    EtatAbstrait.cConsole.Hide();
                }
            }

            public void resetConfig()
            {
                parent_.resetConfig();
            }
        }
    }








    class EtatJeuPause : InterfaceGraphique.ModeJeu.EtatJeuAbstrait
    {
        public EtatJeuPause(ModeJeu modeJeu)
            : base(modeJeu)
        {
            //Console.WriteLine("Constructeur Etat :" + '\t' + "Pause");

            parent_.setVisibilityMenuStrip(true);
            FonctionsNatives.modePause(true);
            parent_.setPeutAnimer(false);

        }

        public override bool traiterKeyPress(object sender, KeyPressEventArgs e)
        {
            bool treated = false;
            if (e.KeyChar == (char)27)
            {
                parent_.resumeGame();
                treated = true;
            }
            if (e.KeyChar == 'b')
            {
                toggleDebugOutput();
                treated = true;
            }
            return treated;
        }
    }







    class EtatJeuJouer : InterfaceGraphique.ModeJeu.EtatJeuAbstrait
    {
        public EtatJeuJouer(ModeJeu modeJeu)
            : base(modeJeu)
        {
            //Console.WriteLine("Etat :" + '\t' + "Jouer");

            parent_.setVisibilityMenuStrip(false);
            FonctionsNatives.modePause(false);
            parent_.setPeutAnimer(true);

        }

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
            if ((e.KeyData == Keys.Add ||
                e.KeyCode == Keys.Oemplus && e.Modifiers == Keys.Shift))
            {
                FonctionsNatives.zoomIn();
                parent_.setCurrentZoom(FonctionsNatives.obtenirZoomCourant());
            }

            return true;
        }
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

        public override bool traiterKeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 'b')
            {
                toggleDebugOutput();
            }

            else if (e.KeyChar == 'j')
            {
                //Console.WriteLine("LUMIERE AMBIANTE");
                parent_.toggleAmbiantLight();
                FonctionsNatives.spotLight(0, parent_.getAmbiantLight());
            }
            else if (e.KeyChar == 'k')
            {
                //Console.WriteLine("LUMIERE DIRECTE");
                parent_.toggleDirectLight();
                FonctionsNatives.spotLight(1, parent_.getDirectLight());
            }
            else if (e.KeyChar == 'l')
            {
                //Console.WriteLine("LUMIERE SPOTS");
                parent_.toggleSpotLight();
                FonctionsNatives.spotLight(2, parent_.getSpotLight());
            }
            /*
            else
                if (e.KeyChar == 'n')
                {
                    Console.WriteLine(parent_.currentZone);
                    if (parent_.currentZone >= parent_.nbZones)
                        if (MessageBox.Show("VICTOIRE! VOULEZ VOUR RECOMMENCER?", "FIN DE LA CAMPAGNE",
                   MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation) == DialogResult.Yes)
                        {
                            parent_.RecommencerTout();
                        }
                        else
                        {
                            parent_.Quitter();
                        }
                    else
                    {
                        parent_.map = new StringBuilder(parent_.myMaps[parent_.currentZone]);
                        parent_.nextMap = new StringBuilder(parent_.map.ToString());
                        parent_.nextMap.Remove(parent_.nextMap.Length - 4, 4);
                        Console.WriteLine(Path.GetFileName(parent_.nextMap.ToString()));
                        parent_.zInfo = new ZoneInfo(Path.GetFileName(parent_.nextMap.ToString()), FonctionsNatives.obtenirDifficulte(parent_.map, parent_.map.Capacity).ToString(),false);
                        //this.Hide();
                        parent_.zInfo.ShowDialog();
                        //this.Show();

                        FonctionsNatives.ouvrirXML(parent_.map, parent_.map.Capacity);
                        parent_.resetConfig();
                        FonctionsNatives.construireListesPalettes();
                        parent_.currentZone++;
                }
            * */
            else if (e.KeyChar == (char)8)
                {
                    // RELOAD DE LA MAP
                    parent_.RecommencerPartie();
                }
            else if (e.KeyChar == (char)27)
            {
                //Console.WriteLine("¨METTRE EN PAUSE");
                parent_.pauseGame();
            }
            return true;
        }
    }








    class EtatJeuDebutDePartie : InterfaceGraphique.ModeJeu.EtatJeuAbstrait
    {
        public EtatJeuDebutDePartie(ModeJeu modeJeu) : base(modeJeu)
        {
            //Console.WriteLine("Etat :" + '\t' + "DebutDePartie");
            // Reset des points
            resetConfig();
            // TODO: Complete member initialization
        }

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







    class EtatJeuFinDePartie : InterfaceGraphique.ModeJeu.EtatJeuAbstrait
    {
        public EtatJeuFinDePartie(ModeJeu modeJeu) : base(modeJeu)
        {
            //Console.WriteLine("Etat :" + '\t' + "FinDePartie");
        }
    }

}
