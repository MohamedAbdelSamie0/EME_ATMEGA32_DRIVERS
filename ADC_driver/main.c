/*
 * ADC1.c
 *
 * Created: 8/24/2023 12:45:09 PM
 * Author : Mohamed Abdelsamie
 */ 

#include "ADC.h"
#include "LCD.h"
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

uint16_t A_in;
uint8_t g_readFlag;

int main(void)
{
    /* Replace with your application code */
	
	uint8_t string[5];
	//uint16_t* x;
	DIO_setPinDirection(DIO_PORTA, DIO_PIN0, PIN_INPUT);
	
	ADC_init();
	LCD_init();
	LCD_Clear();

    while (1) 
    {
		LCD_WriteString((uint8_t*)"ADC value: ");
		LCD_moveCursor(0, 11);
		ADC_read(ADC0_CHANNEL, &A_in);
		itoa(A_in, string, 10);
		LCD_WriteString(string);
		_delay_ms(1000);
		LCD_Clear();
    }
	return 0;
}

#if ADC_MODE == INTERRUPT_MODE
/*
 * Interrupt service routine for the ADC interrupt
 * 
 */ 
ISR(ADC_vect)
{
	//g_readFlag = 1;		/*	Set the read flag to indicate that ADC conversion is complete	*/
	A_in = (ADCL_REG | ((ADCH_REG & 0x03) << 8) );	/*	Read lower byte and higher 2 bits then left shift them by 8	*/
	
	/*	clear ADIF flag	*/
	SetBit(ADC_CTRL_REG, ADC_IF_BIT);
}
#endif