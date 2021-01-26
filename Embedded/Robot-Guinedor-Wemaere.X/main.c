#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.H"

int main(void) 
{
    InitOscillator();
    
    InitIO();
    LED_BLANCHE=1;
    LED_BLEUE=1;
    LED_ORANGE=1;
    
    while(1)
    {
        LED_BLANCHE = !LED_BLANCHE;
    }
    return (EXIT_SUCCESS);
}

