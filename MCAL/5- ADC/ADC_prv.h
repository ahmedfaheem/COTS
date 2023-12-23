#ifndef ADC_PRV_H
#define ADC_PRV_H


#define AREF   1u
#define AVCC   2u
#define INTERNAL   3u


#define _8BIT 1u
#define _10BIT 2u


#define ENABLE  1u
#define DISABLED 2u


#define DIVISION_BY_2  1u
#define DIVISION_BY_4  2u
#define DIVISION_BY_8  3u
#define DIVISION_BY_16 4u
#define DIVISION_BY_32 5u
#define DIVISION_BY_64 6u
#define DIVISION_BY_128 7u


#define PRESCALER_BIT_MASK  0b11111000
#define PRESCALER_BIT_POS    0u
#define ANALOG_CHANNEL_BIT_MASK  0b11100000

#define   SINGLE_ENDED_ADC0    0u
#define   SINGLE_ENDED_ADC1    1u
#define   SINGLE_ENDED_ADC2    2u
#define   SINGLE_ENDED_ADC3    3u
#define   SINGLE_ENDED_ADC4    4u
#define   SINGLE_ENDED_ADC5    5u
#define   SINGLE_ENDED_ADC6    6u
#define   SINGLE_ENDED_ADC7    7u



#define IDEL   1u
#define BUSY   2u


#define SINGLE_MODE  1u
#define CHAININ_MODE 2u


static void voidHandleStartChainConAsynch(void);

static void voidHandleStartSingelConAsynch(void);



#endif 
