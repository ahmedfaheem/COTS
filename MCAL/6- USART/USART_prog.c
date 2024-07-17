#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"
#include "USART_interface.h"
#include "USART_reg.h"
#include "USART_cfg.h"
#include "USART_prv.h"

volatile static uint8  *USART_pu8GlobalData = NULL;
volatile static uint8  USART_u8GlobalDataSize = 0;
static void (*USART_pvGlobalFunc)(void) = NULL;
static uint8 BusyFlag = IDEL;
void USART_voidInit(){

	uint8 Local_u8UCSRCValue = 0u;


	/*  Select register to UCSRC */
	SET_BIT(Local_u8UCSRCValue, UCSRC_URSEL);

	/* Select Parity */
#if USART_PARITY_OPT == EVEN
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UPM0);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UPM1);
#elif USART_PARITY_OPT == ODD
	SET_BIT(Local_u8UCSRCValue, UCSRC_UPM0);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UPM1);
#elif USART_PARITY_OPT == NO_PARITY
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UPM0);
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UPM1);
#else #error Configuration Error
#endif
	/* Stop Bit Selection */
#if USART_STOP_BIT_OPT == ONE_BIT
	CLR_BIT(Local_u8UCSRCValue, UCSRC_USBS);
#elif USART_STOP_BIT_OPT == TWO_BIT
	SET_BIT(Local_u8UCSRCValue, UCSRC_USBS);
#else #error Configuration Error
#endif

#if USART_CHAR_SIZE == CHAR_5_BIT
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UCSZ0);
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UCSZ1);
#elif USART_CHAR_SIZE == CHAR_6_BIT
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ0);
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UCSZ1);
#elif USART_CHAR_SIZE == CHAR_7_BIT
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ1);
#elif USART_CHAR_SIZE == CHAR_8_BIT
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ1);
#else #error Configuration Error
#endif

	/*set USART Mode Select to Asynchronous*/
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);

	/*add final value to register (can not use set and clr because select reg must be on same operation)*/
	UCSRC = Local_u8UCSRCValue;

#if USART_BAUD_RATE == BAUD_2400
	uint16 Local_u6Baud = 416;
	UBRRL = Local_u6Baud;
	UBRRH = UBRRH & 0xF0; /* Mask least bit */
	UBRRH = UBRRH | Local_u6Baud>>8;
#elif USART_BAUD_RATE == BAUD_4800
	UBRRH = UBRRH & 0xF0; /* Mask least bit */
	UBRRL = 207;
#elif USART_BAUD_RATE == BAUD_9600
	UBRRH = UBRRH & 0xF0; /* Mask least bit */
	UBRRL  = 103;
#elif USART_BAUD_RATE == BAUD_14400
	UBRRH = UBRRH & 0xF0; /* Mask least bit */
	UBRRL = 68;
#elif USART_BAUD_RATE == BAUD_19200
	UBRRH = UBRRH & 0xF0; /* Mask least bit */
	UBRRL = 51;
#else #error Configuration Error
#endif


	/*Enable transmit and receiver */
	SET_BIT(UCSRB, UCSRB_TXEN);
	SET_BIT(UCSRB, UCSRB_RXEN);

}

void USART_voidSendByte(uint8 Copy_u8Data){

	/* wait until UDRE is empty */
	while(GET_BIT(UCSRA,UCSRA_UDRE) == 0);

	UDR = Copy_u8Data;
}

