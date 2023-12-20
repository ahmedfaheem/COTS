#ifndef ADC_REG_H
#define ADC_REG_H




#define ADMUX     *((volatile uint8 *)0X27) /*  ADC Multiplexer Selection  */

#define ADMUX_REFS1    7u     /* Reference Selection Bit1 */
#define ADMUX_REFS0    6u     /* Reference Selection Bit0 */
#define ADMUX_ADLAR    5u   /* Left Adjust Result */
#define ADMUX_MUX4     4u   /*0:4: Analog Channel and Gain Selection Bit */
#define ADMUX_MUX3     3u
#define ADMUX_MUX2     2u
#define ADMUX_MUX1     1u
#define ADMUX_MUX0     0u




/*  ADC Control and Status */

#define ADCSRA     *((volatile uint8 *)0X26)

#define ADCSRA_ADEN      7u  /*  ADC Enable */
#define ADCSRA_ADSC      6u  /* ADC Start Conversion */
#define ADCSRA_ADATE     5u  /*  ADC Auto Trigger Enable */
#define ADCSRA_ADIF      4u  /* ADC Interrupt Flag */
#define ADCSRA_ADIE      3u  /*  ADC Interrupt Enable */
#define ADCSRA_ADPS2     2u  /* Bits 2:0  ADPS2:0: ADC Prescaler Select Bits */
#define ADCSRA_ADPS1     1u
#define ADCSRA_ADPS0     0u

/*   ADC Data Register    */

#define ADCH     *((volatile uint8 *)0X25)    /* MSBs */



#define ADCL     *((volatile uint8 *)0X24)   /* LSBs */


#define ADC     *((volatile uint16 *)0X24)  /* (MSB + LSB)point to ADCL and ADCH */

#endif
