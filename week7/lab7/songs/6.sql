-- Get name of songs by Post Malone
SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE artists.name = 'Post Malone');