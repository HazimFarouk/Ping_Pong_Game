/*
 * ATMEGA32_Driver.c
 *
 * Created: 1/28/2024 2:01:23 PM
 * Author : dell
 */ 

#include "main.h"


										   
u8 Ball_Row[7] = {CLCD_ROW1 , CLCD_ROW2 , CLCD_ROW3 , CLCD_ROW4 , CLCD_ROW3 , CLCD_ROW2 , CLCD_ROW1}; /*This describe the moving of the ball up and down*/
u8 Ball_Row_Counter = 0, Ball_Col = 0;											 /*Iterator to iterate through the Ball_Row array and the Col position */

volatile u8 PlayerOne_Current_Position = CLCD_ROW1 , PlayerTwo_Current_Position = CLCD_ROW1;		  /*Players Current Position Row1 -> Row4*/



Return_Status_t RetVal = Return_OK;				/*Return status to check if the functions works as expected*/


CLCD_t CLCD = {							/*Initialize the lcd int 4 bit mode*/
	.Bits_Mode = CLCD_8_Bit_Mode,
	.Data_Port = DIO_PORTC,
	
	.Commond_Port = DIO_PORTD,
	.RS_Pin = DIO_PIN5,
	.RW_Pin = DIO_PIN6,
	.E_Pin = DIO_PIN7
};

EXTI_t ISR_PlayerOne = {				/*ISR for player one to control moving in rows*/
	.EXTI_INTx = EXTI_INT0,
	.EXTI_Handler = ISR1_PlayerOneMove,
	.EXTI_TRIGGER = EXTI_FALLING_EDGE_TRIGGER
};

EXTI_t ISR_PlayerTwo = {				/*ISR for player two to control moving in rows*/
	.EXTI_INTx = EXTI_INT1,
	.EXTI_Handler = ISR2_PlayerTwoMove,
	.EXTI_TRIGGER = EXTI_FALLING_EDGE_TRIGGER
};

SSD_t PlayerOne_Score_Display = {		/*Initialize 7 segment display to display player one score*/
	.Data_Port = DIO_PORTA,
	.Common_Type = SSD_Common_Cathode
};
SSD_t PlayerTwo_Score_Display = {		/*Initialize 7 segment display to display player two score*/
	.Data_Port = DIO_PORTB,
	.Common_Type = SSD_Common_Cathode
};
u8 PlayerOne_Score = 0 , PlayerTwo_Score = 0;

SW_t Turn_On_Off = {					/*Initialize switch to turn on the game and start new game*/
	.Port = DIO_PORTD,
	.Pin  = DIO_PIN0,
	.PULL_Status =SW_Int_PULL_UP 
};

BUZ_t Buzzer = {						/*Initialize buzzer to run when any player score a point*/
	.Port = DIO_PORTD,
	.Pin  = DIO_PIN4,
	.Status = DIO_Active_HIGH
};

