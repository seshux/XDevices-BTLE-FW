
/*********************************************************************
 * INCLUDES
 */
#include "bcomdef.h"
#include "OSAL.h"
#include "linkdb.h"
#include "att.h"
#include "gatt.h"
#include "gatt_uuid.h"
#include "gattservapp.h"
#include "gapbondmgr.h"

#include "xdevices_profile.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

#define SERVAPP_NUM_ATTR_SUPPORTED        17

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */
// XDevices GATT Profile Service UUID: 0xFFF0
CONST uint8 xdevicesProfileServUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16(XDEVICESPROFILE_SERV_UUID), HI_UINT16(XDEVICESPROFILE_SERV_UUID)
};

// Characteristic 1 UUID: 0xFFF1
CONST uint8 xdevicesProfilechar1UUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16(XDEVICESPROFILE_CHAR1_UUID), HI_UINT16(XDEVICESPROFILE_CHAR1_UUID)
};

// Characteristic 2 UUID: 0xFFF2
CONST uint8 xdevicesProfilechar2UUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16(XDEVICESPROFILE_CHAR2_UUID), HI_UINT16(XDEVICESPROFILE_CHAR2_UUID)
};

// Characteristic 3 UUID: 0xFFF3
CONST uint8 xdevicesProfilechar3UUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16(XDEVICESPROFILE_CHAR3_UUID), HI_UINT16(XDEVICESPROFILE_CHAR3_UUID)
};

// Characteristic 4 UUID: 0xFFF4
CONST uint8 xdevicesProfilechar4UUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16(XDEVICESPROFILE_CHAR4_UUID), HI_UINT16(XDEVICESPROFILE_CHAR4_UUID)
};

// Characteristic 5 UUID: 0xFFF5
CONST uint8 xdevicesProfilechar5UUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16(XDEVICESPROFILE_CHAR5_UUID), HI_UINT16(XDEVICESPROFILE_CHAR5_UUID)
};

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */

static xdevicesProfileCBs_t *xdevicesProfile_AppCBs = NULL;

/*********************************************************************
 * Profile Attributes - variables
 */

// XDevices Profile Service attribute
static CONST gattAttrType_t xdevicesProfileService = { ATT_BT_UUID_SIZE, xdevicesProfileServUUID };


// XDevices Profile Characteristic 1 Properties
static uint8 xdevicesProfileChar1Props = GATT_PROP_READ | GATT_PROP_WRITE;

// Characteristic 1 Value
static uint8 xdevicesProfileChar1 = 0;

// XDevices Profile Characteristic 1 User Description
static uint8 xdevicesProfileChar1UserDesp[17] = "Characteristic 1\0";


// XDevices Profile Characteristic 2 Properties
static uint8 xdevicesProfileChar2Props = GATT_PROP_READ;

// Characteristic 2 Value
static uint8 xdevicesProfileChar2 = 0;

// XDevices Profile Characteristic 2 User Description
static uint8 xdevicesProfileChar2UserDesp[17] = "Characteristic 2\0";


// XDevices Profile Characteristic 3 Properties
static uint8 xdevicesProfileChar3Props = GATT_PROP_WRITE;

// Characteristic 3 Value
static uint8 xdevicesProfileChar3 = 0;

// XDevices Profile Characteristic 3 User Description
static uint8 xdevicesProfileChar3UserDesp[17] = "Characteristic 3\0";


// XDevices Profile Characteristic 4 Properties
static uint8 xdevicesProfileChar4Props = GATT_PROP_NOTIFY;

// Characteristic 4 Value
static uint8 xdevicesProfileChar4 = 0;

// XDevices Profile Characteristic 4 Configuration Each client has its own
// instantiation of the Client Characteristic Configuration. Reads of the
// Client Characteristic Configuration only shows the configuration for
// that client and writes only affect the configuration of that client.
static gattCharCfg_t xdevicesProfileChar4Config[GATT_MAX_NUM_CONN];
                                        
// XDevices Profile Characteristic 4 User Description
static uint8 xdevicesProfileChar4UserDesp[17] = "Characteristic 4\0";


// XDevices Profile Characteristic 5 Properties
static uint8 xdevicesProfileChar5Props = GATT_PROP_READ;

// Characteristic 5 Value
static uint8 xdevicesProfileChar5[XDEVICESPROFILE_CHAR5_LEN] = { 0, 0, 0, 0, 0 };

// XDevices Profile Characteristic 5 User Description
static uint8 xdevicesProfileChar5UserDesp[17] = "Characteristic x\0";


/*********************************************************************
 * Profile Attributes - Table
 */

