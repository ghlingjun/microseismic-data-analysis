username: microseismic
password: yunling

-- create database
create database microseismic;

-- grant 
grant create, select, update, delete, alter on microseismic.* to microseismic@"%" identified by "yunling";

-- create tables
create table msdata (id MEDIUMINT NOT NULL AUTO_INCREMENT, name CHAR(30) NOT NULL, x float, y float,
z float, longitude float, latitude float, altitude float, pressure float, time DATETIME,
primary key (id))

-- init
insert into msdata(name, x, y, z, time) values('C1', 1.1, 3.2, 2.1, now());
insert into msdata(name, x, y, z, time) values('C2', 5.3, 4.3, 3.2, now());
insert into msdata(name, x, y, z, time) values('C3', 3.3, 3.1, 5.3, now());
insert into msdata(name, x, y, z, time) values('C4', 4.3, 2.1, 2.3, now());
