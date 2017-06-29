#include "Image.h"
using std::vector;
using cv::Mat;
using namespace cv;

Image::Image()
{
	//N = 10;
}
void Image::set_size(int _N)
{
	N = _N;
}
int Image::get_size()
{
	return N;
}

std::vector<std::vector<double>> Image::get_avg(Mat I)
{
	int newN = N;
	if (newN > min(I.cols, I.rows))
		newN = min(I.cols, I.rows);

	double Avg;
	vector<vector<double>> A;
	A.resize(newN);
	for (int i = 0; i < newN; i++)
		A[i].resize(newN);
	for (int i = 0; i < newN; i++) {
		for (int j = 0; j < newN; j++) {
			for (int x = 0; x < I.cols / newN; x++) {
				for (int y = 0; y < I.rows / newN; y++) {
					A[i][j] += (I.at<cv::Vec3b>(cv::Point(i * I.cols / newN + x, j * I.rows / newN + y)).val[0] +
						I.at<cv::Vec3b>(cv::Point(i * I.cols / newN + x, j * I.rows / newN + y)).val[1] +
						I.at<cv::Vec3b>(cv::Point(i * I.cols / newN + x, j * I.rows / newN + y)).val[2]) / 3;
				}
			}
			A[i][j] /= I.cols * I.rows / (newN*newN);
		}
	}
	return A;
}

void Image::Interp(Mat I, Mat &Dst)
{
	int newN = N;
	if (newN > min(I.cols, I.rows))
		newN = min(I.cols, I.rows);

	Dst = I.clone();
	double W = double(I.cols) / double(newN);
	double H = double(I.rows) / double(newN);
	auto A = Image::get_avg(I);
	double Avg = 0;

	for (int i = 0; i < newN; i++) {
		for (int j = 0; j < newN; j++) {
			Avg += A[i][j];
		}
	}

	Avg /= newN*newN;

	for (int x = 0; x < I.cols; x++) {
		for (int y = 0; y < I.rows; y++) {
			int i = double(x) / W;
			int j = double(y) / H;

			vector<int> B;
			B.resize(8);
			if (x - i * W <= ((W) / 2) && y - j * H <= ((H) / 2))
			{
				B[0] = i - 1;
				B[1] = j - 1;
				B[2] = i;
				B[3] = j - 1;
				B[4] = i - 1;
				B[5] = j;
				B[6] = i;
				B[7] = j;
			}
			if (x - i * W >= ((W) / 2) && y - j * H <= ((H) / 2))
			{
				B[0] = i;
				B[1] = j - 1;
				B[2] = i + 1;
				B[3] = j - 1;
				B[4] = i;
				B[5] = j;
				B[6] = i + 1;
				B[7] = j;
			}
			if (x - i * W <= ((W) / 2) && y - j * H >= ((H) / 2))
			{
				B[0] = i - 1;
				B[1] = j;
				B[2] = i;
				B[3] = j;
				B[4] = i - 1;
				B[5] = j + 1;
				B[6] = i;
				B[7] = j + 1;
			}
			if (x - i * W >= ((W) / 2) && y - j * H >= ((H) / 2))
			{
				B[0] = i;
				B[1] = j;
				B[2] = i + 1;
				B[3] = j;
				B[4] = i;
				B[5] = j + 1;
				B[6] = i + 1;
				B[7] = j + 1;
			}

			for (int k = 0; k < 8; k++)
			{
				if (B[k] <= 0)
					B[k] = 0;
				if (B[k] >= newN)
					B[k] = newN - 1;
			}

			double dx = (x) - (B[0] * W);
			double dy = (y) - (B[1] * H);

			dx /= double(W);
			dy /= double(H);

			double Ndx = 1 - dx;
			double Ndy = 1 - dy;

			double In = (A[B[0]][B[1]])*Ndx*Ndy + (A[B[2]][B[3]])*dx*Ndy + (A[B[4]][B[5]])*Ndx*dy + (A[B[6]][B[7]])*dx*dy;

			for (int c = 0; c < 3; c++)
			{
				if (I.at<Vec3b>(Point(x, y)).val[c] + Avg - In <= 255 && I.at<Vec3b>(Point(x, y)).val[c] + Avg - In >= 0)
					Dst.at<Vec3b>(Point(x, y)).val[c] += Avg - In;
				else if (I.at<Vec3b>(Point(x, y)).val[c] + Avg - In > 255)
					Dst.at<Vec3b>(Point(x, y)).val[c] = 255;
				else if (I.at<Vec3b>(Point(x, y)).val[c] + Avg - In < 0)
					Dst.at<Vec3b>(Point(x, y)).val[c] = 0;
			}
		}
	}
}

