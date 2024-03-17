/*
 * DIO_interface.h
 *
 * Created: 1/28/2024 2:49:55 PM
 *  Author: dell
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/*******************Includes************************/
#include "../../LIB/STD_Types.h"
#include "DIO_config.h"
#include "DIO_private.h"
/**********************PINS**************************/

typedef enum{
	DIO_PIN0 = 0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7
}Pin_indix_t;

#define DIO_MaxPinIndex 7
#define DIO_MinPinIndex 0


/**********************PORTS**************************/
typedef enum{
	DIO_PORTA = 0,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD
}Port_indix_t;

#define DIO_MaxPortIndex 3
#define DIO_MinPortIndex 0

/***********************Nibbles************************/
#define DIO_HIGH_NIBBLE  0xF0
#define DIO_LOW_NIBBLE  0x0F

/********************Directions**********************/
typedef enum{
	DIO_Direction_INPUT = 0,
	DIO_Direction_OUTPUT = 0xFF,
	DIO_Direction_INPUT_PULL_UP
}Direction_t;

#define DIO_Pin_OUTPUT 1
#define DIO_Pin_INPUT 0

#define DIO_PORT_OUTPUT 0xFF
#define DIO_PORT_INPUT 0x00


/******************Logic**********************/
typedef enum{
	DIO_Logic_LOW = 0,
	DIO_Logic_HIGH = 0xFF
}Logic_t;
#define DIO_PIN_HIGH 1
#define DIO_PIN_LOW 0

#define DIO_PORT_HIGH 0xFF
#define DIO_PORT_LOW 0x00

/***************************Active Status*************************************/
typedef enum{
	DIO_Active_LOW,
	DIO_Active_HIGH
}Active_Status_t;

/*********************pin_config********************/
typedef struct{
	Port_indix_t Port : 3;
	Pin_indix_t  Pin  : 3;
	Direction_t Direction;
	Logic_t Logic;  
}pin_config_t;

/****************Functions*******************/

/************************************************************************/
/*******************************I/O PINS*********************************/
/************************************************************************/

/* Name : DIO_SetPinDirection
 * Brief : This Function set the direction of the Pin  (INPUT || OUTPUT || INPUT_PULL_UP)
 * Parameters :
  	  =>Port --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Pin  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
  	  =>Direction --> Pin Direction [ DIO_Direction_OUTPUT , DIO_Direction_INPUT , DIO_Direction_INPUT_PULL_UP ]
 * return : its status
 */
Return_Status_t DIO_SetPinDirection		(Port_indix_t Port , Pin_indix_t Pin , Direction_t Direction);

/* Name : DIO_SetPinValue
 * Brief : This Function set the Value of the Pin  (HIGH || LOW)
 * Parameters :
  	  =>Port --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Pin  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
  	  =>Logic --> Pin Direction [ DIO_Direction_HIGH , DIO_Direction_LOW ]
 * return : its status
 */
Return_Status_t DIO_SetPinValue			(Port_indix_t Port , Pin_indix_t Pin , Logic_t Logic		);

/* Name : DIO_GetPinValue
 * Brief : This Function Get the Value of the Pin
 * Parameters :
 	  =>Port --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Pin  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
  	  =>*Value  --> pointer to recieve the pin value
 * return : its status and receive Pin Value in pointer
 */
Return_Status_t DIO_GetPinValue			(Port_indix_t Port , Pin_indix_t Pin , u8 *Value			);

/* Name : DIO_TogglePinValue
 * Brief : This Function Toggle the Value of the Pin
 * Parameters :
  	  =>Port --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Pin  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
 * return : its status
 */
Return_Status_t DIO_TogglePinValue		(Port_indix_t Port , Pin_indix_t Pin						);


/************************************************************************/
/*******************************I/O PORTS********************************/
/************************************************************************/

/* Name : DIO_SetPortDirection
 * Brief : This Function Set the direction of the port (INPUT || OUTPUT || DIO_Direction_INPUT_PULL_UP)
 * Parameters :
 	  =>Port --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
 	  =>Direction  --> Port direction [ DIO_Direction_OUTPUT , DIO_Direction_INPUT ]
 * return :  its status
 */
Return_Status_t DIO_SetPortDirection	(Port_indix_t Port , Direction_t Direction);

/* Name : DIO_SetPortValue
 * Brief : This Function Set value on Port
 * Parameters :
  	  =>Port --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
 	  =>Value  --> The Value  [DIO_PORT_HIGH , DIO_PORT_LOW , Another Value]
 * return : its status
 */
Return_Status_t DIO_SetPortValue		(Port_indix_t Port , Logic_t Logic		  );

/* Name : DIO_GetPortValue
 * Brief : This Function GET value on Port
 * Parameters :
 	  =>Port --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
 	  =>*Value  --> pointer to recieve the port value
 * return : its status and receive Port Value in pointer
 */
Return_Status_t DIO_GetPortValue		(Port_indix_t Port , u8 *Value			  );

/* Name : DIO_TogglePortValue
 * Brief : This Function Toggle value on Port
 * Parameters :
 	  =>Port --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
 * return : its status
 */
Return_Status_t DIO_TogglePortValue		(Port_indix_t Port						  );


Return_Status_t DIO_SetHighNibbleValue		(Port_indix_t Port , Logic_t Logic		  );
Return_Status_t DIO_SetLowNibbleValue		(Port_indix_t Port , Logic_t Logic		  );

#endif /* DIO_INTERFACE_H_ */