// gcc main.c -o main.exe
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main()
{
    /* printf("El tamano de un char es: %zu\n", sizeof(char));
    printf("El tamano de un short int es: %zu\n", sizeof(short int));
    printf("El tamano de un int es: %zu\n", sizeof(int));
    printf("El tamano de un long int es: %zu\n", sizeof(long int));
    printf("El tamano de un float es: %zu\n", sizeof(float));
    printf("El tamano de un double es: %zu\n\n", sizeof(double));

    printf("El tamano de un uint8_t es: %zu\n", sizeof(uint8_t));
    printf("El tamano de un uint16_t es: %zu\n", sizeof(uint16_t));
    printf("El tamano de un uint32_t es: %zu\n", sizeof(uint32_t));
    printf("El tamano de un uint64_t es: %zu\n", sizeof(uint64_t)); */


    /* printf("%zu\n", sizeof(void)); // This is not right!
    printf("%zu\n", sizeof(void *));  */

    uint8_t edad = 0;
    uint16_t birth_year = 0;

    printf("Ingresa tu edad: ");
    scanf("%u", &edad);

    printf("El doble de tu edad es: %u\n", edad*2);
    printf("El tamano de memoria que usa tu edad es de %zu bytes\n", sizeof(edad));

    return 0;
}