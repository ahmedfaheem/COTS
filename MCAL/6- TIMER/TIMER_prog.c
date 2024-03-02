#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"
#include "TIMER_interface.h"
#include "TIMER_reg.h"
#include "TIMER_cfg.h"
#include "TIMER_prv.h"

/*  Timer0 ISR  -> 2
 *  Timer1 ISR  -> 4
 *  Timer2 ISR  -> 2
 */

static void(*GlobalCallBackFucn[8])(void) = {NULL};

uint8 TIMER0_u8Init(const TIMER0_cfg_t  *Copy_suCfg){

	uint8 Local_u8ErrState = OK;

	if(Copy_suCfg != NULL){

		/* Select Mode */
		switch(Copy_suCfg->WFG_Mode){
		case T0_NORMAL:CLR_BIT(TCCR0, TCCR0_WGM00);CLR_BIT(TCCR0, TCCR0_WGM01);break;
		case T0_COMPARE_MATCH:CLR_BIT(TCCR0, TCCR0_WGM00);SET_BIT(TCCR0, TCCR0_WGM01); break;
		case T0_FAST_PWM:SET_BIT(TCCR0, TCCR0_WGM00);SET_BIT(TCCR0, TCCR0_WGM01); break;
		case T0_PHASE_CORRECT_PWM:SET_BIT(TCCR0, TCCR0_WGM00);CLR_BIT(TCCR0, TCCR0_WGM01); break;
		default: Local_u8ErrState = NOK;
		}

		/* Enable Interrupt Mode*/
		switch(Copy_suCfg->INT_State){
		case T0_INT_OVERFLOW:SET_BIT(TIMSK, TIMSK_TOIE0); break;
		case T0_INT_COMPARE: SET_BIT(TIMSK, TIMSK_OCIE0); break;
		case T0_INT_DISABLED:CLR_BIT(TIMSK, TIMSK_TOIE0); CLR_BIT(TIMSK, TIMSK_OCIE0);break;
		default:Local_u8ErrState = NOK;
		}

		/* Select Hardware action on Pin OC0*/

		switch(Copy_suCfg->Out_HW_Opt){
		case T0_OC0_DISCONNECT:	CLR_BIT(TCCR0, TCCR0_COM00);CLR_BIT(TCCR0, TCCR0_COM01);break;
		case T0_OC0_NON_PWM_TOGGEL:	SET_BIT(TCCR0, TCCR0_COM00);CLR_BIT(TCCR0, TCCR0_COM01);break;
		case T0_OC0_NON_PWM_CLEAR:CLR_BIT(TCCR0, TCCR0_COM00);SET_BIT(TCCR0, TCCR0_COM01);break;
		case T0_OC0_NON_PWM_SET:SET_BIT(TCCR0, TCCR0_COM00);SET_BIT(TCCR0, TCCR0_COM01);break;
		case T0_OC0_FAST_PWM_CLRON_COM_SETON_TOP:CLR_BIT(TCCR0, TCCR0_COM00);SET_BIT(TCCR0, TCCR0_COM01);break;
		case T0_OC0_FAST_PWM_SETON_COM_CLRON_TOP:SET_BIT(TCCR0, TCCR0_COM00);SET_BIT(TCCR0, TCCR0_COM01);break;
		case T0_OC0_PHASE_CORRECT_PWM_CLRON_UPCOUNTCOM_SETON_DOWNCOUNTCOM:CLR_BIT(TCCR0, TCCR0_COM00);SET_BIT(TCCR0, TCCR0_COM01);break;
		case T0_OC0_PHASE_CORRECT_PWM_SETON_UPCOUNTCOM_CLRON_DOWNCOUNTCOM:SET_BIT(TCCR0, TCCR0_COM00);SET_BIT(TCCR0, TCCR0_COM01);break;
		default: Local_u8ErrState= NOK;
		}

		/*Set Prescaler */
		TCCR0 &= MASK_LEAST_3_BIT;
		TCCR0 |= (Copy_suCfg->Prescaler);

	}else{
		Local_u8ErrState = NULL_PTR_ERR;
	}



	return Local_u8ErrState;

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


uint8 TIMER0_u8SetCompareOutputMode(TIMER0_OUT_HW_Option Copy_u8OutputMode){
	uint8 Local_u8ErrState = OK;
	switch(Copy_u8OutputMode){
	case T0_OC0_DISCONNECT:	CLR_BIT(TCCR0, TCCR0_COM00);CLR_BIT(TCCR0, TCCR0_COM01);break;
	case T0_OC0_NON_PWM_TOGGEL:	SET_BIT(TCCR0, TCCR0_COM00);CLR_BIT(TCCR0, TCCR0_COM01);break;
	case T0_OC0_NON_PWM_CLEAR:CLR_BIT(TCCR0, TCCR0_COM00);SET_BIT(TCCR0, TCCR0_COM01);break;
	case T0_OC0_NON_PWM_SET:SET_BIT(TCCR0, TCCR0_COM00);SET_BIT(TCCR0, TCCR0_COM01);break;
	case T0_OC0_FAST_PWM_CLRON_COM_SETON_TOP:CLR_BIT(TCCR0, TCCR0_COM00);SET_BIT(TCCR0, TCCR0_COM01);break;
	case T0_OC0_FAST_PWM_SETON_COM_CLRON_TOP:SET_BIT(TCCR0, TCCR0_COM00);SET_BIT(TCCR0, TCCR0_COM01);break;
	case T0_OC0_PHASE_CORRECT_PWM_CLRON_UPCOUNTCOM_SETON_DOWNCOUNTCOM:CLR_BIT(TCCR0, TCCR0_COM00);SET_BIT(TCCR0, TCCR0_COM01);break;
	case T0_OC0_PHASE_CORRECT_PWM_SETON_UPCOUNTCOM_CLRON_DOWNCOUNTCOM:SET_BIT(TCCR0, TCCR0_COM00);SET_BIT(TCCR0, TCCR0_COM01);break;
	default: Local_u8ErrState= NOK;
	}

	return Local_u8ErrState;
}


uint8  TIMER0_u8EnableInt(TIMER0_INT_State Copy_sIntOpt){
	uint8 Local_u8ErrState = OK;

	switch(Copy_sIntOpt){
	case T0_INT_OVERFLOW:SET_BIT(TIMSK, TIMSK_TOIE0); break;
	case T0_INT_COMPARE: SET_BIT(TIMSK, TIMSK_OCIE0); break;
	default:Local_u8ErrState = NOK;
	}

	return Local_u8ErrState;

}
uint8  TIMER0_u8DisableInt(TIMER0_INT_State Copy_sIntOpt){
	uint8 Local_u8ErrState = OK;
	switch(Copy_sIntOpt){
	case T0_INT_OVERFLOW:CLR_BIT(TIMSK, TIMSK_TOIE0); break;
	case T0_INT_COMPARE: CLR_BIT(TIMSK, TIMSK_OCIE0); break;
	case T0_INT_DISABLED:CLR_BIT(TIMSK, TIMSK_TOIE0); CLR_BIT(TIMSK, TIMSK_OCIE0);break;
	default:Local_u8ErrState = NOK;
	}
	return Local_u8ErrState;

}

void  TIMER0_vStopTimer(){
	TCCR0 &= MASK_LEAST_3_BIT;
	TCCR0 |= TIMER_NO_PRESCALER;
	/*Disable All interrupts */
	CLR_BIT(TIMSK, TIMSK_TOIE0); CLR_BIT(TIMSK, TIMSK_OCIE0);
}

/* TIMER1*/

uint8 TIMER1_u8Init(const TIMER1_cfg_t  *Copy_suCfg){

	uint8  Local_u8ErrState = OK;
	if(Copy_suCfg != NULL){

		/* MODE SELECT*/

		switch(Copy_suCfg->WFG_Mode){
		case T1_NORMAL: TCCR1A &=0b11111100; TCCR1A |=0b11111100;CLR_BIT(TCCR1B, TCCR1B_WGM13);CLR_BIT(TCCR1B, TCCR1B_WGM12); break;
		case T1_PWM_PHASE_CORRECT_8BIT:TCCR1A &=0b11111100;TCCR1A |=0b11111101;CLR_BIT(TCCR1B, TCCR1B_WGM12);CLR_BIT(TCCR1B, TCCR1B_WGM13); break;
		case T1_PWM_PHASE_CORRECT_9BIT:TCCR1A &=0b11111100;TCCR1A |=0b11111110;CLR_BIT(TCCR1B, TCCR1B_WGM12);CLR_BIT(TCCR1B, TCCR1B_WGM13); break;
		case T1_PWM_PHASE_CORRECT_10BIT:TCCR1A &=0b11111100;TCCR1A |=0b11111111;CLR_BIT(TCCR1B, TCCR1B_WGM12);CLR_BIT(TCCR1B, TCCR1B_WGM13); break;
		case T1_CTC_TOP_OCRA1:TCCR1A &=0b11111100;TCCR1A |=0b11111100;SET_BIT(TCCR1B, TCCR1B_WGM12);CLR_BIT(TCCR1B, TCCR1B_WGM13); break;
		case T1_FAST_PWM_8BIT:TCCR1A &=0b11111100;TCCR1A |=0b11111101;SET_BIT(TCCR1B, TCCR1B_WGM12);CLR_BIT(TCCR1B, TCCR1B_WGM13); break;
		case T1_FAST_PWM_9BIT:TCCR1A &=0b11111100;TCCR1A |=0b11111110;SET_BIT(TCCR1B, TCCR1B_WGM12);CLR_BIT(TCCR1B, TCCR1B_WGM13); break;
		case T1_FAST_PWM_10BIT:TCCR1A &=0b11111100;TCCR1A |=0b11111111;SET_BIT(TCCR1B, TCCR1B_WGM12);CLR_BIT(TCCR1B, TCCR1B_WGM13); break;
		case T1_PWM_PHASE_FREQENCY_CORRECT_TOP_ICR1:TCCR1A &=0b11111100;TCCR1A |=0b11111100;CLR_BIT(TCCR1B, TCCR1B_WGM12);SET_BIT(TCCR1B, TCCR1B_WGM13); break;
		case T1_PWM_PHASE_FREQENCY_CORRECT_TOP_OCR1A:TCCR1A &=0b11111100;TCCR1A |=0b11111101;CLR_BIT(TCCR1B, TCCR1B_WGM12);SET_BIT(TCCR1B, TCCR1B_WGM13); break;
		case T1_PWM_PHASE_CORRECT_TOP_ICR1:TCCR1A &=0b11111100; TCCR1A |=0b11111110;CLR_BIT(TCCR1B, TCCR1B_WGM12);SET_BIT(TCCR1B, TCCR1B_WGM13);break;
		case T1_PWM_PHASE_CORRECT_TOP_OCR1A:TCCR1A &=0b11111100;TCCR1A |=0b11111111;CLR_BIT(TCCR1B, TCCR1B_WGM12);SET_BIT(TCCR1B, TCCR1B_WGM13); break;
		case T1_CTC_TOP_ICR1:TCCR1A &=0b11111100;TCCR1A |=0b11111100;SET_BIT(TCCR1B, TCCR1B_WGM12);SET_BIT(TCCR1B, TCCR1B_WGM13); break;
		case T1_FAST_PWM_TOP_ICR1:TCCR1A &=0b11111100;TCCR1A |=0b11111110;SET_BIT(TCCR1B, TCCR1B_WGM12);SET_BIT(TCCR1B, TCCR1B_WGM13); break;
		case T1_FAST_PWM_TOP_OCR1A:TCCR1A &=0b11111100;TCCR1A |=0b11111111;SET_BIT(TCCR1B, TCCR1B_WGM12);SET_BIT(TCCR1B, TCCR1B_WGM13); break;
		default: Local_u8ErrState = NOK;
		}

		/*Set HW Action On OC1A*/

		switch(Copy_suCfg->OC1A_Opt){
		case T1_OC1A_DISCONNECT:CLR_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0);  break;
		case T1_OC1A_NON_PWM_TOGGEL_ONCOMPARE:CLR_BIT(TCCR1A, TCCR1A_COM1A1);SET_BIT(TCCR1A, TCCR1A_COM1A0);break;
		case T1_OC1A_NON_PWM_CLEAR_ONCOMPARE:SET_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0); break;
		case T1_OC1A_NON_PWM_SET_ONCOMPARE:SET_BIT(TCCR1A, TCCR1A_COM1A1);SET_BIT(TCCR1A, TCCR1A_COM1A0);break;
		case T1_OC1A_FAST_PWM_CLRON_COM_SETON_TOP:SET_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0);break;
		case T1_OC1A_FAST_PWM_SETON_COM_CLRON_TOP:SET_BIT(TCCR1A, TCCR1A_COM1A1);SET_BIT(TCCR1A, TCCR1A_COM1A0); break;
		case T1_OC1A_PHASE_CORRECT_PWM_CLRON_UPCOUNTCOM_SETON_DOWNCOUNTCOM:SET_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0);break;
		case T1_OC1A_PHASE_CORRECT_PWM_SETON_UPCOUNTCOM_CLRON_DOWNCOUNTCOM:SET_BIT(TCCR1A, TCCR1A_COM1A1);SET_BIT(TCCR1A, TCCR1A_COM1A0); break;
		default: Local_u8ErrState = NOK;
		}

		/*Set HW Action On OC1B*/

		switch(Copy_suCfg->OC1B_Opt){
		case T1_OC1B_DISCONNECT:CLR_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0);  break;
		case T1_OC1B_NON_PWM_TOGGEL_ONCOMPARE:CLR_BIT(TCCR1A, TCCR1A_COM1B1);SET_BIT(TCCR1A, TCCR1A_COM1B0); break;
		case T1_OC1B_NON_PWM_CLEAR_ONCOMPARE:SET_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0); break;
		case T1_OC1B_NON_PWM_SET_ONCOMPARE:SET_BIT(TCCR1A, TCCR1A_COM1B1);SET_BIT(TCCR1A, TCCR1A_COM1B0); break;
		case T1_OC1B_FAST_PWM_CLRON_COM_SETON_TOP:SET_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0); break;
		case T1_OC1B_FAST_PWM_SETON_COM_CLRON_TOP:SET_BIT(TCCR1A, TCCR1A_COM1B1);SET_BIT(TCCR1A, TCCR1A_COM1B0); break;
		case T1_OC1B_PHASE_CORRECT_PWM_CLRON_UPCOUNTCOM_SETON_DOWNCOUNTCOM:SET_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0); break;
		case T1_OC1B_PHASE_CORRECT_PWM_SETON_UPCOUNTCOM_CLRON_DOWNCOUNTCOM:SET_BIT(TCCR1A, TCCR1A_COM1B1);SET_BIT(TCCR1A, TCCR1A_COM1B0); break;
		default: Local_u8ErrState = NOK;
		}



		/*Set ICU Trigger Option*/

		switch(Copy_suCfg->ICU_Trigger_Opt){
		case T1_ICU_FALLING_EDGE:CLR_BIT(TCCR1B,TCCR1B_ICES1); break;
		case T1_ICU_RISING_EDGE:SET_BIT(TCCR1B,TCCR1B_ICES1);break;
		case T1_ICU_NONE: break;
		default:Local_u8ErrState = NOK;
		}

		/* Set ICU Noise Cancel State */

		switch(Copy_suCfg->ICU_Noise_State){
		case T1_ICU_ENABLED_NOISE_CANCELER: SET_BIT(TCCR1B,TCCR1B_ICNC1);break;
		case T1_ICU_DISABLED_NOISE_CANCELER:CLR_BIT(TCCR1B,TCCR1B_ICNC1); break;
		default: Local_u8ErrState = NOK;
		}

		/* Set Interrupt State */
		switch(Copy_suCfg->INT_State){
		case T1_INT_ICU: SET_BIT(TIMSK, TIMSK_TICIE1);break;
		case T1_INT_COMPARE_OCIE1A:SET_BIT(TIMSK,TIMSK_OCIE1A); break;
		case T1_INT_COMPARE_OCIE1B:SET_BIT(TIMSK,TIMSK_OCIE1B); break;
		case T1_INT_COMPARE_OCIE1A_B:SET_BIT(TIMSK,TIMSK_OCIE1A);SET_BIT(TIMSK,TIMSK_OCIE1B); break;
		case T1_INT_OVERFLOW:SET_BIT(TIMSK,TIMSK_TOIE1); break;
		case T1_INT_DISABLED:CLR_BIT(TIMSK, TIMSK_TICIE1);CLR_BIT(TIMSK,TIMSK_OCIE1A);CLR_BIT(TIMSK,TIMSK_OCIE1B);CLR_BIT(TIMSK,TIMSK_TOIE1); break;
		default: Local_u8ErrState = NOK;
		}

		/* Set Prescaler */

		TCCR1B &= MASK_LEAST_3_BIT;
		TCCR1B |= (Copy_suCfg->Prescaler);


	}else{
		Local_u8ErrState = NULL_PTR_ERR;
	}


	return Local_u8ErrState;

}

