/*
Alias: WORK
LiveAnswer: FALSE

*/

select m.memberid, p.particid, p.gameid, p.gameprice,
p.status, m.email, m.signupsource
from :asmember:member m, :asmember:partic p
where (m.memberid = p.memberid)
and (p.gameid = "ASFtbl99")
order by p.particid
