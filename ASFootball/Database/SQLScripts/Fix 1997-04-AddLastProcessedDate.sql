connect "h:\tag999\asfantasy\asfootball\database\asfootball.gdb"
user "sysdba" password "!!!!!!!!";

alter table League add LastProcessedDate date;

update League set LastProcessedDate = "8/29/1997";

commit work;
exit;