void TIMER1_voidSetTimerValue(uint16 Copy_u8TimerVal){
	TCNT1 =Copy_u8TimerVal;
}

uint16 TIMER1_u16ReadTimerVal(){
	return TCNT1;
}

uint8 TIMER1_u8SetCompareValue(TIMER1_OUT_PIN Copy_OutPin,uint16 Copy_u16CompareVal){
	uint8 Local_u8ErrState = OK;

	switch(Copy_OutPin){
	case TIMER1_OC1A:OCR1A = Copy_u16CompareVal; break;
	case TIMER1_OC1B: OCR1B = Copy_u16CompareVal; break;
	default:Local_u8ErrState = NOK;
	}
	return Local_u8ErrState;

}

uint8 TIMER1_u8SetTopValue(TIMER1_Top_Opt Copy_u8TopOpt, uint16 Copy_u16TopValue){
	uint8 Local_u8ErrState = OK;

	switch(Copy_u8TopOpt){
	case T1_OCR1A_TOP:   OCR1A =Copy_u16TopValue; break;
	case T1_ICR1_TOP: ICR1=Copy_u16TopValue; break;
	default: Local_u8ErrState = NOK;
	}
	return Local_u8ErrState;
}

void TIMER1_voidSetPrescaler(TIMER_Prescaler_t  Copy_PrescalerVal){
	TCCR1B &= MASK_LEAST_3_BIT;
	TCCR1B |= Copy_PrescalerVal;
}


