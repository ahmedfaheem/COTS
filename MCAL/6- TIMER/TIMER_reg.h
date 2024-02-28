#ifndef TIMER_REG_H
#define TIMER_REG_H


/*************TIMER0  8bit***************/

/* Generation Mode  Select Mode */
#define TCCR0   *((volatile uint8*)0x53)
/* Select Mode */
#define TCCR0_WGM00   6u
#define TCCR0_WGM01   3u

/* Compare Match Output Mode to control hardware action*/
#define TCCR0_COM00   4u
#define TCCR0_COM01   5u


/*  Clock Select */
#define   TCCR0_CS00  0u
#define   TCCR0_CS01  1u
#define   TCCR0_CS02  2u


/*Timer/Counter Register for data in timer*/

#define  TCNT0       *((volatile uint8*)0x52)


/*Output Compare Register */

#define  OCR0        *((volatile uint8*)0x5C)


/*Timer/Counter Interrupt Mask */
#define   TIMSK         *((volatile uint8*)0x59)
#define   TIMSK_TOIE0    0u   /*To enable Timer/Counter0 Overflow Interrupt Enable*/
#define   TIMSK_OCIE0    1u   /*: Timer/Counter0 Output Compare Match Interrupt Enable*/
#define   TIMSK_TOIE1    2u
#define   TIMSK_OCIE1B   3u
#define   TIMSK_OCIE1A   4u
#define   TIMSK_TICIE1   5u
#define   TIMSK_OCIE2    7u
#define   TIMSK_TOIE2    6u
/*************END OF TIMER0***************/

/*************START OF 16bit TIMER1 ***************/

#define TCCR1A   *((volatile uint8*)0x4F)   /*Timer/Counter1 Control Register A */

/*Compare Output Mode*/

/*FOR  OC1A*/
#define TCCR1A_COM1A0   6u
#define TCCR1A_COM1A1   7u
/* FOR  OC1B*/
#define TCCR1A_COM1B0   4u
#define TCCR1A_COM1B1   5u

/*: Waveform Generation Mode On Register TCCR1A*/
/**/
#define TCCR1A_WGM10    0u
#define TCCR1A_WGM11    1u

/*Timer/Counter1 Control Register B*/
#define TCCR1B   *((volatile uint8*)0x4E)

/*Waveform Generation Mode On Register TCCR1B*/
#define  TCCR1B_WGM13    4u
#define  TCCR1B_WGM12    3u

/*ICU Trigger State*/

#define  TCCR1B_ICES1    6u

/*ICU Noise Canceler State*/

#define  TCCR1B_ICNC1    7u


/*Timer/Counter1  data register*/
#define TCNT1H   *((volatile uint8*)0x4D)
#define TCNT1L   *((volatile uint8*)0x4C)

#define TCNT1   *((volatile uint16*)0x4C)  /* Refer to 16 bit TCNT1H:TCNT1L */

/*Output Compare Register 1 A */
#define OCR1AH   *((volatile uint8*)0x4B)
#define OCR1AL   *((volatile uint8*)0x4A)

#define OCR1A   *((volatile uint16*)0x4A) /* Refer to 16 bit OCR1AH:OCR1AL */


/*Output Compare Register 1 B */
#define OCR1BH   *((volatile uint8*)0x49)
#define OCR1BL   *((volatile uint8*)0x48)

#define OCR1B   *((volatile uint16*)0x48) /* Refer to 16 bit OCR1BH:OCR1BL */


/*Input Capture Register 1*/
#define ICR1   *((volatile uint16*)0x46)  /* used for defining the counter TOP value*/



/*************START OF 8bit TIMER2 ***************/


#define TCCR2   *((volatile uint8*)0x45)   /*Timer/Counter2 Control Register – */

/*Waveform Generation Mode Bit*/

#define TCCR2_WGM20    6u
#define TCCR2_WGM21    3u


/* Compare Match Output Mode For Non PWM and Fast PWM and Phase Correct*/

#define TCCR2_COM20   4u
#define TCCR2_COM21   5u

/*Timer/Counter Data Register */

#define TCNT2   *((volatile uint8*)0x44)


/*Output Compare Register*/

#define OCR2   *((volatile uint8*)0x43)


/*Asynchronous Operation of the Timer/Counter Register*/

#define ASSR   *((volatile uint8*)0x42)


#define ASSR_AS2    3u       /* set Asynchronous Timer/Counter2*/

#define ASSR_TCN2UB   2u
#define ASSR_OCR2UB   1u
#define ASSR_TCR2UB   0u




/*Timer/Counter Interrupt Flag Register*/

#define TIFR   *((volatile uint8*)0x58)

#define TIFR_OCF2   7u
#define TIFR_TOV2   6u






#endif
