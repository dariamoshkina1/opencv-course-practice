package lab0_moshkina;

import org.opencv.core.*;
import org.opencv.highgui.Highgui;


public class FuncTest {

	public static void main(String[] args) {
		System.loadLibrary( Core.NATIVE_LIBRARY_NAME );
	    	
		Funcs img1 = new Funcs(Highgui.imread("D:/test.png"));
		Funcs img2 = new Funcs(Highgui.imread("D:/test.png"));
		Funcs img3 = new Funcs(Highgui.imread("D:/test.png"));
		
		img1.DoCanny();
		new LoadImage("D:/Canny.jpg", img1.mat, "Canny");
		
		img2.DoBlur();
		new LoadImage("D:/Blur.jpg", img2.mat, "Blur");
		
		img3.DoHoughLines();
		new LoadImage("D:/HoughLines.jpg", img3.mat, "HoughLines");

	}

}


