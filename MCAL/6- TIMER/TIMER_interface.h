#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H


enum{

	TIMER0_OV_INT,  /* overflow source */
	TIMER0_OC_INT,   /* Output Compare Match */
	TIMER1_OV_INT,
	TIMER1_OC1A_INT,
	TIMER1_OC1B_INT,


}typedef TIMER_IntSource_t;

enum{
   TIMER1_OC1A,
   TIMER1_OC1B,
}typedef TIMER1_OUT_PIN;
enum{
	 TIMER_NO_CLOCK,
	 TIMER_NO_PRESCALER,
	 TIMER_PRESCALER_DIVISION_8,
	 TIMER_PRESCALER_DIVISION_64,
	 TIMER_PRESCALER_DIVISION_256,
	 TIMER_PRESCALER_DIVISION_1024,
	 TIMER_EXTERNAL_CLOCK_FALLING_EDGE,
	 TIMER_EXTERNAL_CLOCK_RISING_EDGE,

}typedef TIMER_Prescaler_t;

/*TIMER 0 */

void TIMER0_voidInit();

uint8 TIMER_u8SetCallBackFunc(uint8 Copy_u8IntSource,void(*Copy_pvCallBackFucn)(void));

void TIMER0_voidSetPreloadValue(uint8 Copy_u8PreloadVal);

void TIMER0_voidSetCompareValue(uint8 Copy_u8CompareVal);

void TIMER0_voidSetPrescaler(TIMER_Prescaler_t  Copy_PrescalerVal);

void TIMER0_voidStop();

/* TIMER 1 */
void TIMER1_voidInit();

/*Out Pin TIMER1_OC1A,  TIMER1_OC1B*/
void TIMER1_voidSetCompareValue(TIMER1_OUT_PIN Copy_OutPin,uint16 Copy_u16CompareVal);

void TIMER1_voidSetPreloadValue(uint8 Copy_u8PreloadVal);

void TIMER1_voidSetPrescaler(TIMER_Prescaler_t  Copy_PrescalerVal);


#endif
