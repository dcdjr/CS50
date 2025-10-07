-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Query to get information about the crime based on the given date, and verifying that the theft of the cs50 duck took place on Humprey Street
SELECT street, description
FROM crime_scene_reports
WHERE year = 2024
    AND month = 7
    AND day = 28;

-- Query to extract information from the interview that the crime scene report mentioned
SELECT transcript
    FROM interviews
    WHERE year = 2024
        AND month = 7
        AND day = 28;

-- Query to get list of license plates that left the bakery in the time frame given
SELECT license_plate
FROM bakery_security_logs
    WHERE year = 2024
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute >= 15
        AND minute <= 25
        AND activity = 'exit';

-- Getting a list of callers based on date and given duration from interview to build list of suspects
SELECT receiver
FROM phone_calls
WHERE year = 2024
    AND month = 7
    AND day = 28
    AND duration < 60;

-- Getting list of people_ids from atm on Leggett Street mentioned in interview
SELECT person_id
FROM bank_accounts AS b
JOIN atm_transactions AS a
    ON b.account_number = a.account_number
WHERE year = 2024
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw')

-- Puts all information together into one query to yield the name 'Bruce' and his information
SELECT name, phone_number, passport_number, license_plate
FROM people
WHERE passport_number IN
(
    SELECT passport_number
    FROM passengers
    JOIN flights
        ON flights.id = passengers.flight_id
    WHERE year = 2024
        AND month = 7
        AND day = 29
        AND hour = 8
        AND minute = 20
        AND origin_airport_id = 8
    )
    AND phone_number IN
    (
        SELECT caller
        FROM phone_calls
        WHERE year = 2024
            AND month = 7
            AND day = 28
            AND duration < 60
            )
    AND license_plate IN
    (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2024
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= 15
            AND minute <= 25
            AND activity = 'exit'
            )
    AND id IN
    (
        SELECT person_id
        FROM bank_accounts AS b
        JOIN atm_transactions AS a
            ON b.account_number = a.account_number
        WHERE year = 2024
            AND month = 7
            AND day = 28
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
            );

-- Gets name of destination city from the flight Bruce was on, which was the flight earliest in the morning from fiftyville on july 29
SELECT city
FROM airports AS a
JOIN flights AS f
    ON a.id = f.destination_airport_id
WHERE year = 2024
    AND month = 7
    AND day = 29
    AND hour = 8
    AND minute = 20;

-- Gets receiving caller's phone number from Bruce's call
SELECT receiver
FROM phone_calls
WHERE year = 2024
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller = '(367) 555-5533';

-- Gets name from people table that matches the phone number Bruce called
SELECT name
FROM people
WHERE phone_number = '(375) 555-8161';
