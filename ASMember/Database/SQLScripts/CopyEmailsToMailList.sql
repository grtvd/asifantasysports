/*
Alias: WORK
LiveAnswer: FALSE

*/

insert into :asmembermisc:maillist
(email, receiveddatetime, source, status)
select m.email, "3/2/98", "ASFtbl98", "A"
from :asmember:member m, :asmember:partic p
where (m.memberid = p.memberid) and (p.gameid = "ASFtbl98")
