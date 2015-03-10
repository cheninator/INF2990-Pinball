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
            
            public virtual bool KeyDown(object sender, KeyEventArgs e)
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



                if (e.KeyValue == parent_.touches.PGJ1)
                {
                    FonctionsNatives.activerPalettesGJ1();
                }

                else if (e.KeyValue == parent_.touches.PGJ2)
                {
                    // TODO: palette gauche joueur 2
                }
                else if (e.KeyValue == parent_.touches.PDJ1)
                {

                }
                else if (e.KeyValue == parent_.touches.PDJ2)
                {

                }
                else if (e.KeyValue == parent_.touches.Ressort)
                {

                }

                return false;
            }

            public virtual bool KeyPress(object sender, KeyPressEventArgs e)
            {
                if (e.KeyChar == (char)27)
                {
                    if (parent_.menuStrip.Visible)
                    {
                        parent_.menuStrip.Visible = false;
                        FonctionsNatives.modePause(false);
                        parent_.peutAnimer = true;

                    }
                    else
                    {
                        parent_.menuStrip.Visible = true;
                        FonctionsNatives.modePause(true);
                        parent_.peutAnimer = false;

                    }
                }
                else if (e.KeyChar == 'b')
                {
                    if (FonctionsNatives.obtenirAffichageGlobal() == 0)
                    {
                        Console.WriteLine("Affichage bloque. On debloque");
                        FonctionsNatives.bloquerAffichageGlobal(1);
                    }
                    else
                    {
                        Console.WriteLine("Affichage permis. On bloque");
                        FonctionsNatives.bloquerAffichageGlobal(0);
                    }
                }
                else if (e.KeyChar == 'j')
                {
                    //Console.WriteLine("LUMIERE AMBIANTE");
                    parent_.activateAmbianteLight = !(parent_.activateAmbianteLight);
                    FonctionsNatives.spotLight(0, parent_.activateAmbianteLight);
                }
                else if (e.KeyChar == 'k')
                {
                    //Console.WriteLine("LUMIERE DIRECTE");
                    parent_.activateDirectLight = !(parent_.activateDirectLight);
                    FonctionsNatives.spotLight(1, parent_.activateDirectLight);
                }
                else if (e.KeyChar == 'l')
                {
                    //Console.WriteLine("LUMIERE SPOTS");
                    parent_.activateSpotLight = !(parent_.activateSpotLight);
                    FonctionsNatives.spotLight(2, parent_.activateSpotLight);
                }
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

                    }
                    else if (e.KeyChar == (char)8)
                    {
                        // RELOAD DE LA MAP
                        FonctionsNatives.ouvrirXML(parent_.map, parent_.map.Capacity);
                        parent_.resetConfig();
                    }
                return false;
            }
        }
    }

    class EtatJeuPause : InterfaceGraphique.ModeJeu.EtatJeuAbstrait
    {        
        public EtatJeuPause(ModeJeu modeJeu)
        {
            // TODO: Complete member initialization
            this.parent_ = modeJeu;
        }


    }

    class EtatJeuJouer : InterfaceGraphique.ModeJeu.EtatJeuAbstrait
    {
        public EtatJeuJouer(ModeJeu modeJeu)
        {
            // TODO: Complete member initialization
            this.parent_ = modeJeu;
        }

        
    }

    class EtatJeuDebutDePartie : InterfaceGraphique.ModeJeu.EtatJeuAbstrait
    {
        public EtatJeuDebutDePartie(ModeJeu modeJeu)
        {
            // TODO: Complete member initialization
            this.parent_ = modeJeu;
        }
        
    }

    class EtatJeuFinDePartie : InterfaceGraphique.ModeJeu.EtatJeuAbstrait
    {
        public EtatJeuFinDePartie(ModeJeu modeJeu)
        {
            // TODO: Complete member initialization
            this.parent_ = modeJeu;
        }

    }

}
