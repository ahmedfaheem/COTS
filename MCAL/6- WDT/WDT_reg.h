#ifndef WDT_REG_H
#define WDT_REG_H

#define WDTCR    *((volatile uint8*)0x41)  /*Watchdog Timer Control Register */

#define WDTCR_WDE    3u   /*Watchdog Enable*/


#define SREG   *((volatile uint8 *)0x5F)    /* Status Regeister */

#define SREG_I  7u                          /* Interrupt BIT*/

#endif
