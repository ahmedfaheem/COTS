#include "STD_TYPES.h"
#include "ADC_interface.h"
#include "VOLTAMETER_interface.h"
#include "VOLTAMETER_cfg.h"


uint16 VOLTAMETER_voidGetmVoltageReading(uint8 Copy_u8ADC_Channel){

	uint16 VoltmeterVal = 0;
	ADC_u8StartConversionSynch(Copy_u8ADC_Channel, &VoltmeterVal);
	VoltmeterVal = (VOLTAMETER_VREF * VoltmeterVal)/ 255UL;

	return VoltmeterVal;
}
