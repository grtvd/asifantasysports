connect "h:\tag999\asfantasy\asfootball\database\asfootball.gdb"
user "sysdba" password "!!!!!!!!";

create domain Dom_ParticID as integer;		/* also defined in ASMember.gbd */

alter table Team add ParticID Dom_ParticID;


commit work;
exit;
