/*
 * DIO_private.h
 *
 * Created: 1/28/2024 2:49:26 PM
 *  Author: dell
 */ 


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

/***************Regiters*******************/
#define PORTA_Register		 *((volatile u8*)0x3B)
#define PORTB_Register		 *((volatile u8*)0x38)
#define PORTC_Register		 *((volatile u8*)0x35)
#define PORTD_Register		 *((volatile u8*)0x32)

#define DDRA_Register	 	 *((volatile u8*)0x3A)
#define DDRB_Register	  	 *((volatile u8*)0x37)
#define DDRC_Register		 *((volatile u8*)0x34)
#define DDRD_Register		 *((volatile u8*)0x31)

#define PINA_Register		 *((volatile u8*)0x39)
#define PINB_Register		 *((volatile u8*)0x36)
#define PINC_Register		 *((volatile u8*)0x33)
#define PIND_Register		 *((volatile u8*)0x30)


#endif /* DIO_PRIVATE_H_ */