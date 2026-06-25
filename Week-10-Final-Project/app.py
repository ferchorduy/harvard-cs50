import sqlite3

from flask import Flask, request, render_template, redirect, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash


app = Flask(__name__)

app.config["SESSION_PERMAMENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

@app.route("/")
def layout():
    return render_template("layout.html")