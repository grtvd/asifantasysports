connect "h:\tag999\asfantasy\asfootball\database\asfootball.gdb"
user "sysdba" password "!!!!!!!!";

alter table ProfPlayer
	add GameStatus char(1) not null;

update ProfPlayer set
	GameStatus = "A";

commit work;
exit;
