/* ASFOrbServer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFOrbServer.h"

using namespace tag;

/******************************************************************************/

#pragma resource "*.dfm"

/******************************************************************************/
/******************************************************************************/

TASFOrbServerNotify::TASFOrbServerNotify()
{
	fListBox = NULL;
}

/******************************************************************************/

void TASFOrbServerNotify::notify(const AnsiString &msg)
{
	if (fListBox != NULL)
		fListBox->Items->Add(msg);
}

/******************************************************************************/

void TASFOrbServerNotify::setListBox(TListBox &ListBox)
{
	fListBox = &ListBox;
}

/******************************************************************************/
/******************************************************************************/

__fastcall TASFOrbServer::TASFOrbServer(TComponent* Owner) : TForm(Owner)
{
}

/******************************************************************************/

TASFOrbServer* TASFOrbServer::Open(System::TMetaClass* InstanceClass) throw(Exception)
{
	TASFOrbServer *server;
	TFulfillerNotify *notify;
	int portID;
	int pos;
	
	// Create Form
	Application->CreateForm(InstanceClass,&server);

	if (dynamic_cast<TASFOrbServer*>(server) == NULL)
		throw Exception("TASFOrbServer::Open: invalid InstanceClass, not derived from TASFOrbServer");

	Application->Title = server->GetApplicationTitle();
	server->Caption = server->GetApplicationTitle();
	
	// Link ListBox1 to FulfillerNotity
	notify = &server->GetFulfiller().getFulfillerNotify();
	
	if (dynamic_cast<TASFOrbServerNotify*>(notify) != NULL)
		((TASFOrbServerNotify*)notify)->setListBox(*server->ListBox1);

	// Get PortID from command line or use default.
	if (ParamCount() > 0)
		portID = atoi(ParamStr(1).c_str());
	else
		portID = server->GetDefaultPortID();

	// Get Form Position from command line
	if (ParamCount() > 1)
	{
		pos = atoi(ParamStr(2).c_str());
		server->Position = poDesigned;
		server->Top = 25 + (pos * 25);
		server->Left = 25 + (pos * 25);
	}
	else
		server->Position = poScreenCenter;

	// Initiate TCP/IP Listen		
	server->BeginListening(portID);
	
	return server;
}                      

/******************************************************************************/

void __fastcall TASFOrbServer::FormCreate(TObject *Sender)
{
	Initialize();
	
	SetStatusLabel(TCP1);
}

/******************************************************************************/

void __fastcall TASFOrbServer::FormDestroy(TObject *Sender)
{
	if (Listening)
		TCP1->Close();

	Release();
}

/******************************************************************************/

void __fastcall TASFOrbServer::BeginListening(int PortID)
{
	char s[20];

	sprintf(s,"%d",PortID);
	PortIDLbl->Caption = s;
	ListeningSpeedButton->Down = true;
	ListeningSpeedButtonClick(ListeningSpeedButton);
}

/******************************************************************************/

void __fastcall TASFOrbServer::ListeningSpeedButtonClick(TObject *Sender)
{
	if (!Listening)
	{
		TCP1->LocalPort = StrToInt(PortIDLbl->Caption);
		TCP1->Listen();
		SetStatusLabel(TCP1);
		Listening = True;
	}
	else
	{
		TCP1->Close();
		SetStatusLabel(TCP1);
		Listening = False;   
	}
}

/******************************************************************************/

void __fastcall TASFOrbServer::TCP1ConnectionRequest(TObject *Sender,
	int requestID)
{
	TTCP *socket;

	try
	{
		socket = new TTCP(this);
		socket->Accept(requestID);
		SetStatusLabel(socket);
		GetFulfiller().accept(*socket);
	}
	catch (...)
	{
	}

	socket->Free();

	SetStatusLabel(TCP1);
}

/******************************************************************************/

void __fastcall TASFOrbServer::ExitBitBtnClick(TObject *Sender)
{
	Close();
}

/******************************************************************************/

void __fastcall TASFOrbServer::ListBox1Click(TObject *Sender)
{
	if (ListBox1->ItemIndex != -1)
		ItemMem->Text = ListBox1->Items->Strings[ListBox1->ItemIndex];
	else
		ItemMem->Text = "";
}

/******************************************************************************/

void TASFOrbServer::SetStatusLabel(TTCP *tcp)
{
	switch (tcp->State)
	{
		case sckClosed:
			StatusLbl->Caption = "Closed.";
			break;
		case sckOpen:
			StatusLbl->Caption = "Open.";
			break;
		case sckListening:
			StatusLbl->Caption = "Listening...";
			break;
		case sckConnectionPending:
			StatusLbl->Caption = "Connection pending...";
			break;
		case sckResolvingHost:
			StatusLbl->Caption = "Resolving host...";
			break;
		case sckHostResolved:
			StatusLbl->Caption = "Host resolved...";
			break;
		case sckConnecting:
			StatusLbl->Caption = "Connecting...";
			break;
		case sckConnected:
			StatusLbl->Caption = "Connected...";
			break;
		case sckClosing:
			StatusLbl->Caption = "Peer is closing the connection...";
			break;
		case sckError:
			StatusLbl->Caption = "Error.";
			break;
	}
}

/******************************************************************************/
/******************************************************************************/

