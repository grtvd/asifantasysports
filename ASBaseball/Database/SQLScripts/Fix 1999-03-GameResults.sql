connect "z:\tag999\asbaseball\database\asbaseball.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

alter table GameResult
	drop status,
	drop NumOffGameStats,
	drop OffGameStat01Player,
	drop OffGameStat01Date,
	drop OffGameStat02Player,
	drop OffGameStat02Date,
	drop OffGameStat03Player,
	drop OffGameStat03Date,
	drop OffGameStat04Player,
	drop OffGameStat04Date,
	drop OffGameStat05Player,
	drop OffGameStat05Date,
	drop OffGameStat06Player,
	drop OffGameStat06Date,
	drop OffGameStat07Player,
	drop OffGameStat07Date,
	drop OffGameStat08Player,
	drop OffGameStat08Date,
	drop OffGameStat09Player,
	drop OffGameStat09Date,
	drop NumDefGameStats,
	drop DefGameStat01Player,
	drop DefGameStat01Date,
	drop DefGameStat02Player,
	drop DefGameStat02Date,
	drop DefGameStat03Player,
	drop DefGameStat03Date,
	drop DefGameStat04Player,
	drop DefGameStat04Date,
	drop DefGameStat05Player,
	drop DefGameStat05Date,
	drop DefGameStat06Player,
	drop DefGameStat06Date,
	drop DefGameStat07Player,
	drop DefGameStat07Date,
	drop DefGameStat08Player,
	drop DefGameStat08Date,
	drop DefGameStat09Player,
	drop DefGameStat09Date,
	drop DefGameStat10Player,
	drop DefGameStat10Date;

alter table GameResult
	add NumOffPlayers smallint not null,

	add OffPlayer01 Dom_PlayerID,
	add OffPlayer01Points smallint,
	add OffPlayer01Dates varchar(512),

	add OffPlayer02 Dom_PlayerID,
	add OffPlayer02Points smallint,
	add OffPlayer02Dates varchar(512),

	add OffPlayer03 Dom_PlayerID,
	add OffPlayer03Points smallint,
	add OffPlayer03Dates varchar(512),

	add OffPlayer04 Dom_PlayerID,
	add OffPlayer04Points smallint,
	add OffPlayer04Dates varchar(512),

	add OffPlayer05 Dom_PlayerID,
	add OffPlayer05Points smallint,
	add OffPlayer05Dates varchar(512),

	add OffPlayer06 Dom_PlayerID,
	add OffPlayer06Points smallint,
	add OffPlayer06Dates varchar(512),

	add OffPlayer07 Dom_PlayerID,
	add OffPlayer07Points smallint,
	add OffPlayer07Dates varchar(512),

	add OffPlayer08 Dom_PlayerID,
	add OffPlayer08Points smallint,
	add OffPlayer08Dates varchar(512),

	add OffPlayer09 Dom_PlayerID,
	add OffPlayer09Points smallint,
	add OffPlayer09Dates varchar(512),

	add NumDefPlayers smallint not null,

	add DefPlayer01 Dom_PlayerID,
	add DefPlayer01Points smallint,
	add DefPlayer01Dates varchar(512),

	add DefPlayer02 Dom_PlayerID,
	add DefPlayer02Points smallint,
	add DefPlayer02Dates varchar(512),

	add DefPlayer03 Dom_PlayerID,
	add DefPlayer03Points smallint,
	add DefPlayer03Dates varchar(512),

	add DefPlayer04 Dom_PlayerID,
	add DefPlayer04Points smallint,
	add DefPlayer04Dates varchar(512),

	add DefPlayer05 Dom_PlayerID,
	add DefPlayer05Points smallint,
	add DefPlayer05Dates varchar(512),

	add DefPlayer06 Dom_PlayerID,
	add DefPlayer06Points smallint,
	add DefPlayer06Dates varchar(512),

	add DefPlayer07 Dom_PlayerID,
	add DefPlayer07Points smallint,
	add DefPlayer07Dates varchar(512),

	add DefPlayer08 Dom_PlayerID,
	add DefPlayer08Points smallint,
	add DefPlayer08Dates varchar(512),

	add DefPlayer09 Dom_PlayerID,
	add DefPlayer09Points smallint,
	add DefPlayer09Dates varchar(512);

commit work;

/******************************************************************************/

alter table ScheduleDay
	add Status char(1) not null;

update ScheduleDay set Status = "N";

commit work;

/******************************************************************************/
exit;
