connect "z:\tag999\ashockey\database\ashockey.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

alter table Team
	drop OffensePlayer01,
	drop OffensePlayer02,
	drop OffensePlayer03,
	drop OffensePlayer04,
	drop OffensePlayer05,
	drop OffensePlayer06,
	drop OffensePlayer07,
	drop OffensePlayer08,
	drop OffensePlayer09,
	drop OffensePlayer10,
	drop DefensePlayer01,
	drop DefensePlayer02;

alter table Team
	add SkaterPlayer01 Dom_PlayerID,
	add SkaterPlayer02 Dom_PlayerID,
	add SkaterPlayer03 Dom_PlayerID,
	add SkaterPlayer04 Dom_PlayerID,
	add SkaterPlayer05 Dom_PlayerID,
	add SkaterPlayer06 Dom_PlayerID,
	add SkaterPlayer07 Dom_PlayerID,
	add SkaterPlayer08 Dom_PlayerID,
	add SkaterPlayer09 Dom_PlayerID,
	add SkaterPlayer10 Dom_PlayerID,
	add GoaliePlayer01 Dom_PlayerID;

commit work;

/******************************************************************************/

drop table OffGameStat;
commit work;

/******************************************************************************/

create table OffGameStat
(
	PlayerID Dom_PlayerID not null,
	StatPeriod char(1) not null,
	StatDate date not null, /* 12/30/1899 dates are considered null*/

	TotalPoints smallint not null,

	GamesPlayed smallint not null,
	Goals smallint not null,
	Assists smallint not null,
	Points smallint not null,
	Shots smallint not null,
	PlusMinus smallint not null,

	PowerPlayGoals smallint not null,
	PowerPlayAssists smallint not null,
	ShortHandedGoals smallint not null,
	ShortHandedAssists smallint not null,
	GameWinningGoals smallint not null,
	GameTyingGoals smallint not null,
	EmptyNetGoals smallint not null,
	OvertimeGoals smallint not null,

	MajorPenalties smallint not null,
	MinorPenalties smallint not null,
	PenaltyMinutes smallint not null,
	HatTricks smallint not null,
	Fights smallint not null,

	constraint OffGameStatIDKey primary key (PlayerID, StatPeriod, StatDate),
	constraint OffGameStatPlayerIDKey foreign key (PlayerID)
		references ProfPlayer (PlayerID)
);

commit work;

/******************************************************************************/

drop table DefGameStat;
commit work;

/******************************************************************************/

create table DefGameStat
(
	PlayerID Dom_PlayerID not null,
	StatPeriod char(1) not null,
	StatDate date not null, /* 12/30/1899 dates are considered null*/

	TotalPoints smallint not null,

	GamesPlayed smallint not null,
	GamesStarted smallint not null,
	MinutesPlayed smallint not null,

	Wins smallint not null,
	Losses smallint not null,
	Ties smallint not null,

	GoalsAgainst smallint not null,
	EmptyNetGoalsAgainst smallint not null,
	ShotsAgainst smallint not null,
	Saves smallint not null,
	Shutouts smallint not null,

	MajorPenalties smallint not null,
	PenaltyMinutes smallint not null,
	Fights smallint not null,

	constraint DefGameStatIDKey primary key (PlayerID, StatPeriod, StatDate),
	constraint DefGameStatPlayerIDKey foreign key (PlayerID)
		references ProfPlayer (PlayerID)
);

commit work;

/******************************************************************************/

alter table GameResult
	drop DefPlayer02,
	drop DefPlayer02Points,
	drop DefPlayer02Dates;

commit work;

/******************************************************************************/
exit;
