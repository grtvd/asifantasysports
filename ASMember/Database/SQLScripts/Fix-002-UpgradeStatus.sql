connect "h:\tag999\asmember\database\asmember.gdb"
user "sysdba" password "!!!!!!!!";

alter table Partic
	add UpgradeStatus char(1) not null,
	add TrialDateTime date;

update Partic
	set UpgradeStatus = "X";

commit work;
exit;
