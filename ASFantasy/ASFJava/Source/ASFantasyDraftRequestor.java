/* ASFantasyDraftRequestor.java */

/******************************************************************************/
/******************************************************************************/

//import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class ASFantasyDraftRequestor extends ASFantasyRequestor
{
	/**************************************************************************/

	public ASFantasyDraftRequestor(String hostName,int hostPortID,
		String requestDll,String encodedParticID)
	{
		super(hostName,hostPortID,requestDll,encodedParticID);
	}

	/**************************************************************************/
	
	public SignupLeagueListResp signupLeagueListRequest(String partialLeagueName)
	{
		SignupLeagueListRqst requestObj = new SignupLeagueListRqst(partialLeagueName);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof SignupLeagueListResp)
			{
				return((SignupLeagueListResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public LeagueSignupResp leagueSignupRequest(LeagueSignupRqst requestObj)
	{
		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof LeagueSignupResp)
			{
				return((LeagueSignupResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public DraftRankingQueryResp draftRankingQueryRequest()
	{
		DraftRankingQueryRqst requestObj = new DraftRankingQueryRqst(
			fEncodedParticID);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof DraftRankingQueryResp)
			{
				return((DraftRankingQueryResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public DraftRankingUpdateResp draftRankingUpdateRequest(
		DraftRankingPlayerVector playerVector)
	{
		DraftRankingUpdateRqst requestObj = new DraftRankingUpdateRqst(
			fEncodedParticID,playerVector);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof DraftRankingUpdateResp)
			{
				return((DraftRankingUpdateResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public DraftResultResp draftResultRequest()
	{
		DraftResultRqst requestObj = new DraftResultRqst(fEncodedParticID);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof DraftResultResp)
			{
				return((DraftResultResp)responseObj);
			}
		}

		return(null);
	}

}

/******************************************************************************/
/******************************************************************************/
