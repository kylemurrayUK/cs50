SELECT people.name FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id
WHERE movies.year = '2004' GROUP BY people.name ORDER BY people.birth;