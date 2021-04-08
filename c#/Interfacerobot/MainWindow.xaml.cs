using System;
using System.Collections.Generic;
using System.IO.Ports;
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
using ExtendedSerialPort;
using System.Windows.Threading;


namespace Interfacerobot
{
    public partial class MainWindow : Window
    {
        ReliableSerialPort serialPort1;
        DispatcherTimer timerAffichage;
        Robot robot = new Robot();
        int i;
        public MainWindow()
        {
            InitializeComponent();
            serialPort1 = new ReliableSerialPort("COM3", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            serialPort1.Open();

            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timerAffichage.Tick += TimerAffichage_Tick;
            timerAffichage.Start();

        }

        private void TimerAffichage_Tick(object sender, EventArgs e)
        {
            int x=0;
            /*TextBoxReception.Text += robot.ReceivedText;
            robot.ReceivedText = "";*/
            while(robot.byteListReceived.Count > 0)
            {
                //TextBoxReception.Text += robot.byteListReceived.Dequeue();
                byte byteReceived = robot.byteListReceived.Dequeue();
                string receivedText = "0x" + byteReceived.ToString("X2") + " " ;
                //char receivedText = Convert.ToChar(byteReceived);
                TextBoxReception.Text += receivedText;
            }
        }

        private void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        {
            //robot.ReceivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);
            for (int i = 0; i < e.Data.Length; i++)
            {
                robot.byteListReceived.Enqueue(e.Data[i]);
            }
        }

        int checksum = 0;
        byte CalculateChecksum(int msgFunction, int msgPayloadLength, byte[] msgPayload) //stackoverflow
        {

        }

        /*private void textBox_TextChanged(object sender, TextChangedEventArgs e) 
        {

        }
        
        private void TextBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if(e.Key == Key.Enter)
            {
                sendMessage();
            }
        }

        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            robot.ReceivedText = null;
            TextBoxEmission.Text = "";
            TextBoxReception.Text = "";

        }

        private void sendMessage()
        {
            
            //TextBoxReception.Text = TextBoxReception.Text + "Message reçu: " + TextBoxEmission.Text + "\r\n";
            //TextBoxEmission.Text = "";
            serialPort1.Write(TextBoxEmission.Text);
            TextBoxEmission.Text = "";
        }

        private void buttonTest_Click(object sender, RoutedEventArgs e)
        {
            byte[] byteList= new byte[20];
            for (i= 0;i < 20;i++)
            {
                byteList[i] = (byte)(2 * i);
            }
            serialPort1.Write(byteList,0,byteList.Length);
        }

        int cpt = 0;
        private void buttonColor_Click(object sender, RoutedEventArgs e)
        {
            
            if (cpt==0)
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

