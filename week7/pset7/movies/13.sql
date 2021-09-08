-- Get names of people starring in films alongside Kevin Bacon (1958)
SELECT name FROM people
    JOIN (SELECT DISTINCT person_id FROM stars
            WHERE movie_id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958))
            AND person_id NOT IN (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958))
    ON id = person_id
    ORDER BY name;