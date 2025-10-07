# SQL

Category: Programming
Date Learned: August 9, 2025
Links: https://cs50.harvard.edu/x/2025/psets/ | https://cs50.harvard.edu/x/ | https://learning.edx.org/course/course-v1:HarvardX+CS50+X/home | https://verbose-cod-9x75jg9rq9qfgp5.github.dev/?autoStart=true&folder=%2Fworkspaces%2F75383640&vscodeChannel=stable | https://cs50.me/ | https://manual.cs50.io/ | https://docs.python.org/ | https://www.google.com/search?q=ascii+chart#vhid=gXuaxtMeA2vKyM&vssid=_9kpYaL2KJqCi5NoPtLfx0Qw_59
Module: 7
Source: CS50
Status: Done
Tags: Python, SQL

## Flat-File Databases

- Data can often be described in patterns of columns and rows.
- Spreadsheets like those created in Excel or Sheets can be outputted to a `csv` or *comma-separated values* files.
- If you look at a `csv` file, you’ll notice that the file is flat in that all the data is stored in a single table represented by a text file. We call this form of data a *flat-file database*.
    - All data is stored row by row, with each column being separated by a comma or another value
- Python comes with native support for `csv` files.
- Examining the data in favorites.csv, notice that the first row is special because it defines each column. Then, each record is stored row by row.
- `code [favorites.py](http://favorites.py)`  as follows:

```python
# Prints all favorites in CSV using csv.reader

import csv

# Open CSV file
with open("favorites.csv", "r") as file:

    # Create reader
    reader = csv.reader(file)

    # Skip header row
    next(reader)

    # Iterate over CSV file, printing each favorite
    for row in reader:
        print(row[1])
```

- You can improve the code as follows:

```python
# Stores favorite in a variable

import csv

# Open CSV file
with open("favorites.csv", "r") as file:

    # Create reader
    reader = csv.reader(file)

    # Skip header row
    next(reader)

    # Iterate over CSV file, printing each favorite
    for row in reader:
        favorite = row[1]
        print(favorite)
```

- A disadvantage of the above approach is that we are trusting that `row[1]` is always the favorite language. But if the columns had been moved, the code would break.
- We can fix this issue because Python allows you to index by the keys of a list.

```python
# Prints all favorites in CSV using csv.DictReader

import csv

# Open CSV file
with open("favorites.csv", "r") as file:

    # Create DictReader
    reader = csv.DictReader(file)

    # Iterate over CSV file, printing each favorite
    for row in reader:
        favorite = row["language"]
        print(favorite)
```

- This could be further simplified to:

```python
# Prints all favorites in CSV using csv.DictReader

import csv

# Open CSV file
with open("favorites.csv", "r") as file:

    # Create DictReader
    reader = csv.DictReader(file)

    # Iterate over CSV file, printing each favorite
    for row in reader:
        print(row["language"])
```

- To count the number of favorite languages expressed in the `csv` file, we can do the following:

```python
# Counts favorites using variables

import csv

# Open CSV file
with open("favorites.csv", "r") as file:

    # Create DictReader
    reader = csv.DictReader(file)

    # Counts
    scratch, c, python = 0, 0, 0

    # Iterate over CSV file, counting favorites
    for row in reader:
        favorite = row["language"]
        if favorite == "Scratch":
            scratch += 1
        elif favorite == "C":
            c += 1
        elif favorite == "Python":
            python += 1

# Print counts
print(f"Scratch: {scratch}")
print(f"C: {c}")
print(f"Python: {python}")
```

- Python allows us to use a dictionary to count the `counts` of each language. Consider the following improvement:

```python
# Counts favorites using dictionary

import csv

# Open CSV file
with open("favorites.csv", "r") as file:

    # Create DictReader
    reader = csv.DictReader(file)

    # Counts
    counts = {}

    # Iterate over CSV file, counting favorites
    for row in reader:
        favorite = row["language"]
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

# Print counts
for favorite in counts:
    print(f"{favorite}: {counts[favorite]}")
```

- Python also allows sorting `counts`.