uint8 TIMER1_u8Set_OC1A_OutPinState(TIMER1_OC1A_OutPin_State Copy_u8OC1A_Opt){
	uint8 Local_u8ErrState = OK;

	/*Set HW Action On OC1A*/

	switch(Copy_u8OC1A_Opt){
	case T1_OC1A_DISCONNECT:CLR_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0);  break;
	case T1_OC1A_NON_PWM_TOGGEL_ONCOMPARE:CLR_BIT(TCCR1A, TCCR1A_COM1A1);SET_BIT(TCCR1A, TCCR1A_COM1A0);break;
	case T1_OC1A_NON_PWM_CLEAR_ONCOMPARE:SET_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0); break;
	case T1_OC1A_NON_PWM_SET_ONCOMPARE:SET_BIT(TCCR1A, TCCR1A_COM1A1);SET_BIT(TCCR1A, TCCR1A_COM1A0);break;
	case T1_OC1A_FAST_PWM_CLRON_COM_SETON_TOP:SET_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0);break;
	case T1_OC1A_FAST_PWM_SETON_COM_CLRON_TOP:SET_BIT(TCCR1A, TCCR1A_COM1A1);SET_BIT(TCCR1A, TCCR1A_COM1A0); break;
	case T1_OC1A_PHASE_CORRECT_PWM_CLRON_UPCOUNTCOM_SETON_DOWNCOUNTCOM:SET_BIT(TCCR1A, TCCR1A_COM1A1);CLR_BIT(TCCR1A, TCCR1A_COM1A0);break;
	case T1_OC1A_PHASE_CORRECT_PWM_SETON_UPCOUNTCOM_CLRON_DOWNCOUNTCOM:SET_BIT(TCCR1A, TCCR1A_COM1A1);SET_BIT(TCCR1A, TCCR1A_COM1A0); break;
	default: Local_u8ErrState = NOK;
	}


	return Local_u8ErrState;

}
uint8 TIMER1_u8Set_OC1B_OutPinState(TIMER1_OC1B_OutPin_State Copy_u8OC1B_Opt){
	uint8 Local_u8ErrState = OK;


	/*Set HW Action On OC1B*/

	switch(Copy_u8OC1B_Opt){
	case T1_OC1B_DISCONNECT:CLR_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0);  break;
	case T1_OC1B_NON_PWM_TOGGEL_ONCOMPARE:CLR_BIT(TCCR1A, TCCR1A_COM1B1);SET_BIT(TCCR1A, TCCR1A_COM1B0); break;
	case T1_OC1B_NON_PWM_CLEAR_ONCOMPARE:SET_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0); break;
	case T1_OC1B_NON_PWM_SET_ONCOMPARE:SET_BIT(TCCR1A, TCCR1A_COM1B1);SET_BIT(TCCR1A, TCCR1A_COM1B0); break;
	case T1_OC1B_FAST_PWM_CLRON_COM_SETON_TOP:SET_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0); break;
	case T1_OC1B_FAST_PWM_SETON_COM_CLRON_TOP:SET_BIT(TCCR1A, TCCR1A_COM1B1);SET_BIT(TCCR1A, TCCR1A_COM1B0); break;
	case T1_OC1B_PHASE_CORRECT_PWM_CLRON_UPCOUNTCOM_SETON_DOWNCOUNTCOM:SET_BIT(TCCR1A, TCCR1A_COM1B1);CLR_BIT(TCCR1A, TCCR1A_COM1B0); break;
	case T1_OC1B_PHASE_CORRECT_PWM_SETON_UPCOUNTCOM_CLRON_DOWNCOUNTCOM:SET_BIT(TCCR1A, TCCR1A_COM1B1);SET_BIT(TCCR1A, TCCR1A_COM1B0); break;
	default: Local_u8ErrState = NOK;
	}
	return Local_u8ErrState;
}