u8 Read_Switch = SW_NOT_PRESSED;		/*Variable to read the turn_on_off button state*/
u8 Catch_Status = 0;					/*Variable to check if the player has scored a point so it returns 1 otherwise 0*/
int main(void)
{
	
	
	RetVal = Main_Initialization(); /**Initialize LCD and SSD and Make 2 interrrupt pins input pins**/
	
	RetVal = CLCD_GoToX_Y(&CLCD , CLCD_ROW2 , CLCD_COL2);				/*Go to specific positoin* and print the start message*/
	RetVal = CLCD_SendString(&CLCD , "Press Turn On      To Start");
	
	Read_Switch = SW_GetPressed(Turn_On_Off);
	while(Read_Switch == SW_NOT_PRESSED){					/*Stuck here until he press the turn_on_off button*/
		Read_Switch = SW_GetPressed(Turn_On_Off);
	}
	RetVal = CLCD_ClearScreen(&CLCD);						/*Clear the start message when he press the key*/
	
	/*Send Custom Char for the player and set it in PLAYER_POSITION_IN_CGRAM*/
	RetVal = CLCD_SetCustomChar(&CLCD , Custom_Characters_Player , PLAYER_POSITION_IN_CGRAM , CLCD_ROW1 , CLCD_COL1); 
	
	/*Send Custom Char for the Ball and set it in BALL_POSITION_IN_CGRAM*/
	RetVal = CLCD_SetCustomChar(&CLCD , Custom_Characters_Ball   , BALL_POSITION_IN_CGRAM   , CLCD_ROW1 , CLCD_COL1);
	
	/***********************Initialize EXTI interrupt***********************/
	RetVal = EXTI_Initializatoin(&ISR_PlayerOne);
	RetVal = EXTI_Initializatoin(&ISR_PlayerTwo);
	
	/***********************Disable Until the countdown ends************************/
	RetVal = EXTI_DisableInterrupt(&ISR_PlayerOne);
	RetVal = EXTI_DisableInterrupt(&ISR_PlayerTwo);
	
	
    while (1) 
    {
		PlayerOne_Score = 0;			/*Set the score of player one*/
		PlayerTwo_Score = 0;			/*Set the score of player two*/
		RetVal = SSD_DisplayNumber(PlayerOne_Score_Display , PlayerOne_Score);	/*Display the score of player one*/
		RetVal = SSD_DisplayNumber(PlayerTwo_Score_Display , PlayerTwo_Score);	/*Display the score of player two*/
		
		/**Display The Start Message as a counter*/
		RetVal = CLCD_GoToX_Y(&CLCD , CLCD_ROW2 , CLCD_COL2);
		for(int Counter = 5 ; Counter >= 1 ; --Counter){
			RetVal = CLCD_GoToX_Y(&CLCD , CLCD_ROW2 , CLCD_COL2);
			RetVal = CLCD_SendString(&CLCD , "The Game Will    Start In : ");
			RetVal = CLCD_SendData(&CLCD , Counter + '0');
			_delay_ms(200);
		}
		RetVal = CLCD_ClearScreen(&CLCD);
		
		/***********************Enable EXTI interrupt***********************/
		RetVal = EXTI_EnableInterrupt(&ISR_PlayerOne);
		RetVal = EXTI_EnableInterrupt(&ISR_PlayerTwo);
		
		
		RetVal = Start_Round();							/********Set the players at the beginnig************************/
		
		
		while(PlayerOne_Score < GAME_ROUNDS && PlayerTwo_Score < GAME_ROUNDS){		/*Iterate until any player win the game*/
			
			
			
			RetVal = Ball_MoveToRight(START_FROM_RIGHT_BEGIN);	/*Make the move to the right most*/
			RetVal = Check_Right(&Catch_Status);				/*Check if player two  catch the ball or player one scores a point*/
			if(Catch_Status){
				Catch_Status = 0;		
			}
				
			if(PlayerOne_Score == GAME_ROUNDS){			/*check if player one win the game and if he does he wins the game and no need to continue*/
				break;	
			}
			
			RetVal = Ball_MoveToLeft(START_FROM_LEFT_BEGIN);	/*Make the move to the left most*/
			RetVal = Check_Left(&Catch_Status);					/*Check if player one catch the ball or player two scores a point*/
			if(Catch_Status){
				Catch_Status = 0;
			}
			
		}
		
		/***********************Disable EXTI interrupt***********************/
		RetVal = EXTI_DisableInterrupt(&ISR_PlayerOne);			/*No more need for interrupt so we disable it*/
		RetVal = EXTI_DisableInterrupt(&ISR_PlayerTwo);
		
		RetVal = CLCD_ClearScreen(&CLCD);						/*Clear the screen and display a message to the winner*/
		if(PlayerOne_Score == GAME_ROUNDS){
			RetVal = CLCD_GoToX_Y(&CLCD , CLCD_ROW2 , CLCD_COL2);
			RetVal = CLCD_SendString(&CLCD , "Player One Win");
		}
		else{
			RetVal = CLCD_GoToX_Y(&CLCD , CLCD_ROW2 , CLCD_COL2);
			RetVal = CLCD_SendString(&CLCD , "Player Two Win");
		}
		_delay_ms(3000);						/*Wait some time to display the winner then clear the screen*/
		RetVal = BUZ_Off(Buzzer);
		RetVal = CLCD_ClearScreen(&CLCD);
		
		RetVal = CLCD_GoToX_Y(&CLCD , CLCD_ROW2 , CLCD_COL1);
		RetVal = CLCD_SendString(&CLCD , "Press Turn On To Start New Game");
		
		Read_Switch = SW_GetPressed(Turn_On_Off);		/*Stuck here until he press turn_on_off button to start new game*/
		while(Read_Switch == SW_NOT_PRESSED){
			Read_Switch = SW_GetPressed(Turn_On_Off);
		}
		RetVal = CLCD_ClearScreen(&CLCD);
		
    }
	
}

/**************************************************************************************/

