/* ASFantasyRequestor.java */

/******************************************************************************/
/******************************************************************************/

//import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

public abstract class ASFantasyRequestor
{
	private String fHostName = null;
	//BOB private final static String fRequestDll = "/Scripts/ASFbIsOb.dll";
	private String fRequestDll = null;
	//private int fHostPortID = 0;
	protected String fEncodedParticID = null;

	/**************************************************************************/

	public ASFantasyRequestor(String hostName,int hostPortID,String requestDll,
		String encodedParticID)
	{
		fHostName = (hostName == null) ? "" : hostName;
		//fHostPortID = hostPortID;
		fRequestDll = (requestDll == null) ? "" : requestDll;
		fEncodedParticID = (encodedParticID == null) ? "" : encodedParticID;
	}

	/**************************************************************************/
	
	public String getEncodeParticID() { return(fEncodedParticID); }

	/**************************************************************************/

	public Object request(Object requestObj)
	{
		TAGRequesterParam requesterParam = new TAGURLRequesterParam(fHostName,
			fRequestDll);

		Object responseObj = TAGRequester.request(requesterParam,requestObj);

		return(responseObj);
	}

	/**************************************************************************/
	/**************************************************************************/
	
	public PlayerScoutResp playerScoutRequest(PlayerScoutRqst requestObj)
	{
		requestObj.fEncodedParticID = fEncodedParticID;

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof PlayerScoutResp)
			{
				return((PlayerScoutResp)responseObj);
			}
		}

		return(null);
	}

}

/******************************************************************************/
/******************************************************************************/