uint8 TIMER1_u8Set_ICU_Edge_Trigger(TIMER1_ICU_Edge_Opt  Copy_u8ICU_Trigger_Opt){

	uint8 Local_u8ErrState = OK;

	switch(Copy_u8ICU_Trigger_Opt){
	case T1_ICU_FALLING_EDGE:CLR_BIT(TCCR1B,TCCR1B_ICES1); break;
	case T1_ICU_RISING_EDGE:SET_BIT(TCCR1B,TCCR1B_ICES1);break;
	case T1_ICU_NONE: break;
	default:Local_u8ErrState = NOK;
	}

	return Local_u8ErrState;
}


uint16 TIMER1_u16ReadTimerTopICR1(void){
	return ICR1;
}

uint8  TIMER1_u8EnableInt(TIMER1_INT_State Copy_sIntOpt){
	uint8 Local_u8ErrState = OK;

	/* Enable Interrupt State */
	switch(Copy_sIntOpt){
	case T1_INT_ICU: SET_BIT(TIMSK, TIMSK_TICIE1);break;
	case T1_INT_COMPARE_OCIE1A:SET_BIT(TIMSK,TIMSK_OCIE1A); break;
	case T1_INT_COMPARE_OCIE1B:SET_BIT(TIMSK,TIMSK_OCIE1B); break;
	case T1_INT_COMPARE_OCIE1A_B:SET_BIT(TIMSK,TIMSK_OCIE1A);SET_BIT(TIMSK,TIMSK_OCIE1B); break;
	case T1_INT_OVERFLOW:SET_BIT(TIMSK,TIMSK_TOIE1); break;
	default: Local_u8ErrState = NOK;
	}

	return Local_u8ErrState;

}
uint8  TIMER1_u8DisableInt(TIMER1_INT_State Copy_sIntOpt){
	uint8 Local_u8ErrState = OK;

	/* Disable Interrupt State */
	switch(Copy_sIntOpt){
	case T1_INT_ICU: CLR_BIT(TIMSK, TIMSK_TICIE1);break;
	case T1_INT_COMPARE_OCIE1A:CLR_BIT(TIMSK,TIMSK_OCIE1A); break;
	case T1_INT_COMPARE_OCIE1B:CLR_BIT(TIMSK,TIMSK_OCIE1B); break;
	case T1_INT_COMPARE_OCIE1A_B:CLR_BIT(TIMSK,TIMSK_OCIE1A);CLR_BIT(TIMSK,TIMSK_OCIE1B); break;
	case T1_INT_OVERFLOW:CLR_BIT(TIMSK,TIMSK_TOIE1); break;
	case T1_INT_DISABLED:CLR_BIT(TIMSK, TIMSK_TICIE1);CLR_BIT(TIMSK,TIMSK_OCIE1A);CLR_BIT(TIMSK,TIMSK_OCIE1B);CLR_BIT(TIMSK,TIMSK_TOIE1); break;
	default: Local_u8ErrState = NOK;
	}
	return Local_u8ErrState;

}

