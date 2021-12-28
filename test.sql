CREATE TABLE tmp(name VARCHAR(128), id INT, PRIMARY KEY (id, name));
--INSERT INTO tmp VALUES ('peichen', 2018013400),('chenxin', 2018013401);
--SELECT * FROM tmp;
--SELECT AVG(tmp.name),MAX(tmp.id),COUNT(*) FROM tmp WHERE tmp.name < 30 AND tmp.name < (SELECT * FROM tmp) AND tmp.name IS NULL;


CREATE TABLE tmp(name VARCHAR(128), id INT);
INSERT INTO tmp VALUES('Jack',20);
INSERT INTO tmp VALUES('Mike',NULL);
INSERT INTO tmp VALUES('Mike', NULL);
SELECT * FROM tmp;
SELECT * FROM tmp WHERE tmp.id > 10;