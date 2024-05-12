/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _APP_H    /* Guard against multiple inclusion */
#define _APP_H


void handle_button(uintptr_t context);
void print_header(void);
void print_oled_data(void);
void toggle_led(void);
void init_modules(void);
void handle_USART_cmd(void);
void execute_button_task(void);

#endif /* _APP_H */

/* *****************************************************************************
 End of File
 */
