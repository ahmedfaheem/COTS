#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

#define CLCD_u8CLEAR_LCD   0b00000001

void CLCD_voidSendCmd(uint8 Copy_u8Cmd);
void CLCD_voidSendData(uint8 Copy_u8Data);

void CLCD_voidInit(void); 

uint8 CLCD_u8SendString(const char *Copy_pcharString);
void CLCD_u8SendNumber(sint32 Copy_s32Number);
void CLCD_voidGoToXY(uint8 Copy_u8XPos, uint8 Copy_u8YPos);

uint8 CLCD_u8SendSpecialCharacter(uint8 Copy_u8LocationNum, uint8 *Copy_pu8Pattern, uint8 Copy_u8XPos, uint8 Copy_u8YPos);

#endif