```python
# Sorts favorites by key

import csv

# Open CSV file
with open("favorites.csv", "r") as file:

    # Create DictReader
    reader = csv.DictReader(file)

    # Counts
    counts = {}

    # Iterate over CSV file, counting favorites
    for row in reader:
        favorite = row["language"]
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

# Print counts
for favorite in sorted(counts):
    print(f"{favorite}: {counts[favorite]}")
```

- If you look at the parameters for the `sorted` function in the documentation, you will find it has many built-in parameters. You can leverage these parameters as follows:

```python
# Sorts favorites by value using .get

import csv

# Open CSV file
with open("favorites.csv", "r") as file:

    # Create DictReader
    reader = csv.DictReader(file)

    # Counts
    counts = {}

    # Iterate over CSV file, counting favorites
    for row in reader:
        favorite = row["language"]
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

# Print counts
for favorite in sorted(counts, key=counts.get, reverse=True):
    print(f"{favorite}: {counts[favorite]}")
```

---

## Relational Databases

- Google, X, and Meta all use relational databases to store their information at scale.
- Relational databases store data in rows and columns in structures called *tables*.
- SQL allows for four types of commands (CRUD):

```sql
  Create
  Read
  Update
  Delete
```

- You can create a database with the SQL syntax `CREATE TABLE table (column type, ...);`. But where do you run this command?
- `sqlite3` is a type of SQL database that has the core features required for this course.
- We can create a SQL database at the terminal by typing `sqlite3 favorites.db`. Press y.
- You will notice a different prompt as we are now using a program called `sqlite`.
- We can put `sqlite` into `csv` mode by typing `.mode csv`. Then, we can import our data from our `csv` file by typing `.import favorites.csv favorites`. It seems that nothing has happened!
- We can type `.schema` to see the structure of the database.
- You can read items from a table using the syntax `SELECT columns FROM table`.
- For example, you can type `SELECT * FROM favorites;` which will print every row in `favorites`.
- You can get a subset of the data using the command `SELECT language FROM favorites;`.
- SQL supports many commands to access data, including:

```sql
AVG
COUNT
DISTINCT
LOWER
MAX
MIN
UPPER
```

- For example, you can type `SELECT COUNT(*) FROM favorites;`. Further, you can type `SELECT DISTINCT language FROM favorites;` to get a list of the individual languages within the database. You could even type `SELECT COUNT(DISTINCT language) FROM favorites;` to get a count of those.
- SQL offers additional commands we can utilize in our queries:

```sql
WHERE       -- adding a Boolean expression to filter our data
LIKE        -- filtering responses more loosely
ORDER BY    -- ordering responses
LIMIT       -- limiting the number of responses
GROUP BY    -- grouping responses together
```

---

## SELECT

- For example, we can execute `SELECT COUNT(*) FROM favorites WHERE language = 'C';`. A count is presented
- We could type `SELECT COUNT(*) FROM favorites WHERE language = 'C' AND problem = 'Hello, World';`. Notice how the `AND` is utilized to narrow the results.
- Similarly, we could execute `SELECT language, COUNT(*) FROM favorites GROUP BY language;`.
- We could improve this by typing `SELECT language, COUNT(*) FROM favorites GROUP BY language ORDER BY COUNT(*);`. This will order the resulting table by the `count`.
- Likewise, we could execute `SELECT COUNT(*) FROM favorites WHERE language = 'C' AND (problem = 'Hello, World' OR problem = 'Hello, It''s Me';`. Notice the two `''` apostrophes to allow the use of single quotes in a way that doesn’t confuse SQL.
- Furthermore, we could execute `SELECT COUNT(*) FROM favorites WHERE language = 'C' AND problem LIKE 'Hello, %';` to find any problems that start with `Hello,`  (including the space)
- We can also group the values of each language by executing `SELECT language, COUNT(*) FROM favorites GROUP BY language;`.
- We can order the output as follows: `SELECT language, COUNT(*) FROM favorites GROUP BY language ORDER BY COUNT(*) DESC;`.
- We can also create aliases, like variables in our queries: `SELECT language, COUNT(*) AS n FROM favorites GROUP BY language ORDER BY n DESC;`.
- Finally, we can limit the output to 1 or more values: `SELECT language, COUNT(*) AS n FROM favorites GROUP BY language ORDER BY n DESC LIMIT 1;`.

