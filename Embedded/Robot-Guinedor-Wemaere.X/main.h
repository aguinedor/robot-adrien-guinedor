#ifndef MAIN_H
#define	MAIN_H

#define FCY 40000000

void OperatingSystemLoop(void);
void SetNextRobotStateInAutomaticMode(void);
void SetRobotState(unsigned char RobotState);
void SetRobotAutoControlState(unsigned char SetRobotState);
void SendInfos(void);
extern unsigned char ModeAuto;

#endif