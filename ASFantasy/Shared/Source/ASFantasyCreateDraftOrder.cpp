/* ASFantasyCreateDraftOrder.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include <algorith.h>
#include <vector.h>

#include "ASFantasyAppOptions.h"
#include "ASFantasyCreateDraftOrder.h"

namespace asfantasy
{

/******************************************************************************/

const int	DraftTeamCountMin = MinTeamsPerPrivateLeague();
const int	DraftTeamCountMax = MaxTeamsPerPrivateLeague();

/******************************************************************************/

// Basic draft order for leagues with 8-15 teams
// The order for each round is listed vertically.

static char DraftBlock8[] = {
		 1,  8,  5,  4,  3,  6,  7,  2,
		 2,  7,  6,  3,  4,  5,  8,  1,
		 3,  6,  7,  2,  1,  8,  5,  4,
		 4,  5,  8,  1,  2,  7,  6,  3,
		 5,  4,  1,  8,  7,  2,  3,  6,
		 6,  3,  2,  7,  8,  1,  4,  5,
		 7,  2,  3,  6,  5,  4,  1,  8,
		 8,  1,  4,  5,  6,  3,  2,  7
	};

static char DraftBlock9[] = {
		 1,  9,  5,  4,  3,  7,  8,  2,  6,
		 2,  8,  6,  3,  5,  4,  9,  1,  7,
		 3,  7,  8,  2,  4,  5,  6,  9,  1,
		 4,  5,  9,  7,  1,  6,  2,  8,  3,
		 5,  6,  1,  9,  2,  8,  3,  7,  4,
		 6,  4,  7,  1,  9,  2,  5,  3,  8,
		 7,  3,  2,  8,  6,  9,  1,  4,  5,
		 8,  2,  3,  6,  7,  1,  4,  5,  9,
		 9,  1,  4,  5,  8,  3,  7,  6,  2
	};

static char DraftBlock10[] = {
		 1, 10,  6,  5,  4,  7,  9,  2,  8,  3,
		 2,  9,  8,  3,  5,  6, 10,  1,  7,  4,
		 3,  8,  7,  4,  2,  9,  6,  5, 10,  1,
		 4,  7,  9,  2,  1, 10,  8,  3,  6,  5,
		 5,  6, 10,  1,  3,  8,  7,  4,  9,  2,
		 6,  5,  1, 10,  8,  3,  4,  7,  2,  9,
		 7,  4,  2,  9, 10,  1,  3,  8,  5,  6,
		 8,  3,  4,  7,  9,  2,  5,  6,  1, 10,
		 9,  2,  3,  8,  6,  5,  1, 10,  4,  7,
		10,  1,  5,  6,  7,  4,  2,  9,  3,  8
	};

static char DraftBlock11[] = {
		 1, 11,  7,  5,  3,  6,  8,  2,  9,  4, 10,
		 2, 10,  8,  4,  1,  7,  9,  3,  5,  6, 11,
		 3,  9,  6,  2,  4, 10,  7,  5, 11,  8,  1,
		 4,  8,  9,  3,  5, 11,  6, 10,  1,  7,  2,
		 5,  6, 10,  1,  2,  9, 11,  4,  7,  3,  8,
		 6,  7, 11, 10,  8,  4,  5,  1,  2,  9,  3,
		 7,  5,  1, 11,  9,  8, 10,  6,  3,  2,  4,
		 8,  4,  3,  9, 11,  2,  1,  7, 10,  5,  6,
		 9,  3,  2,  6, 10,  5,  4, 11,  8,  1,  7,
		10,  2,  4,  8,  7,  1,  3,  9,  6, 11,  5,
		11,  1,  5,  7,  6,  3,  2,  8,  4, 10,  9
	};

