-- Get titles and release years of all Harry Potter movies ordered by release year
SELECT title, year FROM movies WHERE title LIKE 'Harry Potter%' ORDER BY year;