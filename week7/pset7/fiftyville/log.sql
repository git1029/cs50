-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get all crime reports for date and location theft took place
SELECT * FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = 'Chamberlin Street';
-- 295 | 2020 | 7 | 28 | Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- Get all interview transcripts that mention courthouse and occur after theft took place
SELECT * FROM interviews WHERE transcript LIKE '%courthouse%' AND year >= 2020 AND month >= 7 AND day >= 28;
-- id | name | year | month | day | transcript
-- 161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- 163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Get earliest next day flight from Fiftyville
SELECT * FROM flights
    WHERE origin_airport_id IN (SELECT id FROM airports WHERE city = 'Fiftyville')
    AND year = 2020 AND month = 7 AND day = 29
    ORDER BY hour, minute
    LIMIT 1;
-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
-- 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20

-- Get destination city
SELECT * FROM airports WHERE id = 4;
-- id | abbreviation | full_name | city
-- 4 | LHR | Heathrow Airport | London

-- Get passengers on flight
SELECT * FROM passengers WHERE flight_id = 36;

-- Get calls made on day of theft
SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28;

-- Get courthouse logs from day of theft
SELECT * FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND activity = 'exit' AND hour = 10 AND minute >= 15 AND minute <= 25;

-- Get ATM actiivty on Fifer Street on day of theft
SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT DISTINCT account_number FROM atm_transactions
            WHERE atm_location = 'Fifer Street' AND year = 2020 AND month = 7 AND day = 28 AND transaction_type = 'withdraw'
    );

-- Cross reference people database with
-- ...license plate of anyone leaving courtroom within timeframe of theft (based on Ruth interview),
-- ...passports of passenges on flight 36 to London (based on Raymond interview),
-- ...phone numbers of outgoing calls less than 1 minute in duration made on day of theft (based on Raymond interview),
-- ...and bank accounts that had money withdrawn from an ATM on Fifer Street on day of theft (based on Eugene interview)
SELECT * FROM people
    WHERE license_plate IN (
        SELECT DISTINCT license_plate FROM courthouse_security_logs
            WHERE year = 2020 AND month = 7 AND day = 28 AND activity = 'exit' AND hour = 10 AND minute >= 15 AND minute <= 25
    )
    AND passport_number IN (
        SELECT passport_number FROM passengers WHERE flight_id = 36
    )
    AND phone_number IN (
        SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
    )
    AND id IN (
        SELECT person_id FROM bank_accounts
        WHERE account_number IN (
            SELECT DISTINCT account_number FROM atm_transactions
                WHERE atm_location = 'Fifer Street' AND year = 2020 AND month = 7 AND day = 28 AND transaction_type = 'withdraw'
        )
    );
-- id | name | phone_number | passport_number | license_plate
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- Get accomplice information by cross referencing people data with
-- ...Ernest's outgoing calls on day of theft less than 1 minute in duration (based on Raymond interview)
SELECT * FROM people WHERE phone_number IN (
    SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND caller = '(367) 555-5533' AND duration < 60
);
-- id | name | phone_number | passport_number | license_plate
-- 864400 | Berthold | (375) 555-8161 |  | 4V16VO0