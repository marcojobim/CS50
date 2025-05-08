-- Keep a log of any SQL queries you execute as you solve the mystery.

--Looking for the crimes on 'Humphrey Street' on July 28, 2024
SELECT * 
FROM crime_scene_reports
WHERE street = 'Humphrey Street' AND year = 2024 AND month = 7 AND day = 28;


--Looking for the 3 interviews of the witnesses who mentioned 'bakery'
SELECT id,name,transcript 
FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';


--Looking for 'bakery_security_log' logs between 10:15 and 10:25
SELECT * 
FROM bakery_security_logs 
WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;


--Getting the name, activity, and license plate of people who left between 10:15 and 10:25
SELECT p.name, bsl.activity, bsl.license_plate, bsl.hour, bsl.minute
FROM bakery_security_logs AS bsl
JOIN people AS p ON bsl.license_plate = p.license_plate  
WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;


--Looking for records of people who withdrew money on Leggett Street on the 28th
SELECT *
FROM atm_transactions
WHERE atm_location = 'Leggett Street' AND year = 2024 AND month = 7 AND day = 28
AND transaction_type = 'withdraw';


--Getting information from people found in the last query
SELECT a.*, p.name
FROM atm_transactions AS a
JOIN bank_accounts AS b ON  a.account_number = b.account_number
JOIN people AS p ON b.person_id = p.id
WHERE a.atm_location = 'Leggett Street' AND a.year = 2024 AND a.month = 7 AND a.day=  28 AND a.transaction_type = 'withdraw';


--Looking for the name and information of people who made calls of less than 1 minute on the 28th
SELECT p.name, pc.*
FROM phone_calls AS pc
JOIN people AS p ON pc.caller = p.phone_number
WHERE pc.year = 2024 AND pc.month = 7 AND pc.day = 28 AND pc.duration < 60;


--Finding out the name of who Bruce called
SELECT DISTINCT p.name
FROM phone_calls AS pc
JOIN people AS p ON pc.caller = p.phone_number
WHERE p.phone_number = '(375) 555-8161';


--Looking for flights on the 29th and sorting them by time
SELECT *
FROM flights
WHERE year = 2024 AND month = 7 AND day = 29
ORDER BY hour,minute;


--Looking for the names of the passengers on flight 36
SELECT p.name, pa.* 
FROM people AS p
JOIN passengers AS pa ON p.passport_number = pa.passport_number
JOIN flights AS f ON pa.flight_id = f.id
WHERE f.id = 36; 


--Looking for city and airport name with id 4 (destination of flight 36)
SELECT a.abbreviation, a.full_name, a.city
FROM airports AS a
WHERE id = 4;