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
	Mat I = imread("test.jpg");//, CV_LOAD_IMAGE_COLOR);
	//I.at<Vec3b>(Point(x, y)).val[0] = 1;
	imshow("awd", I);
	//Mat I2;
//	//Сетка
//	for (int i = 0; i < I.rows; i++)
//		for (int j = 0; j < I.cols; j++)
//			if ((i % 20 == 10 && j % 2 == 1) ||
//				(j % 50 == 25 && i % 2 == 1))
//			{
//				I.at<Vec3b>(i, j)[0] = 255;
//				I.at<Vec3b>(i, j)[1] = 255;
//				I.at<Vec3b>(i, j)[2] = 255;
//			}
//	waitKey(0);
////	imwrite("test1.jpg", I);
//	imshow("image01_res.jpg", I);
	//waitKey(0);
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

	imshow("faff", I);
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
	imshow("kh",I);
	//cout << endl; cout << endl;

	//vector<vector<double>> B;
	//B.resize(N);
	//for (int i = 0; i < N; i++)
	//	B[i].resize(N-1);
	//for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < N - 1; j++) {
	//		B[i][j] = (A[i][j+1] + A[i][j]) / 2;
	//	}
	//}

	///*for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < N-1; j++) {
	//		cout << B[i][j] << " ";
	//	}
	//	cout << endl;
	//}*/

	//
	///*cout << endl << endl;
	//for (int i = 0; i < N - 1; i++) {
	//	for (int j = 0; j < N; j++) {
	//		cout << C[i][j] << " ";
	//	}
	//	cout << endl;
	//}*/

	//cout << endl << endl;

	//vector<double> X;
	//X.resize(N - 1);
	//for (int i = 0; i < N - 1; i++)
	//	X[i] = i + 1;

	//for (int i = 0; i < N; i++)
	//{
	//	tk::spline s;
	//	s.set_points(X, B[i]);    // currently it is required that X is already sorted
	//	cout << s(0.5) << " ";
	//	A[i][0] = s(0.5);
	//	for (int j = 0; j < N-1; j++)
	//	{
	//		cout << s(X[j] + 0.5) << " ";
	//		A[i][j + 1] = s(X[j] + 0.5);
	//	}
	//	cout << endl;
	//}

	//vector<vector<double>> C;
	//C.resize(N - 1);
	//for (int i = 0; i < N - 1; i++)
	//	C[i].resize(N);
	//for (int i = 0; i < N - 1; i++) {
	//	for (int j = 0; j < N; j++) {
	//		C[i][j] = (A[i][j] + A[i + 1][j]) / 2;
	//	}
	//}

	//cout << endl << endl;

	//vector<double> temp;
	//temp.resize(N - 1);
	//for (int i = 0; i < N; i++)
	//{
	//	for (int j = 0; j < N - 1; j++)
	//		temp[j] = C[j][i];
	//	tk::spline s;
	//	s.set_points(X, temp);    // currently it is required that X is already sorted
	//	cout << s(0.5) << " ";
	//	A[i][0] = s(0.5);
	//	for (int j = 0; j < N - 1; j++)
	//	{
	//		cout << s(X[j] + 0.5) << " ";
	//		A[i][j + 1] = s(X[j] + 0.5);
	//	}
	//	cout << endl;
	//}

	////Mat I2 = I;
	////I2 *= 2;
	////imshow("test2.jpg", I2);
	waitKey(0);
	return 0;
}

