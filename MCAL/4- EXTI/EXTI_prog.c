#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "EXTI_interface.h"
#include "EXTI_prv.h"
#include "EXTI_cfg.h"   /*Should be on this order because depend on enum on interface.h, and macros on prv */
#include "EXTI_reg.h"

static void (*EXTI_pvCallBackFunc[3])(void) = {0};

void EXTI_voidInit(void){


#if INT0_SENSE_CTRL == EXTI_LOW_LEVEL

	CLR_BIT(MCUCR, MCUCR_ISC00);
	CLR_BIT(MCUCR, MCUCR_ISC01);

#elif INT0_SENSE_CTRL == EXTI_RISING_EDGE

	SET_BIT(MCUCR, MCUCR_ISC00);
	SET_BIT(MCUCR, MCUCR_ISC01);

#elif INT0_SENSE_CTRL == EXTI_FALLING_EDGE

	CLR_BIT(MCUCR, MCUCR_ISC00);
	SET_BIT(MCUCR, MCUCR_ISC01);

#elif INT0_SENSE_CTRL == EXTI_ON_CHANE

	SET_BIT(MCUCR, MCUCR_ISC00);
	CLR_BIT(MCUCR, MCUCR_ISC01);

#else  #error Wrong INT0_SENSE_CTRL Configuration

#endif



#if INT1_SENSE_CTRL == EXTI_LOW_LEVEL

	CLR_BIT(MCUCR, MCUCR_ISC10);
	CLR_BIT(MCUCR, MCUCR_ISC11);

#elif INT0_SENSE_CTRL == EXTI_RISING_EDGE

	SET_BIT(MCUCR, MCUCR_ISC10);
	SET_BIT(MCUCR, MCUCR_ISC11);

#elif INT0_SENSE_CTRL == EXTI_FALLING_EDGE

	CLR_BIT(MCUCR, MCUCR_ISC10);
	SET_BIT(MCUCR, MCUCR_ISC11);

#elif INT0_SENSE_CTRL == EXTI_ON_CHANE

	SET_BIT(MCUCR, MCUCR_ISC10);
	CLR_BIT(MCUCR, MCUCR_ISC11);

#else  #error Wrong INT1_SENSE_CTRL Configuration

#endif




#if INT2_SENSE_CTRL == EXTI_RISING_EDGE

	SET_BIT(MCUCSR, MCUCSR_ISC2);

#elif INT2_SENSE_CTRL == EXTI_FALLING_EDGE

	CLR_BIT(MCUCSR, MCUCSR_ISC2);


#else  #error Wrong INT2_SENSE_CTRL Configuration

#endif



#if INT0_INIT_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);
#elif INT0_INIT_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);
#else  #error Wrong  INT0_INIT_STATE  Configuration
#endif

#if INT1_INIT_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);
#elif INT1_INIT_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);
#else  #error Wrong INT1_INIT_STATE  Configuration
#endif


#if INT2_INIT_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);
#elif INT2_INIT_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT2);
#else  #error Wrong  INT2_INIT_STATE  Configuration
#endif



}

uint8 EXTI_u8SetSenseCtrl(EXTI_IntChannel_t Copy_IntCh, EXTI_SenceCtrl_t Copy_SenceCtrl){
	uint8 Local_u8ErrorState = OK;

	if(Copy_IntCh == INT0){


		switch(Copy_SenceCtrl){
		case LOW_LEVEL: CLR_BIT(MCUCR, MCUCR_ISC00); CLR_BIT(MCUCR, MCUCR_ISC01); break;
		case ON_CHANE: SET_BIT(MCUCR, MCUCR_ISC00); CLR_BIT(MCUCR, MCUCR_ISC01); break;
		case FALLING_EDGE: CLR_BIT(MCUCR, MCUCR_ISC00); SET_BIT(MCUCR, MCUCR_ISC01); break;
		case RISING_EDGE: SET_BIT(MCUCR, MCUCR_ISC00); SET_BIT(MCUCR, MCUCR_ISC01); break;
		default: Local_u8ErrorState = NOK; break;
		}

	}else if(Copy_IntCh == INT1){


		switch(Copy_SenceCtrl){
		case LOW_LEVEL: CLR_BIT(MCUCR, MCUCR_ISC10); CLR_BIT(MCUCR, MCUCR_ISC11); break;
		case ON_CHANE:  SET_BIT(MCUCR, MCUCR_ISC10); CLR_BIT(MCUCR, MCUCR_ISC11); break;
		case FALLING_EDGE: CLR_BIT(MCUCR, MCUCR_ISC10); SET_BIT(MCUCR, MCUCR_ISC11); break;
		case RISING_EDGE: SET_BIT(MCUCR, MCUCR_ISC10); SET_BIT(MCUCR, MCUCR_ISC11); break;
		default: Local_u8ErrorState = NOK; break;
		}

	}else if(Copy_IntCh == INT2){


		switch(Copy_SenceCtrl){
		case FALLING_EDGE: CLR_BIT(MCUCSR, MCUCSR_ISC2); break;
		case RISING_EDGE: SET_BIT(MCUCSR, MCUCSR_ISC2); break;
		default: Local_u8ErrorState = NOK; break;
		}

	}
	return Local_u8ErrorState;

}
uint8 EXTI_u8EnableIntChannel(EXTI_IntChannel_t Copy_IntCh){
	uint8 Local_u8ErrorState = OK;

	switch(Copy_IntCh){
	case INT0: SET_BIT(GICR,GICR_INT0); break;
	case INT1: SET_BIT(GICR,GICR_INT1); break;
	case INT2: SET_BIT(GICR,GICR_INT2); break;
	default: Local_u8ErrorState = NOK; break;
	}

	return Local_u8ErrorState;
}

uint8 EXTI_u8DisableIntChannel(EXTI_IntChannel_t Copy_IntCh){
	uint8 Local_u8ErrorState = OK;

	switch(Copy_IntCh){
	case INT0: CLR_BIT(GICR,GICR_INT0); break;
	case INT1: CLR_BIT(GICR,GICR_INT1); break;
	case INT2: CLR_BIT(GICR,GICR_INT2); break;
	default: Local_u8ErrorState = NOK; break;
	}

	return Local_u8ErrorState;
}

/* ISR CODE (callback form App layer) */

uint8 EXTI_u8SetCallBack(EXTI_IntChannel_t Copy_IntCh, void (*Copy_pvCallBackFunc)(void)){
	uint8 Local_u8ErrorState = OK;

	if(Copy_pvCallBackFunc != NULL){

		if(Copy_IntCh == INT0 || Copy_IntCh == INT1 || Copy_IntCh == INT2 ){
		EXTI_pvCallBackFunc[Copy_IntCh] = Copy_pvCallBackFunc;
		}else{
			Local_u8ErrorState = NOK;
		}

	}else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}


	return Local_u8ErrorState;
}





__attribute__((signal)) void  __vector_1(void);

void  __vector_1(void){ /* INT0 ISR*/

	if(EXTI_pvCallBackFunc[INT0] != NULL){
		EXTI_pvCallBackFunc[INT0]();
	}
}

__attribute__((signal)) void  __vector_2(void);

void  __vector_2(void){ /* INT1 ISR*/

	if(EXTI_pvCallBackFunc[INT1] != NULL){
		EXTI_pvCallBackFunc[INT1]();
	}
}


__attribute__((signal)) void  __vector_3(void);

void  __vector_3(void){ /* INT2 ISR*/
	if(EXTI_pvCallBackFunc[INT2] != NULL){

		EXTI_pvCallBackFunc[INT2]();
	}
}







