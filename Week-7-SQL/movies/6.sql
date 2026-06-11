-- 6. Average rating of movies in 2012
SELECT AVG(rating) AS average_rating
FROM ratings
JOIN movies ON movies.id = ratings.movie_id
WHERE movies.year = 2012;