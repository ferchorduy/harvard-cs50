-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred
SELECT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id
WHERE people.name = 'Jennifer Lawrence'

INTERSECT

SELECT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id
WHERE people.name = 'Bradley Cooper';