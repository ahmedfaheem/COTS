#ifndef TIMER_CFG_H
#define TIMER_CFG_H

/*************TIMER0******************/

/*
1- NORMAL    -> overflow mode
2-PHASE_CORRECT_PWM
3-COMPARE_MATCH
4- FAST_PWM

 */
#define   TIMER0_MODE_SELECTION     FAST_PWM




/*
  Prescaler Selection

  1- NO_CLOCK
  2- NO_PRESCALER
  3- PRESCALER_DIVISION_8
  4- PRESCALER_DIVISION_64
  5- PRESCALER_DIVISION_256
  6- PRESCALER_DIVISION_1024
  7- EXTERNAL_CLOCK_FALLING_EDGE
  8- EXTERNAL_CLOCK_RISING_EDGE

 */

#define TIMER0_PRESCALER_SELECTION     PRESCALER_DIVISION_256

/*
  Interrupt Status
  1- ENABLED
  2- DISABLED
 */

#define TIMER0_INTERRUPT_ENABLE        DISABLED

/*
  Set Init Preload value
 */
#define TIMER0_INIT_PRELOAD_VAL        230





/* Compare Output Mode
 Select Hardware Action on OC0 PIN On TIMER0
 1- NO_HW_ACTION
 2- TOGGEL_PIN_HW_ACTION
 3- CLEAR_PIN_HW_ACTION
 4- SET_PIN_HW_ACTION
 */
#define TIMER0_COMPARE_MODE_HW_ACTION_OC0    NO_HW_ACTION

/*
  Set Init Compare value  CTC MODE
 */

#define TIMER0_CTC_INIT_COMPARE_VAL        200



/* Compare Output Mode, Fast PWM Mode
   Select Fast PWM Mode Options
   1- FAST_PWM_DISCONNECTED
   2- FAST_PWM_CLR_ONCOMP_SET_ONTOP         -> non inverted mode
   3- FAST_PWM_SET_ONCOMP_CLR_ONTOP         -> inverted mode

 */

#define TIMER0_FAST_PWM_MODE_SELECTION      FAST_PWM_CLR_ONCOMP_SET_ONTOP

/*
  Set Init Compare value  FAST PWM  --> min val 0  -- max - 255
 */

#define TIMER0_FAST_PWM_INIT_COMPARE_VAL        0




/*************TIMER1 - 16bit timer******************/


/*
1- NORMAL    -> overflow mode
2-COMPARE_MATCH_TOP_ICR1
3- FAST_PWM_TOP_ICR1

 */

#define   TIMER1_MODE_SELECTION     FAST_PWM_TOP_ICR1



/*Prescaler Selection

  1- NO_CLOCK
  2- NO_PRESCALER
  3- PRESCALER_DIVISION_8
  4- PRESCALER_DIVISION_64
  5- PRESCALER_DIVISION_256
  6- PRESCALER_DIVISION_1024
  7- EXTERNAL_CLOCK_FALLING_EDGE
  8- EXTERNAL_CLOCK_RISING_EDGE

 */

#define TIMER1_PRESCALER_SELECTION     PRESCALER_DIVISION_8


/* Compare Output Mode, Fast PWM Mode
   Select Fast PWM Mode Options
   1- FAST_PWM_DISCONNECTED
   2- FAST_PWM_CLR_ONCOMP_SET_ONTOP         -> non inverted mode
   3- FAST_PWM_SET_ONCOMP_CLR_ONTOP         -> inverted mode

 */

#define TIMER1_FAST_PWM_MODE_SELECTION      FAST_PWM_CLR_ONCOMP_SET_ONTOP

/* Set Init TOP Value */

#define TIMER1_INIT_TOP_VAL        40000



/*
  Set Init Compare value  CTC MODE   16bit
 */

#define TIMER1_CTC_OCRA1_INIT_COMPARE_VAL        0

#define TIMER1_CTC_OCRB1_INIT_COMPARE_VAL        0


/*
  Set Init Compare value  FAST PWM  --> 16bit
 */

#define TIMER1_FAST_PWM_OCRA1_INIT_COMPARE_VAL        0

#define TIMER1_FAST_PWM_OCRB1_INIT_COMPARE_VAL        0


/*
  Interrupt Status
  1- ENABLED
  2- DISABLED
 */

#define TIMER1_INTERRUPT_ENABLE        DISABLED



#endif
