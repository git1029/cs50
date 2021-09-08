-- Get titles of movies starring both Johnny Depp and Helena Bonham Carter
SELECT title FROM movies
    JOIN stars ON movies.id = stars.movie_id
    WHERE person_id IN (SELECT id FROM people WHERE name IN ('Johnny Depp', 'Helena Bonham Carter'))
    GROUP BY movie_id HAVING COUNT(movie_id) > 1;