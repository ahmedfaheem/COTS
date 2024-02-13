#ifndef LM35_INTERFACE_H
#define LM35_INTERFACE_H


/* This Function work with ADC driver by Synchronous Function with this channels

1-	ADC_u8SINGLE_ENDED_ADC0,
2-	ADC_u8SINGLE_ENDED_ADC1,
3-	ADC_u8SINGLE_ENDED_ADC2,
4-	ADC_u8SINGLE_ENDED_ADC3,
5-	ADC_u8SINGLE_ENDED_ADC4,
6-	ADC_u8SINGLE_ENDED_ADC5,
7-	ADC_u8SINGLE_ENDED_ADC6,
8-	ADC_u8SINGLE_ENDED_ADC7,

*/

uint8 LM34_u8GetTempInC(uint8 Copy_u8ADCChannel);



#endif 
