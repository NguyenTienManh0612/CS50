-- Keep a log of any SQL queries you execute as you solve the mystery.

-- to know description about the theft took place on July 28, 2023 and that it took place on Humphrey Street.
SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND street = 'Humphrey Street';

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today
-- with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- each of their interview transcripts mentions the bakery => check interviews
SELECT * FROM interviews WHERE day = 28 AND month = 7 AND transcript LIKE '%bakery%';
-- Witness Ruth:
-- ten minutes of the theft from 10:15am
SELECT * FROM bakery_security_logs WHERE day = 28 AND month = 7
AND hour = 10 AND minute BETWEEN 10 AND 25;
-- license_plate: 13FNH73 5P2BI95 94KL13X 6P58WS2 4328GD8 G412CB7 L93JTIZ 322W7JE 0NTHK55

-- Witness Eugene:
-- Earlier this morning, by the ATM on Leggett Street, the thief there withdrawing some money.
SELECT * FROM atm_transactions
WHERE day = 28 AND month = 7
AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- Witness Raymond:
-- they called someone who talked to them for less than a minute.
SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND duration <= 60;
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
SELECT * FROM flights WHERE day = 29 AND month = 7 AND origin_airport_id IN (
    SELECT id FROM airports WHERE city = 'Fiftyville'
);
-- earliest flight at 8h20m on 29/7,
-- destination_airport_id = 4 = New York City
-- flight_id = 36
SELECT city FROM airports WHERE id = 4;
SELECT * FROM passengers WHERE flight_id = 36;

-- the theif has 2 people => they will book a row of seat
-- check license plate above we have:
SELECT * FROM people WHERE license_plate = '94KL13X';
-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+-------+----------------+-----------------+---------------+
-- receiver phone call: (375) 555-8161
SELECT * FROM bank_accounts WHERE person_id = 686048;
-- account: 49610011
-- match with account in database in witness Eugene
-- The ACCOMPLICE:
SELECT * FROM people WHERE phone_number = '(375) 555-8161';
