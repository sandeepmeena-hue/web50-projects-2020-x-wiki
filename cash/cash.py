from cs50 import get_float

def main():
    n = get_positive_int()
    noofcoin(n)

def get_positive_int():
    while(True):
        m = get_float("change owed: ")
        if m > 0:
            break
    return m

def noofcoin(n):
    x = round(n * 100)
    count = 0
    while(x > 0):
        if x >= 25:
            x -= 25
            count += 1
        elif x >= 10:
            x -= 10
            count += 1
        elif x >= 5:
            x -= 5
            count += 1
        else:
            x -= 1
            count += 1

    print(count)

main()
