-- Keep a log of any SQL queries you execute as you solve the mystery.

-- getting the details of the crime scene report from that day. Determined there were interviews
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28;
-- got the transcript for the interviews by searching for courthouse as crime scene report stipulates this
SELECT transcript FROM interviews WHERE transcript LIKE "%courthouse%";
-- got a list of phone calls made as per the witness statement. Managed to extract a list of phone numbers for thier
-- and accomplice
SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60;
-- one of the witnesses said the phone call they heard indicated that the thief would be leaving on first flight out of
-- Fiftyville the next day so I did this to get the first flight out then the second statement to get the airport that that
-- flight was leaving to, which was London Heathrow
SELECT * FROM flights WHERE month = 7 AND day = 29 ORDER BY hour;
SELECT * FROM airports WHERE id = "4";
-- as per transcript i got a list of possible number plates for the suspect
SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour < 11
AND minute < 25 AND minute > 15 AND activity = 'exit';
-- got a list of possible passport numbers for the suspect
SELECT passport_number FROM passengers WHERE flight_id = 36;
-- got a list of account numbers for the suspect
SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 and atm_location = 'Fifer Street' AND transaction_type = 'withdraw';
-- now at the point where I can narrow down a list of suspects from the information that i have so ran to below command
FROM people WHERE (passport_number = "6216255522" OR passport_number = "3355598951" OR passport_number = "2750542732"
 OR passport_number = "1207566299" OR passport_number = "9692634019" OR passport_number = "5138876283"
 OR passport_number = "1165086731") AND (license_plate = "5P2BI95" OR license_plate = "94KL13X" );
 SELECT * FROM people WHERE (license_plate = "5P2BI95" OR license_plate = "94KL13X" OR license_plate = "6P58WS2" OR
 license_plate = "4328GD8" OR license_plate = "G412CB7" OR OR license_plate = "L93JTIZ"
 OR license_plate = "322W7JE" OR license_plate = "0NTHK55");
-- deducting suspects from the list via a process of elimation got me to three suspects - Roger, Evelyn and Ernest. I
-- tried to wittle them down by seeing if any where out of the country when it happened using the command below
SELECT * FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number = "<list of possible bank accounts>";
-- from this i deduced that the thieft must be Ernest. To find his accomplice I know need to look at phone calls from
-- after the theft and see who he contacted to buy him a plane ticket
SELECT * FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60 AND caller = "(367) 555-5533";
-- from this i ran the commands below to get their name
SELECT * FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60 AND caller = "(367) 555-5533";
SELECT * FROM people WHERE phone_number = "(375) 555-8161";