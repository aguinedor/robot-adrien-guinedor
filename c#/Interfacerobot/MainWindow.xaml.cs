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
            serialPort1 = new ReliableSerialPort("COM4", 115200, Parity.None, 8, StopBits.One);
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

        public byte CalculateChecksum(int msgFunction, int msgPayloadLength, byte[] msgPayload)
        {
            byte checksum = 0;
            checksum ^= 0xFE;
            checksum ^= (byte)(msgFunction >> 8);
            checksum ^= (byte)(msgFunction >> 0);
            checksum ^= (byte)(msgPayloadLength >> 8);
            checksum ^= (byte)(msgPayloadLength >> 0);
            for (int i = 0 ; i < msgPayload.Length; i++)
            {
                checksum ^= msgPayload[i];
            }
            return checksum;
        }

        public void UartEncodeAndSendMessage(int msgFunction,int msgPayloadLength, byte [ ] msgPayload)
        {
            byte[] trame = new byte[6 + msgPayload.Length];
            int pos = 0;
            int i;
            trame[pos++] = 0xFE ;
            trame[pos++] = (byte)(msgFunction >> 8);
            trame[pos++] = (byte)(msgFunction >> 0);
            trame[pos++] = (byte)(msgPayloadLength >> 8);
            trame[pos++] = (byte)(msgPayloadLength >> 0);
            for (i = 0; i < msgPayload.Length; i++)
            {
                trame[pos++]= msgPayload[i];
            }
            trame[pos++] = CalculateChecksum(msgFunction, msgPayloadLength,  msgPayload);
            serialPort1.Write(trame, 0, pos);
        }

        private void textBox_TextChanged(object sender, TextChangedEventArgs e) 
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
        private void buttonTest2_Click(object sender, RoutedEventArgs e)
        {
            byte[] message = Encoding.ASCII.GetBytes("Bonjour");
            UartEncodeAndSendMessage(0x0080 , 7, message);
        }

        
    }
}

