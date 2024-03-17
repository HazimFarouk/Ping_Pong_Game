/*
 * BUZ_interface.h
 *
 * Created: 1/28/2024 7:45:36 PM
 *  Author: dell
 */ 


#ifndef BUZ_INTERFACE_H_
#define BUZ_INTERFACE_H_

/****************************Includes************************************/
#include "../../LIB/STD_Types.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "BUZ_private.h"
#include "BUZ_config.h"

/***************************BUZ PINS*************************************/


/***************************BUZ PORTS*************************************/


/***************************Active Status*************************************/


typedef struct{
	Port_indix_t Port : 3;
	Pin_indix_t  Pin  : 4;
	Active_Status_t  Status : 1;
}BUZ_t;

/***************************Function*************************************/
Return_Status_t BUZ_Initialization(BUZ_t BUZ);
Return_Status_t BUZ_On(BUZ_t BUZ);
Return_Status_t BUZ_Off(BUZ_t BUZ);
Return_Status_t BUZ_Toggle(BUZ_t BUZ);



#endif /* BUZ_INTERFACE_H_ */