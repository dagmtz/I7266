#ifndef USART_H_
#define USART_H_

#ifndef F_CPU
	#warning F_CPU is undefined, UBRR_CALC macro may not work properly
#endif

#define UBRR_CALC(x) ((F_CPU+(x)*8UL) / (16UL*(x))-1UL) /* macro calculating precise UBRR value */

/* Set the frame and speed */
void USART_init( unsigned int ubrr );

/* Print a character through USART */
void USART_putc( char character );

/* Print a string through USART */
void USART_puts( char *p_string );

/* Reads a character through USART */
char USART_getc( void );

/* Reads a string ended in "\r" through USART */
void USART_getl(char* buf, uint8_t length);

#endif /* USART_H_ */


