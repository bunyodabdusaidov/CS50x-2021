# print double half-pyramid of a specified height
def mario():
    # prompt the user for input until valid input is entered
    while True:
        height = input("Height: ")  # prompt the user for input (height)
        # if input consists of only numbers and in range of 1 and 8 (inclusive)
        if height.isdigit() and 1 <= int(height) <= 8:
            break
    
    height = int(height)  # convert str to int
    space = height - 1  # get number of spaces to print from # (bricks) in first-half pyramid
    for i in range(1, height+1):
        print(" " * space, end="")  # print leading spaces of first pyramid
        print("#" * i, end="")  # print bricks of first pyramid
        print("  ", end="")  # print middle two spaced between first and second pyramid
        print("#" * i)  # print bricks of second pyramid
        space -= 1  # decrement space


mario()