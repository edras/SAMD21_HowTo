/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    app.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "definitions.h"

#include "OLED/oled.h"
#include "sensirion/sensirion_api.h"


bool button_set = false;
bool button_state = false;

void handle_button(uintptr_t context) 
{
    button_set = true;

    if (SW0_Get() == 0)
    {
        button_state = true;
    }
    else
    {
        button_state = false;
    }  
}

void execute_button_task(void)
{
    if(button_set)
    {
        if(button_state)
        {
            sensirion_print_data();  
        }
            
    }    
}

void print_header(void)
{
    // send welcome message to terminal
    printf("\e[1;1H\e[2J");
    printf("Sensor Demo Board\r\nVersion %s - %s\r\n", __DATE__, __TIME__);
    printf("Curiosity Nano Board > 1[None] 2[OLED] 3[HVAC Click]\r\n");
    
    printf("\r\nProgram Running: \r\n");
    printf("- Each 5s: Read sensor data\r\n");
    printf("- User interaction: key press/release prints sensor data\r\n");
    printf("\r\nType following commands to interact:\r\n\r\n");
    printf(" w - Print weather info \r\n");
    printf(" c - Clear screen\r\n");
    printf(" a - Print Hello World\r\n");
}

void init_modules(void)
{
    OLEDC_initialize();
    oledc_print_curiosity_logo();
    sensirion_init();
    
    oledc_fill_screen(BLACK);
    oledc_draw_string(2, 2, 1, 2, "  SAMD21 Demo  ", GREEN);
}

void toggle_led(void)
{
    LED_Toggle();
}

void handle_USART_cmd(void)
{
    char buffer[5];
    if(SERCOM5_USART_ReceiverIsReady())
    {
        *buffer = SERCOM5_USART_ReadByte();
        while(SERCOM5_USART_ReceiverIsReady())
            SERCOM5_USART_ReadByte();
        
        switch(buffer[0])
        {
            case 'c': print_header();               break;
            case 'w': sensirion_print_data();       break;
            case 'a': printf("Hello World!\r\n");   break; 
            default: break;
        }
    } 
}

void print_oled_data(void)
{    
    sensirion_data *sensor = sensirion_get_data();
    char msg[20];
    if(sensor != NULL)
    {
        sprintf(msg, "Temp: %.1f C    ", (float)sensor->sen5x.temperature/100);
        oledc_draw_string_on_bg(2, 20, 1, 2, msg, GREEN, BLACK);
        sprintf(msg, "Mois: %.1f %%RH ", (float)sensor->sen5x.humidity/100);
        oledc_draw_string_on_bg(2, 40, 1, 2, msg, GREEN, BLACK);
        sprintf(msg, "CO2:  %d ppm     ", sensor->scd4x.co2);
        oledc_draw_string_on_bg(2, 60, 1, 2, msg, GREEN, BLACK);
    }
}

/* *****************************************************************************
 End of File
 */
