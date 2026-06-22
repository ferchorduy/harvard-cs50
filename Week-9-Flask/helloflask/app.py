from flask import Flask, request, render_template, redirect

app = Flask(__name__)

VALID_COLORS = ["red", "blue"]

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        return render_template("index.html")
    else:
        color = request.form.get("color")
        if color in VALID_COLORS:
            return render_template("color.html", color=color)
        else:
            return redirect("/")