SELECT DISTINCT people.name FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE NOT people.name = "Kevin Bacon" AND movies.id IN (
SELECT movies.id FROM movies
JOIN stars ON people.id = stars.person_id
JOIN people ON movies.id = stars.movie_id
WHERE people.name = "Kevin Bacon" AND birth = 1958);


