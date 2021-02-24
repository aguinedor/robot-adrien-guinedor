#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.H"
#include "timer.h"
#include "PWM.h"
#include "robot.h"
#include "ADC.h" 
#include "main.h"
#include "etat.h"

#define STATE_ATTENTE 0
#define STATE_ATTENTE_EN_COURS 1
#define STATE_AVANCE 2
#define STATE_AVANCE_EN_COURS 3
#define STATE_TOURNE_GAUCHE 4
#define STATE_TOURNE_GAUCHE_EN_COURS 5
#define STATE_TOURNE_DROITE 6
#define STATE_TOURNE_DROITE_EN_COURS 7
#define STATE_TOURNE_GAUCHE_DOUX 8
#define STATE_TOURNE_GAUCHE_DOUX_EN_COURS 9
#define STATE_TOURNE_DROITE_DOUX 10
#define STATE_TOURNE_DROITE_DOUX_EN_COURS 11
#define STATE_TOURNE_SUR_PLACE_GAUCHE 12
#define STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS 13
#define STATE_TOURNE_SUR_PLACE_DROITE 14
#define STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS 15
#define STATE_DROITE_TUNNEL 16
#define STATE_DROITE_TUNNEL_EN_COURS 17
#define STATE_GAUCHE_TUNNEL 18
#define STATE_GAUCHE_TUNNEL_EN_COURS 19
#define STATE_ARRET 20
#define STATE_ARRET_EN_COURS 21

#define PAS_D_OBSTACLE 0
#define OBSTACLE_A_GAUCHE 1 //tourne en avançant vers la droite
#define OBSTACLE_SUR_LA_GAUCHE 2  //tourne vers la droite
#define OBSTACLE_A_DROITE 3 //tourne en avançant vers la gauche
#define OBSTACLE_SUR_LA_DROITE 4 //tourne vers la gauche
#define OBSTACLE_EN_FACE 5 //tourne sur place vers la gauche/la droite 
#define TUNNEL_GAUCHE 6
#define TUNNEL_DROITE 7

 unsigned int mode,vr=15,rdm=0; //  vitesses (manoeuvre,route) et modes

int main(void) 
{
    InitOscillator();
    InitIO();
    InitPWM();
    InitADC1();
    InitTimer1() ;
    InitTimer23() ;
    InitTimer4();
//   PWMSetSpeedConsigne(-20, MOTEUR_DROIT);
//   PWMSetSpeedConsigne(-20, MOTEUR_GAUCHE);
    
    while(1)        
    {
        if(ADCIsConversionFinished()==1)
        {
            ADCClearConversionFinishedFlag();
            unsigned int * result=ADCGetResult();
            float volts =((float) result [0])*3.3/4096*3.2;
            robotState.distanceTelemetreDroit2 = 34 / volts-5 ;
            volts =((float) result [1])*3.3/4096*3.2;
            robotState.distanceTelemetreDroit = 34 / volts-5 ;
            volts =((float) result [2])*3.3/4096*3.2;
            robotState.distanceTelemetreCentre = 34 / volts-5 ;
            volts =((float) result [4])*3.3/4096*3.2;
            robotState.distanceTelemetreGauche = 34 / volts-5 ;
            volts =((float) result [3])*3.3/4096*3.2;
            robotState.distanceTelemetreGauche2 = 34 / volts-5 ;
        }
        
//        if (robotState.distanceTelemetreDroit > 10)
//        {
//            LED_ORANGE=1;
//        }
//        else
//        {
//            LED_ORANGE=0;
//        }
//        if (robotState.distanceTelemetreDroit2 > 10)
//        {
//            LED_BLEUE=1;
//        }
//        else
//        {
//            LED_BLEUE=0;
//        }
//        if (robotState.distanceTelemetreGauche2 > 10)
//        {
//            LED_BLANCHE=1;
//        }
//        else
//        {
//            LED_BLANCHE=0;
//        }
   }
    return (EXIT_SUCCESS);
}

unsigned char stateRobot;

