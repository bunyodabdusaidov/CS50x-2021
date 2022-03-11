def credit():
    number = input("Number: ")  # Get user input
    valid = is_valid(number)  # Check if input is valid card number

    # If card number is valid, check the card type
    if valid:
        # Check if card is from American Express
        if len(number) == 15 and number[:2] in ["34", "37"]:
            print("AMEX")
        # Check if card is from Mastercard
        elif len(number) == 16 and number[:2] in ["51", "52", "53", "54", "55"]:
            print("MASTERCARD")
        # Check if card is from Visa
        elif len(number) in [13, 16] and number[0] == "4":
            print("VISA")
        # If card type is Invalid
        else:
            print("INVALID")
    else:
        print("INVALID")


def is_valid(number):
    """Checks if the number is a valid card number by using Luhn's algorithm."""
    n = 0  # Store the sum
    for i in range(0, len(number), -2):
        tmp = str(int(number[i]) * 2)  # Multiply every other digit by 2
        # If product is two digit number, take each digit and add to n
        if len(tmp) == 2:
            n += int(tmp[0])
            n += int(tmp[1])
        # If product is not two digit number, add it to n
        else:
            n += int(tmp)
        
        n += int(number[i+1])  # Add digits that weren’t multiplied by 2
    
    # If total modulo 10 is congruent to 0, number is valid, return True
    if n % 10 == 0:
        return True

    return False


credit()
