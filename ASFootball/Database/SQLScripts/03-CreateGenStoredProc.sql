connect "z:\tag999\asfootball\database\asfootball.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

set term ^ ;

/* League */
create procedure Next_LeagueID
returns (new_ID integer) as
begin
	new_ID = gen_id(Gen_LeagueID, 1);
end ^

/******************************************************************************/

/* Team */
create procedure Next_TeamID
returns (new_ID integer) as
begin
	new_ID = gen_id(Gen_TeamID, 1);
end ^

/******************************************************************************/

/* FreeAgentClaim */
create procedure Next_FreeAgentClaimID
returns (new_ID integer) as
begin
	new_ID = gen_id(Gen_FreeAgentClaimID, 1);
end ^

/******************************************************************************/

/* Trade */
create procedure Next_TradeID
returns (new_ID integer) as
begin
	new_ID = gen_id(Gen_TradeID, 1);
end ^

/******************************************************************************/

commit work ^
set term ; ^

/******************************************************************************/

exit;
