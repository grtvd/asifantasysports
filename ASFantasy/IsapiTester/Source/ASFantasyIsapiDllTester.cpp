/* ASFantasyIsapiDllTester.h */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "PasswordEncode.h"
#include "ASMemberType.h"
#include "ASFantasyIsapiDllTester.h"

#include "ASFantasyPlayerScoutRqst.h"
#include "ASFantasyLeagueSignupRqst.h"

using namespace tag;
using namespace asmember;

namespace asfantasy
{

/******************************************************************************/

static const char* gAllPagesStrs[] = 
{
" 1. Hub                                51. URL Draft Ranking Query Request\n",
" 2. League Sign-up                     52. URL Draft Ranking Update Request\n",
" 3. Teams                              53. URL Player Scout Request\n",
" 4. Draft Rankings                     54. URL League Signup Request\n",
" 5. Draft Results                      55. URL Signup League List Request\n",
" 6. Schedule                           56. URL Draft Result Request\n",
" 7. Lineup                             \n",
" 8. Game Results                       \n",
" 9. Standings                          57. URL Schedule Request\n",
"10. Free Agents                        58. URL Lineup Query Request\n",
"11. Trades                             59. URL Lineup Update Request\n",
"12. Playoffs                           \n",
"13. Sign-Up Intro Get                  \n",
"14. Sign-Up Which Get                  \n",
"15. Sign-Up New Member Premium Get     60. URL Game Results Request\n",
"16. Sign-Up New Member Premium Post    61. URL Standings Request\n",
"17. Sign-Up New Partic Premium Get     62. URL Free Agent Query Request\n",
"18. Sign-Up New Partic Premium Post    63. URL Free Agent Update Request\n",
"                                       \n",
"                                       66. URL Trade Propose Query Request\n",
"                                       67. URL Trade Propose Team Request\n",
"                                       68. URL Trade Propose Update Request\n",
"                                       69. URL Trade Receive Update Request\n",
"                                       70. URL Trade Protest Update Request\n",
"                                       \n",
"                                       80. URL Playoff Request\n",
};
static int gNumAllPagesStrs = sizeof(gAllPagesStrs) / sizeof(*gAllPagesStrs);

/******************************************************************************/

void ASFantasyIsapiDllLoader::printAllPages() const
{
	int i;

	for(i = 0; i < gNumAllPagesStrs; i++)
		printf(gAllPagesStrs[i]);
}

/******************************************************************************/

const char* ASFantasyIsapiDllLoader::getPageName(int pageNo) const
{
	switch(pageNo)
	{
		case 1:
			return("Hub");
		case 2:
			return("LeagueSignup");
		case 3:
			return("Teams");
		case 4:
			return("DraftRankings");
		case 5:
			return("DraftResults");
		case 6:
			return("Schedule");
		case 7:
			return("Lineup");
		case 8:
			return("GameResults");
		case 9:
			return("Standings");
		case 10:
			return("FreeAgent");
		case 11:
			return("Trade");
		case 12:
			return("Playoff");
		case 13:
			return("Signup");
		case 14:
			return("SignupWhichGet");
		case 15:
			return("NewMemberSignupPremiumGet");
		case 16:
			return("NewMemberSignupPost");
		case 17:
			return("NewParticSignupPremiumGet");
		case 18:
			return("NewParticSignupPost");
		default:
			break;
	}

	return("Unknown");
}

/******************************************************************************/

bool ASFantasyIsapiDllLoader::isPageDataBinary(int pageNo) const
{
	return(pageNo >= 50);
}

/******************************************************************************/

