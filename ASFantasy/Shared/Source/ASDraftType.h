/* ASDraftType.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASDraftTypeH
#define ASDraftTypeH

namespace asfantasy
{

/******************************************************************************/

class TDraftPosCountKey
{
public:
	TTeamID fTeamID;
	int fPos;

	TDraftPosCountKey(TTeamID teamID = TTeamID(),int pos = 0)
		{ fTeamID = teamID; fPos = pos; }

	bool operator<(TDraftPosCountKey rhs) const
	{
		if(fTeamID < rhs.fTeamID)
			return(true);

		if(fTeamID > rhs.fTeamID)
			return(false);

		return(fPos < rhs.fPos);
	}
};

class TDraftPosCount
{
public:
	TDraftPosCountKey fKey;
	int fCount;

	TDraftPosCount(TDraftPosCountKey key = TDraftPosCountKey(),int count = 0)
		{ fKey = key; fCount = count; }
		
	TDraftPosCountKey getKey() const { return(fKey); }
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASDraftTypeH
/******************************************************************************/
/******************************************************************************/
