connect "h:\tag999\asfantasy\asfootball\database\asfootball.gdb"
user "sysdba" password "!!!!!!!!";

alter table League
	add EastWinnerTeamID Dom_TeamID,
	add EastWildCardTeamID Dom_TeamID,
	add WestWinnerTeamID Dom_TeamID,
	add WestWildCardTeamID Dom_TeamID,
	add FinalistOneTeamID Dom_TeamID,
	add FinalistTwoTeamID Dom_TeamID,
	add LeagueChampTeamID Dom_TeamID;

update League set
	EastWinnerTeamID = 0,
	EastWildCardTeamID = 0,
	WestWinnerTeamID = 0,
	WestWildCardTeamID = 0,
	FinalistOneTeamID = 0,
	FinalistTwoTeamID = 0,
	LeagueChampTeamID = 0;

commit work;
exit;
