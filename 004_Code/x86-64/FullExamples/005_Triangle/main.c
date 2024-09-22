#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

void printTriangle(uint8_t);

int main(int argc, char **argv)
{
    int _n;
    uint8_t n;
    
    switch (argc)
    {
    case 1:
        _n = 0;
        n = 0;
        bool valid_value = false;        
        
        while (valid_value != true)
        {
            printf("Enter a natural number (less than 256) to print a triangle with that base and height: ");
            scanf("%d", &_n);
            if(_n < 1 || _n > 255)
            {
                printf("The number entered is not valid\n");   
            }
            else
            {
                valid_value = true;
                n = _n;
            }
        }
        printTriangle(n);
        break;
    
    case 2:
        _n = atoi(argv[1]);
        n = 0;
        if(_n < 1 || _n > 255)
        {
            printf("The number entered is not valid\n");    
            return 0;
        }
        else
        {
            n = (uint8_t) atoi(argv[1]);
        }
        printTriangle(n);
        break;

    default:
        printf("This program did not receive the right amount of arguments.\n");    
        return 0;
        break;
    }

    return 0;
}

void printTriangle(uint8_t n)
{
    for (uint8_t h = 0; h <= n; h++)
    {
        for (uint8_t s = 0; s < n-h; s++)
        {
            printf(" ");    
        }
        for (uint8_t c = 0; c < h; c++)
        {
            printf("* ");    
        }
        printf("\n");    
    }
}