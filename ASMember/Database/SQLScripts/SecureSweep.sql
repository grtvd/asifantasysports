connect "h:\tag999\asmember\database\asmember.gdb"
user "sysdba" password "!!!!!!!!";

update Member set
	Passwd = "xxxxxx",
	AddrStreet1 = "Address Street 1",
	AddrStreet2 = "Address Street 2",
	AddrCity = "Address City",
	AddrState = "PA",
	AddrZip = "99999",
	AddrCountry = "USA",
	Email = "somebody@nowhere.com",
	CCardType = "VS",
	CCardNumber = "",
	CCardExpDate = "",
	CCardNameOn = "";

update Partic set
	Passwd = "xxxxxx";

delete from PayHistory;

commit work;
exit;