/******************************Progarm Initializatoin*********************************/
Return_Status_t Main_Initialization(){
	Return_Status_t RetVal = Return_OK;
	
	RetVal = CLCD_Initialization(&CLCD);									  /*Initialize the LCD*/
	
	RetVal = DIO_SetPinDirection(DIO_PORTD , DIO_PIN2 , DIO_Direction_INPUT); /*Set pins as input for the interrupt*/
	RetVal = DIO_SetPinDirection(DIO_PORTD , DIO_PIN3 , DIO_Direction_INPUT);
	
	RetVal = SSD_Initialization(PlayerOne_Score_Display);					  /*Initialize the 7 segment*/
	RetVal = SSD_Initialization(PlayerTwo_Score_Display);
	
	RetVal = SSD_DisplayNumber(PlayerOne_Score_Display , 0);				
	RetVal = SSD_DisplayNumber(PlayerTwo_Score_Display , 0);
	
	RetVal = SW_Initialization(Turn_On_Off);								 /*Initialize the button*/
	
	RetVal = BUZ_Initialization(Buzzer);									 /*Initialize the buzzer*/
	RetVal = DIO_SetPinDirection(DIO_PORTD , DIO_PIN4 , DIO_Direction_OUTPUT); /*Set the pin as output for the buzzer*/
	
	return RetVal;
}


/**************************Set the players at the beginnig****************************/
Return_Status_t Start_Round(void){
	Return_Status_t RetVal = Return_OK;
	
	PlayerOne_Current_Position = CLCD_ROW1;										/*Set the player to the start positoin*/
	PlayerTwo_Current_Position = CLCD_ROW1;										/*Set the player to the start positoin*/
	
	RetVal = CLCD_GoToX_Y(&CLCD , PlayerOne_Current_Position , CLCD_COL1);
	RetVal = CLCD_SendData(&CLCD , PLAYER_POSITION_IN_CGRAM);					/*Display the player pattern*/
	
	
	RetVal = CLCD_GoToX_Y(&CLCD , PlayerTwo_Current_Position , CLCD_COL16);
	RetVal = CLCD_SendData(&CLCD , PLAYER_POSITION_IN_CGRAM);
	
	return RetVal;
}

/**************************************************************************************/

/*********************Check fo the player in the left side**********************/
Return_Status_t Check_Left(u8 *Catch_Flag){
	Return_Status_t RetVal = Return_OK;
	
	if(Ball_Row[Ball_Row_Counter]  != PlayerOne_Current_Position){					/*********Check if the ball isnt's in the same row as the player***/
		
		PlayerTwo_Score++;															/*********Update the player score**********************************/
		RetVal = SSD_DisplayNumber(PlayerTwo_Score_Display , PlayerTwo_Score);		/*********Display the new score************************************/
		
		RetVal = BUZ_On(Buzzer);													/*********Fire the buzzer******************************************/
		
		
		*Catch_Flag = 1;															/*********Change the flage means the the player lose the round*****/
	}
	
	return RetVal;
}

/*********************Check fo the player in the right side**********************/
Return_Status_t Check_Right(u8 *Catch_Flag){
	Return_Status_t RetVal = Return_OK;
	
	if(Ball_Row[Ball_Row_Counter]  != PlayerTwo_Current_Position){
		
		PlayerOne_Score++;
		RetVal = SSD_DisplayNumber(PlayerOne_Score_Display , PlayerOne_Score);
		
		RetVal = BUZ_On(Buzzer);		
		
		
		
		*Catch_Flag = 1;
	}
	
	return RetVal;
}

/**************************************************************************************/

/************************Move from left to right most*************************************/
Return_Status_t Ball_MoveToRight(u8 Start_Positoin){
	Return_Status_t RetVal = Return_OK;
	
	
	for(Ball_Col = Start_Positoin; Ball_Col < CLCD_COL16 ; ++Ball_Col){
		RetVal = EXTI_DisableInterrupt(&ISR_PlayerOne);
		RetVal = EXTI_DisableInterrupt(&ISR_PlayerTwo);
		
		RetVal = CLCD_GoToX_Y(&CLCD , Ball_Row[Ball_Row_Counter] , Ball_Col);
		RetVal = CLCD_SendData(&CLCD , BALL_POSITION_IN_CGRAM);
		RetVal = EXTI_EnableInterrupt(&ISR_PlayerOne);
		RetVal = EXTI_EnableInterrupt(&ISR_PlayerTwo);
		
		Ball_Row_Counter++;
		_delay_ms(200);
		RetVal = BUZ_Off(Buzzer);
		
		RetVal = EXTI_DisableInterrupt(&ISR_PlayerOne);
		RetVal = EXTI_DisableInterrupt(&ISR_PlayerTwo);
		RetVal = CLCD_GoToX_Y(&CLCD , Ball_Row[Ball_Row_Counter - 1] , Ball_Col);
		RetVal = CLCD_SendString(&CLCD , " ");
		RetVal = EXTI_EnableInterrupt(&ISR_PlayerOne);
		RetVal = EXTI_EnableInterrupt(&ISR_PlayerTwo);
		
		
		 if(7 <= Ball_Row_Counter){
			 Ball_Row_Counter = 1;
		 }
	}
	
	return RetVal;
}
		
