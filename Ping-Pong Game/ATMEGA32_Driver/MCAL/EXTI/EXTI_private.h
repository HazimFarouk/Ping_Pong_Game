/*
 * EXTI_private.h
 *
 * Created: 2/17/2024 7:05:50 PM
 *  Author: dell
 */ 


#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

/***********************REGISTERS*****************************/

#define SREG_REG	*((volatile u8 *)0x5F)   /************Contain global Interrupt Enable Pin*******************/
#define GICR_REG	*((volatile u8 *)0x5B)	 /************Contain Interrupt Enable For each pin*****************/
#define GIFR_REG	*((volatile u8 *)0x5A)	 /************Contain Interrupt Flag For each pin*******************/
#define MCUCR_REG	*((volatile u8 *)0x55)	 /************Contain Trigger Pins For INT0 && INT1*****************/
#define MCUCSR_REG	*((volatile u8 *)0x54)	 /************Contain Trigger Pin For INT2 *************************/



#define  ENALBE_INTERRUPT_I 7                /************0xIxxxxxxx ==> To Enable Golbal Interrupt*************/

#endif /* EXTI_PRIVATE_H_ */