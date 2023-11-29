#include "STD_TYPES.h"
#include "MOTOR_interface.h"
#include "DIO_interface.h"




void  MOTOR_vRotateCW(const MOTOR_Confg_t* Copy_spMOTOR_cfg){

	DIO_u8SetPinValue(Copy_spMOTOR_cfg->MOTOR_u8Port,Copy_spMOTOR_cfg->MOTOR_u8Pin2,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(Copy_spMOTOR_cfg->MOTOR_u8Port,Copy_spMOTOR_cfg->MOTOR_u8Pin1,DIO_u8PIN_HIGH);


}
void  MOTOR_vRotateCCW(const MOTOR_Confg_t* Copy_spMOTOR_cfg){

	DIO_u8SetPinValue(Copy_spMOTOR_cfg->MOTOR_u8Port,Copy_spMOTOR_cfg->MOTOR_u8Pin1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(Copy_spMOTOR_cfg->MOTOR_u8Port,Copy_spMOTOR_cfg->MOTOR_u8Pin2,DIO_u8PIN_HIGH);

}
void  MOTOR_vStop(const MOTOR_Confg_t* Copy_spMOTOR_cfg){

	DIO_u8SetPinValue(Copy_spMOTOR_cfg->MOTOR_u8Port,Copy_spMOTOR_cfg->MOTOR_u8Pin1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(Copy_spMOTOR_cfg->MOTOR_u8Port,Copy_spMOTOR_cfg->MOTOR_u8Pin2,DIO_u8PIN_LOW);


}
