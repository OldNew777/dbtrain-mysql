--SELECT AVG(tmp.name),MAX(tmp.id),COUNT(*) FROM tmp WHERE tmp.name < 30 AND tmp.name < (SELECT * FROM tmp) AND tmp.name IS NULL;

-- CREATE DATABASE THU;
-- CREATE DATABASE THU1;

-- DROP DATABASE THU;
-- DROP DATABASE THU1;



-- CREATE DATABASE THU1;
-- USE THU1;
-- CREATE TABLE student(name VARCHAR(1800), id INT);

CREATE DATABASE THU;
USE THU;
CREATE TABLE order(id INT, customer VARCHAR(64), date DATE NOT NULL);

INSERT INTO order VALUES(1, 'Jack', 2022-01-07);

SELECT * FROM order WHERE order.date = 2022-01-07;
SELECT * FROM order WHERE order.date > 2022-02-29;
SELECT * FROM order WHERE order.date < 2023-01-07;

CREATE TABLE student(name VARCHAR(64), id INT);
CREATE TABLE math(id INT, score FLOAT NOT NULL, PRIMARY KEY(id));

INSERT INTO math VALUES(20, 90.5);
INSERT INTO math VALUES(21, 88.5);
INSERT INTO math VALUES(872, 0);
INSERT INTO math VALUES(873, NULL);
INSERT INTO math VALUES(874, 30);
INSERT INTO math VALUES(875, 78.5);
INSERT INTO math VALUES(875, 78.5);

UPDATE math SET score = NULL WHERE math.id > 1;
UPDATE math SET id = 20 WHERE math.score = 0;

SELECT * FROM math;
SELECT * FROM math LIMIT 2 OFFSET 1;

INSERT INTO student VALUES('Jack',20);
INSERT INTO student VALUES('bob',20);
INSERT INTO student VALUES('alice',21);
INSERT INTO student VALUES('Mike',20);


-- INSERT INTO student VALUES('Mike',NULL);
-- INSERT INTO student VALUES(NULL,872);

SELECT * FROM student, math WHERE student.id = math.id;
SELECT * FROM student WHERE student.name = 'Jack' AND student.id = 20;
SELECT * FROM student WHERE student.name IN ('Jack', 'Mike');

-- UPDATE student SET id = 777 WHERE student.name IN ('Jack', 'Mike');

SELECT * FROM student WHERE student.id > 30;
SELECT * FROM student WHERE student.name = 'Jack';
ALTER TABLE student ADD INDEX(id);
SELECT * FROM student WHERE student.id > 30;


-- DUMP TO FILE 'dump.txt' FROM TABLE student;
-- LOAD FROM FILE 'dump.txt' TO TABLE student;

SELECT * FROM student WHERE student.name = 'Jack';



SELECT * FROM student;
DESC student;


-- DROP DATABASE THU;


-- CREATE TABLE student1(name VARCHAR(2000), id INT);
-- CREATE TABLE student2(name VARCHAR(2000), id INT);
-- CREATE TABLE student3(name VARCHAR(2000), id INT);
-- CREATE TABLE student4(name VARCHAR(2000), id INT);
-- CREATE TABLE student5(name VARCHAR(2000), id INT);
-- CREATE TABLE student6(name VARCHAR(2000), id INT);
-- CREATE TABLE student7(name VARCHAR(2000), id INT);
-- CREATE TABLE student8(name VARCHAR(2000), id INT);
-- CREATE TABLE student9(name VARCHAR(2000), id INT);
-- CREATE TABLE student10(name VARCHAR(2000), id INT);
-- CREATE TABLE student11(name VARCHAR(2000), id INT);
-- CREATE TABLE student12(name VARCHAR(2000), id INT);
-- CREATE TABLE student13(name VARCHAR(2000), id INT);
-- CREATE TABLE student14(name VARCHAR(2000), id INT);
-- CREATE TABLE student15(name VARCHAR(2000), id INT);
-- CREATE TABLE student16(name VARCHAR(2000), id INT);
-- CREATE TABLE student17(name VARCHAR(2000), id INT);
-- CREATE TABLE student18(name VARCHAR(2000), id INT);
-- CREATE TABLE student19(name VARCHAR(2000), id INT);
-- CREATE TABLE student20(name VARCHAR(2000), id INT);
-- CREATE TABLE student21(name VARCHAR(2000), id INT);
-- CREATE TABLE student22(name VARCHAR(2000), id INT);
-- CREATE TABLE student23(name VARCHAR(2000), id INT);
-- CREATE TABLE student24(name VARCHAR(2000), id INT);
-- CREATE TABLE student25(name VARCHAR(2000), id INT);
-- CREATE TABLE student26(name VARCHAR(2000), id INT);
-- CREATE TABLE student27(name VARCHAR(2000), id INT);
-- CREATE TABLE student28(name VARCHAR(2000), id INT);
-- CREATE TABLE student29(name VARCHAR(2000), id INT);
-- CREATE TABLE student30(name VARCHAR(2000), id INT);
-- CREATE TABLE student31(name VARCHAR(2000), id INT);
-- CREATE TABLE student32(name VARCHAR(2000), id INT);
-- CREATE TABLE student33(name VARCHAR(2000), id INT);
-- CREATE TABLE student34(name VARCHAR(2000), id INT);
-- CREATE TABLE student35(name VARCHAR(2000), id INT);
-- CREATE TABLE student36(name VARCHAR(2000), id INT);
-- CREATE TABLE student37(name VARCHAR(2000), id INT);
-- CREATE TABLE student38(name VARCHAR(2000), id INT);
-- CREATE TABLE student39(name VARCHAR(2000), id INT);
-- CREATE TABLE student40(name VARCHAR(2000), id INT);
-- CREATE TABLE student41(name VARCHAR(2000), id INT);
-- CREATE TABLE student42(name VARCHAR(2000), id INT);
-- CREATE TABLE student43(name VARCHAR(2000), id INT);
-- CREATE TABLE student44(name VARCHAR(2000), id INT);
-- CREATE TABLE student45(name VARCHAR(2000), id INT);
-- CREATE TABLE student46(name VARCHAR(2000), id INT);
-- CREATE TABLE student47(name VARCHAR(2000), id INT);
-- CREATE TABLE student48(name VARCHAR(2000), id INT);
-- CREATE TABLE student49(name VARCHAR(2000), id INT);
-- CREATE TABLE student50(name VARCHAR(2000), id INT);
-- CREATE TABLE student51(name VARCHAR(2000), id INT);
-- CREATE TABLE student52(name VARCHAR(2000), id INT);
-- CREATE TABLE student53(name VARCHAR(2000), id INT);
-- CREATE TABLE student54(name VARCHAR(2000), id INT);
-- CREATE TABLE student55(name VARCHAR(2000), id INT);
-- CREATE TABLE student56(name VARCHAR(2000), id INT);
-- CREATE TABLE student57(name VARCHAR(2000), id INT);
-- CREATE TABLE student58(name VARCHAR(2000), id INT);
-- CREATE TABLE student59(name VARCHAR(2000), id INT);
-- CREATE TABLE student60(name VARCHAR(2000), id INT);
-- CREATE TABLE student61(name VARCHAR(2000), id INT);
-- CREATE TABLE student62(name VARCHAR(2000), id INT);
-- CREATE TABLE student63(name VARCHAR(2000), id INT);
-- CREATE TABLE student64(name VARCHAR(2000), id INT);
-- CREATE TABLE student65(name VARCHAR(2000), id INT);
-- CREATE TABLE student66(name VARCHAR(2000), id INT);
-- CREATE TABLE student67(name VARCHAR(2000), id INT);
-- CREATE TABLE student68(name VARCHAR(2000), id INT);
-- CREATE TABLE student69(name VARCHAR(2000), id INT);
-- CREATE TABLE student70(name VARCHAR(2000), id INT);

