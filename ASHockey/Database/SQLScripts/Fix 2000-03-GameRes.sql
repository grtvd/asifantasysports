connect "z:\tag999\ashockey\database\ashockey.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

alter table GameResult
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
	add DefPlayer09Dates varchar(512),

	add DefPlayer10 Dom_PlayerID,
	add DefPlayer10Points smallint,
	add DefPlayer10Dates varchar(512);

commit work;

/******************************************************************************/
exit;
