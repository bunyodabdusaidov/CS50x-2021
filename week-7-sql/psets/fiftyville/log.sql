/*
-- Get the description of the crime
SELECT description 
FROM crime_scene_reports 
WHERE year=2021 AND month=7 AND day=28 AND street="Humphrey Street";

-- Get the interview descriptions that mention bakery
SELECT id, transcript
FROM interviews
WHERE year=2021 AND month=7 AND day=28 AND transcript LIKE "%bakery%";

-- Get the names of the people who have the same license plate as in the security logs
SELECT name 
FROM people
JOIN bakery_security_logs ON people.license_plate=bakery_security_logs.license_plate
WHERE year=2021 AND month=7 AND day=28 AND activity="exit" AND hour=10 AND minute >= 15 AND minute <= 25;

-- Get the names of the people who withdrew money in ATM in Leggett Street
SELECT DISTINCT name
FROM people
JOIN bank_accounts ON people.id=bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number=atm_transactions.account_number
WHERE year=2021 AND month=7 AND day=28 AND atm_location="Leggett Street" AND transaction_type="withdraw";

-- Get the names of the people who made a call on the day of theft
SELECT name
FROM people
JOIN phone_calls ON people.phone_number=phone_calls.caller
WHERE year=2021 AND month=7 AND day=28 AND duration < 60;

-- Get the names of the people who took the earliest flight out of Fiftyville

SELECT name
FROM people
JOIN passengers ON passengers.passport_number=people.passport_number
JOIN flights ON passengers.flight_id=flights.id
WHERE flights.id = (
    SELECT id 
    FROM flights
    WHERE year=2021 AND month=7 AND day=29 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville")
    ORDER BY hour, minute);
    --LIMIT 1);
*/
-- Combine all the name quiries to find the unique person
SELECT name 
FROM people
JOIN bakery_security_logs ON people.license_plate=bakery_security_logs.license_plate
WHERE year=2021 AND month=7 AND day=28 AND activity="exit" AND hour=10 AND minute >= 15 AND minute <= 25
INTERSECT
SELECT DISTINCT name
FROM people
JOIN bank_accounts ON people.id=bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number=atm_transactions.account_number
WHERE year=2021 AND month=7 AND day=28 AND atm_location="Leggett Street" AND transaction_type="withdraw"
INTERSECT
SELECT name
FROM people
JOIN phone_calls ON people.phone_number=phone_calls.caller
WHERE year=2021 AND month=7 AND day=28 AND duration < 60
INTERSECT
SELECT name
FROM people
JOIN passengers ON passengers.passport_number=people.passport_number
JOIN flights ON passengers.flight_id=flights.id
WHERE flights.id = (
    SELECT id 
    FROM flights
    WHERE year=2021 AND month=7 AND day=29 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville")
    ORDER BY hour, minute);

-- Get the destination where the thief escaped to
SELECT city 
FROM airports
WHERE id=(
    SELECT destination_airport_id
    FROM flights
    WHERE year=2021 AND month=7 AND day=29 AND origin_airport_id=(
        SELECT id 
        FROM airports
        WHERE city="Fiftyville"
    )
    AND id=(
        SELECT flight_id
        FROM passengers
        WHERE passport_number=(
            SELECT passport_number 
            FROM people
            WHERE name="Bruce"
        )
    )
);

-- Get the thief's accomplice by thief's phone_calls
SELECT name 
FROM people
WHERE phone_number=(
    SELECT receiver
    FROM phone_calls
    WHERE year=2021 AND month=7 AND day=28 AND duration<60 
    AND caller=(
        SELECT phone_number
        FROM people
        WHERE name="Bruce"
    )
);