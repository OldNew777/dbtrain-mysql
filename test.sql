CREATE TABLE tmp(name VARCHAR(128), id INT, PRIMARY KEY (id, name));
--INSERT INTO tmp VALUES ('peichen', 2018013400),('chenxin', 2018013401);
--SELECT * FROM tmp;
--SELECT AVG(tmp.name),MAX(tmp.id),COUNT(*) FROM tmp WHERE tmp.name < 30 AND tmp.name < (SELECT * FROM tmp) AND tmp.name IS NULL;


CREATE TABLE student(name VARCHAR(2000), id INT);
INSERT INTO student VALUES('Jack',20);
INSERT INTO student VALUES('Mike',NULL);
INSERT INTO student VALUES('Mike', NULL);
INSERT INTO student VALUES(NULL,872);
SELECT * FROM student;
SELECT * FROM student WHERE student.id > 10;