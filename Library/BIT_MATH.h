#ifndef BIT_MATH_H  // file guard to prevent code repetion
#define BIT_MATH_H


#define SET_BIT(VAR, BIT_NUM)  (VAR) = (VAR) | ( 1U <<(BIT_NUM) )

#define CLR_BIT(VAR, BIT_NUM)  (VAR) = (VAR) & ( ~(1U <<(BIT_NUM)) )

#define TOG_BIT(VAR, BIT_NUM)  (VAR) = (VAR) ^ ( 1U<<(BIT_NUM) )

#define GET_BIT(VAR, BIT_NUM)  (( (VAR)>>(BIT_NUM) ) & (1U))


#endif