/************************Move from right to left most*************************************/
Return_Status_t Ball_MoveToLeft(u8 Start_Positoin){
	Return_Status_t RetVal = Return_OK;
	
	/*************Start form specific colum to the end******************/
	for(Ball_Col =  Start_Positoin; Ball_Col > CLCD_COL1 ; --Ball_Col){
		RetVal = EXTI_DisableInterrupt(&ISR_PlayerOne);
		RetVal = EXTI_DisableInterrupt(&ISR_PlayerTwo);
		RetVal = CLCD_GoToX_Y(&CLCD , Ball_Row[Ball_Row_Counter] , Ball_Col);	    /**************Set display to specific points*****************/
		RetVal = CLCD_SendData(&CLCD , BALL_POSITION_IN_CGRAM);						/**************Diaplay the Ball*******************************/
		RetVal = EXTI_EnableInterrupt(&ISR_PlayerOne);								/**************Disable interrupt to not interrupt the function while increase the ball position*/
		RetVal = EXTI_EnableInterrupt(&ISR_PlayerTwo);
		
		Ball_Row_Counter++;															/**************Update the row*********************************/
		_delay_ms(200);																/**************Wait some time to see the ball*****************/
		RetVal = BUZ_Off(Buzzer);		/*Turn of the buzzer ==> we but it here to give time for it to be heard and we can't but a delay to not stop the flow of the ball movement*/
		
		RetVal = EXTI_DisableInterrupt(&ISR_PlayerOne);
		RetVal = EXTI_DisableInterrupt(&ISR_PlayerTwo);								
		RetVal = CLCD_GoToX_Y(&CLCD , Ball_Row[Ball_Row_Counter - 1] , Ball_Col);   /**************Go to the same place to remove the ball********/
		RetVal = CLCD_SendString(&CLCD , " ");
		RetVal = EXTI_EnableInterrupt(&ISR_PlayerOne);
		RetVal = EXTI_EnableInterrupt(&ISR_PlayerTwo);
		
		
		if(7 <= Ball_Row_Counter){													/**************Check if Ball_Row_Counter Get out of boundaries*/
			Ball_Row_Counter = 1;												
		}
	}
																
	
	return RetVal;
}







void ISR1_PlayerOneMove(void){
	
	RetVal = CLCD_GoToX_Y(&CLCD , PlayerOne_Current_Position , CLCD_COL1);		/*Go to the current position of the player*/
	
	PlayerOne_Current_Position++;												/*Update the position of the player*/
	PlayerOne_Current_Position %= 4;											/*Make sure that the position won't be more than 3*/
	
	RetVal = CLCD_SendString(&CLCD , " ");										/*Clear the player form the old position*/
	
	RetVal = CLCD_GoToX_Y(&CLCD , PlayerOne_Current_Position , CLCD_COL1);		/*Go to the current position of the player*/
	RetVal = CLCD_SendData(&CLCD , PLAYER_POSITION_IN_CGRAM);					/*Set the player in the new position*/
	
}

void ISR2_PlayerTwoMove(void){
	
	
	RetVal = CLCD_GoToX_Y(&CLCD , PlayerTwo_Current_Position , CLCD_COL16);		/*Go to the current position of the player*/
	PlayerTwo_Current_Position++;												/*Update the position of the player*/
	PlayerTwo_Current_Position %= 4;											/*Make sure that the position won't be more than 3*/
	
	RetVal = CLCD_SendString(&CLCD , " ");										/*Clear the player form the old position*/
	
	RetVal = CLCD_GoToX_Y(&CLCD , PlayerTwo_Current_Position , CLCD_COL16);		/*Go to the current position of the player*/
	RetVal = CLCD_SendData(&CLCD , PLAYER_POSITION_IN_CGRAM);					 /*Set the player in the new position*/

}