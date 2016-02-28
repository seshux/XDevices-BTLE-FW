#ifndef PIRSENSOR_H
#define PIRSENSOR_H

#include "hal_types.h"

#define PIR_MOTION_IN         0x01
#define PIR_MOTION_OUT        0x02
#define PIR_MOTION_DETECTED   0xDE

#define PIR_CONN_PIN_IEN      IEN0  /* CPU interrupt mask register */
#define PIR_CONN_PIN_ICTL     P0IEN /* Port Interrupt Control register */
#define PIR_CONN_PIN_ICTLBIT  (1<<5) /* P0IEN - P0.5 enable/disable bit */
#define PIR_CONN_PIN_IENBIT   (1<<5) /* Mask bit for all of Port_1 */
#define PIR_CONN_PIN_PXIFG    P0IFG /* Interrupt flag at source */

#define PIR_CONN_PIN_PORT     P0
#define PIR_CONN_PIN_BIT      BV(5)
#define PIR_CONN_PIN_SEL      P0SEL
#define PIR_CONN_PIN_DIR      P0DIR

#define PIR_INTR_PORT         P0
#define PIR_INTR_BIT          BV(5)

#define NO_TASK_ID             0xFF

void PIR_Init();
uint8 PIR_SendMessage( uint8 state, uint8 motionDetect);
uint8 RegisterForPIRSensor( uint8 task_id );

#endif