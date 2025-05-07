/**
 * @file main.c
 *
 * @brief Main application entry point.
 *
 * This file demonstrates the use of either the PMOD BTN or PMOD ALS (SSI2) 
 * module on the TM4C123G LaunchPad to control a servo via PWM. Only one
 * module should be enabled at a time using the corresponding macro.
 *
 * @author Macy Varga
 */

#include "PWM1_3.h"
#include "SysTick_Delay.h"
#include "TM4C123GH6PM.h"
#include "GPIO.h"


// Uncomment one of the following to select the active module:
// dont forget under project ->Target 1-> C/C++-> Define USE_PMOD_ALS or USE_PMOD_BTN
//#define USE_PMOD_BTN
 #define USE_PMOD_ALS


#ifdef USE_PMOD_BTN
#include "PMOD_BTN_Interrupt.h"
#endif

#ifdef USE_PMOD_ALS
#include "SSI2.h"
#endif



//(used if PMOD_BTN interrupts are active)
volatile uint8_t move_servo = 0;

#ifdef USE_PMOD_BTN
/**
 * @brief Handler function for PMOD BTN interrupts.
 *
 * This function is triggered when a button on the PMOD BTN module is pressed.
 * It adjusts the PWM duty cycle based on which button is pressed.
 *
 * @param pmod_btn_status Status of the PMOD BTN input (bits PA2-PA5).
 */
void PMOD_BTN_Handler(uint8_t pmod_btn_status)
{
    switch (pmod_btn_status)
    {
        case 0x04: // BTN0 (PA2)
            PWM1_3_SetDuty(1875);
            break;

        case 0x08: // BTN1 (PA3)
            PWM1_3_SetDuty(3590); // 90 degrees
            break;

        case 0x10: // BTN2 (PA4)
            PWM1_3_SetDuty(0);
            break;

        case 0x20: // BTN3 (PA5)
            // No action defined
            break;

        default:
            break;
    }
}
#endif

int main(void)
{
    SysTick_Delay_Init();
    PWM1_3_Init(62500, 1875); // 50Hz PWM, start at 0 degrees
    EduBase_LEDs_Init();     // Optional: Visual feedback

#ifdef USE_PMOD_BTN
    PMOD_BTN_Interrupt_Init(&PMOD_BTN_Handler);
#endif

#ifdef USE_PMOD_ALS
    SSI2_Init();


#endif

    while (1)
    {
#ifdef USE_PMOD_ALS
        uint8_t light_level = PMOD_ALS_Read();
			EduBase_LEDs_Output(light_level >> 4); // Visualize light level on LEDs


        if (light_level > 100)
        {
            PWM1_3_SetDuty(1875); // down
        }
        else
        {
            PWM1_3_SetDuty(9599); // up
        }

        SysTick_Delay1ms(300); // Delay 300ms
#endif

#ifdef USE_PMOD_BTN
        // All logic handled in ISR, loop can be idle or extended
#endif
    }
}

