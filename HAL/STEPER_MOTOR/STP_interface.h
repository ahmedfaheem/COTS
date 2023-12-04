#ifndef STP_INTERFACE_H
#define STP_INTERFACE_H


typedef struct{
	
	uint8 STP_Port;
	uint8 STP_W_Blue;   /* STP Wire Blue Pin*/
	uint8 STP_W_Pink;
	uint8 STP_W_Yellow;
	uint8 STP_W_Orange;

	
}STP_Confg_t;

#define STP_ROTATE_CW   0

#define STP_ROTATE_CCW   1

/*

** Direction **

1- STP_ROTATE_CW
2- STP_ROTATE_CCW

** Angle  **

0 TO 360 only

*/

uint8 STP_u8Rotate(const STP_Confg_t *Copy_psConfg, uint8 Copy_u8Direction , uint16 Copy_uint16Angle);

#endif
