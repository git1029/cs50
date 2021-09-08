-- Get names of people who starred in movies released in 2004 ordered by birth year
SELECT name FROM people
    WHERE id IN (SELECT DISTINCT person_id FROM stars
                    JOIN movies ON movie_id = id
                    WHERE year = 2004)
    ORDER BY birth;