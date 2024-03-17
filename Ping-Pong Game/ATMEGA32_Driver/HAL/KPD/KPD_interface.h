/*
 * KPD_interface.h
 *
 * Created: 2/3/2024 8:39:51 PM
 *  Author: dell
 */ 


#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

#include "../../MCAL/DIO/DIO_interface.h"
//#include "KPD_config.h"
#include "KPD_private.h"
#include "util/delay.h"



#define KPD_ROWS_START DIO_PIN0
#define KPD_ROWS_END   DIO_PIN3

#define KPD_COLS_START DIO_PIN4
#define KPD_COLS_END   DIO_PIN7

typedef struct{
	Port_indix_t KPD_Port;
	/*The upper nipple for rows  and the lower one for columns*/
}KPD_t;

#define KPD_NOT_PRESSED 0xFF

Return_Status_t KPD_Initialization(KPD_t KPD);
Return_Status_t KPD_GetPressed(KPD_t KPD , u8 *KPD_Button);

#endif /* KPD_INTERFACE_H_ */