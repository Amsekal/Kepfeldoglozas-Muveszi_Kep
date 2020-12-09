#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>
#include <iostream>



int main() {

	cv::Mat I = cv::imread("B:\\YS.jpg",1);
	cv::Mat I2(I.size(), CV_8UC3);
	cv::Mat I3(I.size(), CV_8UC3);
	cv::Mat I4(I.size(), CV_8UC3);
	cv::Mat Best(I.size(), CV_8UC3);
	cv::Mat Filter(I.size(), CV_8UC3);
	cv::Mat Filter2(I.size(), CV_8UC3);
	cv::Mat Filter3(I.size(), CV_8UC3);
	
	cv::GaussianBlur(I, Filter3, cv::Size(53, 53),-1);
	cv::addWeighted(I, 1.5, Filter3, -0.5, 0, Filter3);
	cv::boxFilter(I, Filter, -1, cv::Size(53, 53));

	
	Filter2 = I - Filter;
	Best = I - Filter2;
	for (int i = 0; i < I.rows; ++i) {
		for (int j = 0; j < I.cols; ++j) {
			cv::Vec3b currentPixelGroup = I.at<cv::Vec3b>(i, j);
			cv::Vec3b nextPixelGroup = Filter2.at<cv::Vec3b>(i, j);
			currentPixelGroup[2] = nextPixelGroup[2] + nextPixelGroup[1] + nextPixelGroup[0];

			

			I2.at<cv::Vec3b>(i, j) = currentPixelGroup;
		}
	}



	for (int i = 0; i < I.rows; ++i) {
		for (int j = 0; j < I.cols; ++j) {
			cv::Vec3b currentPixelGroup = I.at<cv::Vec3b>(i, j);
			cv::Vec3b nextPixelGroup = Filter2.at<cv::Vec3b>(i, j);

			currentPixelGroup[0] = nextPixelGroup[2] + nextPixelGroup[1] + nextPixelGroup[0];
			


			I3.at<cv::Vec3b>(i, j) = currentPixelGroup;
		}
	}




	for (int i = 0; i < I.rows; ++i) {
		for (int j = 0; j < I.cols; ++j) {
			cv::Vec3b currentPixelGroup = I.at<cv::Vec3b>(i, j);
			cv::Vec3b nextPixelGroup = Filter2.at<cv::Vec3b>(i, j);

			currentPixelGroup[1] = nextPixelGroup[2]+ nextPixelGroup[1]+ nextPixelGroup[0];
			I4.at<cv::Vec3b>(i, j) = currentPixelGroup;
		}
	}
	cv::imshow("Eredti", I);
	cv::imshow("BlueChannel", I2);
	cv::imshow("Sarga", I3);
	//cv::imshow("BlueChannel4", I4);
	//cv::imshow("Filter", Filter2);
	//cv::imshow("Filter3", I+I2+I3+I4-Filter);
	cv::imshow("Kepregeny", Best);
	cv::imshow("Gold",Filter3+I3);
	cv::waitKey();

	return 0;
}