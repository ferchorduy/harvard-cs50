-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check the report first.
SELECT *
FROM crime_scene_reports
WHERE street = 'Humphrey Street'
    AND year = 2025
    AND month = 7
    AND day = 28;
-- Theft took place at 10:15am, July 28, 2025. Three interviews took place.

-- Check interviews
SELECT *
FROM interviews
WHERE year = 2025
    AND month = 7
    AND day = 28;
-- Ruth said to look for cars that left the parking lot between 10:15am and 10:25am
-- Eugene said he saw thief withdrawing from an ATM on Leggett St. earlier in the morning.
-- Raymond said the thief was taking the earliest flight the next morning out of Fiftyville.

-- Check Ruth's claims
SELECT *
FROM bakery_security_logs
WHERE year = 2025
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25;
-- Narrowed down to eight license plates

-- Check Eugene's claims
SELECT *
FROM atm_transactions
WHERE year = 2025
    AND month = 7
    AND day = 28
    AND transaction_type = 'withdraw'
    AND atm_location = 'Leggett Street';
-- Eight withdrawals

-- Check Raymond's claims
SELECT *
FROM phone_calls
WHERE year = 2025
    AND month = 7
    AND day = 28
    AND duration < 60;
-- Down to nine calls under a minute

-- Check earliest flight on July 29, 2025
SELECT *
FROM flights
WHERE year = 2025
    AND month = 7
    AND day = 29
    ORDER BY hour;
-- Earliest is 8:20am, destination_airport_id is 4, flights.id is 36

-- Find airport location
SELECT *
FROM airports
WHERE id = 4;
-- LGA, LaGuardia Airport is where they escaped to!

-- Check passenger info on flight 36
SELECT *
FROM passengers
JOIN flights ON flights.id = passengers.flight_id
WHERE flights.id = 36;
-- Eight passport numbers

-- Search in people with all factors considered
SELECT *
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2025
    AND month = 7
    AND day = 28
    AND duration < 60
)
AND passport_number IN (
    SELECT passport_number
    FROM passengers
    JOIN flights ON flights.id = passengers.flight_id
    WHERE flights.id = 36
)
AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2025
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25
);
-- Sofia, Kelsey, Bruce. Check bank accounts

-- Cross reference bank accounts with three suspects
SELECT *
FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE name = 'Sofia' OR name = 'Kelsey' OR name = 'Bruce';
-- Bruce is it!

-- Find accomplice number
SELECT *
FROM phone_calls
WHERE caller IN (
    SELECT phone_number
    FROM bank_accounts
    JOIN people ON bank_accounts.person_id = people.id
    WHERE name = 'Bruce'
)
AND year = 2025
    AND month = 7
    AND day = 28
    AND duration < 60;
-- Receiver is (375) 555-8161

-- Get name of accomplice
SELECT name
FROM people
WHERE phone_number = '(375) 555-8161';
-- Robin is the accomplice!