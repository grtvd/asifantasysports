create database "z:\tag999\ashockey\database\ashockey.gdb"
user "sysdba" password "!!!!!!!!"
page_size 1024;

/******************************************************************************/

create domain Dom_FirstName as varchar(15);	/* also defined in ASMember.gbd */
create domain Dom_LastName as varchar(25);	/* also defined in ASMember.gbd */
create domain Dom_Password as varchar(10);	/* also defined in ASMember.gbd */

create domain Dom_ParticID as integer;		/* also defined in ASMember.gbd */
create domain Dom_LeagueID as integer;
create domain Dom_TeamID as integer;		/* also defined in ASMember.gbd */
create domain Dom_ProfTeamID as smallint;
create domain Dom_PlayerID as integer;
create domain Dom_FreeAgentClaimID as integer;
create domain Dom_TradeID as integer;

/******************************************************************************/

create generator Gen_LeagueID;
create generator Gen_TeamID;
/* create generator Gen_PlayerID; */
create generator Gen_FreeAgentClaimID;
create generator Gen_TradeID;

set generator Gen_LeagueID to 100;	/* Leave room for custom IDs. */
set generator Gen_TeamID to 1000;	/* Leave room for custom IDs: DefaultDraftRankingTeamID, etc. */

/******************************************************************************/

commit work;

/******************************************************************************/

exit;
