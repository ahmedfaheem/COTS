#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "ADC_reg.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"
#include "ADC_interface.h"


static uint16* ADC_pu16Result = NULL;
static void (*ADC_pvNotificationFunc)(void) = NULL;

static uint8 ADC_u8BusyFlag = IDEL;

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


uint8 ADC_u8StartConversionSynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result){

	uint8 Local_u8Err_State = OK;

	uint8 Local_u8Counter = 0u;
	if(Copy_pu16Result != NULL){

		/*check if ADC is IDEL  */
		if(ADC_u8BusyFlag == IDEL){

			/* ADC Now Is Busy*/
			ADC_u8BusyFlag = BUSY;



			/* Select Channel  */

			ADMUX &= ANALOG_CHANNEL_BIT_MASK;  /*Clear The Channel Selection bits */
			ADMUX |= Copy_u8Channel;


			/* Enable Start Conversion */

			SET_BIT(ADCSRA, ADCSRA_ADSC);



			/* Pooling (Blocking) on the conversion Complete on this condition, Timeout not passed Yet */
			while(((GET_BIT(ADCSRA, ADCSRA_ADIF)) == 0) && (Local_u8Counter <  ADC_u8TIMEOUT)){
				Local_u8Counter++;
			}

			if(Local_u8Counter == ADC_u8TIMEOUT){

				/* Time out has passed without the flag beign raised */
				Local_u8Err_State = TIMEOUT_ERR;
			}else{

				/*Flag is raised before time out */

				/* Disable ADC Interrupt Flag */
				SET_BIT(ADCSRA, ADCSRA_ADIF);

				/* get conversion  Result */
#if ADC_ADJUST_SELECTION == _8BIT   /* LEFT ADjust */
				*Copy_pu16Result =  ADCH;

#elif ADC_ADJUST_SELECTION == _10BIT   /* RIGHT Adjust */
				*Copy_pu16Result =  ADC;
#else
#error Wrong ADC Adjust Configuration Option
#endif


				/* ADC Now Is IDEL*/
				ADC_u8BusyFlag = IDEL;

			}

		}else{
			/*ADC is Busy, update error state */
			Local_u8Err_State = BUSY_ERR;
		}
	}else{

		Local_u8Err_State= NULL_PTR_ERR;
	}

	return Local_u8Err_State;
}




uint8 ADC_u8StartConversionAsynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result,  void (*Copy_pvNotificationFunc)()){
	uint8 Local_u8Err_State = OK;

	if((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL)){

		/*check if ADC is IDEL  */
		if(ADC_u8BusyFlag == IDEL){

			/* ADC Now Is Busy*/
			ADC_u8BusyFlag = BUSY;


			/* Convert Local Result to Global Result for ISR */
			ADC_pu16Result = Copy_pu16Result;

			/* Convert Local Notification Function to Global Notification Function for ISR */
			ADC_pvNotificationFunc = Copy_pvNotificationFunc;

			/* Select Channel  */

			ADMUX &= ANALOG_CHANNEL_BIT_MASK;  /*Clear The Channel Selection bits */
			ADMUX |= Copy_u8Channel;

			/* Enable Start Conversion */

			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/* Enable ADC Interrupt */

			SET_BIT(ADCSRA, ADCSRA_ADIE);



		}else{
			/*ADC is Busy, update error state */
			Local_u8Err_State = BUSY_ERR;
		}



	}else{

		Local_u8Err_State= NULL_PTR_ERR;
	}

	return Local_u8Err_State;

}



__attribute__((signal)) void __vector_16(void);

/* Page 42 on datasheet*/
void __vector_16(void){

	if(ADC_pu16Result != NULL){

		/* get conversion  Result */
#if ADC_ADJUST_SELECTION == _8BIT   /* LEFT ADjust */
		*ADC_pu16Result =  ADCH;
#elif ADC_ADJUST_SELECTION == _10BIT   /* RIGHT Adjust */
		*ADC_pu16Result =  ADC;
#endif

		/* Disable ADC conversion complete Interrupt */

		CLR_BIT(ADCSRA, ADCSRA_ADIE);
	}

/* Should be here because Call Back function may call ADC  */
	/* ADC Now Is IDEL*/
	ADC_u8BusyFlag = IDEL;



	/*Invoke the call back notification Function */

	if(ADC_pvNotificationFunc != NULL){
		ADC_pvNotificationFunc();
	}



}
