/*
 * main.h
 *
 * Created: 1/28/2024 2:07:57 PM
 *  Author: dell
 */ 


#ifndef MAIN_H_
#define MAIN_H_


/*****************************CPU PULSES*********************************/
#define F_CPU 8000000UL

/*****************************Includes*********************************/
#include "../LIB/STD_Types.h"
#include "util/delay.h"
#include "../HAL/LED/LED_interface.h"
#include "../HAL/Switch/SW_interface.h"
#include "../HAL/SSD/SSD_interface.h"
#include "../HAL/Relay/Relay_interface.h"
#include "../HAL/KPD/KPD_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../HAL/BUZ/BUZ_interface.h"


/*************************Custom Characters****************************/
const char Custom_Characters_Player[8] = {0b000100,0b001110,0b010101,0b000100,0b000100,0b001010,0b010001,0b000000};
const char Custom_Characters_Ball[8] = {0b000000,0b001110,0b011111,0b011111,0b011111,0b001110,0b000000,0b000000};


/*****************************Macros***********************************/
#define PLAYER_POSITION_IN_CGRAM    0
#define BALL_POSITION_IN_CGRAM      1
#define GAME_ROUNDS				    3
#define START_FROM_LEFT_BEGIN		CLCD_COL15
#define START_FROM_RIGHT_BEGIN		CLCD_COL2
#define START_FROM_CENTER			CLCD_COL8


Return_Status_t Main_Initialization();


void ISR1_PlayerOneMove(void);
void ISR2_PlayerTwoMove(void);

Return_Status_t Start_Round(void);

Return_Status_t Ball_MoveToRight(u8 Start_Positoin);
Return_Status_t Ball_MoveToLeft (u8 Start_Positoin);

Return_Status_t Check_Right(u8 *Catch_Flag);
Return_Status_t Check_Left (u8 *Catch_Flag);



#endif /* MAIN_H_ */