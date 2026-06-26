import requests
import re
import pytz

from flask import redirect, render_template, session
from functools import wraps
from datetime import datetime


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


def apology(message, code=400):
    """Render message as an apology to user."""

    return render_template("apology.html", code=code, message=message), code


def to_local(utc_timestamp_str, timezone="America/New_York"):
    utc_dt = datetime.strptime(utc_timestamp_str, "%Y-%m-%d %H:%M:%S")
    utc_dt = pytz.utc.localize(utc_dt)
    local_dt = utc_dt.astimezone(pytz.timezone(timezone))
    return local_dt.strftime("%Y-%m-%d %I:%M %p")