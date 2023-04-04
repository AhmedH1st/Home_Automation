
/*****************************************************************/
/* FILE DESCRIPTION:
----------------------------------------------------------------
*  file     : Mcu_HW.h
*
*  breif    : this file contains all registers addresses
*
*****************************************************************
*/
#ifndef MCU_HW_H_
#define MCU_HW_H_
/******************************************
  INCLUDES
*******************************************/
#include "STD_TYPES.h"
/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/


/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/
//-------------------DIO-------------------
//------------------ END of DIO------------


#define PORTA_REG  (*((volatile u8*)0x3B))
#define DDRA_REG  (*((volatile u8*)0x3A))
#define PINA_REG  (*((volatile u8*)0x39))

#define PORTB_REG  (*((volatile u8*)0x38))
#define DDRB_REG  (*((volatile u8*)0x37))
#define PINB_REG  (*((volatile u8*)0x36))

#define PORTC_REG  (*((volatile u8*)0x35))
#define DDRC_REG  (*((volatile u8*)0x34))
#define PINC_REG  (*((volatile u8*)0x33))

#define PORTD_REG  (*((volatile u8*)0x32))
#define DDRD_REG  (*((volatile u8*)0x31))
#define PIND_REG  (*((volatile u8*)0x30))



//-------------------EX_INTERRUPT-------------------


#define GICR         (*((volatile u8*)0x5B))//
#define MCUCR        (*((volatile u8*)0x55))//
#define MCUCSR       (*((volatile u8*)0x54))//
#define GIFR         (*((volatile u8*)0x5A))//
#define SREG         (*((volatile u8*)0x5f))//


//-------------------    ADC    -------------------



#define ADMUX     (*(volatile unsigned char*)0x27)
#define ADLAR  5
#define REFS0  6
#define REFS1  7

#define ADCSRA    (*(volatile unsigned char*)0x26)
#define ADPS0  0
#define ADPS1  1
#define ADPS2  2
#define ADIE   3
#define ADIF   4
#define ADATE  5
#define ADSC   6
#define ADEN   7

#define ADCH      (*(volatile unsigned char*)0x25)
#define ADCL      (*(volatile unsigned char*)0x24)
#define ADC       (*(volatile unsigned short*)0x24)
#define SFIOR     (*(volatile unsigned char*)0x50)




//-------------------    TIMER0    -------------------
#define OCR0      (*(volatile unsigned char*)0x5c)
#define TIMSK      (*(volatile unsigned char*)0x59)
#define TIFR      (*(volatile unsigned char*)0x58)
#define TCCR0      (*(volatile unsigned char*)0x53)
#define TCNT0      (*(volatile unsigned char*)0x52)

#define FOC0   7
#define OCIE0  1
#define TOIE0  0
#define OCF0   1
#define TOV0   0
#define WGM00  6
#define WGM01  3

//-------------------    TIMER1    -------------------

#define ICR1    (*(volatile unsigned short*)0x46)
#define ICR1L   (*(volatile unsigned char*)0x46)
#define ICR1H   (*(volatile unsigned char*)0x47)
#define OCR1B   (*(volatile unsigned short*)0x48)
#define OCR1BL  (*(volatile unsigned char*)0x48)
#define OCR1BH  (*(volatile unsigned char*)0x49)
#define OCR1A   (*(volatile unsigned short*)0x4A)
#define OCR1AL  (*(volatile unsigned char*)0x4A)
#define OCR1AH  (*(volatile unsigned char*)0x4B)
#define TCNT1   (*(volatile unsigned short*)0x4C)
#define TCNT1L  (*(volatile unsigned char*)0x4C)
#define TCNT1H  (*(volatile unsigned char*)0x4D)
#define TCCR1B  (*(volatile unsigned char*)0x4E)
#define TCCR1A  (*(volatile unsigned char*)0x4F)

#define OSCCAL (*(volatile unsigned char*)0x51)

/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

/* TCCR1B */
#define ICNC1   7
#define ICES1   6
/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

/* TIFR */
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0



//-------------------    USART    -------------------
#define UBRRL  (*(volatile unsigned char*)0x29)
#define UCSRC  (*(volatile unsigned char*)0x40)
#define UBRRH  (*(volatile unsigned char*)0x40)

#define UCSRB  (*(volatile unsigned char*)0x2A)
#define UCSRA  (*(volatile unsigned char*)0x2B)
#define UDR    (*(volatile unsigned char*)0x2C)

/* UCSRA */
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0

/* UCSRB */
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

/* UCSRC */
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0

//-------------------    SPI    -------------------


#define SPCR    (*(volatile unsigned char*)0x2D)
#define SPSR    (*(volatile unsigned char*)0x2E)
#define SPDR    (*(volatile unsigned char*)0x2F)




/* SPCR */
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0


#define SPIF    7
#define WCOL    6
/* bits 5-1 reserved */
#define SPI2X   0


//-------------------    I2C    -------------------



#define TWBR    (*(volatile unsigned char*)0x20)
#define TWSR    (*(volatile unsigned char*)0x21)
#define TWAR    (*(volatile unsigned char*)0x22)
#define TWDR    (*(volatile unsigned char*)0x23)
#define TWCR    (*(volatile unsigned char*)0x56)


/* TWCR */
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
/* bit 1 reserved */
#define TWIE    0

/* TWAR */
#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE   0

/* TWSR */
#define TWS7    7
#define TWS6    6
#define TWS5    5
#define TWS4    4
#define TWS3    3
/* bit 2 reserved */
#define TWPS1   1
#define TWPS0   0


/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/
#endif /* MCU_HW_H_ */
