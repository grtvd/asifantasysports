connect "z:\tag999\ashockey\database\ashockey.gdb"
user "sysdba" password "!!!!!!!!";

/******************************************************************************/

/* League Name */

create table LeagueName
(
	Name varchar(25) not null primary key,
	Used smallint default 0
);

/******************************************************************************/

/* League */

create table League
(
	LeagueID Dom_LeagueID not null primary key,	/* auto generated */
	Name varchar(25) not null,
	Passwd Dom_Password, /* Can't use name Password */

	GamePhase char(2) not null,
	Reserved smallint not null,

	LastProcessedDate date not null,
	DraftDate date,
	SeasonDate date,

	NumOverallTeams smallint not null,
	OverallStand01 Dom_TeamID,
	OverallStand02 Dom_TeamID,
	OverallStand03 Dom_TeamID,
	OverallStand04 Dom_TeamID,
	OverallStand05 Dom_TeamID,
	OverallStand06 Dom_TeamID,
	OverallStand07 Dom_TeamID,
	OverallStand08 Dom_TeamID,
	OverallStand09 Dom_TeamID,
	OverallStand10 Dom_TeamID,
	OverallStand11 Dom_TeamID,
	OverallStand12 Dom_TeamID,
	OverallStand13 Dom_TeamID,
	OverallStand14 Dom_TeamID,
	
	NumEastDivTeams smallint not null,
	EastDivStand01 Dom_TeamID,
	EastDivStand02 Dom_TeamID,
	EastDivStand03 Dom_TeamID,
	EastDivStand04 Dom_TeamID,
	EastDivStand05 Dom_TeamID,
	EastDivStand06 Dom_TeamID,
	EastDivStand07 Dom_TeamID,

	NumWestDivTeams smallint not null,
	WestDivStand01 Dom_TeamID,
	WestDivStand02 Dom_TeamID,
	WestDivStand03 Dom_TeamID,
	WestDivStand04 Dom_TeamID,
	WestDivStand05 Dom_TeamID,
	WestDivStand06 Dom_TeamID,
	WestDivStand07 Dom_TeamID,

	NumFAClaimTeams smallint not null,
	FAClaimTeam01 Dom_TeamID,
	FAClaimTeam02 Dom_TeamID,
	FAClaimTeam03 Dom_TeamID,
	FAClaimTeam04 Dom_TeamID,
	FAClaimTeam05 Dom_TeamID,
	FAClaimTeam06 Dom_TeamID,
	FAClaimTeam07 Dom_TeamID,
	FAClaimTeam08 Dom_TeamID,
	FAClaimTeam09 Dom_TeamID,
	FAClaimTeam10 Dom_TeamID,
	FAClaimTeam11 Dom_TeamID,
	FAClaimTeam12 Dom_TeamID,
	FAClaimTeam13 Dom_TeamID,
	FAClaimTeam14 Dom_TeamID,

	EastWinnerTeamID Dom_TeamID,
	EastWildCardTeamID Dom_TeamID,
	WestWinnerTeamID Dom_TeamID,
	WestWildCardTeamID Dom_TeamID,
	FinalistOneTeamID Dom_TeamID,
	FinalistTwoTeamID Dom_TeamID,
	LeagueChampTeamID Dom_TeamID
);

/******************************************************************************/

/* Team */

create table Team
(
	TeamID Dom_TeamID not null primary key,	/* auto generated */
	ParticID Dom_ParticID not null,
	LeagueID Dom_LeagueID,
	Division char(1) not null,

	RegionName varchar(25),
	TeamName varchar(25),

	ManagerName Dom_FirstName,	/* Nick Name */

	Wins smallint not null,
	Loses smallint not null,
	Ties smallint not null,
	DivWins smallint not null,
	DivLoses smallint not null,
	DivTies smallint not null,
	Streak smallint not null, 
	TotalPoints smallint not null,

	/* Skater Lineup */
	SkaterPlayer01 Dom_PlayerID,
	SkaterPlayer02 Dom_PlayerID,
	SkaterPlayer03 Dom_PlayerID,
	SkaterPlayer04 Dom_PlayerID,
	SkaterPlayer05 Dom_PlayerID,
	SkaterPlayer06 Dom_PlayerID,
	SkaterPlayer07 Dom_PlayerID,
	SkaterPlayer08 Dom_PlayerID,
	SkaterPlayer09 Dom_PlayerID,
	SkaterPlayer10 Dom_PlayerID,

	/* Goalie Lineup */
	GoaliePlayer01 Dom_PlayerID,
	
	/* Trades */
	NumTradeProtests smallint not null,

	constraint TeamLeagueIDKey foreign key (LeagueID)
		references League (LeagueID)
);

