import requests
import re
import pytz

from flask import redirect, render_template, session
from functools import wraps
from datetime import datetime


def apology(message, code=400):
    """Render message as an apology to user."""

    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/latest/patterns/viewdecorators/
    """

    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)

    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""
    url = f"https://finance.cs50.io/quote?symbol={symbol.upper()}"
    try:
        response = requests.get(url)
        response.raise_for_status()  # Raise an error for HTTP error responses
        quote_data = response.json()
        return {
            "name": quote_data["companyName"],
            "price": quote_data["latestPrice"],
            "symbol": symbol.upper()
        }
    except requests.RequestException as e:
        print(f"Request error: {e}")
    except (KeyError, ValueError) as e:
        print(f"Data parsing error: {e}")
    return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"

# Checksum.
def luhn(card_number):

    card_number = int(card_number)
    normal_sum = 0
    doubled_sum = 0
    counter = 0

    while card_number != 0:
        if counter % 2 == 0:
            normal_sum += card_number % 10
            card_number //= 10
            counter += 1
        else:
            temp_sum = (card_number % 10) * 2
            if temp_sum > 9:
                temp_sum -= 9
            doubled_sum += temp_sum
            card_number //= 10
            counter += 1

    return (normal_sum + doubled_sum) % 10 == 0


def validate_card_number(card_number):

    # Get card number length.
    card_number_length = len(card_number)

    if (not luhn(card_number)): return False
    elif card_number[:2] in ["34", "37"] and card_number_length == 15: return True
    elif card_number[:1] == "4" and (card_number_length == 13 or card_number_length == 16): return True
    elif card_number_length == 16 and re.match("5[12345]", card_number): return True
    else: return False


def to_local(utc_timestamp_str, timezone="America/New_York"):
    utc_dt = datetime.strptime(utc_timestamp_str, "%Y-%m-%d %H:%M:%S")
    utc_dt = pytz.utc.localize(utc_dt)
    local_dt = utc_dt.astimezone(pytz.timezone(timezone))
    return local_dt.strftime("%Y-%m-%d %I:%M %p")