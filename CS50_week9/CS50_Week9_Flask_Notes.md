# Flask

Category: Programming
Date Learned: August 21, 2025
Links: https://cs50.harvard.edu/x/2025/psets/ | https://cs50.harvard.edu/x/ | https://learning.edx.org/course/course-v1:HarvardX+CS50+X/home | https://verbose-cod-9x75jg9rq9qfgp5.github.dev/?autoStart=true&folder=%2Fworkspaces%2F75383640&vscodeChannel=stable | https://cs50.me/ | https://manual.cs50.io/ | https://docs.python.org/ | https://www.google.com/search?q=ascii+chart#vhid=gXuaxtMeA2vKyM&vssid=_9kpYaL2KJqCi5NoPtLfx0Qw_59
Module: 9
Source: CS50
Status: Done
Tags: CSS, Flask, HTML, Javascript, Networking, Python, SQL, Software Development

## http-server

- Up until this point, all HTML was pre-written and static.
- In the past, when you visited a page, the browser downloaded an HTML page, you were able to view it. These are called *static* pages, in that what is programmed in the HTML is exactly what the user sees and downloads *client-side* to their internet browser.
- Dynamic pages refer to the ability of Python and similar languages to create HTML dynamically. Accordingly, you can have pages that are generated *server-side* by code based upon the input or behavior of users.
- Used `http-server` in the past, to serve web pages, week 9 introduces a server that can parse out a web address and do things based on the URL.
- Further, last week, you saw URLs as follows:
    
    ```
    https://www.example.com/folder/file.html
    ```
    
    Notice that `file.html` is an HTML file inside a folder called `folder` at `example.com`.
    

---

## Flask

