
SELECT name FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE caller = (SELECT phone_number FROM people WHERE name = "Bruce")
AND year = 2021
AND month = 7
AND day = 28
AND duration < 60;
