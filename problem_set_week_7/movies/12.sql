SELECT title FROM movies
JOIN stars s1 ON movies.id = s1.movie_id
JOIN stars s2 ON movies.id = s2.movie_id
WHERE s1.person_id = (
    SELECT id FROM people WHERE name = 'Bradley Cooper'
) AND s2.person_id = (
    SELECT id FROM people WHERE name = 'Jennifer Lawrence'
);
