connect "z:\tag999\ashockey\database\ashockey.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

create table TempCity external file "z:\tag999\ashockey\database\sqlscripts\city.unf"
(
	Name char(16),
	EOL char(2)
);

/******************************************************************************/

insert into LeagueName (Name) select distinct Name from TempCity;

commit work;

/******************************************************************************/

drop table TempCity;

commit work;

/******************************************************************************/

exit;
