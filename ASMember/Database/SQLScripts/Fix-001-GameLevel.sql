connect "h:\tag999\asmember\database\asmember.gdb"
user "sysdba" password "!!!!!!!!";

alter table Partic
	add GameLevel char(1) not null,
	add UpgradeDate date,
	add UpgradePrice double precision;

update Partic
	set GameLevel = "S",
	UpgradePrice = 0.0;

commit work;
exit;
