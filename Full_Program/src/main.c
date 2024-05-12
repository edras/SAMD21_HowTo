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

#include "tasks.h"
#include "app.h"
#include "sensirion/sensirion_api.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

void Millisecond_Callback(uintptr_t context) {
    /* This function should be called each 1 millisecond */
    Task_synch();
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    // Interrupt function for SW0 button
    EIC_CallbackRegister(EIC_PIN_11, handle_button, 0);
    SYSTICK_TimerCallbackSet(Millisecond_Callback, 0);
    SYSTICK_TimerStart();
    
    print_header();
    init_modules();
    
    Task_register(0, 2000, sensirion_read_data);
    Task_register(0, 5000, print_oled_data);    
    Task_register(0, 500, toggle_led);   

    while ( true )
    {   
        Task_execute();
        execute_button_task();
        handle_USART_cmd();
    }

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

