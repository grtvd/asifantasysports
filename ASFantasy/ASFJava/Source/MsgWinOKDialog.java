
/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.awt.Button;
import java.awt.Frame;
import java.awt.Insets;
import java.awt.Label;
import java.awt.FlowLayout;
import java.net.URL;
import symantec.itools.multimedia.ImageViewer;
import symantec.itools.awt.util.dialog.ModalDialog;

/******************************************************************************/

public class MsgWinOKDialog extends Dialog
{
	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fBorderPnl;
	symantec.itools.awt.WrappingLabel fMsg;
	java.awt.Panel fBtnPnl;
	java.awt.Button fOKBtn;
	//}}

	/* Singleton, only one copy at a time. */
	private static MsgWinOKDialog fMsgWinDialog;
	private static Frame fMsgWinDialogParent;

	/**************************************************************************/

	private MsgWinOKDialog(Frame parent, String title, String message)
	{
		super(parent, title, false);

		//{{INIT_CONTROLS
		setLayout(new BorderLayout(0,0));
		addNotify();
		resize(insets().left + insets().right + 270,insets().top + insets().bottom + 200);
		setBackground(new Color(12632256));
		fBorderPnl = new symantec.itools.awt.BorderPanel();
		fBorderPnl.setLayout(new BorderLayout(0,0));
		fBorderPnl.reshape(insets().left + 0,insets().top + 0,270,169);
		add("Center", fBorderPnl);
		fBorderPnl.setPaddingTop(6);
		fBorderPnl.setIPadTop(6);
		fBorderPnl.setIPadBottom(6);
		fBorderPnl.setIPadSides(6);
		fBorderPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fMsg = new symantec.itools.awt.WrappingLabel();
		fMsg.reshape(0,0,247,143);
		fBorderPnl.add("Center", fMsg);
		fMsg.setText("Message goes here!");
		fBtnPnl = new java.awt.Panel();
		fBtnPnl.setLayout(new FlowLayout(FlowLayout.CENTER,15,15));
		fBtnPnl.reshape(insets().left + 0,insets().top + 169,270,31);
		add("South", fBtnPnl);
		fOKBtn = new java.awt.Button("OK");
		fOKBtn.reshape(119,5,31,21);
		fBtnPnl.add(fOKBtn);
		setTitle("");
		//}}

		fMsg.setText(message);

		Dimension parentDim = getToolkit().getScreenSize();
		Dimension dim = size();
		move(((parentDim.width - dim.width) / 2),
			((parentDim.height - dim.height) / 2));
	}

	/**************************************************************************/

    public static Frame getFrame(Component component)
    {
        Component c = component;

        if(c instanceof Frame)
            return (Frame)c;

        while((c = c.getParent()) != null) {
            if(c instanceof Frame)
                return (Frame)c;
        }
        return null;
    }

	/**************************************************************************/
/*

	public boolean handleEvent(Event evt) 
	{
		if(evt.id == Event.WINDOW_DESTROY)
		{
			if(fMsgWinDialog != null)
				fMsgWinDialog.dispose();

			if(fMsgWinDialogParent != null)
				fMsgWinDialogParent.requestFocus();
				
			fMsgWinDialog = null;
			fMsgWinDialogParent = null;
		}
		
		return(false);
	}

*/
	/**************************************************************************/

	public boolean action(Event evt,Object arg)
	{
		if(evt.id == Event.ACTION_EVENT)
		{
			if(evt.target == fOKBtn)
				dispose();
			else
				return false;
		}
		else
			return false;

		return true;
	}

	/**************************************************************************/

	public static void Msg(Component parent,int flag,String msg)
	{
		if(fMsgWinDialog != null)
			fMsgWinDialog.dispose();

		fMsgWinDialog = null;
		fMsgWinDialogParent = null;
		
		fMsgWinDialogParent = MsgWinOKDialog.getFrame(parent);
		fMsgWinDialog = new MsgWinOKDialog(fMsgWinDialogParent,"" /*"Error"*/,msg);
		fMsgWinDialog.show();

		//return MWR_OK;
	}

	/**************************************************************************/
}

/******************************************************************************/
/******************************************************************************/
