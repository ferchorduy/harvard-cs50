import sqlite3

from flask import Flask, flash, request, render_template, redirect, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, to_local

# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMAMENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# SQLite connection
orduylap = sqlite3.connect("orduylap.db")
orduylap_db = orduylap.cursor()

# Timestamp filter
app.jinja_env.filters["to_local"] = to_local

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Home page"""
    return apology("To do")


@app.route("/workout")
@login_required
def workout():
    """ """
    return render_template("workout.html")


@app.route("/exercises")
@login_required
def exercises():
    """ """
    return apology("To do")


@app.route("/records")
@login_required
def records():
    """ """
    return apology("To do")


@app.route("/register")
def register():
    """ """
    return apology("To do")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        # Ensure username and password were submitted
        if not username:
            return apology("Must provide username", 403)
        elif not password:
            return apology("Must provide password", 403)
        
        # Query database for username
        rows = orduylap_db.execute(
            "SELECT username FROM users WHERE username = ?", username
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
            return apology("invalid username and/or password", 403)
        
        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        flash("Logged in!")

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("login.html")
    
@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")