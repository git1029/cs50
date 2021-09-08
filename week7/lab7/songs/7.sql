-- Get average energy of songs by Drake
SELECT AVG(energy) AS 'Average Energy' FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Drake');