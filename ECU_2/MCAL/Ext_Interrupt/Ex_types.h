/*
 * Ex_types.h
 *
 *  Created on: Feb 24, 2023
 *      Author: Ahmed Hesham
 */

#ifndef EXT_INTERRUPT_EX_TYPES_H_
#define EXT_INTERRUPT_EX_TYPES_H_

typedef enum{
	INT_0,
	INT_1,
	INT_2
}Inter_ID_t;


#define ISC11     3
#define ISC10     2
#define ISC01     1
#define ISC00     0
#define ISC2      6

#define INT1      7
#define INT0      6
#define INT2      5

#define INTF1     7
#define INTF0     6
#define INTF5     2


/*#define EXT_1    __Vector_0
#define EXT_2    __Vector_1
#define EXT_3    __Vector_2


#define ISR(vector)   void vector (void) __attribute__ ((singal)); \
					  void vector (void)
*/







#endif /* EXT_INTERRUPT_EX_TYPES_H_ */
