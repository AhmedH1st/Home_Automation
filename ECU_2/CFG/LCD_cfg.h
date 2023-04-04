/*
 * LCD_cfg.h
 *
 *  Created on: Feb 19, 2023
 *      Author: Ahmed Hesham
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_
#define NUMBER_OF_DIGIT_ROWS      8

/****************************************************************************/
/*            Config what type pf LCD do you have (LCD_4_BIT or LCD_8_BIT) */
/****************************************************************************/
#define LCD_TYPE     LCD_4_BIT

/************************************************************************/
/*            Config what size of LCD do you have (2*16 or 4*20)        */
/************************************************************************/

#define LCD_SIZE      4*20//2*16//



/*
Please config the pins you connect the LCD on
*/
#define DB0
#define DB1
#define DB2
#define DB3
#define DB4   DIO_PB0//DIO_PA3////DIO_PA4
#define DB5   DIO_PB1//DIO_PA4////DIO_PA5
#define DB6   DIO_PB2//DIO_PA5////DIO_PA6
#define DB7   DIO_PB4//DIO_PA6////DIO_PA7
#define RS    DIO_PA3//DIO_PA1//
#define EN    DIO_PA2//DIO_PA2//



/***********************************************/

/**** Config The LCD DDRAM Start PoInt && CGRAM One  ********/

#define DDRAM_START_ADDRESS   0x80
#define CGRAM_START_ADDRESS   0x40

/**************************************************************/

typedef enum{
	LOW=0,
	HIGH
}LCD_PIN_LVL_type;


#endif /* LCD_CFG_H_ */
