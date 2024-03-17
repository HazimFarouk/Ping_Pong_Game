/*
 * CLCD_interface.h
 *
 * Created: 2/3/2024 10:17:01 PM
 *  Author: dell
 */ 


#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_


/****************************Includes************************************/
#include "../../LIB/STD_Types.h"
#include "../../MCAL/DIO/DIO_interface.h"

#define CLCD_4BIT 0b00100000

/*************************************Type********************/
#define CLCD_4x16 1
#define CLCD_2x16 2
#define CLCD_TYPE CLCD_4x16

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																																					 //			
/**************************Commonds For 4_BIT*******************************/																	     //
#define CLCD_4BIT_FUNCTION_SET_2LINE_5x8FONT  0b00101000     /**********************Function Set**********************/								 //
#define CLCD_4BIT_FUNCTION_SET_1LINE_5x8FONT  0b00100000	 /***********************0b0010NFXX***********************/								 //
#define CLCD_4BIT_FUNCTION_SET_2LINE_5x11FONT 0b00101100	 /***N = Display Lines ->> 1 for 2 line & 0 for 1 line****/								 //
#define CLCD_4BIT_FUNCTION_SET_1LINE_5x11FONT 0b00100100	 /***F = Font Size     ->> 1 for 5x11 and 0 for 5x8*******/								 //
																																					 //
/**************************Commonds For 8_BIT*******************************/																		 //
#define CLCD_8BIT_FUNCTION_SET_2LINE_5x8FONT  0b00111000     /**********************Function Set**********************/						   		 //
#define CLCD_8BIT_FUNCTION_SET_1LINE_5x8FONT  0b00110000	 /***********************0b0011NFXX***********************/						   		 //
#define CLCD_8BIT_FUNCTION_SET_2LINE_5x11FONT 0b00111100	 /***N = Display Lines ->> 1 for 2 line & 0 for 1 line****/						   		 //
#define CLCD_8BIT_FUNCTION_SET_1LINE_5x11FONT 0b00110100	 /***F = Font Size     ->> 1 for 5x11 and 0 for 5x8*******/						   		 //
																																					 //
																																					 //
/*********************************************************************************************************************************************/		 //
#define CLCD_DISPLAY_ON_CURSOR_BLINK          0b00001111	 /**********************Display On/Off Control************/				       /**/		 //
#define CLCD_DISPLAY_ON						  0b00001100	 /***********************0b00001DCB************************/				   /**/		 //
#define CLCD_DISPLAY_ON_CURSOR				  0b00001110	 /***B = Display On/Off->> 0 for Off % 1 for On************/				   /**/		 //
#define CLCD_DISPLAY_ON_BLINK				  0b00001101	 /***C = Cursor On/Off ->> 0 for Off % 1 for On************/				   /**/		 //
#define CLCD_DISPLAY_OFF					  0b00000000	 /***B = Blink Cursor  ->> 0 for Off % 1 for On************/				   /**/		 //
											 				 																		       /**/		 //
#define CLCD_DISPLAY_CLEAR				      0b00000001	 																		       /**/		 //
											 				 																		       /**/		 //
#define CLCD_ENTRY_MODE_SHIFT_LEFT            0b00000111	 /**********************Entry Mode Set*********************************/	   /**/		 //
#define CLCD_ENTRY_MODE_SHIFT_RIGHT			  0b00000101	 /***********************0b000001(I/D)SH*******************************/	   /**/		 //
#define CLCD_ENTRY_MODE_DECREMENT_POSITION	  0b00000100	 /***I/D = Increment Position ->> 1 for Increment & 0 for Decrement****/	   /**/		 //
#define CLCD_ENTRY_MODE_INCREMENT_POSITION	  0b00000110	 /***SH  = Display Shift All Time ->> 1 for On and 0 for Off***********/	   /**/		 //
/*********************************************************************************************************************************************/		 //
																																					 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ONE_STEP_CURSOR_LEFT			 0b00010000		/**********************Cursor Or Display Shift************************/
#define ONE_STEP_CURSOR_RIGHT			 0b00010100		/************************0b0001(S/C)(R/L)XX***************************/
#define ONE_STEP_SHIFT_LEFT				 0b00011000		/***S/C = Shift Display **********************************************/
#define ONE_STEP_SHIFT_RIGHT			 0b00011100		/***R/L = Shift Cursor ***********************************************/

#define CLCD_RETURN_HOME                      0b00000010     /*********************************************************************/


#define CGRAM_ADDRESS                    0b01000000	   /*Start AddressFor Write Custom Character*/

#define DDRAM_ADDRESS                    0b10000000    /*Start Address For Display Data*/


typedef enum{
	 CLCD_COL1,
	 CLCD_COL2,
	 CLCD_COL3,
	 CLCD_COL4,
	 CLCD_COL5,
	 CLCD_COL6,
	 CLCD_COL7,
	 CLCD_COL8,
	 CLCD_COL9,
	 CLCD_COL10,
	 CLCD_COL11,
	 CLCD_COL12,
	 CLCD_COL13,
	 CLCD_COL14,
	 CLCD_COL15,
	 CLCD_COL16
}COL_t;

typedef enum{
	CLCD_ROW1,
	CLCD_ROW2,
	CLCD_ROW3,
	CLCD_ROW4
}ROW_t;

typedef enum{
	CLCD_4_Bit_Mode,
	CLCD_8_Bit_Mode
}BIT_Mode_t;


typedef struct{
	BIT_Mode_t   Bits_Mode : 1;
	Port_indix_t Data_Port : 3;
	u8           Data_Nibble;
	Port_indix_t Commond_Port : 3;
	Pin_indix_t  RS_Pin : 4;
	Pin_indix_t  RW_Pin : 4;
	Pin_indix_t  E_Pin : 4;
}CLCD_t;

Return_Status_t CLCD_Initialization(CLCD_t *CLCD);
Return_Status_t CLCD_SendCommond(CLCD_t *CLCD , u8 Commond);
Return_Status_t CLCD_SendData(CLCD_t *CLCD , u8 Data);
Return_Status_t CLCD_SendString(CLCD_t *CLCD , char *String);

Return_Status_t CLCD_SendNumber(CLCD_t *CLCD , u32 Number);
Return_Status_t CLCD_GoToX_Y(CLCD_t *CLCD , ROW_t Row , COL_t Col);
Return_Status_t CLCD_SetCustomChar(CLCD_t *CLCD ,const char Custom_Character[] , u8 Custom_Position ,u8 Row , u8 Col);
Return_Status_t CLCD_ClearScreen(CLCD_t *CLCD);


#endif /* CLCD_INTERFACE_H_ */



