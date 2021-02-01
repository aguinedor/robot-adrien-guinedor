#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.H"
#include "timer.h"
#include "PWM.h"

int main(void) 
{
    InitOscillator();
    
    InitIO();
    LED_BLANCHE=1;
    LED_BLEUE=1;
    LED_ORANGE=1;
    InitTimer23() ;
    InitTimer1() ;
    
    InitPWM();
    PWMSetSpeed(10,MOTEUR_DROIT);
    PWMSetSpeed(10,MOTEUR_GAUCHE);
    
    
    while(1)        
    {
        
    }
    return (EXIT_SUCCESS);
}