void  TIMER1_vStopTimer(){
	TCCR1B &= MASK_LEAST_3_BIT;
	TCCR1B |= TIMER_NO_CLOCK;

	/*Disable All interrupts */
	CLR_BIT(TIMSK, TIMSK_TICIE1);
	CLR_BIT(TIMSK,TIMSK_OCIE1A);
	CLR_BIT(TIMSK,TIMSK_OCIE1B);
	CLR_BIT(TIMSK,TIMSK_TOIE1);


}

/*******************Timer2********************/

uint8 TIMER2_u8Init(const TIMER2_cfg_t  *Copy_suCfg){
	uint8 Local_u8ErrState = OK;

	if(Copy_suCfg != NULL){

		/*Step 1: Disable the Timer/Counter2 interrupts*/
		CLR_BIT(TIMSK, TIMSK_TOIE2);
		CLR_BIT(TIMSK, TIMSK_OCIE2);


		/*Step 2: Set Clock Source */
		switch(Copy_suCfg->Clock_opt){
		case T2_IO_CLOCK: CLR_BIT(ASSR, ASSR_AS2); break;
		case T2_EXTERNAL_CLOCK:SET_BIT(ASSR, ASSR_AS2); break;
		default:  Local_u8ErrState= NOK;
		}


		/* Step 3: Write new values to  TCCR2*/

		/* Select Mode */
		switch(Copy_suCfg->WFG_Mode){
		case T2_NORMAL:CLR_BIT(TCCR2, TCCR2_WGM21);CLR_BIT(TCCR2, TCCR2_WGM20);break;
		case T2_COMPARE_MATCH:CLR_BIT(TCCR2, TCCR2_WGM21);SET_BIT(TCCR2, TCCR2_WGM20); break;
		case T2_FAST_PWM:SET_BIT(TCCR2, TCCR2_WGM21);SET_BIT(TCCR2, TCCR2_WGM20); break;
		case T2_PHASE_CORRECT_PWM:SET_BIT(TCCR2, TCCR2_WGM21);CLR_BIT(TCCR2, TCCR2_WGM20); break;
		default: Local_u8ErrState = NOK;
		}


		/* Select Hardware action on Pin OC2*/

		switch(Copy_suCfg->Out_HW_Opt){
		case T2_OC2_DISCONNECT:	CLR_BIT(TCCR2, TCCR2_COM20);CLR_BIT(TCCR2, TCCR2_COM21);break;
		case T2_OC2_NON_PWM_TOGGEL:	SET_BIT(TCCR2, TCCR2_COM20);CLR_BIT(TCCR2, TCCR2_COM21);break;
		case T2_OC2_NON_PWM_CLEAR:CLR_BIT(TCCR2, TCCR2_COM20);SET_BIT(TCCR2, TCCR2_COM21);break;
		case T2_OC2_NON_PWM_SET:SET_BIT(TCCR2, TCCR2_COM20);SET_BIT(TCCR2, TCCR2_COM21);break;
		case T2_OC2_FAST_PWM_CLRON_COM_SETON_TOP:CLR_BIT(TCCR2, TCCR2_COM20);SET_BIT(TCCR2, TCCR2_COM21);break;
		case T2_OC2_FAST_PWM_SETON_COM_CLRON_TOP:SET_BIT(TCCR2, TCCR2_COM20);SET_BIT(TCCR2, TCCR2_COM21);break;
		case T2_OC2_PHASE_CORRECT_PWM_CLRON_UPCOUNTCOM_SETON_DOWNCOUNTCOM:CLR_BIT(TCCR2, TCCR2_COM20);SET_BIT(TCCR2, TCCR2_COM21);break;
		case T2_OC2_PHASE_CORRECT_PWM_SETON_UPCOUNTCOM_CLRON_DOWNCOUNTCOM:SET_BIT(TCCR2, TCCR2_COM20);SET_BIT(TCCR2, TCCR2_COM21);break;
		default: Local_u8ErrState= NOK;
		}


		/*Set Prescaler */
		TCCR2 &= MASK_LEAST_3_BIT;
		TCCR2 |= (Copy_suCfg->Prescaler);


		/* Step 4: Wait for registers to update*/

		/* if Result is zero out form loop */
		while (ASSR & ((1 << ASSR_TCN2UB) | (1 << ASSR_OCR2UB) | (1 << ASSR_TCR2UB)));

		/*  while((GET_BIT(ASSR,ASSR_TCN2UB) == 0) && (GET_BIT(ASSR,ASSR_OCR2UB) == 0) (GET_BIT(ASSR,ASSR_TCR2UB) == 0));*/


		/* Step 5: Clear Timer/Counter2 Interrupt Flags */
		SET_BIT(TIFR, TIFR_OCF2);
		SET_BIT(TIFR, TIFR_TOV2);


		/* Step 6: Set Interrupt Mode*/
		switch(Copy_suCfg->INT_State){
		case T2_INT_OVERFLOW:SET_BIT(TIMSK, TIMSK_TOIE2); break;
		case T2_INT_COMPARE: SET_BIT(TIMSK, TIMSK_OCIE2); break;
		case T2_INT_DISABLED:CLR_BIT(TIMSK, TIMSK_TOIE2); CLR_BIT(TIMSK, TIMSK_OCIE2);break;
		default:Local_u8ErrState = NOK;
		}



	}else{
		Local_u8ErrState = NULL_PTR_ERR;
	}



	return Local_u8ErrState;
}





