/*
 * CLCD_program.c
 *
 * Created: 2/3/2024 10:16:37 PM
 *  Author: dell
 */ 

#define F_CPU 8000000UL

#include "CLCD_interface.h"
#include "util/delay.h"
#include "CLCD_private.h"



Return_Status_t static CLCD_FallingEdge(CLCD_t *CLCD);

Return_Status_t CLCD_Initialization(CLCD_t *CLCD){
	Return_Status_t RetVal = Return_OK;
	
	if(NULL_POINTER == CLCD){
		RetVal = Return_NOK;
	}
	
	else{
		_delay_ms(50);
		RetVal = DIO_SetPinDirection(CLCD->Commond_Port , CLCD->RS_Pin , DIO_Direction_OUTPUT);
		RetVal = DIO_SetPinDirection(CLCD->Commond_Port , CLCD->RW_Pin , DIO_Direction_OUTPUT);
		RetVal = DIO_SetPinDirection(CLCD->Commond_Port , CLCD->E_Pin  , DIO_Direction_OUTPUT);
		
		if(CLCD_8_Bit_Mode == CLCD->Bits_Mode){
				RetVal = DIO_SetPortDirection(CLCD->Data_Port , DIO_Direction_OUTPUT);
				
				RetVal = CLCD_SendCommond(CLCD , CLCD_RETURN_HOME);
				_delay_ms(1);

				RetVal = CLCD_SendCommond(CLCD , CLCD_8BIT_FUNCTION_SET_2LINE_5x8FONT);
				_delay_ms(1);
			
		}
			
		else if(CLCD_4_Bit_Mode == CLCD->Bits_Mode){
				if(DIO_LOW_NIBBLE == CLCD->Data_Nibble){
						RetVal = DIO_SetPinDirection(CLCD->Data_Port , DIO_PIN0 , DIO_Direction_OUTPUT);
						RetVal = DIO_SetPinDirection(CLCD->Data_Port , DIO_PIN1 , DIO_Direction_OUTPUT);
						RetVal = DIO_SetPinDirection(CLCD->Data_Port , DIO_PIN2 , DIO_Direction_OUTPUT);
						RetVal = DIO_SetPinDirection(CLCD->Data_Port , DIO_PIN3 , DIO_Direction_OUTPUT);
				}
				else{
						RetVal = DIO_SetPinDirection(CLCD->Data_Port , DIO_PIN4 , DIO_Direction_OUTPUT);
						RetVal = DIO_SetPinDirection(CLCD->Data_Port , DIO_PIN5 , DIO_Direction_OUTPUT);
						RetVal = DIO_SetPinDirection(CLCD->Data_Port , DIO_PIN6 , DIO_Direction_OUTPUT);
						RetVal = DIO_SetPinDirection(CLCD->Data_Port , DIO_PIN7 , DIO_Direction_OUTPUT);
				}
				
				RetVal = CLCD_SendCommond(CLCD , CLCD_RETURN_HOME);
				_delay_ms(1);
				
				RetVal = CLCD_SendCommond(CLCD , CLCD_4BIT_FUNCTION_SET_2LINE_5x8FONT);
				_delay_ms(1);
					
		}
		
		RetVal = CLCD_SendCommond(CLCD , CLCD_DISPLAY_ON);
		_delay_ms(1);
		
		RetVal = CLCD_ClearScreen(CLCD);
		
		RetVal = CLCD_SendCommond(CLCD , CLCD_ENTRY_MODE_INCREMENT_POSITION);
		_delay_ms(1);
	
	}
	
	return RetVal;
}

Return_Status_t CLCD_SendCommond(CLCD_t *CLCD , u8 Commond){
	Return_Status_t RetVal = Return_OK;
	
	if(NULL_POINTER == CLCD){
		RetVal = Return_NOK;
	}
	
	else{
		RetVal = DIO_SetPinValue(CLCD->Commond_Port , CLCD->RS_Pin , DIO_Logic_LOW);
		RetVal = DIO_SetPinValue(CLCD->Commond_Port , CLCD->RW_Pin , DIO_Logic_LOW);
		
		if(CLCD_8_Bit_Mode == CLCD->Bits_Mode){
			
			RetVal = DIO_SetPortValue(CLCD->Data_Port , Commond);
			RetVal = CLCD_FallingEdge(CLCD);
			
		}
		
		else if(CLCD_4_Bit_Mode == CLCD->Bits_Mode){
			
			RetVal = DIO_SetHighNibbleValue(CLCD->Data_Port , (Commond >> 4));
			RetVal = CLCD_FallingEdge(CLCD);
			
			RetVal = DIO_SetHighNibbleValue(CLCD->Data_Port , Commond);
			RetVal = CLCD_FallingEdge(CLCD);
		}
		
		else{
			RetVal = Return_NOK;
		}
	}
	
	return RetVal;
}

