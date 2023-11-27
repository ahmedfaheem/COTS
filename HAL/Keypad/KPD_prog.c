#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "ErrType.h"

#include "KPD_interface.h"
#include "KPD_prv.h"
#include "KPD_cfg.h"


uint8 KPD_u8GetPressedKey(void){
	
	uint8 Local_u8ColIdx, Local_u8RowIdx, Local_u8PinState, Local_u8PressedKey = KPD_u8NO_PRESSED_KEY_VAL;
	uint8 Locla_au8Button_Arr[ROW_NUM][COL_NUM] = KPD_au8_BUTTON_ARR;

    uint8  Locla_au8ColArr[COL_NUM] = {KPD_u8COL0_PIN,KPD_u8COL1_PIN,KPD_u8COL2_PIN,KPD_u8COL3_PIN};

    uint8  Locla_au8RowArr[ROW_NUM] = {KPD_u8ROW0_PIN,KPD_u8ROW1_PIN,KPD_u8ROW2_PIN,KPD_u8ROW3_PIN};


	/* Activate Columns Pin */
	for(Local_u8ColIdx = 0u; Local_u8ColIdx < COL_NUM; Local_u8ColIdx++){

		/*Activate Current Column*/

        DIO_u8SetPinValue(KPD_u8COLPORT, Locla_au8ColArr[Local_u8ColIdx], DIO_u8PIN_LOW);


        /*Read Rows Pin*/

    	for(Local_u8RowIdx = 0u; Local_u8RowIdx < ROW_NUM; Local_u8RowIdx++){

    		/*Read the current Row Pins*/
         DIO_u8ReadPinValue(KPD_u8ROWPORT,Locla_au8RowArr[Local_u8RowIdx], &Local_u8PinState);

         if(Local_u8PinState == DIO_u8PIN_LOW){
        	 Local_u8PressedKey = Locla_au8Button_Arr[Local_u8RowIdx][Local_u8ColIdx];


        	 /* Polling with Blocking(Waiting) until button released*/
        	 while(Local_u8PinState == DIO_u8PIN_LOW){
                 DIO_u8ReadPinValue(KPD_u8ROWPORT,Locla_au8RowArr[Local_u8RowIdx], &Local_u8PinState);
        	 }

        	 return Local_u8PressedKey;
         }

    	}

    	/* Deactivate Column Pins*/
        DIO_u8SetPinValue(KPD_u8COLPORT, Locla_au8ColArr[Local_u8ColIdx], DIO_u8PIN_HIGH);

	}




	return Local_u8PressedKey;

}
