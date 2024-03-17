/*
 * Relay_interface.h
 *
 * Created: 2/3/2024 12:37:27 AM
 *  Author: dell
 */ 


#ifndef RELAY_INTERFACE_H_
#define RELAY_INTERFACE_H_

/****************************Includes************************************/
#include "../../LIB/STD_Types.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "Relay_config.h"
#include "Relay_private.h"

typedef struct{
	Port_indix_t Port : 3;
	Pin_indix_t  Pin  : 4;
	Active_Status_t Status : 1;
}Relay_t;

Return_Status_t Relay_Initialization(Relay_t Relay);
Return_Status_t Relay_On(Relay_t Relay);
Return_Status_t Relay_Off(Relay_t Relay);
Return_Status_t Relay_Toggle(Relay_t Relay);

#endif /* RELAY_INTERFACE_H_ */