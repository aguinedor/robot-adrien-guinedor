#ifndef MAIN_H
#define	MAIN_H

#define FCY 4000000
int a,b,c,m,v; // distance pour les telemetres (a-b-c) et vitesses (manoeuvre, moyenne, croisière)

void OperatingSystemLoop(void);
void SetNextRobotStateInAutomaticMode(void);
#endif