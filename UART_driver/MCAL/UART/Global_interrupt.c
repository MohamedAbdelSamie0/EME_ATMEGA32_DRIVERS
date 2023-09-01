/*
 * Global_interrupt.c
 *
 * Created: 9/1/2023
 *  Author: Mohamed Abdelsamie
 */ 

#include "Global_interrupt.h"

void Global_interrupts_enable(void)
{
	SetBit(SREG, GIE_BIT);
}

void Global_interrupts_disable(void)
{
	ClearBit(SREG, GIE_BIT);
}