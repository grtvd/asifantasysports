connect "h:\tag999\asfantasy\asfootball\database\asfootball.gdb"
user "sysdba" password "!!!!!!!!";

alter table ProfPlayer add TotalPoints smallint, add LastWeeksPoints smallint;

update ProfPlayer set TotalPoints = 0, LastWeeksPoints = 0;

commit work;
exit;
