/* TFullName.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class TFullName implements Streamable
{
	String fLastName = new String();
	String fFirstName = new String();
	String fMidInit = new String();

	/**************************************************************************/

	public void clear()
	{
	    fLastName = new String();
	    fFirstName = new String();
	    fMidInit = new String();
	}
	
	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fLastName = stream.readUTF();
		fFirstName = stream.readUTF();
		fMidInit = stream.readUTF();
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeUTF(fLastName);
		stream.writeUTF(fFirstName);
		stream.writeUTF(fMidInit);
	}                         

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
	
	/**************************************************************************/

	public String buildFullName()
	{
		String str = new String();

		if((fFirstName != null) && (fFirstName.length() > 0))
		{
			str = fFirstName;
			
			if((fMidInit != null) && (fMidInit.length() > 0))
				str += " " + fMidInit + ".";
		}
		if((fLastName != null) && (fLastName.length() > 0))
		{
			if(str.length() != 0)
				str += " ";
			str += fLastName;
		}

		return(str);
	}        
			  
	/**************************************************************************/

	public String buildRevFullName()
	{
		String str = new String();

		if((fLastName != null) && (fLastName.length() > 0))
			str = fLastName;
		if((fFirstName != null) && (fFirstName.length() > 0))
		{
			if(str.length() != 0)
				str += ", ";
			str += fFirstName;
			
			if((fMidInit != null) && (fMidInit.length() > 0))
				str += " " + fMidInit + ".";
		}

		return(str);
	}                  

	/**************************************************************************/

	int compare(TFullName rhs)
	{
		int rc;

		if((rc = TAGNativeCompare.compareString(fLastName,rhs.fLastName)) != 0)
			return(rc);
			
		if((rc = TAGNativeCompare.compareString(fFirstName,rhs.fFirstName)) != 0)
			return(rc);
			
		return(TAGNativeCompare.compareString(fMidInit,rhs.fMidInit));
	}                                               
	
}              

/******************************************************************************/
/******************************************************************************/
