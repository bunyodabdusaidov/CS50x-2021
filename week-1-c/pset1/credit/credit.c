#include <stdio.h>
#include <cs50.h>
#include <math.h>

/* program that prompts the user for a credit card number 
and then reports (via printf) whether it is a valid 
American Express, MasterCard, or Visa card number 
using Luhn's Algorithm that's used for determining if 
credit card number is (syntactically) valid. */

bool check_card_validity(long n); // function prototype
string check_card_type(long n); // function prototype

int main(void)
{
    long n = get_long("Number: "); // get input
    // check card validity and card type, then print corresponding message
    if (check_card_validity(n))
    {
        printf("%s", check_card_type(n));
    }
    else
    {
        printf("INVALID\n");
    }
}

bool check_card_validity(long n)
{
    /* checks card validity by implementing Luhn's algorithm that checks
    if credit card number if (syntactically) valid */
    int sum = 0;
    int temp = 0;
    do 
    {
        temp = ((n % 100) / 10) * 2; // multiplies every other digit by 2, starting with the number's second-to-last digit
        sum += temp / 10; // sorts to digit: 12 / 10 = 1, and adds it to sum
        sum += temp % 10; // sorts to digit: 12 % 10 = 2, and adds it to sum
        sum += n % 10; // adds the sum to the sum of the digits that weren't multiplied by 2
        n /= 100; // shrink the initial number
    }
    while (n != 0);

    // if the total's last digit is 0, number is valid!
    if (sum % 10 == 0)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

string check_card_type(long n)
{
    int len = 0;
    long temp = n;
    int start;
    int visa;

    // calculate number of digits in integer
    do
    {
        temp /= 10;
        len++;
    }
    while (temp != 0);

    temp = pow(10, (len - 2)); // calculates the number to be divided by, to get the first two digits of initial number
    start = n / temp; // gets the first two digits of initial number
    visa = start / 10; // gets the first digit for checking visa cards

    if ((start == 34 || start == 37) & (len == 15))
    {
        // all American Express numbers start with 34 or 37 and contain 15 digits
        return ("AMEX\n");
    }
    else if ((start == 51 || start == 52 || start == 53 || start == 54 || start == 55) & (len == 16))
    {
        // most MasterCard numbers start with 51, 52, 53, 54, or 55 and contain 16 digits
        return ("MASTERCARD\n");
    }
    else if ((visa == 4) & (len == 13 || len == 16))
    {
        // all Visa numbers start with 4 and contain 13 and 16 digits
        return ("VISA\n");
    }
    else
    {
        return ("INVALID\n");
    }
}