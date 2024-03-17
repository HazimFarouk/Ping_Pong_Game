/*
 * LED_program.c
 *
 * Created: 1/28/2024 6:49:38 PM
 *  Author: dell
 */ 

#include "LED_interface.h"



Return_Status_t LED_Initialization(LED_t LED){
	Return_Status_t RetVal = Return_OK;
	
	RetVal = DIO_SetPinDirection(LED.Port , LED.Pin , DIO_Direction_OUTPUT);
	
	return RetVal;
}

/****************************************************************************************************************************************************************/
Return_Status_t LED_On(LED_t LED){
	Return_Status_t RetVal = Return_OK;
	
	if(DIO_Active_LOW == LED.Status){
		RetVal = DIO_SetPinValue(LED.Port , LED.Pin , DIO_Logic_LOW);
	}
	
	else if(DIO_Active_HIGH == LED.Status){
		RetVal = DIO_SetPinValue(LED.Port , LED.Pin , DIO_Logic_HIGH);
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

/****************************************************************************************************************************************************************/
Return_Status_t LED_Off(LED_t LED){
	Return_Status_t RetVal = Return_OK;
	
	if(DIO_Active_LOW == LED.Status){
		RetVal = DIO_SetPinValue(LED.Port , LED.Pin , DIO_Logic_HIGH);
	}
	
	else if(DIO_Active_HIGH == LED.Status){
		RetVal = DIO_SetPinValue(LED.Port , LED.Pin , DIO_Logic_LOW);
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

/****************************************************************************************************************************************************************/
Return_Status_t LED_Toggle(LED_t LED){
	Return_Status_t RetVal = Return_OK;
	
	RetVal = DIO_TogglePinValue(LED.Port , LED.Pin);
	
	return RetVal;
}