void OperatingSystemLoop(void)
{
            if(mode==1)
            {   
                vr= 15;
            }
            else if (mode==2)
                vr= 20;
            else if (mode==3)
                vr= 25;
    switch (stateRobot)
    {
        case STATE_ATTENTE:
        timestamp = 0;
        PWMSetSpeedConsigne(0, MOTEUR_DROIT);
        PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
        stateRobot = STATE_ATTENTE_EN_COURS;

        case STATE_ATTENTE_EN_COURS:
        if (timestamp > 1000)
        stateRobot = STATE_AVANCE;
        break;

        case STATE_AVANCE:
        rdm=rdm+1;
        PWMSetSpeedConsigne(vr, MOTEUR_DROIT);
        PWMSetSpeedConsigne(vr, MOTEUR_GAUCHE);
        stateRobot = STATE_AVANCE_EN_COURS;
        break;
        case STATE_AVANCE_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;
        
        case STATE_TOURNE_GAUCHE_DOUX:
        PWMSetSpeedConsigne(15, MOTEUR_DROIT);
        PWMSetSpeedConsigne(10, MOTEUR_GAUCHE);
        stateRobot = STATE_TOURNE_GAUCHE_DOUX_EN_COURS;
        break;
        case STATE_TOURNE_GAUCHE_DOUX_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;
        
        case STATE_TOURNE_DROITE_DOUX:
        PWMSetSpeedConsigne(10, MOTEUR_DROIT);
        PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
        stateRobot = STATE_TOURNE_DROITE_DOUX_EN_COURS;
        break;
        case STATE_TOURNE_DROITE_DOUX_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;

        case STATE_TOURNE_GAUCHE:
        PWMSetSpeedConsigne(15, MOTEUR_DROIT);
        PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
        stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
        break;
        case STATE_TOURNE_GAUCHE_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;

        case STATE_TOURNE_DROITE:
        PWMSetSpeedConsigne(0, MOTEUR_DROIT);
        PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
        stateRobot = STATE_TOURNE_DROITE_EN_COURS;
        break;
        case STATE_TOURNE_DROITE_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;

        case STATE_TOURNE_SUR_PLACE_GAUCHE:
        PWMSetSpeedConsigne(15, MOTEUR_DROIT);
        PWMSetSpeedConsigne(-15, MOTEUR_GAUCHE);
        stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
        break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;

        case STATE_TOURNE_SUR_PLACE_DROITE:
        PWMSetSpeedConsigne(-15, MOTEUR_DROIT);
        PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
        stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
        break;
        case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;

        case STATE_DROITE_TUNNEL:
        PWMSetSpeedConsigne(10, MOTEUR_DROIT);
        PWMSetSpeedConsigne(5, MOTEUR_GAUCHE);
        stateRobot = STATE_DROITE_TUNNEL_EN_COURS;
        break;
        case STATE_DROITE_TUNNEL_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;
        
        case STATE_GAUCHE_TUNNEL:
        PWMSetSpeedConsigne(5, MOTEUR_DROIT);
        PWMSetSpeedConsigne(10, MOTEUR_GAUCHE);
        stateRobot = STATE_GAUCHE_TUNNEL_EN_COURS;
        break;
        case STATE_GAUCHE_TUNNEL_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;
        
        default :
        stateRobot = STATE_ATTENTE;
        break;
    }
}

unsigned char nextStateRobot=0;

void SetNextRobotStateInAutomaticMode(void)
{
    unsigned char positionObstacle=PAS_D_OBSTACLE;
    

    //Détermination de la position des obstacles en fonction des télémètres

    if ( robotState.distanceTelemetreGauche2 < 20 ||
    robotState.distanceTelemetreGauche < 30 ||
    robotState.distanceTelemetreCentre < 35 ||
    robotState.distanceTelemetreDroit < 30 ||
    robotState.distanceTelemetreDroit2 < 20 )
    {
        mode=1;
        positionObstacle=etat();
    }
    else if( robotState.distanceTelemetreGauche2 < 40 ||
    robotState.distanceTelemetreGauche < 50 ||
    robotState.distanceTelemetreCentre < 60 ||
    robotState.distanceTelemetreDroit < 50 ||
    robotState.distanceTelemetreDroit2 < 40 )
    {
        mode=2;
    }
    else if (robotState.distanceTelemetreGauche2 >= 40 ||
    robotState.distanceTelemetreGauche >= 50 ||
    robotState.distanceTelemetreCentre >= 60 ||
    robotState.distanceTelemetreDroit >= 50 ||
    robotState.distanceTelemetreDroit2 >= 40 )
    {
       mode=3 ;
    }

    //Détermination de l?état à venir du robot
    if (positionObstacle == PAS_D_OBSTACLE)
    nextStateRobot = STATE_AVANCE;
    else if (positionObstacle == OBSTACLE_A_DROITE)
    nextStateRobot = STATE_TOURNE_GAUCHE_DOUX;
    else if (positionObstacle == OBSTACLE_A_GAUCHE)
    nextStateRobot = STATE_TOURNE_DROITE_DOUX;
    else if (positionObstacle == OBSTACLE_SUR_LA_DROITE)
    nextStateRobot = STATE_TOURNE_GAUCHE;
    else if (positionObstacle == OBSTACLE_SUR_LA_GAUCHE)
    nextStateRobot = STATE_TOURNE_DROITE;
    else if (positionObstacle == OBSTACLE_EN_FACE)
    {
        if (rdm%2==0)
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
        else
        nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
    } 
    else if (positionObstacle == TUNNEL_GAUCHE)
    nextStateRobot = STATE_DROITE_TUNNEL;
    else if (positionObstacle == TUNNEL_DROITE)
    nextStateRobot = STATE_GAUCHE_TUNNEL;
    //Si l?on n?est pas dans la transition de l?étape en cours
    if (nextStateRobot != stateRobot - 1);
    stateRobot = nextStateRobot;
}