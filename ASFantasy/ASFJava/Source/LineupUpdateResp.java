/* LineupUpdateResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class LineupUpdateResp implements Streamable
{
	//no data
	
	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		// nothing to read
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		// nothing to write
	}                     

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
