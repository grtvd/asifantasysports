/* ASFantasyPlayerScoutDialog.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.util.*;

/******************************************************************************/

public abstract class ASFantasyPlayerScoutDialog extends Dialog
{
	//{{DECLARE_CONTROLS
	java.awt.Panel fBackgroundPnl;
	symantec.itools.awt.BorderPanel fSelectPnl;
	TAGLabel fPartialLastNameLbl;
	java.awt.TextField fPartialLastNameEdt;
	TAGLabel fProfTeamLbl;
	java.awt.Choice fProfTeamChc;
	symantec.itools.awt.BorderPanel fPositionPnl;
	symantec.itools.awt.BorderPanel fShowStatsPnl;
	TAGLabel fStat1Lbl;
	java.awt.Choice fStat1TypeChc;
	java.awt.Choice fStat1YearChc;
	TAGLabel fStat2Lbl;
	java.awt.Choice fStat2TypeChc;
	java.awt.Choice fStat2YearChc;
	TAGLabel fStat3Lbl;
	java.awt.Choice fStat3TypeChc;
	java.awt.Choice fStat3YearChc;
	TAGLabel fSelectTopLbl;
	java.awt.TextField fSelectTopEdt;
	TAGLabel fPlayersByLbl;
	java.awt.Choice fSelectTopByChc;
	java.awt.Checkbox fSelectTopByAscChk;
	java.awt.Checkbox fDontShowRankedChk;
	java.awt.Checkbox fDontShowDraftedChk;
	java.awt.Checkbox fShowMyTeamPlayersChk;
	java.awt.Checkbox fShowOtherTeamsPlayersChk;
	java.awt.Button fOKBtn;
	java.awt.Button fCancelBtn;
	//}}

	protected DialogClient fDialogClient;
	protected boolean fSuccess;
	
	protected PlayerScoutRqst fPlayerScoutRqst;
	protected TGameLevel fGameLevel;

	/**************************************************************************/

	public ASFantasyPlayerScoutDialog(Component component,
		DialogClient dialogClient,PlayerScoutRqst playerScoutRqst,
		TGameLevel gameLevel)
	{
		super(getFrame(component), "", false);

		fDialogClient = dialogClient;
		fSuccess = false;
		fPlayerScoutRqst = playerScoutRqst;
		fGameLevel = gameLevel;

		Dimension parentDim;
		Dimension dim;
		int showStatsOffset = 0;

		if(fGameLevel == TGameLevel.gml_Standard)
			showStatsOffset = -125;

		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(insets().left + insets().right + 414,insets().top + insets().bottom + 425 + showStatsOffset);
		setBackground(new Color(12632256));
		fBackgroundPnl = new java.awt.Panel();
		fBackgroundPnl.setLayout(null);
		fBackgroundPnl.reshape(insets().left + 0,insets().top + 0,414,425 + showStatsOffset);
		fBackgroundPnl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBackgroundPnl.setBackground(new Color(12632256));
		add(fBackgroundPnl);
		fSelectPnl = new symantec.itools.awt.BorderPanel();
		fSelectPnl.setLayout(null);
		fSelectPnl.reshape(0,0,319,201);
		fSelectPnl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBackgroundPnl.add(fSelectPnl);
		fSelectPnl.setLabel("Select Player By");
		fSelectPnl.setAlignStyle(symantec.itools.awt.BorderPanel.ALIGN_LEFT);
		fSelectPnl.setPaddingTop(6);
		fSelectPnl.setIPadBottom(10);
		fSelectPnl.setIPadSides(10);
		fSelectPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fPartialLastNameLbl = new TAGLabel();
		fPartialLastNameLbl.reshape(0,5,115,14);
		fSelectPnl.add(fPartialLastNameLbl);
		fPartialLastNameLbl.setAlignment(0);
		fPartialLastNameEdt = new java.awt.TextField();
		fPartialLastNameEdt.reshape(120,2,125,24);
		fPartialLastNameEdt.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fSelectPnl.add(fPartialLastNameEdt);
		fProfTeamLbl = new TAGLabel();
		fProfTeamLbl.reshape(0,35,115,14);
		fSelectPnl.add(fProfTeamLbl);

		fProfTeamLbl.setAlignment(0);
		fProfTeamChc = new java.awt.Choice();
		fProfTeamChc.addItem("--All--");
		addProfTeamChoiceItems(fProfTeamChc);
		fSelectPnl.add(fProfTeamChc);
		fProfTeamChc.reshape(120,30,85,23);
		fProfTeamChc.setFont(new Font("Helvetica", Font.PLAIN, 12));

		fPositionPnl = new symantec.itools.awt.BorderPanel();
		fPositionPnl.setLayout(null);
		fPositionPnl.reshape(0,60,285,100);
		fSelectPnl.add(fPositionPnl);
		fPositionPnl.setLabel("Position");
		fPositionPnl.setAlignStyle(symantec.itools.awt.BorderPanel.ALIGN_LEFT);
		fPositionPnl.setPaddingTop(6);
		fPositionPnl.setPaddingBottom(0);
		fPositionPnl.setPaddingLeft(0);
		fPositionPnl.setPaddingRight(0);
		fPositionPnl.setIPadSides(10);
		fPositionPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);

