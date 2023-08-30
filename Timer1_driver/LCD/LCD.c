/*
 * LCD.c
 *
 * Created: 8/18/2023 9:58:00 AM
 *  Author: Mohamed Abdelsamie
 */ 

#include "LCD.h"
#include <stdlib.h>
#define F_CPU							16000000UL
#include <util/delay.h>

void LCD_init(void)
{
	#if (LCD_MODE == 4)

	/* Configure the direction for RS and E pins as output pins */
	DIO_setPinDirection(LCD_4BIT_CMD_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	DIO_setPinDirection(LCD_4BIT_CMD_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);
	
	/* Configure the data port as output port */
	DIO_setPortDirection(LCD_4BIT_DATA_PORT_ID, PORT_OUTPUT);
	
	_delay_ms(20);		/* LCD Power ON delay always > 15ms */
	
	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_WriteCommand(LCD_TWO_LINES_4_BITS_MODE);
	LCD_WriteCommand(LCD_CURSOR_ON_BLINK); /* cursor on and blinking */
	LCD_WriteCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
	
	#elif (LCD_MODE == 8)
	
	/* Configure the direction for RS and E pins as output pins */
	DIO_setPinDirection(LCD_8BIT_CMD_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	DIO_setPinDirection(LCD_8BIT_CMD_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);
	
	/* Configure the data port as output port */
	DIO_setPortDirection(LCD_8BIT_DATA_PORT_ID, PORT_OUTPUT);
	
	_delay_ms(20);		/* LCD Power ON delay always > 15ms */
	
	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_WriteCommand(LCD_TWO_LINES_8_BITS_MODE);
	LCD_WriteCommand(LCD_CURSOR_ON_BLINK); /* cursor on and blinking */
	LCD_WriteCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
	
	#endif
}

void LCD_WriteCommand(uint8_t cmd)
{
	uint8_t BIT4 = 0;
	DIO_WritePin(LCD_4BIT_CMD_PORT_ID, LCD_RS_PIN_ID, PIN_LOW);
	DIO_WritePin(LCD_4BIT_CMD_PORT_ID, LCD_E_PIN_ID, PIN_LOW);
	//DIO_WritePin(LCD_4BIT_DATA_PORT_ID, LCD_RW_PIN_ID, PIN_HIGH);
	
	/*	Normal implementation	*/
	/*	PORTB = (cmd & 0x0F) | (PORTB & 0xF0);	*/
	
	/*	HARDWARE RESTRICTIONS	*/
	PORTB = ( (cmd >> 4) & 0x07 ) | ( PORTB & 0xF8 );	/*	0x07 = 0000 0111  ,  0xF8 = 1111 1000	*/
	
	BIT4 = GetBit(cmd, 7);
	if(BIT4)
	{
		SetBit(PORTB, LCD_D7);
	}else
	{
		ClearBit(PORTB, LCD_D7);
	}

	DIO_WritePin(LCD_4BIT_CMD_PORT_ID, LCD_E_PIN_ID, PIN_HIGH);
	_delay_ms(5);
	DIO_WritePin(LCD_4BIT_CMD_PORT_ID, LCD_E_PIN_ID, PIN_LOW);
	
	
	PORTB = ( (cmd) & 0x07 ) | ( PORTB & 0xF8 );	/*	0x07 = 0000 0111  ,  0xF8 = 1111 1000	*/
	
	BIT4 = GetBit(cmd, 3);
	if(BIT4)
	{
		SetBit(PORTB, LCD_D7);
	}else
	{
		ClearBit(PORTB, LCD_D7);
	}
	
	DIO_WritePin(LCD_4BIT_CMD_PORT_ID, LCD_E_PIN_ID, PIN_HIGH);
	_delay_ms(5);
	DIO_WritePin(LCD_4BIT_CMD_PORT_ID, LCD_E_PIN_ID, PIN_LOW);
}

void LCD_WriteChar(uint8_t chr)
{
	uint8_t BIT4 = 0;
	DIO_WritePin(LCD_4BIT_CMD_PORT_ID, LCD_RS_PIN_ID, PIN_HIGH);
	DIO_WritePin(LCD_4BIT_CMD_PORT_ID, LCD_E_PIN_ID, PIN_LOW);
	DIO_WritePin(LCD_4BIT_CMD_PORT_ID, LCD_RW_PIN_ID, PIN_LOW);
	
	/*	Normal implementation	*/
	/*	PORTB = (cmd & 0x0F) | (PORTB & 0xF0);	*/
	
	/*	HARDWARE RESTRICTIONS	*/
	PORTB = ( (chr >> 4) & 0x07 ) | ( PORTB & 0xF8 );	/*	0x07 = 0000 0111  ,  0xF8 = 1111 1000	*/
	
	BIT4 = GetBit(chr, 7);
	if(BIT4)
	{
		SetBit(PORTB, LCD_D7);
	}else
	{
		ClearBit(PORTB, LCD_D7);
	}
	
	DIO_WritePin(LCD_4BIT_CMD_PORT_ID, LCD_E_PIN_ID, PIN_HIGH);
	_delay_ms(5);
	DIO_WritePin(LCD_4BIT_CMD_PORT_ID, LCD_E_PIN_ID, PIN_LOW);
	
	PORTB = ( (chr) & 0x07 ) | ( PORTB & 0xF8 );	/*	0x07 = 0000 0111  ,  0xF8 = 1111 1000	*/
	
	BIT4 = GetBit(chr, 3);
	if(BIT4)
	{
		SetBit(PORTB, LCD_D7);
	}else
	{
		ClearBit(PORTB, LCD_D7);
	}
	
	DIO_WritePin(LCD_4BIT_CMD_PORT_ID, LCD_E_PIN_ID, PIN_HIGH);
	_delay_ms(5);
	DIO_WritePin(LCD_4BIT_CMD_PORT_ID, LCD_E_PIN_ID, PIN_LOW);
}

void LCD_WriteString(uint8_t *str)
{
	while(*str != '\0')
	{
		LCD_WriteChar(*str++);
	}
}

void LCD_moveCursor(uint8_t row,uint8_t col)
{
	uint8_t lcd_memory_address;
	
	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
		lcd_memory_address=col;
		break;
		case 1:
		lcd_memory_address=col+0x40;
		break;
		case 2:
		lcd_memory_address=col+0x40;
		break;
		case 3:
		lcd_memory_address=col+0x40;
		break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_WriteCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

void LCD_intgerToString(uint8_t data)
{
	uint8_t buff[16]; /* String to hold the ascii result */
	itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	LCD_WriteString(buff); /* Display the string */
}

void LCD_Clear(void)
{
	LCD_WriteCommand(LCD_CLEAR_COMMAND);
}