/******************************************************************************/

/* ProfTeam */

create table ProfTeam
(
	ProfTeamID Dom_ProfTeamID not null primary key,
	ProfTeamAbbr varchar(3) not null,

	RegionName varchar(25),
	TeamName varchar(25)
);

/******************************************************************************/

/* ProfPlayer */

create table ProfPlayer
(
	PlayerID Dom_PlayerID not null primary key,	/* assigned by stat company */

	FirstName Dom_FirstName,
	LastName Dom_LastName not null,

	ProfTeamID smallint not null,
	GameStatus char(1) not null,

	NewPlayerDate date,
	TotalPoints smallint not null,
	LastWeeksPoints smallint not null,
	
	Pos char(1) not null,	/* Can't use name Position */

	LastUpdated date,
	RosterStatus char(1) not null,
	
	constraint ProfPlayerProfTeamIDKey foreign key (ProfTeamID)
		references ProfTeam (ProfTeamID)
);

/******************************************************************************/

/* Player */

create table Player
(
	LeagueID Dom_LeagueID not null,
	PlayerID Dom_PlayerID not null,

	TeamID Dom_TeamID,

	NewFADate date,
	
	primary key (LeagueID, PlayerID),
	constraint PlayerLeagueIDKey foreign key (LeagueID)
		references League (LeagueID),
	constraint PlayerTeamIDKey foreign key (TeamID)
		references Team (TeamID),
	constraint PlayerPlayerIDKey foreign key (PlayerID)
		references ProfPlayer (PlayerID)
);

/******************************************************************************/

/* OffGameStat */

create table OffGameStat
(
	PlayerID Dom_PlayerID not null,
	StatPeriod char(1) not null,
	StatDate date not null, /* 12/30/1899 dates are considered null*/

	TotalPoints smallint not null,

	GamesPlayed smallint not null,
	Goals smallint not null,
	Assists smallint not null,
	Points smallint not null,
	Shots smallint not null,
	PlusMinus smallint not null,

	PowerPlayGoals smallint not null,
	PowerPlayAssists smallint not null,
	ShortHandedGoals smallint not null,
	ShortHandedAssists smallint not null,
	GameWinningGoals smallint not null,
	GameTyingGoals smallint not null,
	EmptyNetGoals smallint not null,
	OvertimeGoals smallint not null,

	MajorPenalties smallint not null,
	MinorPenalties smallint not null,
	PenaltyMinutes smallint not null,
	HatTricks smallint not null,
	Fights smallint not null,

	constraint OffGameStatIDKey primary key (PlayerID, StatPeriod, StatDate),
	constraint OffGameStatPlayerIDKey foreign key (PlayerID)
		references ProfPlayer (PlayerID)
);

/******************************************************************************/

/* DefGameStat */

create table DefGameStat
(
	PlayerID Dom_PlayerID not null,
	StatPeriod char(1) not null,
	StatDate date not null, /* 12/30/1899 dates are considered null*/

	TotalPoints smallint not null,

	GamesPlayed smallint not null,
	GamesStarted smallint not null,
	MinutesPlayed smallint not null,

	Wins smallint not null,
	Losses smallint not null,
	Ties smallint not null,

	GoalsAgainst smallint not null,
	EmptyNetGoalsAgainst smallint not null,
	ShotsAgainst smallint not null,
	Saves smallint not null,
	Shutouts smallint not null,

	MajorPenalties smallint not null,
	PenaltyMinutes smallint not null,
	Fights smallint not null,

	constraint DefGameStatIDKey primary key (PlayerID, StatPeriod, StatDate),
	constraint DefGameStatPlayerIDKey foreign key (PlayerID)
		references ProfPlayer (PlayerID)
);

