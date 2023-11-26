#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SSD_interface.h"
#include "SSD_prv.h"
#include "SSD_cfg.h"
#include "DIO_interface.h"
#include "ErrType.h"


uint8 SSD_u8On(const SDD_Confg_t* Copy_pConfig){

	uint8 Local_u8Error_State = OK;

	if(Copy_pConfig != NULL){

		if(Copy_pConfig->SSD_u8Type == ANODE || Copy_pConfig->SSD_u8Type == ETAKIT ){

			DIO_u8SetPinValue(Copy_pConfig->SSD_u8Enable_Port, Copy_pConfig->SSD_u8Enable_Pin, DIO_u8PIN_HIGH);
		}else if(Copy_pConfig->SSD_u8Type == CATHOD ){

			DIO_u8SetPinValue(Copy_pConfig->SSD_u8Enable_Port, Copy_pConfig->SSD_u8Enable_Pin, DIO_u8PIN_LOW);

		}else{
			Local_u8Error_State = NOK;

		}

	}else{
		Local_u8Error_State = NULL_PTR_ERR;
	}


	return Local_u8Error_State;

}

uint8 SSD_u8Off(const SDD_Confg_t* Copy_pConfig){

	uint8 Local_u8Error_State = OK;

	if(Copy_pConfig != NULL){

		if(Copy_pConfig->SSD_u8Type == ANODE || Copy_pConfig->SSD_u8Type == ETAKIT ){

			DIO_u8SetPinValue(Copy_pConfig->SSD_u8Enable_Port, Copy_pConfig->SSD_u8Enable_Pin, DIO_u8PIN_LOW);
		}else if(Copy_pConfig->SSD_u8Type == CATHOD ){

			DIO_u8SetPinValue(Copy_pConfig->SSD_u8Enable_Port, Copy_pConfig->SSD_u8Enable_Pin, DIO_u8PIN_HIGH);

		}else{
			Local_u8Error_State = NOK;

		}

	}else{
		Local_u8Error_State = NULL_PTR_ERR;
	}



	return Local_u8Error_State;
}

uint8 SSD_u8SetNumber(const SDD_Confg_t* Copy_pConfig, uint8 Copy_u8Number){

	uint8 Local_u8Error_State = OK;

	uint8 SSD_Arr[10]={   // Local_Au8SSD_Decode
			0b00111111, // 0
			0b00000110,  // 1
			0b01011011,  // 2
			0b01001111,  // 3
			0b01100110,  // 4
			0b01101101,  // 5
			0b01111101,  // 6
			0b00000111, // 7
			0b11111111, // 8
			0b01101111  //9
	};

	uint8 Local_u8Number = 0;

	if(Copy_pConfig != NULL){

		if(Copy_pConfig->SSD_u8Type == ANODE ){

			Local_u8Number = ~SSD_Arr[Copy_u8Number];

			if(Copy_pConfig->SSD_u8LedA_Pin == DIO_u8PIN0){

				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN0, GET_BIT(Local_u8Number, 0));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN1, GET_BIT(Local_u8Number, 1));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN2, GET_BIT(Local_u8Number, 2));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN3, GET_BIT(Local_u8Number, 3));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN4, GET_BIT(Local_u8Number, 4));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN5, GET_BIT(Local_u8Number, 5));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN6, GET_BIT(Local_u8Number, 6));



			}else if(Copy_pConfig->SSD_u8LedA_Pin == DIO_u8PIN1){

				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN1, GET_BIT(Local_u8Number, 0));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN2, GET_BIT(Local_u8Number, 1));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN3, GET_BIT(Local_u8Number, 2));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN4, GET_BIT(Local_u8Number, 3));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN5, GET_BIT(Local_u8Number, 4));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN6, GET_BIT(Local_u8Number, 5));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN7, GET_BIT(Local_u8Number, 6));



			}else{

				Local_u8Error_State = NOK;
			}




		}else if(Copy_pConfig->SSD_u8Type == CATHOD || Copy_pConfig->SSD_u8Type == ETAKIT ){


			Local_u8Number = SSD_Arr[Copy_u8Number];

			if(Copy_pConfig->SSD_u8LedA_Pin == DIO_u8PIN0){

				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN0, GET_BIT(Local_u8Number, 0));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN1, GET_BIT(Local_u8Number, 1));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN2, GET_BIT(Local_u8Number, 2));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN3, GET_BIT(Local_u8Number, 3));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN4, GET_BIT(Local_u8Number, 4));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN5, GET_BIT(Local_u8Number, 5));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN6, GET_BIT(Local_u8Number, 6));



			}else if(Copy_pConfig->SSD_u8LedA_Pin == DIO_u8PIN1){

				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN1, GET_BIT(Local_u8Number, 0));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN2, GET_BIT(Local_u8Number, 1));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN3, GET_BIT(Local_u8Number, 2));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN4, GET_BIT(Local_u8Number, 3));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN5, GET_BIT(Local_u8Number, 4));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN6, GET_BIT(Local_u8Number, 5));
				DIO_u8SetPinValue(Copy_pConfig->SSD_u8LedPort, DIO_u8PIN7, GET_BIT(Local_u8Number, 6));


			}else{

				Local_u8Error_State = NOK;
			}


		}else{
			Local_u8Error_State = NOK;

		}

	}else{
		Local_u8Error_State = NULL_PTR_ERR;
	}



	return Local_u8Error_State;

}
