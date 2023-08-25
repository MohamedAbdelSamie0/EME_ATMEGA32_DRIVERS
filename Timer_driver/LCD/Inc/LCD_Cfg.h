/*
 * LCD_Cfg.h
 *
 * Created: 8/18/2023 10:18:19 AM
 *  Author: Mohamed Abdelsamie
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* LCD HW Ports and Pins Ids */
#define LCD_4BIT_CMD_PORT_ID			DIO_PORTA
#define LCD_4BIT_DATA_PORT_ID			DIO_PORTB

#define LCD_8BIT_CMD_PORT_ID			DIO_PORTA
#define LCD_8BIT_DATA_PORT_ID			DIO_PORTB

#define LCD_RS_PIN_ID					DIO_PIN3
#define LCD_E_PIN_ID					DIO_PIN2
#define LCD_RW_PIN_ID					DIO_PIN1

#define LCD_D4							DIO_PIN0
#define LCD_D5							DIO_PIN1
#define LCD_D6							DIO_PIN2
#define LCD_D7							DIO_PIN4

/* LCD Commands */
#define LCD_CLEAR_COMMAND				0x01
#define LCD_GO_TO_HOME					0x02
#define LCD_TWO_LINES_8_BITS_MODE		0x38
#define LCD_TWO_LINES_4_BITS_MODE		0x28
#define LCD_CURSOR_OFF					0x0C
#define LCD_CURSOR_ON					0x0E
#define LCD_CURSOR_ON_BLINK				0x0F
#define LCD_SET_CURSOR_LOCATION			0x80

/*	LCD_MODE	*/
#define LCD_MODE						4


#endif /* LCD_CFG_H_ */