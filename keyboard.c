#include <LPC21xx.H>
#include "keyboard.h"

#define BUTTON_0_bm 		(1<<4) 
#define BUTTON_1_bm 		(1<<5)
#define BUTTON_2_bm 		(1<<6)
#define BUTTON_3_bm 		(1<<7)

void KeyboardInit(){
		IO0DIR&=~(BUTTON_0_bm | BUTTON_1_bm | BUTTON_2_bm | BUTTON_3_bm);
	}

enum ButtonState ReadButton1(){
	if(IO0PIN&BUTTON_0_bm){
			return RELEASED;
		}
		else{
			return PRESSED;
		}
	}	

enum KeyboardState eKeyboardRead(){
		if((IO0PIN&BUTTON_0_bm)==0){
			return BUTTON_0;
		}
		
		else if((IO0PIN&BUTTON_1_bm)==0){
			return BUTTON_1;
		}
		
		else if((IO0PIN&BUTTON_2_bm)==0){
			return BUTTON_2;
		}
		
		else if((IO0PIN&BUTTON_3_bm)==0){
			return BUTTON_3;
		}
		
		else return RELASED;
	}
