/**
* @file PWM1_3.h
*
* @brief Header file for the PWM1_3 driver.
*
* This file contains function declarations for controlling PWM Generator 3
* on PWM Module 1 for use with a servo motor connected to PF2 (M1PWM6).
* It provides initialization and dynamic duty cycle adjustment functions.
*
* @author Macy Varga
*/


#ifndef _PWM1_3_H_
#define _PWM1_3_H_


#include <stdint.h>


/**
* @brief Initializes PWM Generator 3 on Module 1.
*
* Sets up PF2 for PWM output, configures the PWM clock and generator behavior.
*
* @param period_constant The total period value for the PWM signal.
* @param duty_cycle The initial duty cycle value for the PWM signal.
*
* @return None
*/
void PWM1_3_Init(uint16_t period_constant, uint16_t duty_cycle);


/**
* @brief Updates the duty cycle of the PWM signal.
*
* @param duty_cycle New duty cycle value to be loaded into the generator.
*
* @return None
*/
void PWM1_3_SetDuty(uint16_t duty_cycle);


#endif // _PWM1_3_H_