static gattAttribute_t xdevicesProfileAttrTbl[SERVAPP_NUM_ATTR_SUPPORTED] = 
{
  // XDevices Profile Service
  { 
    { ATT_BT_UUID_SIZE, primaryServiceUUID }, /* type */
    GATT_PERMIT_READ,                         /* permissions */
    0,                                        /* handle */
    (uint8 *)&xdevicesProfileService            /* pValue */
  },

    // Characteristic 1 Declaration
    { 
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ, 
      0,
      &xdevicesProfileChar1Props 
    },

      // Characteristic Value 1
      { 
        { ATT_BT_UUID_SIZE, xdevicesProfilechar1UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE, 
        0, 
        &xdevicesProfileChar1 
      },

      // Characteristic 1 User Description
      { 
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ, 
        0, 
        xdevicesProfileChar1UserDesp 
      },      

    // Characteristic 2 Declaration
    { 
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ, 
      0,
      &xdevicesProfileChar2Props 
    },

      // Characteristic Value 2
      { 
        { ATT_BT_UUID_SIZE, xdevicesProfilechar2UUID },
        GATT_PERMIT_READ, 
        0, 
        &xdevicesProfileChar2 
      },

      // Characteristic 2 User Description
      { 
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ, 
        0, 
        xdevicesProfileChar2UserDesp 
      },           
      
    // Characteristic 3 Declaration
    { 
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ, 
      0,
      &xdevicesProfileChar3Props 
    },

      // Characteristic Value 3
      { 
        { ATT_BT_UUID_SIZE, xdevicesProfilechar3UUID },
        GATT_PERMIT_WRITE, 
        0, 
        &xdevicesProfileChar3 
      },

      // Characteristic 3 User Description
      { 
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ, 
        0, 
        xdevicesProfileChar3UserDesp 
      },

    // Characteristic 4 Declaration
    { 
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ, 
      0,
      &xdevicesProfileChar4Props 
    },

      // Characteristic Value 4
      { 
        { ATT_BT_UUID_SIZE, xdevicesProfilechar4UUID },
        0, 
        0, 
        &xdevicesProfileChar4 
      },

      // Characteristic 4 configuration
      { 
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE, 
        0, 
        (uint8 *)xdevicesProfileChar4Config 
      },
      
      // Characteristic 4 User Description
      { 
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ, 
        0, 
        xdevicesProfileChar4UserDesp 
      },
      
    // Characteristic 5 Declaration
    { 
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ, 
      0,
      &xdevicesProfileChar5Props 
    },

      // Characteristic Value 5
      { 
        { ATT_BT_UUID_SIZE, xdevicesProfilechar5UUID },
        GATT_PERMIT_AUTHEN_READ, 
        0, 
        xdevicesProfileChar5 
      },

      // Characteristic 5 User Description
      { 
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ, 
        0, 
        xdevicesProfileChar5UserDesp 
      },


};


/*********************************************************************
 * LOCAL FUNCTIONS
 */
static uint8 xdevicesProfile_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr, 
                            uint8 *pValue, uint8 *pLen, uint16 offset, uint8 maxLen );
static bStatus_t xdevicesProfile_WriteAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                 uint8 *pValue, uint8 len, uint16 offset );

static void xdevicesProfile_HandleConnStatusCB( uint16 connHandle, uint8 changeType );


/*********************************************************************
 * PROFILE CALLBACKS
 */
