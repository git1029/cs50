-- Get names of people who starred in Toy Story
SELECT name FROM people
    JOIN (SELECT person_id FROM stars WHERE movie_id = (SELECT id FROM movies WHERE title = 'Toy Story'))
    ON id = person_id;