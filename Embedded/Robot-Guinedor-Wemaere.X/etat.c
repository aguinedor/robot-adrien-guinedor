#include "etat.h"
#include <xc.h>
#include "main.h"

#define PAS_D_OBSTACLE 0
#define OBSTACLE_A_GAUCHE 1 
#define OBSTACLE_SUR_LA_GAUCHE 2  //tourne sur place vers la droite
#define OBSTACLE_A_DROITE 3
#define OBSTACLE_SUR_LA_DROITE 4 //tourne sur place vers la gauche
#define OBSTACLE_EN_FACE 5 //recule et tourne sur place vers la gauche

unsigned char positionObstacle = PAS_D_OBSTACLE;

void etat(int gauche,int centre,int droite)
{
        if ( robotState.distanceTelemetreGauche2 >30  && //cas n° 0
     robotState.distanceTelemetreGauche >30  &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = PAS_D_OBSTACLE

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 1
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_A_GAUCHE  

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 2
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_A_GAUCHE  

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 3
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_SUR_LA_DROITE 

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 4
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_A_DROITE 

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 5
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_A_DROITE 

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 6
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_SUR_LA_DROITE

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 7 
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_SUR_LA_DROITE

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 8
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_EN_FACE 

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 9 (à enlever ?)
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = PAS_D_OBSTACLE 

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 10
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_A_GAUCHE  

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 11
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_SUR_LA_GAUCHE

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 12
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_SUR_LA_DROITE

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 13
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_A_DROITE

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 14
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_SUR_LA_DROITE  

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 15
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_SUR_LA_GAUCHE

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 16
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_EN_FACE

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 17
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_SUR_LA_GAUCHE 

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 18
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_SUR_LA_DROITE 

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 19
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_EN_FACE

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 20
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_EN_FACE

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 21
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_SUR_LA_DROITE

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 22
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_SUR_LA_GAUCHE 

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 23
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_EN_FACE

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 24
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_SUR_LA_GAUCHE 

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 25
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_SUR_LA_DROITE

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 26
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_SUR_LA_DROITE

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 27
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_SUR_LA_GAUCHE 

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 28
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_EN_FACE 

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 29
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre > 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_EN_FACE 

     else if ( robotState.distanceTelemetreGauche2 > 30 && //cas n° 30
     robotState.distanceTelemetreGauche < 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit > 30 &&
     robotState.distanceTelemetreDroit2 < 30) 
     positionObstacle = OBSTACLE_SUR_LA_DROITE

     else if ( robotState.distanceTelemetreGauche2 < 30 && //cas n° 31
     robotState.distanceTelemetreGauche > 30 &&
     robotState.distanceTelemetreCentre < 20 &&
     robotState.distanceTelemetreDroit < 30 &&
     robotState.distanceTelemetreDroit2 > 30) 
     positionObstacle = OBSTACLE_SUR_LA_GAUCHE 
 
}