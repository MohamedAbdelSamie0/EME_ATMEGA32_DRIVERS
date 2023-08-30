/*
 * Timer.c
 *
 * Created: 8/25/2023 11:35:50 AM
 *  Author: Mohamed Abdelsamie
 */ 

#include "Timer.h"
#include <avr/interrupt.h>

#ifndef F_CPU
#define  F_CPU		16000000UL
#endif

uint8_t g_watchDogCounter = 0;
uint8_t g_TimerCounter = 0;
uint8_t g_TimerCounter_flag = 0;

/*
 * function name: Timer_init
 *
 * input params: NONE
 * output params: NONE
 */ 
void Timer_init(Timer0_ConfigType* Timer_config)
{
	
	TIMER0_CTRL_REG = TIMER0_OPERATION_MODE | Timer_config->prescaler;	/*	normal mode operation with 256 prescaler	*/
	
	#if TIMER_MODE == INTERRUPT_MODE_OVF
		TIMERS_IMSK_REG |= (1 << INTERRUPT_BIT);	/*	Enable Timeroverflow interrupt	*/
		TIMER0_CNTR_REG = Timer_config->initial_value;	/*	initial value and start timer	*/
	#elif	TIMER_MODE == INTERRUPT_MODE_CTC
		TIMERS_IMSK_REG |= (1 << INTERRUPT_BIT);	/*	Enable Timeroverflow interrupt	*/
		TIMER0_OCR0_REG = Timer_config->compare_value;
	#endif
}

/*
 * function name: Timer_stop
 *
 * input params: NONE
 * output params: NONE
 */ 
void Timer_stop()
{
	TIMER0_CTRL_REG = 0x00;	/* No clock source; timer stopped	*/
}

#if TIMER_MODE == INTERRUPT_MODE_OVF
/*
 * Interrupt Service Routine for Timer0 overflow mode
 *
 */ 
ISR(TIMER0_OVF_vect)
{
	if( TIMER0_NUMBER_OVERFLOWS > g_TimerCounter_flag )
	{
		g_TimerCounter_flag++;	/*	Increment timer counter FLAG till it reaches the number of required overflows	*/
	}
	
	if(g_TimerCounter_flag == TIMER0_NUMBER_OVERFLOWS)
	{
		ToggleBit(PORTA, DIO_PIN5);	/*	Toggle BLUE LED	*/
		g_TimerCounter++;			/*	Increment timer counter to idicate one second	*/
		g_TimerCounter_flag = 0;	/*	Reset Timer Counter FLAG	*/
	}
	if(g_TimerCounter == Timer_count_value)
	{
		g_TimerCounter = 0;		/*	Reset Timer counter	*/
		g_watchDogCounter++;	/*	Increment watchdog timer	*/
	}
	if(g_watchDogCounter == Watchdog_count_value)
	{
		g_watchDogCounter = 0;	/*	Resest watchdog counter	*/
		Timer_stop();
	}
	SetBit(TIMERS_IF_REG, TIMER0_IF_BIT);	/*	Clear TIMER0 interrupt Flag	*/
}
#endif

#if TIMER_MODE == INTERRUPT_MODE_CTC
ISR(TIMER0_COMP_vect)
{
	if(g_TimerCounter < 500)
	{
		g_TimerCounter++;
	}
	else if(g_TimerCounter == 500)
	{
		g_TimerCounter = 0;
		ToggleBit(PORTA, DIO_PIN4);
	}
	SetBit(TIMERS_IF_REG, (TIMER0_IF_BIT+1));	/*	Clear TIMER0 interrupt Flag	*/
}
#endif