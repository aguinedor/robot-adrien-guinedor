#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.H"
#include "timer.h"

int main(void) 
{
    InitOscillator();
    
    InitIO();
    LED_BLANCHE=1;
    LED_BLEUE=1;
    LED_ORANGE=1;
    InitTimer23() ;
    InitTimer1() ;
    
    while(1)
        
    {
    }
    return (EXIT_SUCCESS);
}