		createPositionCheckboxes(fPositionPnl);

		if(fGameLevel == TGameLevel.gml_Premium)
		{
			fShowStatsPnl = new symantec.itools.awt.BorderPanel();
			fShowStatsPnl.setLayout(null);
			fShowStatsPnl.reshape(0,201,319,125);
			fShowStatsPnl.setFont(new Font("Helvetica", Font.BOLD, 12));
			fBackgroundPnl.add(fShowStatsPnl);
			fShowStatsPnl.setLabel("Show Player Stats");
			fShowStatsPnl.setAlignStyle(symantec.itools.awt.BorderPanel.ALIGN_LEFT);
			fShowStatsPnl.setPaddingTop(6);
			fShowStatsPnl.setIPadBottom(10);
			fShowStatsPnl.setIPadSides(10);
			fShowStatsPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);

			fStat1Lbl = new TAGLabel();
			fStat1Lbl.reshape(0,5,45,14);
			fShowStatsPnl.add(fStat1Lbl);
			fStat1Lbl.setAlignment(0);

			fStat1TypeChc = new java.awt.Choice();
			fStat1TypeChc.addItem("--None--");
			addStatTypeChoiceItems(fStat1TypeChc);
			fShowStatsPnl.add(fStat1TypeChc);
			fStat1TypeChc.reshape(50,0,145,23);
			fStat1TypeChc.setFont(new Font("Helvetica", Font.PLAIN, 12));

			fStat1YearChc = new java.awt.Choice();
			addStatYearTypeChoiceItems(fStat1YearChc);
			fShowStatsPnl.add(fStat1YearChc);
			fStat1YearChc.reshape(205,0,80,23);
			fStat1YearChc.setFont(new Font("Helvetica", Font.PLAIN, 12));

			fStat2Lbl = new TAGLabel();
			fStat2Lbl.reshape(0,35,45,14);
			fShowStatsPnl.add(fStat2Lbl);
			fStat2Lbl.setAlignment(0);

			fStat2TypeChc = new java.awt.Choice();
			fStat2TypeChc.addItem("--None--");
			addStatTypeChoiceItems(fStat2TypeChc);
			fShowStatsPnl.add(fStat2TypeChc);
			fStat2TypeChc.reshape(50,30,145,23);
			fStat2TypeChc.setFont(new Font("Helvetica", Font.PLAIN, 12));

			fStat2YearChc = new java.awt.Choice();
			addStatYearTypeChoiceItems(fStat2YearChc);
			fShowStatsPnl.add(fStat2YearChc);
			fStat2YearChc.reshape(205,30,80,23);
			fStat2YearChc.setFont(new Font("Helvetica", Font.PLAIN, 12));

			fStat3Lbl = new TAGLabel();
			fStat3Lbl.reshape(0,62,45,14);
			fShowStatsPnl.add(fStat3Lbl);
			fStat3Lbl.setAlignment(0);

			fStat3TypeChc = new java.awt.Choice();
			fStat3TypeChc.addItem("--None--");
			addStatTypeChoiceItems(fStat3TypeChc);
			fShowStatsPnl.add(fStat3TypeChc);
			fStat3TypeChc.reshape(50,60,145,23);
			fStat3TypeChc.setFont(new Font("Helvetica", Font.PLAIN, 12));

