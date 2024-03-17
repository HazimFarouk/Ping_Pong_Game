/*
 * EXTI_program.c
 *
 * Created: 2/17/2024 7:06:38 PM
 *  Author: dell
 */ 

/*************************INCLUDES*****************************/
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_interface.h"


void (*EXTI_InterruptCallBackHandler[3])(void);

/*=======================================================================================================================================*/
Return_Status_t EXTI_Initializatoin(EXTI_t *EXTI_Interrupt){
	Return_Status_t RetVal = Return_OK;
	if(NULL_POINTER == EXTI_Interrupt){
		RetVal = Return_NOK;
	}
	
	else{
		
		/******************Open global interrupt*******************/
		SET_BIT(SREG_REG , ENALBE_INTERRUPT_I);
		
		/************************Choose INTx And Enable It***********************/
		RetVal = EXTI_EnableInterrupt(EXTI_Interrupt);
		
		/******************Set Handler*******************/
		RetVal = EXTI_SetHandler(EXTI_Interrupt);
		
		/************************Choose Trigger State***********************/
		RetVal = EXTI_SetTriggerState(EXTI_Interrupt);	
		
	}
	return RetVal;
}

/*=======================================================================================================================================*/
Return_Status_t EXTI_EnableInterrupt(EXTI_t *EXTI_Interrupt){
	Return_Status_t RetVal = Return_OK;
	if(NULL_POINTER == EXTI_Interrupt || (EXTI_Interrupt->EXTI_INTx != EXTI_INT0 && 
	   EXTI_Interrupt->EXTI_INTx != EXTI_INT1 && EXTI_Interrupt->EXTI_INTx != EXTI_INT2)){
		RetVal = Return_NOK;
	}
	
	else{
		SET_BIT(GICR_REG , EXTI_Interrupt->EXTI_INTx);
	}
	return RetVal;
}

/*=======================================================================================================================================*/
Return_Status_t EXTI_DisableInterrupt(EXTI_t *EXTI_Interrupt){
	Return_Status_t RetVal = Return_OK;
	if(NULL_POINTER == EXTI_Interrupt){
		RetVal = Return_NOK;
	}
	
	else{
		CLR_BIT(GICR_REG , EXTI_Interrupt->EXTI_INTx);
	}
	return RetVal;
}

/*=======================================================================================================================================*/
void EXTI_ClearFlag(EXTI_INTx_t EXTI_INTx){
	CLR_BIT(GIFR_REG , EXTI_INTx);
}

/*=======================================================================================================================================*/
Return_Status_t EXTI_SetHandler(EXTI_t *EXTI_Interrupt){
	Return_Status_t RetVal = Return_OK;
	if(NULL_POINTER == EXTI_Interrupt){
		RetVal = Return_NOK;
	}
	
	else{
		switch(EXTI_Interrupt->EXTI_INTx){
			case EXTI_INT0 : 
				EXTI_InterruptCallBackHandler[0] = EXTI_Interrupt->EXTI_Handler;
				break;
			case EXTI_INT1 :
				EXTI_InterruptCallBackHandler[1] = EXTI_Interrupt->EXTI_Handler;
				break;
			case EXTI_INT2 :
				EXTI_InterruptCallBackHandler[2] = EXTI_Interrupt->EXTI_Handler;
				break;
			default :
				break;
		}
	}
	return RetVal;
}

/*=======================================================================================================================================*/
Return_Status_t EXTI_SetTriggerState(EXTI_t *EXTI_Interrupt){
	Return_Status_t RetVal = Return_OK;
	if(NULL_POINTER == EXTI_Interrupt){
		RetVal = Return_NOK;
	}
	
	else{
		
		if(EXTI_Interrupt->EXTI_TRIGGER >= EXTI_LOW_LEVEL_TRIGGER && EXTI_Interrupt->EXTI_TRIGGER <= EXTI_RISING_EDGE_TRIGGER){
			
			if(EXTI_Interrupt->EXTI_INTx == EXTI_INT0 || EXTI_Interrupt->EXTI_INTx == EXTI_INT1){
				
				u8 Trigger_Bit = (6 - EXTI_Interrupt->EXTI_INTx) * -2;
				switch(EXTI_Interrupt->EXTI_TRIGGER){
					case EXTI_LOW_LEVEL_TRIGGER :
						CLR_BIT(MCUCR_REG , Trigger_Bit);
						CLR_BIT(MCUCR_REG , (Trigger_Bit + 1));
						break;
					case EXTI_ON_CHANGE_TRIGGER :
						SET_BIT(MCUCR_REG , Trigger_Bit);
						CLR_BIT(MCUCR_REG , (Trigger_Bit + 1));
						break;
					case EXTI_FALLING_EDGE_TRIGGER :
						CLR_BIT(MCUCR_REG , Trigger_Bit);
						SET_BIT(MCUCR_REG , (Trigger_Bit + 1));
						break;
					case EXTI_RISING_EDGE_TRIGGER :
						SET_BIT(MCUCR_REG , Trigger_Bit);
						SET_BIT(MCUCR_REG , (Trigger_Bit + 1));
						break;
					default :
						RetVal = Return_NOK;
						break;
				}
			}
			else if(EXTI_Interrupt->EXTI_INTx == EXTI_INT2){
				switch(EXTI_Interrupt->EXTI_TRIGGER){
					case EXTI_FALLING_EDGE_TRIGGER :
						CLR_BIT(MCUCR_REG , 6);
						break;
					case EXTI_RISING_EDGE_TRIGGER :
						SET_BIT(MCUCR_REG , 6);
						break;
					default :
						RetVal = Return_NOK;
						break;
				}
			}
			else{
				RetVal = Return_NOK;
			}
		}
			
		else{
			RetVal = Return_NOK;
		}
	}
	return RetVal;
}


/*=======================================================================================================================================*/

/*****************************ISRs***************************/
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{

	if( EXTI_InterruptCallBackHandler[0] != NULL_POINTER ){

		EXTI_InterruptCallBackHandler[0](); /*  Call The Global Pointer to Function  */
		EXTI_ClearFlag( EXTI_INT0 );

	}

}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{

	if( EXTI_InterruptCallBackHandler[1] != NULL_POINTER ){

		EXTI_InterruptCallBackHandler[1]();
		EXTI_ClearFlag( EXTI_INT1 );

	}

}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{

	if( EXTI_InterruptCallBackHandler[2] != NULL_POINTER ){

		EXTI_InterruptCallBackHandler[2]();
		EXTI_ClearFlag(EXTI_INT2);

	}

}