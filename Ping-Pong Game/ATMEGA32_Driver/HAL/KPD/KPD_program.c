/*
 * KPD_program.c
 *
 * Created: 2/3/2024 8:40:06 PM
 *  Author: dell
 */ 

#include "KPD_interface.h"
#include "KPD_config.h"

Return_Status_t KPD_Initialization(KPD_t KPD){
	Return_Status_t RetVal = Return_OK;
	
	/*******************************************Rows**********************************************/
	RetVal = DIO_SetPinDirection(KPD.KPD_Port , DIO_PIN0 , DIO_Direction_INPUT_PULL_UP);
	RetVal = DIO_SetPinDirection(KPD.KPD_Port , DIO_PIN1 , DIO_Direction_INPUT_PULL_UP);
	RetVal = DIO_SetPinDirection(KPD.KPD_Port , DIO_PIN2 , DIO_Direction_INPUT_PULL_UP);
	RetVal = DIO_SetPinDirection(KPD.KPD_Port , DIO_PIN3 , DIO_Direction_INPUT_PULL_UP);
	
	/*******************************************Cols**********************************************/
	RetVal = DIO_SetPinDirection(KPD.KPD_Port , DIO_PIN4 , DIO_Direction_OUTPUT);
	RetVal = DIO_SetPinDirection(KPD.KPD_Port , DIO_PIN5 , DIO_Direction_OUTPUT);
	RetVal = DIO_SetPinDirection(KPD.KPD_Port , DIO_PIN6 , DIO_Direction_OUTPUT);
	RetVal = DIO_SetPinDirection(KPD.KPD_Port , DIO_PIN7 , DIO_Direction_OUTPUT);
	
	RetVal = DIO_SetPinValue(KPD.KPD_Port , DIO_PIN4 , DIO_Logic_HIGH);
	RetVal = DIO_SetPinValue(KPD.KPD_Port , DIO_PIN5 , DIO_Logic_HIGH);
	RetVal = DIO_SetPinValue(KPD.KPD_Port , DIO_PIN6 , DIO_Logic_HIGH);
	RetVal = DIO_SetPinValue(KPD.KPD_Port , DIO_PIN7 , DIO_Logic_HIGH);
	
	return RetVal;
}

Return_Status_t KPD_GetPressed(KPD_t KPD , u8 *KPD_Button){
	Return_Status_t RetVal = Return_OK;
	u8 Button = KPD_NOT_PRESSED;
	u8 Row_Counter = 0 , Col_Counter = 0;
	
	for(Col_Counter = KPD_COLS_START ; Col_Counter <= KPD_COLS_END ; ++Col_Counter){
		
		RetVal = DIO_SetPinValue(KPD.KPD_Port , Col_Counter , DIO_Logic_LOW);
		
		for(Row_Counter = KPD_ROWS_START ; Row_Counter <= KPD_ROWS_END ; ++Row_Counter){
			
			RetVal = DIO_GetPinValue(KPD.KPD_Port , Row_Counter , &Button);
			
			if(0 == Button){
				
				/*Delay for debounceing*/
				_delay_ms(50); 
				RetVal = DIO_GetPinValue(KPD.KPD_Port , Row_Counter , &Button);
				
				if(0 == Button){
					*KPD_Button = KPD_Buttons[Row_Counter][Col_Counter - KPD_COLS_NUMBER];
				}
				
				while(0 == Button){
					RetVal = DIO_GetPinValue(KPD.KPD_Port , Row_Counter , &Button);
				}
				
				return RetVal;
			}
			
		}
		RetVal = DIO_SetPinValue(KPD.KPD_Port , Col_Counter , DIO_Logic_HIGH);
	}
	return RetVal;
}


