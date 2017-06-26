#include <cstdio>
#include <cstdlib>
#include <vector>
#include "spline.h"
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
using namespace cv;
using namespace std;

const int N = 50;
int main() {
	Mat I = imread("test.jpg");
	imshow("Main", I);
	vector<vector<double>> A;
	A.resize(N);
	for (int i = 0; i < N; i++)
		A[i].resize(N);
	double Avg = 0.0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			for (int x = 0; x < I.cols / N; x++) {
				for (int y = 0; y < I.rows / N; y++) {
					A[i][j] += (I.at<Vec3b>(Point(i * I.cols / N + x, j * I.rows / N + y)).val[0] +
						I.at<Vec3b>(Point(i * I.cols / N + x, j * I.rows / N + y)).val[1] +
						I.at<Vec3b>(Point(i * I.cols / N + x, j * I.rows / N + y)).val[2]) / 3;
				}
			}
			A[i][j] /= I.cols * I.rows / (N*N);
			Avg += A[i][j];
		}
	}

	Avg /= N*N;
	int W = I.cols / N;
	int H = I.rows / N;

	//for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < N; j++) {

	//		for (int x = 0; x < I.cols / N; x++) {
	//			for (int y = 0; y < I.rows / N; y++) {
	//				for (int c = 0; c < 3; c++) {
	//					if (I.at<Vec3b>(i, j)[c] < I.cols / N / 2)
	//						cout << "0" << endl;
	//				}
	//			}
	//		}
	//	}
	//}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			for (int x = 0; x < I.cols / N; x++) {
				for (int y = 0; y < I.rows / N; y++) {
					//for (int c = 0; c < 3; c++)
				//		if (I.at<Vec3b>(Point(i * I.cols / N + x, j * I.rows / N + y)).val[c] + Avg - A[i][j] <= 255 && I.at<Vec3b>(Point(i * I.cols / N + x, j * I.rows / N + y)).val[c] + Avg - A[i][j] >= 0)
							//I.at<Vec3b>(Point(i * I.cols / N + x, j * I.rows / N + y)).val[c] += Avg - A[i][j];
				}
			}
		}
	}

	cout << Avg << endl;
	//for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < N; j++) {
	//		cout << A[i][j] << " " ;
	//	}
	//	cout << endl;
	//}


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			for (int x = 0; x < I.cols / N; x++) {
				for (int y = 0; y < I.rows / N; y++) {
					vector<int> B;
					B.resize(8);
					if (x < (I.cols / N) / 2 && y < (I.rows / N) / 2)
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
					if (x >= (I.cols / N) / 2 && y < (I.rows / N) / 2)
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
					if (x < (I.cols / N) / 2 && y >= (I.rows / N) / 2)
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
					if (x >= (I.cols / N) / 2 && y >= (I.rows / N) / 2)
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

					for (int i = 0; i < 8; i++)
					{
						if (B[i] < 0)
							B[i] = 0;
						if (B[i] >= N)
							B[i] = N - 1;
					}
					double dx = (i*W + x) - (B[0] * W);
					double dy = (j*H + y) - (B[1] * H);
					dx /= double(W);
					dy /= double(H);
					double Ndx = 1 - dx;
					double Ndy = 1 - dy;
					double In = (A[B[0]][B[1]])*Ndx*Ndy + (A[B[2]][B[3]])*dx*Ndy + (A[B[4]][B[5]])*Ndx*dy + (A[B[6]][B[7]])*dx*dy;
					for (int c = 0; c < 3; c++)
					{
						if (I.at<Vec3b>(Point(i * I.cols / N + x, j * I.rows / N + y)).val[c] + Avg - In <= 255 && I.at<Vec3b>(Point(i * I.cols / N + x, j * I.rows / N + y)).val[c] + Avg - In >= 0)
							I.at<Vec3b>(Point(i * I.cols / N + x, j * I.rows / N + y)).val[c] += Avg - In;
						else if(I.at<Vec3b>(Point(i * I.cols / N + x, j * I.rows / N + y)).val[c] + Avg - In > 255)
							I.at<Vec3b>(Point(i * I.cols / N + x, j * I.rows / N + y)).val[c] = 255;
						else if (I.at<Vec3b>(Point(i * I.cols / N + x, j * I.rows / N + y)).val[c] + Avg - In < 0)
							I.at<Vec3b>(Point(i * I.cols / N + x, j * I.rows / N + y)).val[c] = 0;
					}	
				}
			}
		}
	}
	imshow("Result",I);
	waitKey(0);
	return 0;
}

