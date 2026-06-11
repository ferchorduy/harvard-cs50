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
-- Eight license plates

-- Check Eugene's claims
SELECT *
FROM atm_transactions
WHERE year = 2025
    AND month = 7
    AND day = 28
    AND hour = 10
    AND transaction_type = 'withdraw'
    AND atm_location = 'Leggett Street';
-- Eight withdrawals

-- Check Raymond's claims
SELECT *
FROM phone_calls
WHERE year = 2025
    AND month = 7
    AND day = 28;
-- Not a lot of info, maybe cross reference phone numbers

-- Check people
SELECT *
FROM people
-- Has license plate, passport number, and name