#include "STD_TYPES.h"
#include "MAP_interface.h"


sint32 MAP(sint32 Copy_s32InputRangeMin, sint32 Copy_s32InputRangeMax, sint32 Copy_s32OutputRangeMin, sint32 Copy_s32OutputRangeMax, sint32 Copy_s32Result ){

	 sint32 Local_s32Result = 0;

	 Local_s32Result = (((Copy_s32OutputRangeMax - Copy_s32OutputRangeMin)
			            *(Copy_s32Result - Copy_s32InputRangeMin))/(Copy_s32InputRangeMax- Copy_s32InputRangeMin) )
			            + Copy_s32OutputRangeMin;


return Local_s32Result;

}

