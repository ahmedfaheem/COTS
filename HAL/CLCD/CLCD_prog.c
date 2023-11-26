#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "ErrType.h"
#include "DIO_interface.h"


#include "CLCD_interface.h"
#include "CLCD_cfg.h"
#include "CLCD_prv.h"

#if CLCD_u8BIT_MODE == FOUR_BIT

static void voidSetHalfDataPort(uint8 Copy_u8Data){


	DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D4, GET_BIT(Copy_u8Data, 0));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D5, GET_BIT(Copy_u8Data, 1));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D6, GET_BIT(Copy_u8Data, 2));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D7, GET_BIT(Copy_u8Data, 3));

}


#endif

static void voidSendEnablePulse(void){

	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8E_PIN, DIO_u8PIN_LOW);
}

void CLCD_voidSendCmd(uint8 Copy_u8Cmd){

	/* Set RS pin to Low for command */
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_u8PIN_LOW);


#if CLCD_u8RW_CONN_STS == DIO_CONNECTED

	/*Set RW pin to low for writing */

	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_u8PIN_LOW); /*on our kit connected to ground*/
#endif

	/* Send Command */
#if CLCD_u8BIT_MODE == FOUR_BIT
	/* Send the 4 most significant bit of the command */
	voidSetHalfDataPort(Copy_u8Cmd>>4);
	voidSendEnablePulse();
	/* Send the 4 least significant bit of the command */
	voidSetHalfDataPort(Copy_u8Cmd);
	voidSendEnablePulse();


#elif CLCD_u8BIT_MODE == EIGHT_BIT
	DIO_u8SetPortValue(CLCD_u8DATA_PORT, Copy_u8Cmd);
	voidSendEnablePulse();

#else
#error Wrong CLCD_u8BIT_MODE Configuration
#endif

}

void CLCD_voidSendData(uint8 Copy_u8Data){

	/* Set RS pin to Low for Data */

	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_u8PIN_HIGH);

#if CLCD_u8RW_CONN_STS == DIO_CONNECTED

	/*Set RW pin to low for writing */

	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_u8PIN_LOW);
#endif

	/* Send Data */
#if CLCD_u8BIT_MODE == FOUR_BIT
	/* Send the 4 most significant bit of the command */
	voidSetHalfDataPort(Copy_u8Data>>4);
	voidSendEnablePulse();
	/* Send the 4 least significant bit of the command */
	voidSetHalfDataPort(Copy_u8Data);
	voidSendEnablePulse();


#elif CLCD_u8BIT_MODE == EIGHT_BIT
	DIO_u8SetPortValue(CLCD_u8DATA_PORT, Copy_u8Data);
	voidSendEnablePulse();

#else
#error Wrong CLCD_u8BIT_MODE Configuration
#endif


}


void CLCD_voidInit(void){

	/*RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0 */
	/* Wait for more than 40ms after VDD rises to 4.5V. after power on */

	_delay_ms(40);

#if CLCD_u8BIT_MODE == EIGHT_BIT


	/* function Set Command: 2 line, font size: 5 x 7 */
	/*0 0 0 0 1 1 N F X X */
	CLCD_voidSendCmd(0b00111000);



#elif CLCD_u8BIT_MODE == FOUR_BIT

	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b1000);
	voidSendEnablePulse();


#endif

	/*Display on off control : Display on, cursor off, blink cursor off*/
	CLCD_voidSendCmd(0b00001100);

	/*Clear display*/
	CLCD_voidSendCmd(1);

}


uint8 CLCD_u8SendString(const char *Copy_pcharString){

	uint8 Local_u8ErrState = OK;
	uint8 Copy_u8Counter = 0u;
	if(Copy_pcharString != NULL){

		while(Copy_pcharString[Copy_u8Counter] != NULL){

			CLCD_voidSendData(Copy_pcharString[Copy_u8Counter++]);
		}


	}else{


		Local_u8ErrState = NULL_PTR_ERR;
	}


	return Local_u8ErrState;
}


void CLCD_u8SendNumber(sint32 Copy_s32Number){


	uint8  Local_u8NumberOfDigits = 0u;
	uint8 Local_u32Digits;
	uint32 Local_u32OriginalNumber;
	uint32 Local_u32Divider = 1u;
	uint8 Copy_u8Counter = 0u;

	if(Copy_s32Number == 0){
		CLCD_voidSendData('0');
	}else{

		if(Copy_s32Number < 0){
			CLCD_voidSendData('-');
			Copy_s32Number*=-1;
		}

		Local_u32OriginalNumber = Copy_s32Number;
		/*get number of digits */
		while(Local_u32OriginalNumber> 0){
			Local_u8NumberOfDigits++;
			Local_u32OriginalNumber/=10;
		}

		/*get 10 multiplied number of digits */
		for(Copy_u8Counter = 0;Copy_u8Counter <Local_u8NumberOfDigits-1;Copy_u8Counter++){
			Local_u32Divider*=10;
		}
		Local_u32OriginalNumber = Copy_s32Number;

		/*get digits form first, divide by Local_u32Divider, and Local_u32Divider/10 on each step */
		while(Local_u32Divider > 0){
			/*48 is Ascci of zero*/
			Local_u32Digits =  (Local_u32OriginalNumber/Local_u32Divider)+48;
			CLCD_voidSendData(Local_u32Digits);
			Local_u32OriginalNumber%=Local_u32Divider;
			Local_u32Divider/=10;

		}

	}
}

void CLCD_voidGoToXY(uint8 Copy_u8XPos, uint8 Copy_u8YPos){

	uint8 Local_u8Adress;
	if(Copy_u8YPos == 0u){

		Local_u8Adress = Copy_u8XPos;
	}else if(Copy_u8YPos == 1u){

		Local_u8Adress = 0x40 + Copy_u8XPos;

	}
	/* 		Local_u8Adress = 0x40 * Copy_u8YPos  + Copy_u8XPos; */

	/*Set bit 7 for SetDDRAM Address command (on CLCD memory) */
	SET_BIT(Local_u8Adress, 7);

	/*Execute Set DDRAM Address command (on CLCD memory)*/
	CLCD_voidSendCmd(Local_u8Adress);

}


uint8 CLCD_u8SendSpecialCharacter(uint8 Copy_u8LocationNum, uint8 *Copy_pu8Pattern, uint8 Copy_u8XPos, uint8 Copy_u8YPos){

	uint8 Local_u8ErrorState = OK;

	if(Copy_pu8Pattern != NULL){

		uint8 Local_u8LocationAddress = Copy_u8LocationNum * 8;
		uint8 Local_u8Counter;
		/*Set Bit 6 on CGRAM */
		SET_BIT(Local_u8LocationAddress, 6);

		/* Set CGRAM address in address counter.   */
		CLCD_voidSendCmd(Local_u8LocationAddress);

		/* Write data into internal CGRAM). */

		for(Local_u8Counter = 0; Local_u8Counter < 8u;Local_u8Counter++){
			CLCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);  /* Send byte by byte to location */
		}


		/* Set DDRAM address in address counter to display pattern   */

		CLCD_voidGoToXY(Copy_u8XPos, Copy_u8YPos);

		/* * Display the special pattern inside CGRAM
           * send location of pattern, 0 - 7 */

		CLCD_voidSendData(Copy_u8LocationNum);


	}else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}


	return Local_u8ErrorState;
}
