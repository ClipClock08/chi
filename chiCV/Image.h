#pragma once
#include <opencv2\highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <vector>
#include <math.h>
#include <iostream>

class Image
{
	int N=10;
public:

	Image();
	void set_size(int _N);
	int get_size();
	std::vector<std::vector<double>> get_avg(cv::Mat I);
	void Interp(cv::Mat I, cv::Mat& Dst);
	void histogramEqualization(cv::Mat I, cv::Mat& dst);
	void normalizedColor(cv::Mat I, cv::Mat& dst);
	void simpleCorrection(cv::Mat I, cv::Mat &img_clahe);

	~Image();
};

