#ifndef ADC_CFG_H
#define ADC_CFG_H


/*  Reference  Select
  options:-
  1- AREF
  2- AVCC   --> on ETAKIT32
  3- INTERNAL
*/
#define ADC_REF_SELECTION    AVCC


/* Adjust MODE
 options:-

 1- _8BIT   -->  left adjust
 2- _10BIT  --> right adjust

 * */

#define ADC_ADJUST_SELECTION    _8BIT

/*
 ADC Enable
 options:-
 1- ENABLE
 2- DISABLED
*/

#define ADC_ACTIVE   ENABLED



/*  Configure ADC Prescaler  Division Factor, options:- 1- DIVISION_BY_2
 *                                                      2- DIVISION_BY_4
 *                                                      3- DIVISION_BY_8
 *                                                      4- DIVISION_BY_16
 *                                                      5- DIVISION_BY_32
 *                                                      6- DIVISION_BY_64
 *                                                      7- DIVISION_BY_128
 *

*/

#define ADC_u8PRESCALER_DIVISION_FACTOR  DIVISION_BY_128


#define ADC_u8TIMEOUT  50000u

#endif
