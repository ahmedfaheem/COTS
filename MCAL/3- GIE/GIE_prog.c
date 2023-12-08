#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GIE_interface.h"
#include "GIE_reg.h"

void GIE_voidEnableGlobal(void){

      __asm volatile("SEI");   /* inline assembly Set I-Bit */
	/* SET_BIT(SREG, SREG_I);*/
	 
}

void GIE_voidDisableGlobal(void){
	
	   __asm volatile("CLI");  /* inline assembly Clear I-Bit */

	/* CLR_BIT(SREG, SREG_I);*/
		 
}