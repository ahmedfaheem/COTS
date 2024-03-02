#ifndef PWM_INTERFACE_H
#define PWM_INTERFACE_H


enum{
	PERIODIC,
	ONCE
}typedef Schedule_Iteration_t;
/*Work With Timer1 - PWM Mode - On OC1A -> Pin D5  --> Set on MilleSeocnd*/
uint8 PWM_u8Set(uint16 Copy_u16Period_ms,uint16 Copy_u16ONTime_ms);

/*Return Period and On Time on Microsecond -- Enable GIE */
uint8 PWM_u8Get(uint32 *Copy_pu32Period_us, uint32 *Copy_pu32ONTime_us);

/* use timer 0  - Enable GIE
 * Copy_u8PeriodcOrOnce : have 2 Option
   1- PERIODIC
   2- ONCE
 * */
uint8 Schedule_u8Ms(uint32 Copy_u32TimeMs, Schedule_Iteration_t Copy_enPeriodicOrOnce,  void (*const Copy_vCallBackFunc)(void) );

#endif
