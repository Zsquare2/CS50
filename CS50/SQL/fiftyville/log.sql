-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Description of the robery
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street";


--what is in interviews
SELECT name,transcript FROM interviews WHERE name IN (SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit" AND hour > 10));

--were those people who left bakery afet robery flying?
SELECT people.name, year, month, day, hour FROM flights
JOIN passengers ON passengers.flight_id = flights.id
JOIN people ON passengers.passport_number = people.passport_number
WHERE day >= 28 AND name IN (SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit" AND hour > 10))
ORDER BY day, hour;

-- lets check intervies of those who flies
SELECT transcript, name, year, month, day FROM interviews
WHERE month >= 7
AND name IN (
SELECT people.name FROM flights
JOIN passengers ON passengers.flight_id = flights.id
JOIN people ON passengers.passport_number = people.passport_number
WHERE day >= 28 AND name IN (SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit" AND hour > 10)))
ORDER BY month, day;

-- lets see all interviews that day
SELECT transcript, name, day FROM interviews
WHERE year = 2021
AND month >= 7
AND day >= 28
ORDER by day;

-- lets get people that maces licens plate nubers that maches "aw the thief get into a car in the bakery parking lot and drive away".
SELECT name FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute >= 15
AND minute <= 25
AND activity = "exit";


--When Eugine ariverd at bakery   HE DIDNT DRIVE THAT DAY
SELECT name, day, hour, minute, activity FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28
ORDER BY hour, minute;
--WHERE people.name = "Eugene";
--AND day = 28;


--Who was  "withdrawing some money" that morning at Leggett Street?
SELECT name,transaction_type FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE day = 28
AND transaction_type = "withdraw"
AND year = 2021
AND month = 7
AND atm_location = "Leggett Street";


--who was calling before 10:25 and talked less than a minute
SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;


-- who was in firs light
SELECT name, hour, minute, flights.id FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON origin_airport_id = airports.id
WHERE city = "Fiftyville"
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour, minute, name ;


-- if combine all we got who made a crime
SELECT name FROM people
WHERE

name IN
(
-- lets get people that maces licens plate nubers that maches "aw the thief get into a car in the bakery parking lot and drive away".
SELECT name FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute >= 15
AND minute <= 25
AND activity = "exit"
)

AND name IN

(
--When Eugine ariverd at bakery   HE DIDNT DRIVE THAT DAY
SELECT name FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28
ORDER BY hour, minute
--WHERE people.name = "Eugene";
--AND day = 28;
)

AND name IN

(
--Who was  "withdrawing some money" that morning at Leggett Street?
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE day = 28
AND transaction_type = "withdraw"
AND year = 2021
AND month = 7
AND atm_location = "Leggett Street"
)

AND name IN

(
--who was calling before 10:25 and talked less than a minute
SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60
)
;

-- than we now that Bruce was in firs flight - that means that hes stole duck

-- And firs flight next (29)d was form Fiftyville to New Your City
SELECT name, city, (
    SELECT city FROM airports WHERE airports.id = destination_airport_id
    )
FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON origin_airport_id = airports.id
WHERE city = "Fiftyville"
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour, minute, name ;


-- to check who helper Bruse lets see woth who he was talking --  Its Robin
SELECT name FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE caller = (SELECT phone_number FROM people WHERE name = "Bruce")
AND year = 2021
AND month = 7
AND day = 28
AND duration < 60;