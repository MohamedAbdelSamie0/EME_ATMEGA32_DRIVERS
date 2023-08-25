/*
 * DIO.c
 *
 * Created: 8/17/2023 3:04:58 PM
 *  Author: Mohamed Abdelsamie
 */ 
#include "DIO.h"

void DIO_ReadPort(uint8_t Port, uint8_t* val)
{
	switch(Port)
	{
		case DIO_PORTA:
		*val = PINA;
		break;
		
		case DIO_PORTB:
		*val = PINB;
		break;
		
		case DIO_PORTC:
		*val = PINC;
		break;
		
		case DIO_PORTD:
		*val = PIND;
		break;
		
		default:
		/*do nothing*/
		break;
	}
}

void DIO_WritePort(uint8_t Port, uint8_t val)
{
	switch(Port)
	{
		case DIO_PORTA:
		PORTA = val;
		break;
		
		case DIO_PORTB:
		PORTB = val;
		break;
		
		case DIO_PORTC:
		PORTC = val;
		break;
		
		case DIO_PORTD:
		PORTD = val;
		break;
		
		default:
		/*do nothing*/
		break;
	}
}

void DIO_setPortDirection(uint8_t Port, uint8_t dir)
{
	switch(Port)
	{
		case DIO_PORTA:
		DDRA = dir;
		break;
		
		case DIO_PORTB:
		DDRB = dir;
		break;
		
		case DIO_PORTC:
		DDRC = dir;
		break;
		
		case DIO_PORTD:
		DDRD = dir;
		break;
		
		default:
		/*do nothing*/
		break;
	}
}

void DIO_setPinDirection(uint8_t Port, uint8_t pin, uint8_t dir)
{
	if( dir == DIO_PIN_OUTPUT)
	{
		switch(Port)
		{
			case DIO_PORTA:
			SetBit(DDRA, pin);
			break;
			
			case DIO_PORTB:
			SetBit(DDRB, pin);
			break;
			
			case DIO_PORTC:
			SetBit(DDRC, pin);
			break;
			
			case DIO_PORTD:
			SetBit(DDRD, pin);
			break;
			
			default:
			/*do nothing*/
			break;
		}
	}
	else if(dir == DIO_PIN_INPUT)
	{
		switch(Port)
		{
			case DIO_PORTA:
			ClearBit(DDRA, pin);
			break;
			
			case DIO_PORTB:
			ClearBit(DDRB, pin);
			break;
			
			case DIO_PORTC:
			ClearBit(DDRC, pin);
			break;
			
			case DIO_PORTD:
			ClearBit(DDRD, pin);
			break;
			
			default:
			/*do nothing*/
			break;
		}
	}
	else{
		/*do nothing*/
	}
}

void DIO_WritePin(uint8_t Port, uint8_t pin, uint8_t val)
{
	if(val)
	{
		switch(Port)
		{
			case DIO_PORTA:
			SetBit(PORTA, pin);
			break;
		
			case DIO_PORTB:
			SetBit(PORTB, pin);
			break;
		
			case DIO_PORTC:
			SetBit(PORTC, pin);
			break;
		
			case DIO_PORTD:
			SetBit(PORTD, pin);
			break;
		
			default:
			/*do nothing*/
			break;
		}
	}
	else
	{
		switch(Port)
		{
			case DIO_PORTA:
			ClearBit(PORTA, pin);
			break;
			
			case DIO_PORTB:
			ClearBit(PORTB, pin);
			break;
			
			case DIO_PORTC:
			ClearBit(PORTC, pin);
			break;
			
			case DIO_PORTD:
			ClearBit(PORTD, pin);
			break;
			
			default:
			/*do nothing*/
			break;
		}
	}
}

void DIO_ReadPin(uint8_t Port, uint8_t pin, uint8_t* val)
{
	switch(Port)
	{
		case DIO_PORTA:
		*val = GetBit(PORTA, pin);
		break;
		
		case DIO_PORTB:
		*val = GetBit(PORTB, pin);
		break;
		
		case DIO_PORTC:
		*val = GetBit(PORTC, pin);
		break;
		
		case DIO_PORTD:
		*val = GetBit(PORTD, pin);
		break;
		
		default:
		/*do nothing*/
		break;
	}
}

void DIO_SetPullUp(uint8_t Port ,uint8_t Pin)
{
	
	switch(Port)
	{
		case DIO_PORTA :
		SetBit(PORTA,Pin);
		break;
		
		case DIO_PORTB :
		SetBit(PORTB,Pin);
		break;
		
		case DIO_PORTC :
		SetBit(PORTC,Pin);
		break;
		
		case DIO_PORTD :
		SetBit(PORTD,Pin);
		break;
		
		default:
		break;
		
	}
}