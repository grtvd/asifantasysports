connect "z:\tag999\asfootball\database\asfootball.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

delete from ProfTeamSchedule;

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID,
					SchedGame15Date,	SchedGame15VisitProfTeamID, SchedGame15HomeProfTeamID) values
	( 1,		15,
					"9/12/1999 13:00:00",		22,							21,
					"9/12/1999",		33,							14,
					"9/12/1999",		2,							11,
					"9/12/1999",		29,							18,
					"9/12/1999",		4,							10,
					"9/12/1999",		6,							28,
					"9/12/1999",		8,							26,
					"9/12/1999",		12,							3,
					"9/12/1999",		16,							1,
					"9/12/1999",		17,							20,
					"9/12/1999",		19,							27,
					"9/12/1999",		13,							9,
					"9/12/1999",		25,							30,
					"9/12/1999",		23,							5,
					"9/13/1999",		15,							7
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID,
					SchedGame15Date,	SchedGame15VisitProfTeamID, SchedGame15HomeProfTeamID) values
	( 2,		15,
					"9/19/1999 13:00:00",		22,							15,
					"9/19/1999",		5,							10,
					"9/19/1999",		7,							12,
					"9/19/1999",		9,							8,
					"9/19/1999",		11,							17,
					"9/19/1999",		30,							29,
					"9/19/1999",		18,							25,
					"9/19/1999",		13,							16,
					"9/19/1999",		23,							33,
					"9/19/1999",		24,							4,
					"9/19/1999",		26,							3,
					"9/19/1999",		27,							21,
					"9/19/1999",		28,							19,
					"9/19/1999",		20,							2,
					"9/20/1999",		1,							6
					);


insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID) values
	( 3,		14,
					"9/26/1999 13:00:00",		1,							14,
					"9/26/1999",		3,							13,
					"9/26/1999",		4,							29,
					"9/26/1999",		5,							33,
					"9/26/1999",		7,							27,
					"9/26/1999",		8,							12,
					"9/26/1999",		11,							24,
					"9/26/1999",		16,							9,
					"9/26/1999",		21,							2,
					"9/26/1999",		26,							23,
					"9/26/1999",		10,							30,
					"9/26/1999",		28,							20,
					"9/26/1999",		19,							17,
					"9/27/1999",		25,							22
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID) values
	( 4,		14,
					"10/3/1999 13:00:00",		22,							6,
					"10/3/1999",		33,							1,
					"10/3/1999",		29,							28,
					"10/3/1999",		30,							23,
					"10/3/1999",		12,							24,
					"10/3/1999",		17,							5,
					"10/3/1999",		18,							3,
					"10/3/1999",		20,							7,
					"10/3/1999",		21,							19,
					"10/3/1999",		14,							4,
					"10/3/1999",		27,							16,
					"10/3/1999",		10,							25,
					"10/3/1999",		13,							26,
					"10/4/1999",		2,							15
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID) values
	( 5,		14,
					"10/10/1999 13:00:00",		1,							18,
					"10/10/1999",		33,							10,
					"10/10/1999",		3,							16,
					"10/10/1999",		4,							5,
					"10/10/1999",		6,							21,
					"10/10/1999",		7,							13,
					"10/10/1999",		15,							11,
					"10/10/1999",		17,							12,
					"10/10/1999",		19,							22,
					"10/10/1999",		23,							2,
					"10/10/1999",		24,							8,
					"10/10/1999",		25,							14,
					"10/10/1999",		27,							9,
					"10/11/1999",		30,							20
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID) values
	( 6,		14,
					"10/17/1999 13:00:00",		29,							25,
					"10/17/1999",		5,							30,
					"10/17/1999",		9,							7,
					"10/17/1999",		11,							20,
					"10/17/1999",		15,							17,
					"10/17/1999",		16,							8,
					"10/17/1999",		13,							2,
					"10/17/1999",		21,							3,
					"10/17/1999",		23,							4,
					"10/17/1999",		14,							1,
					"10/17/1999",		26,							24,
					"10/17/1999",		10,							18,
					"10/17/1999",		28,							22,
					"10/18/1999",		6,							19
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID) values
	( 7,		14,
					"10/21/1999 20:20:00",		12,							33,
					"10/24/1999",		2,							26,
					"10/24/1999",		3,							27,
					"10/24/1999",		4,							11,
					"10/24/1999",		5,							14,
					"10/24/1999",		7,							17,
					"10/24/1999",		8,							29,
					"10/24/1999",		9,							24,
					"10/24/1999",		18,							19,
					"10/24/1999",		20,							13,
					"10/24/1999",		21,							15,
					"10/24/1999",		25,							16,
					"10/24/1999",		28,							6,
					"10/25/1999",		1,							23
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID) values
	( 8,		14,
					"10/31/1999 13:00:00",		2,							33,
					"10/31/1999",		29,							1,
					"10/31/1999",		3,							28,
					"10/31/1999",		5,							18,
					"10/31/1999",		6,							11,
					"10/31/1999",		30,							4,
					"10/31/1999",		15,							13,
					"10/31/1999",		16,							7,
					"10/31/1999",		17,							22,
					"10/31/1999",		19,							21,
					"10/31/1999",		14,							10,
					"10/31/1999",		24,							12,
					"10/31/1999",		27,							8,
					"11/1/1999",		26,							9
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID) values
	( 9,		14,
					"11/7/1999 13:00:00",		22,							20,
					"11/7/1999",		33,							5,
					"11/7/1999",		2,							28,
					"11/7/1999",		3,							9,
					"11/7/1999",		4,							26,
					"11/7/1999",		7,							24,
					"11/7/1999",		30,							1,
					"11/7/1999",		12,							11,
					"11/7/1999",		21,							29,
					"11/7/1999",		23,							25,
					"11/7/1999",		14,							8,
					"11/7/1999",		27,							18,
					"11/7/1999",		10,							15,
					"11/8/1999",		6,							16
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID,
					SchedGame15Date,	SchedGame15VisitProfTeamID, SchedGame15HomeProfTeamID) values
	( 10,		15,
					"11/14/1999 13:00:00",		33,							30,
					"11/14/1999",		29,							14,
					"11/14/1999",		5,							23,
					"11/14/1999",		8,							22,
					"11/14/1999",		9,							6,
					"11/14/1999",		11,							19,
					"11/14/1999",		12,							27,
					"11/14/1999",		15,							2,
					"11/14/1999",		16,							3,
					"11/14/1999",		24,							13,
					"11/14/1999",		25,							18,
					"11/14/1999",		10,							4,
					"11/14/1999",		28,							21,
					"11/14/1999",		7,							26,
					"11/15/1999",		20,							17
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID,
					SchedGame15Date,	SchedGame15VisitProfTeamID, SchedGame15HomeProfTeamID) values
	( 11,		15,
					"11/21/1999 13:00:00",		1,							27,
					"11/21/1999",		33,							4,
					"11/21/1999",		2,							20,
					"11/21/1999",		29,							5,
					"11/21/1999",		3,							24,
					"11/21/1999",		6,							22,
					"11/21/1999",		8,							9,
					"11/21/1999",		11,							21,
					"11/21/1999",		17,							15,
					"11/21/1999",		19,							28,
					"11/21/1999",		23,							10,
					"11/21/1999",		14,							25,
					"11/21/1999",		26,							12,
					"11/21/1999",		18,							30,
					"11/22/1999",		13,							7
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID,
					SchedGame15Date,	SchedGame15VisitProfTeamID, SchedGame15HomeProfTeamID) values
	( 12,		15,
					"11/25/1999 12:40:00",		3,							8,
					"11/25/1999",		15,							6,
					"11/28/1999",		22,							19,
					"11/28/1999",		4,							23,
					"11/28/1999",		30,							33,
					"11/28/1999",		12,							13,
					"11/28/1999",		17,							2,
					"11/28/1999",		18,							14,
					"11/28/1999",		20,							11,
					"11/28/1999",		21,							28,
					"11/28/1999",		24,							16,
					"11/28/1999",		27,							26,
					"11/28/1999",		10,							5,
					"11/28/1999",		1,							29,
					"11/29/1999",		9,							25
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID,
					SchedGame15Date,	SchedGame15VisitProfTeamID, SchedGame15HomeProfTeamID) values
	( 13,		15,
					"12/2/1999 20:20:00",		23,							30,
					"12/5/1999",		5,							24,
					"12/5/1999",		9,							3,
					"12/5/1999",		11,							15,
					"12/5/1999",		12,							7,
					"12/5/1999",		18,							1,
					"12/5/1999",		20,							19,
					"12/5/1999",		21,							22,
					"12/5/1999",		14,							29,
					"12/5/1999",		25,							4,
					"12/5/1999",		26,							13,
					"12/5/1999",		10,							33,
					"12/5/1999",		28,							8,
					"12/5/1999",		6,							17,
					"12/6/1999",		16,							27
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID,
					SchedGame15Date,	SchedGame15VisitProfTeamID, SchedGame15HomeProfTeamID) values
	( 14,		15,
					"12/9/1999 20:20:00",		13,							10,
					"12/12/1999",		22,							28,
					"12/12/1999",		1,							25,
					"12/12/1999",		33,							23,
					"12/12/1999",		29,							9,
					"12/12/1999",		5,							4,
					"12/12/1999",		8,							27,
					"12/12/1999",		15,							20,
					"12/12/1999",		17,							11,
					"12/12/1999",		19,							2,
					"12/12/1999",		21,							6,
					"12/12/1999",		14,							18,
					"12/12/1999",		24,							26,
					"12/12/1999",		16,							12,
					"12/13/1999",		7,							30
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID,
					SchedGame15Date,	SchedGame15VisitProfTeamID, SchedGame15HomeProfTeamID) values
	( 15,		15,
					"12/18/1999 12:40:00",		23,							12,
					"12/18/1999",		25,							29,
					"12/19/1999",		1,							10,
					"12/19/1999",		8,							3,
					"12/19/1999",		30,							5,
					"12/19/1999",		17,							21,
					"12/19/1999",		18,							33,
					"12/19/1999",		19,							14,
					"12/19/1999",		20,							6,
					"12/19/1999",		24,							15,
					"12/19/1999",		26,							7,
					"12/19/1999",		27,							13,
					"12/19/1999",		28,							11,
					"12/19/1999",		2,							22,
					"12/20/1999",		9,							16
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID,
					SchedGame15Date,	SchedGame15VisitProfTeamID, SchedGame15HomeProfTeamID) values
	( 16,		15,
					"12/24/1999 13:00:00",		6,							18,
					"12/25/1999",		7,							8,
					"12/26/1999",		22,							1,
					"12/26/1999",		3,							17,
					"12/26/1999",		29,							23,
					"12/26/1999",		3,							14,
					"12/26/1999",		4,							33,
					"12/26/1999",		9,							27,
					"12/26/1999",		11,							5,
					"12/26/1999",		30,							10,
					"12/26/1999",		12,							26,
					"12/26/1999",		16,							19,
					"12/26/1999",		13,							24,
					"12/26/1999",		28,							25,
					"12/27/1999",		20,							15
					);

