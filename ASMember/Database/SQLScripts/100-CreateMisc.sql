create database "h:\tag999\asmember\database\asmembermisc.gdb"
user "sysdba" password "!!!!!!!!"
page_size 1024;

create table MailList
(
	Email varchar(50),
	ReceivedDateTime date,
	Source varchar(25),
	Status char(1) not null
);

commit work;
exit;
