connect "h:\tag999\asmember\database\asmember.gdb"
user "sysdba" password "!!!!!!!!";

insert into Member (MemberID, Passwd, FirstName, LastName, Email, CCardType, CCardNumber,
CCardExpDate, CCardNameOn ) values
( "RDAVIDSON", "bob", "Robert", "Davidson", "bobdavidson@compuserve.com", "MC",
"1111222233334444", "9805", "Robert S. Davidson" );

insert into Partic (ParticID, MemberID, Passwd, GameID, GamePrice, Status, TeamID) values
( 1, "RDAVIDSON", "bob", "ASFtbl97", 34.95, "AP", 1);

insert into Partic (ParticID, MemberID, Passwd, GameID, GamePrice, Status, TeamID) values
( 2, "RDAVIDSON", "bob", "ASFtbl97", 19.95, "AP", 2);

set generator Gen_ParticID to 2;

commit work;
exit;