void TIMER2_voidSetPreloadValue(uint8 Copy_u8PreloadVal){

	TCNT2 = Copy_u8PreloadVal;
}
void TIMER2_voidSetCompareValue(uint8 Copy_u8CompareVal){

	OCR2 = Copy_u8CompareVal;
}
void TIMER2_voidSetPrescaler(TIMER2_Prescaler_t  Copy_PrescalerVal){
	TCCR2 &= MASK_LEAST_3_BIT;
	TCCR2 |= (Copy_PrescalerVal);
}


uint8 TIMER2_u8SetCompareOutputMode(TIMER2_OUT_HW_Option Copy_u8OutputMode){
	uint8 Local_u8ErrState = OK;

	switch(Copy_u8OutputMode){
	case T2_OC2_DISCONNECT:	CLR_BIT(TCCR2, TCCR2_COM20);CLR_BIT(TCCR2, TCCR2_COM21);break;
	case T2_OC2_NON_PWM_TOGGEL:	SET_BIT(TCCR2, TCCR2_COM20);CLR_BIT(TCCR2, TCCR2_COM21);break;
	case T2_OC2_NON_PWM_CLEAR:CLR_BIT(TCCR2, TCCR2_COM20);SET_BIT(TCCR2, TCCR2_COM21);break;
	case T2_OC2_NON_PWM_SET:SET_BIT(TCCR2, TCCR2_COM20);SET_BIT(TCCR2, TCCR2_COM21);break;
	case T2_OC2_FAST_PWM_CLRON_COM_SETON_TOP:CLR_BIT(TCCR2, TCCR2_COM20);SET_BIT(TCCR2, TCCR2_COM21);break;
	case T2_OC2_FAST_PWM_SETON_COM_CLRON_TOP:SET_BIT(TCCR2, TCCR2_COM20);SET_BIT(TCCR2, TCCR2_COM21);break;
	case T2_OC2_PHASE_CORRECT_PWM_CLRON_UPCOUNTCOM_SETON_DOWNCOUNTCOM:CLR_BIT(TCCR2, TCCR2_COM20);SET_BIT(TCCR2, TCCR2_COM21);break;
	case T2_OC2_PHASE_CORRECT_PWM_SETON_UPCOUNTCOM_CLRON_DOWNCOUNTCOM:SET_BIT(TCCR2, TCCR2_COM20);SET_BIT(TCCR2, TCCR2_COM21);break;
	default: Local_u8ErrState= NOK;
	}

	return Local_u8ErrState;
}