			fStat3YearChc = new java.awt.Choice();
			addStatYearTypeChoiceItems(fStat3YearChc);
			fShowStatsPnl.add(fStat3YearChc);
			fStat3YearChc.reshape(205,60,80,23);
			fStat3YearChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		}
		fSelectTopLbl = new TAGLabel();
		fSelectTopLbl.reshape(10,showStatsOffset + 330,67,14);
		fBackgroundPnl.add(fSelectTopLbl);
		fSelectTopLbl.setAlignment(0);
		fSelectTopEdt = new java.awt.TextField();
		fSelectTopEdt.reshape(80,showStatsOffset + 326,35,24);
		fSelectTopEdt.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fBackgroundPnl.add(fSelectTopEdt);
		fPlayersByLbl = new TAGLabel();
		fPlayersByLbl.reshape(125,showStatsOffset + 330,70,14);
		fBackgroundPnl.add(fPlayersByLbl);
		fPlayersByLbl.setAlignment(0);
		fSelectTopByChc = new java.awt.Choice();
		fSelectTopByChc.addItem("Name");
		if(fGameLevel == TGameLevel.gml_Standard)
		{
			fSelectTopByChc.addItem("Total Pts");
		}
		else
		{
			fSelectTopByChc.addItem("Stat 1");
			fSelectTopByChc.addItem("Stat 2");
			fSelectTopByChc.addItem("Stat 3");
		}
		fBackgroundPnl.add(fSelectTopByChc);
		fSelectTopByChc.reshape(196,showStatsOffset + 325,65,23);
		fSelectTopByChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fSelectTopByAscChk = new java.awt.Checkbox("Asc");
		fSelectTopByAscChk.reshape(268,showStatsOffset + 332,45,14);
		fBackgroundPnl.add(fSelectTopByAscChk);

		fDontShowRankedChk = new java.awt.Checkbox("Don't Show Ranked Players (last submitted)");
		fDontShowRankedChk.reshape(10,showStatsOffset + 360,300,14);
		fBackgroundPnl.add(fDontShowRankedChk);

		fDontShowDraftedChk = new java.awt.Checkbox("Don't Show Drafted Players");
		fDontShowDraftedChk.reshape(10,showStatsOffset + 385,300,14);
		fBackgroundPnl.add(fDontShowDraftedChk);

		fShowMyTeamPlayersChk = new java.awt.Checkbox("Include My Team's Players in Search");
		fShowMyTeamPlayersChk.reshape(10,showStatsOffset + 360,300,14);
		fBackgroundPnl.add(fShowMyTeamPlayersChk);

		fShowOtherTeamsPlayersChk = new java.awt.Checkbox("Include Other Teams' Players in Search");
		fShowOtherTeamsPlayersChk.reshape(10,showStatsOffset + 385,300,14);
		fBackgroundPnl.add(fShowOtherTeamsPlayersChk);

		fOKBtn = new java.awt.Button("Scout");
		fOKBtn.reshape(329,10,70,20);
		fOKBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBackgroundPnl.add(fOKBtn);
		fCancelBtn = new java.awt.Button("Cancel");
		fCancelBtn.reshape(329,43,70,20);
		fCancelBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBackgroundPnl.add(fCancelBtn);
		setTitle("Scout Players");
		setResizable(false);
		//}}

		fPartialLastNameLbl.setText("Partial Last Name");
		fProfTeamLbl.setText(getProfTeamLblText());
		if(fGameLevel == TGameLevel.gml_Premium)
		{
			fStat1Lbl.setText("Stat 1");
			fStat2Lbl.setText("Stat 2");
			fStat3Lbl.setText("Stat 3");
		}
		fSelectTopLbl.setText("Select top");
		fPlayersByLbl.setText("players by");

		parentDim = getToolkit().getScreenSize();
		dim = size();
		move(((parentDim.width - dim.width) / 2),
			((parentDim.height - dim.height) / 2));
