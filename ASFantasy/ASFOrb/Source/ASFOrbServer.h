/* ASFOrbServer.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFOrbServerH
#define ASFOrbServerH


#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>

#include "FulfillerNotify.h"
#include "SocketFulfiller.h"
#include <vcl\ISP.hpp>
#include <vcl\OleCtrls.hpp>

using namespace tag;

/******************************************************************************/

class TASFOrbServerNotify : public TFulfillerNotify
{
private:
	TListBox *fListBox;
public:
	TASFOrbServerNotify();
	virtual void notify(const AnsiString &msg);
	void setListBox(TListBox &ListBox);
};

/******************************************************************************/

class TASFOrbServer : public TForm
{
__published:	// IDE-managed Components
	TPanel *HeaderPnl;
	TSpeedButton *ListeningSpeedButton;
	TLabel *PortLbl;
	TLabel *PortIDLbl;
	TPanel *MessagePnl;
	TLabel *MessageLbl;
	TMemo *ItemMem;
	TPanel *ExitPnl;
	TBitBtn *ExitBitBtn;
	TPanel *ListPnl;
	TListBox *ListBox1;
	TPanel *ServerStatePnl;
	TLabel *ServerStateLbl;
	TLabel *StatusLbl;
	TPanel *ServerMessagePnl;
	TLabel *ListLbl;
	TTCP *TCP1;
	
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall BeginListening(int PortID);
	void __fastcall ListeningSpeedButtonClick(TObject *Sender);
	void __fastcall TCP1ConnectionRequest(TObject *Sender, int requestID);
	void __fastcall ExitBitBtnClick(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
	
private:	// User declarations
	bool Listening;
	
public:		// User declarations
	__fastcall TASFOrbServer(TComponent* Owner);
	static TASFOrbServer* Open(System::TMetaClass* InstanceClass) throw(Exception);

protected:
	void SetStatusLabel(TTCP *tcp);
	
	virtual void Initialize() {}
	virtual void Release() {}
	
	// Must be defined by derived class.
	virtual int GetDefaultPortID(void) const = 0;
	virtual AnsiString GetApplicationTitle(void) const { return("ASFOrb"); }
	
	virtual TSocketFulfiller& GetFulfiller(void) = 0;
};


#endif //ASFOrbServerH
/******************************************************************************/
/******************************************************************************/