- This week, *routes* are introduced like `https://www.example.com/route?key=value`, where specific functionality can be generated on the server via the keys and values in the URL.
- *Flask* is a third-party library that facilitates web app hosting using the Flask framework, a *micro-framework*, within Python.
- Run Flask by executing `flask run` in the terminal.
    - You need [`app.py`](http://app.py) as well as `requirements.txt`. `app.py` contains code that tells Flask how to run the web app, and requirements.txt includes a list of the libraries that are required for the Flask app to run.
- sample `requirements.txt`:

```
Flask
```

- Simple Flask app in `app.py`:

```python
# Says hello to world by returning a string of text

from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def index():
    return "hello, world"
```

- Code that implements HTML:

```python
# Says hello to world by returning a string of HTML

from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def index():
    return '<!DOCTYPE html><html lang="en"><head><title>hello</title></head><body>hello, world</body></html>'
```

- To improve, you can serve HTML based on templates by creating a folder called `templates` and creating a file called `index.html` with the following code:

```html
<!DOCTYPE html>

<html lang="en">

    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>

    <body>
        hello, {{ name }}
    </body>

</html>
```

- In the same folder that `templates` appears, create [`app.py`](http://app.py) and:

```python
# Uses request.args.get

from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def index():
    name = request.args.get("name", "world")
    return render_template("index.html", name=name)
```

- Once running, click the prompted link, then add `?name=[your name]` to the base URL.

---

## Forms

- Bad design, as users won’t type args into the address bar. Instead, devs use forms. Modify `index.html` as follows:

```html
<!DOCTYPE html>

<html lang="en">

    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>

    <body>
        <form action="/greet" method="get">
            <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
            <button type="submit">Greet</button>
        </form>
    </body>

</html>
```

- Further modifying `app.py`:

```python
# Adds a form, second route

from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/greet")
def greet():
    return render_template("greet.html", name=request.args.get("name", "world"))
```

- To finalize, add a template for `greet.html` in `templates`:

```html
<!DOCTYPE html>

<html lang="en">

    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>

    <body>
        hello, {{ name }}
    </body>

</html>
```

---

## Templates

- Both pages `index.html` and `greet.html` have much of the same data. How do you allow the body to be unique but copy the same layout from page to page?
- Create a template called `layout.html`:

```html
<!DOCTYPE html>

<html lang="en">

    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>

    <body>
        {% block body %}{% endblock %}
    </body>

</html>
```

- Modify `index.html`:

```html
{% extends "layout.html" %}

{% block body %}

    <form action="/greet" method="get">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <button type="submit">Greet</button>
    </form>

{% endblock %}
```

- Finally, change `greet.html` as follows:

```html
{% extends "layout.html" %}

{% block body %}
    hello, {{ name }}
{% endblock %}
```

---

## Request Methods

- There are scenarios where it is not safe to utilize `get`, as sensitive info would show up in the URL.
- You can use `post` to account for this:

```python
# Switches to POST

from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/greet", methods=["POST"])
def greet():
    return render_template("greet.html", name=request.form.get("name", "world"))
```

- This tells the server to look *deeper* into the virtual envelope and not reveal the items in `post` in the URL.
- Improve further by utilizing a single route for both `get` and `post`:

```python
# Uses a single route

from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        return render_template("greet.html", name=request.form.get("name", "world"))
    return render_template("index.html")
```

- Accordingly, modify `index.html`:

```html
{% extends "layout.html" %}

{% block body %}

    <form action="/" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <button type="submit">Greet</button>
    </form>

{% endblock %}
```

- With the new implementation, when someone types no name, `Hello,` is displayed without a name. Improve:

```python
# Moves default value to template

from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        return render_template("greet.html", name=request.form.get("name"))
    return render_template("index.html")
```

- Change `greet.html`:

```html
{% extends "layout.html" %}

{% block body %}

    hello,
    {% if name %}
        {{ name }}
    {% else %}
        world
    {% endif %}

{% endblock %}
```

---

## Frosh IMs

- Frosh IMs or *froshims* is a web app that allows students to register for intramural sports.
- `app.py`:

```python
# Implements a registration form using a select menu, validating sport server-side

from flask import Flask, render_template, request

app = Flask(__name__)

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee"
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():

    # Validate submission
    if not request.form.get("name") or request.form.get("sport") not in SPORTS:
        return render_template("failure.html")

    # Confirm registration
    return render_template("success.html")
```

- `templates`:

```html
{% extends "layout.html" %}

{% block body %}
    <h1>Register</h1>
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <select name="sport">
            <option disabled selected value="">Sport</option>
            {% for sport in sports %}
                <option value="{{ sport }}">{{ sport }}</option>
            {% endfor %}
        </select>
        <button type="submit">Register</button>
    </form>
{% endblock %}
```

- `layout.html`:

```html
<!DOCTYPE html>

<html lang="en">

    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>froshims</title>
    </head>

    <body>
        {% block body %}{% endblock %}
    </body>

</html>
```

- `success.html`:

```html
{% extends "layout.html" %}

{% block body %}
    You are registered!
{% endblock %}
```

- `failure.html`:

```html
{% extends "layout.html" %}

{% block body %}
    You are not registered!
{% endblock %}
```

- How do you see the registration options using radio buttons? Improve `index.html` as follows:

```html
{% extends "layout.html" %}

{% block body %}
    <h1>Register</h1>
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        {% for sport in sports %}
            <input name="sport" type="radio" value="{{ sport }}"> {{ sport }}
        {% endfor %}
        <button type="submit">Register</button>
    </form>
{% endblock %}
```

- How do you accept the registration of many different registrants? Improve [`app.py`](http://app.py) as follows:

```python
# Implements a registration form, storing registrants in a dictionary, with error messages

from flask import Flask, redirect, render_template, request

app = Flask(__name__)

REGISTRANTS = {}

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee"
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():

    # Validate name
    name = request.form.get("name")
    if not name:
        return render_template("error.html", message="Missing name")

    # Validate sport
    sport = request.form.get("sport")
    if not sport:
        return render_template("error.html", message="Missing sport")
    if sport not in SPORTS:
        return render_template("error.html", message="Invalid sport")

    # Remember registrant
    REGISTRANTS[name] = sport

    # Confirm registration
    return redirect("/registrants")

@app.route("/registrants")
def registrants():
    return render_template("registrants.html", registrants=REGISTRANTS)
```

- `error.html`:

```html
{% extends "layout.html" %}

{% block body %}
    <h1>Error</h1>
    <p>{{ message }}</p>
    <img alt="Grumpy Cat" src="/static/cat.jpg">
{% endblock %}
```

- `registrants.html`:

```html
{% extends "layout.html" %}

{% block body %}
    <h1>Registrants</h1>
    <table>
        <thead>
            <tr>
                <th>Name</th>
                <th>Sport</th>
            </tr>
        </thead>
        <tbody>
            {% for name in registrants %}
                <tr>
                    <td>{{ name }}</td>
                    <td>{{ registrants[name] }}</td>
                </tr>
            {% endfor %}
        </tbody>
    </table>
{% endblock %}
```

- This is a web application, albeit with some security flaws. A malicious person could change the HTML and *hack* the website. Also, the data will not persist if the server is shut down.

---

## Flask and SQL

- Python can interface with a SQL database, and you can combine Flask, Python, and SQL to create a web app where data will persist.
- `requirements.txt`:

```
cs50
Flask
```

- `index.html`:

```html
{% extends "layout.html" %}

{% block body %}
    <h1>Register</h1>
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        {% for sport in sports %}
            <input name="sport" type="checkbox" value="{{ sport }}"> {{ sport }}
        {% endfor %}
        <button type="submit">Register</button>
    </form>
{% endblock %}
```

- `layout.html`:

```html
<!DOCTYPE html>

<html lang="en">

    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>froshims</title>
    </head>

    <body>
        {% block body %}{% endblock %}
    </body>

</html>
```

- `error.html`:

```html
{% extends "layout.html" %}

{% block body %}
    <h1>Error</h1>
    <p>{{ message }}</p>
    <img alt="Grumpy Cat" src="/static/cat.jpg">
{% endblock %}
```

- `registrants.html`:

```html
{% extends "layout.html" %}

{% block body %}
    <h1>Registrants</h1>
    <table>
        <thead>
            <tr>
                <th>Name</th>
                <th>Sport</th>
                <th></th>
            </tr>
        </thead>
        <tbody>
            {% for registrant in registrants %}
                <tr>
                    <td>{{ registrant.name }}</td>
                    <td>{{ registrant.sport }}</td>
                    <td>
                        <form action="/deregister" method="post">
                            <input name="id" type="hidden" value="{{ registrant.id }}">
                            <button type="submit">Deregister</button>
                        </form>
                    </td>
                </tr>
            {% endfor %}
        </tbody>
    </table>
{% endblock %}
```

- `app.py`:

```html
# Implements a registration form, storing registrants in a SQLite database, with support for deregistration

from cs50 import SQL
from flask import Flask, redirect, render_template, request

app = Flask(__name__)

db = SQL("sqlite:///froshims.db")

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee"
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/deregister", methods=["POST"])
def deregister():

    # Forget registrant
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM registrants WHERE id = ?", id)
    return redirect("/registrants")

@app.route("/register", methods=["POST"])
def register():

    # Validate name
    name = request.form.get("name")
    if not name:
        return render_template("error.html", message="Missing name")

    # Validate sports
    sports = request.form.getlist("sport")
    if not sports:
        return render_template("error.html", message="Missing sport")
    for sport in sports:
        if sport not in SPORTS:
            return render_template("error.html", message="Invalid sport")

    # Remember registrant
    for sport in sports:
        db.execute("INSERT INTO registrants (name, sport) VALUES(?, ?)", name, sport)

    # Confirm registration
    return redirect("/registrants")

@app.route("/registrants")
def registrants():
    registrants = db.execute("SELECT * FROM registrants")
    return render_template("registrants.html", registrants=registrants)
```

---

## Cookies and Session

- [`app.py`](http://app.py) is considered a *controller*. A *view* is considered what the users see. A *model* is how data is stored and manipulated. Together, this is referred to as *MVC*.
- The prior implementation of `froshims` was insecure, and real web services like Google use login credentials to prevent unauthorized data access.
- Using *cookies*, we can implement this ourselves. Cookies are small files stored on your computer such that your computer can communicate with the server and effectively say, “I’m an authorized user that has already logged in.” This authorization through a cookie is called a *session*.
- Cookies may be stored as follows:

```html
GET / HTTP/2
Host: accounts.google.com
Cookie: session=value
```

- In the simplest form, we can implement this by creating a folder called `login` and then adding the following files.
- `requirements.txt`:

```html
Flask
Flask-Session
```

- `templates/layout.html`:

```html
<!DOCTYPE html>

<html lang="en">

    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>login</title>
    </head>

    <body>
        {% block body %}{% endblock %}
    </body>

</html>
```

- `templates/index.html`:

```html
{% extends "layout.html" %}

{% block body %}

    {% if name %}
        You are logged in as {{ name }}. <a href="/logout">Log out</a>.
    {% else %}
        You are not logged in. <a href="/login">Log in</a>.
    {% endif %}

{% endblock %}
```

- `templates/login.html`:

```html
{% extends "layout.html" %}

{% block body %}

    <form action="/login" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <button type="submit">Log In</button>
    </form>
    
{% endblock %}
```

- `app.py`:

```python
from flask import Flask, redirect, render_template, request, session
from flask_session import Session

# Configure app
app = Flask(__name__)

# Configure session
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

@app.route("/")
def index():
    return render_template("index.html", name=session.get("name"))

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        session["name"] = request.form.get("name")
        return redirect("/")
    return render_template("login.html")

@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")
```

- The `session` abstraction facilitates precise data access and features in the application. It ensures that no one can act on behalf of another user for any purpose.
- Learn more about sessions in the [Flask Documentation](https://flask.palletsprojects.com/en/stable/api/#flask.session).

---

## Shopping Cart