/*
 * File:            main.c
 * Author:          Name Surname
 *                  email
 * Date:            Sun Jan 01 00:00:00 AM CST 2024
 * Target:          ATmega328P
 * Description:     This is a template for ATmega328P programs written in C
 */

#define F_CPU 16000000U

#define DELAY_PER_DIGIT 3U
#define REPETITIONS 85U

#define D4 1U
#define D3 2U
#define D2 4U
#define D1 8U

#include <avr/io.h>
#include <util/delay.h>

/* Recomiendo que los nombres de todas las funciones (excepto la main) y de 
todas las variables y constantes se cambien por aquellos que a cada quién les 
parezcan mejor. */

void select_digit(uint8_t);
void show_number(uint8_t);

void main(void)
{	

    /* Aquí se declaran e inicializan las variables que se usarán para llevar 
    la cuenta de minutos y segundos. */
    uint8_t u_s = 0;
    uint8_t d_s = 0;

    /* Aquí se debe configurar la dirección de los pines de los puertos 
    utilizados, en este caso las salidas tanto al decodificador de 7 segmentos 
    como a los transistores que seleccionan el dígito a encender. */
    
    /* 
    DDRB = ...; 
    */

    /* Este es el ciclo principal */
    while (1U)
    {
        
        /* Y este es el ciclo en el cual se van a llamar a las funciones que van a mostrar un número varias veces para que se alcance a apreciar.
        
        Nótese que la constante REPETITIONS guarda el número de repeticiones que se harán mientras se muestra un mismo número, o al menos esa fue la intención inicial */
        for (uint8_t i = 0; i < REPETITIONS; i++)
        {

            /* La estrategia aquí es: mandar un número al decodificador de 7 
            segmentos... */
            show_number(u_s);
            /* luego encender el primer dígito... */
            select_digit(1);

            /* y repetir los dos pasos anteriores para cada dígito, mandándole 
            a cada dígito el valor correspondiente, o sea, al dígito 1 las 
            unidades de segundos, al 2 las decenas de segundos, y así 
            sucesivamente. */
            
            /* 
            show_number(d_s);
            select_digit(2);
            
            ...
             */
        }
        
        /* Al final de escribir los 4 dígitos varias veces, actualizaremos las
        unidades de segundos incrementando por uno */
        u_s++;

        /* Y después, hay que revisar y ajustar las decenas de segundos, y, en 
        su caso, reiniciar las unidades de segundos */
        if (u_s >= 10)
        {
            d_s++;
            u_s = 0;
        }

        /* A cada uno le toca completar el funcionamiento para los minutos */
    }
    
    return;

}

/* Esta función sirve para encender el dígito que nosotros indiquemos */
void select_digit(uint8_t digit)
{
    switch (digit)
    {
    case 1:
        /* Aquí va la instrucción que encienda el pin a donde está conectado el 
        transistor que controla el pin común (por ejemplo, el ánodo común) del 
        dígito 1 */
        /* PORTB = ? */

        /* Y luego un retardo para que el dígito se muestre durante una
        fracción de tiempo antes de cambiarlo. */
        _delay_ms(DELAY_PER_DIGIT); 
        break;

    case 2:
        /* Lo mismo aquí, pero esta vez para el dígito 2 */
        /* PORTB = ? */

        _delay_ms(DELAY_PER_DIGIT); 
        break;

    case 3:
        /* Y así sucesivamente para los 4 dígitos */

        break;

    case 4:
        /* ... */
        
        break;
    
    default:
        break;
    }   
}

/* Esta función se encarga de enviar un cierto número a través de los primeros 
4 bits de un puerto hacia el decodificador de 7 segmentos, de esta manera, el 
número que se le pasa a la función, se debería iluminar en el dígito que esté 
seleccionado */
void show_number(uint8_t number)
{
    PORTC = ((PORTC & 0xF0) | (number & 0x0F));
}