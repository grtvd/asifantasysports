connect "h:\tag999\asmember\database\asmembermisc.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

create index SendMailStatusIndex on SendMail (Status);

/******************************************************************************/

create Domain Dom_ErrorLogID as integer;

create table ErrorLog
(
	ErrorLogID Dom_ErrorLogID not null,
	DateTime date not null,

	Source varchar(64) not null,
	ErrorLevel varchar(16) not null,
	MessageText blob sub_type text,

	Status char(1) not null,
	Primary Key (ErrorLogID)
);

create Generator Gen_ErrorLogID;

commit work;

/******************************************************************************/

create index ErrorLogStatusIndex on ErrorLog (Status);

commit work;

/******************************************************************************/

/* generator Gen_ErrorLogID */

set term ^ ;

create procedure Next_ErrorLogID
returns (new_ID integer) as
begin
	new_ID = gen_id(Gen_ErrorLogID, 1);
end ^

set term ; ^

commit work;

/******************************************************************************/

exit;
