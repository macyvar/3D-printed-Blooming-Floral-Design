/**
* @file SSI2.h
*
* @brief Header file for the SSI2 driver (used with PMOD ALS).
*
* This file provides function declarations for initializing SSI2 peripheral
* and reading light intensity values from the PMOD ALS sensor module via SPI communication.
*
* @author Macy Varga
*/


#ifndef _SSI2_H_
#define _SSI2_H_


#include "TM4C123GH6PM.h"
#include <stdint.h>


/**
* @brief Initializes the SSI2 module.
*
* Configures GPIO pins PB4 (SCLK), PB5 (CS), PB6 (MISO) for SSI2 operation,
* and sets up SSI2 for 16-bit SPI Mode 0 communication at 1 MHz.
*
* @param None
*
* @return None
*/
void SSI2_Init(void);


/**
* @brief Reads the light intensity value from the PMOD ALS sensor.
*
* @param None
*
* @return uint8_t Light intensity value (8 bits).
*/
uint8_t PMOD_ALS_Read(void);


#endif // _SSI2_H_


