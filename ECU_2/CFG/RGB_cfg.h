/*
 * RGB_cfg.h
 *
 *  Created on: Mar 9, 2023
 *      Author: Ahmed Hesham
 */

#ifndef RGB_CFG_H_
#define RGB_CFG_H_


/*
 *Will Need an Update in Structure if more than 1 RGB is used
 */
#define NO_RGBs                 1

/*
 * Determine size of array of Structs
 */

#define NO_CLOLRS               5

/*
 * Add the colors here and insert in the arr its opposite arrangament(red,blue,green)
 * follow the arrange in ascending so the will be mapping to each other
 */

typedef enum{
	WHITE,
	YELLOW,
	RED,
	GREEN,
	BLUE,
}RGB_User_Colors_t;


RGB_Colors_t  RGB_Colors_arr [NO_CLOLRS];

#endif /* RGB_CFG_H_ */
