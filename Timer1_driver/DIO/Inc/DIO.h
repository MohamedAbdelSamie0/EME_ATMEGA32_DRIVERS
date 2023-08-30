/*
 * DIO.h
 *
 * Created: 8/17/2023 3:05:50 PM
 *  Author: Mohamed ABdelsamie
 */ 


#ifndef DIO_H_
#define DIO_H_

#define F_CPU	16000000UL

#include <stdint.h>
#include "BitMath.h"
//#include <avr/io.h>
#include "Atmega32_Registers.h"

typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}DIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}DIO_PortDirectionType;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define DIO_PORTA	0
#define DIO_PORTB	1
#define DIO_PORTC	2
#define DIO_PORTD	3

#define DIO_PIN0	0
#define DIO_PIN1	1
#define DIO_PIN2	2
#define DIO_PIN3	3
#define DIO_PIN4	4
#define DIO_PIN5	5
#define DIO_PIN6	6
#define DIO_PIN7	7


#define DIO_PIN_OUTPUT	1
#define DIO_PIN_INPUT	0

#define DIO_PORT_OUTPUT	0xFF
#define DIO_PORT_INPUT	0x00

#define PIN_HIGH	1
#define PIN_LOW		0

#define DIO_PORT_HIGH	0xFF
#define DIO_PORT_LOW	0x00

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void DIO_setPinDirection(uint8_t Port, uint8_t pin, uint8_t dir);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void DIO_WritePin(uint8_t Port, uint8_t pin, uint8_t val);

/*
 * Description :
 * Read the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
void DIO_ReadPin(uint8_t Port, uint8_t pin, uint8_t* val);

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void DIO_setPortDirection(uint8_t Port, uint8_t dir);

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void DIO_WritePort(uint8_t Port, uint8_t val);

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
void DIO_ReadPort(uint8_t Port, uint8_t* val);

/*
 * Description :
 * Set the required pin to pull up resistor.
 * If the input port number is not correct, The function will return do nothing.
 */
void DIO_SetPullUp(uint8_t Port ,uint8_t Pin);
#endif /* DIO_H_ */