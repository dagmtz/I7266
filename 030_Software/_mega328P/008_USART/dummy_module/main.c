#include <util/delay.h>
#include "includes/usart.h"

int main( void )
{
    USART_Init(MYUBRR);
    while(1)
    {
        USART_Transmit('H');
        USART_Transmit('i');
        USART_Transmit('!');
        USART_Transmit('\r');
        USART_Transmit('\n');
       	_delay_ms(1000); 
    }
}



