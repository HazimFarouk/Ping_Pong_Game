/*
 * DIO_program.c
 *
 * Created: 1/28/2024 2:50:21 PM
 *  Author: dell
 */ 
/*********************Includes*********************************/
#include "DIO_interface.h"
#include "../../LIB/BIT_MATH.h"

/*********************Registers********************************/
volatile u8 *PORT_Register[] = {&PORTA_Register , &PORTB_Register , &PORTC_Register , &PORTD_Register};
volatile u8 *PIN_Register[]  = {&PINA_Register  , &PINB_Register  , &PINC_Register  , &PIND_Register };
volatile u8 *DDR_Register[]  = {&DDRA_Register  , &DDRB_Register  , &DDRC_Register  , &DDRD_Register };
	
	
/************************************************************************************************************************************************/
/*****************************************************************I/O PINS***********************************************************************/
/************************************************************************************************************************************************/


/* Name : DIO_SetPinDirection
 * Breif : This Function set the direction of the Pin  (INPUT || OUTPUT || INPUT_PULL_UP)
 * Parameters :
  	  =>Port --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Pin  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
  	  =>Direction --> Pin Direction [ DIO_Direction_OUTPUT , DIO_Direction_INPUT , DIO_Direction_INPUT_PULL_UP ]
 * return : its status
 */
