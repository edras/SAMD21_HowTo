/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

void callback(uintptr_t context)
{
    printf("Hello World!\n\r");
    LED_Toggle();
}

void eic_callback(uintptr_t context)
{
    if(SW0_Get())
    {
        printf("Switch released!\n\r");
    }
    else
    {
        printf("Switch pressed!\n\r");
    }    
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart();
    SYSTICK_TimerCallbackSet(callback, 0);
    EIC_CallbackRegister(EIC_PIN_11, eic_callback, 0);    

    while ( true ) { }
    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