//		resize(dim.width,dim.height);

		loadData();
	}

	/**************************************************************************/

	abstract protected String getProfTeamLblText();

	abstract protected void addProfTeamChoiceItems(java.awt.Choice profTeamChc);

	abstract protected void createPositionCheckboxes(
		symantec.itools.awt.BorderPanel positionPnl);

	abstract protected void addStatTypeChoiceItems(java.awt.Choice statTypeChc);

	/**************************************************************************/

	protected void addStatYearTypeChoiceItems(java.awt.Choice statYearChc)
	{
		statYearChc.addItem("This Year");
		statYearChc.addItem("Last 2 Weeks");
		statYearChc.addItem("Last 4 Weeks");
		statYearChc.addItem("Last 8 Weeks");
		statYearChc.addItem("Last Year");
		statYearChc.addItem("2 Years Ago");
		statYearChc.addItem("3 Years Ago");
	}

	/**************************************************************************/

	protected StatYearType convertChoiceIndexToStatYearType(int index)
	{
		switch(index)
		{
			default:
			case 0:
				return(StatYearType.syr_YearToDate);
			case 1:
				return(StatYearType.syr_LastTwoWeeks);
			case 2:
				return(StatYearType.syr_LastFourWeeks);
			case 3:
				return(StatYearType.syr_LastEightWeeks);
			case 4:
				return(StatYearType.syr_LastYear);
			case 5:
				return(StatYearType.syr_TwoYearsAgo);
			case 6:
				return(StatYearType.syr_ThreeYearsAgo);
		}
	}

	/**************************************************************************/

	protected int convertStatYearTypeToChoiceIndex(StatYearType statYear)
	{
		if(statYear == StatYearType.syr_LastTwoWeeks)
			return(1);
		if(statYear == StatYearType.syr_LastFourWeeks)
			return(2);
		if(statYear == StatYearType.syr_LastEightWeeks)
			return(3);
		if(statYear == StatYearType.syr_LastYear)
			return(4);
		if(statYear == StatYearType.syr_TwoYearsAgo)
			return(5);
		if(statYear == StatYearType.syr_ThreeYearsAgo)
			return(6);

		//Default, StatYearType.syr_YearToDate
		return(0);
	}

	/**************************************************************************/

	protected static Frame getFrame(Component component)
	{
		Component c = component;

		if(c instanceof Frame)
			return (Frame)c;

		while((c = c.getParent()) != null)
		{
			if(c instanceof Frame)
				return (Frame)c;
		}
		
		return null;
	}

	/**************************************************************************/

	public boolean action(Event evt,Object arg)
	{
		if(evt.id == Event.ACTION_EVENT)
		{
			if(evt.target == fOKBtn)
			{
				if(validateData())
				{
					unloadData();
					fSuccess = true;
					hide();
					fDialogClient.dialogDismissed(this);
					dispose();
				}
			}
			else if(evt.target == fCancelBtn)
			{
				hide();
				fDialogClient.dialogDismissed(this);
				dispose();
			}
			else
				return false;
		}
		else
			return false;

		return true;
	}

	/**************************************************************************/

	public boolean success()
	{
		return(fSuccess);
	}
	
	/**************************************************************************/

	protected void loadData()
	{
		// Partial Last Name, NFL Team
		fPartialLastNameEdt.setText(fPlayerScoutRqst.fPartialPlayerLastName);
		if(fPlayerScoutRqst.fProfTeamAbbr.length() > 0)
			fProfTeamChc.select(fPlayerScoutRqst.fProfTeamAbbr);

		// Positions
		loadAllPositions();
			
		// Show Stats
		if(fGameLevel == TGameLevel.gml_Premium)
		{
			loadPlayerScoutStat(fStat1TypeChc,fStat1YearChc,
				fPlayerScoutRqst.fStatVector,0);
					
			loadPlayerScoutStat(fStat2TypeChc,fStat2YearChc,
				fPlayerScoutRqst.fStatVector,1);
					
			loadPlayerScoutStat(fStat3TypeChc,fStat3YearChc,
				fPlayerScoutRqst.fStatVector,2);
		}
				
		// Show Top # by Stat
		fSelectTopEdt.setText(Integer.toString(
			fPlayerScoutRqst.fSelectNumPlayers));
			
		fSelectTopByChc.select(fPlayerScoutRqst.fSelectByStat);
		fSelectTopByAscChk.setState(fPlayerScoutRqst.fSelectByStatAsc);

		if(fPlayerScoutRqst.fIsFreeAgentRequest)
		{
			fDontShowRankedChk.show(false);
			fDontShowDraftedChk.show(false);

			fShowMyTeamPlayersChk.setState(fPlayerScoutRqst.fShowMyTeamPlayers);
			fShowOtherTeamsPlayersChk.setState(fPlayerScoutRqst.fShowOtherTeamsPlayers);
		}
		else
		{
			fShowMyTeamPlayersChk.show(false);
			fShowOtherTeamsPlayersChk.show(false);

			fDontShowRankedChk.setState(!fPlayerScoutRqst.fShowRanked);
			fDontShowDraftedChk.setState(!fPlayerScoutRqst.fShowDrafted);
		}
	}

	/**************************************************************************/

	protected boolean validateData()
	{
		short selectNumPlayers;

		selectNumPlayers = (short)(Integer.valueOf(fSelectTopEdt.getText()
			).intValue());

		if((selectNumPlayers < 1) ||
				(selectNumPlayers > PlayerScoutRqst.maxSelectNumPlayers))
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"The \"Select top players\" value must be between 1 and " +
					PlayerScoutRqst.maxSelectNumPlayers + ".");
			return(false);
		}

		return(true);
	}

	/**************************************************************************/

	protected void unloadData()
	{
		// Partial Last Name, NFL Team
		fPlayerScoutRqst.fPartialPlayerLastName = fPartialLastNameEdt.getText();
		if(fProfTeamChc.getSelectedIndex() > 0)
			fPlayerScoutRqst.fProfTeamAbbr = fProfTeamChc.getSelectedItem();
		else
			fPlayerScoutRqst.fProfTeamAbbr = "";
			
		// Positions
		fPlayerScoutRqst.fPositionVector.removeAllElements();
		unloadAllPositions();
	
		// Show Stats
		if(fGameLevel == TGameLevel.gml_Premium)
		{
			fPlayerScoutRqst.fStatVector.removeAllElements();
			
			unloadPlayerScoutStat(fStat1TypeChc,fStat1YearChc,
				fPlayerScoutRqst.fStatVector);
					
			unloadPlayerScoutStat(fStat2TypeChc,fStat2YearChc,
				fPlayerScoutRqst.fStatVector);
					
			unloadPlayerScoutStat(fStat3TypeChc,fStat3YearChc,
				fPlayerScoutRqst.fStatVector);
		}
		
		// Show Top # by Stat
		fPlayerScoutRqst.fSelectNumPlayers = (short)(Integer.valueOf(
			fSelectTopEdt.getText()).intValue());

		fPlayerScoutRqst.fSelectByStat = (byte)fSelectTopByChc.getSelectedIndex();
		fPlayerScoutRqst.fSelectByStatAsc = fSelectTopByAscChk.getState();
			
		if(fPlayerScoutRqst.fIsFreeAgentRequest)
		{
			fPlayerScoutRqst.fShowMyTeamPlayers = fShowMyTeamPlayersChk.getState();
			fPlayerScoutRqst.fShowOtherTeamsPlayers = fShowOtherTeamsPlayersChk.getState();
		}
		else
		{
			fPlayerScoutRqst.fShowRanked = !fDontShowRankedChk.getState();
			fPlayerScoutRqst.fShowDrafted = !fDontShowDraftedChk.getState();
		}
	}
	
	/**************************************************************************/

	abstract protected void loadAllPositions();

	/**************************************************************************/

	protected void loadPosition(Checkbox posChk,TPosition position,
		Vector positionVector)
	{
		int i,numItems = positionVector.size();

		for(i = 0; i < numItems; i++)
		{
			if(position == (TPosition)positionVector.elementAt(i))
			{
				posChk.setState(true);
				return;
			}
		}

		posChk.setState(false);
	}
	
	/**************************************************************************/

	abstract protected void unloadAllPositions();

	/**************************************************************************/

	protected void unloadPosition(Checkbox posChk,TPosition position,
		Vector positionVector)
	{
		if(posChk.getState())
			positionVector.addElement(position);
	}
	
	/**************************************************************************/
	
	protected void loadPlayerScoutStat(Choice statTypeChc,Choice statYearChc,
		Vector statVector,int pos)
	{
		if(statVector.size() > pos)
		{
			PlayerScoutStat playerScoutStat =
				(PlayerScoutStat)statVector.elementAt(pos);
			
			statTypeChc.select((int)PlayerStatType.convertToByte(
				playerScoutStat.fStatType));
			
			if(playerScoutStat.fStatYear != StatYearType.syr_Undefined)
			{
				statYearChc.select(convertStatYearTypeToChoiceIndex(
					playerScoutStat.fStatYear));
			}
		}
	}
	
	/**************************************************************************/
	
	protected void unloadPlayerScoutStat(Choice statTypeChc,Choice statYearChc,
		Vector statVector)
	{
		PlayerScoutStat playerScoutStat = new PlayerScoutStat();
		
		playerScoutStat.fStatType = PlayerStatType.convertFromByte(
			(byte)(statTypeChc.getSelectedIndex()));

		playerScoutStat.fStatYear = convertChoiceIndexToStatYearType(
			statYearChc.getSelectedIndex());

		statVector.addElement(playerScoutStat);
	}
	
}

/******************************************************************************/
/******************************************************************************/