/******************************************************************************/

/* DraftOrder */

create table DraftOrder
(
	LeagueID Dom_LeagueID not null primary key,	/* auto generated */

	NumRounds smallint not null,
	NumTeams smallint not null,

	Round01 varchar(256),
	Round02 varchar(256),
	Round03 varchar(256),
	Round04 varchar(256),
	Round05 varchar(256),
	Round06 varchar(256),
	Round07 varchar(256),
	Round08 varchar(256),
	Round09 varchar(256),
	Round10 varchar(256),
	Round11 varchar(256),
	Round12 varchar(256),
	Round13 varchar(256),
	Round14 varchar(256),
	Round15 varchar(256),
	Round16 varchar(256),
	Round17 varchar(256),

	constraint DraftOrderLeagueIDKey foreign key (LeagueID)
		references League (LeagueID)
);

/******************************************************************************/

/* DraftRanking */

create table DraftRanking
(
	TeamID Dom_TeamID not null primary key,	/* auto generated */

	NumRankings smallint not null,

	Rank001 Dom_PlayerID,
	Rank002 Dom_PlayerID,
	Rank003 Dom_PlayerID,
	Rank004 Dom_PlayerID,
	Rank005 Dom_PlayerID,
	Rank006 Dom_PlayerID,
	Rank007 Dom_PlayerID,
	Rank008 Dom_PlayerID,
	Rank009 Dom_PlayerID,
	Rank010 Dom_PlayerID,
	
	Rank011 Dom_PlayerID,
	Rank012 Dom_PlayerID,
	Rank013 Dom_PlayerID,
	Rank014 Dom_PlayerID,
	Rank015 Dom_PlayerID,
	Rank016 Dom_PlayerID,
	Rank017 Dom_PlayerID,
	Rank018 Dom_PlayerID,
	Rank019 Dom_PlayerID,
	Rank020 Dom_PlayerID,
	
	Rank021 Dom_PlayerID,
	Rank022 Dom_PlayerID,
	Rank023 Dom_PlayerID,
	Rank024 Dom_PlayerID,
	Rank025 Dom_PlayerID,
	Rank026 Dom_PlayerID,
	Rank027 Dom_PlayerID,
	Rank028 Dom_PlayerID,
	Rank029 Dom_PlayerID,
	Rank030 Dom_PlayerID,
	
	Rank031 Dom_PlayerID,
	Rank032 Dom_PlayerID,
	Rank033 Dom_PlayerID,
	Rank034 Dom_PlayerID,
	Rank035 Dom_PlayerID,
	Rank036 Dom_PlayerID,
	Rank037 Dom_PlayerID,
	Rank038 Dom_PlayerID,
	Rank039 Dom_PlayerID,
	Rank040 Dom_PlayerID,
	
	Rank041 Dom_PlayerID,
	Rank042 Dom_PlayerID,
	Rank043 Dom_PlayerID,
	Rank044 Dom_PlayerID,
	Rank045 Dom_PlayerID,
	Rank046 Dom_PlayerID,
	Rank047 Dom_PlayerID,
	Rank048 Dom_PlayerID,
	Rank049 Dom_PlayerID,
	Rank050 Dom_PlayerID,
	
	Rank051 Dom_PlayerID,
	Rank052 Dom_PlayerID,
	Rank053 Dom_PlayerID,
	Rank054 Dom_PlayerID,
	Rank055 Dom_PlayerID,
	Rank056 Dom_PlayerID,
	Rank057 Dom_PlayerID,
	Rank058 Dom_PlayerID,
	Rank059 Dom_PlayerID,
	Rank060 Dom_PlayerID,
	
	Rank061 Dom_PlayerID,
	Rank062 Dom_PlayerID,
	Rank063 Dom_PlayerID,
	Rank064 Dom_PlayerID,
	Rank065 Dom_PlayerID,
	Rank066 Dom_PlayerID,
	Rank067 Dom_PlayerID,
	Rank068 Dom_PlayerID,
	Rank069 Dom_PlayerID,
	Rank070 Dom_PlayerID,
	
	Rank071 Dom_PlayerID,
	Rank072 Dom_PlayerID,
	Rank073 Dom_PlayerID,
	Rank074 Dom_PlayerID,
	Rank075 Dom_PlayerID,
	Rank076 Dom_PlayerID,
	Rank077 Dom_PlayerID,
	Rank078 Dom_PlayerID,
	Rank079 Dom_PlayerID,
	Rank080 Dom_PlayerID,
	
	Rank081 Dom_PlayerID,
	Rank082 Dom_PlayerID,
	Rank083 Dom_PlayerID,
	Rank084 Dom_PlayerID,
	Rank085 Dom_PlayerID,
	Rank086 Dom_PlayerID,
	Rank087 Dom_PlayerID,
	Rank088 Dom_PlayerID,
	Rank089 Dom_PlayerID,
	Rank090 Dom_PlayerID,
	
	Rank091 Dom_PlayerID,
	Rank092 Dom_PlayerID,
	Rank093 Dom_PlayerID,
	Rank094 Dom_PlayerID,
	Rank095 Dom_PlayerID,
	Rank096 Dom_PlayerID,
	Rank097 Dom_PlayerID,
	Rank098 Dom_PlayerID,
	Rank099 Dom_PlayerID,
	Rank100 Dom_PlayerID,

	Rank101 Dom_PlayerID,
	Rank102 Dom_PlayerID,
	Rank103 Dom_PlayerID,
	Rank104 Dom_PlayerID,
	Rank105 Dom_PlayerID,
	Rank106 Dom_PlayerID,
	Rank107 Dom_PlayerID,
	Rank108 Dom_PlayerID,
	Rank109 Dom_PlayerID,
	Rank110 Dom_PlayerID,
	
	Rank111 Dom_PlayerID,
	Rank112 Dom_PlayerID,
	Rank113 Dom_PlayerID,
	Rank114 Dom_PlayerID,
	Rank115 Dom_PlayerID,
	Rank116 Dom_PlayerID,
	Rank117 Dom_PlayerID,
	Rank118 Dom_PlayerID,
	Rank119 Dom_PlayerID,
	Rank120 Dom_PlayerID,
	
	Rank121 Dom_PlayerID,
	Rank122 Dom_PlayerID,
	Rank123 Dom_PlayerID,
	Rank124 Dom_PlayerID,
	Rank125 Dom_PlayerID,
	Rank126 Dom_PlayerID,
	Rank127 Dom_PlayerID,
	Rank128 Dom_PlayerID,
	Rank129 Dom_PlayerID,
	Rank130 Dom_PlayerID,
	
	Rank131 Dom_PlayerID,
	Rank132 Dom_PlayerID,
	Rank133 Dom_PlayerID,
	Rank134 Dom_PlayerID,
	Rank135 Dom_PlayerID,
	Rank136 Dom_PlayerID,
	Rank137 Dom_PlayerID,
	Rank138 Dom_PlayerID,
	Rank139 Dom_PlayerID,
	Rank140 Dom_PlayerID,
	
	Rank141 Dom_PlayerID,
	Rank142 Dom_PlayerID,
	Rank143 Dom_PlayerID,
	Rank144 Dom_PlayerID,
	Rank145 Dom_PlayerID,
	Rank146 Dom_PlayerID,
	Rank147 Dom_PlayerID,
	Rank148 Dom_PlayerID,
	Rank149 Dom_PlayerID,
	Rank150 Dom_PlayerID,
	
	Rank151 Dom_PlayerID,
	Rank152 Dom_PlayerID,
	Rank153 Dom_PlayerID,
	Rank154 Dom_PlayerID,
	Rank155 Dom_PlayerID,
	Rank156 Dom_PlayerID,
	Rank157 Dom_PlayerID,
	Rank158 Dom_PlayerID,
	Rank159 Dom_PlayerID,
	Rank160 Dom_PlayerID,
	
	Rank161 Dom_PlayerID,
	Rank162 Dom_PlayerID,
	Rank163 Dom_PlayerID,
	Rank164 Dom_PlayerID,
	Rank165 Dom_PlayerID,
	Rank166 Dom_PlayerID,
	Rank167 Dom_PlayerID,
	Rank168 Dom_PlayerID,
	Rank169 Dom_PlayerID,
	Rank170 Dom_PlayerID,
	
	Rank171 Dom_PlayerID,
	Rank172 Dom_PlayerID,
	Rank173 Dom_PlayerID,
	Rank174 Dom_PlayerID,
	Rank175 Dom_PlayerID,
	Rank176 Dom_PlayerID,
	Rank177 Dom_PlayerID,
	Rank178 Dom_PlayerID,
	Rank179 Dom_PlayerID,
	Rank180 Dom_PlayerID,
	
	Rank181 Dom_PlayerID,
	Rank182 Dom_PlayerID,
	Rank183 Dom_PlayerID,
	Rank184 Dom_PlayerID,
	Rank185 Dom_PlayerID,
	Rank186 Dom_PlayerID,
	Rank187 Dom_PlayerID,
	Rank188 Dom_PlayerID,
	Rank189 Dom_PlayerID,
	Rank190 Dom_PlayerID,
	
	Rank191 Dom_PlayerID,
	Rank192 Dom_PlayerID,
	Rank193 Dom_PlayerID,
	Rank194 Dom_PlayerID,
	Rank195 Dom_PlayerID,
	Rank196 Dom_PlayerID,
	Rank197 Dom_PlayerID,
	Rank198 Dom_PlayerID,
	Rank199 Dom_PlayerID,
	Rank200 Dom_PlayerID,

	Rank201 Dom_PlayerID,
	Rank202 Dom_PlayerID,
	Rank203 Dom_PlayerID,
	Rank204 Dom_PlayerID,
	Rank205 Dom_PlayerID,
	Rank206 Dom_PlayerID,
	Rank207 Dom_PlayerID,
	Rank208 Dom_PlayerID,
	Rank209 Dom_PlayerID,
	Rank210 Dom_PlayerID,
	
	Rank211 Dom_PlayerID,
	Rank212 Dom_PlayerID,
	Rank213 Dom_PlayerID,
	Rank214 Dom_PlayerID,
	Rank215 Dom_PlayerID,
	Rank216 Dom_PlayerID,
	Rank217 Dom_PlayerID,
	Rank218 Dom_PlayerID,
	Rank219 Dom_PlayerID,
	Rank220 Dom_PlayerID,
	
	Rank221 Dom_PlayerID,
	Rank222 Dom_PlayerID,
	Rank223 Dom_PlayerID,
	Rank224 Dom_PlayerID,

	constraint DraftRankingTeamIDKey foreign key (TeamID)
		references Team (TeamID)
);