uint8 USART_u8ReceiveByte(uint8 *Copy_pu8Data){

	uint8 Local_u8ErrState= OK;
	if( Copy_pu8Data != NULL){
		/* wait until the data received */
		while(GET_BIT(UCSRA,UCSRA_RXC) == 0);
		*Copy_pu8Data = UDR;
	}else{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;

}

uint8 USART_u8SendString(uint8 *Copy_pu8Data){

	uint8 Local_u8ErrState= OK;
	if( Copy_pu8Data != NULL){

		while(*Copy_pu8Data != '\0'){
			USART_voidSendByte(*Copy_pu8Data);
			Copy_pu8Data++;

		}
	}else{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;

}


uint8 USART_u8ReceiveString(uint8 *Copy_pu8Data){
	uint8 Local_u8ErrState = OK;
	if(Copy_pu8Data != NULL){
		uint8 i = 0;

	 USART_u8ReceiveByte(&Copy_pu8Data[i]);
	 while(Copy_pu8Data[i] != '#'){
		 i++;
		 USART_u8ReceiveByte(&Copy_pu8Data[i]);
	 }
	 Copy_pu8Data[i] = '\0';
	}else{
		Local_u8ErrState = NULL_PTR_ERR;
	}
	return Local_u8ErrState;
}

void USART_u8SendNumber(uint32 Copy_u32Data){

	USART_voidSendByte((uint8)Copy_u32Data);
	USART_voidSendByte((uint8)(Copy_u32Data>>8));
	USART_voidSendByte((uint8)(Copy_u32Data>>16));
	USART_voidSendByte((uint8)(Copy_u32Data>>24));

}

uint8 USART_u8ReceiveNumber(uint32 *Copy_pu32Data){
	uint8 Local_u8ErrState = OK;
	if(Copy_pu32Data != NULL){
	uint8 b1,b2,b3,b4;
	USART_u8ReceiveByte(&b1);
	USART_u8ReceiveByte(&b2);
	USART_u8ReceiveByte(&b3);
	USART_u8ReceiveByte(&b4);
	*Copy_pu32Data = b1|(b2<<8)|((uint32)b3<<16)|((uint32)b4<<24);
	}else{
		Local_u8ErrState = NULL_PTR_ERR;
	}
	return Local_u8ErrState;
}





uint8 USART_u8SendBufferSynch(uint8 *Copy_pu8Data, uint8 Copy_u8Size){
	uint8 Local_u8ErrState= OK;

	if(Copy_pu8Data != NULL){
		uint8 Local_u8Counter = 0;
		for(Local_u8Counter = 0;Local_u8Counter<Copy_u8Size;Local_u8Counter++){
			USART_voidSendByte(Copy_pu8Data[Local_u8Counter]);
		}

	}else{
		Local_u8ErrState = NULL_PTR_ERR;
	}


	return Local_u8ErrState;
}

uint8 USART_u8ReceiveBufferSynch(uint8 *Copy_pu8Data, uint8 Copy_u8Size){
	uint8 Local_u8ErrState= OK;

	if(Copy_pu8Data != NULL){
		uint8 Local_u8Counter = 0;
		for(Local_u8Counter = 0;Local_u8Counter<Copy_u8Size;Local_u8Counter++){
			USART_u8ReceiveByte(Copy_pu8Data+ Local_u8Counter);
		}

	}else{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;

}

uint8 USART_u8SendBufferASynch(uint8 *Copy_pu8Data, uint8 Copy_u8Size, void (*Copy_voidNotifyFunc)(void)){
	uint8 Local_u8ErrState= OK;

	if(Copy_pu8Data != NULL && Copy_voidNotifyFunc != NULL){
		if(BusyFlag == IDEL){
			SET_BIT(UCSRB, UCSRB_TXCIE);
			USART_pvGlobalFunc = Copy_voidNotifyFunc;
			USART_u8SendBufferSynch(Copy_pu8Data, Copy_u8Size);


		}else{
			Local_u8ErrState = BUSY_ERR;
		}
	}else{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;



}


uint8 USART_u8ReceiveBufferASynch(uint8 *Copy_pu8Data, uint8 Copy_u8Size, void (*Copy_voidNotifyFunc)(void)){
	uint8 Local_u8ErrState= OK;

	if(Copy_pu8Data != NULL && Copy_voidNotifyFunc != NULL){
		if(BusyFlag == IDEL){
			SET_BIT(UCSRB, UCSRB_RXCIE);
			USART_pu8GlobalData = Copy_pu8Data;
			USART_pvGlobalFunc = Copy_voidNotifyFunc;
			USART_u8GlobalDataSize = Copy_u8Size;
		}else{
			Local_u8ErrState = BUSY_ERR;
		}

	}else{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;



}


/* Interrupt When UDR is Empty*/
__attribute__((signal)) void __vector_15(void);

void __vector_15(void){


	if( USART_pvGlobalFunc != NULL){
		CLR_BIT(UCSRB, UCSRB_TXCIE);
		USART_pvGlobalFunc();
		BusyFlag = IDEL;
	}

}



/*Interrupt When Data Received  */
__attribute__((signal)) void __vector_13(void);

void __vector_13(void){


	if(USART_pu8GlobalData != NULL && USART_pvGlobalFunc != NULL){
		USART_u8ReceiveBufferSynch(USART_pu8GlobalData, USART_u8GlobalDataSize);
		CLR_BIT(UCSRB, UCSRB_RXCIE);
		USART_pvGlobalFunc();
		BusyFlag = IDEL;
	}

}


