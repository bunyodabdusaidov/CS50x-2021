-- Find the crime description in crime scene reports table using the time and place 
SELECT description FROM crime_scene_reports WHERE day=28 AND month=7 AND year=2021 AND street="Humphrey Street";

-- Find the transcripts in interviews table which mention bakery 
SELECT id, transcript FROM interviews WHERE day=28 AND month=7 AND year=2021 AND transcript LIKE "%bakery%";

-- Find the phone numbers of the callers and receivers in phone calls table using time 
SELECT id, caller, receiver FROM phone_calls WHERE day=28 AND month=7 AND year=2021 AND duration < 60;

-- Find the license plates in bakery security logs
SELECT license_plate FROM bakery_security_logs WHERE day=28 AND month=7 AND year=2021 AND hour=10 AND 15 < minute < 25 AND activity="exit";

-- Find the origin airport id or abbreviation in airports table using to city name 
SELECT id FROM airports WHERE city="Fiftyville";

-- Find the flight id in flights table using the time and origin airport id 
SELECT id FROM flights WHERE day=29 AND month=7 AND year=2021 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville") ORDER BY hour LIMIT 1;

-- Find passport numbers of the callers in people table using phone_number and license plate 

SELECT passport_number 
FROM people 
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND month=7 AND year=2021 AND duration < 60) 
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND month=7 AND year=2021 AND hour=10 AND 15 < minute < 25 AND activity="exit");

-- Find passengers in passengers table using flight id and passport number
SELECT passport_number 
FROM passengers 
WHERE flight_id=(SELECT id FROM flights WHERE day=29 AND month=7 AND year=2021 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville") ORDER BY hour LIMIT 1)
AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND month=7 AND year=2021 AND duration < 60) 
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND month=7 AND year=2021 AND hour=10 AND 15 < minute < 25 AND activity="exit"));

-- Find the name and phone_number in people table using shortened list of passport numbers

SELECT id, name, phone_number
FROM people 
WHERE passport_number IN (SELECT passport_number 
FROM passengers 
WHERE flight_id=(SELECT id FROM flights WHERE day=29 AND month=7 AND year=2021 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville") ORDER BY hour LIMIT 1)
AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND month=7 AND year=2021 AND duration < 60) 
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND month=7 AND year=2021 AND hour=10 AND 15 < minute < 25 AND activity="exit")));

-- Shorten the list of people using name and phone number

SELECT caller, receiver 
FROM phone_calls 
WHERE day=28 AND month=7 AND year=2021 AND duration < 60
AND caller IN (SELECT phone_number
FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id=(SELECT id FROM flights WHERE day=29 AND month=7 AND year=2021 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville") ORDER BY hour LIMIT 1)
AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND month=7 AND year=2021 AND duration < 60) 
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND month=7 AND year=2021 AND hour=10 AND 15 < minute < 25 AND activity="exit"))));

-- Shorten the list of potential criminals in atm transactions list using account numbers, location, time, and transaction type
SELECT account_number
FROM atm_transactions
WHERE day=28 AND month=7 AND year=2021 AND transaction_type="withdraw" AND atm_location="Leggett Street"
AND account_number IN (SELECT account_number 
FROM bank_accounts 
WHERE person_id IN (SELECT id
FROM people 
WHERE passport_number IN (SELECT passport_number 
FROM passengers 
WHERE flight_id=(SELECT id FROM flights WHERE day=29 AND month=7 AND year=2021 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville") ORDER BY hour LIMIT 1)
AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND month=7 AND year=2021 AND duration < 60) 
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND month=7 AND year=2021 AND hour=10 AND 15 < minute < 25 AND activity="exit")))));

-- Find the person id in bank_accounts table using account_number
SELECT person_id
FROM bank_accounts
WHERE account_number IN (SELECT account_number 
FROM bank_accounts 
WHERE person_id IN (SELECT id
FROM people 
WHERE passport_number IN (SELECT passport_number 
FROM passengers 
WHERE flight_id=(SELECT id FROM flights WHERE day=29 AND month=7 AND year=2021 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville") ORDER BY hour LIMIT 1)
AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND month=7 AND year=2021 AND duration < 60) 
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND month=7 AND year=2021 AND hour=10 AND 15 < minute < 25 AND activity="exit")))));

-- Find the name, phone_number, passport_number, license_plate in people table using id
SELECT name
FROM people 
WHERE id IN (SELECT person_id
FROM bank_accounts
WHERE account_number IN (SELECT account_number 
FROM bank_accounts 
WHERE person_id IN (SELECT id
FROM people 
WHERE passport_number IN (SELECT passport_number 
FROM passengers 
WHERE flight_id=(SELECT id FROM flights WHERE day=29 AND month=7 AND year=2021 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville") ORDER BY hour LIMIT 1)
AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND month=7 AND year=2021 AND duration < 60) 
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND month=7 AND year=2021 AND hour=10 AND 15 < minute < 25 AND activity="exit"))))));

-- Find flight_id in passengers table using passport_number
SELECT flight_id 
FROM passengers
WHERE passport_number IN (SELECT passport_number
FROM people 
WHERE id IN (SELECT person_id
FROM bank_accounts
WHERE account_number IN (SELECT account_number 
FROM bank_accounts 
WHERE person_id IN (SELECT id
FROM people 
WHERE passport_number IN (SELECT passport_number 
FROM passengers 
WHERE flight_id=(SELECT id FROM flights WHERE day=29 AND month=7 AND year=2021 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville") ORDER BY hour LIMIT 1)
AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND month=7 AND year=2021 AND duration < 60) 
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND month=7 AND year=2021 AND hour=10 AND 15 < minute < 25 AND activity="exit")))))));

-- Find all the destination city in flights table using flight id
SELECT city
FROM airports 
WHERE id=(SELECT destination_airport_id 
FROM flights 
WHERE id=(SELECT flight_id 
FROM passengers
WHERE passport_number IN (SELECT passport_number
FROM people 
WHERE id IN (SELECT person_id
FROM bank_accounts
WHERE account_number IN (SELECT account_number 
FROM bank_accounts 
WHERE person_id IN (SELECT id
FROM people 
WHERE passport_number IN (SELECT passport_number 
FROM passengers 
WHERE flight_id=(SELECT id FROM flights WHERE day=29 AND month=7 AND year=2021 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville") ORDER BY hour LIMIT 1)
AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND month=7 AND year=2021 AND duration < 60) 
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND month=7 AND year=2021 AND hour=10 AND 15 < minute < 25 AND activity="exit")))))))));

-- Find the name of the caller in people table using id and phone number in phone_calls table
SELECT caller 
FROM phone_calls
WHERE caller IN (SELECT phone_number
FROM people 
WHERE id IN (SELECT person_id
FROM bank_accounts
WHERE account_number IN (SELECT account_number 
FROM bank_accounts 
WHERE person_id IN (SELECT id
FROM people 
WHERE passport_number IN (SELECT passport_number 
FROM passengers 
WHERE flight_id=(SELECT id FROM flights WHERE day=29 AND month=7 AND year=2021 AND origin_airport_id=(SELECT id FROM airports WHERE city="Fiftyville") ORDER BY hour LIMIT 1)
AND passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND month=7 AND year=2021 AND duration < 60) 
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND month=7 AND year=2021 AND hour=10 AND 15 < minute < 25 AND activity="exit")))))));