Return_Status_t DIO_SetPinDirection(Port_indix_t Port , Pin_indix_t Pin , Direction_t Direction){
	Return_Status_t RetVal = Return_OK;
	
	if((DIO_MinPortIndex <= Port && DIO_MaxPortIndex >= Port) && (DIO_MinPinIndex <= Pin && DIO_MaxPinIndex >= Pin)){
		if(DIO_Direction_OUTPUT == Direction){
			SET_BIT(*DDR_Register[Port] , Pin);
		}
		
		else if(DIO_Direction_INPUT == Direction){
			CLR_BIT(*DDR_Register[Port] , Pin);
		}
		
		else if(DIO_Direction_INPUT_PULL_UP == Direction){
			CLR_BIT(*DDR_Register[Port] , Pin);
			SET_BIT(*PORT_Register[Port] , Pin);
		}
		
		else{
			RetVal = Return_NOK;
		}
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

/****************************************************************************************************************************************************************/
/* Name : DIO_SetPinValue
 * Breif : This Function set the Value of the Pin  (HIGH || LOW)
 * Parameters :
  	  =>Port --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Pin  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
  	  =>Logic --> Pin Direction [ DIO_Direction_HIGH , DIO_Direction_LOW ]
 * return : its status
 */
Return_Status_t DIO_SetPinValue(Port_indix_t Port , Pin_indix_t Pin , Logic_t Logic){
	Return_Status_t RetVal = Return_OK;
	
	if((DIO_MinPortIndex <= Port && DIO_MaxPortIndex >= Port) && (DIO_MinPinIndex <= Pin && DIO_MaxPinIndex >= Pin)){
		if(DIO_Logic_HIGH == Logic){
			SET_BIT(*PORT_Register[Port] , Pin);
		}
		
		else if(DIO_Logic_LOW == Logic){
			CLR_BIT(*PORT_Register[Port] , Pin);
		}
		
		else{
			RetVal = Return_NOK;
		}
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

/****************************************************************************************************************************************************************/
/* Name : DIO_GetPinValue
 * Breif : This Function Get the Value of the Pin
 * Parameters :
 	  =>Port --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Pin  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
  	  =>*Value  --> pointer to recieve the pin value
 * return : its status and recieve Pin Value in pointer
 */
Return_Status_t DIO_GetPinValue(Port_indix_t Port , Pin_indix_t Pin , u8 *Value){
	Return_Status_t RetVal = Return_OK;
	
	if((DIO_MinPortIndex <= Port && DIO_MaxPortIndex >= Port) && 
	   (DIO_MinPinIndex <= Pin && DIO_MaxPinIndex >= Pin) && 
	   (Value != NULL_POINTER)){
		*Value = GET_BIT(*PIN_Register[Port] , Pin);
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

/****************************************************************************************************************************************************************/
/* Name : DIO_TogglePinValue
 * Breif : This Function Toggle the Value of the Pin
 * Parameters :
  	  =>Port --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Pin  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
 * return : its status
 */
Return_Status_t DIO_TogglePinValue(Port_indix_t Port , Pin_indix_t Pin){
	Return_Status_t RetVal = Return_OK;
	
	if((DIO_MinPortIndex <= Port && DIO_MaxPortIndex >= Port) && (DIO_MinPinIndex <= Pin && DIO_MaxPinIndex >= Pin)){
		TGL_BIT(*PORT_Register[Port] , Pin);
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

/**********************************************************************************************************************************************************/
/*******************************************************************I/O PORTS******************************************************************************/
/**********************************************************************************************************************************************************/

/* Name : DIO_SetPortDirection
 * Breif : This Function Set the direction of the port (INPUT || OUTPUT || DIO_Direction_INPUT_PULL_UP)
 * Parameters :
 	  =>Port --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
 	  =>Direction  --> Port direction [ DIO_Direction_OUTPUT , DIO_Direction_INPUT ]
 * return :  its status
 */
Return_Status_t DIO_SetPortDirection(Port_indix_t Port , Direction_t Direction){
	Return_Status_t RetVal = Return_OK;
	
	if(DIO_MinPortIndex <= Port && DIO_MaxPortIndex >= Port){
		if(DIO_Direction_OUTPUT == Direction){
			*DDR_Register[Port] = DIO_PORT_OUTPUT;
		}
		
		else if(DIO_Direction_INPUT == Direction){
			*DDR_Register[Port] = DIO_PORT_INPUT;
		}
		
		else if(DIO_Direction_INPUT_PULL_UP == Direction){
			*DDR_Register[Port]  = DIO_PORT_INPUT;
			*PORT_Register[Port] = DIO_PORT_HIGH;
		}
		
		else{
			RetVal = Return_NOK;
		}
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

/****************************************************************************************************************************************************************/
/* Name : DIO_SetPortValue
 * Breif : This Function Set value on Port
 * Parameters :
  	  =>Port --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
 	  =>Value  --> The Value  [DIO_PORT_HIGH , DIO_PORT_LOW , Another Value]
 * return : its status
 */
Return_Status_t DIO_SetPortValue(Port_indix_t Port , Logic_t Logic){
	Return_Status_t RetVal = Return_OK;
	
	if(DIO_MinPortIndex <= Port && DIO_MaxPortIndex >= Port){
		if(DIO_Logic_HIGH == Logic){
			*PORT_Register[Port] = DIO_PORT_HIGH;
		}
		
		else if(DIO_Logic_LOW == Logic){
			*PORT_Register[Port] = DIO_PORT_LOW;
		}
		
		else{
			*PORT_Register[Port] = Logic;
		}
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

/****************************************************************************************************************************************************************/
/* Name : DIO_GetPortValue
 * Breif : This Function GET value on Port
 * Parameters :
 	  =>Port --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
 	  =>*Value  --> pointer to recieve the port value
 * return : its status and recieve Port Value in pointer
 */
Return_Status_t DIO_GetPortValue(Port_indix_t Port , u8 *Value){
	Return_Status_t RetVal = Return_OK;
	
	if((DIO_MinPortIndex <= Port && DIO_MaxPortIndex >= Port) && NULL_POINTER != Value){
		*Value = *PIN_Register[Port];
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

/****************************************************************************************************************************************************************/
/* Name : DIO_TogglePortValue
 * Breif : This Function Toggle value on Port
 * Parameters :
 	  =>Port --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
 * return : its status
 */
Return_Status_t DIO_TogglePortValue(Port_indix_t Port){
	Return_Status_t RetVal = Return_OK;
	
	if(DIO_MinPortIndex <= Port && DIO_MaxPortIndex >= Port){
		*PORT_Register[Port] = ~(*PORT_Register[Port]);
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

Return_Status_t DIO_SetHighNibbleValue(Port_indix_t Port , Logic_t Logic){
	Return_Status_t RetVal = Return_OK;
	
	Logic = (Logic << 4);
	
	if(DIO_MinPortIndex <= Port && DIO_MaxPortIndex >= Port){
		*PORT_Register[Port] &= DIO_LOW_NIBBLE;
		*PORT_Register[Port] |= Logic;
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

Return_Status_t DIO_SetLowNibbleValue(Port_indix_t Port , Logic_t Logic){
	Return_Status_t RetVal = Return_OK;
	
	Logic = (Logic & DIO_HIGH_NIBBLE);
	
	if(DIO_MinPortIndex <= Port && DIO_MaxPortIndex >= Port){
		*PORT_Register[Port] &= DIO_HIGH_NIBBLE;
		*PORT_Register[Port] |= Logic;
	}
	
	else{
		RetVal = Return_NOK;
	}
	
	return RetVal;
}

