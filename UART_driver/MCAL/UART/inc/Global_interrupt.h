/*
 * Global_interrupt.h
 *
 * Created: 9/1/2023
 *  Author: Mohamed Abdelsamie
 */ 


#ifndef GLOBAL_INTERRUPT_H_
#define GLOBAL_INTERRUPT_H_

#include <stdint.h>
#include "BitMath.h"
/******************************************************
				global status register
******************************************************/
#define SREG	*((volatile uint8_t *) 0x5F)

/******************************************************
				global Interrupt bit
******************************************************/
#define GIE_BIT	7

/******************************************************
				FUNCTION PROTOTYPES
******************************************************/
void Global_interrupts_enable(void);

void Global_interrupts_disable(void);

#endif /* GLOBAL_INTERRUPT_H_ */