import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, validate_card_number

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


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
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    net_worth = 0

    portfolio = db.execute("SELECT ticker FROM transactions WHERE user_id = ? GROUP BY ticker HAVING SUM(shares) > 0", user_id)

    for symbol in portfolio:
        symbol["shares"] = db.execute("SELECT sum(shares) AS total_shares FROM transactions WHERE ticker = ? AND user_id = ?", symbol["ticker"], user_id)[0]["total_shares"]
        symbol["price"] = lookup(symbol["ticker"])["price"]
        symbol["investment"] = symbol["shares"] * symbol["price"]
        net_worth += symbol["investment"]

    user_cash_balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    net_worth += user_cash_balance

    return render_template("index.html", portfolio=portfolio, user_cash_balance=user_cash_balance, net_worth=net_worth)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Enter valid share amount")

        if not shares or int(shares) < 1:
            return apology("Enter valid share amount")   
        if not symbol:
            return apology("Enter symbol")
        
        company_data = lookup(symbol)
        if not company_data:
            return apology("Not a valid ticker")
        
        user_id = session["user_id"]
        ticker = company_data["symbol"]
        price = company_data["price"]
        investment = price * shares

        user_cash_balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        if user_cash_balance >= investment:
            new_cash_balance = user_cash_balance - investment
            db.execute("BEGIN TRANSACTION")
            db.execute("INSERT INTO transactions (user_id, ticker, price, shares) VALUES(?, ?, ?, ?)", user_id, ticker, price, shares)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash_balance, user_id)
            db.execute("COMMIT")
            flash("Bought!")
            return redirect("/")
        
        else:
            return apology("Not enough cash")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY timestamp DESC", user_id)
    cash_movements = db.execute("SELECT * FROM cash_movements WHERE user_id = ? ORDER BY timestamp DESC", user_id)
    return render_template("history.html", transactions=transactions, cash_movements=cash_movements)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        flash("Logged in!")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()
    flash("Logged out!")

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        company_data = lookup(symbol)
        
        if not symbol:
            return apology("Enter symbol")
        if not company_data:
            return apology("Not a valid ticker")
        
        return render_template("quoted.html", name=company_data["name"], price=company_data["price"], symbol=company_data["symbol"])

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

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
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password))
            flash("Registered!")
            return redirect("/login")
        except ValueError:
            return apology("USERNAME EXISTS!")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    portfolio = db.execute("SELECT ticker FROM transactions WHERE user_id = ? GROUP BY ticker HAVING SUM(shares) > 0", user_id)

    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Enter valid share amount")

        if not symbol:
            return apology("Enter symbol")
        
        tickers = [row["ticker"] for row in portfolio]
        if symbol not in tickers:
            return apology("You don't own this")
        
        if not shares or int(shares) < 1:
            return apology("Enter valid share amount")
        
        total_shares = db.execute("SELECT sum(shares) AS total_shares FROM transactions WHERE ticker = ? AND user_id = ?", symbol, user_id)[0]["total_shares"]
        if shares > total_shares:
            return apology("You don't have enough stock")
        
        company_data = lookup(symbol)
        price = company_data["price"]
        total_price = price * shares

        user_cash_balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        new_cash_balance = user_cash_balance + total_price

        db.execute("BEGIN TRANSACTION")
        db.execute("INSERT INTO transactions (user_id, ticker, price, shares) VALUES(?, ?, ?, ?)", user_id, symbol, price, -shares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash_balance, user_id)
        db.execute("COMMIT")
        flash("Sold!")

        return redirect("/")
    
    return render_template("sell.html", portfolio=portfolio)

@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """Add funds to account"""
    if request.method == "POST":
        card_number = request.form.get("card_number")
        try:
            deposit = round(float(request.form.get("deposit")), 2)
        except ValueError:
            return apology("Enter deposit in valid format")
        
        if not card_number.isdigit():
            return apology("Enter valid card number")
        
        if not deposit or deposit < 0:
            return apology("Enter valid deposit amount")

        if validate_card_number(str(card_number)):
            user_id = session["user_id"]

            db.execute("BEGIN TRANSACTION")
            db.execute("INSERT INTO cash_movements (user_id, movement_type, amount) VALUES(?, ?, ?)", user_id, 'deposit', deposit)
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", deposit, user_id)
            db.execute("COMMIT")
            flash("Deposited!")
            return redirect("/")
        
        else:
            return apology("Invalid card number")

    return render_template("deposit.html")