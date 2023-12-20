#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "ADC_reg.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"
#include "ADC_interface.h"


void ADC_voidInit(void){


/*  Reference Selection */

#if ADC_REF_SELECTION == AREF

	 CLR_BIT(ADMUX, ADMUX_REFS1);
	 CLR_BIT(ADMUX, ADMUX_REFS0);

#elif ADC_REF_SELECTION == AVCC

 CLR_BIT(ADMUX, ADMUX_REFS1);
 SET_BIT(ADMUX, ADMUX_REFS0);

#elif ADC_REF_SELECTION == INTERNAL

 SET_BIT(ADMUX, ADMUX_REFS1);
 SET_BIT(ADMUX, ADMUX_REFS0);

#else
#error Wrong Reselution Configuration Option
#endif

 /* ADC Adjust Selections */

#if ADC_ADJUST_SELECTION == _8BIT   /* LEFT ADjust */
 SET_BIT(ADMUX, ADMUX_ADLAR);

#elif ADC_ADJUST_SELECTION == _10BIT   /* RIGHT Adjust */

 CLR_BIT(ADMUX, ADMUX_ADLAR);

#else
#error Wrong ADC Adjust Configuration Option
#endif

/* Disable Auto Trigger Mode */
CLR_BIT(ADCSRA,ADCSRA_ADATE);

/* Disable interrupt  */

CLR_BIT(ADCSRA,ADCSRA_ADIE);


/* Cofigure the Prescaler Division Factor */

ADCSRA &= PRESCALER_BIT_MASK;
ADCSRA |= ADC_u8PRESCALER_DIVISION_FACTOR <<PRESCALER_BIT_POS;

/* ADC Active */
#if ADC_ACTIVE == ENABLED
 SET_BIT(ADCSRA, ADCSRA_ADEN);
#elif ADC_ACTIVE == DISABLED
 CLR_BIT(ADCSRA, ADCSRA_ADEN);
#else
#error Wrong ADC Activation Configuration Option
#endif



}


uint16 ADC_u8GetChannelReading(uint8 Copy_u8Channel){

	  /* Select Channel  */

	   ADMUX &= ANALOG_CHANNEL_BIT_MASK;  /*Clear The Channel Selection bits */
	   ADMUX |= Copy_u8Channel;


  /* Enable Start Conversion */

   SET_BIT(ADCSRA, ADCSRA_ADSC);



   /* Pooling (Blocking) on the conversion Complete */
   while((GET_BIT(ADCSRA, ADCSRA_ADIF)) == 0);

   /* Disable ADC Interrupt Flag */
   SET_BIT(ADCSRA, ADCSRA_ADIF);

   /* get conversion  Result */
#if ADC_ADJUST_SELECTION == _8BIT   /* LEFT ADjust */
 return ADCH;

#elif ADC_ADJUST_SELECTION == _10BIT   /* RIGHT Adjust */
 return ADC;
#else
#error Wrong ADC Adjust Configuration Option
#endif


}
