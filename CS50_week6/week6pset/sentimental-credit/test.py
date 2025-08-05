import math

def main():
    sum = 0
    sum2 = 0
    number = 4222222222222
    numcopy = int(number / 10)
    numcopy2 = number
    iterations = math.ceil(numlen(number) / 2)
    for i in range(iterations):
        n = (numcopy % 10) * 2
        if (numlen(n) == 1):
            sum += n
        else:
            ncopy = str(n)
            for i in range(len(ncopy)):
                sum += int(ncopy[i])
        numcopy = int(numcopy / 100)
    for i in range(iterations):
        n = numcopy2 % 10
        sum2 += n
        numcopy2 = int(numcopy2 / 100)
    print(sum)
    print(sum2)

def numlen(n):
    numlength = len(str(n))
    return numlength


main()
