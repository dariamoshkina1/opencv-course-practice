package lab0_moshkina;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;

import org.opencv.core.Mat;
import org.opencv.highgui.Highgui;

public class LoadImage extends JFrame{
	public LoadImage(String imgStr,Mat m, String title)
	{
	Highgui.imwrite(imgStr,m);
	JFrame frame = new JFrame(title);
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	 
	frame.setResizable(true);
	frame.setLocationRelativeTo(null);
	 
	// Inserts the image icon
	ImageIcon image = new ImageIcon(imgStr);
	frame.setSize(image.getIconWidth()+10,image.getIconHeight()+35);
	// Draw the Image data into the BufferedImage
	JLabel label1 = new JLabel(" ", image, JLabel.CENTER);
	frame.getContentPane().add(label1);
	 
	frame.validate();
	frame.setVisible(true);}

}