uint8  TIMER2_u8EnableInt(TIMER2_INT_State Copy_sIntOpt){
	uint8 Local_u8ErrState = OK;

	switch(Copy_sIntOpt){
	case T2_INT_OVERFLOW:SET_BIT(TIMSK, TIMSK_TOIE2); break;
	case T2_INT_COMPARE: SET_BIT(TIMSK, TIMSK_OCIE2); break;
	default:Local_u8ErrState = NOK;
	}

	return Local_u8ErrState;

}
uint8  TIMER2_u8DisableInt(TIMER2_INT_State Copy_sIntOpt){
	uint8 Local_u8ErrState = OK;

	switch(Copy_sIntOpt){
	case T2_INT_OVERFLOW:CLR_BIT(TIMSK, TIMSK_TOIE2); break;
	case T2_INT_COMPARE: CLR_BIT(TIMSK, TIMSK_OCIE2); break;
	case T2_INT_DISABLED:CLR_BIT(TIMSK, TIMSK_TOIE2); CLR_BIT(TIMSK, TIMSK_OCIE2);break;
	default:Local_u8ErrState = NOK;
	}
	return Local_u8ErrState;

}


void  TIMER2_vStopTimer(){
	TCCR2 &= MASK_LEAST_3_BIT;
	TCCR2 |= TIMER2_NO_CLOCK;

	/*Disable All interrupts */
	CLR_BIT(TIMSK, TIMSK_TOIE2);
	CLR_BIT(TIMSK, TIMSK_OCIE2);
}











