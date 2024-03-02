#ifndef WDT_TIMER_H
#define WDT_TIMER_H


enum{

	WDT_16_3_ms,
	WDT_32_5_ms,
	WDT_65_ms,
	WDT_130_ms,
	WDT_260_ms,
	WDT_520_ms,
	WDT_1_s,
	WDT_2_1_s
}typedef WDT_Time_t;

uint8 WDT_u8SetTime(WDT_Time_t Copy_enTimeOpt);

void WDT_voidEnable();

void WDT_voidDisable();

/*start count down again*/
void WDT_voidRest();








#endif
