/**
 * @file SSI2.c
 *
 * @brief Source file for the SSI2 driver.
 *
 * This file contains the function implementations for configuring the SSI2
 * SPI peripheral to communicate with external SPI devices like the PMOD ALS
 * light sensor module. It includes initialization and sensor data reading functions.
 *
 * @author Macy Varga
 */

#ifdef USE_PMOD_ALS

#include "SSI2.h"

void SSI2_Init(void)
{
    SYSCTL->RCGCSSI |= (1 << 2);    // Enable SSI2 clock
    SYSCTL->RCGCGPIO |= (1 << 1);   // Enable Port B clock

    volatile int delay = SYSCTL->RCGCGPIO; // small delay for clock ready

    // Configure SCLK (PB4) and MISO (PB6) for alternate function
    GPIOB->AFSEL |= (1 << 4) | (1 << 6);  // Enable alt fn on PB4, PB6
    GPIOB->PCTL &= ~0x0F0F0000;           // Clear PCTL for PB4, PB6
    GPIOB->PCTL |= 0x02020000;           // Set SSI2 function
    GPIOB->DEN |= (1 << 4) | (1 << 6);   // Enable digital for PB4, PB6
    GPIOB->AMSEL &= ~((1 << 4) | (1 << 6)); // Disable analog

    // Configure CS (PB5) as GPIO output (manual control)
    GPIOB->AFSEL &= ~(1 << 5); // Remove alt fn for PB5
    GPIOB->DIR |= (1 << 5);    // Set PB5 as output
    GPIOB->DEN |= (1 << 5);    // Enable digital function for PB5
    GPIOB->DATA |= (1 << 5);   // Deassert CS (active low)

    // Configure SSI2 module
    SSI2->CR1 &= ~0x02;     // Disable SSI during setup
    SSI2->CR1 &= ~0x04;     // Master mode
    SSI2->CC = 0x0;         // Use system clock
    SSI2->CPSR = 100;       // SPI clock = system / 100 = 500 kHz
    SSI2->CR0 = 0x0F;       // 16-bit data, SPI Mode 0 (CPOL=0, CPHA=0)
    SSI2->CR1 |= 0x02;      // Enable SSI2
}

uint8_t PMOD_ALS_Read(void)
{
    // Assert CS (active low)
    GPIOB->DATA &= ~(1 << 5);

    // Write dummy data to generate clock
    while ((SSI2->SR & 0x02) == 0); // Wait until TX FIFO not full
    SSI2->DR = 0xAAAA;              // Dummy data

    // Wait for data to be received
    while ((SSI2->SR & 0x04) == 0); // Wait until RX FIFO not empty
    uint16_t als_raw = SSI2->DR;

    // Deassert CS
    GPIOB->DATA |= (1 << 5);

    // Extract 8-bit light value (bits 5–12)
    uint8_t light_level = (als_raw >> 5) & 0xFF;

    return light_level;
}

#endif // USE_PMOD_ALS