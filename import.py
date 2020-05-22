from sys import argv, exit
import csv
import cs50

if len(argv) != 2:
    print("missing command line argument")
    exit(1)

open(f"students.db","w").close()
db = cs50.SQL("sqlite:///students.db")

db.execute("CREATE TABLE students( first VARCHAR(255), middle VARCHAR(255), last VARCHAR(255), house VARCHAR(10), birth INTEGER)")

with open("characters.csv","r") as table:

    reader = csv.DictReader(table)

    for row in reader:

        if len(row["name"].split(" ")) == 2:
            middle = "NULL"
            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", row["name"].split(" ")[0], middle, row["name"].split(" ")[1], row["house"], row["birth"])
        else:
            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", row["name"].split(" ")[0], row["name"].split(" ")[1], row["name"].split(" ")[2], row["house"], row["birth"])


