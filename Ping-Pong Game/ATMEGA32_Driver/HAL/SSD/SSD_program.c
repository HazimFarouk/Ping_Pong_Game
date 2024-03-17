/*
 * SSD_program.c
 *
 * Created: 2/3/2024 1:37:39 AM
 *  Author: dell
 */ 

#include "SSD_interface.h"

u8 SSD_Numbers[10] = {0b00111111 , 0b00000110 , 0b01011011 , 0b01001111 , 0b01100110 , 0b01101101 , 0b01111101 , 0b00000111 , 0b01111111 , 0b01101111};

Return_Status_t SSD_Initialization(SSD_t SSD){
	Return_Status_t RetVal = Return_OK;
	
	RetVal = DIO_SetPortDirection(SSD.Data_Port , DIO_Direction_OUTPUT);
	
	return RetVal;
}

Return_Status_t SSD_Enable(SSD_t SSD){
	Return_Status_t RetVal = Return_OK;
	
	RetVal = DIO_SetPinDirection(SSD.Enable_Port , SSD.Enable_Pin, DIO_Direction_OUTPUT);
	
	if(SSD_Common_Anode == SSD.Common_Type){
		RetVal = DIO_SetPinValue(SSD.Enable_Port , SSD.Enable_Pin, DIO_Logic_HIGH);
	}
	else if(SSD_Common_Cathode == SSD.Common_Type){
		RetVal = DIO_SetPinValue(SSD.Enable_Port , SSD.Enable_Pin, DIO_Logic_LOW);
	}
	else{
		RetVal = Return_NOK;
	}
	return RetVal;
}

Return_Status_t SSD_Disable(SSD_t SSD){
	Return_Status_t RetVal = Return_OK;
	
	if(SSD_Common_Anode == SSD.Common_Type){
		RetVal = DIO_SetPinValue(SSD.Enable_Port , SSD.Enable_Pin, DIO_Logic_LOW);
	}
	else if(SSD_Common_Cathode == SSD.Common_Type){
		RetVal = DIO_SetPinValue(SSD.Enable_Port , SSD.Enable_Pin, DIO_Logic_HIGH);
	}
	else{
		RetVal = Return_NOK;
	}
	return RetVal;
}

Return_Status_t SSD_DisplayNumber(SSD_t SSD , u8 Number){
	Return_Status_t RetVal = Return_OK;
	
	if(SSD_Common_Anode == SSD.Common_Type){
		RetVal = DIO_SetPortValue(SSD.Data_Port , ~(SSD_Numbers[Number]));
	}
	else if(SSD_Common_Cathode == SSD.Common_Type){
		RetVal = DIO_SetPortValue(SSD.Data_Port , SSD_Numbers[Number]);
	}
	else{
		RetVal = Return_NOK;
	}
	return RetVal;
}