// XDevices Profile Service Callbacks
CONST gattServiceCBs_t xdevicesProfileCBs =
{
  xdevicesProfile_ReadAttrCB,  // Read callback function pointer
  xdevicesProfile_WriteAttrCB, // Write callback function pointer
  NULL                       // Authorization callback function pointer
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      XDevicesProfile_AddService
 *
 * @brief   Initializes the XDevices Profile service by registering
 *          GATT attributes with the GATT server.
 *
 * @param   services - services to add. This is a bit map and can
 *                     contain more than one service.
 *
 * @return  Success or Failure
 */
bStatus_t XDevicesProfile_AddService( uint32 services )
{
  uint8 status = SUCCESS;

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( INVALID_CONNHANDLE, xdevicesProfileChar4Config );

  // Register with Link DB to receive link status change callback
  VOID linkDB_Register( xdevicesProfile_HandleConnStatusCB );  
  
  if ( services & XDEVICESPROFILE_SERVICE )
  {
    // Register GATT attribute list and CBs with GATT Server App
    status = GATTServApp_RegisterService( xdevicesProfileAttrTbl, 
                                          GATT_NUM_ATTRS( xdevicesProfileAttrTbl ),
                                          &xdevicesProfileCBs );
  }

  return ( status );
}


/*********************************************************************
 * @fn      XDevicesProfile_RegisterAppCBs
 *
 * @brief   Registers the application callback function. Only call 
 *          this function once.
 *
 * @param   callbacks - pointer to application callbacks.
 *
 * @return  SUCCESS or bleAlreadyInRequestedMode
 */
bStatus_t XDevicesProfile_RegisterAppCBs( xdevicesProfileCBs_t *appCallbacks )
{
  if ( appCallbacks )
  {
    xdevicesProfile_AppCBs = appCallbacks;
    
    return ( SUCCESS );
  }
  else
  {
    return ( bleAlreadyInRequestedMode );
  }
}
  

/*********************************************************************
 * @fn      XDevicesProfile_SetParameter
 *
 * @brief   Set a XDevices Profile parameter.
 *
 * @param   param - Profile parameter ID
 * @param   len - length of data to right
 * @param   value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate 
 *          data type (example: data type of uint16 will be cast to 
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
bStatus_t XDevicesProfile_SetParameter( uint8 param, uint8 len, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case XDEVICESPROFILE_CHAR1:
      if ( len == sizeof ( uint8 ) ) 
      {
        xdevicesProfileChar1 = *((uint8*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case XDEVICESPROFILE_CHAR2:
      if ( len == sizeof ( uint8 ) ) 
      {
        xdevicesProfileChar2 = *((uint8*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case XDEVICESPROFILE_CHAR3:
      if ( len == sizeof ( uint8 ) ) 
      {
        xdevicesProfileChar3 = *((uint8*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case XDEVICESPROFILE_CHAR4:
      if ( len == sizeof ( uint8 ) ) 
      {
        xdevicesProfileChar4 = *((uint8*)value);
        
        // See if Notification has been enabled
        GATTServApp_ProcessCharCfg( xdevicesProfileChar4Config, &xdevicesProfileChar4, FALSE,
                                    xdevicesProfileAttrTbl, GATT_NUM_ATTRS( xdevicesProfileAttrTbl ),
                                    INVALID_TASK_ID );
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case XDEVICESPROFILE_CHAR5:
      if ( len == XDEVICESPROFILE_CHAR5_LEN ) 
      {
        VOID osal_memcpy( xdevicesProfileChar5, value, XDEVICESPROFILE_CHAR5_LEN );
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;
      
    default:
      ret = INVALIDPARAMETER;
      break;
  }
  
  return ( ret );
}

/*********************************************************************
 * @fn      XDevicesProfile_GetParameter
 *
 * @brief   Get a XDevices Profile parameter.
 *
 * @param   param - Profile parameter ID
 * @param   value - pointer to data to put.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate 
 *          data type (example: data type of uint16 will be cast to 
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
bStatus_t XDevicesProfile_GetParameter( uint8 param, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case XDEVICESPROFILE_CHAR1:
      *((uint8*)value) = xdevicesProfileChar1;
      break;

    case XDEVICESPROFILE_CHAR2:
      *((uint8*)value) = xdevicesProfileChar2;
      break;      

    case XDEVICESPROFILE_CHAR3:
      *((uint8*)value) = xdevicesProfileChar3;
      break;  

    case XDEVICESPROFILE_CHAR4:
      *((uint8*)value) = xdevicesProfileChar4;
      break;

    case XDEVICESPROFILE_CHAR5:
      VOID osal_memcpy( value, xdevicesProfileChar5, XDEVICESPROFILE_CHAR5_LEN );
      break;      
      
    default:
      ret = INVALIDPARAMETER;
      break;
  }
  
  return ( ret );
}

/*********************************************************************
 * @fn          xdevicesProfile_ReadAttrCB
 *
 * @brief       Read an attribute.
 *
 * @param       connHandle - connection message was received on
 * @param       pAttr - pointer to attribute
 * @param       pValue - pointer to data to be read
 * @param       pLen - length of data to be read
 * @param       offset - offset of the first octet to be read
 * @param       maxLen - maximum length of data to be read
 *
 * @return      Success or Failure
 */
static uint8 xdevicesProfile_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr, 
                            uint8 *pValue, uint8 *pLen, uint16 offset, uint8 maxLen )
{
  bStatus_t status = SUCCESS;

  // If attribute permissions require authorization to read, return error
  if ( gattPermitAuthorRead( pAttr->permissions ) )
  {
    // Insufficient authorization
    return ( ATT_ERR_INSUFFICIENT_AUTHOR );
  }
  
  // Make sure it's not a blob operation (no attributes in the profile are long)
  if ( offset > 0 )
  {
    return ( ATT_ERR_ATTR_NOT_LONG );
  }
 
  if ( pAttr->type.len == ATT_BT_UUID_SIZE )
  {
    // 16-bit UUID
    uint16 uuid = BUILD_UINT16( pAttr->type.uuid[0], pAttr->type.uuid[1]);
    switch ( uuid )
    {
      // No need for "GATT_SERVICE_UUID" or "GATT_CLIENT_CHAR_CFG_UUID" cases;
      // gattserverapp handles those reads

      // characteristics 1 and 2 have read permissions
      // characteritisc 3 does not have read permissions; therefore it is not
      //   included here
      // characteristic 4 does not have read permissions, but because it
      //   can be sent as a notification, it is included here
      case XDEVICESPROFILE_CHAR1_UUID:
      case XDEVICESPROFILE_CHAR2_UUID:
      case XDEVICESPROFILE_CHAR4_UUID:
        *pLen = 1;
        pValue[0] = *pAttr->pValue;
        break;

      case XDEVICESPROFILE_CHAR5_UUID:
        *pLen = XDEVICESPROFILE_CHAR5_LEN;
        VOID osal_memcpy( pValue, pAttr->pValue, XDEVICESPROFILE_CHAR5_LEN );
        break;
        
      default:
        // Should never get here! (characteristics 3 and 4 do not have read permissions)
        *pLen = 0;
        status = ATT_ERR_ATTR_NOT_FOUND;
        break;
    }
  }
  else
  {
    // 128-bit UUID
    *pLen = 0;
    status = ATT_ERR_INVALID_HANDLE;
  }

  return ( status );
}

