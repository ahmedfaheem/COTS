#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H

typedef struct{

    uint8 MOTOR_u8Port;
	uint8 MOTOR_u8Pin1;
	uint8 MOTOR_u8Pin2;
	
}MOTOR_Confg_t;




void  MOTOR_vRotateCW(const MOTOR_Confg_t* Copy_spMOTOR_cfg);
void  MOTOR_vRotateCCW(const MOTOR_Confg_t* Copy_spMOTOR_cfg);
void  MOTOR_vStop(const MOTOR_Confg_t* Copy_spMOTOR_cfg);



#endif
