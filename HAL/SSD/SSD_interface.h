#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H

typedef enum{
	
	ANODE = 0u,
	CATHOD = 1u,
	ETAKIT = 2u
	
}SSD_Type_t;


/*
  SSD_u8Type Options:
  1- ANODE
  2- CATHOD
  3- ETAKIT
  
  SSD_u8LedA_Pin Options:
  1- DIO_u8PIN0
  2- DIO_u8PIN1
  
*/

typedef struct{
	
	SSD_Type_t  SSD_u8Type;
	uint8       SSD_u8LedPort;
	uint8       SSD_u8LedA_Pin;
	uint8       SSD_u8Enable_Port;
	uint8       SSD_u8Enable_Pin;
	
}SDD_Confg_t;


uint8 SSD_u8On(const SDD_Confg_t* Copy_pConfig);

uint8 SSD_u8Off(const SDD_Confg_t* Copy_pConfig);

uint8 SSD_u8SetNumber(const SDD_Confg_t* Copy_pConfig, uint8 Copy_u8Number);

#endif
