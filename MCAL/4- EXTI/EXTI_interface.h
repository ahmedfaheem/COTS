#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

typedef enum{
	
	INT0, 
	INT1, 
	INT2
}EXTI_IntChannel_t;

typedef enum{
	
	LOW_LEVEL, 
	ON_CHANE, 
	FALLING_EDGE, 
	RISING_EDGE
	
}EXTI_SenceCtrl_t;



void EXTI_voidInit(void);  /* read configuration form cfg.h */

uint8 EXTI_u8SetSenseCtrl(EXTI_IntChannel_t Copy_IntCh, EXTI_SenceCtrl_t Copy_SenceCtrl);

uint8 EXTI_u8EnableIntChannel(EXTI_IntChannel_t Copy_IntCh);

uint8 EXTI_u8DisableIntChannel(EXTI_IntChannel_t Copy_IntCh);

uint8 EXTI_u8SetCallBack(EXTI_IntChannel_t Copy_IntCh, void (*Copy_pvCallBackFunc)(void));

#endif
