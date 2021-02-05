#ifndef MAIN_H
#define	MAIN_H

#define FCY 4000000

int main(void);
void OperatingSystemLoop(void);
unsigned char stateRobot;
unsigned char nextStateRobot=0;
void SetNextRobotStateInAutomaticMode();
#endif