Return_Status_t CLCD_SendData(CLCD_t *CLCD , u8 Data){
	Return_Status_t RetVal = Return_OK;
	
	if(NULL_POINTER == CLCD){
		RetVal = Return_NOK;
	}
	
	else{
		RetVal = DIO_SetPinValue(CLCD->Commond_Port , CLCD->RS_Pin , DIO_Logic_HIGH);
		RetVal = DIO_SetPinValue(CLCD->Commond_Port , CLCD->RW_Pin , DIO_Logic_LOW);
		
		if(CLCD_8_Bit_Mode == CLCD->Bits_Mode){
			
			RetVal = DIO_SetPortValue(CLCD->Data_Port , Data);
			RetVal = CLCD_FallingEdge(CLCD);
		}
		
		else if(CLCD_4_Bit_Mode == CLCD->Bits_Mode){
			
			RetVal = DIO_SetHighNibbleValue(CLCD->Data_Port , (Data >> 4));
			RetVal = CLCD_FallingEdge(CLCD);
			
			RetVal = DIO_SetHighNibbleValue(CLCD->Data_Port , Data);
			RetVal = CLCD_FallingEdge(CLCD);
			
		}
		else{
			RetVal = Return_NOK; 
		}
		
		_delay_ms(1);
	}
	
	return RetVal;
} 

Return_Status_t CLCD_SendString(CLCD_t *CLCD , char *String){
	Return_Status_t RetVal = Return_OK;
	
	if(NULL_POINTER == CLCD || NULL_POINTER == String){
		RetVal = Return_NOK;
	}
	
	else{
		u8 Counter = 0;
		while(String[Counter] != '\0'){
			RetVal = CLCD_SendData(CLCD , String[Counter]);
			Counter++;
		}
	}
	
	return RetVal;
}


Return_Status_t CLCD_SendNumber(CLCD_t *CLCD ,u32 Number){
	Return_Status_t RetVal = Return_OK;
	u32 Reversed_Number = 1;
	
	if(NULL_POINTER == CLCD){
		RetVal = Return_NOK;
	}
	
	else{
		while(0 != Number){
			Reversed_Number = (Reversed_Number * 10) + (Number % 10);
			Number /= 10;
		}
		while(1 != Reversed_Number){
			RetVal = CLCD_SendData(CLCD , ((Reversed_Number % 10 )+ '0'));
			Reversed_Number /= 10;
		}
	}
	
	return RetVal;
}

Return_Status_t CLCD_GoToX_Y(CLCD_t *CLCD , ROW_t Row , COL_t Col){
	Return_Status_t RetVal = Return_OK;
	u8 X__Y = DDRAM_ADDRESS;
	if(CLCD == NULL_POINTER){
		RetVal = Return_NOK;
	}
	
	else{
		#if CLCD_TYPE == CLCD_2x16
			if(Row > CLCD_ROW2 || Row < CLCD_ROW1 || Col > CLCD_COL16 || Col < CLCD_COL1){
				X__Y = DDRAM_ADDRESS;
			}
			else if(CLCD_ROW1 == Row){
				X__Y += Col;
			}	
			else if(CLCD_ROW2 == Row){
				X__Y += 0x40 + Col  ;
			}
		#elif CLCD_TYPE == CLCD_4x16
			if(Row > CLCD_ROW4 || Row < CLCD_ROW1 || Col > CLCD_COL16 || Col < CLCD_COL1){
				X__Y = DDRAM_ADDRESS;
			}
			else if(CLCD_ROW1 == Row){
				X__Y += Col;
			}
			else if(CLCD_ROW2 == Row){
				X__Y += 0x40 + Col  ;
			}
			else if(CLCD_ROW3 == Row){
				X__Y += 0x10 + Col;
			}
			else if(CLCD_ROW4 == Row){
				X__Y += 0x50 + Col  ;
			}
		
		#endif
		RetVal = CLCD_SendCommond(CLCD , X__Y);
	}
	
	return RetVal;
}

Return_Status_t CLCD_SetCustomChar(CLCD_t *CLCD ,const char Custom_Character[] , u8 Custom_Position ,u8 Row , u8 Col){
	Return_Status_t RetVal = Return_OK;
	
	if(NULL_POINTER == CLCD || Custom_Character == NULL_POINTER){
		RetVal = Return_NOK;
	}
	
	else{
			u8 Counter = 0;
			RetVal = CLCD_SendCommond(CLCD , (CGRAM_ADDRESS + Custom_Position * 8) );
			_delay_ms(1);
			
			for(Counter = 0 ; Counter < 8 ; Counter++){
				RetVal = CLCD_SendData(CLCD , Custom_Character[Counter]);
				
			}
			
			RetVal = CLCD_GoToX_Y(CLCD , Row , Col);
			
	}
	
	return RetVal;
}

Return_Status_t CLCD_ClearScreen(CLCD_t *CLCD){
	Return_Status_t RetVal = Return_OK;
	
	if(NULL_POINTER == CLCD){
		RetVal = Return_NOK;
	}
	
	else{
		RetVal = CLCD_SendCommond(CLCD , CLCD_DISPLAY_CLEAR);
		_delay_ms(5);
	}
	
	return RetVal;
}


Return_Status_t static CLCD_FallingEdge(CLCD_t *CLCD){
	Return_Status_t RetVal = Return_OK;
	
	if(NULL_POINTER == CLCD){
		RetVal = Return_NOK;
	}
	
	else{
		RetVal = DIO_SetPinValue(CLCD->Commond_Port , CLCD->E_Pin , DIO_Logic_HIGH);
		_delay_ms(1);
		RetVal = DIO_SetPinValue(CLCD->Commond_Port , CLCD->E_Pin , DIO_Logic_LOW);
		_delay_ms(1);
	}
	
	return RetVal;
}








