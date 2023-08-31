/*
 * UART.c
 *
 * Created: 8/30/2023
 * Author : Mohamed Abdelsamie
 */ 

#include "UART.h"
#include "Atmega32_Registers.h"
volatile uint8_t buffer[10];
volatile uint8_t uart_flag = 0;

void uart_callback(uint8_t data)
{
	static uint32_t buffer_idx = 0;
	buffer[buffer_idx] = data;
	
	if(buffer_idx ==(sizeof(buffer) / sizeof(buffer[0])-1) || buffer[buffer_idx] == '\n' || buffer[buffer_idx] == '\r')
	{
		buffer[buffer_idx] = '\0';
		buffer_idx = 0;
		uart_flag = 1;
	}
	else
	{
		buffer_idx++;
	}
}

UART_ConfigType USART_CONFIGURATION;
int main(void)
{
	uint8_t *str_test = 0;
	USART_CONFIGURATION.baud_rate = 9600;
	USART_CONFIGURATION.data_bits = Eight_bits;
	USART_CONFIGURATION.parity = Disable;
	USART_CONFIGURATION.stop_bit = one_bit;
	
	UART_init(&USART_CONFIGURATION);
	
	USART_setCallback(uart_callback);
	
	SetBit(SREG, 7);	/* enable global interrupts	*/
    /* Replace with your application code */
    while (1) 
    {
		UART_receiveString(str_test);
		
		UART_sendString(str_test);
    }
	return 0;
}