/******************************************************************************/

/* DraftResult */

create table DraftResult
(
	LeagueID Dom_LeagueID not null primary key,

	NumRounds smallint not null,
	NumTeams smallint not null,

	Round01 varchar(512),
	Round02 varchar(512),
	Round03 varchar(512),
	Round04 varchar(512),
	Round05 varchar(512),
	Round06 varchar(512),
	Round07 varchar(512),
	Round08 varchar(512),
	Round09 varchar(512),
	Round10 varchar(512),
	Round11 varchar(512),
	Round12 varchar(512),
	Round13 varchar(512),
	Round14 varchar(512),
	Round15 varchar(512),
	Round16 varchar(512),
	Round17 varchar(512),

	constraint DraftResultLeagueIDKey foreign key (LeagueID)
		references League (LeagueID)
);

/******************************************************************************/

/* ScheduleDay */

create table ScheduleDay
(
	LeagueID Dom_LeagueID not null,
	GameDate date not null,

	Status char(1) not null,

	EarlyProfGameDateTime date not null,
	LateProfGameDate date not null,
	ProfGameWeek smallint not null,

	NumScheduleGames smallint not null,
	
	SchedGame01VisitTeamID Dom_TeamID,
	SchedGame01HomeTeamID Dom_TeamID,
	SchedGame01VisitScore smallint,
	SchedGame01HomeScore smallint,
		
	SchedGame02VisitTeamID Dom_TeamID,
	SchedGame02HomeTeamID Dom_TeamID,
	SchedGame02VisitScore smallint,
	SchedGame02HomeScore smallint,
		
	SchedGame03VisitTeamID Dom_TeamID,
	SchedGame03HomeTeamID Dom_TeamID,
	SchedGame03VisitScore smallint,
	SchedGame03HomeScore smallint,
		
	SchedGame04VisitTeamID Dom_TeamID,
	SchedGame04HomeTeamID Dom_TeamID,
	SchedGame04VisitScore smallint,
	SchedGame04HomeScore smallint,
		
	SchedGame05VisitTeamID Dom_TeamID,
	SchedGame05HomeTeamID Dom_TeamID,
	SchedGame05VisitScore smallint,
	SchedGame05HomeScore smallint,
		
	SchedGame06VisitTeamID Dom_TeamID,
	SchedGame06HomeTeamID Dom_TeamID,
	SchedGame06VisitScore smallint,
	SchedGame06HomeScore smallint,
		
	SchedGame07VisitTeamID Dom_TeamID,
	SchedGame07HomeTeamID Dom_TeamID,
	SchedGame07VisitScore smallint,
	SchedGame07HomeScore smallint,
		
	primary key (LeagueID, GameDate),
	constraint ScheduleDayLeagueIDKey foreign key (LeagueID)
		references League (LeagueID)
);

