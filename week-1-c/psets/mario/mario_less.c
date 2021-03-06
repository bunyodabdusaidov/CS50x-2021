#include <stdio.h>
#include <cs50.h>

/* link to description of the problem: https://cs50.harvard.edu/x/2021/psets/1/mario/less/ */

int main(void)
{
    int n; // variable to store user's input
    do
    {
        n = get_int("Heigth: "); // prompt to enter the heigth of pyramid
    }
    while (n < 1 || n > 9); // check until the heigth is more than 1 and less than 9 inclusively

    int i = 1; // variable to track the number of bricks to be displayed
    while (n > 0)
    {
        // print spaces according to the heigth
        for (int j = 1; j < n; j++)
        {
            printf(" ");
        }
        // print a brick and increment its quantity
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n"); // print new line
        n--; // decrement heigth so that it will align to right gradually
        i++; // increment the number of bricks gradually
    }
}