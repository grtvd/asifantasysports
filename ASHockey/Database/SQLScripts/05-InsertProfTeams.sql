connect "z:\tag999\ashockey\database\ashockey.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  1, "Bos", "Boston", "Bruins" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  2, "Buf", "Buffalo", "Sabres" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  3, "Cgy", "Calgary", "Flames" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  4, "Chi", "Chicago", "Blackhawks" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  5, "Det", "Detroit", "Red Wings" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  6, "Edm", "Edmonton", "Oilers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  7, "Car", "Carolina", "Hurricanes" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  8, "LA", "Los Angeles", "Kings" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  9, "Dal", "Dallas", "Stars" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 10, "Mon", "Montreal", "Canadiens" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 11, "NJ", "New Jersey", "Devils" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 12, "NYI", "New York", "Islanders" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 13, "NYR", "New York", "Rangers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 14, "Ott", "Ottawa", "Senators" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 15, "Phi", "Philadelphia", "Flyers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 16, "Pit", "Pittsburgh", "Penguins" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 17, "Col", "Colorado", "Avalanche" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 18, "SJ", "San Jose", "Sharks" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 19, "StL", "St. Louis", "Blues" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 20, "TB", "Tampa Bay", "Lightning" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 21, "Tor", "Toronto", "Maple Leafs" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 22, "Van", "Vancouver", "Canucks" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 23, "Was", "Washington", "Capitals" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 24, "Pho", "Phoenix", "Coyotes" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 25, "Anh", "Anaheim", "Mighty Ducks" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 26, "Fla", "Florida", "Panthers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 27, "Nsh", "Nashville", "Predators" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 28, "Nsh", "Atlanta", "Thrashers" );

/******************************************************************************/

commit work;

/******************************************************************************/

exit;
