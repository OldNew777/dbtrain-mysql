CREATE DATABASE DATASET;
USE DATASET;
CREATE TABLE REGION (
    R_REGIONKEY    INT,
    R_NAME         VARCHAR(25),
    R_COMMENT      VARCHAR(152),
    PRIMARY KEY (R_REGIONKEY)
);

-- CREATE TABLE PART (
--     P_PARTKEY        INT,
--     P_NAME           VARCHAR(55),
--     P_MFGR           VARCHAR(25),
--     P_BRAND          VARCHAR(10),
--     P_TYPE           VARCHAR(25),
--     P_SIZE           INT,
--     P_CONTAINER      VARCHAR(10),
--     P_RETAILPRICE    FLOAT,
--     P_COMMENT        VARCHAR(23),
--     PRIMARY KEY (P_PARTKEY)
-- );


-- CREATE TABLE NATION (
--     N_NATIONKEY      INT,
--     N_NAME           VARCHAR(25),
--     N_REGIONKEY      INT NOT NULL,
--     N_COMMENT        VARCHAR(152),
--     PRIMARY KEY (N_NATIONKEY),
--     FOREIGN KEY (N_REGIONKEY) REFERENCES REGION(R_REGIONKEY)
-- );

-- CREATE TABLE SUPPLIER (
--     S_SUPPKEY        INT,
--     S_NAME           VARCHAR(25),
--     S_ADDRESS        VARCHAR(40),
--     S_NATIONKEY      INT NOT NULL,
--     S_PHONE          VARCHAR(15),
--     S_ACCTBAL        FLOAT,
--     S_COMMENT        VARCHAR(101),
--     PRIMARY KEY (S_SUPPKEY),
--     FOREIGN KEY (S_NATIONKEY) REFERENCES NATION(N_NATIONKEY)
-- );

-- CREATE TABLE CUSTOMER (
--     C_CUSTKEY        INT,
--     C_NAME           VARCHAR(25),
--     C_ADDRESS        VARCHAR(40),
--     C_NATIONKEY      INT NOT NULL,
--     C_PHONE          VARCHAR(15),
--     C_ACCTBAL        FLOAT,
--     C_MKTSEGMENT     VARCHAR(10),
--     C_COMMENT        VARCHAR(117),
--     PRIMARY KEY (C_CUSTKEY),
--     FOREIGN KEY (C_NATIONKEY) REFERENCES NATION(N_NATIONKEY)
-- );


-- CREATE TABLE PARTSUPP (
--     PS_PARTKEY        INT NOT NULL,
--     PS_SUPPKEY        INT NOT NULL,
--     PS_AVAILQTY       INT,
--     PS_SUPPLYCOST     FLOAT,
--     PS_COMMENT        VARCHAR(199),
--     PRIMARY KEY (PS_PARTKEY, PS_SUPPKEY),
--     FOREIGN KEY (PS_PARTKEY) REFERENCES PART(P_PARTKEY),
--     FOREIGN KEY (PS_SUPPKEY) REFERENCES SUPPLIER(S_SUPPKEY)
-- );

-- CREATE TABLE ORDERS (
--     O_ORDERKEY        INT,
--     O_CUSTKEY         INT NOT NULL,
--     O_ORDERSTATUS     VARCHAR(1),
--     O_TOTALPRICE      FLOAT,
--     O_ORDERDATE       DATE,
--     O_ORDERPRIORITY   VARCHAR(15),
--     O_CLERK           VARCHAR(15),
--     O_SHIPPRIORITY    INT,
--     O_COMMENT         VARCHAR(79),
--     PRIMARY KEY (O_ORDERKEY),
--     FOREIGN KEY (O_CUSTKEY) REFERENCES CUSTOMER(C_CUSTKEY)
-- );


-- CREATE TABLE LINEITEM (
--     L_ORDERKEY        INT NOT NULL,
--     L_PARTKEY         INT NOT NULL,
--     L_SUPPKEY         INT NOT NULL,
--     L_LINENUMBER      INT,
--     L_QUANTITY        FLOAT,
--     L_EXTENDEDPRICE   FLOAT,
--     L_DISCOUNT        FLOAT,
--     L_TAX             FLOAT,
--     L_RETURNFLAG      VARCHAR(1),
--     L_LINESTATUS      VARCHAR(1),
--     L_SHIPDATE        DATE,
--     L_COMMITDATE      DATE,
--     L_RECEIPTDATE     DATE,
--     L_SHIPINSTRUCT    VARCHAR(25),
--     L_SHIPMODE        VARCHAR(10),
--     L_COMMENT         VARCHAR(44),
--     PRIMARY KEY (L_ORDERKEY, L_LINENUMBER),
--     FOREIGN KEY (L_ORDERKEY) REFERENCES ORDERS(O_ORDERKEY),
--     FOREIGN KEY (L_PARTKEY,L_SUPPKEY) REFERENCES PARTSUPP(PS_PARTKEY,PS_SUPPKEY)
-- );
-- DESC NATION;
-- DESC REGION;
-- DESC SUPPLIER;
-- DESC CUSTOMER;
-- DESC PART;
-- DESC PARTSUPP;
-- DESC ORDERS;
-- DESC LINEITEM;
-- SHOW TABLES;
LOAD FROM FILE '../data-with-date/region.csv' TO TABLE REGION;
LOAD FROM FILE '../data-with-date/region.csv' TO TABLE REGION;
-- LOAD FROM FILE '../data-with-date/nation.csv' TO TABLE NATION;
-- LOAD FROM FILE '../data-with-date/supplier.csv' TO TABLE SUPPLIER;
-- LOAD FROM FILE '../data-with-date/part.csv' TO TABLE PART;
-- SELECT * FROM PART WHERE PART.P_PARTKEY = 340;
-- LOAD FROM FILE '../data-with-date/partsupp.csv' TO TABLE PARTSUPP;
-- LOAD FROM FILE '../data-with-date/customer.csv' TO TABLE CUSTOMER;
-- LOAD FROM FILE '../data-with-date/orders.csv' TO TABLE ORDERS;
-- LOAD FROM FILE '../data-with-date/lineitem.csv' TO TABLE LINEITEM;
-- SELECT * FROM REGION, NATION, SUPPLIER 
-- WHERE REGION.R_REGIONKEY = NATION.N_NATIONKEY
-- AND NATION.N_NATIONKEY = SUPPLIER.S_SUPPKEY;