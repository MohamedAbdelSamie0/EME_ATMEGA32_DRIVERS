/*
 * ADC.h
 *
 * Created: 8/24/2023 10:18:45 AM
 *  Author: Mohamed Abdelsamie
 */ 


#ifndef ADC_H_
#define ADC_H_

/*******************************************************************************
 *                                FILE INCLUDES								    *
 *******************************************************************************/
#include "DIO.h"
//#include "std_types.h"
#include "ADC_Cfg.h"

/*******************************************************************************
 *                                PROTOTYPES									*
 *******************************************************************************/
/*
 * function name: ADC_init
 *
 * input params: NONE
 * output params: NONE
 */ 
void ADC_init();

/*
 * function name: ADC_read
 *
 * input params: 
 * output params: va; converted analouge value
 */ 
void ADC_read(uint8_t channel, uint16_t* val);
#endif /* ADC_H_ */