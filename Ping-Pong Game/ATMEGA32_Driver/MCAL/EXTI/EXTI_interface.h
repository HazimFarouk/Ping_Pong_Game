/*
 * EXTI_interface.h
 *
 * Created: 2/17/2024 7:06:17 PM
 *  Author: dell
 */ 


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/********************INCLUDES*************************/
#include "../../LIB/STD_Types.h"
/********************EXTI_INTx**********************/
typedef enum{	
	EXTI_INT0 = 6,
	EXTI_INT1 = 7,
	EXTI_INT2 = 5
}EXTI_INTx_t;

/********************EXTI_TRIGGER**********************/
typedef enum{
	EXTI_LOW_LEVEL_TRIGGER,
	EXTI_ON_CHANGE_TRIGGER,
	EXTI_FALLING_EDGE_TRIGGER,
	EXTI_RISING_EDGE_TRIGGER
}EXTI_TRIGGER_MODE_t;

typedef struct{
	EXTI_INTx_t EXTI_INTx;
	void (* EXTI_Handler)(void);
	EXTI_TRIGGER_MODE_t EXTI_TRIGGER;
}EXTI_t;


Return_Status_t EXTI_Initializatoin(EXTI_t *EXTI_Interrupt);
Return_Status_t EXTI_EnableInterrupt(EXTI_t *EXTI_Interrupt);
Return_Status_t EXTI_DisableInterrupt(EXTI_t *EXTI_Interrupt);
void EXTI_ClearFlag(EXTI_INTx_t EXTI_INTx);
Return_Status_t EXTI_SetHandler(EXTI_t *EXTI_Interrupt);
Return_Status_t EXTI_SetTriggerState(EXTI_t *EXTI_Interrupt);




#endif /* EXTI_INTERFACE_H_ */