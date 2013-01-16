drop database if exists davinciwars;
create database if not exists davinciwars;
use davinciwars;


create table City( idCity INT PRIMARY KEY AUTO_INCREMENT, cityName varchar(40), regent varchar(45), location POINT);


create table Player( idPlayer INTEGER PRIMARY KEY AUTO_INCREMENT,  username varchar(50) UNIQUE, password varchar(50), email varchar(100), idCity INT,
logged varchar(2),
FOREIGN KEY (idCity) REFERENCES City(idCity) 
);


create table Buddy( idBuddy INTEGER PRIMARY KEY AUTO_INCREMENT, idPlayer INT
, idFriend INT,
FOREIGN KEY (idPlayer) REFERENCES Player(idPlayer),
FOREIGN KEY (idFriend) REFERENCES Player(idPlayer)
);


insert into City values(null,"Florence", "None", POINT(10,10) );
insert into City values(null,"Milan", "None", POINT(30,10) );
insert into City values(null,"Venice", "None", POINT(50,50) );
insert into City values(null,"Pisa", "None", POINT(30,40) );
insert into City values(null,"Napoles", "None", POINT(80,100) );

create user 'dvadmin' identified by 'dvWars';
grant all privileges on davinciwars.* to 'dvadmin';





