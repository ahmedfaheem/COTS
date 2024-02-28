#include "STD_TYPES.h"
#include "ErrType.h"
#include "PWM_interface.h"
#include "PWM_cfg.h"
#include "PWM_prv.h"
#include "TIMER_interface.h"


static void ICU_Helper();
static void voidOverFlowCounter();
static uint32 *PWM_pu32Period = NULL;
static uint32 *PWM_pu32OnTime = NULL;
static uint16 PWM_OverflowCounter = 0;
uint8 PWM_u8Set(uint16 Copy_u16Period_ms,uint16 Copy_u16ONTime_ms){
	uint8 Local_u8ErrState = OK;

	if(Copy_u16ONTime_ms < Copy_u16Period_ms){

		TIMER1_cfg_t Local_sTimer1_Cfg = {
				.WFG_Mode=T1_FAST_PWM_TOP_ICR1,
				.OC1A_Opt = T1_OC1A_FAST_PWM_CLRON_COM_SETON_TOP,
				.OC1B_Opt = T1_OC1B_DISCONNECT,
				.Prescaler = TIMER_PRESCALER_DIVISION_256,
				.ICU_Trigger_Opt = T1_ICU_NONE,
				.ICU_Noise_State = T1_ICU_DISABLED_NOISE_CANCELER,
				.INT_State = T1_INT_DISABLED
		};

		uint16  Local_u16TopVal =(uint16)((((uint32)Copy_u16Period_ms)* 1000UL)/ PWM_SYSTEM_FREQENCY_ON_MHz);
		uint16  Local_u16CompareVal =(uint16)((((uint32)Copy_u16ONTime_ms)* 1000UL)/ PWM_SYSTEM_FREQENCY_ON_MHz);

		TIMER1_u8Init(&Local_sTimer1_Cfg);

		TIMER1_u8SetCompareValue(TIMER1_OC1A,Local_u16CompareVal);
		TIMER1_u8SetTopValue(T1_ICR1_TOP,Local_u16TopVal);

	}else{
		Local_u8ErrState = NOK;
	}


	return Local_u8ErrState;
}


uint8 PWM_u8Get(uint32 *Copy_pu32Period_us, uint32 *Copy_pu32ONTime_us){

	uint8 Local_u8ErrState = OK;

	if(Copy_pu32Period_us != NULL && Copy_pu32ONTime_us != NULL){

		TIMER1_cfg_t Local_sTimer1_Cfg = {
				.WFG_Mode=T1_NORMAL,
				.OC1A_Opt = T1_OC1B_DISCONNECT,
				.OC1B_Opt = T1_OC1B_DISCONNECT,
				.Prescaler = TIMER_PRESCALER_DIVISION_1024,
				.ICU_Trigger_Opt = T1_ICU_RISING_EDGE,
				.ICU_Noise_State = T1_ICU_ENABLED_NOISE_CANCELER,
				.INT_State = T1_INT_ICU
		};


		PWM_pu32Period = Copy_pu32Period_us;
		PWM_pu32OnTime = Copy_pu32ONTime_us;


		TIMER1_u8Init(&Local_sTimer1_Cfg);
		TIMER1_u8EnableInt(T1_INT_OVERFLOW);
		TIMER_u8SetCallBackFunc(TIMER1_ICU_INT,ICU_Helper);
		TIMER_u8SetCallBackFunc(TIMER1_OV_INT,voidOverFlowCounter);


	}else{
		Local_u8ErrState = NULL_PTR_ERR;
	}



	return Local_u8ErrState;
}



static void ICU_Helper(){

	volatile static uint8 Counter = 0;
	volatile static uint32 Period_Reading_1 = 0;
	volatile static uint32 Period_Reading_2 = 0;
	volatile static uint32 OnTime_Reading = 0;
	volatile static uint16 PWM_TickTime = 1024/PWM_SYSTEM_FREQENCY_ON_MHz;
	Counter++;

	if(Counter == 1){
		PWM_OverflowCounter = 0;
		Period_Reading_1 = TIMER1_u16ReadTimerTopICR1();

	}else if (Counter == 2){

		Period_Reading_2  = PWM_OverflowCounter * 65536 + TIMER1_u16ReadTimerTopICR1();
		*PWM_pu32Period = Period_Reading_2 - Period_Reading_1;
		TIMER1_u8Set_ICU_Edge_Trigger(T1_ICU_FALLING_EDGE);

	}else if(Counter == 3){
		OnTime_Reading = PWM_OverflowCounter * 65536 + TIMER1_u16ReadTimerTopICR1();
		*PWM_pu32OnTime = OnTime_Reading  - Period_Reading_2;
		*PWM_pu32Period = ((*PWM_pu32Period) *  (uint32)PWM_TickTime);
		*PWM_pu32OnTime = ((*PWM_pu32OnTime) *  (uint32)PWM_TickTime);
		 TIMER1_vStopTimer();
		TIMER1_u8DisableInt(T1_INT_DISABLED);
		PWM_OverflowCounter = 0;
		Counter = 0;
	}

}


static void voidOverFlowCounter(){

	PWM_OverflowCounter++;

}

