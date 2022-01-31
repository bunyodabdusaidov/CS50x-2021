-- Find the crime description in crime scene reports table using the time and place 
SELECT description FROM crime_scene_reports WHERE day=28 AND month=7 AND year=2021 AND street="Humphrey Street";

-- Find the transcripts in interviews table which mention bakery 
SELECT id, transcript FROM interviews WHERE day=28 AND month=7 AND year=2021 AND transcript LIKE "%bakery%";

-- Get the names of the people having the same license plate on the bakery security cameras
SELECT name 
FROM people
JOIN bakery_security_logs ON people.license_plate=bakery_security_logs.license_plate
WHERE day=28 AND month=7 AND year=2021 AND hour=10 AND 15<=minute<25
AND activity="exit";

-- Get the names of the people having the same bank account number used to withdraw money from ATM 

SELECT DISTINCT name
FROM people
JOIN bank_accounts ON people.id=bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number=atm_transactions.account_number
WHERE day=28 AND month=7 AND year=2021
AND transaction_type="withdraw" 
AND atm_location="Leggett Street";

-- Get the names of the people who took the first flight on the 29th

SELECT name
FROM people
JOIN passengers ON people.passport_number=passengers.passport_number
WHERE flight_id=(
    SELECT id
    FROM flights
    WHERE day=29 AND month=7 AND year=2021
    ORDER BY hour, minute
    LIMIT 1);

-- Get the names of the people who made