/*
 * Timer_Cfg.h
 *
 * Created: 8/25/2023 11:35:27 AM
 *  Author: DELL
 */ 


#ifndef TIMER_CFG_H_
#define TIMER_CFG_H_

#define TIMER0_NUMBER_OVERFLOWS		250
#define TIMER0_IF_BIT				0
#define TIMER_MODE					INTERRUPT_MODE_CTC
#define COUNTER_VALUE				6
#define COMPARE_VALUE				62
#define INTERRUPT_BIT				0
#define TIMER0_OPERATION_MODE		0x98
#define Timer_count_value			10
#define Watchdog_count_value		6

#define INTERRUPT_MODE_OVF			1
#define INTERRUPT_MODE_CTC			2
#define POLLING_MODE				0

#endif /* TIMER_CFG_H_ */