 const char* ASFantasyIsapiDllLoader::promptOther(int pageNo,bool repeatLast) const
 {
	static CStrVar result;
	
	result.clear();
	switch(pageNo)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 9:
		case 10:
			result.copy(promptUserID());
			break;
		case 8:
			{
				char temp[256];
				
				result.copy(promptUserID());
				printf("Enter Game Date (x=none): ");
				scanf("%s",temp);
				if(stricmp(temp,"x") != 0)
					result.concatVarg("&GameDate=%s",temp);
			}
			break;
		case 11:
			{
				char temp[256];
				
				result.copy(promptUserID());
				printf("Enter TradeID (x=none): ");
				scanf("%s",temp);
				if(stricmp(temp,"x") != 0)
					result.concatVarg("&TradeID=%s",temp);
			}
			break;
		case 12:
			result.copy(promptUserID());
			break;
		case 13:
			result.copyVarg("&Source=Affinity");
			break;
		case 14:
			result.copyVarg("&Source=Affinity&PrizeEligible=T");
			break;
		case 15:
			result.copyVarg("&Source=Affinity&PrizeEligible=T");
			break;
		case 16:
			result.copy("&Source=Affinity&PrizeEligible=T&GameLevel=P&GamePrice=14.95");
			result.concat("&UserNameTxt=comp10200");
			result.concat("&UserPasswordTxt=bobbob");
			result.concat("&UserRePasswordTxt=bobbob");
			result.concat("&FirstNameTxt=Bob");
			result.concat("&LastNameTxt=Davidson");
			result.concat("&Street1Txt=xxx");
			result.concat("&CityTxt=yyy");
			result.concat("&StateTxt=pa");
			result.concat("&ZipCodeTxt=12345");
			result.concat("&CountryTxt=usa");
			result.concat("&EmailTxt=theref");
			result.concat("&ManagerNameTxt=Bob");
			result.concat("&RegionNameTxt=South Bronx");
			result.concat("&TeamNameTxt=Losers");
			result.concat("&CCardTypeSel=VS");
			result.concat("&CCardNumberTxt=1234-5678-9012-3456");
			result.concat("&CCardExpDateMonSel=10");
			result.concat("&CCardExpDateYearSel=1999");
			result.concat("&CCardNameOnTxt=Joe");
			break;
		case 17:
			result.copyVarg("&Source=Affinity&PrizeEligible=T");
			break;
		case 18:
			result.copyVarg("&Source=Affinity&PrizeEligible=T&GameLevel=P&GamePrice=12.95");

			result.concat("&FirstNameTxt=Bob");
			result.concat("&LastNameTxt=Davidson");
			result.concat("&Street1Txt=xxx");
			result.concat("&CityTxt=yyy");
			result.concat("&StateTxt=pa");
			result.concat("&ZipCodeTxt=12345");
			result.concat("&CountryTxt=usa");
			result.concat("&EmailTxt=theref");

			result.concat("&ManagerNameTxt=Bob");
			result.concat("&RegionNameTxt=South Bronx");
			result.concat("&TeamNameTxt=Losers");

			result.concat("&CCardTypeSel=VS");
			result.concat("&CCardNumberTxt=1234");
			result.concat("&CCardExpDateMonSel=10");
			result.concat("&CCardExpDateYearSel=1999");
			result.concat("&CCardNameOnTxt=Joe");
			break;
		default:
			break;
	}

	return(result);
 }

/******************************************************************************/

const char* ASFantasyIsapiDllLoader::promptUserID() const
{
	static CStr127 result;
	char particID[18];
	char password[12];
	TEncodedParticID encodedParticID;

	printf("Enter ParticID: (x=<none>)");
	scanf("%s",particID);
	if(stricmp(particID,"x") == 0)
		return("");
	printf("Enter Password: ");
	scanf("%s",password);
	
	EncodeUserIDPasswordType<TEncodedParticID>(particID,password,encodedParticID);

	result.CopyVarg("&User=%s",encodedParticID.c_str());
	return(result);
}

/******************************************************************************/

CStrVar ASFantasyIsapiDllLoader::promptEncodedPartic() const
{
	char particID[18];
	char password[12];
	TEncodedParticID encodedParticID;

	printf("Enter ParticID: ");
	scanf("%s",particID);
	printf("Enter Password: ");
	scanf("%s",password);
	
	EncodeUserIDPasswordType<TEncodedParticID>(particID,password,encodedParticID);

	return(encodedParticID.c_str());
}

/******************************************************************************/

