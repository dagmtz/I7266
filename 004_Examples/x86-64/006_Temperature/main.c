#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main()
{

    /*                 0  1  2  3  4  5  6  7  8  9  10 11 */
    int8_t temp[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (uint8_t counter = 0; counter < 12; counter++)
    {
        printf("Enter the temperature for month %u: ", counter+1);
        scanf("%hhi", (temp+counter));
    }
    

    for (uint8_t counter = 1; counter <= 12; counter++)
    {
        printf("The temperature for month %u is: %i\n", counter, temp[counter-1]);
    }

    return 0;
}