static char DraftBlock12[] = {
		 1, 12,  7,  6,  2, 11,  8,  5,  3, 10,  9,  4,
		 2, 11,  8,  5,  4,  9, 10,  3,  1, 12,  7,  6,
		 3, 10,  9,  4,  6,  7, 12,  1,  5,  8, 11,  2,
		 4,  9, 10,  3,  1, 12,  7,  6,  2, 11,  8,  5,
		 5,  8, 11,  2,  3, 10,  9,  4,  6,  7, 12,  1,
		 6,  7, 12,  1,  5,  8, 11,  2,  4,  9, 10,  3,
		 7,  6,  1, 12,  8,  5,  2, 11,  9,  4,  3, 10,
		 8,  5,  2, 11, 10,  3,  4,  9,  7,  6,  1, 12,
		 9,  4,  3, 10, 12,  1,  6,  7, 11,  2,  5,  8,
		10,  3,  4,  9,  7,  6,  1, 12,  8,  5,  2, 11,
		11,  2,  5,  8,  9,  4,  3, 10, 12,  1,  6,  7,
		12,  1,  6,  7, 11,  2,  5,  8, 10,  3,  4,  9
	};

static char DraftBlock13[] = {
		 1, 13,  8,  7,  4, 12, 10,  5,  2, 11,  9,  3,  6,
		 2, 12,  9,  6,  5, 13, 11,  1,  3, 10,  4,  7,  8,
		 3, 11, 10,  5,  6,  7,  9,  2,  1,  8, 12, 13,  4,
		 4, 10, 11,  3,  1,  8,  7,  6,  5, 12,  2,  9, 13,
		 5,  9, 12,  4,  2, 11, 13,  3,  6,  7,  8, 10,  1,
		 6,  7, 13,  1,  3, 10,  8,  4,  9,  2, 11, 12,  5,
		 7,  8,  1,  2,  9,  3, 12, 13,  4,  5,  6, 11, 10,
		 8,  6,  2, 13, 10,  9,  4, 12,  7,  3,  1,  5, 11,
		 9,  5,  4, 12, 11,  2,  3,  8, 13,  6, 10,  1,  7,
		10,  4,  3, 11,  8,  1,  6,  7, 12, 13,  5,  2,  9,
		11,  3,  5, 10,  7,  6,  2,  9,  8,  1, 13,  4, 12,
		12,  2,  6,  9, 13,  5,  1, 11, 10,  4,  7,  8,  3,
		13,  1,  7,  8, 12,  4,  5, 10, 11,  9,  3,  6,  2
	};

static char DraftBlock14[] = {
		 1, 14,  8,  7,  5, 10, 12,  3,  4, 11,  9,  6,  2, 13,
		 2, 13,  9,  6,  4, 11, 10,  5,  1, 14,  8,  7,  3, 12,
		 3, 12, 11,  4,  1, 14,  9,  6,  7,  8, 13,  2,  5, 10,
		 4, 11, 10,  5,  2, 13,  8,  7,  6,  9, 12,  3,  1, 14,
		 5, 10, 12,  3,  7,  8, 14,  1,  2, 13, 11,  4,  6,  9,
		 6,  9, 13,  2,  3, 12, 11,  4,  5, 10, 14,  1,  7,  8,
		 7,  8, 14,  1,  6,  9, 13,  2,  3, 12, 10,  5,  4, 11,
		 8,  7,  1, 14,  9,  6,  2, 13, 12,  3,  5, 10, 11,  4,
		 9,  6,  2, 13, 12,  3,  4, 11, 10,  5,  1, 14,  8,  7,
		10,  5,  3, 12,  8,  7,  1, 14, 13,  2,  4, 11,  9,  6,
		11,  4,  5, 10, 13,  2,  7,  8,  9,  6,  3, 12, 14,  1,
		12,  3,  4, 11, 14,  1,  6,  9,  8,  7,  2, 13, 10,  5,
		13,  2,  6,  9, 11,  4,  5, 10, 14,  1,  7,  8, 12,  3,
		14,  1,  7,  8, 10,  5,  3, 12, 11,  4,  6,  9, 13,  2
	};

