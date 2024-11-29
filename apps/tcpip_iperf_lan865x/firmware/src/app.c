/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "config/FreeRTOS/definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    SYS_STATUS tcpipStat;
    TCPIP_NET_HANDLE netH;
    static IPV4_ADDR dwLastIP = {-1};
    
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;

            
            if (appInitialized)
            {

                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

      case APP_STATE_INIT_TCPIP_WAIT_START:
            tcpipStat = TCPIP_STACK_Status(sysObj.tcpip);
            if (tcpipStat < 0) {
                SYS_CONSOLE_PRINT("TCP/IP stack initialization failed!\r\n");
                appData.state = APP_STATE_IDLE;
            } else if (tcpipStat == SYS_STATUS_READY) {
                SYS_CONSOLE_PRINT("TCP/IP stack successful!\r\n");
                appData.state = APP_STATE_INIT_TCPIP_WAIT_FOR_IP;
            }
            break;

        case APP_STATE_INIT_TCPIP_WAIT_FOR_IP:
            netH = TCPIP_STACK_IndexToNet(0);
            if (!TCPIP_STACK_NetIsReady(netH)) {
                break;
            }
            appData.MyIpAddr.Val = TCPIP_STACK_NetAddress(netH);

            TCPIP_MAC_ADDR * mac_ptr;
            mac_ptr = (TCPIP_MAC_ADDR*) TCPIP_STACK_NetAddressMac(netH);
            memcpy(&mac_ptr->v[0], &appData.MyMacAddr.v[0], 6);

            if (dwLastIP.Val != appData.MyIpAddr.Val) {

                dwLastIP.Val = appData.MyIpAddr.Val;
                SYS_CONSOLE_PRINT("=============================================\n\r");
                SYS_CONSOLE_PRINT("Build Time %s %s \n\r", __DATE__, __TIME__);
                SYS_CONSOLE_PRINT("Default IP Address : %d.%d.%d.%d\r\n", appData.MyIpAddr.v[0], appData.MyIpAddr.v[1], appData.MyIpAddr.v[2], appData.MyIpAddr.v[3]);
                SYS_CONSOLE_PRINT("Default MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\r\n", appData.MyMacAddr.v[0], appData.MyMacAddr.v[1], appData.MyMacAddr.v[2], appData.MyMacAddr.v[3], appData.MyMacAddr.v[4], appData.MyMacAddr.v[5]);
                SYS_CONSOLE_PRINT("T1S Node ID %d\n\r",DRV_LAN865X_PLCA_NODE_ID_IDX0_X);
                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;        
        
        case APP_STATE_SERVICE_TASKS:
        {

            break;
        }

        case APP_STATE_IDLE:
        {

            break;
        }
        
        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
