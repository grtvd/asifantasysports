connect "h:\tag999\asfantasy\asfootball\database\asfootball.gdb"
user "sysdba" password "!!!!!!!!";

update profplayer set profteamid = 32 where profteamid = 13;

update profplayer set profteamid = 31 where profteamid = 14;

commit work;
exit;
