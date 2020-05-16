import re
from cs50 import get_int, get_string

def main():
    n = get_int("NUMBER:")
    s = get_string("number:")
    if check(n) == False:
        print("INVALID ")
    else:
        type(n,s)


def noofdig(n):
    count = 0
    while n >= 10:
        n = n / 10
        count += 1

    return count + 1


def check(n):
    sum1 = 0
    sum2 = 0
    x = noofdig(n)
    for i in range(0,x,2):
        y = n
        for j in range(i + 1):
            y = y // 10
        m = y % 10
        if m * 2 >= 10:
            sum1 += (m * 2) // 10 + (m * 2) % 10
        else:
            sum1 += m*2

    for k in range(0,x,2):
        y = n
        for l in range(0,k):
            y = y // 10
        m = y % 10
        sum2 += m

    if (sum1 + sum2) % 10 == 0:
        return True
    else:
        return False

def type(n,s):
    if noofdig(n) == 15:
        if re.search("^34(.*)$",s) or re.search("^37(.*)$",s):
            print("AMEX\n")
    elif noofdig(n) == 16:
        if re.search("^5(.*)$",s):
            print("MASTERCARD\n")
        elif re.search("^4(.*)$",s):
            print("VISA\n")
        else:
            print("INVALID\n")
    elif noofdig(n) == 13:
        if re.search("^4(.*)$",s):
            print("VISA\n")
    else:
        print("INVALID\n")

main()
