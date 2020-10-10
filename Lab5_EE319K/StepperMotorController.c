// StepperMotorController.c starter file EE319K Lab 5
// Runs on TM4C123
// Finite state machine to operate a stepper motor.  
// Jonathan Valvano
// 1/17/2020

// Hardware connections (External: two input buttons and four outputs to stepper motor)
//  PA5 is Wash input  (1 means pressed, 0 means not pressed)
//  PA4 is Wiper input  (1 means pressed, 0 means not pressed)
//  PE5 is Water pump output (toggle means washing)
//  PE4-0 are stepper motor outputs 
//  PF1 PF2 or PF3 control the LED on Launchpad used as a heartbeat
//  PB6 is LED output (1 activates external LED on protoboard)

#include "SysTick.h"
#include "TExaS.h"
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

void EnableInterrupts(void);
// edit the following only if you need to move pins from PA4, PE3-0      
// logic analyzer on the real board
#define PA4       (*((volatile unsigned long *)0x40004040))
#define PE50      (*((volatile unsigned long *)0x400240FC))
void SendDataToLogicAnalyzer(void){
  UART0_DR_R = 0x80|(PA4<<2)|PE50;
}

void port_init(){
	SYSCTL_RCGCGPIO_R |= 0x11;	
	volatile int delay = 0;
	GPIO_PORTE_DIR_R |= 0x1F;
	GPIO_PORTE_DEN_R |= 0x1F;	//setting port e4-0 to output
	
	GPIO_PORTA_DIR_R |= 0x10;
	GPIO_PORTA_DEN_R |= 0x10;	//setting port a4 to input
}

int main(void){ 
  TExaS_Init(&SendDataToLogicAnalyzer);    // activate logic analyzer and set system clock to 80 MHz
  SysTick_Init();   
	port_init();
	
  EnableInterrupts();   
  while(1){
		if((GPIO_PORTA_DATA_R & 0x00000010) == 0x10){
			GPIO_PORTE_DATA_R |= 0x05;
			SysTick_Wait1ms(100);
			
			GPIO_PORTE_DATA_R |= 0x06;
			SysTick_Wait1ms(100);
			
			GPIO_PORTE_DATA_R |= 0x0A;
			SysTick_Wait1ms(100);
			
			GPIO_PORTE_DATA_R |= 0x09;
			SysTick_Wait1ms(100);
		}
  }
}


