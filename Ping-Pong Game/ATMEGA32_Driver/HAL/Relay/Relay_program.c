/*
 * Relay_program.c
 *
 * Created: 2/3/2024 12:37:45 AM
 *  Author: dell
 */ 

#include "Relay_interface.h"

Return_Status_t Relay_Initialization(Relay_t Relay){
	Return_Status_t RetVal = Return_OK;
	
	RetVal = DIO_SetPinDirection(Relay.Port , Relay.Pin , DIO_Direction_OUTPUT);
	
	return RetVal;
}

/****************************************************************************************************************************************************************/

Return_Status_t Relay_On(Relay_t Relay){
	Return_Status_t RetVal = Return_OK;
	
	if(DIO_Active_LOW == Relay.Status){
		RetVal = DIO_SetPinValue(Relay.Port , Relay.Pin , DIO_Logic_LOW);
	}
	
	else if(DIO_Active_HIGH == Relay.Status){
		RetVal = DIO_SetPinValue(Relay.Port , Relay.Pin , DIO_Logic_HIGH);
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

/****************************************************************************************************************************************************************/

Return_Status_t Relay_Off(Relay_t Relay){
	Return_Status_t RetVal = Return_OK;
	
	if(DIO_Active_LOW == Relay.Status){
		RetVal = DIO_SetPinValue(Relay.Port , Relay.Pin , DIO_Logic_HIGH);
	}
	
	else if(DIO_Active_HIGH == Relay.Status){
		RetVal = DIO_SetPinValue(Relay.Port , Relay.Pin , DIO_Logic_LOW);
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

/****************************************************************************************************************************************************************/

Return_Status_t Relay_Toggle(Relay_t Relay){
	Return_Status_t RetVal = Return_OK;
	
	RetVal = DIO_TogglePinValue(Relay.Port , Relay.Pin);
	
	return RetVal;
}
