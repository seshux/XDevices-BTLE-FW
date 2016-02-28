/*****************************************************************/
/*  XDevices Beacon firmware main                                 */
/*                                                               */
/* This is the main entry point for drivers initialization and   */
/* the OS scheduler to begin. This is not the direct entry       */
/* point for the core functionality of the beacon                */
/*****************************************************************/

/**************************************************************************************************
 *                                           Includes
 **************************************************************************************************/
/* Hal Drivers */
#include "hal_types.h"
#include "hal_key.h"
#include "hal_timer.h"
#include "hal_drivers.h"
#include "hal_led.h"

/* OSAL */
#include "OSAL.h"
#include "OSAL_Tasks.h"
#include "OSAL_PwrMgr.h"
#include "osal_snv.h"
#include "OnBoard.h"

/*APP*/
#include "PIR_Sensor.h"
/**************************************************************************************************
 * FUNCTIONS
 **************************************************************************************************/

/* This callback is triggered when a key is pressed */
void MSA_Main_KeyCallback(uint8 keys, uint8 state);

/**************************************************************************************************
 * @fn          main
 *
 * @brief       Start of application.
 *
 * @param       none
 *
 * @return      none
 **************************************************************************************************
 */
int main(void)
{
  
  HAL_BOARD_INIT();/* Initialize hardware.*/
  /* Includes functionality such as sleeping briefly until 32Mhz 
  crystal oscillator frequency is stabilized*/
 
  InitBoard( OB_COLD ); /* Initialize board I/O*/

  HalDriverInit();  /* Initialze the HAL driver */

  osal_snv_init(); /* Initialize Non Volatile Flash system(On-chip) */

  
  /* Initializing LL*/
  osal_init_system();/* Initialize the operating system */

  
  HAL_ENABLE_INTERRUPTS(); /* Enable interrupts */

  
  InitBoard( OB_READY ); /* Final board initialization */
  PIR_Init();
  #if defined ( POWER_SAVING )
    osal_pwrmgr_device( PWRMGR_BATTERY );
  #endif

  /* Start OSAL */
  osal_start_system(); // No Return from here

  return 0;
}

/**************************************************************************************************
                                           CALL-BACKS
**************************************************************************************************/


/*************************************************************************************************
**************************************************************************************************/
