#include "STD_TYPES.h"
#include "ADC_interface.h"
#include "OHM_interface.h"
#include "OHM_cfg.h"


uint16 OHM_voidGetmOhmReading(uint8 Copy_u8ADC_Channel){

	uint16 VoltmeterVal = 0, OhmVal = 0;
	ADC_u8StartConversionSynch(Copy_u8ADC_Channel, &VoltmeterVal);
	VoltmeterVal = (VOLTAMETER_VREF * VoltmeterVal)/ 255UL;
	OhmVal = (R_KNOWN * (VOLTAMETER_VREF - VoltmeterVal)) / VoltmeterVal;

	return OhmVal;
}
