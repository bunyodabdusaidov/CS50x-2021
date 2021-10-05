#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // get the correct start size
    int start_size;
    do
    {
        start_size = get_int("Start Size: "); // prompt to enter start size
    } 
    while (start_size < 9); // chech until start size is equal or greater than 9
    
    // get the correct end size
    int end_size;
    do
    {
        end_size = get_int("End Size: "); // prompt to enter end size
    } 
    while (end_size < start_size); // check until end size is equal or greater than start size

    // calculate the number of years to reach the end size
    int i = 0; // variable to track the number of years
    while (start_size < end_size) // check until calculated number of years equals to end size
    {
        start_size = start_size + (start_size / 3 - start_size / 4); // calculate
        i++; // increment i
    }
    printf("Years: %i\n", i); // print result - number of years
    
}