---

## INSERT

- We can also `INSERT` into a SQL database utilizing the form `INSERT INTO table (column...) VALUES(value, ...);`.
- We can execute `INSERT INTO favorites (language, problem) VALUES ('SQL', 'Fiftyville');`.
- You can verify the addition of this favorite by executing `SELECT * FROM favorites;`.

---

## DELETE

- `DELETE` allows you to delete parts of the data. For example, you could `DELETE FROM favorites WHERE Timestamp IS NULL;`. This deletes any record where the `Timestamp` is `NULL`.

---

## UPDATE

- We can also utilize the `UPDATE` command to update your data.
- For example, you can execute `UPDATE favorites SET language = 'SQL', problem = 'Fiftyville';`. This will result in overwriting all previous statements where C and Scratch were the favorite programming language.
- Notice that these queries have immense power. Accordingly, in the real-world setting, you should consider who has permissions to execute certain commands and if you have backups available!

---

## IMDb

- We can imagine a database that we might want to create to catalog TV shows. We could create a spreadsheet with columns like `title`, `star`, `star`, `star`, `star`, and more stars. A problem with this approach is that it has a lot of wasted space. Some shows may have one star. Others may have dozens.
- We could separate our database into multiple sheets. We could have a `shows` sheet, a `stars` sheet, and a `people` sheet. On the `people` sheet, each person could have a unique `id`. On the `shows` sheet, each show could have a unique `id` too. On a third sheet called `stars` we could relate how each show has people for each show by having a `show_id` and `person_id`. While this is an improvement, this is not an ideal database.
- IMDb offers a database of people, shows, writers, stars, genres, and ratings. The schema can be visualized as follows:
- Let’s focus on the relationship between two tables within the database called `shows` and `ratings`.
    
    ![cs50Week7Slide025.png](cs50Week7Slide025.png)
    
- To illustrate the relationship between these tables, we can execute the following command: `SELECT * FROM ratings LIMIT 10;`. Examining the output, we could execute `SELECT * FROM shows LIMIT 10;`.
- After examining the two tables, you can see that they have a *one-to-one* relationship: One show has one rating.
- To understand the database, try executing `.schema`, which shows not only the tables in the database but the individual fields of each one.
- `show_id` exists in all of the tables. In the `shows` table, it is simply called `id`. This common field between all the fields is called a *key*. Primary keys are used to identify a unique record in a table. *Foreign keys* are used to build relationships between tables by pointing to the primary key in another table. You can see in the schema of `ratings` that `show_id` is a foreign key that references `id` in `shows`.
    - By storing data in a relational database, as above, it can be stored more efficiently.
- In *sqlite*, we have five data types, including:

```sql
  BLOB       -- binary large objects that are groups of ones and zeros
  INTEGER    -- an integer
  NUMERIC    -- for numbers that are formatted specially like dates
  REAL       -- like a float
  TEXT       -- for strings and the like
```

- Additionally, columns can be set to add special constraints:

```sql
NOT NULL
UNIQUE
```

- We can further limit this data down by executing `SELECT show_id FROM ratings WHERE rating >= 6.0 LIMIT 10;`.
    - From this query, it is apparent that there are 10 shows presented. However, we don’t know what show each `show_id` represents.
    - You can discover what shows these are by executing `SELECT * FROM shows WHERE show_id = 626124;`.
- Improving further:

```sql
SELECT title
FROM shows
WHERE id IN (
	SELECT show_id
	FROM ratings
	WHERE rating >= 6.0
	LIMIT 10
)
```

---

## JOINs

- We are pulling data from `shows` and `ratings`. Notice how both `shows` and `ratings` have an `id` in common.
- How could we combine tables temporarily? Tables could be joined together via the `JOIN` command.
- Execute:

```sql
SELECT * FROM shows
	JOIN ratings on shows.id = ratings.show_id
	WHERE rating >= 6.0
	LIMIT 10;
```

- The previous queries demonstrated one-to-one relationships between keys, but let’s examine some *one-to-many* relationships. Focusing on the *genres* table, execute the following:

```sql
SELECT * FROM genres
LIMIT 10;
```

- Execute the following command to learn about the various comedies in the database

