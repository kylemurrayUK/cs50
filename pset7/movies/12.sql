SELECT movies.title FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON stars.movie_id = movies.id
JOIN ratings ON movies.id = ratings.movie_id WHERE people.name = 'Helena Bonham Carter' OR people.name = 'Johnny Depp'
GROUP BY movies.title HAVING COUNT(*) > 1;

