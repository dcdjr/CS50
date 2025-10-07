import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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

    # Gets necessary info from the database
    rows = db.execute("SELECT symbol, SUM(shares) FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
    user_info = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

    # Initializes cash and portfolio_value variables for readability
    available_cash = user_info[0]["cash"]
    portfolio_value = available_cash

    # Initializes list to hold dictionaries containing stock information
    stocks = []
    for i in range(len(rows)):
        # for each stock, appends a dictionary including its symbol, current price, and name
        stocks.append(lookup(rows[i]["symbol"]))

        # Initializes temp variables to not interefere with calculations when formatting with usd
        temp_num_shares = int(rows[i]["SUM(shares)"])
        temp_price = stocks[i]["price"]

        # Adds important info to each stock's dictionary in stocks, including the number of shares
        # the user holds, the usd formatted total value of each holding of the stock, and the
        # usd formatted price.
        stocks[i]["num_shares"] = temp_num_shares
        stocks[i]["total_value"] = usd(temp_num_shares * temp_price)
        stocks[i]["price"] = usd(temp_price)

        # Adds the total value of each holding of the stock to the portfolio value, initialized
        # to the available_cash the user has
        portfolio_value += temp_num_shares * temp_price

    # Returns the
    return render_template("index.html", stocks=stocks, available_cash=usd(available_cash), portfolio_value=usd(portfolio_value))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # If user submits data via POST
    if request.method == "POST":

        # Get stock symbol from form
        stock_symbol = request.form.get("symbol")
        if not stock_symbol:
            return apology("Enter a valid stock symbol.")

        # Lookup stock
        stock_quote = lookup(stock_symbol)
        if stock_quote is None:
            return apology("Enter a valid stock symbol.")

        # Try to get number of shares as int
        try:
            num_shares = int(request.form.get("shares"))
        except (ValueError, TypeError):
            return apology("Enter a valid number of shares.")

        # If number of shares <= 0
        if num_shares <= 0:
            return apology("Enter a valid value.")

        # Initialize variables for calculations
        stock_price = stock_quote["price"]
        purchase_price = round(stock_price * num_shares, 2)
        current_user_id = session["user_id"]
        transaction_type = "BUY"

        # Query database for user's data
        rows = db.execute("SELECT * FROM users WHERE id = ?", current_user_id)
        available_cash = rows[0]["cash"]

        # Check affordability
        if available_cash < purchase_price:
            return apology("You do not have enough cash for this purchase.")

        # Insert transaction into transactions table
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, ?)",
            current_user_id, stock_symbol, num_shares, stock_price, transaction_type
        )

        # Update user's cash
        updated_cash = available_cash - purchase_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_cash, current_user_id)

        # Redirect to portfolio
        return redirect("/")

    else:
        return render_template("request_buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("SELECT type, symbol, price, shares, time FROM transactions WHERE user_id = ?", session["user_id"])
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

    # If user submitted data via POST
    if request.method == "POST":
        # Lookup the desired stock
        stock_quote = lookup(request.form.get("symbol"))

        # If lookup was unsuccessful, return apology
        if stock_quote == None:
            return apology("Stock doesn't exist.", 400)

        # If lookup was successful, display information on stock
        return render_template("return_quote.html", stock_name=stock_quote["name"], stock_price=usd(stock_quote["price"]), stock_symbol=stock_quote["symbol"])

    # If user request page via GET
    else:
        return render_template("request_quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # If user submitted data through POST
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password was confirmed
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        # Ensure passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Query database for usernames
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username doesn't exist
        if len(rows) != 0:
            return apology("user already exists", 400)

        # If everything is valid, insert user into users table
        new_user_id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

        # Log user in
        session["user_id"] = new_user_id

        # Redirect new user to homepage
        return redirect("/")

    # If user requested page through GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

        # If user submits data via POST
    if request.method == "POST":

        rows = db.execute("SELECT symbol, SUM(shares) FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
        user_info = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        stocks = []
        for i in range(len(rows)):
            stocks.append(lookup(rows[i]["symbol"]))

        # Get stock symbol from form
        stock_symbol = request.form.get("symbol")
        if not stock_symbol:
            return apology("Enter a valid stock symbol.")

        # Lookup stock
        stock_quote = lookup(stock_symbol)
        if stock_quote is None:
            return apology("Enter a valid stock symbol.")

        # Try to get number of shares as int
        try:
            num_shares = int(request.form.get("shares"))
        except (ValueError, TypeError):
            return apology("Enter a valid number of shares.")

        # If number of shares <= 0 or > number of shares that user owns, return an apology
        if num_shares <= 0:
            return apology("Enter a valid value.")

        for i in range(len(rows)):
            if num_shares > rows[i]["SUM(shares)"] and rows[i]["symbol"] == stock_symbol:
                return apology("enter a valid number of shares.")

        # Initialize variables for calculations
        stock_price = stock_quote["price"]
        sell_price = round(stock_price * num_shares, 2)
        current_user_id = session["user_id"]
        transaction_type = "SELL"

        # Insert transaction into transactions table
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, ?)",
            current_user_id, stock_symbol, -1 * num_shares, stock_price, transaction_type
        )

        # Update user's cash
        available_cash = user_info[0]["cash"]
        updated_cash = available_cash + sell_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_cash, current_user_id)

        # Redirect to portfolio
        return redirect("/")

    else:
        rows = db.execute("SELECT symbol, SUM(shares) FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
        user_info = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        stocks = []
        for i in range(len(rows)):
            stocks.append(lookup(rows[i]["symbol"]))
            stocks[i]["num_shares"] = rows[i]["SUM(shares)"]

        return render_template("sell.html", stocks=stocks)

@app.route("/change", methods=["GET", "POST"])
@login_required
def change():
    """Allow users to change their password"""
    if request.method == "POST":

        # Ensure password was submitted
        if not request.form.get("current_password"):
            return apology("must provide current password", 400)

        # Ensure new password was submitted
        elif not request.form.get("new_password"):
            return apology("must provide new password", 400)

        # Ensure new password was confirmed
        elif not request.form.get("confirmed_new_password"):
            return apology("must confirm new password", 400)

        # Ensure new password and confirm password fields match
        elif request.form.get("new_password") != request.form.get("confirmed_new_password"):
            return apology("new password and confirm password fields must match", 400)

        # Query database for user info
        rows = db.execute(
            "SELECT * FROM users WHERE id = ?", session["user_id"]
        )

        # Ensure password exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("current_password")
        ):
            return apology("invalid password", 400)

        # Update hash
        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(request.form.get("new_password")), session["user_id"])

        # Logs user out
        session.clear()

        # Redirect user to login page
        return redirect("/login")

    else:
        return render_template("change.html")
