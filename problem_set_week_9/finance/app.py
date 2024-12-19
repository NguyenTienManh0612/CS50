import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, gettime

# Configure application
app = Flask(__name__)
app.secret_key = "4f92f8db8c5a4c9bb76e874c879f12ab"

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
    totalCash = cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    portfolioTable = db.execute("SELECT symbol, SUM(shares), price FROM purchases WHERE user_id = ? GROUP BY symbol", session["user_id"])

    for purchase in portfolioTable:
        totalCash += purchase["SUM(shares)"] * purchase["price"]

    return render_template("index.html", portfolioTable=portfolioTable, totalCash=totalCash, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol", 400)
        elif not lookup(symbol):
            return apology("symbol does not exist", 400)

        if not shares:
            return apology("must provide number of shares", 400)
        if not shares.isdigit() or int(shares) <= 0:
            return apology("invalid shares, must be a positive integer", 400)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        if not cash:
            return apology("user not found", 400)
        newBalance = cash[0]["cash"] - (int(shares) * lookup(symbol).get("price"))

        if newBalance <= 0:
            return apology("cannot afford", 400)
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", newBalance, session["user_id"])
            db.execute("INSERT INTO purchases (user_id, symbol, shares, price, purchase_date) VALUES(?,?,?,?,?)",
                       session["user_id"], symbol, shares, lookup(symbol).get("price"), gettime())

            flash("Bought!")
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    table = db.execute("SELECT symbol, shares, price, purchase_date FROM purchases WHERE user_id=? ORDER BY purchase_date DESC", session["user_id"])

    return render_template("history.html", table=table)


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

        # Redirect user to home page
        flash("Log In!")
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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("missing symbol", 400)
        elif not lookup(symbol):
            return apology("invalid symbol", 400)
        return render_template("quoted.html", getStockInfo=lookup(symbol))
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username:
            return apology("must provide username", 400)
        elif not password:
            return apology("must provide password", 400)
        elif confirmation != password:
            return apology("passwords do not match", 400)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?,?)", username, generate_password_hash (
                            password, method='scrypt', salt_length=16
                        ))
        except ValueError:
            return apology("this username already exists", 400)
        flash("Registered!")
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    table = db.execute("SELECT symbol, SUM(shares), price FROM purchases WHERE user_id = ? GROUP BY symbol", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    if request.method == "POST":
        shares = request.form.get("shares")
        symbol = request.form.get("symbol")
        if not shares:
            return apology("Invalid shares of stock", 400)

        if not symbol:
            return apology("must select symbol", 400)
        for purchase in table:
            if symbol == purchase["symbol"]:
                if int(shares) > purchase["SUM(shares)"]:
                    return apology("not enough shares", 400)
                newCash = cash + (int(shares)*purchase["price"])
                db.execute("UPDATE users SET cash = ? WHERE id = ?", newCash, session["user_id"])
                db.execute("INSERT INTO purchases (user_id, symbol, shares, price, purchase_date) VALUES(?, ?, ?, ?, ?)",
                        session["user_id"], symbol, -int(shares), purchase["price"], gettime())

        flash("Sold!")
        return redirect("/")
    else:
        return render_template("sell.html", table=table)
