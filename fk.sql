CREATE DATABASE DATASET;
USE DATASET;
CREATE TABLE REGION (
    R_REGIONKEY    INT,
    R_NAME         VARCHAR(25),
    R_COMMENT      VARCHAR(152)
);
CREATE TABLE NATION (
    N_NATIONKEY      INT,
    N_NAME           VARCHAR(25),
    N_REGIONKEY      INT NOT NULL,
    N_COMMENT        VARCHAR(152),
    PRIMARY KEY (N_NATIONKEY),
    FOREIGN KEY (N_REGIONKEY) REFERENCES REGION(R_REGIONKEY)
);
-- 基础信息测试
DESC REGION;
DESC NATION;
DESC SHADOW REGION;
-- 载入测试：成功
LOAD FROM FILE '../data-with-date/region.csv' TO TABLE REGION;
LOAD FROM FILE '../data-with-date/nation.csv' TO TABLE NATION;
SELECT * FROM NATION;
-- 载入无依赖信息测试：失败
LOAD FROM FILE '../data-with-date/nation_fk_test.csv' TO TABLE NATION;
SELECT * FROM NATION;
-- update主表导致子表没有依赖：失败
UPDATE REGION SET R_REGIONKEY = 6 WHERE REGION.R_REGIONKEY = 2;
-- 删除外键，再次插入重复信息：成功
ALTER TABLE NATION DROP FOREIGN KEY N_REGIONKEY;
LOAD FROM FILE '../data-with-date/nation_fk_test.csv' TO TABLE NATION;
SELECT * FROM NATION;
--增添外键：失败
ALTER TABLE NATION ADD FOREIGN KEY (N_REGIONKEY) REFERENCES REGION(R_REGIONKEY);
--删除重复信息后，再增添外键，再插入重复信息：失败
DELETE FROM NATION WHERE NATION.N_REGIONKEY = 10;
SELECT * FROM NATION;
ALTER TABLE NATION ADD FOREIGN KEY (N_REGIONKEY) REFERENCES REGION(R_REGIONKEY);
LOAD FROM FILE '../data-with-date/nation_fk_test.csv' TO TABLE NATION;
SELECT * FROM REGION;
--删除REGION表：失败
DROP TABLE REGION;
--删除NATION表后删除REGION表：
DROP TABLE NATION;
DROP TABLE REGION;