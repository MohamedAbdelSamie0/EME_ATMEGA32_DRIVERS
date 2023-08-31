/*
 * USART_Private.h
 *
 * Created: 8/31/2023
 *  Author: Mohamed Abdelsamie
 */ 


#ifndef PRIVATE_H_
#define PRIVATE_H_

/******************************************************
				USART R0EGISTERS
******************************************************/
#define USART_DATA_REG	*((volatile uint8_t *) 0x2C)
#define USART_CTRLA_REG	*((volatile uint8_t *) 0x2B)
#define USART_CTRLB_REG	*((volatile uint8_t *) 0x2A)
#define USART_CTRLC_REG	*((volatile uint8_t *) 0x40)
#define USART_BRH_REG	*((volatile uint8_t *) 0x40)
#define USART_BRL_REG	*((volatile uint8_t *) 0x29)

/*******************************************************************************
 *								Definitions	                                   *
 *******************************************************************************/
#define ASYNCHRONOUS			0x00
#define SYNCHRONOUS				0x01
#define TX						0x00
#define RX						0x01
#define TX_RX					0x02
#define IRQ_ENABLE				0x00
#define IRQ_DISABLE				0x01

/*******************************************************************************
 *                      Type Definitions	                                   *
 *******************************************************************************/
typedef uint32_t UART_BaudRate;	/*	USART Baud rate	*/

typedef enum
{
	Disable = 0,
	Reserved,
	Even_Parity,
	Odd_Parity
}UART_ParityType;	/*	Parity bit configurations	*/

typedef enum
{
	one_bit = 0,
	two_bit
}UART_StopBitType;	/*	Stop bit configurations	*/

typedef enum
{
 Five_bits = 0,
 Six_bits,
 Seven_bits,
 Eight_bits,
 Nine_bits = 7,
}UART_BitDataType;	/*	data bits number selection	*/

typedef enum
{
	MPCM_BIT = 0,
	U2X_BIT,
	PE_BIT,
	DOR_BIT,
	FE_BIT,
	UDRE_BIT,
	TXC_BIT,
	RXC_BIT
}USART_CTRLA_BITS;	/*	CTRL A register bits	*/

typedef enum
{
	TXB8_BIT = 0,
	RXB8_BIT,
	UCSZ2_BIT,
	TXEN_BIT,
	RXEN_BIT,
	UDRIE_BIT,
	TXCIE_BIT,
	RXCIE_BIT
}USART_CTRLB_BITS;	/*	CTRL B register bits	*/

typedef enum
{
	UCPOL_BIT = 0,
	UCSZ0_BIT,
	UCSZ1_BIT,
	USBS_BIT,
	UPM0_BIT,
	UPM1_BIT,
	UMSEL_BIT,
	URSEL_BIT
}USART_CTRLC_BITS;	/*	CTRL C register bits	*/

typedef struct{
	UART_BitDataType data_bits;
	UART_ParityType parity;
	UART_StopBitType stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;	/* struct to configure USART initialization	*/

extern UART_ConfigType USART_CONFIGURATION;
#endif /* PRIVATE_H_ */