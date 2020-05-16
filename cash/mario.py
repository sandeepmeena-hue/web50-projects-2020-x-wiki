from cs50 import get_int

def main():
    n = get_positive_int()
    pattern(n)

def get_positive_int():
    while(True):
        m = get_int("height:")
        if m > 0 and m < 9:
            break
    return m

def pattern(n):
    for i in range(n):
        for j in range(n):
            if i+j >= n-1:
                print("#",end="")
            else:
                print(" ",end="")
        print()

main()
