/*
 * STD_Types.h
 *
 * Created: 1/28/2024 2:05:38 PM
 *  Author: dell
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*****************Data Types Declliration***********************/
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;
typedef float f32;
typedef double f64;
typedef long double f80;

typedef enum{
	Return_OK,
	Return_NOK
}Return_Status_t;
/****************************Macros**************************/

#define NULL_POINTER ((void *)0)




#endif /* STD_TYPES_H_ */