#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "LED_interface.h"
#include "LED_prv.h"
#include "LED_cfg.h"
#include "DIO_interface.h"
#include "ErrType.h"





uint8 LED_u8SetOn(const LED_Confg_t* Copy_pConfig){

	uint8 Local_u8Error_State = OK;

	if(Copy_pConfig != NULL){

		if(Copy_pConfig->LED_u8ActiveType == ACT_HIGH){

			DIO_u8SetPinValue(Copy_pConfig->LED_u8Port, Copy_pConfig->LED_u8Pin, DIO_u8PIN_HIGH);


		}else if(Copy_pConfig->LED_u8ActiveType == ACT_LOW){

			DIO_u8SetPinValue(Copy_pConfig->LED_u8Port, Copy_pConfig->LED_u8Pin, DIO_u8PIN_LOW);

		}else{

			Local_u8Error_State = NOK;
		}

	}else{

		Local_u8Error_State = NULL_PTR_ERR;
	}

	return Local_u8Error_State;

}

uint8 LED_u8SetOff(const LED_Confg_t* Copy_pConfig){

	uint8 Local_u8Error_State = OK;

	if(Copy_pConfig != NULL){

		if(Copy_pConfig->LED_u8ActiveType == ACT_HIGH){

			DIO_u8SetPinValue(Copy_pConfig->LED_u8Port, Copy_pConfig->LED_u8Pin, DIO_u8PIN_LOW);


		}else if(Copy_pConfig->LED_u8ActiveType == ACT_LOW){

			DIO_u8SetPinValue(Copy_pConfig->LED_u8Port, Copy_pConfig->LED_u8Pin, DIO_u8PIN_HIGH);

		}else{

			Local_u8Error_State = NOK;
		}

	}else{

		Local_u8Error_State = NULL_PTR_ERR;
	}

	return Local_u8Error_State;


}

uint8 LED_u8Toggle(const LED_Confg_t* Copy_pConfig){

	uint8 Local_u8Error_State = OK;


	if(Copy_pConfig != NULL){

		DIO_u8TogglePinValue(Copy_pConfig->LED_u8Port, Copy_pConfig->LED_u8Pin);


	}else{

		Local_u8Error_State = NULL_PTR_ERR;
	}

	return Local_u8Error_State;


}
