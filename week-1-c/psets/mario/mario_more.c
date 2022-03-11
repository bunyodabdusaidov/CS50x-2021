#include <stdio.h>
#include <cs50.h>

/* link to description of the problem: https://cs50.harvard.edu/x/2021/psets/1/mario/more/ */

void pyramid(int n); // function prototype

int main(void)
{
    int n; // variable to store user's input
    do
    {
        n = get_int("Heigth: "); // prompt to enter the heigth of pyramid
    }
    while (n < 1 || n > 8); // check until the heigth is more than 1 and less than 8 inclusively

    pyramid(n); // function call
}

void pyramid(int n)
{
    /*function to abstract implementation details. 
    It takes number as argument which will be the user's input*/
    int i = 1; // variable to track number of #s
    while (n > 0)
    {
        // print same number of spaces as the heigth
        for (int j = 1; j < n; j++)
        {
            printf(" ");
        }
        // print # starting from 1 and aligning to left gradually
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("  "); // print two blank spaces
        // print # startinf from 1 and aligning to right gradually
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n"); // print new line
        n--; // decrement heigth
        i++; // increment i which is the number of #s
    }
}