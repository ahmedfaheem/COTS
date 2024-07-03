#include "STD_TYPES.h"
#include "SOIL_interface.h"
#include "SOIL_cfg.h"
#include "SOIL_prv.h"



uint16 SOIL_u16GetMoisture(uint16 Copy_u16ADCVal){
	
	uint16 Local_u16Reading = 0;
	
#if  SOIL_ADC_MODE == SOIL_8BIT_MODE

Local_u16Reading  = 100UL - ((Copy_u16ADCVal * 100UL)/255UL);


#elif SOIL_ADC_MODE  == SOIL_10BIT_MODE

Local_u16Reading  = ((Copy_u16ADCVal * 100UL)/1023UL);

#else

#error   Erro on congfiguration

#endif 
	
	
	return Local_u16Reading;
	
}

