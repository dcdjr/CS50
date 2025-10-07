SELECT name FROM people WHERE id IN
    (SELECT s1.person_id FROM stars AS s1 JOIN stars AS s2 ON s1.movie_id = s2.movie_id WHERE s2.person_id =
    (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = '1958')
    AND s1.person_id != (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = '1958'));
