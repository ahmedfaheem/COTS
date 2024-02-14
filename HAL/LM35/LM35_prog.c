#include "STD_TYPES.h"
#include "ADC_interface.h"
#include "LM35_interface.h"
#include "LM35_cfg.h"
#include "LM35_prv.h"





uint8 LM34_u8GetTempInC(uint8 Copy_u8ADCChannel){



	 uint8 Local_u8TempVal= 0;

	uint16 Local_u8DigitalVal   = 0;

	ADC_u8StartConversionSynch(Copy_u8ADCChannel, &Local_u8DigitalVal);
   /* Anlaog = Digital  * Step
    * Step = Vref / 2^resolution  --> resolution 8
    * Temp = Analog / 10
    * */
	Local_u8TempVal =(uint8)((((uint32)Local_u8DigitalVal) * 500UL) / 256UL);


  return Local_u8TempVal;
}
