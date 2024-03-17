/*
 * SW_interface.h
 *
 * Created: 1/28/2024 7:55:29 PM
 *  Author: dell
 */ 


#ifndef SW_INTERFACE_H_
#define SW_INTERFACE_H_

/******************************Includes**********************************/
#include "../../LIB/STD_Types.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "SW_config.h"
#include "SW_private.h"

/***************************SW PINS*************************************/


/***************************SW PORTS*************************************/


#define SW_PRESSED	   1
#define SW_NOT_PRESSED 0

typedef enum{
	SW_Int_PULL_UP,
	SW_Ext_Pull_UP,
	SW_Ext_Pull_DOWN,
	SW_Floating    
}SW_Status_t;

typedef struct{
	Port_indix_t Port : 3;
	Pin_indix_t  Pin  : 3;
	SW_Status_t PULL_Status : 2;
}SW_t;

Return_Status_t SW_Initialization(SW_t SW);
u8 SW_GetPressed(SW_t SW);

#endif /* SW_INTERFACE_H_ */