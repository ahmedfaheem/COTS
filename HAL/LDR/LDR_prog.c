#include "STD_TYPES.h"
#include "ADC_interface.h"
#include "LDR_interface.h"
#include "LDR_cfg.h"





uint8 LDR_u8GetLightLevel(uint8 Copy_u8ADC_Channel, uint8 Copy_u8NumberOfLevel){

	uint8 Local_u8StepLevel  = 0, Local_u8LightLevel = 0;
	uint16 Local_u8DigitalVal = 0;

	Local_u8StepLevel = LDR_u8MAXREAD / Copy_u8NumberOfLevel;

    ADC_u8StartConversionSynch(Copy_u8ADC_Channel, &Local_u8DigitalVal);

    Local_u8LightLevel = ((uint8)Local_u8DigitalVal) / Local_u8StepLevel;

	return Local_u8LightLevel;
}
