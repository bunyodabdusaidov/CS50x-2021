#include <stdio.h>
#include <cs50.h>

/* link to description of the problem: https://cs50.harvard.edu/x/2021/labs/1/hello/ */

int main(void)
{
    // Prompt the user to enter his/her name
    string name = get_string("What is your name?\n");
    // Print `Hello` and user's name (input)
    printf("Hello, %s\n", name);
}