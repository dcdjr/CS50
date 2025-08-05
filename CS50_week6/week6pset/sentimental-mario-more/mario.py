from cs50 import get_int

# Defines main function


def main():
    # Fetches desired pyramid height from user
    height = getHeight()

    # Creates the pyramid
    makePyramid(height)

# Defines a function that asks for an input of type integer,
# Reprompts if input isn't an integer or if 1 <= input <= 8


def getHeight():
    # Creates loop that won't end until broken out of
    while True:
        # Fetches an integer from the user
        height = get_int("Height: ")
        # If valid input, break out of loop and return input, else reprompt
        if height <= 8 and height >= 1:
            break
    return height

# Defines the function that prints a mario-style pyramid to the command line
# Takes desired pyramid height as input


def makePyramid(height):
    # For loop that loop froms 1 to height inclusive (done for formatting reasons)
    for row in range(1, height + 1):
        # Prints (height - row) spaces
        for i in range(height - row):
            print(" ", end="")
        # Prints (row) hashtags
        for i in range(row):
            print("#", end="")
        # Prints two spaces to separate sides of pyramid
        print("  ", end="")
        # Prints (row) hashtags
        for i in range(row):
            print("#", end="")
        # Prints new line for each row
        print()


# Calls main to run program
main()
