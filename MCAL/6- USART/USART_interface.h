#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

void USART_voidInit();

void USART_voidSendByte(uint8 Copy_u8Data);

uint8 USART_u8ReceiveByte(uint8 *Copy_pu8Data);

uint8 USART_u8SendString(uint8 *Copy_pu8Data);

/* Send # symbol at the end to end string */
uint8 USART_u8ReceiveString(uint8 *Copy_pu8Data);

void USART_u8SendNumber(uint32 Copy_u32Data);

uint8 USART_u8ReceiveNumber(uint32* Copy_pu32Data);

/*buffer is an Array*/
uint8 USART_u8SendBufferSynch(uint8 *Copy_pu8Data, uint8 Copy_u8Size);
uint8 USART_u8ReceiveBufferSynch(uint8 *Copy_pu8Data, uint8 Copy_u8Size);

uint8 USART_u8SendBufferASynch(uint8 *Copy_pu8Data, uint8 Copy_u8Size, void (*Copy_voidNotifyFunc)(void));
uint8 USART_u8ReceiveBufferASynch(uint8* Copy_pu8Data, uint8 Copy_u8Size, void (*Copy_voidNotifyFunc)(void));

#endif
