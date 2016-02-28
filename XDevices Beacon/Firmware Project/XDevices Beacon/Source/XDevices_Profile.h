/**************************************************************************************************

**************************************************************************************************/

#ifndef XDEVICESPROFILE_H
#define XDEVICESPROFILE_H

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

// Profile Parameters
#define XDEVICESPROFILE_CHAR1                   0  // RW uint8 - Profile Characteristic 1 value 
#define XDEVICESPROFILE_CHAR2                   1  // RW uint8 - Profile Characteristic 2 value
#define XDEVICESPROFILE_CHAR3                   2  // RW uint8 - Profile Characteristic 3 value
#define XDEVICESPROFILE_CHAR4                   3  // RW uint8 - Profile Characteristic 4 value
#define XDEVICESPROFILE_CHAR5                   4  // RW uint8 - Profile Characteristic 4 value
  
// XDEVICES Profile Service UUID
#define XDEVICESPROFILE_SERV_UUID               0xFFF0
    
// Key Pressed UUID
#define XDEVICESPROFILE_CHAR1_UUID            0xFFF1
#define XDEVICESPROFILE_CHAR2_UUID            0xFFF2
#define XDEVICESPROFILE_CHAR3_UUID            0xFFF3
#define XDEVICESPROFILE_CHAR4_UUID            0xFFF4
#define XDEVICESPROFILE_CHAR5_UUID            0xFFF5
  
// XDEVICES Keys Profile Services bit fields
#define XDEVICESPROFILE_SERVICE               0x00000001

// Length of Characteristic 5 in bytes
#define XDEVICESPROFILE_CHAR5_LEN           5  

/*********************************************************************
 * TYPEDEFS
 */

  
/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * Profile Callbacks
 */

// Callback when a characteristic value has changed
typedef void (*xdevicesProfileChange_t)( uint8 paramID );

typedef struct
{
  xdevicesProfileChange_t        pfnXdevicesProfileChange;  // Called when characteristic value changes
} xdevicesProfileCBs_t;

    

/*********************************************************************
 * API FUNCTIONS 
 */


/*
 * XDevicesProfile_AddService- Initializes the XDevices GATT Profile service by registering
 *          GATT attributes with the GATT server.
 *
 * @param   services - services to add. This is a bit map and can
 *                     contain more than one service.
 */

extern bStatus_t XDevicesProfile_AddService( uint32 services );

/*
 * XDevicesProfile_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
extern bStatus_t XDevicesProfile_RegisterAppCBs( xdevicesProfileCBs_t *appCallbacks );

/*
 * XDevicesProfile_SetParameter - Set a XDevices GATT Profile parameter.
 *
 *    param - Profile parameter ID
 *    len - length of data to right
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate 
 *          data type (example: data type of uint16 will be cast to 
 *          uint16 pointer).
 */
extern bStatus_t XDevicesProfile_SetParameter( uint8 param, uint8 len, void *value );
  
/*
 * XDevicesProfile_GetParameter - Get a XDevices GATT Profile parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate 
 *          data type (example: data type of uint16 will be cast to 
 *          uint16 pointer).
 */
extern bStatus_t XDevicesProfile_GetParameter( uint8 param, void *value );


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* SIMPLEGATTPROFILE_H */
