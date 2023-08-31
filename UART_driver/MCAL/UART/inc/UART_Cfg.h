/*
 * UART_Cfg.h
 *
 * Created: 8/30/2023
 *  Author: Mohamed Abdelsamie
 */ 

#ifndef UART_CFG_H_
#define UART_CFG_H_

#include "USART_Private.h"

/*******************************************************************************
 *								Definitions	                                   *
 *******************************************************************************/
/*
*	2 MODES
*	ASYNCHRONOUS
*	SYNCHRONOUS
*/
#define UART_MODE				ASYNCHRONOUS

/*	
*	3 MODES
*	TX_RX -> Transmitter and receiver mode
*	TX	-> Transmitter mode only
*	RX	-> Receiver mode only
*/
#define UART_TRANSMISSION_MODE	TX_RX

/*
*	2 MODES
*	IRQ_ENALBE -> enable uart interrupt
*	IRQ_DISABLE	-> disable uart interrupt
*/
#define UART_INTERRUPT_MODE		IRQ_DISABLE

#endif /* UART_CFG_H_ */