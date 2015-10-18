package lab0_moshkina;

import org.opencv.core.*;
import org.opencv.imgproc.*;

public class Funcs {
	public Mat mat;
	
	public Funcs(Mat src) {
		this.mat = src;
	}
	
	void DoCanny() {
		Imgproc.Canny(mat, mat, 300, 600, 5, true);
	}
	
	void DoBlur() {
		Imgproc.blur(mat, mat, new Size(10,10));
	}
	
	void DoHoughLines() {
		Mat dst = new Mat();
		Mat cdst = new Mat();
		Imgproc.Canny(mat, dst, 50, 200, 3, true);
		Imgproc.cvtColor(dst, cdst, Imgproc.COLOR_GRAY2BGR);		
		Mat lines = new Mat();
		Imgproc.HoughLines(dst, lines, 1, Math.PI/180, 150, 0 ,0);
		for (int i = 0; i < lines.cols(); i++) {
			double rho = lines.get(0, i)[0];
			double theta = lines.get(0, i)[1];
			Point pt1 = new Point();
			Point pt2 = new Point();
			double a = Math.cos(theta), b=Math.sin(theta);
			double x0 = a*rho, y0 = b*rho;
			pt1.x = Math.round(x0+1000*(-b));
			pt1.y = Math.round(y0+1000*(a));
			pt2.x = Math.round(x0-1000*(-b));
			pt2.y = Math.round(y0-1000*(a));
			Core.line(mat, pt1, pt2, new Scalar(0,0,255), 2);
		}
	}
}
