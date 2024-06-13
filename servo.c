#include <LPC21xx.H>
#include "led.h"
#include "timer_interrupts.h"
#include "servo.h"

#define DETECTOR_OUT 1<<10

enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo
{
	enum ServoState eState; 
	unsigned int uiCurrentPosition; 
	unsigned int uiDesiredPosition;
}; 

struct Servo sServo;
enum DetectorState {ACTIVE, INACTIVE};

void DetectorInit(){
	IODIR0&=~(DETECTOR_OUT);
}

enum DetectorState eReadDetector(){
	if(!(IO0PIN&(DETECTOR_OUT))) return ACTIVE;
	else return INACTIVE;
}

void Automat_2(){
	
	switch(sServo.eState){
		case(CALLIB):{
			if(eReadDetector()==ACTIVE){
				sServo.uiCurrentPosition=0; 
				sServo.uiDesiredPosition=0;
				sServo.eState=IDLE	;
			}
			else LedStepLeft();
			break;
			}
		case(IDLE):{
			if(sServo.uiCurrentPosition!=sServo.uiDesiredPosition)	sServo.eState=IN_PROGRESS;
			else sServo.eState=IDLE;
			break;
		}
		case(IN_PROGRESS):{
			if(sServo.uiCurrentPosition<sServo.uiDesiredPosition){
				LedStepRight();
				sServo.uiCurrentPosition++;
			}
			else if(sServo.uiCurrentPosition>sServo.uiDesiredPosition){
				LedStepLeft();
				sServo.uiCurrentPosition--;
			}
			else sServo.eState=IDLE;
			break;	
		}
	}
}

void ServoInit(unsigned int uiServoFrequency){
	LedInit();
	DetectorInit();
	Timer0Interrupts_Init(uiServoFrequency,&Automat_2);
}

void ServoCallib(){
	sServo.eState=CALLIB;
}

void ServoGoTo(unsigned int uiPosition){
	sServo.uiDesiredPosition=uiPosition;	
}

	