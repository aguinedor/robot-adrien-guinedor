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
#define STATE_TOURNE_SUR_PLACE_GAUCHE 8
#define STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS 9
#define STATE_TOURNE_SUR_PLACE_DROITE 10
#define STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS 11
#define STATE_ARRET 12
#define STATE_ARRET_EN_COURS 13
#define STATE_RECULE 14
#define STATE_RECULE_EN_COURS 15

#define PAS_D_OBSTACLE 0
#define OBSTACLE_A_GAUCHE 1 
#define OBSTACLE_SUR_LA_GAUCHE 2  //tourne sur place vers la droite
#define OBSTACLE_A_DROITE 3
#define OBSTACLE_SUR_LA_DROITE 4 //tourne sur place vers la gauche
#define OBSTACLE_EN_FACE 5 //recule et tourne sur place vers la gauche

 unsigned int a,b,c,m,v=0,rdm; // distance pour les telemetres (a-b-c) et vitesses (manoeuvre, moyenne, croisière)

int main(void) 
{
    
    
    
    InitOscillator();
    
    InitIO();
    
    InitPWM();
    InitADC1();
    
    InitTimer1() ;
   InitTimer23() ;
//   PWMSetSpeedConsigne(-20, MOTEUR_DROIT);
//    PWMSetSpeedConsigne(-20, MOTEUR_GAUCHE);
    InitTimer4();
    
    
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


void OperatingSystemLoop(void)
    {
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
    if(m==1)
        v=15;
    else if (m==2)
        v=25;
    else if (m==3)
        v=35;
PWMSetSpeedConsigne(v, MOTEUR_DROIT);
PWMSetSpeedConsigne(v, MOTEUR_GAUCHE);
stateRobot = STATE_AVANCE_EN_COURS;
break;
case STATE_AVANCE_EN_COURS:
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
    LED_BLANCHE=1;
PWMSetSpeedConsigne(15, MOTEUR_DROIT);
PWMSetSpeedConsigne(-15, MOTEUR_GAUCHE);
stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
break;
case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
SetNextRobotStateInAutomaticMode();
break;

case STATE_TOURNE_SUR_PLACE_DROITE:
    LED_ORANGE=1;
PWMSetSpeedConsigne(-15, MOTEUR_DROIT);
PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
break;
case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
SetNextRobotStateInAutomaticMode();
break;

//case STATE_RECULE:
//
//PWMSetSpeedConsigne(-10, MOTEUR_DROIT);
//PWMSetSpeedConsigne(-10, MOTEUR_GAUCHE);
//stateRobot = STATE_RECULE_EN_COURS;
//break;
//case STATE_RECULE_EN_COURS:
//PWMSetSpeedConsigne(10, MOTEUR_DROIT);
//PWMSetSpeedConsigne(-10, MOTEUR_GAUCHE);
//stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
//break;
//case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
//SetNextRobotStateInAutomaticMode();
//break;

default :
stateRobot = STATE_ATTENTE;
break;
}
}

unsigned char nextStateRobot=0;

void SetNextRobotStateInAutomaticMode(void)
{

    rdm+=1;

//Détermination de la position des obstacles en fonction des télémètres

if ( robotState.distanceTelemetreGauche < 30 ||
robotState.distanceTelemetreCentre < 20 ||
robotState.distanceTelemetreDroit < 30 )
{
    m=1;
    a=20;
    b=30;
    c=20;
    
    
    else if(robotState.distanceTelemetreGauche2 < 10 &&
    robotState.distanceTelemetreDroit2 < 10 )
    {
        if (robotState.distanceTelemetreGauche < robotState.distanceTelemetreDroit)
            positionObstacle = OBSTACLE_SUR_LA_GAUCHE  ;
        else if (robotState.distanceTelemetreGauche > robotState.distanceTelemetreDroit)
            positionObstacle = OBSTACLE_SUR_LA_DROITE  ;
        else if (robotState.distanceTelemetreGauche == robotState.distanceTelemetreDroit)
            positionObstacle = PAS_D_OBSTACLE  ;
    }
}
else if(robotState.distanceTelemetreGauche < 50 ||
robotState.distanceTelemetreCentre < 60 ||
robotState.distanceTelemetreDroit < 50 )
{
    m=2;
}



//if ( robotState.distanceTelemetreDroit < 20 &&
//robotState.distanceTelemetreCentre > 15 &&
//robotState.distanceTelemetreGauche > 20) //Obstacle à droite
//positionObstacle = OBSTACLE_A_DROITE;
//else if(robotState.distanceTelemetreDroit > 20 &&
//robotState.distanceTelemetreCentre > 15 &&
//robotState.distanceTelemetreGauche < 20) //Obstacle à gauche
//positionObstacle = OBSTACLE_A_GAUCHE;
//else if(robotState.distanceTelemetreCentre < 15) //Obstacle en face
//positionObstacle = OBSTACLE_EN_FACE;
//else if(robotState.distanceTelemetreDroit > 20 &&
//robotState.distanceTelemetreCentre > 15 &&
//robotState.distanceTelemetreGauche > 20) //pas d?obstacle
//positionObstacle = PAS_D_OBSTACLE;



//Détermination de l?état à venir du robot
if (positionObstacle == PAS_D_OBSTACLE)
nextStateRobot = STATE_AVANCE;
else if (positionObstacle == OBSTACLE_A_DROITE)
nextStateRobot = STATE_TOURNE_GAUCHE;
else if (positionObstacle == OBSTACLE_A_GAUCHE)
nextStateRobot = STATE_TOURNE_DROITE;
else if (positionObstacle == OBSTACLE_SUR_LA_DROITE)
nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
else if (positionObstacle == OBSTACLE_SUR_LA_GAUCHE)
nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
else if (positionObstacle == OBSTACLE_EN_FACE){
    if (rdm%2==0)
    nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
    else
    nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;} 

//Si l?on n?est pas dans la transition de l?étape en cours
if (nextStateRobot != stateRobot - 1);
stateRobot = nextStateRobot;
}