/*
 * Timer.h
 *
 * Created: 8/25/2023 11:35:16 AM
 *  Author: Mohamed Abdelsamie
 */ 

/**********************************************************
				File Includes
**********************************************************/
#include "DIO.h"
#include "Timer_Cfg.h"

#ifndef TIMER_H_
#define TIMER_H_

/**********************************************************
				Type definitions
**********************************************************/
typedef enum
{
	No_Clock,
	Prescalar_0,
	Prescalar_8,
	Prescalar_64,
	Prescalar_256,
	Prescalar_1024,
	EX_Clock_FallingEdge,
	EX_Clock_RisingEdge
}Timer0_Prescaler;

typedef struct {
	uint8_t initial_value;
	uint8_t compare_value; // it will be used in compare mode only.
	Timer0_Prescaler prescaler;
	//Timer0_Mode mode;
}Timer0_ConfigType;
/**********************************************************
				FUNCTION PROTOTYPES
**********************************************************/
void Timer_init(Timer0_ConfigType* Timer_config);
void Timer_stop();

#endif /* TIMER_H_ */