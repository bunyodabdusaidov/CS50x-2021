#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

/* this program encrypts messages using Caesar’s cipher */

int check_if_numeric(char *input);
int convert_to_int(char *input);
void encrypt_message(char *plaintext, int key);

int main(int argc, char *argv[])
{
    // check if number of arguments is exactly two
    if (argc == 2)
    {
        int check = check_if_numeric(argv[1]);

        // if key is valid
        if (check)
        {
            int key = convert_to_int(argv[1]);
            char *plaintext = get_string("plaintext: ");

            printf("ciphertext: ");
            encrypt_message(plaintext, key);
            printf("\n");
            return 0;
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

int check_if_numeric(char *input)
{
    /* checks if the input consists of only numbers and returns a boolean */

    int i = 0;
    
    while (input[i])
    {
        if (isdigit(input[i]))
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

int convert_to_int(char *input)
{
    /* converts the string type integer to int type integer. returns the int type key */

    int key = 0;
    int len = strlen(input);

    for (int i = 0; i < len; i++)
    {
        key *= 10; // multiply by 10, gradually coming near to the int type key
        key += input[i] - 48; // identify the number
    }
    return key;
}

void encrypt_message(char *plaintext, int key)
{
    /* encrypts the message by one letter using its position in the alphabet and the secret key. 
    displays the encrypted message */

    int len = strlen(plaintext);
    int encrypted_pos = 0; // new position of the letter in alphabet once the secret key is applied
    char cipher_letter; // new letter once the secret key is applied
    char *uppercase_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // uppercase letters
    char *lowercase_letters = "abcdefghijklmnopqrstuvwxyz"; // lowercase letters

    for (int i = 0; i < len; i++)
    {
        int pos;
        // check if letter is uppercase
        if (isupper(plaintext[i]))
        {
            pos = plaintext[i] - 65; // identify the position of the letter in alphabet
            encrypted_pos = (pos + key) % 26; // calculate the new position by adding the secret key to old position
            cipher_letter = uppercase_letters[encrypted_pos]; // identify the letter in uppercase letters according to new position
        }
        // check if letter is lowercase
        else if (islower(plaintext[i]))
        {
            pos = plaintext[i] - 97; // identify the position of the letter in alphabet
            encrypted_pos = (pos + key) % 26; // calculate the new position by adding the secret key to old position
            cipher_letter = lowercase_letters[encrypted_pos]; // identify the letter in lowercase letters according to new position
        }
        // if not a letter, don't apply secret key. leave as it is.
        else
        {
            cipher_letter = plaintext[i];
        }
        printf("%c", cipher_letter);
    }
}