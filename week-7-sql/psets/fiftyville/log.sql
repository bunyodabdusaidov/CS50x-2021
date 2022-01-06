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

SELECT name, phone_number
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