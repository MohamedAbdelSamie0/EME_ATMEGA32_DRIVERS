/*
 * Timer.c
 *
 * Created: 8/25/2023 9:32:20 AM
 * Author : DELL
 */ 

#include "Timer.h"
#include "LCD.h"
extern uint8_t g_watchDogCounter;
extern uint8_t g_TimerCounter;

int main(void)
{
	DIO_setPinDirection(DIO_PORTA, DIO_PIN5, PIN_OUTPUT);
	
	SetBit(SREG, 7);		/* Enable global interrupts	*/
	
	LCD_init();
	LCD_Clear();
    /* Replace with your application code */
	Timer_init();
    while (1)
    {
		LCD_Clear();
		LCD_intgerToString(g_TimerCounter);
		//LCD_moveCursor(1,5);
		LCD_intgerToString(g_watchDogCounter);
    }
}

