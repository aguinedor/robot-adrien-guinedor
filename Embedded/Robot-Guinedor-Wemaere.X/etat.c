#include "etat.h"
#include <xc.h>
#include "main.h"
#include "robot.h"

#define PAS_D_OBSTACLE 0
#define OBSTACLE_A_GAUCHE 1 
#define OBSTACLE_SUR_LA_GAUCHE 2  //tourne sur place vers la droite
#define OBSTACLE_A_DROITE 3
#define OBSTACLE_SUR_LA_DROITE 4 //tourne sur place vers la gauche
#define OBSTACLE_EN_FACE 5 //tourne sur place vers la gauche/la droite
#define OBSTACLE_CUL_DE_SAC 6 // tourne sur place vers la gauche/la droite selon la distance 

int obstacle;

int etat(int gauche2, int gauche, int centre, int droit, int droit2)
{ 
        if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 1
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_EN_FACE; 

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 2
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_SUR_LA_DROITE;

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 3
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_SUR_LA_DROITE;

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 4
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_SUR_LA_DROITE;

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 5
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_SUR_LA_GAUCHE;

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 6
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 < droit2) 
        obstacle = OBSTACLE_CUL_DE_SAC; 

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 7
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_A_GAUCHE;  

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 8
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_A_DROITE; 

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 9
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_A_GAUCHE;

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 10
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 < droit2) 
        obstacle = OBSTACLE_A_DROITE;  

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 11
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 < droit2) 
        obstacle = OBSTACLE_SUR_LA_DROITE;  

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 12
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_SUR_LA_GAUCHE;

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 13
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 < droit2 ) 
        obstacle = OBSTACLE_CUL_DE_SAC;

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 14
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 > droit2 ) 
        obstacle = OBSTACLE_SUR_LA_GAUCHE; 

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 15
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 < droit2 ) 
        obstacle = OBSTACLE_SUR_LA_DROITE; 

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 16
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 < droit2 ) 
        obstacle = OBSTACLE_CUL_DE_SAC;

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 17
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 < droit2 ) 
        obstacle = OBSTACLE_CUL_DE_SAC;

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 18
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 < droit2) 
        obstacle = OBSTACLE_SUR_LA_DROITE;

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 19
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_SUR_LA_GAUCHE; 

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 20
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 < droit2) 
        obstacle = OBSTACLE_CUL_DE_SAC;

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 21
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_SUR_LA_GAUCHE; 

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 22
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_SUR_LA_DROITE;

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 23
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 < droit2) 
        obstacle = OBSTACLE_SUR_LA_DROITE;

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 24
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_SUR_LA_GAUCHE; 

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 25
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 < droit2) 
        obstacle = OBSTACLE_CUL_DE_SAC; 

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 26
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 < droit2) 
        obstacle = OBSTACLE_CUL_DE_SAC; 

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 27
        robotState.distanceTelemetreGauche < gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 < droit2) 
        obstacle = OBSTACLE_SUR_LA_DROITE;

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 28
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre < centre &&
        robotState.distanceTelemetreDroit < droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_SUR_LA_GAUCHE; 


        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 29
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 < droit2) 
        obstacle = OBSTACLE_A_DROITE; 

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 30
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = OBSTACLE_A_GAUCHE; 

        else if ( robotState.distanceTelemetreGauche2 < gauche2 && //cas n° 31 (à enlever ?)
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 < droit2) 
        obstacle = PAS_D_OBSTACLE; 

        else if ( robotState.distanceTelemetreGauche2 > gauche2 && //cas n° 32
        robotState.distanceTelemetreGauche > gauche &&
        robotState.distanceTelemetreCentre > centre &&
        robotState.distanceTelemetreDroit > droit &&
        robotState.distanceTelemetreDroit2 > droit2) 
        obstacle = PAS_D_OBSTACLE;
        
        return obstacle;
}