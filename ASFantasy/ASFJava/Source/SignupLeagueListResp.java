/* SignupLeagueListResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class SignupLeagueListResp implements Streamable
{
	public Vector fElementVector = null;

	/**************************************************************************/

	public SignupLeagueListResp()
	{
		fElementVector = new Vector();
	}

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		SignupLeagueListElement element;

		short count;
		int i;

		// Read list of SignupLeagueListElement
		count = stream.readShort();
		for(i = 0; i < count; i++)
		{
			element = new SignupLeagueListElement();
			element.readFromFiler(stream);

			fElementVector.addElement(element);
		}

	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
