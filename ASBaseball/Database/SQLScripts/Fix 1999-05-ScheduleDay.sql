connect "z:\tag999\asbaseball\database\asbaseball.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

alter table ScheduleDay
	add EarlyProfGameDateTime date not null;

commit work;

/******************************************************************************/

update ScheduleDay set EarlyProfGameDateTime = EarlyProfGameDate + 0.2916667;

commit work;

/******************************************************************************/

alter table ScheduleDay
	drop EarlyProfGameDate;

commit work;

/******************************************************************************/

exit;
