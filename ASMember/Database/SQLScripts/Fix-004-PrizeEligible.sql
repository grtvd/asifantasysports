connect "z:\tag999\asmember\database\asmember.gdb"
user "sysdba" password "!!!!!!!!";

alter table Partic
	add PrizeEligible char(1) not null;

update Partic
	set PrizeEligible = "F";

commit work;
exit;
