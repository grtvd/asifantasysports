create database "h:\tag999\asmember\database\asmember.gdb"
user "sysdba" password "!!!!!!!!"
page_size 1024;

create domain Dom_FirstName as varchar(15);	/* also defined in ASFootball.gbd */
create domain Dom_LastName as varchar(25);	/* also defined in ASFootball.gbd */
create domain Dom_Password as varchar(10);	/* also defined in ASFootball.gbd */

create domain Dom_GameID as varchar(10);
create domain Dom_MemberID as varchar(15);
create domain Dom_ParticID as integer;		/* also defined in ASFootball.gbd */

create domain Dom_TeamID as integer;		/* also defined in ASFootball.gbd */

/* create generator Gen_MemberID; */
create generator Gen_ParticID;

/* Member */
create table Member
(
	MemberID Dom_MemberID not null primary key,
	Passwd Dom_Password not null,
	
	FirstName Dom_FirstName,
	LastName Dom_LastName,
	
	AddrStreet1 varchar(35),
	AddrStreet2 varchar(35),
	AddrCity varchar(25),
	AddrState varchar(25),
	AddrZip varchar(10),
	AddrCountry varchar(35),
	
	Email varchar(50),

	CCardType char(2),
	CCardNumber varchar(19),
	CCardExpDate varchar(6),
	CCardNameOn varchar(40)
);

/* Partic */
create table Partic
(
	ParticID Dom_ParticID not null primary key,	/* auto generated */
	MemberID Dom_MemberID not null,
	Passwd Dom_Password not null, /* Can't use name Password */

	GameID Dom_GameID not null,
	GamePrice double precision,
	Status char(2),

	TeamID Dom_TeamID not null,
	SignupDate date,
	LastTransDateTime date
);

/* PayHistory */
create table PayHistory
(
	MemberID Dom_MemberID not null,
	TransDateTime Date not null,	/* date and time */

	ParticID Dom_ParticID not null,
	GameID Dom_GameID not null,

	/* Credit Card Info */
	CCardType char(2),
	CCardNumber varchar(19),
	CCardExpDate varchar(6),
	CCardNameOn varchar(40),

	/* Request Info */
	SaleCommand varchar(3),
	Clerk varchar(15),
	Comment varchar(25),
	Amount double precision,
	
	/* Response Info */
	Approved char(1),
	Response varchar(220),
	
	primary key (MemberID, TransDateTime)
);

set term ^ ;

create procedure Next_ParticID
returns (new_ID integer) as
begin
	new_ID = gen_id(Gen_ParticID, 1);
end ^

set term ; ^

commit work;
exit;
