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
            serialPort1 = new ReliableSerialPort("COM8", 115200, Parity.None, 8, StopBits.One);
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
                ProcessDecodedMessage(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);
            }
        }

        private void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        {
            //robot.ReceivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);
            for (int i = 0; i < e.Data.Length; i++)
            {
                robot.byteListReceived.Enqueue(e.Data[i]);
                DecodeMessage(e.Data[i]);
            }
        }

        byte CalculateChecksum(int msgFunction, int msgPayloadLength, byte[] msgPayload)
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

        void UartEncodeAndSendMessage(int msgFunction,int msgPayloadLength, byte [ ] msgPayload)
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

        public enum StateReception
        {
            Waiting,
            FunctionMSB,
            FunctionLSB,
            PayloadLengthMSB,
            PayloadLengthLSB,
            Payload,
            CheckSum
        }

        StateReception rcvState = StateReception.Waiting;
        int msgDecodedFunction = 0;
        int msgDecodedPayloadLength = 0;
        byte[] msgDecodedPayload;
        int msgDecodedPayloadIndex = 0;

        private void DecodeMessage(byte c)
        {
            int i = 0;
            switch (rcvState)
            {
                case StateReception.Waiting:
                    if (c == 0xFE)
                    {
                        rcvState = StateReception.FunctionMSB;
                    }
                break;

                case StateReception.FunctionMSB:
                    msgDecodedFunction = (byte)(c << 8);
                    rcvState = StateReception.FunctionLSB;
                break;

                case StateReception.FunctionLSB:
                    msgDecodedFunction += (byte)(c << 0);
                    rcvState = StateReception.PayloadLengthMSB;
                break;

                case StateReception.PayloadLengthMSB:
                    msgDecodedPayloadLength = (byte)(c << 8);
                    rcvState = StateReception.PayloadLengthLSB;
                break;

                case StateReception.PayloadLengthLSB:
                    msgDecodedPayloadLength += (byte)(c << 0);
                    if(msgDecodedPayloadLength != 0)
                    {
                        msgDecodedPayload = new byte[msgDecodedPayloadLength];
                        rcvState = StateReception.Payload;
                    }
                    else
                    {
                        rcvState = StateReception.CheckSum;
                    }
                break;

                case StateReception.Payload:
                    msgDecodedPayload[i] = c;
                    i++;
                    if(i > msgDecodedPayloadLength)
                    {
                        rcvState = StateReception.CheckSum;
                    }
                break;

                case StateReception.CheckSum:
                    byte calculatedChecksum, receivedChecksum;
                    receivedChecksum = c;
                    calculatedChecksum = CalculateChecksum(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);
                    if (calculatedChecksum == receivedChecksum)
                    {
                        TextBoxReception.Text = TextBoxReception.Text + "\n\rLe message est correct"; //Success, on a un message valide
                    }
                    else
                    {
                        TextBoxReception.Text = TextBoxReception.Text + "\n\rLe message est corrumpu";
                    }
                break;

                default:
                    rcvState = StateReception.Waiting;
                break;
            }
        }

        void ProcessDecodedMessage(int msgFunction, int msgPayloadLenght, byte[] msgPayload)
        {
            int numLed, etatLed, IRGauche, IRCentre, IRDroite, MG, MD;
            if(msgDecodedFunction==0x0020) //leds
            {
                numLed = msgPayload[0];
                etatLed = msgPayload[1];
                if(numLed == 1)
                {
                    if(etatLed == 1)
                    {
                        CheckBoxLed1.IsChecked = true;
                    }
                    else
                    {
                        CheckBoxLed1.IsChecked = false;
                    }
                }
                else if (numLed == 2)
                {
                    if (etatLed == 1)
                    {
                        CheckBoxLed1.IsChecked = true;
                    }
                    else
                    {
                        CheckBoxLed1.IsChecked = false;
                    }
                }
                else if (numLed == 2)
                {
                    if (etatLed == 1)
                    {
                        CheckBoxLed1.IsChecked = true;
                    }
                    else
                    {
                        CheckBoxLed1.IsChecked = false;
                    }
                }
            }
            else if(msgDecodedFunction == 0x0030) //IR
            {
                IRDroite = msgPayload[0];
                IRCentre = msgPayload[1];
                IRGauche = msgPayload[2];
                TextBoxTelemetres.Text = "IR Gauche:" + IRGauche.ToString() + "cm\n\r" + "IR Centre:" + IRCentre.ToString() + "cm\n\r" + "IR Droite:" + IRDroite.ToString() + "cm";
            }
            else if(msgDecodedFunction == 0x0040) //moteurs
            {
                MG = msgPayload[0];
                MD = msgPayload[1];
                TextBoxMoteurs.Text = "Vitesse Gauche:" + MG.ToString() + "%\n\r" + "Vitesse Droite:" + MD.ToString() + "%\n\r";
            }
        }

        #region Boutons 
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
            //byte[] message = Encoding.ASCII.GetBytes("Bonjour");
            //UartEncodeAndSendMessage(0x0080, 7, message);
            //UartEncodeAndSendMessage(0x0020, 2, new byte[] { 1, 1 });
            //UartEncodeAndSendMessage(0x0020, 2, new byte[] { 2, 1 });
            //UartEncodeAndSendMessage(0x0020, 2, new byte[] { 3, 1 });
            //UartEncodeAndSendMessage(0x0030, 3, new byte[] { 25, 30, 25 });
            UartEncodeAndSendMessage(0x0040, 2, new byte[] { 41, 38 });
        }

        #endregion

    }
}

