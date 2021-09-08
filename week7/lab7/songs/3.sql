-- Get names of top 5 songs ordered by length descending
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;