/******************************************************************************/

/* GameResult */

create table GameResult
(
	TeamID Dom_TeamID not null,
	GameDate date not null,
	OppTeamID Dom_TeamID not null,

	TotalPoints smallint not null,

	NumOffPlayers smallint not null,

	OffPlayer01 Dom_PlayerID,
	OffPlayer01Points smallint,
	OffPlayer01Dates varchar(512),

	OffPlayer02 Dom_PlayerID,
	OffPlayer02Points smallint,
	OffPlayer02Dates varchar(512),

	OffPlayer03 Dom_PlayerID,
	OffPlayer03Points smallint,
	OffPlayer03Dates varchar(512),

	OffPlayer04 Dom_PlayerID,
	OffPlayer04Points smallint,
	OffPlayer04Dates varchar(512),

	OffPlayer05 Dom_PlayerID,
	OffPlayer05Points smallint,
	OffPlayer05Dates varchar(512),

	OffPlayer06 Dom_PlayerID,
	OffPlayer06Points smallint,
	OffPlayer06Dates varchar(512),

	OffPlayer07 Dom_PlayerID,
	OffPlayer07Points smallint,
	OffPlayer07Dates varchar(512),

	OffPlayer08 Dom_PlayerID,
	OffPlayer08Points smallint,
	OffPlayer08Dates varchar(512),

	OffPlayer09 Dom_PlayerID,
	OffPlayer09Points smallint,
	OffPlayer09Dates varchar(512),

	OffPlayer10 Dom_PlayerID,
	OffPlayer10Points smallint,
	OffPlayer10Dates varchar(512),

	NumDefPlayers smallint not null,

	DefPlayer01 Dom_PlayerID,
	DefPlayer01Points smallint,
	DefPlayer01Dates varchar(512),

	DefPlayer02 Dom_PlayerID,
	DefPlayer02Points smallint,
	DefPlayer02Dates varchar(512),

	DefPlayer03 Dom_PlayerID,
	DefPlayer03Points smallint,
	DefPlayer03Dates varchar(512),

	DefPlayer04 Dom_PlayerID,
	DefPlayer04Points smallint,
	DefPlayer04Dates varchar(512),

	DefPlayer05 Dom_PlayerID,
	DefPlayer05Points smallint,
	DefPlayer05Dates varchar(512),

	DefPlayer06 Dom_PlayerID,
	DefPlayer06Points smallint,
	DefPlayer06Dates varchar(512),

	DefPlayer07 Dom_PlayerID,
	DefPlayer07Points smallint,
	DefPlayer07Dates varchar(512),

	DefPlayer08 Dom_PlayerID,
	DefPlayer08Points smallint,
	DefPlayer08Dates varchar(512),

	DefPlayer09 Dom_PlayerID,
	DefPlayer09Points smallint,
	DefPlayer09Dates varchar(512),

	DefPlayer10 Dom_PlayerID,
	DefPlayer10Points smallint,
	DefPlayer10Dates varchar(512),

	primary key (TeamID, GameDate),
	constraint GameResultTeamIDKey foreign key (TeamID)
		references Team (TeamID),
	constraint GameResultOppTeamIDKey foreign key (OppTeamID)
		references Team (TeamID)
);

