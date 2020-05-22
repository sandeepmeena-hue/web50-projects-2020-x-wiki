from sys import exit, argv
import cs50

if len(argv) !=2:
    print("missing command line argument")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

rows = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first",argv[1])
count = db.execute("SELECT COUNT(first) FROM students WHERE house = ?",argv[1])


m = int(count[0]['COUNT(first)'])

for i in range(m):
    if rows[i]["middle"] == 'NULL':
        print(f"{rows[i]['first']} {rows[i]['last']}, born {rows[i]['birth']}")
    else:
        print(f"{rows[i]['first']} {rows[i]['middle']} {rows[i]['last']}, born {rows[i]['birth']}")
