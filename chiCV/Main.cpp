//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/core.hpp"
//#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
//#include <vector>
//
//using namespace cv;
//using namespace std;
//
//
//IplImage* image = 0;
//IplImage* dst = 0;
//
//void Osv(int argc, const char** argv)
//{
//	 им€ картинки задаЄтс€ первым параметром
//	char* filename = argc == 2 ? argv[1] : "Image0.jpg";
//	 получаем картинку
//	image = cvLoadImage(filename, 1);
//	 клонируем картинку 
//	dst = cvCloneImage(image);
//
//	printf("[i] image: %s\n", filename);
//	assert(image != 0);
//
//	 окно дл€ отображени€ картинки
//	cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
//	cvNamedWindow("smooth", CV_WINDOW_AUTOSIZE);
//
//	 сглаживаем исходную картинку
//	cvSmooth(image, dst, CV_BLUR_NO_SCALE, 3, 3);
//
//	 показываем картинку
//	cvShowImage("original", image);
//	cvShowImage("smooth", dst);
//
//	 ждЄм нажати€ клавиши
//	cvWaitKey(0);
//
//	 освобождаем ресурсы
//	cvReleaseImage(&image);
//	cvReleaseImage(&dst);
//	 удал€ем окно
//	cvDestroyWindow("original");
//	cvDestroyWindow("smooth");
//}
//void camera(int argc, const char** argv)
//{
//	 получаем любую подключЄнную камеру
//	CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY);
//	assert(capture);
//
//	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);//1920); 
//	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);//1080); 
//
//	 узнаем ширину и высоту кадра
//	double width = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
//	double height = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
//	printf("[i] %.0f x %.0f\n", width, height);
//
//	IplImage* frame = 0;
//
//	cvNamedWindow("capture", CV_WINDOW_AUTOSIZE);
//
//	printf("[i] press Enter for capture image and Esc for quit!\n\n");
//	int counter = 0;
//	char filename[512];
//
//	while (true) {
//		 получаем кадр
//		frame = cvQueryFrame(capture);
//
//		 показываем
//		cvShowImage("capture", frame);
//
//		char c = cvWaitKey(33);
//		if (c == 27) { // нажата ESC
//			break;
//		}
//		else if (c == 13) { // Enter
//							 сохран€ем кадр в файл
//			sprintf(filename, "Photo%d.jpg", counter);
//			printf("[i] capture... %s\n", filename);
//			cvSaveImage(filename, frame);
//			counter++;
//		}
//	}
//	
//	 освобождаем ресурсы
//	cvReleaseCapture(&capture);
//	cvDestroyWindow("capture");
//}
//
//void simple(int argc, const char** argv)
//{
//	double alpha = 1.0; /*< Simple contrast control */
//	int beta = 0;       /*< Simple brightness control */
//	Mat image = imread("test.jpg");
//	Mat new_image = Mat::zeros(image.size(), image.type());
//	cout << " Basic Linear Transforms " << endl;
//	cout << "-------------------------" << endl;
//	cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
//	cout << "* Enter the beta value [0-100]: ";    cin >> beta;
//	for (int y = 0; y < image.rows; y++) {
//		for (int x = 0; x < image.cols; x++) {
//			for (int c = 0; c < 3; c++) {
//				new_image.at<Vec3b>(y, x)[c] =
//					saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
//			}
//		}
//	}
//	namedWindow("Original Image", WINDOW_AUTOSIZE);
//	namedWindow("New Image", WINDOW_AUTOSIZE);
//	imshow("Original Image", image);
//	imshow("New Image", new_image);
//	waitKey();
//	destroyWindow("New Image");
//	destroyWindow("Original Image");
//}
//
//void Menu()
//{
//	cout << "1.Osveshenie" << endl;
//	cout << "2.Camera" << endl;
//	cout << "3.BrightnessAndContrastAuto" << endl;
//	cout << "----------------" << "\n\n";
//	cout << "0.Exit" << endl;
//}
//int main(int argc, const char** argv)
//{
//	setlocale(LC_ALL, "RUS");
//	int punkt = 0;
//	do {
//		Menu();
//		cout << "¬ведите пункт меню" << endl;
//		cin >> punkt;
//		if (punkt >= 0 && punkt <= 3)
//		{
//			switch (punkt)
//			{
//			case 0:
//				exit(1);
//				break;
//			case 1:Osv(argc, argv);
//				break;
//			case 2:camera(argc, argv);
//				break;
//			case 3:simple(argc, argv); break;
//			}
//		}
//		else
//		{
//			cout << "¬ведите корретное значени€ 0-3" << endl;
//			system("pause");
//		}
//		system("cls");
//		} while (true);
//	
//	return 0;
//}