#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

typedef struct{

	uint8 ChainSize;
	uint8 *ChannelsArr;
	uint16 *ResultsArr;
	void (*NotificationFunc)();

}ADC_Chain_t;



void ADC_voidInit(void);


uint8 ADC_u8StartSingleConversionSynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result);


/*To operate this function should Enable GLobal Interrupt*/
uint8 ADC_u8StartSingleConversionAsynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result,  void (*Copy_pvNotificationFunc)());



uint8 ADC_u8StartChainConvAsynch(ADC_Chain_t * Copy_puChainConv);



/*Analog Channel and Gain Selection (SINGLE_ENDE Bits)Options:-  */
/*
 1-   ADC_u8SINGLE_ENDED_ADC0
 2-   ADC_u8SINGLE_ENDED_ADC1
 3-   ADC_u8SINGLE_ENDED_ADC2
 4-   ADC_u8SINGLE_ENDED_ADC3
 5-   ADC_u8SINGLE_ENDED_ADC4
 6-   ADC_u8SINGLE_ENDED_ADC5
 7-   ADC_u8SINGLE_ENDED_ADC6
 8-   ADC_u8SINGLE_ENDED_ADC7
*/


typedef enum{
	ADC_u8SINGLE_ENDED_ADC0,
	ADC_u8SINGLE_ENDED_ADC1,
	ADC_u8SINGLE_ENDED_ADC2,
	ADC_u8SINGLE_ENDED_ADC3,
	ADC_u8SINGLE_ENDED_ADC4,
	ADC_u8SINGLE_ENDED_ADC5,
	ADC_u8SINGLE_ENDED_ADC6,
	ADC_u8SINGLE_ENDED_ADC7,
}ADC_SINGLE_ENDED_CHANNEL;


/* Interrupt Pin direction must be input */

#endif
