#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"
#include "WDT_interface.h"
#include "WDT_reg.h"
#include "WDT_prv.h"

uint8 WDT_u8SetTime(WDT_Time_t Copy_enTimeOpt){
	uint8 Local_u8ErrState = OK;

	if(Copy_enTimeOpt >WDT_2_1_s || Copy_enTimeOpt < WDT_16_3_ms){

		Local_u8ErrState = NOK;

	}else{

		/*Mask Least 3bit*/
		WDTCR &=WDT_MASK_LEAST_3_BIT;
		WDTCR |= Copy_enTimeOpt;

	}

	return Local_u8ErrState;
}
void WDT_voidEnable(){

	SET_BIT(WDTCR, WDTCR_WDE);

}
void WDT_voidDisable(){


	if(SREG & (1<<SREG_I)){    /*if GIE Enabled */

		__asm volatile("CLI");  /* Disable GIE */

		/*In the same operation, write a logic one to WDTOE and WDE*/
		WDTCR = 0b00011000;

		/* write a logic 0 to WDE */
		WDTCR = 0;

		__asm volatile("SEI");   /*Enable GIE */

	}else{

		/*In the same operation, write a logic one to WDTOE and WDE*/
		WDTCR = 0b00011000;

		/* write a logic 0 to WDE */
		WDTCR = 0;

	}


}
void WDT_voidRest(){

	/* Reset Counting */
	__asm volatile("WDR");
}
