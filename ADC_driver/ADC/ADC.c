/*
 * ADC.c
 *
 * Created: 8/24/2023 10:18:26 AM
 *  Author: Mohamed Abdelsamie
 */ 

#include "ADC.h"

#ifndef F_CPU
#define F_CPU	16000000UL
#endif

#include <util/delay.h>

/*
 * function name: ADC_init
 *
 * input params: NONE
 * output params: NONE
 */ 
void ADC_init()
{	
	SetBit(ADC_CTRL_REG, ADC_ENABLE_BIT);	/*	ENABLE ADC	*/
	
	#if ADC_MODE == INTERRUPT_MODE
		
		SetBit(SREG, 7);			/*	enable global interrupts	*/
	
		SetBit(ADC_CTRL_REG, ADC_IE_BIT);	/*	enable ADC interrupts	*/
	
	#endif
	
	DIO_setPortDirection(ADC0_PORT_ID, PORT_INPUT);	/*	MAKE ADC PORT INPUT	*/
	
	ADC_MUX_REG |= (1 << 6);	/*	AVcc, right adjust, ADC0	*/
		
	ADC_CTRL_REG |= ADC_PRE_FACTOR;	/*	prescaler of 128	*/
	
}

/*
 * function name: ADC_read
 *
 * input params: 
 * output params: va; converted analouge value
 */ 
void ADC_read(uint8_t channel, uint16_t* val)
{
	/*	clear precious channel read	*/
	ADC_MUX_REG &= 0xF0;
	
	/*	set new +input channel to read	*/
	ADC_MUX_REG |= (channel);
	
	/*	start conversion	*/
	SetBit(ADC_CTRL_REG, ADC_SC_BIT);

	#if ADC_MODE == POLLING_MODE
		/*	polling on interrupt flag	*/
		while( BIT_IS_CLEAR(ADC_CTRL_REG, ADC_IF_BIT) );
	#endif
	_delay_ms(10);
	
	*val = (ADCL_REG | ((ADCH_REG & 0x03) << 8) );	/*	Read lower byte and higher 2 bits then left shift them by 8	*/
		
	/*	clear ADIF flag	*/
	SetBit(ADC_CTRL_REG, ADC_IF_BIT);
	
	//return A_in;
}