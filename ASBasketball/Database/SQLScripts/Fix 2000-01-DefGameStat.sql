connect "z:\tag999\asbasketball\database\asbasketball.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

create table DefGameStat
(
	PlayerID Dom_PlayerID not null,
	StatPeriod char(1) not null,
	StatDate date not null, /* 12/30/1899 dates are considered null*/

	TotalPoints smallint not null,

	constraint DefGameStatIDKey primary key (PlayerID, StatPeriod, StatDate),
	constraint DefGameStatPlayerIDKey foreign key (PlayerID)
		references ProfPlayer (PlayerID)
);

/******************************************************************************/

commit work;

/******************************************************************************/
exit;