SHOW TABLES; 
DESC student;
ALTER TABLE student ADD PRIMARY KEY (name);

INSERT INTO order VALUES(1, 'Mike', 2022-01-07);
INSERT INTO order VALUES(2, 'Jack', 2022-01-06);
INSERT INTO order VALUES(3, 'TOM', 2022-01-05);
SELECT * FROM order;
-- ALTER TABLE order ADD PRIMARY KEY (customer, date);
-- DESC order;
-- ALTER TABLE order DROP PRIMARY KEY (date);
DESC order;
SHOW TABLES;

CREATE TABLE teacher (id INT, customer VARCHAR(64), num INT);
INSERT INTO teacher VALUES(1, 'TOM', 4);
-- SELECT * FROM teacher WHERE teacher.customer = 'TOM';

INSERT INTO teacher VALUES(2, 'Jack', 5);
INSERT INTO teacher VALUES(3, 'ZYH', 6);
-- INSERT INTO teacher VALUES(NULL, 'ZYH', 6);
SELECT * FROM teacher;
CREATE TABLE teacher2 (id2 INT, customer2 VARCHAR(64), num2 INT, FOREIGN KEY (id2, num2) REFERENCES teacher (id, num));
INSERT INTO teacher2 VALUES(1, 'TOM', 4);
INSERT INTO teacher2 VALUES(2, 'Jack', 5);
INSERT INTO teacher2 VALUES(3, 'ZYH', 6);
INSERT INTO teacher2 VALUES(0, 'TOM', 4);
INSERT INTO teacher2 VALUES(4, 'Jack', 5);
INSERT INTO teacher2 VALUES(3, 'ZYH', 2);
SELECT * FROM teacher2;
-- DESC SHADOW teacher2;
-- DROP TABLE teacher;
-- DESC SHADOW teacher2;
-- INSERT INTO teacher2 VALUES(3, 'ZYH', 2);
-- SELECT * FROM teacher2;
DESC SHADOW teacher2;
-- DROP TABLE teacher;
INSERT INTO teacher2 VALUES(4, 'Jack', 5);
DESC SHADOW teacher2;
ALTER TABLE teacher2 DROP FOREIGN KEY id2;

DESC teacher;
DESC SHADOW teacher;
DESC teacher2;
DESC SHADOW teacher2;
-- INSERT INTO teacher2 VALUES(4, 'Jack', 5);
ALTER TABLE teacher2 ADD FOREIGN KEY(id2) REFERENCES teacher (id);
INSERT INTO teacher2 VALUES(4, 'Jack', 5);
-- DESC SHADOW teacher2;

CREATE TABLE teacher3 (id INT, customer VARCHAR(64), num INT);
INSERT INTO teacher3 VALUES(4, 'Jack', 5);
-- INSERT INTO teacher3 VALUES(4, 'Tom', 6);
ALTER TABLE teacher3 ADD UNIQUE (id);
INSERT INTO teacher3 VALUES(4, 'Tom', 6);



