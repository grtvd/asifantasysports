connect "z:\tag999\asbasketball\database\asbasketball.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  1, "ATL", "Atlanta", "Hawks" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  2, "BOS", "Boston", "Celtics" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  3, "CHA", "Charlotte", "Hornets" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  4, "CHI", "Chicago", "Bulls" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  5, "CLE", "Cleveland", "Cavaliers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  6, "DAL", "Dallas", "Mavericks" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  7, "DEN", "Denver", "Nuggets" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  8, "DET", "Detroit", "Pistons" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	(  9, "GS",  "Golden State", "Warriors" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 10, "HOU", "Houston", "Rockets" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 11, "IND", "Indiana", "Pacers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 12, "LAC", "Los Angeles", "Clippers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 13, "LAL", "Los Angeles", "Lakers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 14, "MIA", "Miami", "Heat" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 15, "MIL", "Milwaukee", "Bucks" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 16, "MIN", "Minnesota", "Timberwolves" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 17, "NJ",  "New Jersey", "Nets" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 18, "NY",  "New York", "Knicks" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 19, "ORL", "Orlando", "Magic" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 20, "PHI", "Philadelphia", "76ers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 21, "PHO", "Phoenix", "Suns" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 22, "POR", "Portland", "Trail Blazers" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 23, "SAC", "Sacramento", "Kings" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 24, "SA",  "San Antonio", "Spurs" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 25, "SEA", "Seattle", "SuperSonics" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 26, "UTA", "Utah", "Jazz" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 27, "WAS", "Washington", "Wizards" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 28, "TOR", "Toronto", "Raptors" );
insert into ProfTeam (ProfTeamID, ProfTeamAbbr, RegionName, TeamName ) values
	( 29, "VAN", "Vancouver", "Grizzlies" );

/******************************************************************************/

commit work;

/******************************************************************************/

exit;
