connect "z:\tag999\asfootball\database\asfootball.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 22, "ARZ", "Arizona", "Cardinals" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  1, "ATL", "Atlanta", "Falcons" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 33, "BAL", "Baltimore", "Ravens" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  2, "BUF", "Buffalo", "Bills" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 29, "CAR", "Carolina", "Panthers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  3, "CHI", "Chicago", "Bears" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  4, "CIN", "Cincinnati", "Bengals" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  5, "CLE", "Cleveland", "Browns" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  6, "DAL", "Dallas", "Cowboys" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  7, "DEN", "Denver", "Broncos" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  8, "DET", "Detroit", "Lions" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  9, "GRE", "Green Bay", "Packers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 10, "TEN", "Tennessee", "Oilers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 11, "IND", "Indianapolis", "Colts" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 30, "JAC", "Jacksonville", "Jaguars" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 12, "KAN", "Kansas City", "Chiefs" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 15, "MIA", "Miami", "Dolphins" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 16, "MIN", "Minnesota", "Vikings" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 17, "ENG", "New England", "Patriots" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 18, "NOS", "New Orleans", "Saints" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 19, "NYG", "New York", "Giants" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 20, "NYJ", "New York", "Jets" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 13, "OAK", "Oakland", "Raiders" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 21, "PHL", "Philadelphia", "Eagles" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 23, "PIT", "Pittsburgh", "Steelers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 24, "SDC", "San Diego", "Chargers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 25, "SFR", "San Francisco", "49ers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 26, "SEA", "Seattle", "Seahawks" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 14, "STL", "St. Louis", "Rams" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 27, "TAM", "Tampa Bay", "Buccaneers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 28, "WAS", "Washington", "Redskins" );

/******************************************************************************/

commit work;

/******************************************************************************/

exit;
