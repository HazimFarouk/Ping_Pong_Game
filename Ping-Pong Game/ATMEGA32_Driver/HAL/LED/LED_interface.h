/*
 * LED_interface.h
 *
 * Created: 1/28/2024 6:49:19 PM
 *  Author: dell
 */ 


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/****************************Includes************************************/
#include "../../LIB/STD_Types.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "LED_config.h"
#include "LED_private.h"



/*******************************Type************************************/
typedef struct{
	Port_indix_t Port : 3;
	Pin_indix_t  Pin  : 4;
	Active_Status_t  Status : 1;
}LED_t;

/***************************Function*************************************/
Return_Status_t LED_Initialization(LED_t LED);
Return_Status_t LED_On(LED_t LED);
Return_Status_t LED_Off(LED_t LED);
Return_Status_t LED_Toggle(LED_t LED);


#endif /* LED_INTERFACE_H_ */