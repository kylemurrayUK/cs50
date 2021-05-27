SELECT movies.title, ratings.rating FROM movies JOIN ratings ON movies.id = ratings.movie_id
WHERE movies.year = '2010' GROUP BY ratings.rating, movies.title ORDER BY ratings.rating DESC;