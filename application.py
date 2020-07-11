import os
from datetime import datetime
import pytz

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    ids = db.execute("SELECT DISTINCT(id) FROM purchase")
    maxid = db.execute("SELECT MAX(id) FROM purchase")
    for i in ids:
        if x != i["id"]:
            if i["id"] == maxid[0]["MAX(id)"]:
                y = "yes"
                total= 10000.00
                return render_template("index.html", ids = ids, total = total, y = y)
        else:
            y = "no"
            rows = db.execute("SELECT * FROM purchase WHERE purchase_Id = (SELECT MAX(purchase_Id) FROM purchase WHERE id = ?)", x)
            detail = lookup(rows[0]["symbol"])
            name = detail["name"]
            total = round(((rows[0]["share"]) * rows[0]["price"]) + rows[0]["cash"], 2)
            rows[0]["cash"] = round(rows[0]["cash"], 2)
            cost = round(rows[0]["share"] * rows[0]["price"], 2)
            return render_template("index.html", rows = rows, name = name, total = total, cost = cost, y = y)
            break

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("company's symbol Not Found", 400)
        share = request.form.get("share")
        if not share:
            return apology("share not found", 400)
        rows = lookup(symbol)
        if rows == None:
            return apology("Symbol Not Found", 400)
        price = db.execute("SELECT cash from users WHERE id = ?", x)
        if price[0]["cash"] < int (share) * rows["price"]:
            return apology("NOT Enough Money To Purchase", 403)
        cashrem = round(price[0]["cash"] - int (share) * rows["price"], 2);
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cashrem, x)
        tz_IN = pytz.timezone("ASIA/KOLKATA")
        now = datetime.now(tz_IN)
        dt_str = now.strftime("%d/%m/%Y %H:%M:%S")
        db.execute("INSERT INTO purchase (symbol, share, cash, time, price, purtype, id) VALUES (?, ?, ?, ?, ?, ?, ?)", symbol, share, cashrem, dt_str, rows['price'], "bought", x)
        return redirect("/")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM purchase WHERE id = ?", x)
    return render_template("history.html", rows = rows)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        global x
        x = session["user_id"]

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

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if lookup(symbol) == None:
            return apology("NOT FOUND", 400)
        else:
            rows = lookup(symbol)
            return render_template("quoted.html", rows = rows)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        name = request.form.get("username")
        if not name:
            return apology("must provide username", 403)
        password  = request.form.get("password")
        if not password:
            return apology("must provide password", 403)
        confirm_password = request.form.get("confirm password")
        if not confirm_password:
            return apology("Please confirm password", 403)
        if password != confirm_password:
            return apology("confirm password does not match", 403)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", name, generate_password_hash(password))
        return redirect('/login')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        return render_template("sell.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Symbol Not Found", 400)
        shares = request.form.get("shares")
        if not shares:
            return apology("Shares Not Found",400)
        rows = lookup(symbol)
        if rows == None:
            return apology("Symbol Not Found", 400)
        bousha = db.execute("SELECT SUM(share) FROM purchase WHERE symbol = ? AND purtype='bought' AND id = ?", symbol, x)
        selsha = db.execute("SELECT SUM(share) FROM purchase WHERE symbol= ? AND purtype='sold' AND id = ?", symbol, x)
        if bousha[0]["SUM(share)"] == None:
            return apology("NOT ENOUGH SHARES TO SOLD", 403)
        elif selsha[0]["SUM(share)"] == None:
            m = bousha[0]["SUM(share)"]
        else:
            m = bousha[0]["SUM(share)"] - selsha[0]["SUM(share)"]
        if  m < int(shares):
            return apology("NOT ENOUGH SHARES TO SOLD", 403)
        detail = lookup(symbol)
        curcash = db.execute("SELECT cash FROM users WHERE id = ?", x)
        udtcash = round(detail["price"] + curcash[0]["cash"], 2)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", udtcash, x)
        tz_IN = pytz.timezone("ASIA/KOLKATA")
        now = datetime.now(tz_IN)
        dt_str = now.strftime("%d/%m/%Y %H:%M:%S")
        db.execute("INSERT INTO purchase (symbol, share, cash, time, price, purtype, id) VALUES (?, ?, ?, ?, ?, ?, ?)", symbol, int (shares), udtcash, dt_str, detail["price"], "sold", x)
        return redirect("/")

@app.route("/password_change", methods=["GET", "POST"])
def pass_chg():
    if request.method == "GET":
        return render_template("pass_chg.html")
    else:
        rows = db.execute("SELECT * FROM users WHERE username = :username",username=request.form.get("username"))
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("old_password")):
            return apology("invalid username and/or password", 403)
        new_password = request.form.get("new_password")
        confirm_password = request.form.get("confirm_password")
        if not confirm_password and new_password and confirm_password == new_password:
            return apology("ENTER VALID PASSWORD",403)
        db.execute("UPDATE users SET hash=? WHERE username = ?", generate_password_hash(new_password), request.form.get("username"))
        return redirect("/login")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
