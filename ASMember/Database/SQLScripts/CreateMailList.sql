connect "h:\tag999\asmember\database\asmember.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

select email from member where memberid in
(select memberid from partic where gameid = "ASFtbl97")
order by email;

commit work;

/******************************************************************************/

exit;
