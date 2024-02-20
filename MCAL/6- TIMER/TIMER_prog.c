#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"
#include "TIMER_interface.h"
#include "TIMER_reg.h"
#include "TIMER_cfg.h"
#include "TIMER_prv.h"

/*Timer0 overflow and comppare match   -> 2
 *  Timer1 over flow and compare match ->  3
 *  timer2  need 4 call back func
 */

static void(*GlobalCallBackFucn[9])(void) = {NULL};

void TIMER0_voidInit(){

	/* Select Mode */

#if  TIMER0_MODE_SELECTION == NORMAL
	/* Set Mode To normal Mode */
	CLR_BIT(TCCR0, TCCR0_WGM00);
	CLR_BIT(TCCR0, TCCR0_WGM01);

	/* Set Initial Preload Value*/
	TCNT0 = TIMER0_INIT_PRELOAD_VAL;

#elif TIMER0_MODE_SELECTION  == COMPARE_MATCH
	/* Set Mode To Output Compare match*/
	CLR_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);

	/* Set Initial Compare Value*/
	OCR0 = TIMER0_CTC_INIT_COMPARE_VAL;

	/* Select Hardware action on Pin OC0*/

#if  TIMER0_COMPARE_MODE_HW_ACTION_OC0 == NO_HW_ACTION
	CLR_BIT(TCCR0, TCCR0_COM00);
	CLR_BIT(TCCR0, TCCR0_COM01);
#elif TIMER0_COMPARE_MODE_HW_ACTION_OC0 == TOGGEL_PIN_HW_ACTION
	SET_BIT(TCCR0, TCCR0_COM00);
	CLR_BIT(TCCR0, TCCR0_COM01);

#elif TIMER0_COMPARE_MODE_HW_ACTION_OC0 == CLEAR_PIN_HW_ACTION
	CLR_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
#elif TIMER0_COMPARE_MODE_HW_ACTION_OC0 == SET_PIN_HW_ACTION
	SET_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);

#endif

#elif  TIMER0_MODE_SELECTION == FAST_PWM

	/* Set Mode To Output Compare match FAST PWM */
	SET_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);

	/* Set Initial Compare Value*/
	OCR0 = TIMER0_FAST_PWM_INIT_COMPARE_VAL;

#if TIMER0_FAST_PWM_MODE_SELECTION == FAST_PWM_DISCONNECTED
	CLR_BIT(TCCR0, TCCR0_COM00);
	CLR_BIT(TCCR0, TCCR0_COM01);

#elif TIMER0_FAST_PWM_MODE_SELECTION  == FAST_PWM_CLR_ONCOMP_SET_ONTOP
	CLR_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
#elif FAST_PWM_SET_ONCOMP_CLR_ONTOP  == FAST_PWM_CLR_ONCOMP_SET_ONTOP
	SET_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
#endif

#endif


#if TIMER0_INTERRUPT_ENABLE == ENABLED

#if  TIMER0_MODE_SELECTION == NORMAL

	SET_BIT(TIMSK, TIMSK_TOIE0);
#elif TIMER0_MODE_SELECTION  == COMPARE_MATCH
	SET_BIT(TIMSK, TIMSK_OCIE0);
#endif


#elif TIMER0_INTERRUPT_ENABLE == DISABLED

#if  TIMER0_MODE_SELECTION == NORMAL

	CLR_BIT(TIMSK, TIMSK_TOIE0);
#elif TIMER0_MODE_SELECTION  == COMPARE_MATCH
	CLR_BIT(TIMSK, TIMSK_OCIE0);
#endif

#endif

	/* Set Prescaler */
	TCCR0 &= MASK_LEAST_3_BIT;
	TCCR0 |= TIMER0_PRESCALER_SELECTION;

}




