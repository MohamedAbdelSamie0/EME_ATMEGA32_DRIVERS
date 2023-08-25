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

Timer0_ConfigType TimerConfiguration;

int main(void)
{
	TimerConfiguration.compare_value = COMPARE_VALUE;
	//TimerConfiguration->mode = Normal;
	TimerConfiguration.prescaler = Prescalar_256;
	
	DIO_setPinDirection(DIO_PORTB, DIO_PIN3, PIN_OUTPUT);
	
	SetBit(SREG, 7);		/* Enable global interrupts	*/
	
	//LCD_init();
	//LCD_Clear();
    /* Replace with your application code */
	Timer_init(&TimerConfiguration);
    while (1)
    {
		if(g_TimerCounter == 125)
		{
			g_TimerCounter = 0;
			ToggleBit(PORTA, DIO_PIN4);
		}
		//LCD_Clear();
		//LCD_intgerToString(g_TimerCounter);
		//LCD_moveCursor(1,5);
		//LCD_intgerToString(g_watchDogCounter);
    }
}

