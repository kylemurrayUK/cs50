import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
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
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0]
    cash = cash['cash']
    portfolio = db.execute("SELECT symbol,  SUM(shares)FROM transactions WHERE id = ? GROUP BY symbol;", session["user_id"])
    results = []
    row = []
    sumtotal = 0
    for i in range(len(portfolio)):
        row = []
        symbol = portfolio[i - 1]['symbol']
        row.append(symbol)
        name = lookup(symbol)
        name = name['name']
        row.append(name)
        shares = portfolio[i - 1]['SUM(shares)']
        row.append(shares)
        price = lookup(symbol)
        price = price['price']
        row.append(price)
        total = price * shares
        sumtotal += total
        row.append(total)
        results.append(row)

    return render_template("index.html", cash=cash, sumtotal=sumtotal, results=results)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        company = request.form.get("symbol")
        if lookup(company) == None:
            return apology("Invalid Symbol")
        else:
            companyinfo = lookup(company)
            amount = request.form.get("shares")
            if amount.isdigit() == False:
                return apology("Must be none decimal")
            total = float(companyinfo['price']) * int(amount)
            currentbalance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            if amount == '':
                return apology("Must have a share amount")
            if total > int(currentbalance[0]['cash']):
                return apology("Can't Afford")
            if int(float(amount)) % 1 != 0:
                return apology("Cannot accept decimals.")
            if int(float(amount)) < 0:
                return apology("Cannot accept negative numbers")
            if amount.isnumeric() == False:
                return apology("Need to input a number")
            db.execute("INSERT INTO transactions(id, shares, price, symbol, time) VALUES(?, ?, ?, ?, CURRENT_TIMESTAMP)",
                       session["user_id"], amount, round(total, 2), companyinfo['symbol'])
            db.execute("UPDATE users SET cash = ? WHERE id = ?", round(
                (int(currentbalance[0]['cash']) - total), 2), session["user_id"])
            flash("Bought!")
            return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT symbol, shares, price, time FROM transactions WHERE id= ?", session["user_id"])
    return render_template("history.html", transactions=transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

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
        company = request.form.get("symbol")
        if lookup(company) == None:
            return apology("Invalid Symbol")
        else:
            companyinfo = lookup(company)
            return render_template("quoted.html", companyinfo=companyinfo)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("registration.html")
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        usernamecheck = db.execute("SELECT * FROM users WHERE username = ?", username)
        if not request.form.get("username"):
            return apology("Username cannot be blank.")
        if not request.form.get("password"):
            return apology("Password cannot be blank.")
        if not request.form.get("confirmation"):
            return apology("Password cannot be blank.")
        if len(request.form.get("password")) < 8:
            return apology("The password must be at least 8 characters long.")
        if request.form.get("password").isalpha() == True:
            return apology("Must contain at least one number.")
        if request.form.get("password").isalnum() == True:
            return apology("Must contain at least one special character.")
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords must match up.")
        elif len(usernamecheck) > 0:
            return apology("Username already in use")
        else:
            unhashedpassword = request.form.get("password")
            password = generate_password_hash(unhashedpassword)
            db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", username, password)
            return render_template("login.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        stocks = db.execute("SELECT symbol FROM transactions WHERE id = ? GROUP BY symbol;", session["user_id"])
        return render_template("sell.html", stocks=stocks)
    else:
        company = request.form.get("symbol")
        company = lookup(company)
        amount = request.form.get("shares")
        if amount == '':
            return apology("Must have a share amount")
        shareamount = db.execute(
            "SELECT SUM(shares) FROM transactions WHERE id = ? AND symbol = ? GROUP BY symbol;", session["user_id"], company['symbol'])
        shareamount = shareamount[0]['SUM(shares)']
        if int(amount) > shareamount:
            return apology("Too many shares")
        total = float(company['price']) * int(amount)
        currentbalance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        db.execute("INSERT INTO transactions(id, shares, price, symbol, time) VALUES(?, ?, ?, ?, CURRENT_TIMESTAMP)", session["user_id"],
                   (0 - int(amount)), round(total, 2), company['symbol'])
        db.execute("UPDATE users SET cash = ? WHERE id = ?", round((int(currentbalance[0]['cash']) + total), 2), session["user_id"])
        flash("Sold!")
        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
