connect "z:\tag999\ashockey\database\ashockey.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

alter table DraftOrder
	add Round17 varchar(256);

commit work;

/******************************************************************************/

alter table DraftResult
	add Round17 varchar(512);

commit work;

/******************************************************************************/
exit;
