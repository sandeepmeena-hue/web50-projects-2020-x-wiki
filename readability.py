from cs50 import get_string

s = get_string("Text:")

def main():
    calcwls(s)

def calcwls(s):
    letter = 0
    word = 0
    sentence = 0
    for i in s:
        if i.isalpha() == True:
            letter += 1
        elif i == " ":
            word += 1
        elif i == "." or i == "!" or i == "?":
            sentence += 1
        else:
            continue

    l = (letter / (word + 1)) * 100
    s = (sentence / (word + 1)) * 100
    g = round(0.0588 * l - 0.296 * s - 15.8)

    if g < 1:
        print("Before Grade 1")
    elif g > 16:
        print("Grade 16+")
    else:
        print(f"Grade {g}")

main()

