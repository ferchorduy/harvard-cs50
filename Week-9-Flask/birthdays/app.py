import os
import sqlite3

from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


def get_db():
    connection = sqlite3.connect('birthdays.db')
    connection.row_factory = sqlite3.Row
    return connection


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    db = get_db()
    cursor = db.cursor()

    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        if not name or not month or not day:
            return redirect("/")

        try:
            month = int(month)
            day = int(day)
        except ValueError:
            return redirect("/")
        
        if month < 1 or month > 12:
            return redirect("/")

        if day < 1 or day > 31:
            return redirect("/")

        cursor.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", (name, month, day))
        db.commit()
        db.close()

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        rows = cursor.execute("SELECT * FROM birthdays").fetchall()
        db.close()

        return render_template("index.html", rows=rows)


