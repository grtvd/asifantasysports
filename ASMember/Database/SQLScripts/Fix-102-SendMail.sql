connect "h:\tag999\asmember\database\asmembermisc.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

create Domain Dom_SendMailID as integer;

create table SendMail
(
	SendMailID Dom_SendMailID not null,
	CreatedDateTime date not null,
	Sender varchar(128) not null,
	Recipient varchar(128) not null,
	Subject varchar(128) not null,
	BodyText blob sub_type text,
	AttachedFile varchar(1024),
	Status char(1) not null,
	SentDateTime date,
	Primary Key (SendMailID)
);

create Generator Gen_SendMailID;

commit work;

/******************************************************************************/

/* generator Gen_SendMailID */

set term ^ ;

create procedure Next_SendMailID
returns (new_ID integer) as
begin
	new_ID = gen_id(Gen_SendMailID, 1);
end ^

set term ; ^

commit work;

/******************************************************************************/

exit;