/* Timer 0  Overflow ISR */

__attribute__((signal))  void __vector_11(void);

void __vector_11(void){

	if(GlobalCallBackFucn[TIMER0_OV_INT] != NULL){
		GlobalCallBackFucn[TIMER0_OV_INT]();
	}else{

	}

}


/* Timer 0  Out Compare match ISR */

__attribute__((signal))  void __vector_10(void);

void __vector_10(void){

	if(GlobalCallBackFucn[TIMER0_OC_INT] != NULL){
		GlobalCallBackFucn[TIMER0_OC_INT]();
	}else{

	}

}


/*TIMER1 OVF*/
__attribute__((signal)) void __vector_9(void);
void __vector_9(void){

	if(GlobalCallBackFucn[TIMER1_OV_INT] != NULL){
		GlobalCallBackFucn[TIMER1_OV_INT]();
	}else{

	}
}
/*TIMER1 COMPB*/
__attribute__((signal)) void __vector_8(void);
void __vector_8(void){

	if(GlobalCallBackFucn[TIMER1_OC1B_INT] != NULL){
		GlobalCallBackFucn[TIMER1_OC1B_INT]();
	}else{

	}
}

/*TIMER1 COMPA*/
__attribute__((signal)) void __vector_7(void);
void __vector_7(void){
	if(GlobalCallBackFucn[TIMER1_OC1A_INT] != NULL){
		GlobalCallBackFucn[TIMER1_OC1A_INT]();
	}else{

	}
}


/*TIMER1 ICU Int  CAPT*/
__attribute__((signal)) void __vector_6(void);
void __vector_6(void){
	if(GlobalCallBackFucn[TIMER1_ICU_INT] != NULL){
		GlobalCallBackFucn[TIMER1_ICU_INT]();
	}else{

	}
}




/* Timer 2 Overflow ISR */

__attribute__((signal))  void __vector_5(void);

void __vector_5(void){

	if(GlobalCallBackFucn[TIMER2_OV_INT] != NULL){
		GlobalCallBackFucn[TIMER2_OV_INT]();
	}else{

	}

}


/* Timer 2  Out Compare match ISR */

__attribute__((signal))  void __vector_4(void);

void __vector_4(void){

	if(GlobalCallBackFucn[TIMER2_OC_INT] != NULL){
		GlobalCallBackFucn[TIMER2_OC_INT]();
	}

}