void ASFantasyIsapiDllLoader::promptBinaryFiler(int pageNo,TBinaryFiler &filer)
{
	char temp[256];

	switch(pageNo)
	{
		case 51:
			filer.writeString("DraftRankingQueryRqst");
			filer.writeString(promptEncodedPartic().c_str());
			break;
			
		case 52:
			filer.writeString("DraftRankingUpdateRqst");
			filer.writeString(promptEncodedPartic().c_str());

			filer.writeShort(3);	// numPlayers
			filer.writeLong(4344);
			filer.writeLong(4267);
			filer.writeLong(3866);
			break;

		case 53:
			filer.writeString("PlayerScoutRqst");
			filer.writeString(promptEncodedPartic().c_str());
			
			filer.writeString("");	// PartialPlayerLastName
			filer.writeString("");	// ProfTeamAbbr

			// PositionVector
			filer.writeByte(1);	// numItems
			filer.writeByte(1);		//position

			// StatVector
			filer.writeByte(3);	// numItems
			filer.writeByte(1);	// statType
			filer.writeByte(syr_LastYear);	// statYearType
			filer.writeByte(2);	// statType
			filer.writeByte(syr_LastYear);	// statYearType
			filer.writeByte(3);	// statType
			filer.writeByte(syr_LastYear);	// statYearType

			filer.writeShort(25);	// SelectNumPlayers
			filer.writeByte(1);	// SelectByStat
			filer.writeBoolean(false);	// SelectByStatAsc

			filer.writeBoolean(false);	// IsFreeAgentRequest
			filer.writeBoolean(false);	// ShowRanked
			filer.writeBoolean(false);	// ShowDrafted
			filer.writeBoolean(true);	// ShowMyTeamPlayers
			filer.writeBoolean(false);	// ShowOtherTeamsPlayers
			break;

		case 54:
			filer.writeString("LeagueSignupRqst");
			filer.writeShort(lst_JoinOpenPublic);	//fLst
			filer.writeString(promptEncodedPartic().c_str());

			#if 1	//lst_JoinOpenPublic
			#elif 0	//lst_CreatePrivate
			filer.writeString("kickbutt");	//fLeaguePassword
			#else	//lst_JoinPrivate
			filer.writeLong(101);			//fLeagueID
			filer.writeString("kickbutt");	//fLeaguePassword
			#endif
			break;
			
		case 55:
			filer.writeString("SignupLeagueListRqst");

			printf("Enter Partial League Name (x=none): ");
			scanf("%s",temp);
			if(stricmp(temp,"x") == 0)
				memset(temp,0,sizeof(temp));
			filer.writeString(temp);
			break;

		case 56:
			filer.writeString("DraftResultRqst");
			filer.writeString(promptEncodedPartic().c_str());
			break;
			
		case 57:
			filer.writeString("ScheduleRqst");
			filer.writeString(promptEncodedPartic().c_str());
			break;

		case 58:
			filer.writeString("LineupQueryRqst");
			filer.writeString(promptEncodedPartic().c_str());
			filer.writeLong(0);
			break;

		case 59:
			filer.writeString("LineupUpdateRqst");
			filer.writeString(promptEncodedPartic().c_str());
			filer.writeShort(2);		// numLineups
			
			filer.writeShort(2);		// numPlayers
			filer.writeLong(4902);
			filer.writeLong(3901);
			
			filer.writeShort(2);		// numPlayers
			filer.writeLong(5845);
			filer.writeLong(4715);
			break;
			
		case 60:
			filer.writeString("GameResultsRqst");
			filer.writeString(promptEncodedPartic().c_str());
			filer.writeString("");	//fGameDate MM/DD/YYYY
			filer.writeLong(0);	//fHomeTeamID
			break;

		case 61:
			filer.writeString("StandingsRqst");
			filer.writeString(promptEncodedPartic().c_str());
			break;

		case 62:
			filer.writeString("FreeAgentQueryRqst");
			filer.writeString(promptEncodedPartic().c_str());
			break;

		case 63:
			filer.writeString("FreeAgentUpdateRqst");
			filer.writeString(promptEncodedPartic().c_str());
			filer.writeLong(6197);	//fClaimPlayerID
			filer.writeLong(4398);	//fReleasePlayerID
			break;

		case 66:
			filer.writeString("TradeProposeQueryRqst");
			filer.writeString(promptEncodedPartic().c_str());
			filer.writeLong(0);	//fTradeID
			break;

		case 67:
			filer.writeString("TradeProposeTeamRqst");
			filer.writeString(promptEncodedPartic().c_str());
			filer.writeLong(1004);	//fProposeToTeamID
			break;

		case 68:
			filer.writeString("TradeProposeUpdateRqst");
			filer.writeString(promptEncodedPartic().c_str());
			#if 1	//clear
			filer.writeLong(1);	//fTradeID
			filer.writeLong(0);	//fProposeToTeamID
			//fGetPlayerIDVector
			filer.writeShort(0);	//numPlayers
			//fGivePlayerIDVector
			filer.writeShort(0);	//numPlayers
			//fReleasePlayerIDVector
			filer.writeShort(0);	//numPlayers
			#else	//new
			filer.writeLong(0);	//fTradeID
			filer.writeLong(1004);	//fProposeToTeamID
			//fGetPlayerIDVector
			filer.writeShort(1);	//numPlayers
			filer.writeLong(4362);
			//fGivePlayerIDVector
			filer.writeShort(1);	//numPlayers
			filer.writeLong(4267);
			//fReleasePlayerIDVector
			filer.writeShort(0);	//numPlayers
			#endif
			break;

		case 69:
			filer.writeString("TradeReceiveUpdateRqst");
			filer.writeString(promptEncodedPartic().c_str());
			filer.writeLong(1);	//fTradeID
			filer.writeBoolean(true);	//fAccept
			//fReleasePlayerIDVector
			filer.writeShort(0);	//numPlayers
			break;

		case 70:
			filer.writeString("TradeProtestUpdateRqst");
			filer.writeString(promptEncodedPartic().c_str());
			filer.writeLong(1);	//fTradeID
			break;

		case 80:
			filer.writeString("PlayoffRqst");
			filer.writeString(promptEncodedPartic().c_str());
			break;

		default:
			break;
	}
}

/******************************************************************************/

ulong ASFantasyIsapiDllLoader::promptBinaryData(int pageNo,void* lpbDataBuffer,
	ulong lpbDataBufferSize)
{
	char* data = (char*)lpbDataBuffer;
	ulong dataSize = 0;

	switch(pageNo)
	{
		default:
			return(IsapiDllLoader::promptBinaryData(pageNo,lpbDataBuffer,
				lpbDataBufferSize));
	}

	return(dataSize);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
