/*
 * RTC_types.h
 *
 *  Created on: Mar 11, 2023
 *      Author: Ahmed Hesham
 */

#ifndef RTC_RTC_TYPES_H_
#define RTC_RTC_TYPES_H_


#define SECONDS_REG     0x00
#define HULTBIT     7

#define MINUTES_REG     0x01

#define HOURS_REG       0x02
#define HOUR_MODEBIT     6

#define DAY_REG         0x03

#define DATE_REG        0x04

#define MONTH_REG       0x05

#define YEAR_REG        0x06

#define CONTROL_REG     0x07


typedef enum{
	RTC_AM,
	RTC_PM

}RTC_Hours_t;


#endif /* RTC_RTC_TYPES_H_ */
