/*
    A basic extension of the java.applet.Applet class
 */

import java.awt.*;
import java.applet.*;

public class JavaTestApplet extends Applet {

	public void init() {
		super.init();

		// Take out this line if you don't use symantec.itools.net.RelativeURL
        symantec.itools.lang.Context.setDocumentBase(getDocumentBase());

		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(80,51);
		setBackground(new Color(12632256));
		fTestImgV = new symantec.itools.multimedia.ImageViewer();
		fTestImgV.reshape(0,0,80,51);
		add(fTestImgV);
		try {
			fTestImgV.setURL(new java.net.URL("http://www.affinitysports.com/Images/JavaTest.gif"));
		} catch (java.net.MalformedURLException error) {
		}
		//}}
	}

	public boolean handleEvent(Event event) {
		return super.handleEvent(event);
	}

	//{{DECLARE_CONTROLS
	symantec.itools.multimedia.ImageViewer fTestImgV;
	//}}
}