static char DraftBlock15[] = {
		 1, 15,  8,  7,  3, 12, 10,  4,  5, 14,  9,  2,  6, 13, 11,
		 2, 14,  9,  6,  5, 11, 13,  7,  3, 15,  8,  4,  1, 10, 12,
		 3, 13, 10,  4,  2, 14,  9,  6,  1, 11, 12,  7,  5, 15,  8,
		 4, 12, 11,  5,  6, 15, 14,  1,  2,  8, 10,  3,  7,  9, 13,
		 5, 11, 12,  3,  1, 13, 15,  8,  4,  9, 14, 10,  2,  7,  6,
		 6, 10, 13,  2,  8,  9, 11,  5,  7, 12, 15,  1,  3,  4, 14,
		 7,  8, 14,  1,  4, 10, 12,  3,  6, 13, 11,  5,  9,  2, 15,
		 8,  9, 15, 14,  7,  4,  3,  2, 10,  6, 13, 12, 11,  1,  5,
		 9,  7,  1, 15, 10,  8,  5, 12, 13,  4,  3,  6, 14, 11,  2,
		10,  6,  2, 13,  9,  7,  8, 11, 12,  1,  4, 14, 15,  5,  3,
		11,  5,  3, 12, 13,  1,  2, 15,  8, 10,  6,  9,  4, 14,  7,
		12,  4,  5, 11, 15,  6,  1, 14,  9,  7,  2, 13,  8,  3, 10,
		13,  3,  4, 10, 14,  2,  6,  9, 11,  5,  7, 15, 12,  8,  1,
		14,  2,  6,  9, 11,  5,  7, 13, 15,  3,  1,  8, 10, 12,  4,
		15,  1,  7,  8, 12,  3,  4, 10, 14,  2,  5, 11, 13,  6,  9
	};

// Index of team count returns associated draft block
static char *	DraftBlockArray[] = {
		/* Team Count = 8 */	DraftBlock8,
		/* Team Count = 9 */	DraftBlock9,
		/* Team Count = 10 */	DraftBlock10,
		/* Team Count = 11 */	DraftBlock11,
		/* Team Count = 12 */	DraftBlock12,
		/* Team Count = 13 */	DraftBlock13,
		/* Team Count = 14 */	DraftBlock14,
		/* Team Count = 15 */	DraftBlock15,
	};

/******************************************************************************/

static void FillDraftOrder( int numRounds, TDraftRoundVector& draftRoundVector,
	TTeamIDVector& teamIDList );

#ifdef TOOLDEBUGON
static void VerifyDraftOrder( int numRounds, int numTeams,
	TDraftRoundVector& draftRoundVector );
static void PrintDraftOrder( int numRounds, int numTeams,
	TDraftRoundVector& draftRoundVector );
#endif

/******************************************************************************/

TDraftOrderPtr CreateDraftOrder( TLeagueID leagueID, TTeamIDVector& teamIDList )
{
	TDraftOrderPtr	draftOrderPtr;

	// verify the team count is valid
	if ((teamIDList.size() < DraftTeamCountMin) || (teamIDList.size() > DraftTeamCountMax))
		throw ASIException("CreateDraftOrder: invalid team count");

	// randomize list of teams
	std::random_shuffle( teamIDList.begin(), teamIDList.end() );

	// create a new draft order
	draftOrderPtr = TDraftOrder::newInstance();
	draftOrderPtr->setLeagueID( leagueID );

	// access draft round information
	TDraftRoundVector& draftRoundVector = draftOrderPtr->draftRoundVector();

	// fill in the draft order
	FillDraftOrder( NumDraftRounds(), draftRoundVector, teamIDList );

	// update the draft order and return it to the caller
	draftOrderPtr->update();
	return (draftOrderPtr);
}

/******************************************************************************/

