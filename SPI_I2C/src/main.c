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

#include "OLED/oled.h"
#include "sensirion/sensirion_api.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************


uint16_t timeout = 0;
bool key_pressed = 0;

void timer_callback(uintptr_t context)
{
    if(timeout > 0) 
    {
        timeout--;
    }
}

void eic_callback(uintptr_t context)
{
    key_pressed = true;
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart();
    SYSTICK_TimerCallbackSet(timer_callback, 0);
    EIC_CallbackRegister(EIC_PIN_11, eic_callback, 0); 
    
    OLEDC_initialize();
    oledc_print_curiosity_logo();
    sensirion_init();
    
    oledc_fill_screen(BLACK);
    oledc_draw_string(2, 2, 1, 2, "  SAMD21 Demo  ", GREEN);

    while ( true )
    {
        if(key_pressed)
        {
            key_pressed = false;
            sensirion_read_data();
            sensirion_print_data();
        }
        
        if(timeout == 0)
        {
            timeout = 500;
            LED_Toggle();
        }
    }

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

