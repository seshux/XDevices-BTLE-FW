/**********************************************************************/
/*                                                                    */
/**********************************************************************/


#include "PIR_Sensor.h"
#include "osal.h"

#include <ioCC2541.h>
#include "ioCC254x_bitdef.h"
#include "hal_mcu.h"

/* Schematic Notes                                                    */
/* The P0_0 is connected to a tactile switch on CC2541 TI Keyfob board*/
/* The P0_5 is used as SCK signal for debug. This can be accessed via */
/* the 6th pin of STL21 conenctor named DEBUG on the Keyfob board     */

/* In the XDEVICES dual-battery beacon board, the P0_0 is BATT_LVL_P0_0  */
/* on the netlist. (The source of this net is not found in the schematic*/
/* 060403_Sch.pdf .                                                     */
/* The port P0_5 is connected to inverted PIR signal via the transistor */
/* Q1. When the hand is pulled out from the dispenser beacon, P0_5 goes */
/* briefly low then goes high                                           */
/* So the ISR should handle the high-to-low transition                  */

#define PIR_CONN_PIN    P0_5

uint8 msg;



//static void (*fpPIRSensorCallBack) () = 0;

/*Initialize inteerupts for the PIR sensor                       */
/*The I/O port P0_5 is used for detection                        */
/*In the normal condition the P0_5 is pulled high to VDD         */
/*via a 10K resistor. When motion occurs the Q1 transistor       */
/*is turned on and P0_5 goes low                                 */

/*PIR is activated not when the hand enters the field but        */
/*when it leaves the field. The 6th pin of AS083 stays normally  */
/*at 0 volts. In the event of detection, it briefly goes anywhere*/
/*from 300mV to 1.5V than back to 0V.                            */


typedef struct
{
  osal_event_hdr_t hdr;
  uint8             state;           // shift- in-to-out OR out-to-in
  uint8             motionDetected;  // End state. Usually the PIR interrupt happens on removal
} pirActivity_t;

static uint8 registeredPIRSensorTaskID = NO_TASK_ID;


uint8 RegisterForPIRSensor( uint8 task_id )
{
  // Allow only the first task
  if ( registeredPIRSensorTaskID == NO_TASK_ID )
  {
    registeredPIRSensorTaskID = task_id;
    return ( true );
  }
  else
    return ( false );
}

void PIR_Init()
{  
  PIR_CONN_PIN_ICTL |= PIR_CONN_PIN_ICTLBIT; /* enable interrupt generation at port */
  PIR_CONN_PIN_IEN  |= PIR_CONN_PIN_IENBIT;   /* enable CPU interrupt */
  PIR_CONN_PIN_PXIFG = (uint8)(~(PIR_CONN_PIN_BIT));  /* Clear any pending interrupt */
    
  PICTL &= 0x02; /*PICTL_P0ICONH*/  // low nibble, Falling edge gives interrupt
}

#if defined (XDEVICES_BEACON_DISPENSER)
HAL_ISR_FUNCTION(p0isr, P0INT_VECTOR)
{
  
  HAL_ENTER_ISR();
  if (PIR_CONN_PIN_PXIFG & PIR_CONN_PIN_BIT) 
  {
       PIR_CONN_PIN_PXIFG = (uint8)(~(PIR_CONN_PIN_BIT)); /* Clear Interrupt Flag */
       PIR_SendMessage(PIR_MOTION_OUT, PIR_MOTION_DETECTED);
  }
  PIR_CONN_PIN_PXIFG = 0;
  P0IF = 0;
  HAL_EXIT_ISR();
}
#endif

uint8 PIR_SendMessage( uint8 state, uint8 motionDetect)
{
  pirActivity_t *msgPtr; 
  /*This structure also includes the 2 byte header. 
  This is how it works. To push other type of messages, look into the OSAL specs*/
  
  if ( registeredPIRSensorTaskID != NO_TASK_ID )
  {
    msg = (uint8)PIR_MOTION_DETECTED;
    // Send the address to the task
    msgPtr = (pirActivity_t *)osal_msg_allocate( sizeof(pirActivity_t) );
    if ( msgPtr )
    {
      msgPtr->hdr.event = PIR_MOTION_DETECTED;
      msgPtr->state = state;
      msgPtr->motionDetected = motionDetect;

      msg = osal_msg_send( registeredPIRSensorTaskID, (uint8 *)msgPtr );
    }
    return ( SUCCESS );
  }
  else
    return ( FAILURE );
}

//void processPIRSensorInterrupt (void)
//{
//   if( HAL_KEY_SW_1_PXIFG & HAL_KEY_SW_1_BIT) /* Interrupt Flag has been set by SW1 */
//  {
//    HAL_KEY_SW_1_PXIFG = ~(HAL_KEY_SW_1_BIT); /* Clear Interrupt Flag */
//    valid = TRUE;
//  }
//}
//
//uint8 PIRSensorRead(void)
//{
//    uint8 pirDetected = 0;
//  if (!(HAL_KEY_SW_1_PORT & HAL_KEY_SW_1_BIT))    /* PIR_Inv input is active low */
//  {
//    pirDetected |= HAL_KEY_SW_1;
//  }
//}
