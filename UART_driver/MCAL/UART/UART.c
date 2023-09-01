/*
 * UART.c
 *
 * Created: 8/30/2023
 *  Author: Mohamed Abdelsamie
 */ 

#ifndef F_CPU
	#define F_CPU	16000000UL
#endif

#include "UART.h"
#include <avr/interrupt.h>

void (*g_callBackPtr)(uint8_t) = (void*)0;	/*	pointer to function to set ISR for UART	*/

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 *	Description :
 *	Initialization function for the UART device; Asynchronus mode only for now
 *	Re-entrance: Non re-entrant
 */
void UART_init(const UART_ConfigType * Config_Ptr)
{
	#if UART_TRANSMISSION_MODE == TX_RX

		/************************** UCSRB Description **************************
		 * RXCIE = 1 Enable USART RX Complete Interrupt Enable
		 * TXCIE = 1 Enable USART TX Complete Interrupt Enable
		 * UDRIE = 1 Enable USART Data Register Empty Interrupt Enable
		 * RXEN  = 1 Receiver Enable
		 * RXB8 & TXB8 are read for the 9th bit in 9-bit data mode
		***********************************************************************/
		#if UART_INTERRUPT_MODE == IRQ_ENABLE
			USART_CTRLB_REG |= (1<<RXCIE_BIT) | (1<<TXCIE_BIT) | (1<<UDRIE_BIT) | (1<<RXEN_BIT) | (1<<TXEN_BIT);
			/*	UCSZ2_BIT = 1 For 9-bit data mode only, 0 for other	*/
			if(Config_Ptr->data_bits == Nine_bits)
			{
				SetBit(USART_CTRLB_REG, UCSZ2_BIT);
			}
			else
			{
				ClearBit(USART_CTRLB_REG, UCSZ2_BIT);
			}
			
		#elif UART_INTERRUPT_MODE == IRQ_DISABLE
		/************************** UCSRB Description **************************
		 * RXCIE = 0 Enable USART RX Complete Interrupt Enable
		 * TXCIE = 0 Enable USART TX Complete Interrupt Enable
		 * UDRIE = 0 Enable USART Data Register Empty Interrupt Enable
		 * RXEN  = 1 Receiver Enable
		 * RXEN  = 1 Transmitter Enable
		 * RXB8 & TXB8 are read for the 9th bit in 9-bit data mode
		***********************************************************************/
		/*	UCSZ2_BIT = 1 For 9-bit data mode only, 0 for other	*/
		if(Config_Ptr->data_bits == Nine_bits)
		{
			SetBit(USART_CTRLB_REG, UCSZ2_BIT);
		}
		else
		{
			//ClearBit(USART_CTRLB_REG, UCSZ2_BIT);
		}
		
			USART_CTRLB_REG |= (1<<RXEN_BIT) | (1<<TXEN_BIT);
		#endif
		
		#if UART_MODE == ASYNCHRONOUS
			USART_CTRLA_REG |= (1<<U2X_BIT);	/* U2X = 1 for double transmission speed */
			
			/************************** UCSRC Description **************************
			 * URSEL   = 1 The URSEL must be one when writing the UCSRC
			 * UMSEL   = 0 Asynchronous Operation
			 * UPM1:0  = 00 Disable parity bit
			 * USBS    = 0 One stop bit
			 * UCSZ1:0 = 11 For 8-bit data mode
			 * UCPOL   = 0 Used with the Synchronous operation only
			 ***********************************************************************/
			USART_CTRLC_REG |= (1 << URSEL_BIT) | (Config_Ptr->parity << UPM0_BIT) | (Config_Ptr->stop_bit << USBS_BIT);
			/*	UCSZ1:UCSZ0 = 11 For 9-bit AND 8-bit data mode only 0 for others	*/
			if(Config_Ptr->data_bits == Nine_bits)
			{
				SetBit(USART_CTRLC_REG, UCSZ1_BIT);
				SetBit(USART_CTRLC_REG, UCSZ0_BIT);
			}
			else
			{
				USART_CTRLC_REG |= (Config_Ptr->data_bits << UCSZ0_BIT);
			}
		#endif
		
	#endif
	
	/* call this function to set UART baudrate	*/
	UART_setBaudRate(Config_Ptr->baud_rate);
}

/*
 * Description :
 * Function to send a byte to another UART device.
 */
void UART_sendByte(uint8_t data)
{
	/*
	 * UDRE flag is set when the TX buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(GetBit(USART_CTRLA_REG,UDRE_BIT) == 0 );

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	USART_DATA_REG = data;
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8_t UART_recieveByte(void)
{	
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(USART_CTRLA_REG,RXC_BIT));

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return USART_DATA_REG;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(uint8_t *Str)
{
	uint8_t i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}		
	*******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8_t *Str)
{
	do 
	{
		*Str = UART_recieveByte();
	} while ((*(Str - 1) != ('\r' || '\n')));
	*(Str - 1) = '\0';

/*	ANOTHER IMPLEMENTATION	
	 Receive the first byte 
	Str[i] = UART_recieveByte();

	 Receive the whole string until the '\0' 
	while(Str[i] != '\r')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	 After receiving the whole string plus the '#', replace the '#' with '\0' 
	Str[i] = '\0';	
	*/
}

/*
 * Description :
 * Enable the transmission interrupt
 * Re-entrance: Non re-entrant
 */
void UART_enableTX_IE(void)
{
	SetBit(USART_CTRLB_REG, TXCIE_BIT);
}

/*
 * Description :
 * Disable the transmission interrupt
 * Re-entrance: Non re-entrant
 */
void UART_disableTX_IE(void)
{
	ClearBit(USART_CTRLB_REG, TXCIE_BIT);
}

/*
 * Description :
 * Enable the receiving interrupt
 * Re-entrance: Non re-entrant
 */
void UART_enableRX_IE(void)
{
	SetBit(USART_CTRLB_REG, RXCIE_BIT);
}

/*
 * Description :
 * Disable the receiving interrupt
 * Re-entrance: Non re-entrant
 */
void UART_disableRX_IE(void)
{
	ClearBit(USART_CTRLB_REG, RXCIE_BIT);
}

/*
 * Description :
 * Set baud rate of USART
 * Re-entrance: re-entrant
 */
void UART_setBaudRate(uint32_t baudrate)
{
	
	uint32_t BR = 16000000/baudrate ;
	/*	in asynchronous mode double transmission speed is used	*/
	#if UART_MODE == ASYNCHRONOUS
		BR /= 8;
	#else
		BR /= 16;
	#endif
	BR -= 1 ;
	
	
	//ubrr = (uint16_t)(ubrr);	/* round the value to get correct integer	*/
	
	if(BR < 255)
	{
		USART_BRL_REG = (uint8_t)(BR);
	}
	else
	{
		USART_BRH_REG = (uint8_t)(BR);
		USART_BRL_REG = 0x0F & ((uint8_t)BR >> 8);
	}
}

/*
 * Description :
 * Set call back of USART
 * Re-entrance: re-entrant
 */
void USART_setCallback(void (*ptr)(uint8_t))
{
	#if UART_TRANSMISSION_MODE == TX
		g_callBackPtr = *ptr;
	#else
		g_callBackPtr = *ptr;
	#endif
}

/*	USART ISR	*/
void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	if(g_callBackPtr!= (void*)0 )
	{
		g_callBackPtr(USART_DATA_REG);
	}
}