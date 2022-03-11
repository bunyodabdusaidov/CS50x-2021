#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

/* This program encrypts (i.e., conceal in a reversible way) a message by replacing every letter with another letter. */

int check_if_alphabetical(char *input);
void encrypt_message(char *plaintext, char *key);
int check_duplicate(char *plaintext);

int main(int argc, char *argv[])
{
    // check if number of arguments is exactly two
    if (argc == 2)
    {
        int check = check_if_alphabetical(argv[1]);

        // if key is valid (consists of only letters)
        if (check)
        {
            // check if input consists of 26 different characters (without duplicates)
            if (strlen(argv[1]) == 26 & check_duplicate(argv[1]))
            {
                char *plaintext = get_string("plaintext: ");
                printf("ciphertext: ");
                encrypt_message(plaintext, argv[1]);
                printf("\n");
                return 0;
            }
            // if not, print error message
            else
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
        // if key is invalid, print error message
        else
        {
            printf("Usage: %s key\n", argv[0]);
            return 1;
        }
    }
    // if number of arguments is not exactly two, print error message
    else
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
}

int check_if_alphabetical(char *input)
{
    /* checks if the input consists of only letters and returns a boolean */

    int i = 0;
    
    while (input[i])
    {
        if (isalpha(input[i]))
        {
            i++;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int check_duplicate(char *plaintext)
{
    /* linear search algorithm is implemented to identify duplicate characters*/
    int len = strlen(plaintext);
    char temp;
    for (int i = 0; i < len; i++)
    {
        temp = plaintext[i];
        for (int j = i + 1; j <= len; j++)
        {
            if (temp == plaintext[j])
            {
                return false;
            }

        }
    }
    return true;
}

void encrypt_message(char *plaintext, char *key)
{
    /* encrypts the message by one letter at a time using its position 
    and replacing it with the exact position of the letter in the secret key. 
    and displays the encrypted message */

    int len = strlen(plaintext);
    char cipher_letter; // new letter once the secret key is applied
    for (int i = 0; i < len; i++)
    {
        int pos;
        // check if letter is uppercase
        if (isupper(plaintext[i]))
        {
            pos = plaintext[i] - 65; // identify the position of the letter in alphabet
            cipher_letter = toupper(key[pos]); // replace the old letter by new letter according to its position
        }
        // check if letter is lowercase
        else if (islower(plaintext[i]))
        {
            pos = plaintext[i] - 97; // identify the position of the letter in alphabet
            cipher_letter = tolower(key[pos]); // replace the old letter by new letter according to its position
        }
        // if not a letter, don't apply secret key. leave as it is.
        else
        {
            cipher_letter = plaintext[i];
        }
        printf("%c", cipher_letter);
    }
}