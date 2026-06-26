import sqlite3

from flask import Flask, flash, request, render_template, redirect, session, g
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, to_local

# Configure application
app = Flask(__name__)

# Timestamp filter
app.jinja_env.filters["to_local"] = to_local

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# SQLite connection
def get_db():
    if "db" not in g:
        g.db = sqlite3.connect("orduylap.db")
        g.db.row_factory = sqlite3.Row
    return g.db

@app.teardown_appcontext
def close_db(exception):
    db = g.pop("db", None)
    if db is not None:
        db.close()


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
    # Start new session button
    # Last session recap
    # This week toal data maybe? Streak indicator?
    # For new users, not empty, but start first session UI

    return apology("To do")


@app.route("/workout")
@login_required
def workout():
    """Page to start workout session"""
    return render_template("workout.html")


@app.route("/exercises")
@login_required
def exercises():
    """Add exercises to the list"""
    return apology("To do")


@app.route("/records")
@login_required
def records():
    """Shows historical records and data"""
    return apology("To do")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register a new user"""

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("PLEASE INPUT A USERNAME!")
        
        if not password:
            return apology("PLEASE INPUT A PASSWORD!")
        
        if not confirmation:
            return apology("PLEASE CONFIRM PASSWORD!")
        
        if password != confirmation:
            return apology("PASSWORDS DO NOT MATCH!")
        
        try:
            orduylap = get_db()
            orduylap_db = orduylap.cursor()
            orduylap_db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", (username, generate_password_hash(password)))
            orduylap.commit()
            flash("Registered!")
            return redirect("/login")
        except sqlite3.IntegrityError:
            return apology("USERNAME EXISTS!")
        
    else:
        return render_template("register.html")


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
        orduylap = get_db()
        orduylap_db = orduylap.cursor()
        rows = orduylap_db.execute(
            "SELECT * FROM users WHERE username = ?", (username,)
        ).fetchall()

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