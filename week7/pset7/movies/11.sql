-- Get titles of 5 highest rated movies starring Chadwick Boseman ordered by rating descending
SELECT title FROM movies
    JOIN ratings ON id = movie_id
    WHERE movie_id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Chadwick Boseman'))
    ORDER BY rating DESC
    LIMIT 5;