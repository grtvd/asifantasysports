connect "h:\tag999\asfantasy\asfootball\database\asfootball.gdb"
user "sysdba" password "!!!!!!!!";

create domain Dom_TradeID as integer;
create generator Gen_TradeID;

create table Trade
(
	TradeID Dom_TradeID not null primary key,	/* auto generated */

	TeamID Dom_TeamID,
	ProposeToTeamID Dom_TeamID,
	ProposedDate date,
	Status char(1),

	/* GetPlayerIDVector */
	NumGetPlayers smallint,
	GetPlayer01 Dom_PlayerID,
	GetPlayer02 Dom_PlayerID,
	GetPlayer03 Dom_PlayerID,
	GetPlayer04 Dom_PlayerID,
	GetPlayer05 Dom_PlayerID,
	
	/* GivePlayerIDVector */
	NumGivePlayers smallint,
	GivePlayer01 Dom_PlayerID,
	GivePlayer02 Dom_PlayerID,
	GivePlayer03 Dom_PlayerID,
	GivePlayer04 Dom_PlayerID,
	GivePlayer05 Dom_PlayerID,
	
	/* ProposeRelPlayerIDVector */
	NumProposeRelPlayers smallint,
	ProposeRelPlayer01 Dom_PlayerID,
	ProposeRelPlayer02 Dom_PlayerID,
	ProposeRelPlayer03 Dom_PlayerID,
	ProposeRelPlayer04 Dom_PlayerID,
	ProposeRelPlayer05 Dom_PlayerID,

	AcceptedDate date,

	/* AcceptRelPlayerIDVector */
	NumAcceptRelPlayers smallint,
	AcceptRelPlayer01 Dom_PlayerID,
	AcceptRelPlayer02 Dom_PlayerID,
	AcceptRelPlayer03 Dom_PlayerID,
	AcceptRelPlayer04 Dom_PlayerID,
	AcceptRelPlayer05 Dom_PlayerID,

	/* ProtestTeamIDVector */
	NumProtestTeams smallint,
	ProtestTeam01 Dom_TeamID,
	ProtestTeam02 Dom_TeamID,
	ProtestTeam03 Dom_TeamID,
	ProtestTeam04 Dom_TeamID,
	ProtestTeam05 Dom_TeamID,
	ProtestTeam06 Dom_TeamID,
	ProtestTeam07 Dom_TeamID,
	ProtestTeam08 Dom_TeamID,
	ProtestTeam09 Dom_TeamID,
	ProtestTeam10 Dom_TeamID,
	ProtestTeam11 Dom_TeamID,
	ProtestTeam12 Dom_TeamID,
	ProtestTeam13 Dom_TeamID,
	ProtestTeam14 Dom_TeamID
);

alter table Team
	drop TRProposedToTeamID,
	drop TRProposedDate,
	drop TRAcceptedDate,
	drop TRStatus,
	
	drop NumTRGetPlayers,
	drop TRGetPlayer01,
	drop TRGetPlayer02,
	drop TRGetPlayer03,
	drop TRGetPlayer04,
	drop TRGetPlayer05,
	
	drop NumTRGivePlayers,
	drop TRGivePlayer01,
	drop TRGivePlayer02,
	drop TRGivePlayer03,
	drop TRGivePlayer04,
	drop TRGivePlayer05,
	
	drop NumTRReleasePlayers,
	drop TRReleasePlayer01,
	drop TRReleasePlayer02,
	drop TRReleasePlayer03,
	drop TRReleasePlayer04,
	drop TRReleasePlayer05,

	drop NumTRProtestTeams,
	drop TRProtestTeam01,
	drop TRProtestTeam02,
	drop TRProtestTeam03,
	drop TRProtestTeam04,
	drop TRProtestTeam05,
	drop TRProtestTeam06,
	drop TRProtestTeam07,
	drop TRProtestTeam08,
	drop TRProtestTeam09,
	drop TRProtestTeam10,
	drop TRProtestTeam11,
	drop TRProtestTeam12,
	drop TRProtestTeam13,
	drop TRProtestTeam14,
	
	drop TRAcceptTeamID,

	add NumTradeProtests smallint;

update Team set NumTradeProtests = 0;

set term ^ ;

create procedure Next_TradeID
returns (new_ID integer) as
begin
	new_ID = gen_id(Gen_TradeID, 1);
end ^

set term ; ^

commit work;
exit;
