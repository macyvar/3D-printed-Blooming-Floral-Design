/**
* @file PMOD_BTN_Interrupt.h
*
* @brief Header file for the PMOD_BTN_Interrupt driver.
*
* This file contains the function declarations for the PMOD_BTN_Interrupt driver.
* It interfaces with the PMOD BTN module using GPIO Port A pins (PA2 - PA5),
* and sets up interrupts on rising edges to detect button presses.
*
* @author Macy Varga
*/


#ifndef _PMOD_BTN_INTERRUPT_H_
#define _PMOD_BTN_INTERRUPT_H_


#include "TM4C123GH6PM.h"


/**
* @brief Pointer to the user-defined task function called on PMOD BTN interrupt.
*
* @param pmod_btn_state 8-bit unsigned integer representing button status.
*/
extern void (*PMOD_BTN_Task)(uint8_t pmod_btn_state);


/**
* @brief Initializes the PMOD BTN interrupts on Port A.
*
* Configures PA2-PA5 as GPIO inputs, enables pull-down resistors,
* and sets up interrupts on rising edges. Sets interrupt priority and enables IRQ.
*
* @param task Function pointer to the user-defined handler function.
*
* @return None
*/
void PMOD_BTN_Interrupt_Init(void(*task)(uint8_t));


/**
* @brief Reads the current button status of the PMOD BTN module.
*
* @param None
*
* @return uint8_t Current status of buttons (active-high).
*/
uint8_t PMOD_BTN_Read(void);


/**
* @brief Interrupt Service Routine for Port A (PMOD BTN interrupt handling).
*
* Checks which button triggered the interrupt, calls the user task, and clears the interrupt flag.
*
* @param None
*
* @return None
*/
void GPIOA_Handler(void);


#endif // _PMOD_BTN_INTERRUPT_H_




