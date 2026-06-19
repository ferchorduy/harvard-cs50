import csv
import sqlite3

prophecy = sqlite3.connect('prophecy.db')
prophecy_db = prophecy.cursor()
prophecy_db.executescript("""                 
    CREATE TABLE IF NOT EXISTS students (
        id INTEGER,
        student_name TEXT,
        PRIMARY KEY(id)
    );

    CREATE TABLE IF NOT EXISTS houses (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        house TEXT UNIQUE,
        head TEXT
    );

    CREATE TABLE IF NOT EXISTS assignments (
        student_id INTEGER,
        house_id INTEGER,
        FOREIGN KEY(student_id) REFERENCES students(id),
        FOREIGN KEY(house_id) REFERENCES houses(id)
    );
""")

with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        prophecy_db.execute(
            "INSERT OR IGNORE INTO students VALUES (?, ?)",
            (row['id'], row['student_name'])
        )
        prophecy_db.execute(
            "INSERT OR IGNORE INTO houses (house, head) VALUES (?, ?)",
            (row['house'], row['head'])
        )
        house = prophecy_db.execute(
            "SELECT id FROM houses WHERE house = ?",
            (row['house'],)
        ).fetchone()
        prophecy_db.execute(
            "INSERT OR IGNORE INTO assignments (student_id, house_id) VALUES (?, ?)",
            (row['id'], house[0])
        )
    prophecy.commit()


roster = sqlite3.connect('roster.db')
roster_db = roster.cursor()
roster_db.executescript("""                 
    CREATE TABLE IF NOT EXISTS houses (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        house TEXT UNIQUE,
        head TEXT
    );

    CREATE TABLE IF NOT EXISTS assignments (
        student_id INTEGER,
        house_id INTEGER,
        FOREIGN KEY(student_id) REFERENCES students(id),
        FOREIGN KEY(house_id) REFERENCES houses(id)
    );
""")
students = roster_db.execute("SELECT * FROM students").fetchall()

if len(students[0]) > 2:
    for student in students:
        roster_db.execute(
            "INSERT OR IGNORE INTO houses (house, head) VALUES (?, ?)",
            (student[2], student[3])
        )
        house = roster_db.execute(
            "SELECT id FROM houses WHERE house = ?",
            (student[2],)
        ).fetchone()
        roster_db.execute(
            "INSERT OR IGNORE INTO assignments (student_id, house_id) VALUES (?, ?)",
            (student[0], house[0])
        )

try:
    roster_db.executescript("""
        ALTER TABLE students DROP COLUMN house;
        ALTER TABLE students DROP COLUMN head;
    """)
except sqlite3.OperationalError:
    pass

roster.commit()