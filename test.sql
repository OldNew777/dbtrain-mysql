--CREATE TABLE tmp(name VARCHAR(128), id INT, PRIMARY KEY (id, name));
--INSERT INTO tmp VALUES ('peichen', 2018013400),('chenxin', 2018013401);
--SELECT * FROM tmp;
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
CREATE TABLE student(name VARCHAR(1800), id INT, PRIMARY KEY (name, id));


INSERT INTO student VALUES('Jack',20);
INSERT INTO student VALUES('Jack',20);
INSERT INTO student VALUES('Jack',21);
INSERT INTO student VALUES('Mike',20);


INSERT INTO student VALUES('Mike',NULL);
INSERT INTO student VALUES(NULL,872);


-- SELECT * FROM student WHERE student.name IN ('Jack', 'Mike');

-- UPDATE student SET id = 777 WHERE student.name IN ('Jack', 'Mike');

SELECT * FROM student WHERE student.id > 30;
-- SELECT * FROM student WHERE student.name = 'Jack';
-- ALTER TABLE student ADD INDEX(id);
-- SELECT * FROM student WHERE student.id > 30;


-- DUMP TO FILE 'dump.txt' FROM TABLE student;

-- SELECT * FROM student WHERE student.name = 'Jack';



-- SELECT * FROM student;
DESC student;
DROP DATABASE THU;


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

-- SHOW TABLES;
