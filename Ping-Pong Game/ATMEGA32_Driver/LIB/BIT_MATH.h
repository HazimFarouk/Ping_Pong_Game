/*
 * BIT_MATH.h
 *
 * Created: 1/28/2024 2:06:32 PM
 *  Author: dell
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/**********************Macros******************************/
#define SET_BIT(REG , BIT)		REG |=  (1 << BIT)		
#define CLR_BIT(REG , BIT)		REG &= ~(1 << BIT)
#define TGL_BIT(REG , BIT)		REG ^=  (1 << BIT)
#define GET_BIT(REG , BIT)		((REG >> BIT) & 1)



#endif /* BIT_MATH_H_ */