uint8 TIMER_u8SetCallBackFunc(uint8 Copy_u8IntSource,void(*Copy_pvCallBackFucn)(void)){

	uint8 Local_u8ErrState = OK;
	if(Copy_pvCallBackFucn != NULL){
		GlobalCallBackFucn[Copy_u8IntSource] =Copy_pvCallBackFucn;

	}else{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;
}

void TIMER0_voidSetPreloadValue(uint8 Copy_u8PreloadVal){

	TCNT0 = Copy_u8PreloadVal;

}

void TIMER0_voidSetCompareValue(uint8 Copy_u8CompareVal){

	OCR0 = Copy_u8CompareVal;

}


void TIMER0_voidSetPrescaler(TIMER_Prescaler_t  Copy_PrescalerVal){

	/* Set Prescaler */
	TCCR0 &= MASK_LEAST_3_BIT;
	TCCR0 |= Copy_PrescalerVal;

}

void TIMER0_voidStop(){

	/* Set Prescaler */
	TCCR0 &= MASK_LEAST_3_BIT;
	TCCR0 |= NO_CLOCK;

}



/* TIMER2*/

void TIMER1_voidInit(){

	/* MODE SELECT*/

#if TIMER1_MODE_SELECTION == FAST_PWM_TOP_ICR1
	TCCR1A &=0b11111100;
	TCCR1A |= 2;
	SET_BIT(TCCR1B, TCCR1B_WGM13);
	SET_BIT(TCCR1B, TCCR1B_WGM12);
#elif  TIMER1_MODE_SELECTION == NORMAL
	TCCR1A &=0b11111100;
	CLR_BIT(TCCR1B, TCCR1B_WGM13);
	CLR_BIT(TCCR1B, TCCR1B_WGM12);

#elif  TIMER1_MODE_SELECTION == COMPARE_MATCH_TOP_ICR1
	TCCR1A &=0b11111100;
	SET_BIT(TCCR1B, TCCR1B_WGM13);
	SET_BIT(TCCR1B, TCCR1B_WGM12);
#endif


	/* SET FAST PWM MODE */
#if TIMER1_FAST_PWM_MODE_SELECTION == FAST_PWM_CLR_ONCOMP_SET_ONTOP
	SET_BIT(TCCR1A, TCCR1A_COM1A1);
	CLR_BIT(TCCR1A, TCCR1A_COM1A0);
	SET_BIT(TCCR1A, TCCR1A_COM1B1);
	CLR_BIT(TCCR1A, TCCR1A_COM1B0);
#elif TIMER1_FAST_PWM_MODE_SELECTION == FAST_PWM_SET_ONCOMP_CLR_ONTOP
	SET_BIT(TCCR1A, TCCR1A_COM1A1);
	SET_BIT(TCCR1A, TCCR1A_COM1A0);
	SET_BIT(TCCR1A, TCCR1A_COM1B1);
	SET_BIT(TCCR1A, TCCR1A_COM1B0)

#elif TIMER1_FAST_PWM_MODE_SELECTION == FAST_PWM_DISCONNECTED

	CLR_BIT(TCCR1A, TCCR1A_COM1A1);
	CLR_BIT(TCCR1A, TCCR1A_COM1A0);
	CLR_BIT(TCCR1A, TCCR1A_COM1B1);
	CLR_BIT(TCCR1A, TCCR1A_COM1B0);
#endif


	/* SET Init TOP VAL*/
	ICR1 = TIMER1_INIT_TOP_VAL;

	/* Set Init Compare Val */

	OCR1A =TIMER1_CTC_OCRA1_INIT_COMPARE_VAL;
	OCR1B =TIMER1_CTC_OCRB1_INIT_COMPARE_VAL;



#if TIMER1_INTERRUPT_ENABLE == ENABLED

#if  TIMER1_MODE_SELECTION == NORMAL

	SET_BIT(TIMSK, TIMSK_TOIE1);
#elif TIMER1_MODE_SELECTION  == COMPARE_MATCH
	SET_BIT(TIMSK, TIMSK_OCIE1A);
	SET_BIT(TIMSK, TIMSK_OCIE1B);

#endif


#elif TIMER1_INTERRUPT_ENABLE == DISABLED

#if  TIMER1_MODE_SELECTION == NORMAL

	CLR_BIT(TIMSK, TIMSK_TOIE1);
#elif TIMER1_MODE_SELECTION  == COMPARE_MATCH_TOP_ICR1
	CLR_BIT(TIMSK, TIMSK_OCIE1A);
	CLR_BIT(TIMSK, TIMSK_OCIE1B);
#endif

#endif

	/* Set Prescaler */

	TCCR1B &= MASK_LEAST_3_BIT;
	TCCR1B |= TIMER1_PRESCALER_SELECTION;

}

void TIMER1_voidSetPreloadValue(uint8 Copy_u8PreloadVal){
	TCNT1 =Copy_u8PreloadVal;
}

void TIMER1_voidSetCompareValue(TIMER1_OUT_PIN Copy_OutPin,uint16 Copy_u16CompareVal){

	if(Copy_OutPin == TIMER1_OC1A){
		OCR1A = Copy_u16CompareVal;
	}else if(Copy_OutPin == TIMER1_OC1B){
		OCR1B = Copy_u16CompareVal;
	}

}

void TIMER1_voidSetPrescaler(TIMER_Prescaler_t  Copy_PrescalerVal){
	TCCR1B &= MASK_LEAST_3_BIT;
	TCCR1B |= Copy_PrescalerVal;
}

/* Timer 0  Overflow ISR */

__attribute__((signal))  void __vector_11(void);

void __vector_11(void){

	if(GlobalCallBackFucn[TIMER0_OV_INT] != NULL){
		GlobalCallBackFucn[TIMER0_OV_INT]();
	}

}


/* Timer 0  Overflow ISR */

__attribute__((signal))  void __vector_10(void);

void __vector_10(void){

	if(GlobalCallBackFucn[TIMER0_OC_INT] != NULL){
		GlobalCallBackFucn[TIMER0_OC_INT]();
	}

}


/*TIMER1 OVF*/
__attribute__((signal)) void __vector_9(void);
void __vector_9(void){

	if(GlobalCallBackFucn[TIMER1_OV_INT] != NULL){
		GlobalCallBackFucn[TIMER1_OV_INT]();
	}
}
/*TIMER1 COMPB*/
__attribute__((signal)) void __vector_8(void);
void __vector_8(void){

	if(GlobalCallBackFucn[TIMER1_OC1B_INT] != NULL){
		GlobalCallBackFucn[TIMER1_OC1B_INT]();
	}
}

/*TIMER1 COMPA*/
__attribute__((signal)) void __vector_7(void);
void __vector_7(void){
	if(GlobalCallBackFucn[TIMER1_OC1A_INT] != NULL){
		GlobalCallBackFucn[TIMER1_OC1A_INT]();
	}
}

