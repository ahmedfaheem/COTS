#ifndef TIMER_PRV_H
#define TIMER_PRV_H


#define NORMAL              1u
#define PHASE_CORRECT_PWM   2u
#define COMPARE_MATCH       3u
#define FAST_PWM            4u



#define NO_CLOCK                     0u
#define NO_PRESCALER                 1u
#define PRESCALER_DIVISION_8         2u
#define PRESCALER_DIVISION_64        3u
#define PRESCALER_DIVISION_256       4u
#define PRESCALER_DIVISION_1024      5u
#define EXTERNAL_CLOCK_FALLING_EDGE  6u
#define EXTERNAL_CLOCK_RISING_EDGE   7u


#define ENABLED  1u
#define DISABLED 2u




#define MASK_LEAST_3_BIT      0b11111000




#define NO_HW_ACTION            1u
#define TOGGEL_PIN_HW_ACTION    2u
#define CLEAR_PIN_HW_ACTION     3u
#define SET_PIN_HW_ACTION       4u



#define FAST_PWM_DISCONNECTED        1u
#define FAST_PWM_CLR_ONCOMP_SET_ONTOP    2u
#define FAST_PWM_SET_ONCOMP_CLR_ONTOP    3u


/*TIMER1*/

#define COMPARE_MATCH_TOP_ICR1    2u
#define FAST_PWM_TOP_ICR1         3u


#define MASK_LEAST_3_BIT 0b11111000
#endif
