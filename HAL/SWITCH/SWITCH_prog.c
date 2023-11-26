#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SWITCH_interface.h"
#include "SWITCH_prv.h"
#include "SWITCH_cfg.h"
#include "DIO_interface.h"
#include "ErrType.h"


uint8 SWITCH_u8GetState(const SW_Config_t *Copy_pConfig, uint8 *SW_u8State){

	uint8 Local_u8Error_State = OK;
	uint8 Local_u8State;
	DIO_u8ReadPinValue(Copy_pConfig->SWITCH_u8Port, Copy_pConfig->SWITCH_u8Pin, &Local_u8State);

	if(Copy_pConfig != NULL && SW_u8State != NULL){

       if(Copy_pConfig->SWITCH_u8Type == PULL_UP){

           if(Local_u8State == DIO_u8PIN_LOW){
        	   *SW_u8State = SW_PRESSED;
           }else{
        	   *SW_u8State = SW_RELEASES;
           }

       }else if(Copy_pConfig->SWITCH_u8Type == PULL_DOWN){


           if(Local_u8State == DIO_u8PIN_HIGH){
        	   *SW_u8State = SW_PRESSED;
           }else{
        	   *SW_u8State = SW_RELEASES;
           }

       }else{

    	   Local_u8Error_State = NOK;
       }

	}


  return Local_u8Error_State;
}
