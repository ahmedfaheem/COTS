#ifndef EXTI_REG_H
#define EXTI_REG_H


#define GICR  *((volatile uint8* )0x5B)    /*General Interrupt Control Register, activate INT0, INT1, INT2 */

#define GICR_INT0    6u
#define GICR_INT1    7u
#define GICR_INT2    5u


#define MCUCR  *((volatile uint8* )0x55)   /*MCU Control Register ,Control sence of INT0, INT1 */
 
#define MCUCR_ISC00   0u                   /*INT0 Sense control bit0*/
#define MCUCR_ISC01   1u                   /*INT0 Sense control bit1*/
#define MCUCR_ISC10   2u                   /*INT1 Sense control bit0*/
#define MCUCR_ISC11   3u                   /*INT1 Sense control bit1*/


#define MCUCSR *((volatile uint8* )0x54)   /*MCU Control and Status Register, Control sence of INT2 */

#define MCUCSR_ISC2   6u                  /*INT2 Sense control bit0*/

#endif
