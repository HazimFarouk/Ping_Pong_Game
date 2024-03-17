/*
 * SW_program.c
 *
 * Created: 1/28/2024 7:55:51 PM
 *  Author: dell
 */ 

#include "SW_interface.h"

Return_Status_t SW_Initialization(SW_t SW){
	Return_Status_t RetVal = Return_OK;
	
	if(SW.PULL_Status == SW_Int_PULL_UP){
		RetVal = DIO_SetPinDirection(SW.Port , SW.Pin , DIO_Direction_INPUT_PULL_UP);
	}
	else if(SW.PULL_Status == SW_Ext_Pull_UP){
		RetVal = DIO_SetPinDirection(SW.Port , SW.Pin , DIO_Direction_INPUT);
	}
	
	else if(SW.PULL_Status == SW_Ext_Pull_DOWN){
		RetVal = DIO_SetPinDirection(SW.Port , SW.Pin , DIO_Direction_INPUT);
	}
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

u8 SW_GetPressed(SW_t SW){
	
	u8 SW_Presses = SW_NOT_PRESSED;
	u8 SW_RetVal = SW_NOT_PRESSED;
	
	DIO_GetPinValue(SW.Port , SW.Pin , &SW_Presses);
	if(SW.PULL_Status == SW_Int_PULL_UP || SW.PULL_Status == SW_Ext_Pull_UP){
		
		if(SW_Presses == 0){
			SW_RetVal = SW_PRESSED;
		}
		
		else{
			SW_RetVal = SW_NOT_PRESSED;
		}
	}
	
	else if(SW.PULL_Status == SW_Ext_Pull_DOWN){
		
		if(1 == SW_Presses){
			SW_RetVal = SW_PRESSED;
		}
		else{
			SW_RetVal = SW_NOT_PRESSED;
		}
	}
	return SW_RetVal;
}