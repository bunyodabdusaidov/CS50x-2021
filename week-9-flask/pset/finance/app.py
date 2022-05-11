import os
import sys
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
#from getters import get_stocks, get_transactions, get_portfolio, get_cash, get_total

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


def get_stocks(transactions):
    stocks = set()
    for item in transactions:
        for key, value in item.items():
            if key == "symbol":
                stocks.add(value)
    return list(stocks)


def get_transactions(user_id):
    transactions = db.execute("SELECT id, type, symbol, company, shares, filled_price, filled_time FROM transactions WHERE user_id=(?)", user_id)
    return transactions


def get_portfolio(transactions, stocks):
    portfolio = []
    for name in stocks:
        shares = 0
        stock = {}
        for trn in transactions:
            if name in stock.values():
                if trn["type"] == "buy":
                    shares += trn["shares"]
                else:
                    shares -= trn["shares"]
            else:
                shares = trn["shares"]
                stock["symbol"] = name

        price = lookup(name)["price"]

        if shares <= 0:
            shares = 0

        else:
            value = price * shares

            stock["company"] = lookup(name)["name"]
            stock["price"] = price
            stock["shares"] = shares
            stock["value"] = value
            portfolio.append(stock)

    return portfolio


def get_cash(user_id):
    cash = db.execute("SELECT cash FROM users WHERE id=(?)", user_id)[0]['cash']
    return cash


def get_total(cash, portfolio):
    total = cash
    for stock in portfolio:
        total += stock["value"]

    return total


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session['user_id']
    transactions = get_transactions(user_id)
    stocks = get_stocks(transactions)
    portfolio = get_portfolio(transactions, stocks)
    cash = get_cash(user_id)
    total = get_total(cash, portfolio)

    return render_template("index.html", portfolio=portfolio, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        if lookup(symbol):
            company = lookup(symbol)["name"]
            shares = request.form.get("shares")
        else:
            return apology("Invalid stock symbol", 400)

        try:
            if int(shares) < 0:
                return apology("Must provide positive number for shares")
        except ValueError:
            return apology("Must provide valid number for shares", 400)

        price = lookup(symbol)["price"]
        filled_price = price * float(shares)
        filled_time = datetime.now()

        user_id = session['user_id']
        users_cash = float(db.execute("SELECT cash FROM users WHERE id=(?)", user_id)[0]['cash'])
        if users_cash < filled_price:
            return apology("Not enough funds", 403)

        db.execute("INSERT INTO transactions (type, symbol, company, shares, filled_price, filled_time, user_id)"
                   "VALUES (?)", ("buy", symbol, company, float(shares), filled_price, filled_time, user_id))

        users_cash_after_purchase = users_cash - filled_price
        db.execute("UPDATE users SET cash=? WHERE id=?", users_cash_after_purchase, user_id)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = get_transactions(user_id)
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
        symbol = request.form.get("symbol")
        if symbol:
            if lookup(symbol):
                return render_template("quoted.html", symbol=lookup(symbol))
            else:
                return apology("Invalid stock symbol", 400)
        else:
            return apology("Must provide stock symbol", 400)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        usernames = db.execute("SELECT username FROM users")
        username_list = []
        for username in usernames:
            username_list.append(username["username"])

        if not name:
            return apology("must provide username", 400)
        if not password:
            return apology("must provide password", 400)
        if not confirmation:
            return apology("must provide password confirmation", 400)
        if name in username_list:
            return apology("this username already exists", 400)
        if password != confirmation:
            return apology("passwords must match", 400)
        else:
            db.execute("INSERT INTO users (username, hash) VALUES(?,?)", name, generate_password_hash(password))
            return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session['user_id']
    transactions = get_transactions(user_id)
    stocks = get_stocks(transactions)
    portfolio = get_portfolio(transactions, stocks)
    stocks_and_shares = {}
    for i in range(len(stocks)):
        if stocks[i] == portfolio[i]["symbol"]:
            stocks_and_shares[stocks[i]] = portfolio[i]["shares"]

    if request.method == "POST":
        stock = request.form.get("symbol")
        shares = request.form.get("shares")
        company = lookup(stock)["name"]
        filled_price = float(shares) * lookup(stock)["price"]
        filled_time = datetime.now()
        users_cash = get_cash(user_id)

        max_stock = stocks_and_shares[stock]
        if float(shares) > max_stock:
            return apology("Not enough stocks!", 400)

        else:
            db.execute("INSERT INTO transactions (type, symbol, company, shares, filled_price, filled_time, user_id) "
                       "VALUES (?)", ("sell", stock, company, float(shares), filled_price, filled_time, user_id))

            users_cash_after_purchase = users_cash + filled_price
            db.execute("UPDATE users SET cash=? WHERE id=?", users_cash_after_purchase, user_id)

            return redirect("/")

    else:
        return render_template("sell.html", stocks_and_shares=stocks_and_shares)
