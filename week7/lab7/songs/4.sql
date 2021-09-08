-- Get song names with danceability, energy, and valence > 0.75
SELECT name FROM songs WHERE danceability > 0.75 AND ENERGY > 0.75 AND VALENCE > 0.75;