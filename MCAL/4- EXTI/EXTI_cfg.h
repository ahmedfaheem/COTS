#ifndef EXTI_CFG_H
#define EXTI_CFG_H


/* Configure the initial Sense CTRL option for INT0 Channel, Options:
 *                                                                   1- EXTI_LOW_LEVEL
 *                                                                   2- EXTI_RISING_EDGE
 *                                                                   3- EXTI_FALLING_EDGE
 *                                                                   4- EXTI_ON_CHANE
 * */

#define INT0_SENSE_CTRL           EXTI_FALLING_EDGE


/* Configure the initial Sense CTRL option for INT1 Channel, Options:
 *                                                                   1- EXTI_LOW_LEVEL
 *                                                                   2- EXTI_RISING_EDGE
 *                                                                   3- EXTI_FALLING_EDGE
 *                                                                   4- EXTI_ON_CHANE
 * */

#define INT1_SENSE_CTRL           EXTI_FALLING_EDGE



/* Configure the initial Sense CTRL option for INT2 Channel, Options:
 *                                                                   1- EXTI_RISING_EDGE
 *                                                                   2- EXTI_FALLING_EDGE
 * */

#define INT2_SENSE_CTRL           EXTI_FALLING_EDGE



/* Configure the initial State  of INT0 Channel, Options:
 *                                                      1- ENABLED
 *                                                      2- DISABLED
 */


#define INT0_INIT_STATE                ENABLED


/* Configure the initial State  of INT1 Channel, Options:
 *                                                      1- ENABLED
 *                                                      2- DISABLED
 */


#define INT1_INIT_STATE                ENABLED


/* Configure the initial State  of INT2 Channel, Options:
 *                                                      1- ENABLED
 *                                                      2- DISABLED
 */


#define INT2_INIT_STATE                ENABLED
#endif
