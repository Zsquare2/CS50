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
