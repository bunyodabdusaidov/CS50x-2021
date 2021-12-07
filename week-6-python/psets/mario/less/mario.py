# print a half-pyramid of specified height
def mario():
    # prompt the user for input until valid input is entered
    while True:
        height = input("Height: ")  # prompt the user for input (number for height)
        # if input consists of only numbers and is in range of 1 and 8 (inclusive)
        if height.isdigit() and 1 <= int(height) <= 8: 
            break
        
    height = int(height)  # convert from str to int
    space = height - 1  # get number of spaces to print before # (bricks)
    # loop starting from 1 until height
    for h in range(1, (height+1)):
        print(" " * space, end="")  # print spaces
        print("#" * h)  # print bricks
        space -= 1  # decrement space


mario()
