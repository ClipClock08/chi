#include <cstdio>
#include <cstdlib>
#include "Image.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	int N;
	Image img;
	cout << "Size of N: ";
	cin >> N;
	img.set_size(N);
	Mat I = imread("test.jpg");
	imshow("Main", I);
	Mat Dst;
	img.Interp(I, Dst);
	imshow("Result", Dst);
	waitKey(0);
	//destroyWindow("Result");
	//Mat I2 = imread("pic1.png");
	Mat dst, dst2, dst3;
	img.histogramEqualization(I, dst);
	imshow("Result2", dst);
	waitKey(0);
	//destroyWindow("Result2");
	img.normalizedColor(I, dst2);
	imshow("Result3", dst2);
	waitKey(0);
	Mat img_clahe;
	img.simpleCorrection(I, dst3, img_clahe);
	imshow("ResultClashe", img_clahe);
	waitKey(0);
	return 0;
}