insert into ProfTeamSchedule
	( ProfGameWeek,	NumScheduleGames,
					SchedGame01DateTime,	SchedGame01VisitProfTeamID, SchedGame01HomeProfTeamID,
					SchedGame02Date,	SchedGame02VisitProfTeamID, SchedGame02HomeProfTeamID,
					SchedGame03Date,	SchedGame03VisitProfTeamID, SchedGame03HomeProfTeamID,
					SchedGame04Date,	SchedGame04VisitProfTeamID, SchedGame04HomeProfTeamID,
					SchedGame05Date,	SchedGame05VisitProfTeamID, SchedGame05HomeProfTeamID,
					SchedGame06Date,	SchedGame06VisitProfTeamID, SchedGame06HomeProfTeamID,
					SchedGame07Date,	SchedGame07VisitProfTeamID, SchedGame07HomeProfTeamID,
					SchedGame08Date,	SchedGame08VisitProfTeamID, SchedGame08HomeProfTeamID,
					SchedGame09Date,	SchedGame09VisitProfTeamID, SchedGame09HomeProfTeamID,
					SchedGame10Date,	SchedGame10VisitProfTeamID, SchedGame10HomeProfTeamID,
					SchedGame11Date,	SchedGame11VisitProfTeamID, SchedGame11HomeProfTeamID,
					SchedGame12Date,	SchedGame12VisitProfTeamID, SchedGame12HomeProfTeamID,
					SchedGame13Date,	SchedGame13VisitProfTeamID, SchedGame13HomeProfTeamID,
					SchedGame14Date,	SchedGame14VisitProfTeamID, SchedGame14HomeProfTeamID,
					SchedGame15Date,	SchedGame15VisitProfTeamID, SchedGame15HomeProfTeamID) values
	( 17,		15,
					"1/2/2000 13:00:00",			22,							9,
					"1/2/2000",			33,							17,
					"1/2/2000",			4,							30,
					"1/2/2000",			8,							16,
					"1/2/2000",			11,							2,
					"1/2/2000",			15,							28,
					"1/2/2000",			18,							29,
					"1/2/2000",			19,							6,
					"1/2/2000",			13,							12,
					"1/2/2000",			14,							21,
					"1/2/2000",			24,							7,
					"1/2/2000",			26,							20,
					"1/2/2000",			27,							3,
					"1/2/2000",			10,							23,
					"1/3/2000",			25,							1
					);


/******************************************************************************/

commit work;

/******************************************************************************/

exit;