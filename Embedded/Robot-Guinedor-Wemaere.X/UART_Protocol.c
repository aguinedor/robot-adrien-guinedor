#include <xc.h>
#include "UART_Protocol.h"


int msgDecodedFunction = 0;
int msgDecodedPayloadLength = 0;
unsigned char msgDecodedPayload[128];
int msgDecodedPayloadIndex = 0;


unsigned char UartCalculateChecksum(int msgFunction,int msgPayloadLength, unsigned char* msgPayload)
{
    int i;
    unsigned char  checksum = 0xFE;
    checksum ^= msgFunction>>8;
    checksum ^= msgFunction>>0;
    checksum ^= msgPayloadLength>>8;
    checksum ^= msgPayloadLength>>0;
    for (i = 0 ; i < msgPayloadLength; i++)
    {
        checksum ^= msgPayload[i];
    }
    return checksum;
}

void UartEncodeAndSendMessage(int msgFunction,int msgPayloadLength, unsigned char* msgPayload)
{
    int pos=0,i;
    unsigned char trame[6+msgPayloadLength];
    trame[pos++]=0xFE;
    trame[pos++]= msgFunction>>8;
    trame[pos++]= msgFunction>>0;
    trame[pos++]= msgPayloadLength>>8;
    trame[pos++]=msgPayloadLength>>0;
    for(i=0;i<msgPayloadLength;i++)
    {
        trame[pos++]=msgPayload[i];
    }
    trame[pos++]= UartCalculateChecksum(msgFunction, msgPayloadLength, msgPayload);
    SendMessage(trame,pos);
           
}

/*void UartDecodeMessage(unsigned char c)
{
    //Fonction prenant en entrée un octet et servant à reconstituer les trames
    ?
}

void UartProcessDecodedMessage(unsigned char function,unsigned char payloadLength, unsigned char* payload)
{
    //Fonction appelée après le décodage pour exécuter l?action
    //correspondant au message reçu
    ?
}*/