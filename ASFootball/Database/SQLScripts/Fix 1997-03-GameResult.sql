connect "h:\tag999\asfantasy\asfootball\database\asfootball.gdb"
user "sysdba" password "!!!!!!!!";

drop table GameResult;

create table GameResult
(
	TeamID Dom_TeamID not null,
	GameDate date not null,
	OppTeamID Dom_TeamID not null,

	TotalPoints smallint,

	NumOffGameStats smallint,
	OffGameStat01Player Dom_PlayerID,
	OffGameStat01Date date,
	OffGameStat02Player Dom_PlayerID,
	OffGameStat02Date date,
	OffGameStat03Player Dom_PlayerID,
	OffGameStat03Date date,
	OffGameStat04Player Dom_PlayerID,
	OffGameStat04Date date,
	OffGameStat05Player Dom_PlayerID,
	OffGameStat05Date date,
	OffGameStat06Player Dom_PlayerID,
	OffGameStat06Date date,
	OffGameStat07Player Dom_PlayerID,
	OffGameStat07Date date,
	OffGameStat08Player Dom_PlayerID,
	OffGameStat08Date date,

	NumDefGameStats smallint,
	DefGameStat01Player Dom_PlayerID,
	DefGameStat01Date date,
	DefGameStat02Player Dom_PlayerID,
	DefGameStat02Date date,
	DefGameStat03Player Dom_PlayerID,
	DefGameStat03Date date,
	DefGameStat04Player Dom_PlayerID,
	DefGameStat04Date date,
	DefGameStat05Player Dom_PlayerID,
	DefGameStat05Date date,
	DefGameStat06Player Dom_PlayerID,
	DefGameStat06Date date,
	DefGameStat07Player Dom_PlayerID,
	DefGameStat07Date date,
	DefGameStat08Player Dom_PlayerID,
	DefGameStat08Date date,
	
	primary key (TeamID, GameDate)
);   
			  

commit work;
exit;
