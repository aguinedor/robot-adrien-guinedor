#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.H"
#include "timer.h"
#include "PWM.h"
#include "robot.h"

int main(void) 
{
    InitOscillator();
    
    InitIO();
    LED_BLANCHE=1;
    LED_BLEUE=1;
    LED_ORANGE=1;
    
    
    
    InitPWM();
    PwmSetSpeedConsigne(30, MOTEUR_DROIT);
    PwmSetSpeedConsigne(30, MOTEUR_GAUCHE);
    
    //InitTimer1() ;
    InitTimer23() ;
    
    while(1)        
    {
        
    }
    return (EXIT_SUCCESS);
}