void Image::histogramEqualization(Mat I, Mat &dst)
{
	dst = I.clone();
	Mat ch[3];
	Mat res[3];
	split(I, ch);
	//cvtColor(I, I, CV_BGR2GRAY);
	for(int i = 0; i < 3; i++)
	equalizeHist(ch[i], res[i]);
	for(int x = 0; x < dst.cols; x++){
		for (int y = 0; y < dst.rows; y++) {
			for(int c = 0; c < 3; c++)
			dst.at<Vec3b>(Point(x, y)).val[c] = res[c].at<uchar>(Point(x, y));
		}
	}
}

void Image::normalizedColor(Mat I, Mat& dst)
{
	double Mu[3] = { 0,0,0 }; // Math waiting
	double Desp[3] = { 0,0,0 }, standartDev[3] = { 0,0,0 };
	dst = I.clone();

	for (int i = 0; i < I.cols; i++)
		for (int j = 0; j < I.rows; j++)
			for (int c = 0; c < 3; c++)
				Mu[c] += I.at<Vec3b>(Point(i, j)).val[c];
	for(int c = 0; c < 3; c++) Mu[c] /= I.cols * I.rows;

	for (int i = 0; i < I.cols; i++){
		for (int j = 0; j < I.rows; j++)
		{
			for (int c = 0; c < 3; c++) 
			{
				Desp[c] = I.at<Vec3b>(Point(i, j)).val[c] - Mu[c];
				Desp[c] *= Desp[c];
				Desp[c] += Desp[c];
			}
		}
	}
	for (int c = 0; c < 3; c++)
	{
		Desp[c] /= I.cols * I.rows;
		standartDev[c] = sqrt(Desp[c]);
	}
	
	for (int x = 0; x < I.cols; x++) {
		for (int y = 0; y < I.rows; y++) {
			for (int c = 0; c < 3; c++)
			{
				if ((I.at<Vec3b>(Point(x, y)).val[c] - Mu[c]) / standartDev[c] <= 255 && (I.at<Vec3b>(Point(x, y)).val[c] - Mu[c]) / standartDev[c] >= 0)
					dst.at<Vec3b>(Point(x, y)).val[c] = (I.at<Vec3b>(Point(x, y)).val[c] - Mu[c]) / standartDev[c];
				else if ((I.at<Vec3b>(Point(x, y)).val[c] - Mu[c]) / standartDev[c] > 255)
					dst.at<Vec3b>(Point(x, y)).val[c] = 255;
				else if ((I.at<Vec3b>(Point(x, y)).val[c] - Mu[c]) / standartDev[c] < 0)
					dst.at<Vec3b>(Point(x, y)).val[c] = 0;
			}
		}
	}
}

void Image::simpleCorrection(cv::Mat I, cv::Mat& img_clahe)
{
	cv::Mat dst3 = I.clone();
	cvtColor(I, dst3, CV_BGR2Lab);
	// Extract the L channel
	std::vector<cv::Mat> lab_planes(3);
	cv::split(dst3, lab_planes);  // now we have the L image in lab_planes[0]			
								 // apply the CLAHE algorithm to the L channel
	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
	clahe->setClipLimit(4);
	clahe->apply(lab_planes[0], dst3);

	// Merge the the color planes back into an Lab image
	dst3.copyTo(lab_planes[0]);
	cv::merge(lab_planes, dst3);

	// convert back to RGB
	cv::cvtColor(dst3, img_clahe, CV_Lab2BGR);
}



Image::~Image()
{
}
