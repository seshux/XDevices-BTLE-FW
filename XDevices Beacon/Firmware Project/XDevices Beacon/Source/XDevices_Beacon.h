

#ifndef XDEVICESBEACON_H
#define XDEVICESBEACON_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * CONSTANTS
 */
#define ID_LEN                     8
#define XDEVICES_BEACON_DEFAULT_ID  0x00

#define BEACON_CONFBYTE_DISP_ROOM  0x00
#define BEACON_CONFBYTE_DISP_HALL  0x01
#define BEACON_CONFBYTE_LOC_ROOM   0x10
#define BEACON_CONFBYTE_LOC_HALL   0x11

#define CONFIG_MASK_BYTE_DEFAULT   0x3F  /* xx11 1111 */
#define CONFIG_MASK_BYTE_CUSTOM    0x00  /* You can change and use this */
#define XDEVICES_BEACON_ID_LASTBYTE BEACON_CONFBYTE_LOC_HALL | CONFIG_MASK_BYTE_CUSTOM
#define XDEVICES_BEACON_ID          'X','D','E','V','I','C','E',XDEVICES_BEACON_ID_LASTBYTE
  
/* These are multi-line Macros. Be careful when modifying. */
/* The data is only used for a variable. But if you want to*/
/* use it for an IF ELSE comparison etc, make sure to make */
/* relevant modifications to avoid compilation errors      */

  /*Start with these macros and you can change those bytes with a variable*/

  /*LOCATION type beacon in ROOM. 16-to-19th bytes are room number*/

#define XDV_BEACON_ROOM_LOC_SCAN_RESPONSE \
  { \
  0x14,   \
  GAP_ADTYPE_LOCAL_NAME_COMPLETE, \
  0x48,   \
  0x59,   \
  0x47,   \
  0x49,   \
  0x4E,   \
  0x45,   \
  0x58,   \
  0x2D,   \
  0x4C,   \
  0x2D,   \
  0x52,   \
  0x4D,   \
  0x2D,   \
  0x30,   \
  0x30,   \
  0x30,   \
  0x31,   \
  0x20,   \
  0x20,   \
  0x05,   \
  GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE, \
  LO_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ), \
  HI_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ), \
  LO_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ), \
  HI_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ), \
  0x02,   \
  GAP_ADTYPE_POWER_LEVEL,  \
  0       \
}

  /*LOCATION type beacon in HALL. 16-to-19th bytes are hall number*/

#define XDV_BEACON_HALL_LOC_SCAN_RESPONSE \
  { \
  0x14,   \
  GAP_ADTYPE_LOCAL_NAME_COMPLETE, \
  0x48,   \
  0x59,   \
  0x47,   \
  0x49,   \
  0x4E,   \
  0x45,   \
  0x58,   \
  0x2D,   \
  0x4C,   \
  0x2D,   \
  0x48,   \
  0x4C,   \
  0x2D,   \
  0x30,   \
  0x30,   \
  0x30,   \
  0x31,   \
  0x20,   \
  0x20,   \
  0x05,   \
  GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE, \
  LO_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ), \
  HI_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ), \
  LO_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ), \
  HI_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ), \
  0x02,   \
  GAP_ADTYPE_POWER_LEVEL,  \
  0       \
}

  /*DISPENSER-ALCOHOL type beacon in ROOM. 13-to-16th bytes are hall number*/

#define XDV_BEACON_ROOM_DISP_ALCOHOL_SCAN_RESPONSE\
  { \
  0x14,   \
  GAP_ADTYPE_LOCAL_NAME_COMPLETE, \
  0x48,   \
  0x59,   \
  0x47,   \
  0x49,   \
  0x4E,   \
  0x45,   \
  0x58,   \
  0x2D,   \
  0x44,   \
  0x2D,   \
  0x52,   \
  0x4D,   \
  0x2D,   \
  0x30,   \
  0x30,   \
  0x30,   \
  0x31,   \
  0x41,   \
  0x20,   \
  0x05,   \
  GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE, \
  LO_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ), \
  HI_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ), \
  LO_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ), \
  HI_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ), \
  0x02,   \
  GAP_ADTYPE_POWER_LEVEL,  \
  0       \
}


