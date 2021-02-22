#ifndef MAIN_H
#define	MAIN_H

#define FCY 4000000

extern unsigned char positionObstacle;
extern unsigned char stateRobot;
extern unsigned char nextStateRobot=0;
void OperatingSystemLoop(void);
void SetNextRobotStateInAutomaticMode(void);
#endif