```sql
SELECT title FROM shows
WHERE id IN (
	SELECT show_id FROM genres
	WHERE genre = 'Comedy'
	LIMIT 10;
)
```

- To learn more about Catweazle:

```sql
SELECT * FROM shows
JOIN genres
ON shows.id = genres.show_id
WHERE id = 63881;
```

- In contrast to one-to-one and one-to-many relationships, there may be *many-to-many* relationships.
- We can learn more about the show *The Office* and the actors in that show by executing:

```sql
SELECT name FROM people WHERE id IN 
    (SELECT person_id FROM stars WHERE show_id = 
        (SELECT id FROM shows WHERE title = 'The Office' AND year = 2005));
```

- We find all the shows in which Steve Carell starred:

```sql
SELECT title FROM shows WHERE id IN 
    (SELECT show_id FROM stars WHERE person_id = 
        (SELECT id FROM people WHERE name = 'Steve Carell'));
```

- This could also be expressed in this way:

```sql
SELECT title FROM shows, stars, people 
WHERE shows.id = stars.show_id
AND people.id = stars.person_id
AND name = 'Steve Carell';
```

---

## Indexes

- While relational databases can be faster and more robust than utilizing a `csv` file, data can be optimized within a table using *indexes*.
- Indexes can be utilized to speed up our queries
- We can track the speed of our queries by executing `.timer on` in `sqlite3`.
- To understand how indexes can speed up our queries, run the following: `SELECT * FROM shows WHERE title = 'The Office';`.
- Then, we can create an index with the syntax `CREATE INDEX title_index ON shows (title);`. This tells `sqlite3` to create an index and perform some special under-the-hood optimization relating to this column `title`.
- This will create a data structure called a *B Tree*, a data structure that looks similar to a binary tree. However, unlike a binary tree, there can be more than two child nodes.
    
    ![cs50Week7Slide039.png](cs50Week7Slide039.png)
    
- We can create indexes as follows:

```sql
CREATE INDEX name_index ON people (name);
CREATE INDEX person_index ON stars (person_id);
```

- Running the query, you will notice that the query runs much more quickly

```sql
SELECT title FROM shows WHERE id IN 
    (SELECT show_id FROM stars WHERE person_id = 
        (SELECT id FROM people WHERE name = 'Steve Carell'));
```

- Unfortunately, indexing all columns would result in utilizing more storage space. Therefore, there is a tradeoff for enhanced speed.

---

## Using SQL in Python

- To assist in working with SQL in this course, the CS50 library can be utilized as follows:

```python
from cs50 import SQL
```

- The library will assist in the complicated steps of using SQL within Python code.
    - [documentation](https://cs50.readthedocs.io/libraries/cs50/python/#cs50.SQL)
- Modify your code for [favorites.py](http://favorites.py) as follows:

```python
# Searches database popularity of a problem

from cs50 import SQL

# Open database
db = SQL("sqlite:///favorites.db")

# Prompt user for favorite
favorite = input("Favorite: ")

# Search for title
rows = db.execute("SELECT COUNT(*) AS n FROM favorites WHERE language = ?", favorite)

# Get first (and only) row
row = rows[0]

# Print popularity
print(row["n"])
```

---

## Race Conditions

- Utilization of SQL can sometimes result in some problems.
- Imagine a case where multiple users could be accessing the same database and executing commands simultaneously.
- This could result in glitches where code is interrupted by other people’s actions. This could result in a loss of data.
- SQL features like `BEGIN TRANSACTION`, `COMMIT`, and `ROLLBACK` help avoid some of these race condition problems.

---

## SQL Injection Attacks

- What do the `?` question marks do above? It helps to prevent injection attacks, where a malicious actor can input malicious SQL code.
- For example, consider the following login screen:
    
    ![cs50Week7Slide051.png](cs50Week7Slide051.png)
    
- Without the proper protections in our own code, a bad actor could run malicious code:

```python
rows = db.execute("SELECT COUNT(*) FROM users WHERE username = ? AND password = ?", username, password)
```

- You never want to use formatted strings in queries as above or blindly trust the user’s input.
- Using the CS50 library, the library will *sanitize* and remove any potentially malicious characters.

---