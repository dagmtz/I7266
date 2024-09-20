 /*
  * Name:		    usart.h
  * Author:		    dagmtzs@gmail.com
  * Target:		    ATmega328P
  * Date:		    dom 14 abr 2024 12:52:59 CST
  *
  * Description:	Header file for usart.c
  */

#ifndef USART_H_
#define USART_H_

#define DEFAULT_F_CPU 16000000U

#ifdef F_CPU
#   define FOSC F_CPU
#else
#   ifdef DEFAULT_F_CPU
#       define FOSC DEFAULT_F_CPU
#   else 
#       error "No F_CPU defined!"
#   endif
#endif

#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( unsigned int );
void USART_Transmit( unsigned char );

#endif /* USART_H_ */