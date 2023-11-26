#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

typedef enum{
	
	ACT_HIGH = 0u,
	ACT_LOW = 1u
}LED_Act_t;

/*
 
LED_u8ActiveType  Options:
1- ACT_HIGH  
2- ACT_LOW   

*/



typedef struct{
	
	LED_Act_t  LED_u8ActiveType;
	uint8      LED_u8Port;
	uint8      LED_u8Pin;
	
}LED_Confg_t;


uint8 LED_u8SetOn(const LED_Confg_t* Copy_pConfig);

uint8 LED_u8SetOff(const LED_Confg_t* Copy_pConfig);

uint8 LED_u8Toggle(const LED_Confg_t* Copy_pConfig);


#endif