connect "z:\tag999\asfootball\database\asfootball.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

drop table ScheduleDay;

commit work;

/******************************************************************************/

create table ScheduleDay
(
	LeagueID Dom_LeagueID not null,
	GameDate date not null,

	Status char(1) not null,

	EarlyProfGameDateTime date not null,
	LateProfGameDate date not null,
	ProfGameWeek smallint not null,

	NumScheduleGames smallint not null,
	
	SchedGame01VisitTeamID Dom_TeamID,
	SchedGame01HomeTeamID Dom_TeamID,
	SchedGame01VisitScore smallint,
	SchedGame01HomeScore smallint,
		
	SchedGame02VisitTeamID Dom_TeamID,
	SchedGame02HomeTeamID Dom_TeamID,
	SchedGame02VisitScore smallint,
	SchedGame02HomeScore smallint,
		
	SchedGame03VisitTeamID Dom_TeamID,
	SchedGame03HomeTeamID Dom_TeamID,
	SchedGame03VisitScore smallint,
	SchedGame03HomeScore smallint,
		
	SchedGame04VisitTeamID Dom_TeamID,
	SchedGame04HomeTeamID Dom_TeamID,
	SchedGame04VisitScore smallint,
	SchedGame04HomeScore smallint,
		
	SchedGame05VisitTeamID Dom_TeamID,
	SchedGame05HomeTeamID Dom_TeamID,
	SchedGame05VisitScore smallint,
	SchedGame05HomeScore smallint,
		
	SchedGame06VisitTeamID Dom_TeamID,
	SchedGame06HomeTeamID Dom_TeamID,
	SchedGame06VisitScore smallint,
	SchedGame06HomeScore smallint,
		
	SchedGame07VisitTeamID Dom_TeamID,
	SchedGame07HomeTeamID Dom_TeamID,
	SchedGame07VisitScore smallint,
	SchedGame07HomeScore smallint,
		
	primary key (LeagueID, GameDate),
	constraint ScheduleDayLeagueIDKey foreign key (LeagueID)
		references League (LeagueID)
);

commit work;

/******************************************************************************/

drop table ProfTeamSchedule;

commit work;

/******************************************************************************/

/* ProfTeamSchedule */

create table ProfTeamSchedule
(
	ProfGameWeek smallint not null primary key,

	NumScheduleGames smallint not null,
	
	SchedGame01DateTime date,
	SchedGame01VisitProfTeamID Dom_ProfTeamID,
	SchedGame01HomeProfTeamID Dom_ProfTeamID,
	SchedGame01VisitScore smallint,
	SchedGame01HomeScore smallint,
	
	SchedGame02Date date,
	SchedGame02VisitProfTeamID Dom_ProfTeamID,
	SchedGame02HomeProfTeamID Dom_ProfTeamID,
	SchedGame02VisitScore smallint,
	SchedGame02HomeScore smallint,
	
	SchedGame03Date date,
	SchedGame03VisitProfTeamID Dom_ProfTeamID,
	SchedGame03HomeProfTeamID Dom_ProfTeamID,
	SchedGame03VisitScore smallint,
	SchedGame03HomeScore smallint,
	
	SchedGame04Date date,
	SchedGame04VisitProfTeamID Dom_ProfTeamID,
	SchedGame04HomeProfTeamID Dom_ProfTeamID,
	SchedGame04VisitScore smallint,
	SchedGame04HomeScore smallint,
	
	SchedGame05Date date,
	SchedGame05VisitProfTeamID Dom_ProfTeamID,
	SchedGame05HomeProfTeamID Dom_ProfTeamID,
	SchedGame05VisitScore smallint,
	SchedGame05HomeScore smallint,
	
	SchedGame06Date date,
	SchedGame06VisitProfTeamID Dom_ProfTeamID,
	SchedGame06HomeProfTeamID Dom_ProfTeamID,
	SchedGame06VisitScore smallint,
	SchedGame06HomeScore smallint,
	
	SchedGame07Date date,
	SchedGame07VisitProfTeamID Dom_ProfTeamID,
	SchedGame07HomeProfTeamID Dom_ProfTeamID,
	SchedGame07VisitScore smallint,
	SchedGame07HomeScore smallint,
	
	SchedGame08Date date,
	SchedGame08VisitProfTeamID Dom_ProfTeamID,
	SchedGame08HomeProfTeamID Dom_ProfTeamID,
	SchedGame08VisitScore smallint,
	SchedGame08HomeScore smallint,
	
	SchedGame09Date date,
	SchedGame09VisitProfTeamID Dom_ProfTeamID,
	SchedGame09HomeProfTeamID Dom_ProfTeamID,
	SchedGame09VisitScore smallint,
	SchedGame09HomeScore smallint,
	
	SchedGame10Date date,
	SchedGame10VisitProfTeamID Dom_ProfTeamID,
	SchedGame10HomeProfTeamID Dom_ProfTeamID,
	SchedGame10VisitScore smallint,
	SchedGame10HomeScore smallint,
	
	SchedGame11Date date,
	SchedGame11VisitProfTeamID Dom_ProfTeamID,
	SchedGame11HomeProfTeamID Dom_ProfTeamID,
	SchedGame11VisitScore smallint,
	SchedGame11HomeScore smallint,
	
	SchedGame12Date date,
	SchedGame12VisitProfTeamID Dom_ProfTeamID,
	SchedGame12HomeProfTeamID Dom_ProfTeamID,
	SchedGame12VisitScore smallint,
	SchedGame12HomeScore smallint,
	
	SchedGame13Date date,
	SchedGame13VisitProfTeamID Dom_ProfTeamID,
	SchedGame13HomeProfTeamID Dom_ProfTeamID,
	SchedGame13VisitScore smallint,
	SchedGame13HomeScore smallint,
	
	SchedGame14Date date,
	SchedGame14VisitProfTeamID Dom_ProfTeamID,
	SchedGame14HomeProfTeamID Dom_ProfTeamID,
	SchedGame14VisitScore smallint,
	SchedGame14HomeScore smallint,
	
	SchedGame15Date date,
	SchedGame15VisitProfTeamID Dom_ProfTeamID,
	SchedGame15HomeProfTeamID Dom_ProfTeamID,
	SchedGame15VisitScore smallint,
	SchedGame15HomeScore smallint
);

/******************************************************************************/

commit work;

/******************************************************************************/

exit;
