//
//#include <math.h>
//#include <vector>
//#include <opencv2/opencv.hpp>
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/core/core.hpp"
//
//#include <stdlib.h>
//#include <stdio.h>
//
//using namespace cv;
//

/*
Returns measure of diversity between two pixels. The more pixels are different the bigger output number.
Usually it's a good idea to use Euclidean distance but there are variations.
*/
//double distance_squared(unsigned char x, unsigned char y)
//{
//	unsigned char zmax = max(x, y);
//	unsigned char zmin = min(x, y);
//	return (zmax - zmin)*(zmax - zmin);
//}
//
///*
//Returns weight of interaction between regions: the more dissimilar are regions the less resulting influence.
//Usually decaying exponent is used here. If distance is Euclidean, being combined, they form a typical Gaussian function.
//*/
//double decay_function(double x, double dispersion)
//{
//	return exp(-x / dispersion);
//}
//
//int conform_8bit(double x)
//{
//	if (x < 0)
//		return 0;
//	else if (x > 255)
//		return 255;
//	else
//		return static_cast<int>(x);
//}
//
//
//double distance_over_neighbourhood(unsigned char* data, int x00, int y00, int x01, int y01, int radius, int step)
//{
//	double dispersion = 15000.0; //should be manually adjusted
//	double accumulator = 0;
//	for (int x = -radius; x < radius + 1; ++x)
//	{
//		for (int y = -radius; y < radius + 1; ++y)
//		{
//			accumulator += distance_squared(static_cast<unsigned char>(data[(y00 + y)*step + x00 + x]), static_cast<unsigned char>(data[(y01 + y)*step + x01 + x]));
//		}
//	}
//	return decay_function(accumulator, dispersion);
//}
//
//
//int main(int argc, char* argv[])
//{
//	int similarity_window_radius = 3; //may vary; 2 is enough for text filtering
//	char* imageName = "text_noised_30.png";
//	IplImage* image = 0;
//	image = cvLoadImage(imageName, CV_LOAD_IMAGE_GRAYSCALE);
//	if (image == NULL) {
//		printf("Can not load image\n");
//		getchar();
//		exit(-1);
//	}
//
//	CvSize currentSize = cvGetSize(image);
//	int width = currentSize.width;
//	int height = currentSize.height;
//	int step = image->widthStep;
//	unsigned char *data = reinterpret_cast<unsigned char *>(image->imageData);
//	vector
//	//External cycle
//	for (int x = similarity_window_radius + 1; x < width - similarity_window_radius - 1; ++x)
//	{
//		printf("x: %d/%d\n", x, width - similarity_window_radius - 1);
//		for (int y = similarity_window_radius + 1; y < height - similarity_window_radius - 1; ++y)
//		{
//			//Inner cycle: computing weight map
//			vector<double> weight_map(width*height, 0);
//			double* weight_data = &weight_map[0];
//			double norm = 0;
//			for (int xx = similarity_window_radius + 1; xx < width - similarity_window_radius - 1; ++xx)
//				for (int yy = similarity_window_radius + 1; yy < height - similarity_window_radius - 1; ++yy)
//				{
//					double weight = distance_over_neighbourhood(data, x, y, xx, yy, similarity_window_radius, step);
//					norm += weight;
//					weight_map[yy*step + xx] = weight;
//				}
//			//After all weights are known, one can compute new value in pixel
//			for (int xx = similarity_window_radius + 1; xx < width - similarity_window_radius - 1; ++xx)
//				for (int yy = similarity_window_radius + 1; yy < height - similarity_window_radius - 1; ++yy)
//					processed_data[y*step + x] += data[yy*step + xx] * weight_map[yy*step + xx] / norm;
//		}
//	}
//	//Transferring data from buffer to original image
//	for (int x = similarity_window_radius + 1; x < width - similarity_window_radius - 1; ++x)
//		for (int y = similarity_window_radius + 1; y < height - similarity_window_radius - 1; ++y)
//			data[y*step + x] = conform_8bit(processed_data[y*step + x]);
//	cvSaveImage("gray_denoised.png", image);
//
//	cvReleaseImage(&image);
//	return 0;
//}