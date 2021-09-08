-- Get number of movies with IMDb rating of 10.0
-- SELECT title FROM movies JOIN ratings ON id = movie_id WHERE rating = 10.0;
SELECT COUNT(movie_id) AS '10.0 Rating' FROM ratings WHERE rating = 10.0;