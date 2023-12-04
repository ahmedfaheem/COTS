#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "STP_interface.h"
#include "ErrType.h"
#include <util/delay.h>

#define MAX_ANGLE  360
#define MIN_ANGLE  0

uint8 STP_u8Rotate(const STP_Confg_t *Copy_psConfg, uint8 Copy_u8Direction , uint16 Copy_uint16Angle){

	uint8 Local_u8ErrState = OK;
	if(Copy_psConfg != NULL && Copy_uint16Angle <= MAX_ANGLE && Copy_uint16Angle >= MIN_ANGLE){
		/*

                                     2048steps   ------> 360deg

                                   ?Local_u8Steps       Copy_uint16Angle

		 */
		uint16 Local_u8Steps = (uint16) ( ((uint32)Copy_uint16Angle) * ((uint32)2048) / ((uint32)360 ));
		uint16  Local_u8LoopCounter = 0;

		/* Deactivate BLue, PINK, Yellow, Orange*/
		DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Blue, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Pink, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Yellow, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Orange, DIO_u8PIN_HIGH);

		if(Copy_u8Direction == STP_ROTATE_CW){

			for(Local_u8LoopCounter = 0;Local_u8LoopCounter<Local_u8Steps;Local_u8LoopCounter++){

				if(Local_u8LoopCounter % 4 == 0){

					/* Activate Orange*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Orange, DIO_u8PIN_LOW);

					/* Deactivate Blue, Pink, Yellow*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Blue, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Pink, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Yellow, DIO_u8PIN_HIGH);

					_delay_ms(6);


				}else if(Local_u8LoopCounter % 4 == 1){

					/* Activate Yellow*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Yellow, DIO_u8PIN_LOW);

					/* Deactivate Blue, Pink, Orange*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Blue, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Pink, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Orange, DIO_u8PIN_HIGH);

					_delay_ms(6);

				}else if(Local_u8LoopCounter % 4 == 2){

					/* Activate Pink*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Pink, DIO_u8PIN_LOW);

					/* Deactivate Blue, Yellow, Orange*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Blue, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Yellow, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Orange, DIO_u8PIN_HIGH);

					_delay_ms(6);


				}else if(Local_u8LoopCounter % 4 == 3){

					/* Activate Blue*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Blue, DIO_u8PIN_LOW);

					/* Deactivate PINK, Yellow, Orange*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Pink, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Yellow, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Orange, DIO_u8PIN_HIGH);

					_delay_ms(6);

				}

			}




		}else if(Copy_u8Direction == STP_ROTATE_CCW){

			for(Local_u8LoopCounter = 0;Local_u8LoopCounter<Local_u8Steps;Local_u8LoopCounter++){

				if(Local_u8LoopCounter % 4 == 0){


					/* Activate Blue*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Blue, DIO_u8PIN_LOW);

					/* Deactivate PINK, Yellow, Orange*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Pink, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Yellow, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Orange, DIO_u8PIN_HIGH);

					_delay_ms(4);


				}else if(Local_u8LoopCounter % 4 == 1){

					/* Activate Pink*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Pink, DIO_u8PIN_LOW);

					/* Deactivate Blue, Yellow, Orange*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Blue, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Yellow, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Orange, DIO_u8PIN_HIGH);

					_delay_ms(4);

				}else if(Local_u8LoopCounter % 4 == 2){

					/* Activate Yellow*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Yellow, DIO_u8PIN_LOW);

					/* Deactivate Blue, Pink, Orange*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Blue, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Pink, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Orange, DIO_u8PIN_HIGH);

					_delay_ms(4);


				}else if(Local_u8LoopCounter % 4 == 3){


					/* Activate Orange*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Orange, DIO_u8PIN_LOW);

					/* Deactivate Blue, Pink, Yellow*/
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Blue, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Pink, DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_psConfg->STP_Port, Copy_psConfg->STP_W_Yellow, DIO_u8PIN_HIGH);

					_delay_ms(4);

				}
			}
		}else{
			Local_u8ErrState = NOK;

		}



	}else{

		Local_u8ErrState = NULL_PTR_ERR;
	}


	return Local_u8ErrState;
}
