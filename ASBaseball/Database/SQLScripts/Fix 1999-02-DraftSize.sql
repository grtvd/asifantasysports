connect "z:\tag999\asbaseball\database\asbaseball.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

drop table DraftOrder;
commit work;

/******************************************************************************/

create table DraftOrder
(
	LeagueID Dom_LeagueID not null primary key,	/* auto generated */

	NumRounds smallint not null,
	NumTeams smallint not null,

	Round01 varchar(256),
	Round02 varchar(256),
	Round03 varchar(256),
	Round04 varchar(256),
	Round05 varchar(256),
	Round06 varchar(256),
	Round07 varchar(256),
	Round08 varchar(256),
	Round09 varchar(256),
	Round10 varchar(256),
	Round11 varchar(256),
	Round12 varchar(256),
	Round13 varchar(256),
	Round14 varchar(256),
	Round15 varchar(256),
	Round16 varchar(256),
	Round17 varchar(256),
	Round18 varchar(256),
	Round19 varchar(256),
	Round20 varchar(256),
	Round21 varchar(256),
	Round22 varchar(256),
	Round23 varchar(256),
	Round24 varchar(256),
	Round25 varchar(256),
	Round26 varchar(256),
	Round27 varchar(256),
	Round28 varchar(256),

	constraint DraftOrderLeagueIDKey foreign key (LeagueID)
		references League (LeagueID)
);

commit work;

/******************************************************************************/

drop table DraftResult;
commit work;

/******************************************************************************/

create table DraftResult
(
	LeagueID Dom_LeagueID not null primary key,

	NumRounds smallint not null,
	NumTeams smallint not null,

	Round01 varchar(512),
	Round02 varchar(512),
	Round03 varchar(512),
	Round04 varchar(512),
	Round05 varchar(512),
	Round06 varchar(512),
	Round07 varchar(512),
	Round08 varchar(512),
	Round09 varchar(512),
	Round10 varchar(512),
	Round11 varchar(512),
	Round12 varchar(512),
	Round13 varchar(512),
	Round14 varchar(512),
	Round15 varchar(512),
	Round16 varchar(512),
	Round17 varchar(512),
	Round18 varchar(512),
	Round19 varchar(512),
	Round20 varchar(512),
	Round21 varchar(512),
	Round22 varchar(512),
	Round23 varchar(512),
	Round24 varchar(512),
	Round25 varchar(512),
	Round26 varchar(512),
	Round27 varchar(512),
	Round28 varchar(512),

	constraint DraftResultLeagueIDKey foreign key (LeagueID)
		references League (LeagueID)
);

commit work;

/******************************************************************************/
exit;
