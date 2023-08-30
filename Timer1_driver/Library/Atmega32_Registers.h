/*
 * Atmega32_Registers.h
 *
 * Created: 8/18/2023 9:29:18 AM
 *  Author: Mohamed Abdelsamie
 */ 


#ifndef ATMEGA32_REGISTERS_H_
#define ATMEGA32_REGISTERS_H_

/******************************************************
				PORT REGISTERS
******************************************************/

#define PORTA	*((volatile uint8_t *) 0x3B)
#define PORTB	*((volatile uint8_t *) 0x38)
#define PORTC	*((volatile uint8_t *) 0x35)
#define PORTD	*((volatile uint8_t *) 0x32)

/******************************************************
			DIRECTION CONTROL REGISTERS
******************************************************/

#define DDRA	*((volatile uint8_t *) 0x3A)
#define DDRB	*((volatile uint8_t *) 0x37)
#define DDRC	*((volatile uint8_t *) 0x34)
#define DDRD	*((volatile uint8_t *) 0x31)

/******************************************************
				PIN REGISTERS
******************************************************/
#define PINA	*((volatile uint8_t *) 0x39)
#define PINB	*((volatile uint8_t *) 0x36)
#define PINC	*((volatile uint8_t *) 0x33)
#define PIND	*((volatile uint8_t *) 0x30)

/******************************************************
				EXTERNAL INTERRUPTS REGISTERS
******************************************************/
#define SREG	*((volatile uint8_t *) 0x5F)
#define MCUCR	*((volatile uint8_t *) 0x55)
#define MCUCSR	*((volatile uint8_t *) 0x54)
#define	GICR	*((volatile uint8_t *) 0x5B)
#define	GIFR	*((volatile uint8_t *) 0x5A)

/******************************************************
				ADC REGISTERS
******************************************************/
#define ADC_CTRL_REG	*((volatile uint8_t *) 0x26)
#define ADCH_REG		*((volatile uint8_t *) 0x25)
#define ADCL_REG		*((volatile uint8_t *) 0x24)
#define ADC_MUX_REG		*((volatile uint8_t *) 0x27)
#define S_FUNC_REG		*((volatile uint8_t *) 0x50)

/******************************************************
				Timer0 REGISTERS
******************************************************/
#define TIMER0_CTRL_REG	*((volatile uint8_t *) 0x53)
#define TIMER0_CNTR_REG	*((volatile uint8_t *) 0x52)
#define TIMERS_IMSK_REG	*((volatile uint8_t *) 0x59)
#define TIMERS_IF_REG	*((volatile uint8_t *) 0x58)
#define TIMER0_OCR0_REG	*((volatile uint8_t *) 0x5C)

#endif /* ATMEGA32_REGISTERS_H_ */