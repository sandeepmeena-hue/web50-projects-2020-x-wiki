import csv
from sys import argv, exit

if len(argv) != 3:
    print("missing command line argument")
    exit(1)

m = [0 for i in range(9)]
n = [0 for i in range(9)]

with open(argv[2],"r") as file:
    s = file.read()
    j = 1
    for i in range(0,len(s)):
        if s[i:i + 5] == "AGATC":
            count = 0
            j = i + 5
            while s[j:j + 5] == "AGATC":
                count += 1
                j = j + 5
            if m[1] < count + 1:
                m[1] = count + 1
                n[1] = m[1]
        if s[i:i + 8] == "TTTTTTCT":
            count = 0
            j = i + 8
            while s[j:j + 8] == "TTTTTTCT":
                count += 1
                j = j + 8
            if m[2] < count + 1:
                m[2] = count + 1
        if s[i:i + 4] == "AATG":
            count = 0
            j = i + 4
            while s[j:j + 4] == "AATG":
                count += 1
                j = j + 4
            if m[3] < count + 1:
                m[3] = count + 1
                n[2] = m[3]
        if s[i:i + 5] == "TCTAG":
            count = 0
            j = i + 5
            while s[j:j + 5] == "TCTAG":
                count += 1
                j = j + 5
            if m[4] < count + 1:
                m[4] = count + 1
        if s[i:i + 4] == "GATA":
            count = 0
            j = i + 4
            while s[j:j + 4] == "GATA":
                count += 1
                j = j + 4
            if m[5] < count + 1:
                m[5] = count + 1
        if s[i:i + 4] == "TATC":
            count = 0
            j = i + 4
            while s[j:j + 4] == "TATC":
                count += 1
                j = j + 4
            if m[6] < count + 1:
                m[6] = count + 1
                n[3] = m[6]
        if s[i:i + 4] == "GAAA":
            count = 0
            j = i + 4
            while s[j:j + 4] == "GAAA":
                count += 1
                j = j + 4
            if m[7] < count + 1:
                m[7] = count + 1
        if s[i:i + 4] == "TCTG":
            count = 0
            j = i + 4
            while s[j:j + 4] == "TCTG":
                count += 1
                j = j + 4
            if m[8] < count + 1:
                m[8] = count + 1

with open(argv[1],"r") as csvfile:
    reader = csv.reader(csvfile)
    rows = list(reader)

l = len(rows) - 1
k = len(rows[1])
for i in range(1,l):
    for j in range(1,k):
        if int (rows[i][j]) == m[j] or int (rows[i][j]) == n[j] :
            while True:
                if j == len(rows[1]) - 1:
                    print(rows[i][0])
                    exit(0)
                else:
                    break
        else:
            break

print("No match")











