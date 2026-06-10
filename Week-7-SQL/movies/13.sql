-- 13. Names of all people who starred in a movie in which Kevin Bacon also starred
SELECT DISTINCT name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.id = (
    SELECT id
    FROM movies
    WHERE movies.title = (
        SELECT stars.movie_id
        FROM stars
        WHERE person_id = (
            SELECT name
            FROM people
            WHERE name = 'Kevin Bacon' and birth = 1958
        )
    )
)