#define XDV_BEACON_ROOM_DISP_SOAP_SCAN_RESPONSE \
  { \
  0x14,   \
  GAP_ADTYPE_LOCAL_NAME_COMPLETE, \
  0x48,   \
  0x59,   \
  0x47,   \
  0x49,   \
  0x4E,   \
  0x45,   \
  0x58,   \
  0x2D,   \
  0x44,   \
  0x2D,   \
  0x52,   \
  0x4D,   \
  0x2D,   \
  0x30,   \
  0x30,   \
  0x30,   \
  0x31,   \
  0x53,   \
  0x20,   \
  0x05,   \
  GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE, \
  LO_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ), \
  HI_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ), \
  LO_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ), \
  HI_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ), \
  0x02,   \
  GAP_ADTYPE_POWER_LEVEL,  \
  0       \
}

#define XDV_BEACON_HALL_DISP_ALCOHOL_SCAN_RESPONSE \
  { \
  0x14,   \
  GAP_ADTYPE_LOCAL_NAME_COMPLETE, \
  0x48,   \
  0x59,   \
  0x47,   \
  0x49,   \
  0x4E,   \
  0x45,   \
  0x58,   \
  0x2D,   \
  0x44,   \
  0x2D,   \
  0x48,   \
  0x4C,   \
  0x2D,   \
  0x30,   \
  0x30,   \
  0x30,   \
  0x31,   \
  0x41,   \
  0x20,   \
  0x05,   \
  GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE, \
  LO_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ), \
  HI_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ), \
  LO_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ), \
  HI_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ), \
  0x02,   \
  GAP_ADTYPE_POWER_LEVEL,  \
  0       \
}


#define XDV_BEACON_HALL_DISP_SOAP_SCAN_RESPONSE \
  { \
  0x14,   \
  GAP_ADTYPE_LOCAL_NAME_COMPLETE, \
  0x48,   \
  0x59,   \
  0x47,   \
  0x49,   \
  0x4E,   \
  0x45,   \
  0x58,   \
  0x2D,   \
  0x44,   \
  0x2D,   \
  0x48,   \
  0x4C,   \
  0x2D,   \
  0x30,   \
  0x30,   \
  0x30,   \
  0x31,   \
  0x53,   \
  0x20,   \
  0x05,   \
  GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE, \
  LO_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ), \
  HI_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ), \
  LO_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ), \
  HI_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ), \
  0x02,   \
  GAP_ADTYPE_POWER_LEVEL,  \
  0       \
}

#define XDV_BEACON_SCAN_RESPONSE

/*{
  // complete name
  0x14,   // length of this data
  GAP_ADTYPE_LOCAL_NAME_COMPLETE,
  0x48,   // 'X'
  0x59,   // 'D'
  0x47,   // 'E'
  0x49,   // 'V'
  0x4E,   // 'I'
  0x45,   // 'C'
  0x58,   // 'E'
  0x20,   // 'S'
  0x45,   // '_'
  0x50,   // 'P'
  0x65,   // 'e'
  0x72,   // 'r'
  0x69,   // 'i'
  0x70,   // 'p'
  0x68,   // 'h'
  0x65,   // 'e'
  0x72,   // 'r'
  0x61,   // 'a'
  0x6c,   // 'l'

  // connection interval range
  0x05,   // length of this data
  GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE,
  LO_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ),   // 100ms
  HI_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ),
  LO_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ),   // 1s
  HI_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ),

  // Tx power level
  0x02,   // length of this data
  GAP_ADTYPE_POWER_LEVEL,
  0       // 0dBm
};*/

// Simple BLE Peripheral Task Events
#define SBP_START_DEVICE_EVT                              0x0001
#define SBP_PERIODIC_EVT                                  0x0002

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task Initialization for the BLE Application
 */
extern void XDevicesBLEPeripheral_Init( uint8 task_id );

/*
 * Task Event Processor for the BLE Application
 */
extern uint16 XDevicesBLEPeripheral_ProcessEvent( uint8 task_id, uint16 events );

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* SIMPLEBLEPERIPHERAL_H */