/******************************************************************************/

/* FreeAgentClaim */

create table FreeAgentClaim
(
	FreeAgentClaimID Dom_FreeAgentClaimID not null primary key,	/* auto generated */

	TeamID Dom_TeamID not null,
	ClaimDateTime date not null,
	Status char(1) not null,

	ClaimPlayerID Dom_PlayerID not null,
	ReleasePlayerID Dom_PlayerID,

	ProcessedDate date,
	ProcessedStatus char(1) not null,

	constraint FreeAgentClaimTeamIDKey foreign key (TeamID)
		references Team (TeamID),
	constraint FreeAgentClaimClaimPlayerIDKey foreign key (ClaimPlayerID)
		references ProfPlayer (PlayerID),
	constraint FreeAgentClaimRelPlayerIDKey foreign key (ReleasePlayerID)
		references ProfPlayer (PlayerID)
);

/******************************************************************************/

/* Trade */

create table Trade
(
	TradeID Dom_TradeID not null primary key,	/* auto generated */

	TeamID Dom_TeamID not null,
	ProposeToTeamID Dom_TeamID not null,
	ProposedDate date not null,
	Status char(1) not null,

	/* GetPlayerIDVector */
	NumGetPlayers smallint not null,
	GetPlayer01 Dom_PlayerID,
	GetPlayer02 Dom_PlayerID,
	GetPlayer03 Dom_PlayerID,
	GetPlayer04 Dom_PlayerID,
	GetPlayer05 Dom_PlayerID,
	
	/* GivePlayerIDVector */
	NumGivePlayers smallint not null,
	GivePlayer01 Dom_PlayerID,
	GivePlayer02 Dom_PlayerID,
	GivePlayer03 Dom_PlayerID,
	GivePlayer04 Dom_PlayerID,
	GivePlayer05 Dom_PlayerID,
	
	/* ProposeRelPlayerIDVector */
	NumProposeRelPlayers smallint not null,
	ProposeRelPlayer01 Dom_PlayerID,
	ProposeRelPlayer02 Dom_PlayerID,
	ProposeRelPlayer03 Dom_PlayerID,
	ProposeRelPlayer04 Dom_PlayerID,
	ProposeRelPlayer05 Dom_PlayerID,

	AcceptedDate date,

	/* AcceptRelPlayerIDVector */
	NumAcceptRelPlayers smallint not null,
	AcceptRelPlayer01 Dom_PlayerID,
	AcceptRelPlayer02 Dom_PlayerID,
	AcceptRelPlayer03 Dom_PlayerID,
	AcceptRelPlayer04 Dom_PlayerID,
	AcceptRelPlayer05 Dom_PlayerID,

	/* ProtestTeamIDVector */
	NumProtestTeams smallint not null,
	ProtestTeam01 Dom_TeamID,
	ProtestTeam02 Dom_TeamID,
	ProtestTeam03 Dom_TeamID,
	ProtestTeam04 Dom_TeamID,
	ProtestTeam05 Dom_TeamID,
	ProtestTeam06 Dom_TeamID,
	ProtestTeam07 Dom_TeamID,
	ProtestTeam08 Dom_TeamID,
	ProtestTeam09 Dom_TeamID,
	ProtestTeam10 Dom_TeamID,
	ProtestTeam11 Dom_TeamID,
	ProtestTeam12 Dom_TeamID,
	ProtestTeam13 Dom_TeamID,
	ProtestTeam14 Dom_TeamID,

	constraint TradeTeamIDKey foreign key (TeamID)
		references Team (TeamID),
	constraint TradeProposedToTeamIDKey foreign key (ProposeToTeamID)
		references Team (TeamID)
);

/******************************************************************************/

commit work;

/******************************************************************************/

exit;
