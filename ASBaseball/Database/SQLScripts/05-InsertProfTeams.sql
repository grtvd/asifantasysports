connect "z:\tag999\asbaseball\database\asbaseball.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  1, "BAL", "Baltimore", "Orioles" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  2, "BOS", "Boston", "Red Sox" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  3, "ANA", "Anaheim", "Angles" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  4, "CHA", "Chicago", "White Sox" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  5, "CLE", "Cleveland", "Indians" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  6, "DET", "Detroit", "Tigers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  7, "KC", "Kansas City", "Royals" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  8, "MIL", "Milwaukee", "Brewers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  9, "MIN", "Minnesota", "Twins" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 10, "NYA", "New York", "Yankees" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 11, "OAK", "Oakland", "Athletics" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 12, "SEA", "Seattle", "Mariners" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 13, "TEX", "Texas", "Rangers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 14, "TOR", "Toronto", "Blue Jays" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 15, "ATL", "Atlanta", "Braves" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 16, "CHN", "Chicago", "Cubs" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 17, "CIN", "Cincinnati", "Reds" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 18, "HOU", "Houston", "Astros" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 19, "LA", "Los Angeles", "Dodgers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 20, "MON", "Montreal", "Expos" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 21, "NYN", "New York", "Mets" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 22, "PHI", "Philadelphia", "Phillies" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 23, "PIT", "Pittsburgh", "Pirates" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 24, "STL", "St. Louis", "Cardinals" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 25, "SD", "San Diego", "Padres" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 26, "SF", "San Francisco", "Giants" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 27, "COL", "Colorado", "Rockies" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 28, "FLA", "Florida", "Marlins" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 29, "ARI", "Arizona", "Diamondbacks" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 30, "TB", "Tampa Bay", "Devil Rays" );

/******************************************************************************/

commit work;

/******************************************************************************/

exit;
