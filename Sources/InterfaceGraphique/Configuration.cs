using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    public partial class Configuration : Form
    {
        int[] defaultValues = { 65, 83, 52, 53};
        int[] currentValues = { 65, 83, 52, 53, 32, 49, 50, 74, 75, 76, 66 };
        int[] valuesXML = new int[13]; 
        string maTouche;
        bool mediaPlaying = false;
        System.Media.SoundPlayer p = new System.Media.SoundPlayer(Properties.Resources.touche_invalide);
        public Configuration()
        {
            InitializeComponent();
            comboBoxBilles.Text = "3";
            KeyPreview = true;
            InitialiserAvecBinaire();
        }


        private void InitialiserAvecBinaire()
        {
         
            IntPtr config = FonctionsNatives.chargerFichierConfiguration();
            int[] result = new int[13];
            Marshal.Copy(config, valuesXML, 0, 13);
                
            for(int i = 0; i < 5; i++){
                currentValues[i] = valuesXML[i];             
            }
            InitialiserTouches();
            
            //valuesXML[5] = Convert.ToInt32(comboBoxBilles.Text.ToString());
            comboBoxBilles.Text = valuesXML[5].ToString();

            //valuesXML[6] = Convert.ToInt32(MDB_OK.Checked);
            if (valuesXML[6] != 0)
                MDB_OK.Checked = true;
            else
                MDB_Cancel.Checked = true;

            //valuesXML[7] = Convert.ToInt32(FRS_OK.Checked);
            if( valuesXML[7] != 0)
                FRS_OK.Checked = true;
            else
                FRS_Cancel.Checked = true;

            //valuesXML[8] = Convert.ToInt32(GB_OK.Checked);
              if( valuesXML[8] != 0)
                GB_OK.Checked = true;
              else
                GB_Cancel.Checked = true;

            //valuesXML[9] = Convert.ToInt32(VAC_OK.Checked);
             if( valuesXML[9] != 0)
                VAC_OK.Checked = true;
              else
                VAC_Cancel.Checked = true;

            //valuesXML[10] = Convert.ToInt32(AE_OK.Checked);
            if (valuesXML[10] != 0)
                AE_OK.Checked = true;
            else
                AE_Cancel.Checked = true;

            //valuesXML[11] = Convert.ToInt32(PORTAL_OK.Checked);    
            if( valuesXML[11] != 0)
                PORTAL_OK.Checked = true;
            else
                PORTAL_Cancel.Checked = true;

            if (valuesXML[12] != 0)
            {
                GLOB_OK.Checked = true;
               
            }
            else
            {
                GLOB_Cancel.Checked = true;
            }
        }

        private void InitialiserTouches()
        {
            maTouche = char.ConvertFromUtf32(currentValues[0]);
            if (maTouche == " ")
                maTouche = "Espace";
            PGJ1_bouton.Text = maTouche;

            maTouche = char.ConvertFromUtf32(currentValues[1]);
            if (maTouche == " ")
                maTouche = "Espace";
            PDJ1_bouton.Text = maTouche;

            maTouche = char.ConvertFromUtf32(currentValues[2]);
            if (maTouche == " ")
                maTouche = "Espace";
            PGJ2_bouton.Text = maTouche;

            maTouche = char.ConvertFromUtf32(currentValues[3]);
            if (maTouche == " ")
                maTouche = "Espace";
            PDJ2_bouton.Text = maTouche;

            maTouche = char.ConvertFromUtf32(currentValues[4]);
            if (maTouche == " ")
                maTouche = "Espace";
            Ressort_bouton.Text = maTouche;
        }


        private bool isValid(int touche)
        {
            if( (touche >= 65 && touche <= 90) || (touche >= 48 && touche <= 57) || (touche == 32) )
            {
                foreach (int x in currentValues)
                {
                    if (x.Equals(touche))
                    {
                        label_Rebind.Text = "Touche deja utilisée";
                        Console.WriteLine("Touche deja utilise");
                        return false;
                    }
                }
                p.Stop(); 
                mediaPlaying = false;
                return true;
            }
            else
            {
                label_Rebind.Text = "Touche invalide";
                Console.WriteLine("Touche invalide");
                if (!mediaPlaying)
                {
                    p.Stream = Properties.Resources.touche_invalide;
                    p.PlayLooping();
                    mediaPlaying = true;
                }
                return false;
            }

        }
        private void Annuler_bouton_Click(object sender, EventArgs e)
        {
            this.Close();
        }


        private void Default_bouton_Click(object sender, EventArgs e)
        {
            PGJ1_bouton.Text = char.ConvertFromUtf32(defaultValues[0]);
            PDJ1_bouton.Text = char.ConvertFromUtf32(defaultValues[1]);
            PGJ2_bouton.Text = char.ConvertFromUtf32(defaultValues[2]);
            PDJ2_bouton.Text = char.ConvertFromUtf32(defaultValues[3]);
            Ressort_bouton.Text = "Espace";
            currentValues[0] = 65;
            currentValues[1] = 83;
            currentValues[2] = 52;
            currentValues[3] = 53;
            currentValues[4] = 32;
        }

        private void LabelChange(string message)
        {
            label_Rebind.Text = "Appuyez sur une touche pour changer la touche de " + message;

        }

       

        private void PGJ1_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            
           // Console.WriteLine("KeyCode :" + e.KeyCode);
           // Console.WriteLine("KeyData : " + e.KeyData);
           // Console.WriteLine("KeyValue : " + e.KeyValue);
            
            int touche = e.KeyValue;
            if( this.isValid(touche) == true)
            {
                currentValues[0] = touche;
                maTouche = char.ConvertFromUtf32(touche);
                if (maTouche == " ")
                    maTouche = "Espace";
                PGJ1_bouton.Text = maTouche;
            }
                   

        }

        private void PDJ1_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            int touche = e.KeyValue;
            if (this.isValid(touche) == true)
            {
                currentValues[1] = touche;
                maTouche = char.ConvertFromUtf32(touche);
                if (maTouche == " ")
                    maTouche = "Espace";
                PDJ1_bouton.Text = maTouche;
            }
        }

        private void PGJ2_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            int touche = e.KeyValue;
            if (this.isValid(touche) == true)
            {
                maTouche = char.ConvertFromUtf32(touche);
                currentValues[2] = touche;
                if (maTouche == " ")
                    maTouche = "Espace";
                PGJ2_bouton.Text = maTouche;
            }
        }

        private void PDJ2_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            int touche = e.KeyValue;
            if (this.isValid(touche) == true)
            {
                currentValues[3] = touche;
                maTouche = char.ConvertFromUtf32(touche);
                if (maTouche == " ")
                    maTouche = "Espace";
                PDJ2_bouton.Text = maTouche;
            }
        }

        private void Ressort_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            int touche = e.KeyValue;
            if (this.isValid(touche) == true)
            {
                currentValues[4] = touche;
                maTouche = char.ConvertFromUtf32(touche);
                if (maTouche == " ")
                    maTouche = "Espace";
                Ressort_bouton.Text = maTouche;
            }
        }

        private void PGJ1_bouton_Click(object sender, EventArgs e)
        {
           // PGJ1_bouton.ForeColor = Color.Red;
            LabelChange("palette gauche de Joueur 1");
        }

        private void PDJ1_bouton_Click(object sender, EventArgs e)
        {
           // PDJ1_bouton.ForeColor = Color.Red;
            LabelChange("palette droite de Joueur 1");
        }

        private void PGJ2_bouton_Click(object sender, EventArgs e)
        {
            //PGJ2_bouton.ForeColor = Color.Red;
            LabelChange("palette gauche de Joueur 2");
        }

        private void PDJ2_bouton_Click(object sender, EventArgs e)
        {
            //PDJ2_bouton.ForeColor = Color.Red;
            LabelChange("palette droite de Joueur 2");
        }

        private void Ressort_bouton_Click(object sender, EventArgs e)
        {
            //Ressort_bouton.ForeColor = Color.Red;
            LabelChange("Ressorts");
        }

        private void OK_bouton_Click(object sender, EventArgs e)
        {
            for(int i = 0; i < 5; i++)
                valuesXML[i] = currentValues[i];
            valuesXML[5] = Convert.ToInt32(comboBoxBilles.Text.ToString());
            valuesXML[6] = Convert.ToInt32(MDB_OK.Checked);
            valuesXML[7] = Convert.ToInt32(FRS_OK.Checked);
            valuesXML[8] = Convert.ToInt32(GB_OK.Checked);
            valuesXML[9] = Convert.ToInt32(VAC_OK.Checked);
            valuesXML[10] = Convert.ToInt32(AE_OK.Checked);
            valuesXML[11] = Convert.ToInt32(PORTAL_OK.Checked);
            valuesXML[12] = Convert.ToInt32(GLOB_OK.Checked);

            FonctionsNatives.creerFichierConfig(valuesXML);
            this.Close();
        }

        public bool getConfig(int i)
        {
            if (i == 0)
                return GB_OK.Checked;
            else if (i == 1)
                return VAC_OK.Checked;
            else if (i == 2)
                return AE_OK.Checked;
            else if (i == 3)
                return PORTAL_OK.Checked;
            else
                return false;
        }
        private void radioButtonEnable(bool active)
        {
            GB_Cancel.Enabled = active;
            GB_OK.Enabled = active;
            VAC_Cancel.Enabled = active;
            VAC_OK.Enabled = active;
            AE_Cancel.Enabled = active;
            AE_OK.Enabled = active;
            PORTAL_Cancel.Enabled = active;
            PORTAL_OK.Enabled = active;

        }

        private void GLOB_Cancel_CheckedChanged(object sender, EventArgs e)
        {
            if (GLOB_Cancel.Checked)
            {
             /*   GB_Cancel.Checked = true;
                VAC_Cancel.Checked = true;
                AE_Cancel.Checked = true;
                PORTAL_Cancel.Checked = true;
              */
                radioButtonEnable(false);   
            }
        }

        private void GLOB_OK_CheckedChanged(object sender, EventArgs e)
        {
            if (GLOB_OK.Checked)
            {
                radioButtonEnable(true);
            }
        }
    }
}
