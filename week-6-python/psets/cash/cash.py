from decimal import Decimal


def cash():
    """Ask the user for the change owed and spits out the minimum number of coins with which said change can be made"""
    while True:
        # Try prompting the user for input
        try:
            change = input("Change owed: ")
            # If input can be converted to float and it is a non-negative number, break the loop
            if float(change) >= 0:
                break
        # Except ValueError and continue the loop until valid input is given
        except ValueError:
            continue       
    
    change = Decimal(change)  # Using `Decimal` module, convert `change` variable to valid (correct) float number
    coins = [Decimal('0.25'), Decimal('0.10'), Decimal('0.05'), Decimal('0.01')]  # List of coins that can be used for change
    number = 0  # Return variable that will contain the minimum number of change can be made

    # Check and substract the change amounts until the change is 0
    while change > 0:
        # If change is greater that 0.25 (quarters), subtract 0.25 from change
        if change >= coins[0]:
            change -= coins[0]
        # Else if change is greater than 0.10 (dimes), subtract 0.10 from change
        elif change >= coins[1]:
            change -= coins[1]
        # Else if change is greater than 0.05 (nickels), subtract 0.05 from change
        elif change >= coins[2]:
            change -= coins[2]
        # Else if change is greater than 0.01 (pennies), subtract 0.01 from change
        else:
            change -= coins[3]
        # Increment `number` in every subtraction to count the number of changes can be made
        number += 1

    return number


print(cash())

