/*
 * SSD_interface.h
 *
 * Created: 2/3/2024 1:20:07 AM
 *  Author: dell
 */ 


#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_


/****************************Includes************************************/
#include "../../LIB/STD_Types.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "SSD_config.h"
#include "SSD_private.h"

/***********************************Nums**********************************/



/*******************************Type************************************/
typedef enum{
	SSD_Common_Cathode,
	SSD_Common_Anode,
	SSD_DirectCommon
}SSD_Common_t;

typedef struct{
	Port_indix_t Data_Port;
	Port_indix_t Enable_Port;
	Pin_indix_t  Enable_Pin;
	SSD_Common_t Common_Type;
}SSD_t;

/***************************Function*************************************/
Return_Status_t SSD_Initialization(SSD_t SSD);
Return_Status_t SSD_Enable(SSD_t SSD);
Return_Status_t SSD_Disable(SSD_t SSD);
Return_Status_t SSD_DisplayNumber(SSD_t SSD , u8 Number);


#endif /* SSD_INTERFACE_H_ */