#include "STD_TYPES.h"
#include "ErrType.h"
#include "DIO_interface.h"
#include "DAC_cfg.h"
#include "DAC_prv.h"
#include <util/delay.h>





uint8 DAC_u8SetAnalogValue(uint8  Copy_u8Volt){
	
	uint8 Local_u8ErrState = OK;
	uint16 Local_u8Digital = (Copy_u8Volt*RESOLUTION_POSSIBLE)  / VREF;

	if(Copy_u8Volt <= VREF){


       sint32 Local_s16LoopCounter = 0;

       for(Local_s16LoopCounter = 0; Local_s16LoopCounter <= Local_u8Digital;Local_s16LoopCounter++){
         	   DIO_u8SetPortValue(DAC_u8PORT, Local_s16LoopCounter);
         	   _delay_ms(5);
            }


       for(Local_s16LoopCounter = Local_u8Digital-1; Local_s16LoopCounter >= 0;Local_s16LoopCounter--){
        	   DIO_u8SetPortValue(DAC_u8PORT, Local_s16LoopCounter);
        	   _delay_ms(5);

      }

	}else{
		Local_u8ErrState = NOK;
	}


	return Local_u8ErrState;
}