/*********************************************************************
 * @fn      xdevicesProfile_WriteAttrCB
 *
 * @brief   Validate attribute data prior to a write operation
 *
 * @param   connHandle - connection message was received on
 * @param   pAttr - pointer to attribute
 * @param   pValue - pointer to data to be written
 * @param   len - length of data
 * @param   offset - offset of the first octet to be written
 *
 * @return  Success or Failure
 */
static bStatus_t xdevicesProfile_WriteAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                 uint8 *pValue, uint8 len, uint16 offset )
{
  bStatus_t status = SUCCESS;
  uint8 notifyApp = 0xFF;
  
  // If attribute permissions require authorization to write, return error
  if ( gattPermitAuthorWrite( pAttr->permissions ) )
  {
    // Insufficient authorization
    return ( ATT_ERR_INSUFFICIENT_AUTHOR );
  }
  
  if ( pAttr->type.len == ATT_BT_UUID_SIZE )
  {
    // 16-bit UUID
    uint16 uuid = BUILD_UINT16( pAttr->type.uuid[0], pAttr->type.uuid[1]);
    switch ( uuid )
    {
      case XDEVICESPROFILE_CHAR1_UUID:
      case XDEVICESPROFILE_CHAR3_UUID:

        //Validate the value
        // Make sure it's not a blob oper
        if ( offset == 0 )
        {
          if ( len != 1 )
          {
            status = ATT_ERR_INVALID_VALUE_SIZE;
          }
        }
        else
        {
          status = ATT_ERR_ATTR_NOT_LONG;
        }
        
        //Write the value
        if ( status == SUCCESS )
        {
          uint8 *pCurValue = (uint8 *)pAttr->pValue;        
          *pCurValue = pValue[0];

          if( pAttr->pValue == &xdevicesProfileChar1 )
          {
            notifyApp = XDEVICESPROFILE_CHAR1;        
          }
          else
          {
            notifyApp = XDEVICESPROFILE_CHAR3;           
          }
        }
             
        break;

      case GATT_CLIENT_CHAR_CFG_UUID:
        status = GATTServApp_ProcessCCCWriteReq( connHandle, pAttr, pValue, len,
                                                 offset, GATT_CLIENT_CFG_NOTIFY );
        break;
        
      default:
        // Should never get here! (characteristics 2 and 4 do not have write permissions)
        status = ATT_ERR_ATTR_NOT_FOUND;
        break;
    }
  }
  else
  {
    // 128-bit UUID
    status = ATT_ERR_INVALID_HANDLE;
  }

  // If a charactersitic value changed then callback function to notify application of change
  if ( (notifyApp != 0xFF ) && xdevicesProfile_AppCBs && xdevicesProfile_AppCBs->pfnXDevicesProfileChange )
  {
    xdevicesProfile_AppCBs->pfnXDevicesProfileChange( notifyApp );  
  }
  
  return ( status );
}

/*********************************************************************
 * @fn          xdevicesProfile_HandleConnStatusCB
 *
 * @brief       XDevices Profile link status change handler function.
 *
 * @param       connHandle - connection handle
 * @param       changeType - type of change
 *
 * @return      none
 */
static void xdevicesProfile_HandleConnStatusCB( uint16 connHandle, uint8 changeType )
{ 
  // Make sure this is not loopback connection
  if ( connHandle != LOOPBACK_CONNHANDLE )
  {
    // Reset Client Char Config if connection has dropped
    if ( ( changeType == LINKDB_STATUS_UPDATE_REMOVED )      ||
         ( ( changeType == LINKDB_STATUS_UPDATE_STATEFLAGS ) && 
           ( !linkDB_Up( connHandle ) ) ) )
    { 
      GATTServApp_InitCharCfg( connHandle, xdevicesProfileChar4Config );
    }
  }
}


/*********************************************************************
*********************************************************************/
