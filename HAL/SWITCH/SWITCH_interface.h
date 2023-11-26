#ifndef SWITCH_INTERFACE_H
#define SWITCH_INTERFACE_H


typedef enum{
	
	PULL_UP = 0u,
	PULL_DOWN = 1
}SW_Type_t;

/*
SWITCH_u8Type options:-

1- PULL_UP
2- PULL_DOWN

*/
typedef struct{
	
	SW_Type_t  SWITCH_u8Type;
	uint8      SWITCH_u8Port;
	uint8      SWITCH_u8Pin;
}SW_Config_t;


#define SW_PRESSED  0u
#define SW_RELEASES   1u

uint8 SWITCH_u8GetState(const SW_Config_t *Copy_pConfig, uint8 *SW_u8State);

#endif
