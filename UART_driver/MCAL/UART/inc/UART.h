/*
 * UART.h
 *
 * Created: 8/30/2023
 *  Author: Mohamed Abdelsamie
 */ 

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "UART_Cfg.h"
#include "BitMath.h"


/*******************************************************************************
 *                      Function Prototypes                                   *
 *******************************************************************************/

/*
 *	Description :
 *	Initialization function for the UART device by:
 *	Re-entrance: Non re-entrant
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Function to send a byte to another UART device.
 */
void UART_sendByte(const uint8_t data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8_t UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8_t *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8_t *Str); // Receive until #

/*
 * Description :
 * Enable the transmission interrupt
 * Re-entrance: Non re-entrant
 */
void UART_enableTX_IE(void);

/*
 * Description :
 * Disable the transmission interrupt
 * Re-entrance: Non re-entrant
 */
void UART_disableTX_IE(void);

/*
 * Description :
 * Enable the receiving interrupt
 * Re-entrance: Non re-entrant
 */
void UART_enableRX_IE(void);

/*
 * Description :
 * Disable the receiving interrupt
 * Re-entrance: Non re-entrant
 */
void UART_disableRX_IE(void);

/*
 * Description :
 * Set baud rate of USART
 * Re-entrance: re-entrant
 */
void UART_setBaudRate(uint16_t baudrate);

/*
 * Description :
 * Set call back of USART
 * Re-entrance: re-entrant
 */
void USART_setCallback(void (*ptr)(uint8_t));

#endif /* UART_H_ */