connect "h:\tag999\asmember\database\asmember.gdb"
user "sysdba" password "!!!!!!!!";

alter table Member
	add SignupSource varchar(25),
	add EmailInvalid char(1) not null;

update Member
	set EmailInvalid = "F";

commit work;
exit;
