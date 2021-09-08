-- Get average rating of movies released in 2012
SELECT AVG(rating) AS 'Average Rating' FROM ratings JOIN movies ON movie_id = id WHERE year = 2012;