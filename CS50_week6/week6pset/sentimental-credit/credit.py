from cs50 import get_int
import math

AMEX_START = [34, 37]
MASTERCARD_START = [51, 52, 53, 54, 55]
VISA_START = 4

AMEX_LENGTH = 15
MASTERCARD_LENGTH = 16
VISA_LENGTH = [13, 16]


def main():
    number = get_int("Number: ")
    print(whatCard(number))


def sumDigitsFromSecondToLastDigit(number, iterations):
    sum = 0
    numcopy = int(number / 10)
    for i in range(iterations):
        n = (numcopy % 10) * 2
        if (numlen(n) == 1):
            sum += n
        else:
            ncopy = str(n)
            for i in range(len(ncopy)):
                sum += int(ncopy[i])
        numcopy = int(numcopy / 100)
    return sum


def sumDigitsFromLastDigit(number, iterations):
    sum = 0
    numcopy2 = number
    for i in range(iterations):
        n = numcopy2 % 10
        sum += n
        numcopy2 = int(numcopy2 / 100)
    return sum


def getFirstTwoDigits(number):
    digits = ""
    n = str(number)
    for i in range(2):
        digits += n[i]
    return digits


def numlen(n):
    numlength = len(str(n))
    return numlength


def isValid(number):
    iterations = math.ceil(numlen(number) / 2)
    checksum = str(sumDigitsFromSecondToLastDigit(number, iterations) +
                   sumDigitsFromLastDigit(number, iterations))
    if int(checksum) % 10 == 0:
        return True
    return False


def whatCard(number):
    digits = getFirstTwoDigits(number)
    if isValid(number):
        if (int(digits[0]) == VISA_START) and (numlen(number) in VISA_LENGTH):
            return "VISA"
        elif (int(digits) in MASTERCARD_START) and (numlen(number) == MASTERCARD_LENGTH):
            return "MASTERCARD"
        elif (int(digits) in AMEX_START) and (numlen(number) == AMEX_LENGTH):
            return "AMEX"
        else:
            return "INVALID"
    else:
        return "INVALID"


main()
