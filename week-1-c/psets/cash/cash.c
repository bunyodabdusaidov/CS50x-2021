#include <stdio.h>
#include <cs50.h>
#include <math.h>

/* 
This code is implemented using Greedy Algorithms.
At each step of the algorithm, uses the largest value coin possible.

link to description of the problem: https://cs50.harvard.edu/x/2021/psets/1/cash/
*/

int check_coins(int cents); // function prototype

int main(void)
{
    float n;
    int cents;
    do
    {
        n = get_float("Change owed: "); // get input
        cents = round(n * 100); // round from dollars to cents: 0.20 -> 20
    }    
    while (n < 0); // prompt the user until the input is non-negative value

    int coins = check_coins(cents); // call function and assign the return value to variable
    printf("%i\n", coins); // print the answer
}

int check_coins(int cents)
{
    int coin_values[4] = {25, 10, 5, 1}; // list of coin values
    int coins = 0; // variable to track the number of coins
    
    if (cents == 0) // if the input is 0, return 0
    {
        return coins;
    }

    // loop through each value in coin_values list and check
    for (int i = 0; i < 4; i++)
    {
        while (cents >= coin_values[i])
        {
            cents -= coin_values[i]; // subtract the coin_value from the input
            coins++; // increment the number of coins by 1
        }
    }
    return coins; // return the final result
}