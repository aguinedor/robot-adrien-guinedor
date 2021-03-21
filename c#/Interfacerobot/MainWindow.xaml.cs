using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Interfacerobot
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        public MainWindow()
        {
            InitializeComponent();
        }

        private void textBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
        
        private void TextBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if(e.Key == Key.Enter)
            {
                messagerie();
            }
        }

        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            TextBoxReception.Text = "";
        }
        
        private void messagerie()
        {
            TextBoxReception.Text = TextBoxReception.Text + "Message reçu: " + TextBoxEmission.Text + "\r\n";
            TextBoxEmission.Text = "";
        }

        int cpt=0;
        private void buttonColor_Click(object sender, RoutedEventArgs e)
        {
            if(cpt==0)
            {
                buttonColor.Background = Brushes.Red;
                buttonColor.Content = "RED";
                TextBoxEmission.Foreground = Brushes.Red;
                TextBoxReception.Foreground = Brushes.Red;
                cpt++;
            }
            else if (cpt==1)
            {
                buttonColor.Background = Brushes.Green;
                buttonColor.Content = "GREEN";
                TextBoxEmission.Foreground = Brushes.Green;
                TextBoxReception.Foreground = Brushes.Green;
                cpt++;
            }
            else if (cpt == 2)
            {
                buttonColor.Background = Brushes.White;
                buttonColor.Content = "WHITE";
                TextBoxEmission.Foreground = Brushes.White;
                TextBoxReception.Foreground = Brushes.White;
                cpt =0;
            }
        }
    }
}

