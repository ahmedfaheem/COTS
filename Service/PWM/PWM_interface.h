#ifndef PWM_INTERFACE_H
#define PWM_INTERFACE_H


/*Work With Timer1 - PWM Mode - On OC1A -> Pin D5  --> Set on MilleSeocnd*/
uint8 PWM_u8Set(uint16 Copy_u16Period_ms,uint16 Copy_u16ONTime_ms);

/*Return Period and On Time on Microsecond */
uint8 PWM_u8Get(uint32 *Copy_pu32Period_us, uint32 *Copy_pu32ONTime_us);



#endif
