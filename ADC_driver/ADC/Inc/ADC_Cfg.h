/*
 * ADC_Cfg.h
 *
 * Created: 8/24/2023 11:12:19 AM
 *  Author: Mohamed Abdelsamie
 */ 


#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/*******************************************************************************
 *                                Definitions								    *
 *******************************************************************************/
#define POLLING_MODE				0
#define INTERRUPT_MODE				1

#define ADC0_PORT					PORTA
#define ADC0_PORT_ID				DIO_PORTA
#define ADC0_CHANNEL				0
#define ADC_MODE					INTERRUPT_MODE

#define ADC_ENABLE_BIT				7
#define ADC_SC_BIT					6
#define ADC_IF_BIT					4
#define ADC_IE_BIT					3
#define ADC_PS0						0
#define ADC_PS1						1
#define ADC_PS2						2
#define ADC_PRE_FACTOR				pre_128
#define ADC0_REF_VOLTAGE			AVCC

/*******************************************************************************
 *                                Type definitions                              *
 *******************************************************************************/
typedef enum
{
	AREF = 0,	/*	External ADC ref voltage	*/
	AVCC,		/*	ADC 5V pin (Vcc) With capacitor at AREF	*/
	Reserved,	/*	Reserved do not use	*/
	Internal,	/*	Internal ADC ref voltage	*/
}ADC_refSelectionType;		/*	ADC reference voltage selection type	*/

typedef enum
{
	pre_def = 0,	/*	default value is a prescaler of 2	*/
	pre_2,
	pre_4,
	pre_8,
	pre_16,
	pre_32,
	pre_64,
	pre_128,
}ADC_presecalerType;		/*	ADC prescaler division factors (pre_*Factor*)	*/

#endif /* ADC_CFG_H_ */