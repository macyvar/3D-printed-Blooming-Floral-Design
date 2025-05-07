/**
* @file PWM1_3.c
*
* @brief Source file for the PWM1_3 driver.
*
* This file contains the function implementations for controlling PWM Generator 3
* on PWM Module 1. It provides functionality to initialize PWM on PF2 (M1PWM6)
* and adjust the duty cycle to control devices like servo motors.
*
* @author Macy Varga
*/


#include "PWM1_3.h"
#include "TM4C123GH6PM.h"


//Initialize the PWM Generator 3 on Module 1 for use with PF2 as output (M1PWM6)
void PWM1_3_Init(uint16_t period, uint16_t duty)
 {
   if (duty >= period) return;
   //Enable PWM1
   SYSCTL->RCGCPWM |= (1 << 1);        
   //Enable clock for PortF
   SYSCTL->RCGCGPIO |= (1 << 5);
  
  
   //Use PWM divider
   SYSCTL->RCC |= 0x00100000;          
   SYSCTL->RCC &= ~0x000E0000;
   //Sets the PWM clock divider by writing 0x3 to the PWMDIV field (Bits 19-17) in the RCC.
   // That divides the system clock by 64, givinga PWM clock of 3.125 MHz assuming a base of 200MHz
   SYSCTL->RCC |= 0x00060000;         


  
   // Enables alternate fn mode on PF2 , required for PWM functionality (M1PWM6).
   //Bit 2 corresponds to PF2
   GPIOF->AFSEL |= (1 << 2);    
   //Clears the bits 11:8 in the PCTL for PF2
   //Selects the alt fn for that pin
   GPIOF->PCTL &= ~0x00000F00;
   //sets bits 11:8 in PCTL to 0x5, selecting the M1PWM6 function (PF2's PWM
   //function) according to the datasheet
   GPIOF->PCTL |= 0x00000500;
   //Digitally enables PF2 so it can output signals, including the PWM wave
   GPIOF->DEN |= (1 << 2);


   // Disable generator
   PWM1->_3_CTL = 0;    
   // config the output behavior: output is HIGH on LOAD and LOW on
   //CMPA down count. This sets up a standard PWM waveform
   PWM1->_3_GENA |= 0x000000C8;     
   //Sets the total period of the PWM signal (used to get 50Hz). LOAD-1 is
   //required because the timer counts from LOAD to 0   
   PWM1->_3_LOAD = period - 1;
   //pulse width (duty cycle). The output will go low when the counter
   // reaches CMPA
   PWM1->_3_CMPA = duty - 1;
   // Enable generator
   PWM1->_3_CTL |= 0x01;
   // Enables PWM output on M1PWM6 (PF2). Bit 6 corresponds to PWM1 
   //output 6. 
   PWM1->ENABLE |= (1 << 6);           
}


// Updates the duty cycle for PWM without reinitializing the whole PWM module
void PWM1_3_SetDuty(uint16_t duty)
{
   // duty value doesn't exceed the period; PWM would not function correctly
   //if this check fails
   PWM1->_3_CMPA = duty - 1;
}


