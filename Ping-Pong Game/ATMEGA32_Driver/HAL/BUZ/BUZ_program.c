/*
 * BUZ_program.c
 *
 * Created: 1/28/2024 7:45:52 PM
 *  Author: dell
 */ 

#include "BUZ_interface.h"



Return_Status_t BUZ_Initialization(BUZ_t BUZ){
	Return_Status_t RetVal = Return_OK;
	
	RetVal = DIO_SetPinDirection(BUZ.Port , BUZ.Pin , DIO_Direction_OUTPUT);
	
	return RetVal;
}

/****************************************************************************************************************************************************************/
Return_Status_t BUZ_On(BUZ_t BUZ){
	Return_Status_t RetVal = Return_OK;
	
	if(DIO_Active_LOW == BUZ.Status){
		RetVal = DIO_SetPinValue(BUZ.Port , BUZ.Pin , DIO_Logic_LOW);
	}
	
	else if(DIO_Active_HIGH == BUZ.Status){
		RetVal = DIO_SetPinValue(BUZ.Port , BUZ.Pin , DIO_Logic_HIGH);
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

/****************************************************************************************************************************************************************/
Return_Status_t BUZ_Off(BUZ_t BUZ){
	Return_Status_t RetVal = Return_OK;
	
	if(DIO_Active_LOW == BUZ.Status){
		RetVal = DIO_SetPinValue(BUZ.Port , BUZ.Pin , DIO_Logic_HIGH);
	}
	
	else if(DIO_Active_HIGH == BUZ.Status){
		RetVal = DIO_SetPinValue(BUZ.Port , BUZ.Pin , DIO_Logic_LOW);
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

/****************************************************************************************************************************************************************/
Return_Status_t BUZ_Toggle(BUZ_t BUZ){
	Return_Status_t RetVal = Return_OK;
	
	RetVal = DIO_TogglePinValue(BUZ.Port , BUZ.Pin);
	
	return RetVal;
}
