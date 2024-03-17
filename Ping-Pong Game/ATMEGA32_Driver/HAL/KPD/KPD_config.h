/*
 * KPD_config.h
 *
 * Created: 2/3/2024 8:39:13 PM
 *  Author: dell
 */ 


#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

/**********************Keys***************************/

#define KPD_ROWS_NUMBER  4
#define KPD_COLS_NUMBER  4

u8 KPD_Buttons[KPD_ROWS_NUMBER][KPD_COLS_NUMBER] = {{'7' , '8' , '9' , '/'},
													{'4' , '5' , '6' , '*'},
													{'1' , '2' , '3' , '-'},
													{'?' , '0' , '=' , '+'}};
						  
						  


#endif /* KPD_CONFIG_H_ */