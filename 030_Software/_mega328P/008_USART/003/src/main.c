#include <util/delay.h>
#include "usart.h"

#define DELAY_TIME_MS       100U
#define USART_BUFFER_SIZE   255U
#ifndef BAUD_RATE
    #define BAUD_RATE           19200U
#endif
char USART_buffer[USART_BUFFER_SIZE];

int main( void )
{
    USART_init(UBRR_CALC(BAUD_RATE));
    USART_puts( "\033[2J\033[H" );
    USART_puts( "\033[1;36m> USART Ready\r\n\n" );
    USART_puts( "\033[0;32mHello World! :)\r\n" );

    while(1U)
    {
        USART_puts( "\033[0mWrite a string! (max 255 characters)\r\n" );
        USART_getl(USART_buffer, USART_BUFFER_SIZE);
       	_delay_ms(DELAY_TIME_MS); 
        USART_puts( "\nThe string received was:\033[0;33m " );
        USART_puts( USART_buffer );
        USART_puts( "\n" );
    }
}



