#include <xc.h>
#include "UART_Protocol.h"

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

private void DecodeMessage(byte c) {
    switch (rcvState) {
        case StateReception.Waiting:
            ?
            break;
        case StateReception.FunctionMSB:
            ?
            break;
        case StateReception.FunctionLSB:
            ?
            break;
        case StateReception.PayloadLengthMSB:
            ?
            break;
        case StateReception.PayloadLengthLSB:
            ?
            break;
        case StateReception.Payload:
            ?
            break;
        case StateReception.CheckSum:
            ?
            if (calculatedChecksum == receivedChecksum) {
                //Success, on a un message valide
            }
            ?
            break;
        default:
            rcvState = StateReception.Waiting;
            break;
    }
}

/*unsigned char UartCalculateChecksum(int msgFunction,int msgPayloadLength, unsigned char* msgPayload)
{
//Fonction prenant entrée la trame et sa longueur pour calculer le checksum
}

void UartEncodeAndSendMessage(int msgFunction,int msgPayloadLength, unsigned char* msgPayload)
{
//Fonction d?encodage et d?envoi d?un message
}

int msgDecodedFunction = 0;
int msgDecodedPayloadLength = 0;
unsigned char msgDecodedPayload[128];
int msgDecodedPayloadIndex = 0;

void UartDecodeMessage(unsigned char c)
{
//Fonction prenant en entrée un octet et servant à reconstituer les trames
}

void UartProcessDecodedMessage(unsigned char function,unsigned char payloadLength, unsigned char* payload)
{
//Fonction appelée après le décodage pour exécuter l?action
//correspondant au message reçu
}*/

 

//*************************************************************************/
//Fonctions correspondant aux messages
//***** 