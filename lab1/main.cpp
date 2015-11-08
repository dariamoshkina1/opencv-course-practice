#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int getNeighbourhoodSize(int distance){
	if (distance == 0){
		return 0;
	}
	if (distance == 1){
		return 1;
	}
	if (distance <= 3)
	{
		return 3;
	}
	if (distance <= 5)
	{
		return 5;
	}
	if (distance <= 7)
	{
		return 7;
	}
	else
	{
		return 9;
	}
}

unsigned char getFilteredPixelValue(Mat imgChannel, Mat integralChannel, int row, int col, int neighbourhoodSize){
	int k = 1;
	int pixelValue = 0;
	Point2i leftTop = Point2i(0, 0);
	Point2i rightTop = Point2i(0, 0);
	Point2i leftBottom = Point2i(0, 0);
	Point2i rightBottom = Point2i(0, 0);

	if (neighbourhoodSize > 1){
		for (int i = 0; i <= (neighbourhoodSize / 2); i++){
			if (row - i > 0) {
				for (int j = 0; j < (neighbourhoodSize / 2); j++){

					if (col - j > 0){
						leftTop.x = col - j;
						leftTop.y = row - i;
					}
					if (col + j < imgChannel.cols){
						rightTop.x = col + j;
						rightTop.y = row - i;
					}
				}
			}

			if (row + i < imgChannel.rows){
				for (int j = 0; j < (neighbourhoodSize / 2); j++){

					if (col - j > 0) {
						leftBottom.x = col - j;
						leftBottom.y = row + i;
					}

					if (col + j < imgChannel.cols){
						rightBottom.x = col + j;
						rightBottom.y = row + i;
					}
				}
			}
		}

		k = (rightBottom.x - leftBottom.x + 1)*(leftBottom.y - leftTop.y + 1);
		pixelValue = integralChannel.at<int>(leftTop.y, leftTop.x) +
			integralChannel.at<int>(rightBottom.y + 1, rightBottom.x + 1) -
			integralChannel.at<int>(rightTop.y, rightTop.x + 1) -
			integralChannel.at<int>(leftBottom.y + 1, leftBottom.x);
		return ((unsigned char)((pixelValue) / k));
	}
	else {
		return imgChannel.at<unsigned char>(row, col);
	}
}

int main(int argc, char** argv)
{
	Mat image = imread("D://test.png");
	vector<Mat> imgChannels(3);
	vector<Mat> distanceMap(3);
	vector<Mat> edged(3);
	vector<Mat> binary(3);
	vector<Mat> blurred(3);
	vector<Mat> integralChannels(3);
	vector<Mat> channelsCopy(3);

	if (!image.data)                              
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	imshow("Original image", image); 

	split(image, imgChannels);
	for (int i = 0; i < 3; i++) {
		blurred[i] = imgChannels[i].clone();
		Canny(imgChannels[i], edged[i], 100, 250, 3);
		threshold(edged[i], binary[i], 0, 255, THRESH_BINARY_INV);
		distanceTransform(binary[i], distanceMap[i], CV_DIST_L2, CV_DIST_MASK_PRECISE);
		integral(imgChannels[i], integralChannels[i], CV_32S);
		channelsCopy[i] = imgChannels[i].clone();
		for (int k = 0; k < imgChannels[i].rows; k++) {
			for (int j = 0; j < imgChannels[i].cols; j++) {
				int r = getNeighbourhoodSize((int)distanceMap[i].at<float>(k, j));
				imgChannels[i].at<unsigned char>(k, j) = getFilteredPixelValue(channelsCopy[i], integralChannels[i], k, j, r);
			}
		}
	}
	merge(imgChannels, image);
	imshow("Filtered image", image);
	waitKey(0);                                        
	return 0;
}