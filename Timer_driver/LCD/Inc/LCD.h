/*
 * LCD.h
 *
 * Created: 8/18/2023 10:07:57 AM
 *  Author: Mohamed Abdelsamie
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "DIO.h"
#include "LCD_Cfg.h"
#include "BitMath.h"

/**********************************************************
			FUNCTION PROTOTYPES
**********************************************************/

void LCD_init(void);

void LCD_WriteCommand(uint8_t cmd);

void LCD_WriteChar(uint8_t chr);

void LCD_WriteString(uint8_t *str);

void LCD_moveCursor(uint8_t row, uint8_t col);

void LCD_intgerToString(uint8_t data);

void LCD_Clear(void);

#endif /* LCD_H_ */