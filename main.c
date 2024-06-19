#include <LPC21xx.H>

#include "uart.h"
#include "servo.h"
#include "command_decoder.h"
#include "string.h"
#include "timer_interrupts.h"

#define NULL '\0'

struct Token asToken[MAX_TOKEN_NR];
unsigned char ucTokenNr;

struct Watch {
	unsigned char ucMinutes;
	unsigned char ucSecconds;
	unsigned char fSeccondsValueChanged; 
	unsigned char fMinutesValueChanged;
};

struct Watch sWatch = {0,0,0,0};

void WatchUpdate(){
	sWatch.ucSecconds++;
	sWatch.fSeccondsValueChanged=1;
	if(sWatch.ucSecconds==59){
		sWatch.ucSecconds=0;
		sWatch.ucMinutes++;
		sWatch.fMinutesValueChanged=1;
	}
}

struct Calc {
	char cCalcBuffer[RECEIVER_SIZE];
	unsigned char fCalcDone;
	unsigned int uiCalcValue;
};

struct Calc sCalc = {"",0,0};

int main(){
	
	unsigned char fUnknownMessage=0;
	unsigned char fIdIdentifier=0;
	unsigned char fClearRequest=0;
	char cTransmiterString[20];
	Timer0Interrupts_Init(1000000,WatchUpdate);
	UART_InitWithInt(9600);
	
	while(1){
		if(eReciever_GetStatus() == READY){
			Reciever_GetStringCopy(sCalc.cCalcBuffer);
			DecodeMsg(sCalc.cCalcBuffer);
			if((ucTokenNr>0)&&(asToken[0].eType==KEYWORD)){
				switch(asToken[0].uValue.eKeyword){
					case(CALC):{
						sCalc.uiCalcValue=2*asToken[1].uValue.uiNumber;
						sCalc.fCalcDone=1;
						break;
					}
					case(ID):{
						fIdIdentifier=1;
						break;
					}
					case(CLEAR):{
						fClearRequest=1;
						break;
					}
					default:
						fUnknownMessage=1;
						break;
				}
			}
			else{
				fUnknownMessage=1;
			}
		}
		
		if(Transmiter_GetStatus() == FREE){
			if(fClearRequest==1){
				CopyString("\n\x1b[2J",cTransmiterString);
				Transmiter_SendString(cTransmiterString);
				fClearRequest=0;
			}	
			if(fUnknownMessage==1){
				CopyString("\nunknownmessage",cTransmiterString);
				Transmiter_SendString(cTransmiterString);
				fUnknownMessage=0;
			}
			else if(fIdIdentifier==1){
				CopyString("\nID Servo",cTransmiterString);
				Transmiter_SendString(cTransmiterString);
				fIdIdentifier=0;
			}
			if(sCalc.fCalcDone==1){
				CopyString("\ncalc ",cTransmiterString);
				AppendUIntToString(sCalc.uiCalcValue,cTransmiterString);
				Transmiter_SendString(cTransmiterString);
				sCalc.fCalcDone=0;
			}
			else if(sWatch.fMinutesValueChanged==1){
				CopyString("\nmin ",cTransmiterString);
				AppendUIntToString(sWatch.ucMinutes,cTransmiterString);
				Transmiter_SendString(cTransmiterString);
				sWatch.fMinutesValueChanged=0;
			}
			else if(sWatch.fSeccondsValueChanged==1){
				CopyString("\nsec ",cTransmiterString);
				AppendUIntToString(sWatch.ucSecconds,cTransmiterString);
				Transmiter_SendString(cTransmiterString);
				sWatch.fSeccondsValueChanged=0;
			}
		}
	}
}

//ID i unknowncommand