void FillDraftOrder( int numRounds, TDraftRoundVector& draftRoundVector,
	TTeamIDVector& teamIDList )
{
	TTeamIDVector	teamIDRoundOrder;
	TTeamID 		teamID;
	char			* draftBlock, * currentPickIdx;
	int				i, j, teamCount;

	// initialize
	teamCount = teamIDList.size();
	draftBlock = DraftBlockArray[teamCount - DraftTeamCountMin];

	// delete old draft information
	draftRoundVector.erase(draftRoundVector.begin(),draftRoundVector.end());

	// loop through all of the draft rounds
	for (i=0; i<numRounds; i++)
	{
		// find start of preset draft information for this round
		currentPickIdx = draftBlock + (i % teamCount);

		// clear old picks
		teamIDRoundOrder.erase(teamIDRoundOrder.begin(),teamIDRoundOrder.end());

		// loop through all of the teams
		for (j=0; j<teamCount; j++, currentPickIdx+=teamCount)
		{
			// insert a team into this round
			teamID = teamIDList[((int) *currentPickIdx) - 1];	// must be 0 based
			teamIDRoundOrder.push_back(teamID);
		}

		// verify that appropriate number of teams is in the list
		if (teamIDRoundOrder.size() != teamCount)
			throw ASIException("Failure adding team to draft order");

		// add new draft round
		draftRoundVector.push_back(teamIDRoundOrder);
	}

	// verify appropriate number of rounds were added
	if (draftRoundVector.size() != numRounds)
		throw ASIException("FillDraftOrder: Failure adding round to draft order");

#if 0 //defined(TOOLDEBUGON)
	// print the draft order to a file (do it before verify in case of error)
	PrintDraftOrder( numRounds, teamCount, draftRoundVector );
#endif

#if defined(TOOLDEBUGON)
	// verify that each team appears once per round and once per position
	VerifyDraftOrder( numRounds, teamCount, draftRoundVector );
#endif
}

/******************************************************************************/

#ifdef TOOLDEBUGON
static void VerifyDraftOrder( int numRounds, int numTeams,
	TDraftRoundVector& draftRoundVector )
{
	auto_ptr<long> teamPicksBuffer(new long[numTeams]);
	long *	teamPicks, teamID;
	int		size, round, teamIndex, i;

	if(numRounds != draftRoundVector.size())
		throw ASIException("VerifyDraftOrder: numRounds != draftRoundVector.size()");
		
	teamPicks = teamPicksBuffer.get();
	size = sizeof(long) * numTeams;

	// verify that each team only appears once in each round
	for (round=0; round<numRounds; round++)
	{
		TTeamIDVector	teamIDRoundOrder = draftRoundVector[round];

		if(numTeams != teamIDRoundOrder.size())
			throw ASIException("VerifyDraftOrder: numTeams != teamIDRoundOrder.size()");

		memset( teamPicks, 0, size );
		for (teamIndex=0; teamIndex<numTeams; teamIndex++)
		{
			// get next team ID
			teamID = teamIDRoundOrder[teamIndex].getID();

			// verify that team is not already in the list
			for (i=0; i<teamIndex; i++)
			{
				if (teamPicks[i] == teamID)
					throw ASIException("VerifyDraftOrder::Team %ld chooses "
						"multiple times in round %d",teamID,round);
			}
			teamPicks[teamIndex] = teamID;
		}
	}
}
#endif

/******************************************************************************/

#if 0	//def TOOLDEBUGON
static void PrintDraftOrder( int numRounds, int numTeams,
	TDraftRoundVector& draftRoundVector )
{
	FILE *	fp;

	fp = fopen( "DraftOrderDebug.txt", "wt" );
	if (fp != NULL)
	{
		for (int i=0; i<numRounds; i++)
		{
			TTeamIDVector&	teamIDRoundOrder = draftRoundVector[i];

			fprintf(fp,"Round: %d\n", i + 1);
			for (int j=0; j<numTeams; j++)
			{
				TTeamID	id = teamIDRoundOrder[j];
				fprintf(fp,"team %ld\n", id.getID());
			}
			fprintf(fp,"\n");
		}
		fclose(fp);
	}
}
#endif

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/


