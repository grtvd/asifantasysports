connect "z:\tag999\asbaseball\database\asbaseball.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

alter table FreeAgentClaim
	add ClaimDateTime date not null,
	add ProcessedStatus char(1) not null,
	drop ClaimDate;

commit work;

/******************************************************************************/

insert into FreeAgentClaim
	(FreeAgentClaimID,TeamID,ClaimDateTime,Status,ClaimPlayerID,
	ReleasePlayerID,ProcessedStatus)
	select TeamID - 1000,TeamID,FAClaimDate,"P",FAClaimPlayerID,
	FAReleasePlayerID,"P" from Team where (FAClaimPlayerID != 0);

commit work;

/******************************************************************************/

alter table Team
	drop FAClaimDate,
	drop FAClaimPlayerID,
	drop FAReleasePlayerID;

commit work;

/******************************************************************************/

set generator gen_freeagentclaimid to 1000;

commit work;

/******************************************************************************/
exit;
